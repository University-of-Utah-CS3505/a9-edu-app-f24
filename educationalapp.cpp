#include "educationalapp.h"
#include "ui_educationalapp.h"
#include "canvaslabel.h"

EducationalApp::EducationalApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EducationalApp)
{
    ui->setupUi(this);
}

EducationalApp::~EducationalApp()
{
    delete ui;
}
