ARG TARGET_PLATFORM=

#---------------------------------------------------------------------------------
# Build stage
#---------------------------------------------------------------------------------

FROM --platform=$TARGET_PLATFORM gcc:latest AS base
# FROM --platform=$TARGET_PLATFORM arm64v8/gcc:latest AS base

#---------------------------------------------------------------------------------
# Info
#---------------------------------------------------------------------------------

LABEL Victor Timoshin <victor-timoshin@hotmail.com>

#---------------------------------------------------------------------------------
# Args
#---------------------------------------------------------------------------------

# ARG TARGET_PLATFORM_OS==<not used>
ARG TARGET_PLATFORM_ARCH=

ARG GTEST_ROOT_DIR=/usr/src/gtest
ARG GTEST_LIB_DIR=/tmp/lib
ARG ENABLED_TESTS=
ARG ENABLED_COVERAGE=
ARG ENABLED_EXAMPLES=

#---------------------------------------------------------------------------------
# Install
#---------------------------------------------------------------------------------

RUN echo "*** Install build tools ***" \
      && apt-get update -y && apt-get install -y \
         cmake \
         lcov \
         libgtest-dev \
         libgmock-dev \
      && \
    echo "*** Install deps ***" \
      && apt-get update -y && apt-get install -y \
         libglu1-mesa-dev \
         libgles2-mesa-dev \
      && \
    echo

RUN `([ $TARGET_PLATFORM_ARCH = arm64/v8 ] && ln -s /usr/lib/aarch64-linux-gnu /tmp/lib ) || \
     ([ $TARGET_PLATFORM_ARCH = arm64 ] && ln -s /usr/lib/aarch64-linux-gnu /tmp/lib ) || \
     ([ $TARGET_PLATFORM_ARCH = amd64 ] && ln -s /usr/lib/x86_64-linux-gnu /tmp/lib )`

#---------------------------------------------------------------------------------
# Copy project files to the workspace
#---------------------------------------------------------------------------------

COPY /lib /module_gapi_gl_workspace/lib
COPY /submodules /module_gapi_gl_workspace/submodules
COPY /cmake_modules /module_gapi_gl_workspace/cmake_modules
COPY /examples /module_gapi_gl_workspace/examples
COPY /CMakeLists.txt /module_gapi_gl_workspace
COPY /index.html /module_gapi_gl_workspace

RUN mkdir /module_gapi_gl_workspace/lcov_report

#---------------------------------------------------------------------------------
# Build development image
#---------------------------------------------------------------------------------

FROM base as module_gapi_gl-debug

WORKDIR /module_gapi_gl_workspace/build

RUN cmake -D CMAKE_BUILD_TYPE=Debug \
          -D GLOB_GTEST_ROOT_DIR=$GTEST_ROOT_DIR \
          -D GLOB_GTEST_LIB_DIR=$GTEST_LIB_DIR \
          -D MODULE_GAPI_GL_ENABLE_TESTS=$ENABLED_TESTS \
          -D MODULE_GAPI_GL_ENABLE_COVERAGE=$ENABLED_COVERAGE \
          -D MODULE_GAPI_GL_ENABLE_EXAMPLES=$ENABLED_EXAMPLES ../

RUN cmake --build ./

WORKDIR /module_gapi_gl_workspace

ENTRYPOINT ["tail"]
CMD ["-f", "/dev/null"]

#---------------------------------------------------------------------------------
# Build production image
#---------------------------------------------------------------------------------

FROM base as module_gapi_gl-release

WORKDIR /module_gapi_gl_workspace/build

RUN cmake -D CMAKE_BUILD_TYPE=Release \
          -D GLOB_GTEST_ROOT_DIR=$GTEST_ROOT_DIR \
          -D GLOB_GTEST_LIB_DIR=$GTEST_LIB_DIR \
          -D MODULE_GAPI_GL_ENABLE_TESTS=$ENABLED_TESTS \
          -D MODULE_GAPI_GL_ENABLE_COVERAGE=$ENABLED_COVERAGE \
          -D MODULE_GAPI_GL_ENABLE_EXAMPLES=$ENABLED_EXAMPLES ../

RUN cmake --build ./

WORKDIR /module_gapi_gl_workspace

ENTRYPOINT ["tail"]
CMD ["-f", "/dev/null"]
