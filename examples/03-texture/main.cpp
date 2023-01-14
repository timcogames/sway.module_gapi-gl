#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/glx11/canvas.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/math.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

std::shared_ptr<gapi::ConcreatePluginFunctionSet> functions = nullptr;
std::shared_ptr<gapi::Capability> capability = nullptr;
std::shared_ptr<gapi::ShaderProgram> program = nullptr;
std::shared_ptr<gapi::IdGenerator> idGenerator = nullptr;
std::shared_ptr<gapi::Buffer> vtxBuffer = nullptr;
std::shared_ptr<gapi::Buffer> idxBuffer = nullptr;
std::shared_ptr<gapi::VertexAttribLayout> vtxAttribLayout = nullptr;
std::shared_ptr<gapi::Texture> texture = nullptr;
std::shared_ptr<gapi::DrawCall> drawCall = nullptr;

int main(int argc, char *argv[]) {
  glx11::WindowInitialInfo windowInitialInfo;
  windowInitialInfo.title = "examples";
  windowInitialInfo.size.normal = math::size2i_t(800, 600);
  windowInitialInfo.fullscreen = false;
  windowInitialInfo.resizable = false;

  auto connection = std::make_shared<glx11::XScreenConnection>();
  auto canvas = std::make_shared<glx11::Canvas>(connection, windowInitialInfo);

  canvas->show();
  canvas->getContext()->makeCurrent();

  functions = std::make_shared<gapi::ConcreatePluginFunctionSet>();
  gapi::pluginInitialize(functions.get());
  capability = functions->createCapability();

  gapi::ShaderCreateInfo vsoCreateInfo;
  vsoCreateInfo.type = gapi::ShaderType::VERT;
  vsoCreateInfo.code = "attribute vec3 attrib_pos;"
                       "attribute vec2 attrib_texcoord_0;"
                       "varying vec2 io_texcoord;"
                       "void main() {"
                       "  gl_Position = vec4(attrib_pos, 1.0);"
                       "  io_texcoord = attrib_texcoord_0;"
                       "}";

  gapi::ShaderCreateInfo fsoCreateInfo;
  fsoCreateInfo.type = gapi::ShaderType::FRAG;
  fsoCreateInfo.code = "varying vec2 io_texcoord;"
                       "uniform sampler2D ufrm_diffuse;"
                       "void main() {"
                       "  gl_FragColor = texture2D(ufrm_diffuse, io_texcoord);"
                       "}";

  program = functions->createShaderProgram();
  program->attach(functions->createShader(vsoCreateInfo));
  program->attach(functions->createShader(fsoCreateInfo));

  try {
    program->link();
    program->validate();
  } catch (std::exception &exception) {
    throw;
  }

  gapi::BufferCreateInfo vboCreateInfo;
  vboCreateInfo.desc.target = gapi::BufferTarget::ARRAY;
  vboCreateInfo.desc.usage = gapi::BufferUsage::STATIC;
  vboCreateInfo.desc.byteStride = sizeof(math::VertexTexCoord);
  vboCreateInfo.desc.capacity = 3;
  std::array<f32_t, 9 /*pos*/ + 6 /*texcoord*/> vertices = {
      +0.5, -0.5, 0.0, 0.0, 0.0,  // v1
      -0.5, -0.5, 0.0, 1.0, 0.0,  // v2
      +0.0, +0.5, 0.0, 0.5, 1.0  // v3
  };
  vboCreateInfo.data = vertices.data();

  gapi::BufferCreateInfo iboCreateInfo;
  iboCreateInfo.desc.target = gapi::BufferTarget::ELEMENT_ARRAY;
  iboCreateInfo.desc.usage = gapi::BufferUsage::STATIC;
  iboCreateInfo.desc.byteStride = sizeof(u32_t);
  iboCreateInfo.desc.capacity = 3;
  std::array<u32_t, 3> indices = {0, 1, 2};
  iboCreateInfo.data = indices.data();

  idGenerator = functions->createIdGenerator();

  vtxBuffer = functions->createBuffer(idGenerator, vboCreateInfo);
  idxBuffer = functions->createBuffer(idGenerator, iboCreateInfo);
  vtxAttribLayout = functions->createVertexAttribLayout(program);
  vtxAttribLayout->addAttribute(
      gapi::VertexAttribDescriptor::merge<math::vec3f_t>(gapi::VertexSemantic::POS, false, true));
  vtxAttribLayout->addAttribute(
      gapi::VertexAttribDescriptor::merge<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0, false, true));

  auto size = math::size2i_t(64, 64);
  std::vector<u8_t> image(size.getW() * size.getH() * 4);
  for (auto y = 0; y < size.getH(); y++) {
    for (auto x = 0; x < size.getW(); x++) {
      auto col = (((x & 0x8) == 0) ^ ((y & 0x8) == 0)) * 255;
      image[(y * size.getW() + x) * 4 + 0] = (u8_t)col;
      image[(y * size.getW() + x) * 4 + 1] = (u8_t)col;
      image[(y * size.getW() + x) * 4 + 2] = (u8_t)col;
      image[(y * size.getW() + x) * 4 + 3] = 255;
    }
  }

  texture = functions->createTexture();
  texture->create(image.data(), size.getW(), size.getH());

  drawCall = functions->createDrawCall();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    const int TEXTURE_UNIT_ZERO = 0;
    program->setUniform1i("ufrm_diffuse", TEXTURE_UNIT_ZERO);
    program->use();

    texture->setActive(0);
    texture->bind();

    vtxBuffer->bind();
    vtxAttribLayout->enable();

    idxBuffer->bind();

    drawCall->execute(gapi::TopologyType::TRIANGLE_LIST, {vtxBuffer, idxBuffer}, core::ValueDataType::UInt);

    idxBuffer->unbind();

    vtxAttribLayout->disable();
    vtxBuffer->unbind();

    texture->unbind();

    program->unuse();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
