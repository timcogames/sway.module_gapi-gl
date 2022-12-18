#ifndef SWAY_GAPI_GL_CAPABILITY_HPP
#define SWAY_GAPI_GL_CAPABILITY_HPP

#include <sway/gapi/gl/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class Capability : public ICapabilityBase {
public:
  static auto createInstance() -> CapabilityRef_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  Capability();

  /**
   * @brief Деструктор класса.
   */
  virtual ~Capability() = default;

  /**
   * @brief Возвращает версию OpenGL.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getVersion() const -> core::Version);  // clang-format on

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
   * @brief Инициализирует версию.
   */
  void initializeVersion_();

  /**
   * @brief Инициализирует расширения.
   */
  void initializeExtensions_();

  void initLimits_();

  std::string _renderer;
  std::string _vendor;
  std::string _version;
  std::string _shadingLanguageVersion;
  s32_t _majorVersion;
  s32_t _minorVersion;

  s32_t _maxVertexAttributes;
  s32_t _maxVertexOutputComponents;
  s32_t _maxVertexTextureImageUnits;
  s32_t _maxVertexUniformComponents;
  s32_t _maxVertexUniformVectors;

  s32_t _maxDrawBuffers;

  s32_t _maxFragmentInputComponents;
  s32_t _maxFragmentUniformComponents;
  s32_t _maxFragmentUniformVectors;

  s32_t _maxTextureImageUnits;
  s32_t _maxCombineTextureImageUnits;
  s32_t _maxTextureMaxAnisotropyExt;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_CAPABILITY_HPP
