#ifndef CRAFTCHARACTER_H
#define CRAFTCHARACTER_H

#include <QMainWindow>

namespace Ui {
class craftCharacter;
}

class craftCharacter : public QMainWindow
{
    Q_OBJECT

public:
    explicit craftCharacter(QWidget *parent = nullptr);
    ~craftCharacter();

private:
    Ui::craftCharacter *ui;
};

#endif // CRAFTCHARACTER_H
