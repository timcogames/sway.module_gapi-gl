#ifndef SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

struct OGLPixelStorageModeConvertor final {
  static auto toGLenum(PixelStorageMode::Enum face) -> GLenum {
    switch (face) {
      case PixelStorageMode::Enum::UNPACK_ALIGNMENT:
        return GL_UNPACK_ALIGNMENT;
      case PixelStorageMode::Enum::UNPACK_ROW_LENGTH:
        return GL_UNPACK_ROW_LENGTH;
      default:
        return 0;
    }
  }
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP
