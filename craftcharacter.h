#ifndef CRAFTCHARACTER_H
#define CRAFTCHARACTER_H

#include <QVBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include "model.h"
#include "box2dwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class craftCharacter;
}
QT_END_NAMESPACE

class craftCharacter : public QMainWindow
{
    Q_OBJECT
    QList<QPushButton *> allCharacters;
    /// characters that user selected and waiting to be send. Will be cleard after send
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

    void apiKeyChanged();

    void startCraftCharacter();

signals:
    ///
    /// \brief sendSelectedCharacterIndexForCraft this can be used for get a character detail from model and send to box2D
    /// \param requestCharacterIndex
    ///
    void sendSelectedCharacterIndexForCraft(int requestCharacterIndex);

    void sendCraftCharacterRequest();

    void sendAPIKey(std::string apiKey);

private:
    Ui::craftCharacter *ui;
    box2DWidget* m_box2DWidget;
};

#endif // CRAFTCHARACTER_H
