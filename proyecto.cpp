
#include<iostream>
#include<string>
#include <vector>
#include <fstream>

using namespace std;
struct Pelicula{
    int Id;
    string titulo;
    string director;
    int anio;
    string genero;
};

//voy hacerlo con usuriao y contraseña

//de alli que ingrese al menu

void menu(int num) {
    cout<<"=======MENU PELICULAS ======================="<<endl;
    cout<<"1. Ingresar "<<endl;
    cout<<"2. Buscar"<<endl;
    cout<<"3. Mostrar"<<endl;
    cout<<"4. Eliminar "<<endl;
    cout<<"5. Actualizar "<<endl;
    cout<<"6. Salir "<<endl;
    cout<<endl;
}
int main() {
    vector <Pelicula> peliculas;
    const string ruta = "peliculas.txt";


    int opcion;
    menu(opcion);
    do {
        switch (opcion) {
            case 1:
                break;
            case 2:
                break;
                case 3:
                break;
                case 4:
                break;
                case 5:
                break;
                case 6:
                break;
                default:

        }
    }while (opcion != 6);
    return 0;
}

