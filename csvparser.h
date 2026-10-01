#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>

class CsvParser : public QObject
{
    Q_OBJECT

public:
    explicit CsvParser(QObject *parent = nullptr);

    // Геттеры состояния
    int totalLines() const { return m_totalLines; }
    int processedLines() const { return m_processedLines; }
    int errorLines() const { return m_errorLines; }
    double grandSum() const { return m_grandSum; }

public slots:
    // Основной слот: обработать файл целиком
    void parseFile(const QString &filePath);

signals:
    // Излучается для каждой успешно обработанной строки
    void lineProcessed(int lineNumber, double sum, double average);

    // Излучается при ошибке в конкретной строке
    void lineError(int lineNumber, const QString &message);

    // Излучается после завершения обработки файла
    void finished(int totalLines, double grandSum);

    // Излучается при общей ошибке (файл не открылся и т.п.)
    void errorOccurred(const QString &message);

private:
    int m_totalLines;
    int m_processedLines;
    int m_errorLines;
    double m_grandSum;

    // Разбор одной строки CSV: возвращает true, если строка валидна
    bool parseLine(const QString &line, double &sum, double &average);

    // Вспомогательный метод: сброс состояния перед новым файлом
    void resetState();
};

#endif // CSVPARSER_H