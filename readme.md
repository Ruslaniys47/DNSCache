DNSCache

Реализация класса с функционалом - DNS кэш


## Сборка

###Ubuntu 24.04

1. Установка зависимостей:
    ```bash
    sudo apt update
    sudo apt install git
    sudo apt install cmake
    sudo apt install g++
    ```

2. Сборка и запуск:
    ```bash
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    ./DNSCache 
    ```
# Стиль кода
  По умолчанию [Code Style Guidelines | WebKit](https://webkit.org/code-style-guidelines/)
  Форматирование .clang-format webkit

# Сложность методов update и resolve
  update(): поиск, добавление, удаление имеют сложность О(1).  
  resolve(): поиск имеет сложность О(1).
