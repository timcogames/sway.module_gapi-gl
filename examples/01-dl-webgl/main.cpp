#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/math.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

using namespace sway;

void update() {}

void loadGapiPlugin(const char *plugname) {
  auto *plug = new core::Plugin(core::generic::io::Path(plugname), RTLD_NOW);
  EM_ASM({ console.log("ERR: " + UTF8ToString($0)); }, dlerror());

  auto *plugFuncset = new gapi::ConcreatePluginFunctionSet();

  plug->initialize(plugFuncset);
  EM_ASM({ console.log("ERR" + UTF8ToString($0)); }, dlerror());

  auto capability = plugFuncset->createCapability();

  auto capabilityPtr = capability.get();
  EM_ASM({ console.log('capability: ' + $0); }, ((gapi::OGLCapability *)capabilityPtr)->toStr().c_str());
}

auto main() -> int {
  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.explicitSwapControl = 0;
  attrs.depth = 1;
  attrs.stencil = 1;
  attrs.antialias = 1;
  attrs.majorVersion = 2;
  attrs.minorVersion = 0;
  auto ctx = emscripten_webgl_create_context("#canvas", &attrs);
  if (ctx <= 0) {
    printf("Webgl ctx could not be created {%i}\n", ctx);
    return -1;
  }

  if (emscripten_webgl_make_context_current(ctx) != EMSCRIPTEN_RESULT_SUCCESS) {
    printf("emscripten_webgl_make_context_current FAILED");
    emscripten_webgl_destroy_context(ctx);
    return -1;
  }

  const char *version = (const char *)glGetString(GL_VERSION);
  EM_ASM({ console.log("gl version: " + UTF8ToString($0)); }, version);

  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  const auto *const plugname = "./module_gapi_gl_wasm.wasm";
  // const auto *const plugname = "./libmodule_gapi_gl.dylib";

  emscripten_async_wget(
      "http://localhost:7800/wwwroot/dist/module_gapi_gl_wasm.wasm", plugname, loadGapiPlugin, nullptr);

  return 0;
}
