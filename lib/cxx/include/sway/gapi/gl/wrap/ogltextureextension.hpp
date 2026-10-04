#ifndef SWAY_GAPI_GL_WRAP_OGLTEXTUREEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLTEXTUREEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

namespace sway::gapi {

class OGLTextureExtension {
public:
  static core::TFunctionPointer<void(i32_t, u32_t *)> glGenTexturesEXT;
  static core::TFunctionPointer<void(i32_t, u32_t *)> glDeleteTexturesEXT;
  static core::TFunctionPointer<void(u32_t, u32_t)> glBindTextureEXT;
  static core::TFunctionPointer<void(u32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, i32_t, const void *)>
      glTextureImage2DEXT;
  static core::TFunctionPointer<void(u32_t, i32_t, i32_t, i32_t, i32_t, i32_t, u32_t, u32_t, const void *)>
      glTexSubImage2DEXT;
  static core::TFunctionPointer<void(u32_t)> glActiveTextureARB;
  static core::TFunctionPointer<void(u32_t, u32_t, const i32_t *)> glTexParameterIivEXT;

  static void define(const std::function<core::ProcAddress_t(ExtensionInitList_t)> &);
};

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_OGLTEXTUREEXTENSION_HPP
