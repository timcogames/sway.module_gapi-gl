#ifndef SWAY_GAPI_GL_OGLCAPABILITY_HPP
#define SWAY_GAPI_GL_OGLCAPABILITY_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

class OGLCapability : public Capability {
public:
#pragma region "Static methods"

  /**
   * @name creators
   * @{
   */

  static auto createInstance() -> CapabilityPtr_t;

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
  OGLCapability();

  DTOR_VIRTUAL_DEFAULT(OGLCapability);

#pragma endregion

#pragma region "Overridden Capability methods"

  /**
   * \~russian @brief Возвращает версию OpenGL.
   */
  MTHD_OVERRIDE(auto getVersion() const -> core::Version);

#pragma endregion

  [[nodiscard]] auto toStr() const -> std::string;

  static auto getExtensions() -> lpcstr_t { return reinterpret_cast<lpcstr_t>(glGetString(GL_EXTENSIONS)); }

  static auto isExtensionSupported(lpcstr_t extensions, lpcstr_t name) -> bool {
    if (strstr(extensions, name) == nullptr) {
      std::cout << "(!) Extension " << name << " is not supported." << std::endl;
      return false;
    }

    return true;
  }

private:
  /**
   * \~russian @brief Инициализирует версию.
   */
  void initializeVersion_();

  /**
   * \~russian @brief Инициализирует расширения.
   */
  void initializeExtensions_();

  void initLimits_();

  std::string renderer_;
  std::string vendor_;
  std::string version_;
  std::string shadingLanguageVersion_;
  i32_t majorVersion_;
  i32_t minorVersion_;

  i32_t maxVertexAttributes_;
  i32_t maxVertexOutputComponents_;
  i32_t maxVertexTextureImageUnits_;
  i32_t maxVertexUniformComponents_;
  i32_t maxVertexUniformVectors_;

  i32_t maxDrawBuffers_;

  i32_t maxFragmentInputComponents_;
  i32_t maxFragmentUniformComponents_;
  i32_t maxFragmentUniformVectors_;

  i32_t maxTextureImageUnits_;
  i32_t maxCombineTextureImageUnits_;
  i32_t maxTextureMaxAnisotropyExt_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLCAPABILITY_HPP
