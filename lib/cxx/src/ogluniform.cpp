#include <sway/gapi/gl/ogluniform.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>

namespace sway::gapi {

auto OGLUniform::createInstance(std::optional<u32_t> programId, const std::string &name) -> UniformStackPtr_t {
  auto *instance = new OGLUniform(programId, name);
  return instance;
}

}  // namespace sway::gapi
