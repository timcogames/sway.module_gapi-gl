#ifndef SWAY_GAPI_TESTS_GOOGLE_UNIT_MOCKOGLGENERICSHADERHELPER_HPP
#define SWAY_GAPI_TESTS_GOOGLE_UNIT_MOCKOGLGENERICSHADERHELPER_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/wrap/oglgenericshaderhelper.hpp>
#include <sway/math.hpp>

#undef None
#undef Bool

#include <gmock/gmock.h>

using namespace sway;

class MockOGLGenericShaderHelper : public gapi::OGLGenericShaderHelper {
public:
  MOCK_METHOD(u32_t, createShader, (u32_t));

  MOCK_METHOD(void, deleteShader, (std::optional<u32_t>));

  MOCK_METHOD(void, shaderSource, (std::optional<u32_t>, s32_t, lpcstr_t *, const s32_t *));

  MOCK_METHOD(void, compileShader, (std::optional<u32_t>, s32_t *));

  MOCK_METHOD(s32_t, getAttribLocation, (u32_t, lpcstr_t));
};

#endif  // SWAY_GAPI_TESTS_GOOGLE_UNIT_MOCKOGLGENERICSHADERHELPER_HPP
