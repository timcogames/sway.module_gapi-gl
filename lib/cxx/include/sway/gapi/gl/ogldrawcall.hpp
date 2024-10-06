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
#pragma region "Преобразование внутренних типов к GLenum"

  /**
   * @brief Переводит тип топологии (режим отображение примитива) в GL.
   */
  static GLenum topologyToGLenum(TopologyType::Enum topology);

#pragma endregion

  static auto createInstance() -> DrawCallPtr_t;

  OGLDrawCall() = default;

  virtual ~OGLDrawCall() = default;

  /**
   * @brief Выполняет отрисовку примитива.
   *
   * @param[in] topology Топология примитива.
   * @param[in] bufset Набор буферных объектов.
   * @param[in] type Тип значений в индексах.
   */
  MTHD_OVERRIDE(void execute(TopologyType::Enum topology, BufferSet bufset, core::ValueDataType::Enum type));

private:
  /**
   * @brief Выводит примитивы по данным в массивах.
   *
   * @sa drawIndexed_(BufferPtr_t)
   */
  void draw_(BufferPtr_t ebo);

  /**
   * @brief Выводит индексные примитивы по данным в массивах.
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
