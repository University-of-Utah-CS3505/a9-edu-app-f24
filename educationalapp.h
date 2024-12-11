#ifndef EDUCATIONALAPP_H
#define EDUCATIONALAPP_H

#include <QVBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include "model.h"
#include "craftcharacter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EducationalApp;
}
QT_END_NAMESPACE

/**
 * @class EducationalApp
 * @brief Main application window for managing the educational app's functionality.
 *
 * This class provides the main UI and logic for interacting with characters, crafting new ones, and handling drawing tools.
 *
 * Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
 * Course: CS3500 - A9 Educational App
 */
class EducationalApp : public QMainWindow
{
    Q_OBJECT

    QPushButton *lastButtonSelected; ///< Pointer to the last selected button.
    QWidget *characterOverviewContainer; ///< Container for character overview.
    QVBoxLayout * characterLayout; ///< Layout for organizing character buttons.
    craftCharacter craftCharacter; ///< CraftCharacter window for creating new characters.

public:
    /**
     * @brief Constructs the EducationalApp object.
     * @param m Reference to the Model object.
     * @param parent Optional QWidget parent (default is nullptr).
     */
    EducationalApp(Model &m, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the EducationalApp class.
     */
    ~EducationalApp();

public slots:
    /**
     * @brief Selects the drawing brush tool.
     */
    void selectDrawBrush();

    /**
     * @brief Selects the erasing brush tool.
     */
    void selectEraseBrush();

    /**
     * @brief Sends a signal to clear the canvas.
     */
    void sendCleanCanvas();

    /**
     * @brief Receives an image and updates the relevant UI components.
     * @param image The image to display.
     */
    void receiveImage(QImage image);

    /**
     * @brief Updates the connotation header in the UI.
     */
    void updateConnotationHeader();

    /**
     * @brief Receives a new character and adds it as a button in the UI.
     * @param character The character to add.
     * @param CharacterIndex The index of the character.
     */
    void receiveNewCharacter(Character& character, int CharacterIndex);

    /**
     * @brief Receives the index of a character button.
     * @param index The index of the selected character button.
     */
    void receiveCharacterButtonIndex(int index);

    /**
     * @brief Processes a character received from the model.
     * @param character The character to process.
     */
    void receiveCharacter(Character& character);

    /**
     * @brief Displays the craftCharacter window for creating new characters.
     */
    void popupCraftTable();

    /**
     * @brief Receives correctness data and updates the UI accordingly.
     * @param correctness The correctness value to process.
     */
    void receiveCorrectness(int correctness);

signals:
    /**
     * @brief Sends a signal indicating whether the brush tool is active.
     * @param isPainting True if painting is active, false otherwise.
     */
    void sendIsBrushPainting(bool isPainting);

    /**
     * @brief Sends a signal to clear the canvas.
     */
    void sendClearCanvasSignal();

    /**
     * @brief Sends a request to get a character by its index.
     * @param requestCharacterIndex The index of the character to request.
     */
    void sendGetCharacterRequest(int requestCharacterIndex);

    /**
     * @brief Sends a signal to select a new character by its index.
     * @param index The index of the new character to select.
     */
    void sendSelectNewCharactersIndex(int index);

private:
    Ui::EducationalApp *ui; ///< Pointer to the UI object.
};

#endif // EDUCATIONALAPP_H
