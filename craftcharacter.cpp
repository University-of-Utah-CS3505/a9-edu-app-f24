#include "craftcharacter.h"
#include "ui_craftcharacter.h"
#include "characterbutton.h"

/**
 * @brief Constructs the craftCharacter object and initializes the UI components.
 * @param parent Optional parent widget.
 */
craftCharacter::craftCharacter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::craftCharacter)
{
    ui->setupUi(this);

    // Setup the scroll area to contain the character buttons
    characterOverviewContainer = new QWidget;
    characterLayout = new QVBoxLayout(characterOverviewContainer);
    characterLayout->setAlignment(Qt::AlignTop);
    characterLayout->setContentsMargins(0, 0, 0, 0);
    characterLayout->setSpacing(10); // Set spacing between buttons
    characterOverviewContainer->setLayout(characterLayout);

    // Add the scroll area to the character selector widget
    ui->CharacterSelector->setWidgetResizable(true);
    ui->CharacterSelector->setWidget(characterOverviewContainer);
    ui->CharacterSelector->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->CharacterSelector->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Assign the Box2D widget
    m_box2DWidget = ui->box2DWidgetContainer;

    // Connect the API key text edit to signal for API key changes
    connect(ui->apiKey, &QTextEdit::textChanged, this, &craftCharacter::apiKeyChanged);

    // Connect the craft button to start crafting characters
    connect(ui->craftButton, &QPushButton::pressed, this, &craftCharacter::startCraftCharacter);

    // Connect the hint button to display the popup hint window
    connect(ui->hintButton, &QPushButton::pressed, this, &craftCharacter::popupHitWindows);
}

/**
 * @brief Destructor for the craftCharacter class, cleaning up UI resources.
 */
craftCharacter::~craftCharacter()
{
    delete ui;
}

/**
 * @brief Receives a new character from the model and adds it as a button in the UI.
 * @param character The character to add.
 * @param CharacterIndex The index of the character.
 */
void craftCharacter::receiveNewCharacter(Character& character, int CharacterIndex)
{
    qDebug() << "craft received new character" << character.getDef();

    // Create a new button for the character
    CharacterButton *button = new CharacterButton(CharacterIndex);
    button->setFixedSize(75, 75); // Set button size
    button->setIconSize(QSize(70, 70)); // Set icon size
    button->setIcon(QPixmap::fromImage(character.getImage())); // Set the character image
    ui->chracterLabel->setPixmap(QPixmap::fromImage(character.getImage())); // Update character label
    ui->defLabel->setText(character.getDef()); // Update definition label

    // Connect button to handle sending its index when clicked
    connect(button, &CharacterButton::sendSelfIndex, this, &craftCharacter::receiveCharacterButtonIndex);

    // Add the button to the layout
    characterLayout->addWidget(button);
    characterOverviewContainer->adjustSize(); // Adjust the container size

    qDebug() << "Size: " << characterLayout->count(); // Log the current count of buttons
}

/**
 * @brief Receives the index of a character button and emits a signal for crafting.
 * @param index The index of the selected character.
 */
void craftCharacter::receiveCharacterButtonIndex(int index)
{
    emit sendSelectedCharacterIndexForCraft(index);
}

/**
 * @brief Processes a character received from the model for Box2D interactions.
 * @param character The character to process.
 */
void craftCharacter::receiveCharacter(Character& character)
{
    qDebug() << "craft received";

    if (m_box2DWidget) {
        // Drop the character in the Box2D widget
        m_box2DWidget->dropRadical(character);
    }
}

/**
 * @brief Handles changes to the API key and emits the updated key.
 */
void craftCharacter::apiKeyChanged()
{
    emit sendAPIKey(ui->apiKey->toPlainText().toStdString());
}

/**
 * @brief Displays the hint window as a popup.
 */
void craftCharacter::popupHitWindows()
{
    hint.show();
}

/**
 * @brief Initiates the character crafting process and clears the Box2D widget.
 */
void craftCharacter::startCraftCharacter()
{
    emit sendCraftCharacterRequest();
    m_box2DWidget->clear(); // Clear the Box2D widget for new interactions
}
