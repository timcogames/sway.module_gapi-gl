#ifndef SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

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

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP
