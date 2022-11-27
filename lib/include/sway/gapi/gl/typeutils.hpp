#ifndef SWAY_GAPI_GL_TYPEUTILS_HPP
#define SWAY_GAPI_GL_TYPEUTILS_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class TypeUtils {
public:
  static u32_t toGL(core::ValueDataType type) {
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
