#include "characterbutton.h"
#include "character.h"

CharacterButton::CharacterButton(int characterIndex, QWidget *parent)
    : QPushButton{parent}, characterIndex(characterIndex)
{
    connect(this, &QPushButton::clicked, this, &CharacterButton::pushed);
}

void CharacterButton::pushed()
{
    emit sendSelfIndex(characterIndex);
}

void CharacterButton::setCharacterIndex(int sendCharacterIndex)
{
    characterIndex = sendCharacterIndex;
}
