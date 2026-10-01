QT -= gui # Отключаем GUI-модуль, чтобы не тянуть лишние зависимости
QT += core # Оставляем только ядро Qt
CONFIG += c++17 console
CONFIG -= app_bundle
TARGET = ConsoleCalculator
TEMPLATE = app
SOURCES += \
        calculator.cpp \
        main.cpp
HEADERS += \
        calculator.h