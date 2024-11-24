#include "educationalapp.h"
#include "ui_educationalapp.h"
#include "canvaslabel.h"


EducationalApp::EducationalApp(Model &m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EducationalApp)
{
    ui->setupUi(this);
    connect(ui->Brush_Button, &QPushButton::pressed, this, &EducationalApp::selectDrawBrush);
    connect(ui->Erase_Button, &QPushButton::pressed, this, &EducationalApp::selectEraseBrush);
    connect(ui->Clean_Button, &QPushButton::pressed, this, &EducationalApp::sendCleanCanvas);
    connect(this, &EducationalApp::sendIsBrushPainting, &m, &Model::receiveIsBrushPainting);
    connect(this, &EducationalApp::sendCleanCanvas, &m, &Model::receiveCleanCanvas);
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
    emit clearCanvas();
}
