#ifndef LOGGER_H
#define LOGGER_H
#include <QString>
#include <QObject>


class LoggerInterface : public QObject
{
    Q_OBJECT
public:
    enum Levels {
        DEBUG = 10,
        INFO = 20,
        WARNING = 30,
        ERROR = 40
    };

    virtual QString toString() = 0;

signals:
    void log(const QString &message, const LoggerInterface *sender, int level=DEBUG);
};

#endif // LOGGER_H
