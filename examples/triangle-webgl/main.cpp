#include "../../../../submodules/sway.module_core/lib/src/_embinds.cpp"

#include <sway/core.hpp>
#include <sway/core/plugin.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/math.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <array>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

std::shared_ptr<gapi::ShaderProgramBase> program = nullptr;
std::shared_ptr<gapi::BufferIdQueue> idQueue = nullptr;
std::shared_ptr<gapi::Buffer> vbo = nullptr;
std::shared_ptr<gapi::VertexAttribLayout> vlayout = nullptr;
std::shared_ptr<gapi::IDrawCallBase> drawCall = nullptr;

void update() {
  auto t = emscripten_get_now();

  program->use();

  vbo->bind();
  vlayout->enable();

  drawCall->execute(gapi::TopologyType_t::TriangleList, {vbo, nullptr}, core::ValueDataType::Char);

  vlayout->disable();
  vbo->unbind();

  program->unuse();
}

int main() {
  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.majorVersion = 2;
  attrs.minorVersion = 0;
  int ctx = emscripten_webgl_create_context("#canvas", &attrs);
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
  vsoCreateInfo.type = gapi::ShaderType_t::Vertex;
  vsoCreateInfo.code = "attribute vec3 attr_position; \
    void main() { \
      gl_Position = vec4(attr_position, 1.0); \
     }";

  gapi::ShaderCreateInfo fsoCreateInfo;
  fsoCreateInfo.type = gapi::ShaderType_t::Fragment;
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
  vboCreateInfo.desc.target = gapi::BufferTarget_t::Array;
  vboCreateInfo.desc.usage = gapi::BufferUsage_t::Static;
  vboCreateInfo.desc.byteStride = sizeof(math::VertexPosition);
  vboCreateInfo.desc.capacity = 3;
  std::array<float, 9> vertices = {-0.5, -0.5, 0.0, 0.5, -0.5, 0.0, 0.0, 0.5, 0.0};
  vboCreateInfo.data = vertices.data();

  idQueue = functions->createBufferIdQueue();
  vbo = functions->createBuffer(idQueue, vboCreateInfo);
  vlayout = functions->createVertexAttribLayout(program);
  vlayout->addAttribute(gapi::VertexAttribute::merge<math::vec3f_t>(gapi::VertexSemantic_t::Position, false, true));

  drawCall = functions->createDrawCall();

  emscripten_set_main_loop(update, 0, 0);

  return 0;
}
