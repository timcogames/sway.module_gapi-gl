#ifndef SWAY_GAPI_GL_OGLGENERICBUFFER_HPP
#define SWAY_GAPI_GL_OGLGENERICBUFFER_HPP

#include <sway/gapi/buffercreateinfo.hpp>
#include <sway/gapi/bufferdescriptor.hpp>
#include <sway/gapi/buffermapaccesses.hpp>
#include <sway/gapi/buffermaprangeaccesses.hpp>
#include <sway/gapi/buffersubdatadescriptor.hpp>
#include <sway/gapi/buffertargets.hpp>
#include <sway/gapi/bufferusages.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>
#include <sway/gapi/idgenerator.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

/**
 * \~russian @brief Представление аппаратного буфера.
 */
class OGLGenericBuffer final : public Buffer {
public:
#pragma region "Static methods"

  /**
   * \~russian @brief Преобразует BufferUsage в соответствующий GLenum.
   *
   * @param[in] usage Внутренний тип BufferUsage
   * @return GLenum
   */
  static auto usageToGLenum(BufferUsage::Enum usage) -> GLenum { return OGLBufferUsageConvertor::toGLenum(usage); }

#pragma endregion

  /**
   * @name creators
   * @{
   */

  static auto createInstance(IdGeneratorPtr_t idgen, const BufferCreateInfo &createInfo) -> BufferPtr_t;

  /**
   * end of creators group
   * @}
   */

#pragma region "Ctors/Dtor"

  /**
   * \~russian @brief Конструктор класса.
   *                  Выполняет инициализацию нового экземпляра класса.
   */
  OGLGenericBuffer(IdGeneratorPtr_t idgen, const BufferDescriptor &desc);

  DTOR_VIRTUAL_DEFAULT(OGLGenericBuffer);

#pragma endregion

#pragma region "Overridden Buffer methods"

  /**
   * \~russian @brief Устанавливает данные в аппаратный буфер.
   *
   * @param[in] data Первоначальный данные.
   */
  MTHD_OVERRIDE(auto allocate(const void *data) -> bool);

  /**
   * \~russian @brief Изменяет данные в уже существующем буфере.
   *
   * @param[in] desc Описание конкретной заполняемой области.
   * @sa updateSubdata(const void *)
   */
  MTHD_OVERRIDE(void updateSubdata(BufferSubdataDescriptor desc));

  /**
   * \~russian @brief Изменяет данные в уже существующем буфере.
   *
   * @param[in] src Область памяти, содержащая новые значения.
   * @sa updateSubdata(u32_t, u32_t, const void *)
   */
  MTHD_OVERRIDE(void updateSubdata(const void *src));

  MTHD_OVERRIDE(void flush(i32_t offset, i32_t len));

  MTHD_OVERRIDE(auto map(BufferMapAccess::Enum flags) -> void *);

  MTHD_OVERRIDE(auto mapRange(i32_t offset, i32_t len, core::detail::EnumClassBitset<BufferMapRangeAccess::Enum> bitset)
          -> void *);

  MTHD_OVERRIDE(void unmap());

  MTHD_OVERRIDE(void bindRange(u32_t buffer, ptrdiff_t offset, ptrdiff_t size));

  /**
   * \~russian @brief Делает буфер текущим.
   *
   * @sa unbind()
   */
  MTHD_OVERRIDE(void bind());

  /**
   * \~russian @brief Делает текущим пустой буфер.
   *
   * @sa bind()
   */
  MTHD_OVERRIDE(void unbind());

  /**
   * \~russian @brief Получает целевой тип буфера.
   */
  MTHD_OVERRIDE(auto getTarget() const -> BufferTarget::Enum) {
    return target_;
  }

  /**
   * \~russian @brief Получает режим работы с данными.
   */
  MTHD_OVERRIDE(auto getUsage() const -> BufferUsage::Enum) {
    return usage_;
  }

  /**
   * \~russian @brief Получает количество элементов в массиве.
   */
  MTHD_OVERRIDE(auto getCapacity() const -> i32_t) {
    return capacity_;
  }

  /**
   * \~russian @brief Получает размер структуры данных.
   */
  MTHD_OVERRIDE(auto getByteStride() const -> i32_t) {
    return byteStride_;
  }

#pragma endregion

private:
  OGLGenericBufferHelper helper_;
  BufferTarget::Enum target_;
  BufferUsage::Enum usage_;
  i32_t capacity_;
  i32_t byteStride_;
};

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_OGLGENERICBUFFER_HPP
