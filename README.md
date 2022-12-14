# sway.module_gapi-gl

[![codecov][codecov-svg]][codecov-url] [![Documentation][codedocs-svg]][codedocs-url] [![License][license-svg]][license-url]

## Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_gapi-gl.git
```

## Сборка проекта

Создаем директорию build и переходим в неё

```console
mkdir build && cd ./build
```

Конфигурируем проект для сборки

```console
# Только динимическая библиотека
cmake -DCMAKE_BUILD_TYPE=Release -DMODULE_GAPI_GL_SHARED_LIB=ON ../
```

Опция сборки | Тип | Описание | По умолчанию
:---|:---|:---|:---:
`BOOST_ROOT` | `PATH` | Путь до корневой директории Boost библиотеки | `-`
`MODULE_GAPI_BUILD_SHARED` | `BOOL` | Сборка библиотеки общего пользования | `OFF`
`ENABLE_COVERAGE` | `BOOL` | Включает поддержку сбора данных о покрытии кода тестами | `OFF`
`ENABLE_TESTS` | `BOOL` | Включает построение тестов | `OFF`
`ENABLE_EXAMPLES` | `BOOL` | Включает построение примеров | `OFF`

Запускаем сборку

```console
cmake --build ./
```

Таблица символов

```console
readelf -Ws ./../bin/module_gapi_gl.so.*

# macos
nm -g ./../bin/module_gapi_gl.dylib.*
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
