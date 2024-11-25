#include "craftcharacter.h"
#include "ui_craftcharacter.h"

craftCharacter::craftCharacter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::craftCharacter)
{
    ui->setupUi(this);
}

craftCharacter::~craftCharacter()
{
    delete ui;
}
