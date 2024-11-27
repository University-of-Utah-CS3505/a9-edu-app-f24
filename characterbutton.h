#ifndef CHARACTERBUTTON_H
#define CHARACTERBUTTON_H

#include <QPushButton>
#include "character.h"

class CharacterButton : public QPushButton
{
    Q_OBJECT
    Character character;

public:
    explicit CharacterButton(Character character, QWidget *parent = nullptr);

public slots:
    void pushed();
    void setCharacter(Character character);

signals:
    void sendSelfCharacter(Character character);
};

#endif // CHARACTERBUTTON_H
