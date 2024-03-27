#ifndef SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP
#define SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct OGLPixelStorageModeConvertor final {
  static auto toGLenum(PixelStorageMode face) -> GLenum {
    switch (face) {
      case PixelStorageMode::UNPACK_ALIGNMENT:
        return GL_UNPACK_ALIGNMENT;
      case PixelStorageMode::UNPACK_ROW_LENGTH:
        return GL_UNPACK_ROW_LENGTH;
      default:
        return 0;
    }
  }
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLPIXELSTORAGEMODECONVERTOR_HPP
