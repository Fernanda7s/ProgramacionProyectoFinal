#include "ventana.h"
#include "ui_ventana.h"

Ventana::Ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);

    QRegularExpression regExp("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]*$");
    QRegularExpressionValidator *soloLetras = new QRegularExpressionValidator(regExp, this);

    ui->txtProducto->setValidator(soloLetras);
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
{   if(ui->txtCodigo->text().isEmpty() || ui->txtProducto->text().isEmpty()||ui->sbxStock->value()==0||ui->sbxPrecio->value()==0) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, completa las casillas");
        return;
    }


    Tienda nuevo;


    nuevo.codigo=ui->txtCodigo->text().toUpper();
    nuevo.producto=ui->txtProducto->text().toUpper();
    nuevo.categoria=ui->cbxCategoria->currentText().toUpper();
    nuevo.stock=ui->sbxStock->value();
    nuevo.precio=ui->sbxPrecio->value();
    for (int i = 0; i < lista.size(); ++i) {
        if(lista[i].codigo == nuevo.codigo){
            QMessageBox::warning(this, "Error", "Ya existe el código: " + nuevo.codigo);
            return;
        }
    }
    lista.push_back(nuevo);
    //para que se agrege en la tabla
    int fila = ui->tableRegistro->rowCount();
    ui->tableRegistro->insertRow(fila);
    ui->tableRegistro->setItem(fila,0,new QTableWidgetItem(nuevo.codigo));
    ui->tableRegistro->setItem(fila,1,new QTableWidgetItem(nuevo.producto));
    ui->tableRegistro->setItem(fila,2,new QTableWidgetItem(nuevo.categoria));
    ui->tableRegistro->setItem(fila, 3, new QTableWidgetItem(QString::number(nuevo.stock)));
    ui->tableRegistro->setItem(fila,4,new QTableWidgetItem(QString::number(nuevo.precio)));


    ui->txtCodigo->clear();
    ui->txtProducto->clear();

    ui->sbxStock->clear();
    ui->sbxPrecio->clear();
}





void Ventana::on_btnBuscar_clicked()
{

    if (ui->txtCodigo->text().isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, completa las casillas");
        return;
    }
    QString codigo=ui->txtCodigo->text();
    bool encontrado=false;
    for (int i = 0; i < lista.size(); ++i) {
        if(QString::compare(lista[i].codigo, codigo, Qt::CaseInsensitive) == 0){
            ui->tableRegistro->selectRow(i);

            ui->txtProducto->setText(lista[i].producto);
            ui->cbxCategoria->setCurrentText(lista[i].categoria);
            ui->sbxStock->setValue(lista[i].stock);
            ui->sbxPrecio->setValue(lista[i].precio);
            encontrado = true;
            break;

        }

    }
    if(!encontrado){
        QMessageBox::warning(this,"Error","No encontrado");
        //limpiear cajas
    }
    ui->txtCodigo->clear();
    ui->txtProducto->clear();

    ui->sbxStock->clear();
    ui->sbxPrecio->clear();
}


void Ventana::on_btnActualizar_clicked()
{
    if(ui->txtCodigo->text().isEmpty() || ui->txtProducto->text().isEmpty()||ui->sbxStock->value()==0||ui->sbxPrecio->value()==0) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, completa las casillas");
        return;
    }

    QString codigo=ui->txtCodigo->text();
    bool encontrado=false;

    for (int i = 0; i < lista.size(); ++i){
        if(QString::compare(lista[i].codigo, codigo, Qt::CaseInsensitive) == 0){

            lista[i].codigo = ui->txtCodigo->text();
            lista[i].producto = ui->txtProducto->text();
            lista[i].categoria = ui->cbxCategoria->currentText();
            lista[i].stock = ui->sbxStock->value();
            lista[i].precio = ui->sbxPrecio->value();
            encontrado =true;

            // Actualizar tabla
            ui->tableRegistro->item(i, 0)->setText(lista[i].codigo);
            ui->tableRegistro->item(i, 1)->setText(lista[i].producto);
            ui->tableRegistro->item(i, 2)->setText(lista[i].categoria);
            ui->tableRegistro->item(i, 3)->setText(QString::number(lista[i].stock));
            ui->tableRegistro->item(i, 4)->setText(QString::number(lista[i].precio));
        }
    }
    if(!encontrado){
        QMessageBox::warning(this,"Error","No encontrado");
        //limpiear cajas
    }
    ui->txtCodigo->clear();
    ui->txtProducto->clear();

    ui->sbxStock->clear();
    ui->sbxPrecio->clear();
}




void Ventana::on_btnEliminar_clicked()
{
    if (ui->txtCodigo->text().isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, completa las casillas");
        return;
    }
    QString codigo=ui->txtCodigo->text();
    bool encontrado=false;

    for (int i = 0; i < lista.size(); ++i){
        if(QString::compare(lista[i].codigo, codigo, Qt::CaseInsensitive) == 0){
            lista.erase(lista.begin()+i);
            ui->tableRegistro->removeRow(i);
            encontrado==true;
        }
    }
    if(!encontrado){
        QMessageBox::warning(this,"Error","No encontrado");
        //limpiear cajas
    }
    ui->txtCodigo->clear();
    ui->txtProducto->clear();

    ui->sbxStock->clear();
    ui->sbxPrecio->clear();
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
    QMessageBox::information(this,"MENSAJE","Datos guardados");
    this->close();

}





