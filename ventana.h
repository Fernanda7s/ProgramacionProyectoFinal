#ifndef VENTANA_H
#define VENTANA_H
#include <QRegularExpressionValidator>
#include <QMainWindow>
#include <vector>
#include <QFile>
#include<QIODevice>
#include<QMessageBox>
#include<QDir>


struct Tienda{
    //voy a cambiar el codigo a string
    QString codigo;
    QString producto;
    QString categoria;
    int stock;
    double precio;
};

namespace Ui { class Ventana; }


class Ventana : public QMainWindow {
    Q_OBJECT
public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();
    void CargarARchivo();


    //aqui voy a ver como funcionan los botones
private slots:

    void on_brnAgregar_clicked();

    void on_pushButton_5_clicked();

    void on_btnBuscar_clicked();

    void on_btnActualizar_clicked();

    void on_btnEliminar_clicked();

private:
    Ui::Ventana *ui;
    std::vector<Tienda>lista;
};


#endif // VENTANA_H
