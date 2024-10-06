#ifndef SWAY_GAPI_GL_OGLVECUNIFORM_HPP
#define SWAY_GAPI_GL_OGLVECUNIFORM_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramhelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

template <typename TValueType, size_t size = sizeof(TValueType) / sizeof(f32_t)>
struct OGLVecUniform : public Uniform {
  MTHD_OVERRIDE(u32_t getType() const) {
    switch (size) {
      case 2:
        return GL_FLOAT_VEC2;
      case 3:
        return GL_FLOAT_VEC3;
      case 4:
        return GL_FLOAT_VEC4;
      default:
        return 0;
    }
  }

  bool execute(const TValueType &val) const {
    switch (size) {
      case 2: {
        glUniform2fv(location, 1, val);
        return true;
      } break;
      case 3: {
        glUniform3fv(location, 1, val);
        return true;
      } break;
      case 4: {
        // glUniform4fv(location, 1, val);
        helper_.setUniformArr4f(location, 1, val);
        return true;
      } break;
      default: {
        return false;
      } break;
    }
  }

private:
  OGLShaderProgramHelper helper_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLVECUNIFORM_HPP
