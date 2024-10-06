#ifndef SWAY_GAPI_GL_OGLINTUNIFORM_HPP
#define SWAY_GAPI_GL_OGLINTUNIFORM_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

template <typename TValueType>
struct OGLIntUniform : public Uniform {
  MTHD_OVERRIDE(u32_t getType() const) { return GL_INT; }

  bool execute(const TValueType &val) const {
    helper_.setUniform1i(location, val);
    return true;
  }

private:
  OGLShaderProgramHelper helper_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLINTUNIFORM_HPP
