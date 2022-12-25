#ifndef SWAY_GAPI_GL_WRAP_OGLTEXTUREEXTENSION_HPP
#define SWAY_GAPI_GL_WRAP_OGLTEXTUREEXTENSION_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLTextureExtension {
public:
  static core::binding::TFunction<void(s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, s32_t, const void *)>
      glTextureImage2DEXT;
  static core::binding::TFunction<void(u32_t)> glActiveTextureARB;

  static void define(const std::function<core::binding::ProcAddress_t(ExtensionInitList_t)> &);
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLTEXTUREEXTENSION_HPP
