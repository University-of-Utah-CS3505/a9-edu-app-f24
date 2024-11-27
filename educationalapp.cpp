#include "educationalapp.h"
#include "ui_educationalapp.h"
#include "canvaslabel.h"
#include "characterbutton.h"

EducationalApp::EducationalApp(Model &m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EducationalApp)
{
    ui->setupUi(this);
    connect(ui->Brush_Button, &QPushButton::pressed, this, &EducationalApp::selectDrawBrush);
    connect(ui->Erase_Button, &QPushButton::pressed, this, &EducationalApp::selectEraseBrush);
    connect(ui->Clean_Button, &QPushButton::pressed, this, &EducationalApp::sendCleanCanvas);
    connect(this, &EducationalApp::sendIsBrushPainting, &m, &Model::receiveIsBrushPainting);
    connect(this, &EducationalApp::sendClearCanvasSignal, &m, &Model::receiveCleanCanvas);

    connect(ui->Canvas, &CanvasLabel::sendMouseEvent, &m, &Model::receiveMouseEvent);

    connect(&m, &Model::sendOverlayImage, this, &EducationalApp::receiveImage);

    lastButtonSelected = ui->Brush_Button;
    ui->Brush_Button->setEnabled(false);
    emit sendIsBrushPainting(true);

    //character layout setup
    characterLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
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
    qDebug() << "received";
    ui->Canvas->setPixmap(QPixmap::fromImage(image));
}

//BK part writing the update buttons in the UI
void EducationalApp::receiveNewCharacter(Character newCharacter)
{
    CharacterButton *newButton = new CharacterButton(newCharacter);
    characterLayout->addWidget(newButton);
}
