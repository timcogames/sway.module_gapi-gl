#ifndef SWAY_GAPI_TESTS_GOOGLE_UNIT_MOCKOGLBUFFERIDGENHELPER_HPP
#define SWAY_GAPI_TESTS_GOOGLE_UNIT_MOCKOGLBUFFERIDGENHELPER_HPP

#include <sway/core.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>
#include <sway/math.hpp>

#undef None
#undef Bool

#include <gmock/gmock.h>

using namespace sway;

class FakeOGLBufferIdgenHelper : public gapi::OGLGenericBufferHelperIface {
public:
  MTHD_OVERRIDE(void generateBuffers(u32_t latest, u32_t num, u32_t *uids)) {
    for (auto i = 0; i < (i32_t)num; ++i) {
      uids[i] = i + latest + 1;
    }
  }

  MTHD_OVERRIDE(void deleteBuffers(u32_t num, u32_t *uids)) {}
};

class MockOGLBufferIdgenHelper : public gapi::OGLGenericBufferHelperIface {
public:
  MockOGLBufferIdgenHelper() {
    ON_CALL(*this, generateBuffers).WillByDefault([this](u32_t latest, u32_t num, u32_t *uids) {
      fake_.generateBuffers(latest, num, uids);
    });

    ON_CALL(*this, deleteBuffers).WillByDefault([this](u32_t num, u32_t *uids) { fake_.deleteBuffers(num, uids); });
  }

  MOCK_METHOD(void, generateBuffers, (u32_t latest, u32_t num, u32_t *uids));

  MOCK_METHOD(void, deleteBuffers, (u32_t num, u32_t *uids));

private:
  FakeOGLBufferIdgenHelper fake_;
};

#endif  // SWAY_GAPI_TESTS_GOOGLE_UNIT_MOCKOGLBUFFERIDGENHELPER_HPP
