#ifndef SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLVertexArrayHelper {
public:
  OGLVertexArrayHelper();

  DECLARE_GENERIC_MEMBER(void, OGLVertexArrayHelper, generateVertexArrays, s32_t, u32_t *)
  void EMU_GenerateVertexArrays(s32_t nbr, u32_t *arrays);
  void STD_GenerateVertexArrays(s32_t nbr, u32_t *arrays);
  void APPLE_GenerateVertexArrays(s32_t nbr, u32_t *arrays);

  DECLARE_GENERIC_MEMBER(void, OGLVertexArrayHelper, deleteVertexArrays, s32_t, const u32_t *)
  void EMU_DeleteVertexArrays(s32_t nbr, const u32_t *arrays);
  void STD_DeleteVertexArrays(s32_t nbr, const u32_t *arrays);
  void APPLE_DeleteVertexArrays(s32_t nbr, const u32_t *arrays);

  DECLARE_GENERIC_MEMBER(void, OGLVertexArrayHelper, bindVertexArray, u32_t)
  void EMU_BindVertexArray(u32_t array);
  void STD_BindVertexArray(u32_t array);
  void APPLE_BindVertexArray(u32_t array);

  DECLARE_GENERIC_MEMBER(bool, OGLVertexArrayHelper, isVertexArray, u32_t)
  auto EMU_IsVertexArray(u32_t array) -> bool;
  auto STD_IsVertexArray(u32_t array) -> bool;
  auto APPLE_IsVertexArray(u32_t array) -> bool;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAP_OGLVERTEXARRAYHELPER_HPP
