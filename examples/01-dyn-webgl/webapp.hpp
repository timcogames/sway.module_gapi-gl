#ifndef SWAY_WEBAPP_HPP
#define SWAY_WEBAPP_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/math.hpp>
#include <sway/pltf.hpp>
#include <sway/pltf/timer.hpp>
#include <sway/pltf/web/emscontext.hpp>
#include <sway/pltf/web/emslooper.hpp>
#include <sway/pltf/web/emswindow.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading.h>
#include <memory>

NS_BEGIN_SWAY()

class WebApp {
public:
  WebApp(const std::string &canvasId)
      : canvasId_(canvasId) {}

  ~WebApp() {}

  void runWorker();

  static void mainLoopCallback_(void *target);

  void createWorker();

  void dispose();

  void dispose_() { delete this; }

  static void disposeInstance(WebApp *app) { app->dispose_(); }

private:
  std::shared_ptr<pltf::EMSLooper> looper_;
  std::string canvasId_;
  pthread_t worker_;
};

void WebAppDestroy(WebApp *app);

NS_END()  // namespace sway

#endif  // SWAY_WEBAPP_HPP
