#include "ventana.h"
#include "ui_ventana.h"

// Implementación del constructor
Ventana::Ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
}

// Implementación del destructor
Ventana::~Ventana()
{
    delete ui;
}

