#ifndef SWAY_GAPI_GL_WRAP_IDGENERATORHELPER_HPP
#define SWAY_GAPI_GL_WRAP_IDGENERATORHELPER_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>
#include <sway/gapi/idgeneratortypes.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

struct OGLIdGeneratorHelperBase {
  PURE_VIRTUAL(void generate(ObjectUid_t latest, i32_t num, ObjectUid_t *uids));

  PURE_VIRTUAL(void release(i32_t num, const ObjectUid_t *uids));
};

template <IdGeneratorType::Enum TYPE>
struct OGLIdGeneratorHelper : public OGLIdGeneratorHelperBase {
  MTHD_OVERRIDE(void generate(ObjectUid_t latest, i32_t num, ObjectUid_t *uids)) {
    // Empty
  }

  MTHD_OVERRIDE(void release(i32_t num, const ObjectUid_t *uids)) {
    // Empty
  }
};

template <>
struct OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER> : public OGLIdGeneratorHelperBase {
  inline OGLIdGeneratorHelper();

  DECLARE_GENERIC_CALLBACK_FUNC(
      void, OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>, generate, ObjectUid_t, i32_t, ObjectUid_t *)

public:
  MTHD_OVERRIDE(void generate(ObjectUid_t latest, i32_t num, ObjectUid_t *uids)) { (this->*generate_)(latest, num, uids); }

  inline void EMU_generate(ObjectUid_t latest, i32_t num, ObjectUid_t *uids);
  inline void STD_generate(ObjectUid_t latest, i32_t num, ObjectUid_t *uids);
  inline void EXT_generate(ObjectUid_t latest, i32_t num, ObjectUid_t *uids);

  DECLARE_GENERIC_CALLBACK_FUNC(
      void, OGLIdGeneratorHelper<IdGeneratorType::Enum::FRAME_BUFFER>, release, i32_t, const ObjectUid_t *)
public:
  MTHD_OVERRIDE(void release(i32_t num, const ObjectUid_t *uids)) { (this->*release_)(num, uids); }

  inline void EMU_release(i32_t num, const ObjectUid_t *uids);
  inline void STD_release(i32_t num, const ObjectUid_t *uids);
  inline void EXT_release(i32_t num, const ObjectUid_t *uids);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#include <sway/gapi/gl/wrap/oglidgeneratorhelper.inl>

#endif  // SWAY_GAPI_GL_WRAP_IDGENERATORHELPER_HPP
