#ifndef SWAY_GAPI_GL_OGLVIEWPORT_HPP
#define SWAY_GAPI_GL_OGLVIEWPORT_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/viewportmodes.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLViewport : public Viewport {
public:
  static auto createInstance() -> ViewportPtr_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLViewport();

  /**
   * @brief Деструктор класса.
   */
  virtual ~OGLViewport() = default;

  /**
   * @brief Устанавливает новые значения прямоугольной области.
   *
   * @param[in] x Значение координаты по оси X.
   * @param[in] y Значение координаты по оси Y.
   * @param[in] w Значение ширины.
   * @param[in] h Значение высоты.
   */
  MTHD_OVERRIDE(void set(i32_t x, i32_t y, i32_t w, i32_t h));

  /**
   * @brief Устанавливает размер прямоугольной области.
   *
   * @param[in] w Значение ширины.
   * @param[in] h Значение высоты.
   */
  MTHD_OVERRIDE(void set(i32_t w, i32_t h));

  /**
   * @brief Получает размер прямоугольной области.
   */
  MTHD_OVERRIDE(auto get() const -> math::rect4i_t);

  /**
   * @brief Получает соотношение сторон.
   */
  MTHD_OVERRIDE(auto aspect() const -> f32_t);

  MTHD_OVERRIDE(void setClearColor(const math::col4f_t &col));

  MTHD_OVERRIDE(void clear());

  auto getMode() const -> ViewportMode { return mode_; }

private:
  ViewportMode mode_;
  math::col4f_t clearColor_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLVIEWPORT_HPP
