#include <sway/gapi/gl/ogluniform.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

auto OGLUniform::createInstance(std::optional<u32_t> programId, const std::string &name) -> UniformStackPtr_t {
  auto *instance = new OGLUniform(programId, name);
  return instance;
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
