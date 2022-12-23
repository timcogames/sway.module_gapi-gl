#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/glx11/canvas.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/math.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

std::shared_ptr<gapi::ShaderProgram> program = nullptr;
std::shared_ptr<gapi::IdGenerator> idGenerator = nullptr;
std::shared_ptr<gapi::Buffer> vtxBuffer = nullptr;
std::shared_ptr<gapi::Buffer> idxBuffer = nullptr;
std::shared_ptr<gapi::VertexAttribLayout> vtxAttribLayout = nullptr;
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

  auto *functions = new gapi::ConcreatePluginFunctionSet();
  gapi::pluginInitialize(functions);
  auto capability = functions->createCapability();

  gapi::ShaderCreateInfo vsoCreateInfo;
  vsoCreateInfo.type = gapi::ShaderType::VERT;
  vsoCreateInfo.code = "attribute vec3 attrib_pos; \
    void main() { \
      gl_Position = vec4(attrib_pos, 1.0); \
     }";

  gapi::ShaderCreateInfo fsoCreateInfo;
  fsoCreateInfo.type = gapi::ShaderType::FRAG;
  fsoCreateInfo.code = "void main() { \
      gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0); \
    }";

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
  vboCreateInfo.desc.byteStride = sizeof(math::VertexPosition);
  vboCreateInfo.desc.capacity = 3;
  std::array<float, 9> vertices = {-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0};
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

  drawCall = functions->createDrawCall();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    program->use();

    vtxBuffer->bind();
    vtxAttribLayout->enable();

    idxBuffer->bind();

    drawCall->execute(gapi::TopologyType::TRIANGLE_LIST, {vtxBuffer, idxBuffer}, core::ValueDataType::UInt);

    idxBuffer->unbind();

    vtxAttribLayout->disable();
    vtxBuffer->unbind();

    program->unuse();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
