#ifndef SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTHELPER_HPP
#define SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTHELPER_HPP

#include <sway/core/binding/procaddress.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/genericmembermacros.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLVertexAttribLayoutHelper {
public:
  OGLVertexAttribLayoutHelper();

  DECLARE_GENERIC_MEMBER(void, OGLVertexAttribLayoutHelper, enableArray, u32_t)
  void EMU_EnableVertexAttribArray(u32_t index);
  void STD_EnableVertexAttribArray(u32_t index);
  void ARB_EnableVertexAttribArray(u32_t index);

  DECLARE_GENERIC_MEMBER(void, OGLVertexAttribLayoutHelper, disableArray, u32_t)
  void EMU_DisableVertexAttribArray(u32_t index);
  void STD_DisableVertexAttribArray(u32_t index);
  void ARB_DisableVertexAttribArray(u32_t index);

  DECLARE_GENERIC_MEMBER(void, OGLVertexAttribLayoutHelper, setup, u32_t, i32_t, u32_t, u8_t, i32_t, const void *)
  void EMU_SetupVertexAttribPointer(
      u32_t index, i32_t size, u32_t type, u8_t normalized, i32_t stride, const void *pointer);
  void STD_SetupVertexAttribPointer(
      u32_t index, i32_t size, u32_t type, u8_t normalized, i32_t stride, const void *pointer);
  void ARB_SetupVertexAttribPointer(
      u32_t index, i32_t size, u32_t type, u8_t normalized, i32_t stride, const void *pointer);
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_OGLVERTEXATTRIBLAYOUTHELPER_HPP
