#ifndef SWAY_GAPI_GL_OGLDRAWCALL_HPP
#define SWAY_GAPI_GL_OGLDRAWCALL_HPP

#include <sway/gapi/gl/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

struct DrawElements {
  u32_t mode;
  i32_t count;
  u32_t type;
};

struct DrawArrays {
  u32_t mode;
  i32_t first;
  i32_t count;
};

class OGLDrawCall : public DrawCall {
public:
#pragma region "Static methods"

  /**
   * \~russian @brief Преобразует TopologyType в соответствующий GLenum.
   *
   * @param[in] topology Внутренний тип TopologyType.
   * @return GLenum
   */
  static auto topologyToGLenum(TopologyType::Enum topology) -> GLenum;

#pragma endregion

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> DrawCallPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma region "Ctors/Dtor"

  OGLDrawCall() = default;

  DTOR_VIRTUAL_DEFAULT(OGLDrawCall);

#pragma endregion

#pragma region "Overridden DrawCall methods"

  /**
   * \~russian @brief Выполняет отрисовку примитива.
   *
   * @param[in] topology Топология примитива.
   * @param[in] bufset Набор буферных объектов.
   * @param[in] type Тип значений в индексах.
   */
  MTHD_OVERRIDE(void execute(TopologyType::Enum topology, BufferSet bufset, core::ValueDataType::Enum type));

#pragma endregion

private:
  /**
   * \~russian @brief Выводит примитивы по данным в массивах.
   *
   * @sa drawIndexed_(BufferPtr_t)
   */
  void draw_(BufferPtr_t ebo);

  /**
   * \~russian @brief Выводит индексные примитивы по данным в массивах.
   *
   * @sa draw_(BufferPtr_t)
   */
  void drawIndexed_(BufferPtr_t ebo);

  DrawCbFunc_t drawCbFunc_;

  union {
    DrawElements drawElements_;
    DrawArrays drawArrays_;
  };
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLDRAWCALL_HPP
