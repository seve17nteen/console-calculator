# ConsoleCalculator

Консольный калькулятор на Qt (QtCore) с использованием сигналов и слотов.

## Возможности

- Сложение, вычитание, умножение, деление
- Обработка деления на ноль
- Обработка неверного ввода
- Сброс состояния

## Требования

- Qt 5.x или Qt 6.x (модуль Core)
- qmake
- Компилятор C++17

## Сборка и запуск

```bash
qmake ConsoleCalculator.pro
make        # или mingw32-make / nmake
./ConsoleCalculator