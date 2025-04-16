#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> // per std::setprecision

using namespace std;



bool ImportData(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r)
{
    

	// Apro il File
    ifstream file;
    file.open(inputFilePath);
	
    if (file.fail())
    {
        cerr << "file open failed" << endl;
        return false;
    }

    string line;

    // 1) Leggo S
    while (!file.eof())
    {
        getline(file, line);
        if (!line.empty() && line[0] != '#')
            break;
    }

    {
        size_t pos = line.find(';');
        if (pos == string::npos)
        {
            cerr << "Wrong format for S" << endl;
            return false;
        }

        string value = line.substr(pos + 1);
        istringstream convertS;
        convertS.str(value);
        convertS >> S;
    }

    // 2) Leggo n
    while (!file.eof())
    {
        getline(file, line);
        if (!line.empty() && line[0] != '#')
            break;
    }

    {
        size_t pos = line.find(';');
        if (pos == string::npos)
        {
            cerr << "Wrong format for n" << endl;
            return false;
        }

        string value = line.substr(pos + 1);
        istringstream convertN;
        convertN.str(value);
        convertN >> n;
    }

    // 3) Salto l'intestazione w;r
    while (!file.eof())
    {
        getline(file, line);
        if (!line.empty() && line[0] != '#')
            break;
    }

    // 4) Alloco gli array
    w = new double[n];
    r = new double[n];

    // 5) Leggo n righe w_i;r_i
    for (size_t i = 0; i < n; i++)
    {
        while (!file.eof())
        {
            getline(file, line);
            if (!line.empty() && line[0] != '#')
                break;
        }

        size_t pos = line.find(';');
        if (pos == string::npos)
        {
            cerr << "Wrong format for w;r" << endl;
            delete[] w;          //Pulizia memoria dinamica
            delete[] r;
            return false;
        }

        string wStr = line.substr(0, pos);
        string rStr = line.substr(pos + 1);

        istringstream convertW;
        convertW.str(wStr);
        convertW >> w[i];

        istringstream convertR;
        convertR.str(rStr);
        convertR >> r[i];
    }

    file.close();
    return true;
}




double ComputePortfolioReturn(const size_t& n,
                              const double* const& w,
                              const double* const& r)
{
    double rate = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        rate += w[i] * r[i];
    }
    return rate;
}



bool ExportResult(const string& outputFilePath,
                  const double& S,
                  const size_t& n,
                  const double* const& w,
                  const double* const& r,
                  const double& portfolioRate)
{
	//Apro il file
    ofstream file;
	file.open(outputFilePath);
	
    if (file.fail())
    {
        cerr << "file open failed: " << outputFilePath << endl;
        return false;
    }

    // FOrmatto come da consgena
    file << fixed << setprecision(2);
    file << "S = " << S << ", n = " << n << "\n";

    file << "w = [ ";        
    for (size_t i = 0; i < n; i++)
        file << w[i] << (i < n-1 ? " " : "");   // Aggiungo uno spazio fino all'ultimo valore
    file << " ]\n";

    file << "r = [ ";
    for (size_t i = 0; i < n; i++)
        file << r[i] << (i < n-1 ? " " : "");
    file << " ]\n";

    // Rate of return con 4 cifre di precisione
    file << setprecision(4);
    file << "Rate of return of the portfolio: " << portfolioRate << "\n";

    double V = S * (1.0 + portfolioRate);
    file << fixed << setprecision(2);
    file << "V: " << V << "\n";

    file.close();
    return true;
}
