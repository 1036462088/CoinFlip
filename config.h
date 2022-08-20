#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QMap>
#include <QVector>
class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);

    QMap<int,QVector<QVector<int>>> mData;

signals:

};

#endif // CONFIG_H
