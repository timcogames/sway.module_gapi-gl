
#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglframebufferextension.hpp>
#include <sway/gapi/gl/wrap/oglidgeneratorhelper.hpp>
#include <sway/gapi/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::OGLIdGeneratorHelper() {
#ifdef _STUB
  generate_ = &OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::EMU_generate;
  release_ = &OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::EMU_release;
#else

  const auto *extensions = OGLCapability::getExtensions();
  if (OGLCapability::isExtensionSupported(extensions, "GL_EXT_direct_state_access")) {
    generate_ = &OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::EXT_generate;
    release_ = &OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::EXT_release;
  } else {
    generate_ = &OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::STD_generate;
    release_ = &OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::STD_release;
  }

#endif
}

void OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::EMU_generate(
    ObjectUid_t latest, i32_t num, ObjectUid_t *uids) {
  for (auto i = 0; i < (i32_t)num; ++i) {
    uids[i] = i + latest + 1;
  }
}

void OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::STD_generate(
    ObjectUid_t latest, i32_t num, ObjectUid_t *uids) {
  glGenFramebuffers(num, uids);
}

void OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::EXT_generate(
    ObjectUid_t latest, i32_t num, ObjectUid_t *uids) {
  OGLFramebufferExtension::glGenFramebuffersEXT(num, uids);
}

void OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::EMU_release(i32_t num, const ObjectUid_t *uids) {
  // Empty
}

void OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::STD_release(i32_t num, const ObjectUid_t *uids) {
  glDeleteFramebuffers(num, uids);
}

void OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>::EXT_release(i32_t num, const ObjectUid_t *uids) {
  OGLFramebufferExtension::glDeleteFramebuffersEXT(num, uids);
}

NS_END()  // namespace gapi
NS_END()  // namespace sway
