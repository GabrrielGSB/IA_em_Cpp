#include "../include/myFuncoes.h"
#include "../../Perceptron/include/Perceptron.h"

float gerarNumAleatorio()
{
	default_random_engine gerador(random_device{}());
    normal_distribution<float> distribuicao(0.0, 1);
    return distribuicao(gerador);
}

string limparEspacos(const string& str) 
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

void lerCSV(const string &arquivo, int numEntradas, vector<vector<float>> &dadosEntrada, vector<float> &saidaDesejada) 
{
    ifstream arquivoCSV(arquivo);

    if (!arquivoCSV.is_open()) 
    {
        cerr << "Erro ao abrir o arquivo: " << arquivo << endl;
        return;
    }

    string linha;

    // Ignora a primeira linha (cabeçalho)
    getline(arquivoCSV, linha);  // Pular a linha de cabeçalho

    while (getline(arquivoCSV, linha)) 
    {
        stringstream ss(linha);
        string valor;
        vector<float> linhaMatriz;
        float ultimoValor = 0.0;

        int colunaAtual = 0;

        while (getline(ss, valor, ',')) 
        {
            valor = limparEspacos(valor); // Remove espaços em torno do valor
            if (valor.empty()) continue; // Ignora valores vazios

            try 
            {
                float numero = stof(valor);

                if (colunaAtual < numEntradas)       linhaMatriz.push_back(numero); // Adiciona às primeiras colunas
                else if (colunaAtual == numEntradas) ultimoValor = numero;          // Última coluna
                
            } catch (const invalid_argument& e) {
                cerr << "Valor inválido encontrado: " << valor << endl;
                continue; // Pula valores inválidos
            }

            colunaAtual++;
        }

        if ((int)linhaMatriz.size() == numEntradas) 
        {
            dadosEntrada.push_back(linhaMatriz);   // Adiciona a linha ao vector<vector<float>>
            saidaDesejada.push_back(ultimoValor); // Adiciona à última coluna
        }
    }

    arquivoCSV.close();
}

