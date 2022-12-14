#### Конфигурируем проект для Google тестов

```console
cmake -DCUSTOM_GTEST_ROOT_DIR=/Users/apriori85/Documents/Third-party/googletest -DMODULE_GAPI_GL_ENABLE_TESTS=ON ../
```

#### Запускаем сборку

```console
cmake --build ./
```

mkdir -p build
cd ./build
/opt/homebrew/bin/cmake -DCUSTOM_GTEST_ROOT_DIR=/Users/apriori85/Documents/Third-party/googletest -DMODULE_CORE_ENABLE_TESTS=ON ../
/opt/homebrew/bin/cmake --build .