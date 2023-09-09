#include <iostream>
#include <stdio.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

using namespace std;

void inicializarTabla();
void mostrarTabla();
bool fueraDeRango(int,int);
bool estadoTerminal();

void elegirValor();
void comenzarJuego();
void insertarFichaHumano();
void insertarFichaCPU();
int minimax(bool);

char letraJugador=' ', letraCPU=' ';
int espaciosLibres;
char tabla[3][3];

int main()
{
    char c;
    int opcion, ch;
    while(true)
    {
        cout<<
        "Bienvenido/a al programa de Tic Tac Toe con minimax.\n"
        "1-Elegir ficha.\n"
        "2-Comenzar juego.\n"
        "3-Salir.\n"
        "Ingrese su opcion: ";
        cin>>opcion;
        system(CLEAR);
        switch(opcion)
        {
        case 1:
            elegirValor();
            break;
        case 2:
            comenzarJuego();
            break;
        case 3:
            return 0;
        default:
            cout<<"ERROR: opcion invalida."<<endl;
        }
        while((c=getchar())!='\n' && c!=EOF);
        cout<<endl<<"Presione ENTER para continuar...";
        ch=getchar();
        system(CLEAR);
    }
    return 1;
}

void inicializarTabla()
{
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            tabla[i][j]=' ';
    }
    return;
}

void mostrarTabla()
{
    cout<<endl;
    for(int i=0;i<3;i++)
    {
        if(i!=0)
            cout<<"---|---|---"<<endl;
        for(int j=0;j<3;j++)
        {
            cout<<" "<<tabla[i][j];
            if(j!=2)
                cout<<" |";
        }
        cout<<endl;
    }
    return;
}

bool fueraDeRango(int fila, int columna)
{
    if(fila>2 || fila<0 || columna>2 || columna<0)
        return true;
    return false;
}

bool estadoTerminal()
{
    int i,j=0;
    for(i=0;i<3;i++)
    {
        if(tabla[i][j]!=' ')
        {
            if(tabla[i][j]==tabla[i][j+1] && tabla[i][j]==tabla[i][j+2])
                return true;
        }
    }
    i=0;
    for(j=0;j<3;j++)
    {
        if(tabla[i][j]!=' ')
        {
            if(tabla[i][j]==tabla[i+1][j] && tabla[i][j]==tabla[i+2][j])
                return true;
        }
    }
    i=0;
    j=0;
    if(tabla[i][j]!=' ')
    {
        if(tabla[i][j]==tabla[i+1][j+1]&& tabla[i][j]==tabla[i+2][j+2])
            return true;
    }
    if(tabla[i+2][j]!=' ')
    {
        if(tabla[i+2][j]==tabla[i+1][j+1] && tabla[i+2][j]==tabla[i][j+2])
            return true;
    }
    return false;
}

void elegirValor()
{
    int opcion=0;
    cout<<
    "Ingrese con que valor desea jugar:\n"
    "Opcion 1: X (comenzar primero)\n"
    "Opcion 2: O (comenzar segundo)\n";
    while(opcion!=1 && opcion!=2)
    {
        cout<<"Opcion elegida: ";
        cin>>opcion;
        switch(opcion)
        {
        case 1:
            letraJugador='X';
            letraCPU='O';
            break;
        case 2:
            letraJugador='O';
            letraCPU='X';
            break;
        default:
            cout<<"ERROR: la opcion elegida no es valida."<<endl;
        }
    }
    return;
}

void comenzarJuego()
{
    inicializarTabla();
    espaciosLibres=9;
    if(letraJugador==' ')
    {
        cout<<"ERROR: no se ha elegido una ficha para el jugador."<<endl;
        return;
    }
    if(letraJugador=='X')
        insertarFichaHumano();
    else
        insertarFichaCPU();
    return;
}

void insertarFichaHumano()
{
    mostrarTabla();
    if(estadoTerminal())
    {
        cout<<endl<<"GANADOR: CPU"<<endl;
        return;
    }
    else if(espaciosLibres==0)
    {
        cout<<endl<<"LA POSICION TERMINA EN EMPATE. Ultimo turno: CPU"<<endl;
        return;
    }
    bool valido;
    int fila,columna;
    do
    {
        valido=true;
        cout<<"ingresar fila (1-3): ";
        cin>>fila;
        cout<<"ingresar columna (1-3): ";
        cin>>columna;
        if(fueraDeRango(fila-1,columna-1) || tabla[fila-1][columna-1]!=' ')
            valido=false;
    }while(!valido);
    tabla[fila-1][columna-1]=letraJugador;
    espaciosLibres--;
    system(CLEAR);
    insertarFichaCPU();
    return;
}

void insertarFichaCPU()
{
    if(estadoTerminal())
    {
        mostrarTabla();
        cout<<endl<<"GANADOR: JUGADOR"<<endl;
        return;
    }
    else if(espaciosLibres==0)
    {
        mostrarTabla();
        cout<<endl<<"LA POSICION TERMINA EN EMPATE. Ultimo turno: Jugador"<<endl;
        return;
    }
    int movValor, mejorMovValor=-100;
    int mejorMovFila=-1, mejorMovColumna=-1;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(tabla[i][j]==' ')
            {
                tabla[i][j]=letraCPU;
                espaciosLibres--;
                movValor=minimax(false);
                if(movValor>mejorMovValor)
                {
                    mejorMovValor=movValor;
                    mejorMovFila=i;
                    mejorMovColumna=j;
                }
                tabla[i][j]=' ';
                espaciosLibres++;
            }
        }
    }
    tabla[mejorMovFila][mejorMovColumna]=letraCPU;
    espaciosLibres--;
    system(CLEAR);
    insertarFichaHumano();
    return;
}

int minimax(bool turnoCPU)
{
    if(estadoTerminal())
    {
        if(turnoCPU)
            return -1*(espaciosLibres+1);
        else
            return 1*(espaciosLibres+1);
    }
    else if(espaciosLibres==0)
        return 0;

    int mejorValor, valMinimax, modificador;
    char ficha;
    if(turnoCPU)
    {
        mejorValor=-100;
        modificador=1;
        turnoCPU=false;
        ficha=letraCPU;
    }
    else
    {
        mejorValor=100;
        modificador=-1;
        turnoCPU=true;
        ficha=letraJugador;
    }
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(tabla[i][j]==' ')
            {
                tabla[i][j]=ficha;
                espaciosLibres--;
                valMinimax=minimax(turnoCPU);
                if(valMinimax*modificador>mejorValor*modificador)
                    mejorValor=valMinimax;
                tabla[i][j]=' ';
                espaciosLibres++;
            }
        }
    }
    return mejorValor;
}
