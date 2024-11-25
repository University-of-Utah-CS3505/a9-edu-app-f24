#ifndef EDUCATIONALAPP_H
#define EDUCATIONALAPP_H

#include <QMainWindow>
#include <QPushButton>
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

signals:
    void sendIsBrushPainting(bool isPainting);
    void clearCanvas();

private:
    Ui::EducationalApp *ui;
};
#endif // EDUCATIONALAPP_H
