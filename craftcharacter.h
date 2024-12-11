#ifndef CRAFTCHARACTER_H
#define CRAFTCHARACTER_H

#include <QVBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include "model.h"
#include "box2dwidget.h"
#include "hint.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class craftCharacter;
}
QT_END_NAMESPACE

/**
 * @class craftCharacter
 * @brief Manages the crafting process for characters in the application.
 *
 * This class provides the main UI and logic to receive, display, and handle characters for crafting purposes.
 *
 * Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
 * Course: CS3500 - A9 Educational App
 */
class craftCharacter : public QMainWindow
{
    Q_OBJECT

    QList<QPushButton *> allCharacters; ///< List of all character buttons in the UI.
    QPushButton* lastButtonSelected; ///< Pointer to the last selected button.
    QWidget *characterOverviewContainer; ///< Container widget for character overview.
    QVBoxLayout * characterLayout; ///< Layout for organizing character buttons.
    Hint hint; ///< Hint object for providing user guidance.

public:
    /**
     * @brief Constructs a craftCharacter object.
     * @param parent Optional QWidget parent (default is nullptr).
     */
    explicit craftCharacter(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the craftCharacter class.
     */
    ~craftCharacter();

public slots:
    /**
     * @brief Receives a new character and adds it as a button in the UI.
     * @param character The character to add.
     * @param CharacterIndex The index of the character.
     */
    void receiveNewCharacter(Character& character, int CharacterIndex);

    /**
     * @brief Receives and processes a character.
     * @param character The character to process.
     */
    void receiveCharacter(Character& character);

    /**
     * @brief Displays a popup hint window.
     */
    void popupHitWindows();

    /**
     * @brief Handles receiving the index of a character button.
     *
     * This will be implemented in the receiveNewCharacter method.
     * @param index The index of the character button.
     */
    void receiveCharacterButtonIndex(int index);

    /**
     * @brief Handles changes to the API key.
     */
    void apiKeyChanged();

    /**
     * @brief Starts the character crafting process.
     */
    void startCraftCharacter();

signals:
    /**
     * @brief Sends the index of the selected character for crafting.
     * @param requestCharacterIndex The index of the character requested for crafting.
     */
    void sendSelectedCharacterIndexForCraft(int requestCharacterIndex);

    /**
     * @brief Sends a request to craft a character.
     */
    void sendCraftCharacterRequest();

    /**
     * @brief Sends the API key to the relevant components.
     * @param apiKey The API key as a std::string.
     */
    void sendAPIKey(std::string apiKey);

private:
    Ui::craftCharacter *ui; ///< Pointer to the UI object.
    box2DWidget* m_box2DWidget; ///< Pointer to the Box2D widget for rendering.
};

#endif // CRAFTCHARACTER_H
