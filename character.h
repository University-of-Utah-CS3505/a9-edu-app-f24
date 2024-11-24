#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QImage>
#include <QPainter>

class Character : public QObject
{
    Q_OBJECT
    QString character;
    std::string spell;
    std::string definition;
    QImage image;
public:
    explicit Character(QString character, std::string def, QObject *parent = nullptr);
    void exportImage(std::string path);

signals:
};

#endif // CHARACTER_H
