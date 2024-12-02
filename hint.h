#ifndef HINT_H
#define HINT_H

#include <QDialog>

namespace Ui {
class Hint;
}

class Hint : public QDialog
{
    Q_OBJECT

public:
    explicit Hint(QWidget *parent = nullptr);
    ~Hint();

private:
    Ui::Hint *ui;
};

#endif // HINT_H
