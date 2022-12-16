#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/glx11/canvas.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/math.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

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
  vsoCreateInfo.type = gapi::ShaderType::VERTEX;
  vsoCreateInfo.code = "attribute vec3 attr_position; \
    void main() { \
      gl_Position = vec4(attr_position, 1.0); \
     }";

  gapi::ShaderCreateInfo fsoCreateInfo;
  fsoCreateInfo.type = gapi::ShaderType::FRAGMENT;
  fsoCreateInfo.code = "void main() { \
      gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0); \
    }";

  auto program = functions->createShaderProgram();
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

  auto vboIdGenerator = functions->createIdGenerator();
  auto vbo = functions->createBuffer(vboIdGenerator, vboCreateInfo);
  auto vlayout = functions->createVertexAttribLayout(program);
  vlayout->addAttribute(
      gapi::VertexAttributeDescriptor::merge<math::vec3f_t>(gapi::VertexSemantic_t::Position, false, true));

  auto drawCall = functions->createDrawCall();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    program->use();

    vbo->bind();
    vlayout->enable();

    drawCall->execute(gapi::TopologyType::TRIANGLE_LIST, {vbo, nullptr}, core::ValueDataType::Char);

    vlayout->disable();
    vbo->unbind();

    program->unuse();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
