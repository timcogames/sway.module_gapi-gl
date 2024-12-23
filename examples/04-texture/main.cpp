#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/math.hpp>
#include <sway/pltf/mac/dtpcanvas.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

gapi::IdGenerator::SharedPtr_t bufIdgen = nullptr;
gapi::IdGenerator::SharedPtr_t texIdgen = nullptr;
std::shared_ptr<gapi::ConcreatePluginFunctionSet> functions = nullptr;
std::shared_ptr<gapi::Capability> capability = nullptr;
std::shared_ptr<gapi::ShaderProgram> program = nullptr;
std::shared_ptr<gapi::VertexAttribLayout> vtxAttribLayout = nullptr;
std::shared_ptr<gapi::Texture> texture = nullptr;
std::shared_ptr<gapi::TextureSampler> textureSampler = nullptr;
std::shared_ptr<gapi::DrawCall> drawCall = nullptr;

auto main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) -> int {
  pltf::WindowInitialInfo windowInitialInfo;
  windowInitialInfo.title = "examples";
  windowInitialInfo.size.normal = math::size2i_t(800, 600);
  windowInitialInfo.fullscreen = false;
  windowInitialInfo.resizable = false;

  auto connection = std::make_shared<pltf::DTPScreenConnection>();
  auto canvas = std::make_shared<pltf::DTPCanvas>(connection, windowInitialInfo);

  canvas->show();
  canvas->getContext()->makeCurrent();

  functions = std::make_shared<gapi::ConcreatePluginFunctionSet>();
  gapi::pluginInitialize(functions.get());
  capability = functions->createCapability();

  gapi::ShaderCreateInfo vsoCreateInfo;
  vsoCreateInfo.type = gapi::ShaderType::Enum::VERT;
  vsoCreateInfo.code = "attribute vec3 attrib_pos;"
                       "attribute vec2 attrib_texcoord_0;"
                       "varying vec2 io_texcoord;"
                       "void main() {"
                       "  gl_Position = vec4(attrib_pos, 1.0);"
                       "  io_texcoord = attrib_texcoord_0;"
                       "}";

  gapi::ShaderCreateInfo fsoCreateInfo;
  fsoCreateInfo.type = gapi::ShaderType::Enum::FRAG;
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
  vboCreateInfo.desc.target = gapi::BufferTarget::Enum::ARRAY;
  vboCreateInfo.desc.usage = gapi::BufferUsage::Enum::STATIC;
  vboCreateInfo.desc.byteStride = sizeof(math::VertexTexCoord);
  vboCreateInfo.desc.capacity = 3;
  std::array<f32_t, 9 /*pos*/ + 6 /*texcoord*/> vertices = {
      +0.5F, -0.5F, 0.0F, 0.0F, 0.0F,  // v1
      -0.5F, -0.5F, 0.0F, 1.0F, 0.0F,  // v2
      +0.0F, +0.5F, 0.0F, 0.5F, 1.0F  // v3
  };
  vboCreateInfo.data = vertices.data();

  gapi::BufferCreateInfo eboCreateInfo;
  eboCreateInfo.desc.target = gapi::BufferTarget::Enum::ELEMENT_ARRAY;
  eboCreateInfo.desc.usage = gapi::BufferUsage::Enum::STATIC;
  eboCreateInfo.desc.byteStride = sizeof(u32_t);
  eboCreateInfo.desc.capacity = 3;
  std::array<u32_t, 3> indices = {0, 1, 2};
  eboCreateInfo.data = indices.data();

  bufIdgen = functions->createBufferIdGenerator();

  gapi::BufferSet bufset;
  bufset.vbo = functions->createBuffer(bufIdgen, vboCreateInfo);
  bufset.ebo = functions->createBuffer(bufIdgen, eboCreateInfo);

  vtxAttribLayout = functions->createVertexAttribLayout(program);
  vtxAttribLayout->addAttribute(
      gapi::VertexAttribDescriptor::merge<math::vec3f_t>(gapi::VertexSemantic::POS, false, true));
  vtxAttribLayout->addAttribute(
      gapi::VertexAttribDescriptor::merge<math::vec2f_t>(gapi::VertexSemantic::TEXCOORD_0, false, true));

  auto depth = 4;
  auto size = math::size2i_t(64, 64);
  std::vector<u8_t> image(size.getW() * size.getH() * depth);
  for (auto y = 0; y < size.getH(); y++) {
    for (auto x = 0; x < size.getW(); x++) {
      auto col = (((x & 0x8) == 0) ^ ((y & 0x8) == 0)) * 255;
      image[(y * size.getW() + x) * depth + 0] = (u8_t)col;
      image[(y * size.getW() + x) * depth + 1] = (u8_t)col;
      image[(y * size.getW() + x) * depth + 2] = (u8_t)col;
      image[(y * size.getW() + x) * depth + 3] = 255;
    }
  }

  // s8_t *texdata = new s8_t[depth * wdt * hgt];
  // for (auto y = 0; y < hgt; ++y) {
  //   for (auto x = 0; x < wdt; ++x) {
  //     i32_t c = (((y & 0x8) == 0) ^ ((x & 0x8)) == 0) * 255;

  //     texdata[y * wdt * depth + x * depth + 0] = c;  // red
  //     texdata[y * wdt * depth + x * depth + 1] = c;  // green
  //     texdata[y * wdt * depth + x * depth + 2] = c;  // blue
  //     texdata[y * wdt * depth + x * depth + 3] = 255;  // alpha
  //   }
  // }

  gapi::TextureCreateInfo createInfo;
  createInfo.target = gapi::TextureTarget::Enum::TEX_2D;
  createInfo.size = size;
  // createInfo.arraySize
  createInfo.format = gapi::PixelFormat::RGBA;
  createInfo.internalFormat = gapi::PixelFormat::RGBA;
  createInfo.dataType = core::ValueDataType::UBYTE;
  createInfo.pixels = (s8_t *)image.data();
  createInfo.mipLevels = 0;
  // createInfo.sampleCount

  // SAFE_DELETE_ARRAY(texdata);

  texIdgen = functions->createTextureIdGenerator();

  texture = functions->createTexture(texIdgen, createInfo);
  textureSampler = functions->createTextureSampler(texture);
  // texture->bind();
  textureSampler->setWrapMode(
      gapi::TextureWrap::Enum::REPEAT, gapi::TextureWrap::Enum::REPEAT, gapi::TextureWrap::Enum::REPEAT);
  textureSampler->setFilterMode(gapi::TextureFilter::Enum::NEAREST, gapi::TextureFilter::Enum::NEAREST);
  // texture->unbind();

  drawCall = functions->createDrawCall();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    const int TEXTURE_UNIT_ZERO = 0;
    program->setUniform1i("ufrm_diffuse", TEXTURE_UNIT_ZERO);
    program->use();

    texture->setActive(0);
    texture->bind();

    bufset.vbo->bind();
    vtxAttribLayout->enable();

    bufset.ebo->bind();

    drawCall->execute(gapi::TopologyType::Enum::TRIANGLE_LIST, bufset, core::ValueDataType::UINT);

    bufset.ebo->unbind();

    vtxAttribLayout->disable();
    bufset.vbo->unbind();

    texture->unbind();

    program->unuse();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
