#include "../../submodules/sway.module_core/lib/cxx/src/_embinds.cpp"

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/math.hpp>
#include <sway/pltf/web/emslooper.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <array>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

std::shared_ptr<pltf::EMSLooper> looper = nullptr;

gapi::BufferSet bufset;
gapi::ShaderProgram *program = nullptr;
gapi::IdGenerator::Ptr_t bufIdgen = nullptr;
gapi::VertexAttribLayout *vlayout = nullptr;
gapi::DrawCall *drawCall = nullptr;

void mainLoopCallback(void *target) {
  program->use();

  bufset.vbo->bind();
  vlayout->enable();

  drawCall->execute(gapi::TopologyType::Enum::TRIANGLE_LIST, bufset, core::ValueDataType::Enum::BYTE);

  vlayout->disable();
  bufset.vbo->unbind();

  program->unuse();
}

auto main() -> int {
  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.majorVersion = 2;
  attrs.minorVersion = 0;
  auto ctx = emscripten_webgl_create_context("#canvas", &attrs);
  if (!ctx) {
    printf("Webgl ctx could not be created!\n");
    return -1;
  }

  emscripten_webgl_make_context_current(ctx);

  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  auto *functions = new gapi::ConcreatePluginFunctionSet();
  gapi::pluginInitialize(functions);
  auto capability = functions->createCapability();

  // EM_ASM({ console.log('version: ' + $0); }, capability->getVersion().getMajor());

  gapi::ShaderCreateInfo vsoCreateInfo;
  vsoCreateInfo.type = gapi::ShaderType::Enum::VERT;
  vsoCreateInfo.code = "attribute vec3 attrib_pos;"
                       "void main() {"
                       "  gl_Position = vec4(attrib_pos, 1.0);"
                       "}";

  gapi::ShaderCreateInfo fsoCreateInfo;
  fsoCreateInfo.type = gapi::ShaderType::Enum::FRAG;
  fsoCreateInfo.code = "void main() {"
                       "  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);"
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
  vboCreateInfo.desc.byteStride = sizeof(math::VertexPosition);
  vboCreateInfo.desc.capacity = 3;
  std::array<f32_t, 9> vertices = {-0.5F, -0.5F, 0.0F, 0.5F, -0.5F, 0.0F, 0.0F, 0.5F, 0.0F};
  vboCreateInfo.data = vertices.data();

  bufIdgen = functions->createBufferIdGenerator();

  bufset.vbo = functions->createBuffer(bufIdgen, vboCreateInfo);
  vlayout = functions->createVertexAttribLayout(program);
  vlayout->addAttribute(gapi::VertexAttribDescriptor::merge<math::vec3f_t>(gapi::VertexSemantic::POS, false, true));

  drawCall = functions->createDrawCall();

  looper = std::make_shared<pltf::EMSLooper>();
  looper->loop(mainLoopCallback, nullptr, false);

  return 0;
}
