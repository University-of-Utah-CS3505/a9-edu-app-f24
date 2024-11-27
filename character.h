#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QImage>
#include <QPainter>


class Character
{
    QString character;
    std::string spell;
    std::string definition;
    QImage image;
public:
    explicit Character(QString character, std::string def, QObject *parent = nullptr);
    void exportImage(std::string path);
    QImage& getImage();
    QString& getString();

signals:
};

#endif // CHARACTER_H
