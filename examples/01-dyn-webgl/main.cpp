#include "webapp.hpp"

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

auto main() -> int {
  if (!emscripten_supports_offscreencanvas()) {
    printf("Browser does not support OffscreenCanvas");
    return -1;
  }

  auto *app = new WebApp();
  app->createRenderThread();
  return 0;
}
