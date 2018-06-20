# sway.module_gapi-gl [![Discord](https://discordapp.com/api/guilds/402238411639095297/widget.png)](https://discord.gg/vCMcgwQ)

[![Build Status](https://travis-ci.com/timcogames/sway.module_gapi-gl.svg?branch=master)](https://travis-ci.com/timcogames/sway.module_gapi-gl)
[![codecov](https://codecov.io/gh/timcogames/sway.module_gapi-gl/branch/master/graph/badge.svg)](https://codecov.io/gh/timcogames/sway.module_gapi-gl)
[![Documentation](https://codedocs.xyz/timcogames/sway.module_gapi-gl.svg)](https://codedocs.xyz/timcogames/sway.module_gapi-gl/)

### Клонирование проекта

```console
git clone --recursive https://github.com/timcogames/sway.module_gapi-gl.git
```

### Сборка проекта

Создаем директорию build и переходим в неё

```console
mkdir build && cd ./build
```

Конфигурируем проект для сборки

```console
cmake -DCMAKE_BUILD_TYPE=Release ../
```

Опция сборки | Описание | По умолчанию
:---|:---|:---:
`BUILD_SHARED_LIBS` | Сборка библиотеки общего пользования | `OFF`
`ENABLE_COVERAGE` | Включает поддержку сбора данных о покрытии кода тестами | `OFF`
`ENABLE_TESTS` | Включает построение тестов | `OFF`

Запускаем сборку

```console
cmake --build .
```
