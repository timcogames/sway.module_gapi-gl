#include "webapp.hpp"

NAMESPACE_BEGIN(sway)

void loadGapiPlugin(lpcstr_t plugname) {
  auto *plug = new core::Plugin(core::generic::io::Path(plugname), RTLD_NOW);
  auto *plugFuncset = new gapi::ConcreatePluginFunctionSet();

  plug->initialize(plugFuncset);

  auto capability = plugFuncset->createCapability();
  auto capabilityPtr = capability.get();
  EM_ASM({ console.log(UTF8ToString($0)); }, ((gapi::OGLCapability *)capabilityPtr)->toStr().c_str());
}

auto renderThreadEntry(void *arg) -> void * {
  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.alpha = attrs.depth = attrs.stencil = attrs.antialias = 0;
  attrs.explicitSwapControl = 1;
  attrs.majorVersion = 2;
  attrs.minorVersion = 0;
  auto ctx = emscripten_webgl_create_context("#canvas", &attrs);
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

  // emscripten_pause_main_loop();
  emscripten_set_main_loop(&WebApp::mainLoopCallback, 60, 1);
  // emscripten_resume_main_loop();

  return arg;
}

void WebApp::mainLoopCallback() {
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}

void WebApp::createRenderThread() {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  emscripten_pthread_attr_settransferredcanvases(&attr, "canvas");
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_create(&thread_, &attr, &renderThreadEntry, nullptr);
}

NAMESPACE_END(sway)
