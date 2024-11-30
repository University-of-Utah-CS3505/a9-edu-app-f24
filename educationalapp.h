#ifndef EDUCATIONALAPP_H
#define EDUCATIONALAPP_H

#include <QVBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include "model.h"
#include "craftcharacter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EducationalApp;
}
QT_END_NAMESPACE

class EducationalApp : public QMainWindow
{
    Q_OBJECT
    QPushButton *lastButtonSelected;
    QWidget *characterOverviewContainer;
    QVBoxLayout * characterLayout;
    craftCharacter craftCharacter;
public:
    EducationalApp(Model &m, QWidget *parent = nullptr);
    ~EducationalApp();

public slots:
    void selectDrawBrush();
    void selectEraseBrush();
    void sendCleanCanvas();
    void receiveImage(QImage image);
    void updateConnotationHeader();

    //this is the method will get a new character from the model, then add it as a button in the UI
    void receiveNewCharacter(Character& character, int CharacterIndex);
    void receiveCharacterButtonIndex(int index);
    void receiveCharacter(Character& character);

    //this will show the craft window to create new character
    void popupCraftTable();

signals:
    void sendIsBrushPainting(bool isPainting);
    void sendClearCanvasSignal();
    void sendGetCharacterRequest(int requestCharacterIndex);

private:
    Ui::EducationalApp *ui;
};
#endif // EDUCATIONALAPP_H
