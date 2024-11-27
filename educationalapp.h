#ifndef EDUCATIONALAPP_H
#define EDUCATIONALAPP_H

#include <QVBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include "character.h"
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class EducationalApp;
}
QT_END_NAMESPACE

class EducationalApp : public QMainWindow
{
    Q_OBJECT
    QPushButton *lastButtonSelected;
public:
    EducationalApp(Model &m, QWidget *parent = nullptr);
    ~EducationalApp();

public slots:
    void selectDrawBrush();
    void selectEraseBrush();
    void sendCleanCanvas();
    void receiveImage(QImage image);

    //this is the method will get a new character from the model, then add it as a button in the UI
    void receiveNewCharacter(Character newCharacter);

signals:
    void sendIsBrushPainting(bool isPainting);
    void sendClearCanvasSignal();

private:
    Ui::EducationalApp *ui;
    QVBoxLayout *characterLayout;
};
#endif // EDUCATIONALAPP_H
