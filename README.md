# sway.module_gapi-gl

[![codecov][codecov-svg]][codecov-url] [![Documentation][codedocs-svg]][codedocs-url] [![License][license-svg]][license-url]

## Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_gapi-gl.git
```

```console
git submodule foreach --recursive git checkout develop
git submodule foreach --recursive git pull origin develop
```

## Сборка проекта

Создаем директорию build и переходим в неё

```console
mkdir build && cd ./build
```

Конфигурируем проект для сборки

```console
# Только динимическая библиотека
cmake -D CMAKE_BUILD_TYPE=Release \
      -D MODULE_GAPI_GL_SHARED_LIB=ON \
      ../

cmake -D CMAKE_BUILD_TYPE=Release \
      -D GLOB_EMSCRIPTEN_ROOT_DIR=/Users/<USER_NAME>/Documents/Third-party/emsdk/upstream/emscripten \
      -D GLOB_EMSCRIPTEN_PLATFORM=ON \
      -D GLOB_GTEST_ROOT_DIR= \
      -D GLOB_GMOCK_ROOT_DIR= \
      -D GLOB_GTEST_LIB_DIR= \
      -D GLOB_GMOCK_LIB_DIR= \
      -D MODULE_CORE_ENVIRONMENT=web,node \
      -D MODULE_CORE_COMPILATION=async \
      -D MODULE_GAPI_GL_ENVIRONMENT=node \
      -D MODULE_GAPI_GL_COMPILATION=async \
      -D MODULE_GAPI_GL_SHARED_LIB=ON \
      -D MODULE_GAPI_GL_MT=ON \
      -D MODULE_GAPI_GL_ENABLE_TESTS=OFF \
      -D MODULE_GAPI_GL_ENABLE_COVERAGE=OFF \
      -D MODULE_GAPI_GL_ENABLE_EXAMPLES=ON \
      ../
```

Опция сборки | Тип | Описание | По умолчанию
:---|:---|:---|:---:
`MODULE_GAPI_GL_SHARED_LIB` | `BOOL` | Сборка библиотеки общего пользования | `OFF`
`MODULE_GAPI_GL_MT` | `BOOL` | Многопоточность | `OFF`
`MODULE_GAPI_GL_ENABLE_COVERAGE` | `BOOL` | Включает поддержку сбора данных о покрытии кода тестами | `OFF`
`MODULE_GAPI_GL_ENABLE_TESTS` | `BOOL` | Включает построение тестов | `OFF`
`MODULE_GAPI_GL_ENABLE_EXAMPLES` | `BOOL` | Включает построение примеров | `OFF`
`MODULE_USE_AS_STUB` | `BOOL` | Сборка библиотеки в виде заглушки | `OFF`
`GLOB_EMSCRIPTEN_PLATFORM` | `BOOL` | Использует emscripten компилятор | `OFF`
`GLOB_EMSCRIPTEN_ROOT_DIR` | `PATH` | Путь до корневой директории Emscripten | `OFF`
`GLOB_BOOST_ROOT_DIR` | `PATH` | (не актуален) Путь до корневой директории Boost | `OFF`
`GLOB_GTEST_ROOT_DIR` | `PATH` | Путь до корневой директории GTest | `OFF`

Запускаем сборку

```console
cmake --build ./
```

Таблица символов

```console
readelf -Ws ./../bin/module_gapi_gl.so.*

# macos
nm -g ./../bin/libmodule_gapi_gl.dylib.*
# or
/opt/homebrew/Cellar/binutils/2.39_1/bin/gobjdump -t ./../bin/module_gapi_gl.dylib.*
nm ./../bin/module_gapi_gl.dylib.* | grep ' T '
```

Запуск osx desktop версии
<HOSTNAME> = System Preferences -> Sharing -> Local Hostname

```console
ssh -X root@<HOSTNAME>
```

## Contributing

См. [CONTRIBUTING](./github/CONTRIBUTING.md)

[codecov-svg]: https://codecov.io/gh/timcogames/sway.module_gapi-gl/branch/master/graph/badge.svg
[codecov-url]: https://codecov.io/gh/timcogames/sway.module_gapi-gl
[codedocs-svg]: https://codedocs.xyz/timcogames/sway.module_gapi-gl.svg
[codedocs-url]: https://codedocs.xyz/timcogames/sway.module_gapi-gl/
[license-svg]: https://img.shields.io/github/license/mashape/apistatus.svg
[license-url]: LICENSE

docker build --tag sway/module_gapi-api:latest \
             --build-arg ENABLED_COVERAGE=ON \
             --build-arg ENABLED_TESTS=ON \
             --build-arg ENABLED_EXAMPLES=ON \
             --build-arg TARGET_PLATFORM=linux/arm64/v8 \
             --build-arg TARGET_PLATFORM_OS=linux \
             --build-arg TARGET_PLATFORM_ARCH=arm64/v8 \
             --file gcc-linux-xarch.Dockerfile \
             --target module_gapi_gl-release \
             --progress plain \
             /.

docker build --tag sway/module_gapi-api:latest \
             --build-arg ENABLED_COVERAGE=ON \
             --build-arg ENABLED_TESTS=ON \
             --build-arg ENABLED_EXAMPLES=ON \
             --build-arg TARGET_PLATFORM=linux/arm64/v8 \
             --build-arg TARGET_PLATFORM_OS=linux \
             --build-arg TARGET_PLATFORM_ARCH=arm64/v8 \
             --file gcc-wasm.Dockerfile \
             --target module_gapi_gl-release \
             --progress plain \
             ./

docker cp 262103c54e84a9b5e51a3d429fc4bca78477b53afa28db71ad3885e8f1b2b755:/module_gapi_gl_workspace/bin/. /Users/apriori85/Documents/Projects/sway.module_gapi-gl/bin


