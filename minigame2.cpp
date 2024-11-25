#include "miniGame2.h"
#include "ui_miniGame2.h"
#include "canvaslabel.h"


miniGame2::miniGame2(Model &m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::miniGame2){}


miniGame2::~miniGame2()
{
    delete ui;
}

