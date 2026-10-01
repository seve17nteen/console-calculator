#include "csvparser.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

CsvParser::CsvParser(QObject *parent)
    : QObject(parent)
    , m_totalLines(0)
    , m_processedLines(0)
    , m_errorLines(0)
    , m_grandSum(0.0)
{
    qDebug() << "CsvParser created";
}

void CsvParser::resetState()
{
    m_totalLines = 0;
    m_processedLines = 0;
    m_errorLines = 0;
    m_grandSum = 0.0;
}

void CsvParser::parseFile(const QString &filePath)
{
    qDebug() << "CsvParser::parseFile(" << filePath << ")";
    resetState();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit errorOccurred(QString("Не удалось открыть файл: %1").arg(filePath));
        return;
    }

    QTextStream in(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    in.setCodec("UTF-8");
#endif

    int lineNumber = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        ++lineNumber;

        // Пустые строки пропускаем, но считаем их как "обработанные"
        if (line.isEmpty()) {
            continue;
        }

        ++m_totalLines;

        double sum = 0.0;
        double average = 0.0;

        if (parseLine(line, sum, average)) {
            ++m_processedLines;
            m_grandSum += sum;
            emit lineProcessed(lineNumber, sum, average);
        } else {
            ++m_errorLines;
            emit lineError(lineNumber, "Некорректные данные в строке");
        }
    }

    file.close();
    emit finished(m_totalLines, m_grandSum);
}

bool CsvParser::parseLine(const QString &line, double &sum, double &average)
{
    // Разделители: запятая или точка с запятой
    QStringList tokens = line.split(QRegularExpression("[,;]"), Qt::SkipEmptyParts);

    if (tokens.isEmpty()) {
        return false;
    }

    sum = 0.0;
    int count = 0;

    for (const QString &token : tokens) {
        bool ok = false;
        double value = token.trimmed().toDouble(&ok);
        if (!ok) {
            return false;   // хотя бы одно поле — не число
        }
        sum += value;
        ++count;
    }

    if (count == 0) {
        return false;
    }

    average = sum / count;
    return true;
}