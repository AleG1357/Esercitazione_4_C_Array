#include <iostream>
#include <iomanip>   // per std::fixed e std::setprecision
#include <fstream>
#include <sstream>
#include "src/Utils.hpp"

using namespace std;

int main()
{
    double S = 0.0;      // somma totale investita
    size_t n = 0;        // numero di asset
    double* w = nullptr; // array delle frazioni
    double* r = nullptr; // array dei singoli tassi di rendimento

    // Import dei dati dal file data.txt 
    if (!ImportData("data.txt", S, n, w, r))
    {
        cerr << "Something goes wrong with import" << endl;
        return -1;
    }
    else
    {
        cout << "Import successful: n= " << n << endl;
    }

    // Calcolo del rate di rendimento complessivo
    double portfolioRate = ComputePortfolioReturn(n, w, r);
	
    // Calcolo del valore finale V
    double V = S * (1.0 + portfolioRate);


    // Stampo a schermo (con i trailing zeros)
    cout << fixed << setprecision(2);
    cout << "S = " << S << ", n = " << n << endl;

    // Stampo w e r 
    cout << "w = [ ";
    for (size_t i = 0; i < n; i++)
        cout << w[i] << (i < n-1 ? " " : "");
    cout << " ]" << endl;

    cout << "r = [ ";
    for (size_t i = 0; i < n; i++)
        cout << r[i] << (i < n-1 ? " " : "");
    cout << " ]" << endl;

    // Tasso di rendimento del portfolio ( 4 cifre)
    cout << setprecision(4);
    cout << "Rate of return of the portfolio: " << portfolioRate << endl;

    // Valore finale a 2 cifre
    cout << fixed << setprecision(2);
    cout << "V: " << V << endl;


    // Esportiamo tutto su file "result.txt"
	
	string outputFileName = "./result.txt";
    if (!ExportResult(outputFileName, S, n, w, r, portfolioRate))
    //if(!ExportResult("result.txt", S, n, w, r, portfolioRate)) //potrei fare direttamente così , ma teniamo il nome come variabile
    {
        cerr << "Something goes wrong with export" << endl;
        return -1;
    }
    else
    {
        cout << "Export successful" << endl;
    }

    // Pulizia della memoria dinamica
    delete[] w;
    delete[] r;

    return 0;
}
