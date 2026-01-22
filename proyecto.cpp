
#include<iostream>
#include<string>
#include <vector>
#include <fstream>

using namespace std;
struct Tienda{
    int codigo;
    string producto;
    string categoria;
    int stock;
    double precio;
};
void cargarArchivo (vector<Tienda> &market,const string &ruta) {
    //leer
    ifstream archivo(ruta);

    Tienda t;

    if (!archivo) {
        cout<<"no existe el archivo"<<endl;
    }


    while (archivo >> t.codigo) {
        archivo.ignore(); // para ingorar el |
        //lee el texto del archivo
        getline(archivo, t.producto, '|');
        getline(archivo, t.categoria, '|');
        archivo >> t.stock;
        //leer enteero y double ignorando |
        archivo.ignore();
        archivo >> t.precio;
        //para guardar en el vector
        archivo.ignore();
        market.push_back(t);
    }

    archivo.close();

}
//los archivos no te olvides
void guardarArchivo(vector<Tienda> &market,const string &ruta) {
    //sobreescribe
    //tambien creea el archivo
    ofstream archivo(ruta, ios::out);

    if (!archivo) {
        cout<<"no se abre el archivo "<<endl;
        return;
    }
    for(int i=0;i<market.size();i++) {
        archivo<<market[i].codigo<<"|"
        <<market[i].producto<<"|"
        <<market[i].categoria<<"|"
        <<market[i].stock<<"|"
        <<market[i].precio<<endl;

    }
    archivo.close();



}

//voy hacerlo con usuriao y contraseña
bool ingresarUsuario() {
    string password;
    string usuario;
    cout<<"Ingrese un usuario: ";
    cin>>usuario;
    cout<<"Ingresar contraeña";
    cin>>password;

    if(usuario=="usuarioEpn"&&password=="usuarioEpn") {
        cout<<"Bienvenido al sistema "<<endl;
        return true;

    }

}



void ingresar(vector<Tienda> &market) {
    Tienda nuevo;
    cout<<"Ingrese un codigo: ";
    cin>>nuevo.codigo;
    for (int i = 0; i < market.size(); i++) {
        if (market[i].codigo == nuevo.codigo) {
            cout << "Codigo ya existe" << endl;
            return;
        }
    }
    cin.ignore();
    cout<<"Ingrese un produto: ";
    getline(cin,nuevo.producto);
    cout<<"Ingrese un categoria: ";
    cin>>nuevo.categoria;
    cout<<"Ingrese un stock: ";
    cin>>nuevo.stock;
    cout<<"Ingrese un precio: ";
    cin>>nuevo.precio;
    market.push_back(nuevo);

}

//de alli que ingrese al menu
void buscar(vector<Tienda> &market) {
    if (market.empty()) {
        cout<<"Esta vacio"<<endl;
        return;
    }

    bool encontrado = false;
    int codigo;
    cout<<"Codigo:";
    cin>>codigo;
    for(int i=0;i<market.size();i++) {
        if(market[i].codigo==codigo) {
            cout<<"Producto: "<<market[i].producto<<endl;
            cout<<"Categoria: "<<market[i].categoria<<endl;
            cout<<"Stock: "<<market[i].stock<<endl;
            cout<<"Precio: "<<market[i].precio<<endl;
            encontrado = true;
            break;

        }
    }
    if(!encontrado) {
        cout<<"No encontrado "<<endl;
    }
}



void mostrar(vector<Tienda> &market) {
    if (market.empty()) {
        cout<<"Esta vacio"<<endl;
        return;
    }
    for(int i=0;i<market.size();i++) {
        cout<<"______________________________"<<endl;
        cout<<"Codigo:"<<market[i].codigo<<endl;
        cout<<"producto:"<<market[i].producto<<endl;
        cout<<"Categoria:"<<market[i].categoria<<endl;
        cout<<"Stock:"<<market[i].stock<<endl;
        cout<<"Precio:"<<market[i].precio<<endl;
        cout<<endl;
    }
}
void actualizar(vector<Tienda> &market,const string &ruta) {
    if (market.empty()) {
        cout<<"Esta vacio"<<endl;
        return;
    }
    bool encontrado = false;
    int codigo;
    cout<<"Codigo:";
    cin>>codigo;
    for(int i=0;i<market.size();i++) {
        if(market[i].codigo==codigo) {
            cout<<"Producto: ";
            cin.ignore();
            getline(cin,market[i].producto);
            cout<<"Categoria: ";
            cin>>market[i].categoria;
            cout<<"Stock: ";
            cin>>market[i].stock;
            cout<<"Precio: ";
            cin>>market[i].precio;
            cout<<"Actualizado correctamente "<<endl;
            encontrado = true;

        }
    }
    if (encontrado) {
        guardarArchivo(market,ruta);
        cout<<"Guardado en er archivo"<<endl;
    }else {
        cout<<"codigo no encontrado"<<endl;

    }
}

void eliminar (vector<Tienda> &market,const string &ruta) {
    if (market.empty()) {
        cout<<"Esta vacio"<<endl;
        return;
    }
    bool encontrado = false;
    int codigo;
    cout<<"Codigo:";
    cin>>codigo;
    for(int i=0;i<market.size();i++) {
        if(market[i].codigo==codigo) {
           market.erase(market.begin()+i);
            guardarArchivo(market,ruta);
            cout<<"eliminado correctamente "<<endl;
            encontrado = true;
            return;

        }
    }
    if (!encontrado) {
        cout<<"codigo no encontrado"<<endl;
    }
}


void menu() {
    cout<<"=======MENU PELICULAS ======================="<<endl;
    cout<<"1. Ingresar "<<endl;
    cout<<"2. Buscar"<<endl;
    cout<<"3. Mostrar"<<endl;
    cout<<"4. Eliminar "<<endl;
    cout<<"5. Actualizar "<<endl;
    cout<<"6. Salir "<<endl;
    cout<<"ingrese opcion: ";
}
int main() {
    vector <Tienda> market;
    const string ruta = "tienda.txt";

    //ayuda a que el vector no empiece vacio
    cargarArchivo(market,ruta);
    ingresarUsuario();


    int opcion;

    do {
        menu();
        cin>>opcion;
        switch (opcion) {
            case 1:
                ingresar(market);
                guardarArchivo(market,ruta);
                break;
            case 2:
                buscar(market);
                break;
            case 3:
                mostrar(market);
                break;
            case 4:
                eliminar(market,ruta);
                break;
            case 5:
                actualizar(market, ruta);
                break;
            case 6:
                cout<<"SALIENDO ____-----"<<endl;
                break;
            default:
                break;
        }
    }while (opcion != 6);


    return 0;
}