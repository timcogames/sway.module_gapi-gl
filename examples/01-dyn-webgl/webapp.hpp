#ifndef SWAY_WEBAPP_HPP
#define SWAY_WEBAPP_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/gapi/gl.hpp>
#include <sway/math.hpp>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading.h>

NAMESPACE_BEGIN(sway)

class WebApp {
public:
  WebApp() {}

  ~WebApp() {}

  static void mainLoopCallback();

  void createRenderThread();

private:
  pthread_t thread_;
};

NAMESPACE_END(sway)

#endif  // SWAY_WEBAPP_HPP
