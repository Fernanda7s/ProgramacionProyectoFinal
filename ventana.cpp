#include "ventana.h"
#include "ui_ventana.h"

Ventana::Ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
    CargarARchivo();
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::CargarARchivo(){
    //para limpiar el vector
    lista.clear();
    ui->tableRegistro->setRowCount(0);

    //para abrir y y leer el archivo
    QFile archivo ("tienda.txt");
    if(!archivo.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox:: warning(this,"Error","No se puede cargar los datos"+ QDir::currentPath());
        return;
    }
    QString contenido=archivo.readAll();
    archivo.close();

    QStringList lineas=contenido.split("\n");

    for(QString lines :lineas){
        if(lines.trimmed().isEmpty()){
            continue;
        }
        QStringList c= lines.split("|");

        if(c.size()==5){
            Tienda t;
            t.codigo=c[0];
            t.producto=c[1];
            t.categoria=c[2];
            t.stock=c[3].toInt();
            t.precio=c[4].toDouble();

            lista.push_back(t);

            int fila =ui->tableRegistro->rowCount();
            ui->tableRegistro->insertRow(fila);
            ui->tableRegistro->setItem(fila,0,new QTableWidgetItem(c[0]));
            ui->tableRegistro->setItem(fila,1,new QTableWidgetItem(c[1]));
            ui->tableRegistro->setItem(fila,2,new QTableWidgetItem(c[2]));
            ui->tableRegistro->setItem(fila,3, new QTableWidgetItem(c[3]));
            ui->tableRegistro->setItem(fila,4,new QTableWidgetItem(c[4]));
        }
    }

}

void Ventana::on_brnAgregar_clicked()
{
    Tienda nuevo;
    nuevo.codigo=ui->txtCodigo->text();
    nuevo.producto=ui->txtProducto->text();
    nuevo.categoria=ui->cbxCategoria->currentText();
    nuevo.stock=ui->sbxStock->text().toInt();
    nuevo.precio=ui->sbxPrecio->text().toDouble();

    lista.push_back(nuevo);
    //para que se agrege en la tabla
    int fila = ui->tableRegistro->rowCount();
    ui->tableRegistro->insertRow(fila);
    ui->tableRegistro->setItem(fila,0,new QTableWidgetItem(nuevo.codigo));
    ui->tableRegistro->setItem(fila,1,new QTableWidgetItem(nuevo.producto));
    ui->tableRegistro->setItem(fila,2,new QTableWidgetItem(nuevo.categoria));
    ui->tableRegistro->setItem(fila, 3, new QTableWidgetItem(QString::number(nuevo.stock)));
    ui->tableRegistro->setItem(fila,4,new QTableWidgetItem(QString::number(nuevo.precio)));

}


void Ventana::on_pushButton_5_clicked()
{
    QFile archivo("tienda.txt");
    if(!archivo.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox:: warning(this,"Error","No se pudo guardar el archivo");
        return;
    }
    QTextStream out (&archivo);
    for (auto&t: lista) {
        out<<t.codigo<<"|"
        <<t.producto<<"|"
        <<t.categoria<<"|"
        <<t.stock<<"|"
            <<t.precio<<"\n";
    }
    archivo.close();
    QMessageBox::information(this,"Error","Datos guardados");

}

