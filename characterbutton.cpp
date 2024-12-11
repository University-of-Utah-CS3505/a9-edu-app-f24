#include "characterbutton.h"
#include "character.h"

/**
 * @brief Constructs a CharacterButton object and connects the clicked signal to the pushed slot.
 * @param characterIndex The index of the character represented by this button.
 * @param parent Optional QWidget parent (default is nullptr).
 */
CharacterButton::CharacterButton(int characterIndex, QWidget *parent)
    : QPushButton{parent}, characterIndex(characterIndex)
{
    // Connect the button's clicked signal to the pushed slot.
    connect(this, &QPushButton::clicked, this, &CharacterButton::pushed);
}

/**
 * @brief Slot triggered when the button is clicked.\n
 * Emits the sendSelfIndex signal with the button's character index.
 */
void CharacterButton::pushed()
{
    emit sendSelfIndex(characterIndex);
}

/**
 * @brief Updates the character index for this button.
 * @param sendCharacterIndex The new index to set.
 */
void CharacterButton::setCharacterIndex(int sendCharacterIndex)
{
    characterIndex = sendCharacterIndex;
}
