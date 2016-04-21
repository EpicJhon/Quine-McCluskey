#include "includes.h"

using namespace std;

/**
 * Main
 * 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv) {

    QuineMcCluskey q;
    int nun_vars, number;
    bool verbose;

    uint64 timeStart, timeEnd;

    cout << "¿Mostrar proceso? (1 o 0): " << endl;
    cin >> verbose;
    q.setVerbose(verbose);

    cout << "Numero de variables: ";
    cin >> nun_vars;
    q.setNunVars(nun_vars);

    while (cin >> number)
        q.addMinterm(number);

    cout << "Inicio del proceso..." << endl;
    timeStart = GetTimeMs64();
    q.minimize();
    timeEnd = GetTimeMs64();
    cout << "Fin del proceso! Tiempo de calculo en milisegundos: " << (timeEnd - timeStart) << endl;
    cout << "Formula minima: " << endl;
    q.printSOP();

    return 0;
}