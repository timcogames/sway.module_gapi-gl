#ifndef SWAY_GAPI_GL_OGLVIEWPORT_HPP
#define SWAY_GAPI_GL_OGLVIEWPORT_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/viewportmodes.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLViewport : public Viewport {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> ViewportPtr_t;

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
  OGLViewport();

  DTOR_VIRTUAL_DEFAULT(OGLViewport);

#pragma endregion

#pragma region "Overridden Viewport methods"

  /**
   * \~russian @brief Устанавливает новые значения прямоугольной области.
   *
   * @param[in] x Значение координаты по оси X.
   * @param[in] y Значение координаты по оси Y.
   * @param[in] w Значение ширины.
   * @param[in] h Значение высоты.
   */
  MTHD_OVERRIDE(void set(i32_t x, i32_t y, i32_t w, i32_t h));

  /**
   * \~russian @brief Устанавливает размер прямоугольной области.
   *
   * @param[in] w Значение ширины.
   * @param[in] h Значение высоты.
   */
  MTHD_OVERRIDE(void set(i32_t w, i32_t h));

  /**
   * \~russian @brief Получает размер прямоугольной области.
   */
  MTHD_OVERRIDE(auto get() const -> math::rect4i_t);

  /**
   * \~russian @brief Получает соотношение сторон.
   */
  MTHD_OVERRIDE(auto aspect() const -> f32_t);

  MTHD_OVERRIDE(void setClearColor(const math::col4f_t &col));

  MTHD_OVERRIDE(void clear(ClearFlag flags));

#pragma endregion

  auto getMode() const -> ViewportMode::Enum { return mode_; }

private:
  ViewportMode::Enum mode_;
  math::col4f_t clearColor_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLVIEWPORT_HPP
