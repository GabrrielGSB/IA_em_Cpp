#ifndef MYFUNCOES_H
#define MYFUNCOES_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

// Funções auxiliares
double gerarNumAleatorio();
string limparEspacos(const string& str);
void lerCSV(const string &arquivo, int numEntradas, 
            vector<vector<double>> &dadosEntrada, 
            vector<vector<double>> &saidaDesejada);
void salvarCSV(const string &nomeArquivo, const string &nomesColunas,
               const vector<vector<double>> &dados);
void salvarCSV(const string &nomeArquivo, const string &nomesColunas,
               const vector<double> &dados);

#endif // MYFUNCOES_H
