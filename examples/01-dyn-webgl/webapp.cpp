#include "webapp.hpp"

NS_BEGIN_SWAY()

void loadGapiPlugin(lpcstr_t plugname) {
  auto *plug = new core::Plugin(core::generic::io::Path(plugname), RTLD_NOW);
  auto *plugFuncset = new gapi::ConcreatePluginFunctionSet();

  plug->initialize(plugFuncset);

  auto capability = plugFuncset->createCapability();
  auto capabilityPtr = capability.get();

  // clang-format off
  EM_ASM({
    console.log(UTF8ToString($0));
  }, ((gapi::OGLCapability *)capabilityPtr)->toStr().c_str());  // clang-format on
}

void createContext(const std::string &canvasId) {
  auto ctx = std::make_shared<pltf::EMSContext>(canvasId);
  ctx->create(nullptr);
  ctx->makeCurrent();
}

void WebApp::runWorker() {
  createContext(canvasId_);

  loadGapiPlugin("./module_gapi_gl_wasm_async.wasm");

  looper_ = std::make_shared<pltf::EMSLooper>();
  looper_->loop(&WebApp::mainLoopCallback_, this, false);
}

void WebApp::mainLoopCallback_(void *target) {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(0, 0, 0, 0);
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void WebApp::createWorker() {
  assert(emscripten_is_main_browser_thread());

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  emscripten_pthread_attr_settransferredcanvases(&attr, canvasId_.substr(1).c_str());
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  // clang-format off
  pthread_create(&worker_, &attr, [](void *ctx) -> void * {
    static_cast<WebApp *>(ctx)->runWorker();
    return nullptr;
  }, this);  // clang-format on
}

void WebApp::dispose() {
  assert(emscripten_is_main_browser_thread());

  emscripten_dispatch_to_thread(
      worker_, EM_FUNC_SIG_VI, reinterpret_cast<void *>(WebApp::disposeInstance), nullptr, this);
}

void WebAppDestroy(WebApp *app) { app->dispose(); }

NS_END()  // namespace sway
