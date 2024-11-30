#ifndef CRAFTCHARACTER_H
#define CRAFTCHARACTER_H

#include <QVBoxLayout>
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
    QWidget *characterOverviewContainer;
    QVBoxLayout * characterLayout;

public:
    explicit craftCharacter(QWidget *parent = nullptr);
    ~craftCharacter();

public slots:
    //this is the method will get a new character from the model, then add it as a button in the UI
    void receiveNewCharacter(Character& character, int CharacterIndex);
    void receiveCharacter(Character& character);

    //this will be implemented in the Receive new Charcter part
    void receiveCharacterButtonIndex(int index);


signals:
    //this can be used for get a character detail from model and send to box2D
    void sendGetCharacterRequest(int requestCharacterIndex);

private:
    Ui::craftCharacter *ui;
};

#endif // CRAFTCHARACTER_H
