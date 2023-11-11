#ifndef SWAY_GAPI_GL_TYPEUTILS_HPP
#define SWAY_GAPI_GL_TYPEUTILS_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

// enum class VideoDriverType { GL, GLES, WEBGL };
// class VideoDriver {
// public:
//   VideoDriver(VideoDriverType type, s32_t major, s32_t minor, lpcstr_t extra = "\0")
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
  static auto toGL(core::ValueDataType type) -> u32_t {
    switch (type) {
      case core::ValueDataType::Char:
        return GL_BYTE;
      case core::ValueDataType::Short:
        return GL_SHORT;
      case core::ValueDataType::Int:
        return GL_INT;
      case core::ValueDataType::UChar:
        return GL_UNSIGNED_BYTE;
      case core::ValueDataType::UShort:
        return GL_UNSIGNED_SHORT;
      case core::ValueDataType::UInt:
        return GL_UNSIGNED_INT;
      case core::ValueDataType::Float:
        return GL_FLOAT;
      case core::ValueDataType::Double:
        return GL_DOUBLE;
      default:
        return 0;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_TYPEUTILS_HPP
