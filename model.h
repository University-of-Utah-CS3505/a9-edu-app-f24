#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "character.h"
#include "QMouseEvent"
#include "QTimer"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <sstream>

/**
 * @class Model
 * @brief Handles the application's data and logic.
 *
 * The Model class manages character data, canvas drawing, API interactions, and signal-slot communications between the UI and backend.
 *
 * Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
 * Course: CS3500 - A9 Educational App
 */
class Model : public QObject
{
    Q_OBJECT

    bool isPainting; ///< Indicates whether the brush painting mode is active.
    bool isMousePressed; ///< Tracks the mouse press state for drawing.
    int characterIndex; ///< Current index of the character in use.
    std::string jsonEX; ///< Example JSON data.
    std::string apiKey; ///< API key for external communication.
    QList<Character> characterLib; ///< Library of all available characters.
    QList<std::string> selectedCharactersForCraft; ///< List of selected characters for crafting.
    QImage canvas; ///< Canvas image for drawing.

    /**
     * @brief Creates an overlay image with user drawings and a character image.
     * @return The generated overlay image.
     */
    QImage creatOverlayImage();

    /**
     * @brief Checks the correctness of the current drawing.
     * @return A float value indicating the correctness score.
     */
    float checkCorrectness();

    /**
     * @brief Initializes the character library.
     */
    void initiallizeCharacterLib();

public:
    /**
     * @brief Constructs the Model object.
     * @param parent Optional QObject parent (default is nullptr).
     */
    explicit Model(QObject *parent = nullptr);

public slots:
    /**
     * @brief Receives the brush painting state from the UI.
     * @param isPainting True if brush painting is active, false otherwise.
     */
    void receiveIsBrushPainting(bool isPainting);

    /**
     * @brief Clears the canvas when requested.
     */
    void receiveCleanCanvas();

    /**
     * @brief Processes mouse events for drawing on the canvas.
     * @param pos The position of the mouse event.
     * @param isMousePressed True if the mouse is pressed, false otherwise.
     */
    void receiveMouseEvent(QPoint pos, bool isMousePressed);

    /**
     * @brief Handles requests to retrieve a character by index.
     * @param index The index of the requested character.
     */
    void receiveGetCharacterRequest(int index);

    /**
     * @brief Handles requests to craft a new character.
     */
    void receiveCraftCharacterRequest();

    /**
     * @brief Receives and stores the API key.
     * @param apiKey The API key as a string.
     */
    void receiveAPIKey(std::string apiKey);

    /**
     * @brief Receives the index of a selected character for educational app class.
     * @param index The index of the selected character.
     */
    void receiveSelectedCharactersIndex(int index);

    /**
     * @brief Receives the index of a selected character for crafting purposes.
     * @param index The index of the selected character.
     */
    void receiveSelectedCharacterIndexForCraft(int index);

signals:
    /**
     * @brief Sends the updated canvas image with user drawings.
     * @param image The overlay image.
     */
    void sendOverlayImage(QImage image);

    /**
     * @brief Sends a new character to the UI to create a button.
     * @param character The character object.
     * @param index The index of the character.
     */
    void sendNewCharacter(Character& character, int index);

    /**
     * @brief Sends a requested character back to the UI.
     * @param character The requested character.
     */
    void sendRequestedCharacter(Character& character);

    /**
     * @brief Sends the result of crafting a new character.
     * @param isThereNewCharacter True if a new character is found, false otherwise.
     */
    void sendCraftResult(bool isThereNewCharacter);

    /**
     * @brief Sends the correctness score to the UI.
     * @param correctness The correctness value.
     */
    void sendCorrectness(int correctness);

    /**
     * @brief Sends a selected character to the crafting UI.
     * @param character The selected character.
     */
    void sendCraftSelectedCharacter(Character& character);
};

#endif // MODEL_H
