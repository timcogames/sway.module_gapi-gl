#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/math.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading.h>

using namespace sway;

void update() {}

void loadGapiPlugin(const char *plugname) {
  auto *plug = new core::Plugin(core::generic::io::Path(plugname), RTLD_NOW);

  auto *plugFuncset = new gapi::ConcreatePluginFunctionSet();

  plug->initialize(plugFuncset);

  auto capability = plugFuncset->createCapability();

  auto capabilityPtr = capability.get();
  EM_ASM({ console.log(UTF8ToString($0)); }, ((gapi::OGLCapability *)capabilityPtr)->toStr().c_str());
}

pthread_t thread;

void *renderThreadEntry(void *) {
  EmscriptenWebGLContextAttributes attr;
  emscripten_webgl_init_context_attributes(&attr);
  attr.alpha = attr.depth = attr.stencil = attr.antialias = 0;
  attr.majorVersion = 2;
  attr.minorVersion = 0;
  auto ctx = emscripten_webgl_create_context("#canvas", &attr);
  if (ctx <= 0) {
    printf("Webgl ctx could not be created {%i}\n", ctx);
    return nullptr;
  }

  if (emscripten_webgl_make_context_current(ctx) != EMSCRIPTEN_RESULT_SUCCESS) {
    printf("emscripten_webgl_make_context_current FAILED");
    emscripten_webgl_destroy_context(ctx);
    return nullptr;
  }

  const auto *const plugname = "./module_gapi_gl_wasm_async.wasm";
  loadGapiPlugin(plugname);

  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  return nullptr;
}

void createRenderThread() {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  emscripten_pthread_attr_settransferredcanvases(&attr, "canvas");
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_create(&thread, &attr, &renderThreadEntry, nullptr);
}

auto main() -> int {
  createRenderThread();
  return 0;
}
