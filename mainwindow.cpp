#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnIngresar_clicked()
{
    QString password=ui->txtPassword->text();
    QString usuario=ui->txtUsuario->text();
    //y si los datos estan vacio
    if (usuario.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Campos vacíos");
        return;
    }


    if(usuario=="usuarioEpn"&&password=="usuarioEpn") {
        //crear la venta para abrir


    }else{
        QMessageBox::warning (this,"Datos Ingresado ","Tiene un arrero vulva a intentarlo");
    }
}

