#ifndef VENTANA_H
#define VENTANA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Ventana; }
QT_END_NAMESPACE

class Ventana : public QMainWindow
{
public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();

private:
    Ui::Ventana *ui;
};

#endif // VENTANA_H
