#ifndef SWAY_GAPI_GL_OGLVERTEXARRAY_HPP
#define SWAY_GAPI_GL_OGLVERTEXARRAY_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/typeutils.hpp>
#include <sway/gapi/gl/wrap/oglvertexarrayhelper.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLVertexArray final : public VertexArray {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> VertexArrayPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma endregion

#pragma region "Ctors/Dtor"

  /**
   * \~russian @brief Конструктор класса.
   *                  Выполняет инициализацию нового экземпляра класса.
   */
  OGLVertexArray();

  DTOR_VIRTUAL(OGLVertexArray);

#pragma endregion

#pragma region "Overridden VertexArray methods"

  MTHD_OVERRIDE(void bind());

  MTHD_OVERRIDE(void unbind());

#pragma endregion

private:
  OGLVertexArrayHelper helper_;
  u32_t objname_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLVERTEXARRAY_HPP
