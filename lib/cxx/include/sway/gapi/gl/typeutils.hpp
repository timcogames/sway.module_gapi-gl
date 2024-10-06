#ifndef SWAY_GAPI_GL_TYPEUTILS_HPP
#define SWAY_GAPI_GL_TYPEUTILS_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

// enum class VideoDriverType { GL, GLES, WEBGL };
// class VideoDriver {
// public:
//   VideoDriver(VideoDriverType type, i32_t major, i32_t minor, lpcstr_t extra = "\0")
//       : type_(type)
//       , ver_(core::Version(major, minor, DONT_CARE, extra)) {}

//   ~VideoDriver() = default;

// private:
//   VideoDriverType type_;
//   core::Version ver_;
// };

// std::vector<VideoDriver> drivers = {
//   VideoDriver(VideoDriverType::GL, 1, 5, "higher"),
//   VideoDriver(VideoDriverType::GLES, 2, 0), VideoDriver(VideoDriverType::GLES, 3, 0, "higher"),
//   VideoDriver(VideoDriverType::WEBGL, 1, 0), VideoDriver(VideoDriverType::WEBGL, 2, 0)
// };

// OpenGL 1.5+
//  glGetBufferSubData(): YES
//  glMapBufferRange(): YES
// OpenGL ES 2.0
//  glGetBufferSubData(): NO
//  glMapBufferRange(): NO
// OpenGL ES 3.0+
//  glGetBufferSubData(): NO
//  glMapBufferRange(): YES
// WebGL 1.0
//  glGetBufferSubData(): NO
//  glMapBufferRange(): NO
// WebGL 2.0
//  glGetBufferSubData(): YES
//  glMapBufferRange(): NO

class TypeUtils {
public:
  static auto getIntParams(u32_t name) -> i32_t * {
    i32_t *params = nullptr;
    glGetIntegerv(name, params);
    return params;
  }

  static auto getU32Params(u32_t name) -> u32_t {
    u32_t param = 0;
    glGetIntegerv(name, (GLint *)&param);
    return param;
  }

  static auto toGL(core::ValueDataType::Enum type) -> u32_t {
    switch (type) {
      case core::ValueDataType::Enum::BYTE:
        return GL_BYTE;
      case core::ValueDataType::Enum::SHORT:
        return GL_SHORT;
      case core::ValueDataType::Enum::INT:
        return GL_INT;
      case core::ValueDataType::Enum::UBYTE:
        return GL_UNSIGNED_BYTE;
      case core::ValueDataType::Enum::USHORT:
        return GL_UNSIGNED_SHORT;
      case core::ValueDataType::Enum::UINT:
        return GL_UNSIGNED_INT;
      case core::ValueDataType::Enum::FLOAT:
        return GL_FLOAT;
      case core::ValueDataType::Enum::DOUBLE:
        return GL_DOUBLE;
      default:
        return 0;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_TYPEUTILS_HPP
