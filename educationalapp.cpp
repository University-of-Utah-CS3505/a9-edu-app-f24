#include "educationalapp.h"
#include "ui_educationalapp.h"
#include "canvaslabel.h"
#include "characterbutton.h"

/**
 * @brief Constructs the EducationalApp object and initializes the UI components.
 * @param m Reference to the Model object.
 * @param parent Optional QWidget parent.
 */
EducationalApp::EducationalApp(Model &m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EducationalApp)
{
    ui->setupUi(this);

    // Connect UI buttons to relevant slots for drawing and erasing functionality
    connect(ui->Brush_Button, &QPushButton::pressed, this, &EducationalApp::selectDrawBrush);
    connect(ui->Erase_Button, &QPushButton::pressed, this, &EducationalApp::selectEraseBrush);
    connect(ui->Clean_Button, &QPushButton::pressed, this, &EducationalApp::sendCleanCanvas);

    // Connect signals to the model for brush painting and canvas clearing
    connect(this, &EducationalApp::sendIsBrushPainting, &m, &Model::receiveIsBrushPainting);
    connect(this, &EducationalApp::sendClearCanvasSignal, &m, &Model::receiveCleanCanvas);
    connect(this, &EducationalApp::sendGetCharacterRequest, &m, &Model::receiveGetCharacterRequest);
    connect(this, &EducationalApp::sendSelectNewCharactersIndex, &m, &Model::receiveSelectedCharactersIndex);

    // Connect the canvas label to the model for mouse event handling
    connect(ui->Canvas, &CanvasLabel::sendMouseEvent, &m, &Model::receiveMouseEvent);

    // Connect model outputs to the UI for updating images and characters
    connect(&m, &Model::sendOverlayImage, this, &EducationalApp::receiveImage);
    connect(&m, &Model::sendNewCharacter, this, &EducationalApp::receiveNewCharacter);
    connect(&m, &Model::sendRequestedCharacter, this, &EducationalApp::receiveCharacter);
    connect(&m, &Model::sendCorrectness, this, &EducationalApp::receiveCorrectness);

    // Connect the craft button to show the crafting table
    connect(ui->Craft_Button, &QPushButton::pressed, this, &EducationalApp::popupCraftTable);

    // Connect crafting window signals and model interactions
    connect(&m, &Model::sendNewCharacter, &craftCharacter, &craftCharacter::receiveNewCharacter);
    connect(&m, &Model::sendCraftSelectedCharacter, &craftCharacter, &craftCharacter::receiveCharacter);
    connect(&craftCharacter, &craftCharacter::sendSelectedCharacterIndexForCraft, &m, &Model::receiveSelectedCharacterIndexForCraft);
    connect(&craftCharacter, &craftCharacter::sendCraftCharacterRequest, &m, &Model::receiveCraftCharacterRequest);

    // Initialize the last selected button and enable the brush painting mode by default
    lastButtonSelected = ui->Brush_Button;
    ui->Brush_Button->setEnabled(false);
    emit sendIsBrushPainting(true);

    // API key connection for the crafting window
    connect(&craftCharacter, &craftCharacter::sendAPIKey, &m, &Model::receiveAPIKey);

    // Setup the scroll area for character selection
    characterOverviewContainer = new QWidget;
    characterLayout = new QVBoxLayout(characterOverviewContainer);
    characterLayout->setAlignment(Qt::AlignTop);
    characterLayout->setContentsMargins(0, 0, 0, 0);
    characterLayout->setSpacing(10); // Set spacing between buttons
    characterOverviewContainer->setLayout(characterLayout);
    ui->CharacterSelector->setWidgetResizable(true);
    ui->CharacterSelector->setWidget(characterOverviewContainer);
    ui->CharacterSelector->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->CharacterSelector->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

/**
 * @brief Destructor for the EducationalApp class.
 */
EducationalApp::~EducationalApp()
{
    delete ui;
}

/**
 * @brief Selects the drawing brush tool and updates the UI state.
 */
void EducationalApp::selectDrawBrush()
{
    lastButtonSelected->setEnabled(true);
    ui->Brush_Button->setEnabled(false);
    lastButtonSelected = ui->Brush_Button;
    emit sendIsBrushPainting(true);
}

/**
 * @brief Selects the erasing brush tool and updates the UI state.
 */
void EducationalApp::selectEraseBrush()
{
    lastButtonSelected->setEnabled(true);
    ui->Erase_Button->setEnabled(false);
    lastButtonSelected = ui->Erase_Button;
    emit sendIsBrushPainting(false);
}

/**
 * @brief Sends a signal to clear the canvas.
 */
void EducationalApp::sendCleanCanvas()
{
    emit sendClearCanvasSignal();
}

/**
 * @brief Receives an image from the model and updates the canvas.
 * @param image The image to display on the canvas.
 */
void EducationalApp::receiveImage(QImage image)
{
    ui->Canvas->setPixmap(QPixmap::fromImage(image));
}

/**
 * @brief Adds a new character as a button in the UI.
 * @param character The character to add.
 * @param CharacterIndex The index of the character.
 */
void EducationalApp::receiveNewCharacter(Character& character, int CharacterIndex)
{
    qDebug() << "received";

    // Create a button for the character
    CharacterButton *button = new CharacterButton(CharacterIndex);
    button->setFixedSize(75, 75);
    button->setIconSize(QSize(70, 70));
    button->setIcon(QPixmap::fromImage(character.getImage()));

    // Connect the button to handle character selection
    connect(button, &CharacterButton::sendSelfIndex, this, &EducationalApp::receiveCharacterButtonIndex);

    characterLayout->addWidget(button);
    characterOverviewContainer->adjustSize(); // Adjust layout size
}

/**
 * @brief Updates the connotation header in the UI.
 */
void EducationalApp::updateConnotationHeader()
{
    ui->Connotation_Description->setText("<b>BK喜歡玩黃遊</b>");
}

/**
 * @brief Receives the index of a selected character button and sends requests to the model.
 * @param index The index of the selected character.
 */
void EducationalApp::receiveCharacterButtonIndex(int index)
{
    emit sendGetCharacterRequest(index);
    emit sendSelectNewCharactersIndex(index);
}

/**
 * @brief Updates the UI with character details from the model.
 * @param character The character to display.
 */
void EducationalApp::receiveCharacter(Character& character)
{
    ui->Connotation_Description->setText(character.getDef());
    ui->Pronounce_Description->setText(character.getSpell());
    ui->Canvas->setPixmap(QPixmap::fromImage(character.getImage()));
}

/**
 * @brief Displays the crafting table window.
 */
void EducationalApp::popupCraftTable()
{
    craftCharacter.show();
}

/**
 * @brief Updates the correctness indicator in the UI.
 * @param correctness The correctness value to display.
 */
void EducationalApp::receiveCorrectness(int correctness)
{
    ui->correctness->setValue(correctness);
}
