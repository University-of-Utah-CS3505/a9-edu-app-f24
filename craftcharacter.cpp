#include "craftcharacter.h"
#include "ui_craftcharacter.h"
#include "characterbutton.h"

craftCharacter::craftCharacter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::craftCharacter)
{
    ui->setupUi(this);


    //the way this ui communicate with model radical dataset is in the educational app ui
    // setup the scroll area to contain the button
    characterOverviewContainer = new QWidget;
    characterLayout = new QVBoxLayout(characterOverviewContainer);
    characterLayout->setAlignment(Qt::AlignTop);
    characterLayout->setContentsMargins(0, 0, 0, 0);
    characterLayout->setSpacing(10); // set button spacing
    characterOverviewContainer->setLayout(characterLayout);

    // add scroll area to the Character selector weight area
    ui->CharacterSelector->setWidgetResizable(true);
    ui->CharacterSelector->setWidget(characterOverviewContainer);
    ui->CharacterSelector->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->CharacterSelector->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Create the Box2D widget
    m_box2DWidget = new box2DWidget(this);

    // Create a central widget to hold layouts
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Add the Box2D widget to the layout
    mainLayout->addWidget(m_box2DWidget);

    // Set the central widget
    setCentralWidget(centralWidget);

    //connect api part
    connect(this->ui->apiKey, &QTextEdit::textChanged, this, &craftCharacter::apiKeyChanged);

    connect(this->ui->craftButton, &QPushButton::pressed, this, &craftCharacter::startCraftCharacter);

    //DEBUG, PLEASE DELETE IT!!!!!!!
    selectedCharacters.push_back("火");
    selectedCharacters.push_back("火");
}

craftCharacter::~craftCharacter()
{
    delete ui;
}
void craftCharacter::receiveNewCharacter(Character& character, int CharacterIndex){
    qDebug() << "craft received new character" << character.getDef();


    CharacterButton *button = new CharacterButton(CharacterIndex);
    button->setFixedSize(75, 75);
    button->setIconSize(QSize(70, 70));
    button->setIcon(QPixmap::fromImage(character.getImage()));
    ui->chracterLabel->setPixmap(QPixmap::fromImage(character.getImage()));
    ui->defLabel->setText(character.getDef());

    connect(button, &CharacterButton::sendSelfIndex, this, &craftCharacter::receiveCharacterButtonIndex);

    characterLayout->addWidget(button);

    characterOverviewContainer->adjustSize(); // adjust button to center
    qDebug() << "Size: "<<characterLayout->count();
}

void craftCharacter::receiveCharacterButtonIndex(int index){
     emit sendGetCharacterRequest(index);
}
void craftCharacter::receiveCharacter(Character& character){
    // for box 2d, this is the slot, when model send the user clicked radical,
    // the box 2d will drop a box with this character in the box
    qDebug() << "craft received";

    if (m_box2DWidget) {
        // Drop the radical in the Box2D widget
        m_box2DWidget->dropRadical(character);
    }
}

void craftCharacter::apiKeyChanged(){
    emit sendAPIKey(this->ui->apiKey->toPlainText().toStdString());
}

void craftCharacter::startCraftCharacter(){
    emit sendCraftCharacterRequest(selectedCharacters);
    selectedCharacters.clear();
    //TODO update the box2d about characters
}
