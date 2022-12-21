#ifndef SWAY_GAPI_GL_OGLDRAWCALL_HPP
#define SWAY_GAPI_GL_OGLDRAWCALL_HPP

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

class OGLDrawCall : public DrawCall {
public:
#pragma region "Преобразование внутренних типов к GLenum"

  /**
   * @brief Переводит тип топологии (режим отображение примитива) в GL.
   */
  static GLenum topologyToGLenum(TopologyType topology);

#pragma endregion

  static auto createInstance() -> DrawCallRef_t;

  OGLDrawCall() = default;

  virtual ~OGLDrawCall() = default;

  /**
   * @brief Выполняет отрисовку примитива.
   *
   * @param[in] topology Топология примитива.
   * @param[in] bufset Набор буферных объектов.
   * @param[in] type Тип значений в индексах.
   */
  MTHD_OVERRIDE(void execute(TopologyType topology, BufferSet bufset, core::ValueDataType type));

private:
  /**
   * @brief Выводит примитивы по данным в массивах.
   *
   * @sa _drawIndexed(std::shared_ptr<Buffer>)
   */
  void draw_(BufferRef_t ibo);

  /**
   * @brief Выводит индексные примитивы по данным в массивах.
   *
   * @sa _draw(BufferRef_t)
   */
  void drawIndexed_(std::shared_ptr<Buffer> ibo);

  DrawCbFunc_t _drawCbFunc;

  union {
    DrawElements _drawElements;
    DrawArrays _drawArrays;
  };
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLDRAWCALL_HPP
