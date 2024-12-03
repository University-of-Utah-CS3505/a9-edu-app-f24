#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QImage>
#include <QPainter>


class Character
{
    QString character;
    QString spell;
    QString definition;
    QImage image;
    int blackPixelCount;
public:
    explicit Character(QString character, QString spell, QString def, QObject *parent = nullptr);
    void exportImage(std::string path);
    int getBlackPixelCount();
    QImage& getImage();
    QString& getCharacter();
    QString& getDef();
    QString& getSpell();


signals:
};

#endif // CHARACTER_H
