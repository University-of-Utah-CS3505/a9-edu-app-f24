#ifndef CHARACTERBUTTON_H
#define CHARACTERBUTTON_H

#include <QPushButton>
#include "character.h"

class CharacterButton : public QPushButton
{
    Q_OBJECT
    int characterIndex;

public:
    explicit CharacterButton(int characterIndex, QWidget *parent = nullptr);

public slots:
    void pushed();
    void setCharacterIndex(int characterIndex);

signals:
    void sendSelfIndex(int characterIndex);
};

#endif // CHARACTERBUTTON_H
