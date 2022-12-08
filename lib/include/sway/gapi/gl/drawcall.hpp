#ifndef SWAY_GAPI_GL_DRAWCALL_HPP
#define SWAY_GAPI_GL_DRAWCALL_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct DrawElements {
  u32_t mode;
  s32_t count;
  u32_t type;
};

struct DrawArrays {
  u32_t mode;
  s32_t first;
  s32_t count;
};

class DrawCall : public IDrawCallBase {
public:
#pragma region "Преобразование внутренних типов к GLenum"

  /**
   * @brief Переводит тип топологии (режим отображение примитива) в GL.
   */
  static GLenum topologyToGLenum(TopologyType_t topology);

#pragma endregion

  static auto createInstance() -> DrawCallRef_t;

  DrawCall() = default;

  virtual ~DrawCall() = default;

  /**
   * @brief Выполняет отрисовку примитива.
   *
   * @param[in] topology Топология примитива.
   * @param[in] bufset Набор буферных объектов.
   * @param[in] type Тип значений в индексах.
   */
  MTHD_OVERRIDE(void execute(TopologyType_t topology, BufferSet bufset, core::ValueDataType type));

private:
  /**
   * @brief Выводит примитивы по данным в массивах.
   *
   * @sa _drawIndexed(BufferRef_t)
   */
  void _draw(BufferRef_t ibo);

  /**
   * @brief Выводит индексные примитивы по данным в массивах.
   *
   * @sa _draw(BufferRef_t)
   */
  void _drawIndexed(BufferRef_t ibo);

  DrawCbFunc_t _drawCbFunc;

  union {
    DrawElements _drawElements;
    DrawArrays _drawArrays;
  };
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_DRAWCALL_HPP
