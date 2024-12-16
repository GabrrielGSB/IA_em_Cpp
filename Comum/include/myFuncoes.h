#ifndef MYFUNCOES_H
#define MYFUNCOES_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>

using namespace std;

// Funções auxiliares
float gerarNumAleatorio();
string limparEspacos(const string& str);
void lerCSV(const string &arquivo, int n, vector<vector<float>> &matriz, vector<float> &ultimaColuna);

#endif // MYFUNCOES_H
