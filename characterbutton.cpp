#include "characterbutton.h"
#include "character.h"

CharacterButton::CharacterButton(Character character, QWidget *parent)
    : QPushButton{parent}, character(character)
{
    connect(this, &QPushButton::clicked, this, &CharacterButton::pushed);
}

void CharacterButton::pushed()
{
    emit sendSelfCharacter(character);
}

void CharacterButton::setCharacter(Character sendCharacter)
{
    character = sendCharacter;
}
