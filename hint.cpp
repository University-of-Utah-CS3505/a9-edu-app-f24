#include "hint.h"
#include "ui_hint.h"

Hint::Hint(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Hint)
{
    ui->setupUi(this);
}

Hint::~Hint()
{
    delete ui;
}
