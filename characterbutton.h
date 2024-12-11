#ifndef CHARACTERBUTTON_H
#define CHARACTERBUTTON_H

#include <QPushButton>
#include "character.h"

/**
 * @class CharacterButton
 * @brief A custom QPushButton that represents a character and its index.
 *
 * This button emits signals related to its character index when interacted with.
 *
 * Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
 * Course: CS3500 - A9 Educational App
 */
class CharacterButton : public QPushButton
{
    Q_OBJECT
    int characterIndex; ///< Index of the character represented by this button.

public:
    /**
     * @brief Constructs a CharacterButton object.
     * @param characterIndex The index of the character.
     * @param parent Optional QWidget parent (default is nullptr).
     */
    explicit CharacterButton(int characterIndex, QWidget *parent = nullptr);

public slots:
    /**
     * @brief Slot to handle button press events.
     */
    void pushed();

    /**
     * @brief Sets the character index for the button.
     * @param characterIndex The new index to set.
     */
    void setCharacterIndex(int characterIndex);

signals:
    /**
     * @brief Signal emitted to send the character index of this button.
     * @param characterIndex The index of the character.
     */
    void sendSelfIndex(int characterIndex);
};

#endif // CHARACTERBUTTON_H
