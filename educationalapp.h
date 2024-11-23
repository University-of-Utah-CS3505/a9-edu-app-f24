#ifndef EDUCATIONALAPP_H
#define EDUCATIONALAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class EducationalApp;
}
QT_END_NAMESPACE

class EducationalApp : public QMainWindow
{
    Q_OBJECT

public:
    EducationalApp(QWidget *parent = nullptr);
    ~EducationalApp();

private:
    Ui::EducationalApp *ui;
};
#endif // EDUCATIONALAPP_H
