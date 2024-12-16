#include "../include/myFuncoes.h"
#include "../../Perceptron/include/Perceptron.h"

float gerarNumAleatorio()
{
	default_random_engine gerador;
    normal_distribution<float> distribuicao(0.0, 1.0);
    return distribuicao(gerador);

    // float aleatorio = (float)rand() / RAND_MAX;
    // return min + aleatorio * (max - min);
}

string limparEspacos(const string& str) 
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

void lerCSV(const string &arquivo, int n, vector<vector<float>> &matriz, vector<float> &ultimaColuna) 
{
    ifstream arquivoCSV(arquivo);

    if (!arquivoCSV.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << arquivo << endl;
        return;
    }

    string linha;

    // Ignora a primeira linha (cabeçalho)
    getline(arquivoCSV, linha);  // Pular a linha de cabeçalho

    while (getline(arquivoCSV, linha)) {
        stringstream ss(linha);
        string valor;
        vector<float> linhaMatriz;
        float ultimoValor = 0.0;

        int colunaAtual = 0;

        while (getline(ss, valor, ',')) {
            valor = limparEspacos(valor); // Remove espaços em torno do valor
            if (valor.empty()) continue; // Ignora valores vazios

            try {
                float numero = stof(valor);

                if (colunaAtual < n) {
                    linhaMatriz.push_back(numero); // Adiciona às primeiras colunas
                } else if (colunaAtual == n) {
                    ultimoValor = numero; // Última coluna
                }
            } catch (const invalid_argument& e) {
                cerr << "Valor inválido encontrado: " << valor << endl;
                continue; // Pula valores inválidos
            }

            colunaAtual++;
        }

        if (linhaMatriz.size() == n) {
            matriz.push_back(linhaMatriz);   // Adiciona a linha ao vector<vector<float>>
            ultimaColuna.push_back(ultimoValor); // Adiciona à última coluna
        }
    }

    arquivoCSV.close();
}

