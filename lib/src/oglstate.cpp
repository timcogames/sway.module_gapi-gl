#include <sway/gapi/gl/oglstate.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLState::createInstance() -> StateRef_t {
  auto instance = std::make_shared<OGLState>();
  return instance;
}

OGLState::OGLState() {}

void OGLState::apply() {
  blend_.capture();
  blend_.apply(helper_ /*, dirty_*/);

  depth_.capture();
  depth_.apply(helper_ /*, dirty_*/);

  cull_.capture();
  cull_.apply(helper_ /*, dirty_*/);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
