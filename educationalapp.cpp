#include "educationalapp.h"
#include "ui_educationalapp.h"
#include "canvaslabel.h"
#include "characterbutton.h"

EducationalApp::EducationalApp(Model &m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EducationalApp)
{
    ui->setupUi(this);
    //this is for drawing part
    connect(ui->Brush_Button, &QPushButton::pressed, this, &EducationalApp::selectDrawBrush);
    connect(ui->Erase_Button, &QPushButton::pressed, this, &EducationalApp::selectEraseBrush);
    connect(ui->Clean_Button, &QPushButton::pressed, this, &EducationalApp::sendCleanCanvas);
    connect(this, &EducationalApp::sendIsBrushPainting, &m, &Model::receiveIsBrushPainting);
    connect(this, &EducationalApp::sendClearCanvasSignal, &m, &Model::receiveCleanCanvas);
    connect(this, &EducationalApp::sendGetCharacterRequest, &m, &Model::receiveGetCharacterRequest);
    connect(this, &EducationalApp::sendSelectNewCharactersIndex, &m, &Model::receiveSelectedCharactersIndex);
    connect(ui->Canvas, &CanvasLabel::sendMouseEvent, &m, &Model::receiveMouseEvent);


    connect(&m, &Model::sendOverlayImage, this, &EducationalApp::receiveImage);
    connect(&m, &Model::sendNewCharacter, this, &EducationalApp::receiveNewCharacter);
    connect(&m, &Model::sendRequestedCharacter, this, &EducationalApp::receiveCharacter);
    connect(&m, &Model::sendCorrectness, this, &EducationalApp::receiveCorrectness);
    //press the craft button,the level will show up
    connect(ui->Craft_Button, &QPushButton::pressed, this, &EducationalApp::popupCraftTable);

    //this part will be the crafttable, which will connect to the model data set
    connect(&m, &Model::sendNewCharacter, &(this->craftCharacter), &craftCharacter::receiveNewCharacter);
    connect(&m, &Model::sendCraftSelectedCharacter, &(this->craftCharacter), &craftCharacter::receiveCharacter);
    connect(&(this->craftCharacter), &craftCharacter::sendSelectedCharacterIndexForCraft, &m, &Model::receiveSelectedCharacterIndexForCraft);
    connect(&(this->craftCharacter), &craftCharacter::sendCraftCharacterRequest, &m, &Model::receiveCraftCharacterRequest);


    lastButtonSelected = ui->Brush_Button;
    ui->Brush_Button->setEnabled(false);
    emit sendIsBrushPainting(true);


    // API key
    connect(&(this->craftCharacter), &craftCharacter::sendAPIKey, &m, &Model::receiveAPIKey);

    // setup the scroll area
    characterOverviewContainer = new QWidget;
    characterLayout = new QVBoxLayout(characterOverviewContainer);
    characterLayout->setAlignment(Qt::AlignTop);
    characterLayout->setContentsMargins(0, 0, 0, 0);
    characterLayout->setSpacing(10); // set button spacing
    characterOverviewContainer->setLayout(characterLayout);
    ui->CharacterSelector->setWidgetResizable(true);
    ui->CharacterSelector->setWidget(characterOverviewContainer);
    ui->CharacterSelector->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->CharacterSelector->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}

EducationalApp::~EducationalApp()
{
    delete ui;
}

void EducationalApp::selectDrawBrush(){
    lastButtonSelected->setEnabled(true);
    ui->Brush_Button->setEnabled(false);
    lastButtonSelected = ui->Brush_Button;
    emit sendIsBrushPainting(true);
}
void EducationalApp::selectEraseBrush(){
    lastButtonSelected->setEnabled(true);
    ui->Erase_Button->setEnabled(false);
    lastButtonSelected = ui->Erase_Button;
    emit sendIsBrushPainting(false);
}
void EducationalApp::sendCleanCanvas(){
    emit sendClearCanvasSignal();
}


void EducationalApp::receiveImage(QImage image){
    ui->Canvas->setPixmap(QPixmap::fromImage(image));
}

void EducationalApp::receiveNewCharacter(Character& character, int CharacterIndex)
{
    qDebug() << "received";

    CharacterButton *button = new CharacterButton(CharacterIndex);
    button->setFixedSize(75, 75);
    button->setIconSize(QSize(70, 70));
    button->setIcon(QPixmap::fromImage(character.getImage()));

    connect(button, &CharacterButton::sendSelfIndex, this, &EducationalApp::receiveCharacterButtonIndex);

    characterLayout->addWidget(button);

    characterOverviewContainer->adjustSize(); // adjust button to center
}

void EducationalApp::updateConnotationHeader(){
    ui->Connotation_Description->setText("<b>BK喜歡玩黃遊</b>");
}

void EducationalApp::receiveCharacterButtonIndex(int index){
    emit sendGetCharacterRequest(index);
    emit sendSelectNewCharactersIndex(index);
}

void EducationalApp::receiveCharacter(Character& character){
    ui->Connotation_Description->setText(character.getDef());
    ui->Pronounce_Description->setText(character.getSpell());
    ui->Canvas->setPixmap(QPixmap::fromImage(character.getImage()));
}

void EducationalApp::popupCraftTable(){
    craftCharacter.show();
}

void EducationalApp::receiveCorrectness(int correctness){
    ui->correctness->setValue(correctness);
}
