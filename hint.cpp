#include "hint.h"
#include "ui_hint.h"

/**
 * @brief Constructs the Hint dialog and sets up the UI.
 * @param parent Optional parent widget.
 */
Hint::Hint(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Hint)
{
    ui->setupUi(this); // Initialize the UI components
}

/**
 * @brief Destructor for the Hint dialog.
 * Cleans up the UI resources.
 */
Hint::~Hint()
{
    delete ui; // Free the UI memory
}
