#ifndef CRAFTCHARACTER_H
#define CRAFTCHARACTER_H

#include <QMainWindow>
#include <QPushButton>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class craftCharacter;
}
QT_END_NAMESPACE

class craftCharacter : public QMainWindow
{
    Q_OBJECT
    QList<QPushButton *> allCharacters;
    QPushButton* lastButtonSelected;

public:
    explicit craftCharacter(QWidget *parent = nullptr);
    ~craftCharacter();

public:

private:
    Ui::craftCharacter *ui;
};

#endif // CRAFTCHARACTER_H
