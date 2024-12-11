#ifndef HINT_H
#define HINT_H

#include <QDialog>

namespace Ui {
class Hint;
}

/**
 * @class Hint
 * @brief A dialog window to provide hints or tips to the user.
 *
 * This class represents a popup dialog that can be used to display helpful hints or guidance in the application.
 *
 * Team Members: Bingkun Han, Shu Chen, Rohith Veeramachaneni, Ping-Hsun Hsieh
 * Course: CS3500 - A9 Educational App
 */
class Hint : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the Hint dialog.
     * @param parent Optional QWidget parent (default is nullptr).
     */
    explicit Hint(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Hint dialog.
     */
    ~Hint();

private:
    Ui::Hint *ui; ///< Pointer to the UI object.
};

#endif // HINT_H
