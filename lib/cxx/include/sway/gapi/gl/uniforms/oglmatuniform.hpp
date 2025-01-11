#ifndef SWAY_GAPI_GL_OGLMATUNIFORM_HPP
#define SWAY_GAPI_GL_OGLMATUNIFORM_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

namespace sway::gapi {

template <typename TValueType>
struct OGLMatUniform : public Uniform {
  MTHD_OVERRIDE(u32_t getType() const) { return GL_FLOAT_MAT4; }

  bool execute(const TValueType &val) const {
    // glUniformMatrix4fv(location, 1, GL_FALSE, val);
    helper_.setUniformMatrix4f(location, 1, false, val);
    return true;
  }

private:
  OGLShaderProgramHelper helper_;
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_OGLMATUNIFORM_HPP
