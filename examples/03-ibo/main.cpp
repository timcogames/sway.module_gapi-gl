#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/math.hpp>
#include <sway/pltf/mac/dtpcanvas.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

std::shared_ptr<gapi::ConcreatePluginFunctionSet> functions = nullptr;
std::shared_ptr<gapi::Capability> capability = nullptr;
std::shared_ptr<gapi::ShaderProgram> program = nullptr;
gapi::IdGenerator::SharedPtr_t bufIdgen = nullptr;
std::shared_ptr<gapi::VertexAttribLayout> vtxAttribLayout = nullptr;
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
  vsoCreateInfo.code = "attribute vec3 attrib_pos; \
    void main() { \
      gl_Position = vec4(attrib_pos, 1.0); \
    }";

  gapi::ShaderCreateInfo fsoCreateInfo;
  fsoCreateInfo.type = gapi::ShaderType::Enum::FRAG;
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
  vboCreateInfo.desc.target = gapi::BufferTarget::Enum::ARRAY;
  vboCreateInfo.desc.usage = gapi::BufferUsage::Enum::STATIC;
  vboCreateInfo.desc.byteStride = sizeof(math::VertexPosition);
  vboCreateInfo.desc.capacity = 3;
  std::array<f32_t, 9> vertices = {-0.5F, -0.5F, 0.0F, 0.5F, -0.5F, 0.0F, 0.0F, 0.5F, 0.0F};
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

  drawCall = functions->createDrawCall();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    program->use();

    bufset.vbo->bind();
    vtxAttribLayout->enable();

    bufset.ebo->bind();

    drawCall->execute(gapi::TopologyType::Enum::TRIANGLE_LIST, bufset, core::ValueDataType::UINT);

    bufset.ebo->unbind();

    vtxAttribLayout->disable();
    bufset.vbo->unbind();

    program->unuse();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
