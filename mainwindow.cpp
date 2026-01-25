#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ventana.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegularExpression regExp("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]*$");
    QRegularExpressionValidator *soloLetras = new QRegularExpressionValidator(regExp, this);

    ui->txtUsuario->setValidator(soloLetras);
    ui->txtPassword->setValidator(soloLetras);
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


    if(usuario=="epn"&&password=="epn") {
        //crear la venta para abrir
        qDebug() << "Login correcto, intentando abrir ventana...";
        Ventana *v2 = new Ventana();
        v2->show();
        this->hide();
    }else{
        //QMessageBox::warning (this,"Datos Ingresado ","Tiene un arrero vulva a intentarlo");
        qDebug() << "Login fallido. Usuario ingresado: " << usuario;
    }
}

