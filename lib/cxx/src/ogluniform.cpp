#include <sway/gapi/gl/ogluniform.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

auto OGLUniform::createInstance(std::optional<u32_t> programId, const std::string &name) -> UniformStackPtr_t {
  auto *instance = new OGLUniform(programId, name);
  return instance;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
