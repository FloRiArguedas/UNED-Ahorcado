/*
Tarea #2 Floricela Arguedas Zúñiga

Programa que incentiva el aprendizaje de las vocales a través de un juego de ahorcado. Esto mediante el uso de punteros y funciones.

*/
#include <iostream>
#include <cstdlib> //Libreria para usar función rand
#include <ctime> //Librería para usar la función srand
#include <conio.h> //Librería para usar el getch

using namespace std;


//Declaracion de variables y funciones
char jugador1 [15];
char jugador2 [15];
char continuar = 's';
int intentos=5;
string adivinando;
char bandera='F';
int turnosj1 =0;
int turnosj2 =0;
int win1=0;
int win2=0;
bool turno_activo=true;
char generarvocal();
void solicitar_palabra(string *palabraadivinar,char*);
void imprimir_palabra(string *palabraadivinar,char*);
void turno_adivinar(string *);
bool verifica_ganador(string *palabraadivinar);

//Cuerpo del programa

int main()
{
    cout << "**** | Bienvenido al juego de Adivina que es | ****" <<endl;
    cout <<"\n";
    //Se genera ciclo para dar la posibilidad de iniciar el juego de nuevo.
    while (continuar == 's') {
            srand(time(0));
            string palabraadivinar;
            cout << " Digite el nombre del jugador #1: ";
            cin >>jugador1;
            cout <<"\n";
            cout << " Digite el nombre del jugador #2: ";
            cin >>jugador2;
            cout <<"\n";
            cout << "**** Comienza el juego ****"<<endl;
            cout <<"\n";
            //Se realiza un ciclo para limitar los turnos de los jugadores o permitirles salir antes del juego
            while ((turnosj1<5 || turnosj2<5) && continuar == 's'){
                //Llamo a función que genere vocal aleatoria.
                char vocalaleatoria = generarvocal(); //Guardo la vocal en una variable para después pasarla como parámetro.
                cout << " La vocal que vamos a utilizar es: " <<vocalaleatoria <<endl;
                cout <<"\n";
                solicitar_palabra(&palabraadivinar, &vocalaleatoria);
                imprimir_palabra (&palabraadivinar, &vocalaleatoria);
                turno_adivinar (&palabraadivinar);
                cout <<"\n";
                cout << " Desean continuar jugando ? Digite (S o N)" <<endl;
                cin >>continuar;
                continuar = tolower(continuar);
                //genero ciclo para validar parámetros.
                while (continuar != 's' && continuar != 'n'){
                    cout << " Desean continuar jugando ? Digite (S o N)" <<endl;
                    cin >>continuar;
                    continuar = tolower(continuar); //Convierto a minúscula el caracter.
                }
                //Reestablezco valores necesarios para jugar un nuevo turno en limpio.
                adivinando.erase();
                palabraadivinar.erase();
                intentos=5;
                bandera='F';
            }
            cout <<"\n";

            //Genero condiciones que consideran las posibilidades de gane en el juego, gracias a los contadores de gane para cada jugador.

            if (win1 > win2) cout << "**** |El ganador del juego es: " <<jugador1 <<" |**** "<<endl;

            if (win2 > win1) cout << "**** |El ganador del juego es: " <<jugador2 <<" |**** "<<endl;

            if (win1 == win2) cout << "**** |Hubo un empate| ****" <<endl;

            cout <<"\n";
            cout <<" **** |Bien Hecho | **** " <<endl;
            cout <<"\n";

        cout << " Desean jugar de nuevo ? Digite (S o N)" <<endl;
        cin >>continuar;
        continuar = tolower(continuar); //Convierto a minúscula el caracter.
        //Genero ciclo para verificar parámetros
        while (continuar != 's' && continuar != 'n'){
            cout << " Desean jugar de nuevo ? Digite (S o N)" <<endl;
            cin >>continuar;
            continuar = tolower(continuar); //Convierto a minúscula el caracter.
        }
        //Reestablezco todo lo necesario para iniciar un nuevo juego en limpio.
        adivinando.erase();
        win1=0;
        win2=0;
        turnosj1=0;
        turnosj2=0;
    }
        return 0;
}

//Creacion de funciones, para el funcionamiento del programa.

//Funcion para generar vocal aleatoria
char generarvocal(){
    char vocales[]= "aeiou";
    char vocal_al = vocales[rand()%5];
    return vocal_al;
}


//Funcion para solicitar palabra y mostrarla oculta en pantalla, adicional verifica que la palabra digitada contenga la vocal en juego.
void solicitar_palabra(string *palabraadivinar, char *vocalaleatoria) {
    char palabra;
    //Ciclo para solicitar la palabra al usuario y repetir en caso de que no contenga la vocal.
    while (bandera=='F'){
        if (turno_activo == true){
        cout <<jugador1 <<" digite la palabra que "<<jugador2 <<" debe adivinar "<<endl;
        turnosj1++;
        }
        else {
            cout <<jugador2 <<" digite la palabra que "<<jugador1 <<" debe adivinar "<<endl;
            turnosj2++;
        }
        cout <<"\n";
        palabra= getch(); //Utilizo el getch para leer los caracteres
        palabra=tolower(palabra);
        //Código entre las líneas 136 a 147 obtenido desde: (Angelini,marzo,2022)
        while (palabra != 13){
            if (palabra != 8){
                palabraadivinar->push_back(palabra); //con el push_back guardo los caracteres leídos, en el string.
                cout <<"*";
            }
            else {
                if (palabraadivinar->length() > 0) {
                    cout << "\b \b";
                    *palabraadivinar = palabraadivinar->substr(0,palabraadivinar->length() -1);//En caso de que el usuario toque la tecla de borrar, devuelvo los caracteres.
                }
            }
            palabra= getch();//Vuelvo a esperar una entrada del usuario diferente a "enter".
            palabra=tolower(palabra);
        }
        //Ciclo para revisar que contenga la vocal en juego.
        for (int i=0; i<palabraadivinar->length();i++){
          if (palabraadivinar->at(i)== *vocalaleatoria){
            bandera='T';
          }
        }
        //Si la vocal no está, se le indica al usuario.
        if (bandera=='F'){
            palabraadivinar->erase();//Borro lo que se guardo en el string, en caso de que el usuario no haya incluído la vocal.
            if (turno_activo == true){
                turnosj1--;
            }
            else {
                turnosj2--;
            }
            cout <<"\n";
            cout << "La palabra debe contener la vocal en juego: " <<*vocalaleatoria<<endl;
            cout <<"\n";
        }
    }
}

//Función para imprimir en pantalla el incógnito de la palabra por adivinar con su vocal(es) correspondiente.
void imprimir_palabra(string *palabraadivinar, char *vocalaleatoria){
cout <<"\n";
//En este ciclo utilizo el string adivinando, para guardarle _guiones_bajos que tengan la misma longitud de la palabra que debe adivinarse.
   for (int i=0; i < palabraadivinar->length(); i++){
        adivinando.push_back('_');
   }
//Con este ciclo reviso las casillas que contienen la vocal que está en juego y reemplazo el guión bajo en la posición que corresponde.
   for (int i=0; i<palabraadivinar->length();i++){
    if (palabraadivinar->at(i)== *vocalaleatoria){
        adivinando.at(i)= *vocalaleatoria;
    }
   }
   //Imprimo en pantalla la incógnita de la palabra por adivinar, mostrando la vocal en juego.
    cout <<"\n";
    for (int i=0; i<palabraadivinar->length();i++){
        cout <<" " <<adivinando.at(i) <<" ";
    }
    cout <<"\n";
}


//Funcion que revisa los caracteres digitados por el jugador que está adivinando, para saber si están en la palabra e imprimir en pantalla.
void turno_adivinar (string *palabraadivinar){
    char caracter;
    cout <<"\n";
    turno_activo=!turno_activo;
    if (turno_activo==true) cout <<jugador1 << " usted cuenta con " <<intentos <<" intentos... adivina "<<endl;
    else cout <<jugador2 << " usted cuenta con " <<intentos <<" intentos... adivina "<<endl;
    cout <<"\n";
    while (intentos>0 && verifica_ganador(palabraadivinar) == false){
        char acierto = 'f';
        cout <<"\n";
        cout << "Digite la letra: ";
        cin >>caracter;
        caracter=tolower(caracter);
        for (int i=0; i < palabraadivinar->length(); i++){
            if (caracter == palabraadivinar->at(i)){
                adivinando.at(i)= caracter;
                acierto = 't';
           }
        }

        cout<<"\n";
        for (int i=0; i < palabraadivinar->length(); i++){
         cout <<" "<<adivinando.at(i) <<" ";
        }
        cout <<"\n";
        if (acierto == 'f'){
            intentos--;
            cout << "Intentos restantes: "<<intentos<<endl;
            cout<<"\n";
        }
        if ( intentos == 0 && verifica_ganador(palabraadivinar) == false){
            cout << " Lo siento, la palabra a adivinar era: " <<*palabraadivinar <<endl;
            cout<<"\n";
        }
        if (verifica_ganador(palabraadivinar) == true){
            cout<<"\n";
            cout << " ****|Excelente adivinaste| **** " <<endl;
            cout<<"\n";
        }
    }
}

//Función que verifica si el jugador adivinó toda la palabra.
bool verifica_ganador (string *palabraadivinar) {
    for (int i=0; i < palabraadivinar->length(); i++){
        if ('_'== adivinando.at(i)){
            return false;
        }
    }
    if (turno_activo==true){
        win1++;
    }
    else {
        win2++;
    }
    return true;
}


//REFERENCIA

//Angelini, A.(26 marzo,2022).Ejemplo Ocultar palabra.[Post]https://aprende.uned.ac.cr/mod/forum/discuss.php?d=33700.









