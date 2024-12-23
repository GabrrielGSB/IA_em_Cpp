#include "../include/myFuncoes.h"
#include "../../Perceptron/include/Perceptron.h"

double gerarNumAleatorio()
{
	default_random_engine gerador(random_device{}());
    normal_distribution<double> distribuicao(0.0, 1);
    return distribuicao(gerador);
}

string limparEspacos(const string& str) 
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

void lerCSV(const string &arquivo, int numEntradas, 
            vector<vector<double>> &dadosEntrada, 
            vector<vector<double>> &saidaDesejada) 
{
    ifstream arquivoCSV(arquivo);

    if (!arquivoCSV.is_open()) 
    {
        std::cerr << "Erro ao abrir o arquivo: " << arquivo << std::endl;
        return;
    }

    string linha;

    // Ignora a primeira linha (cabeçalho)
    getline(arquivoCSV, linha);  // Pular a linha de cabeçalho

    while (getline(arquivoCSV, linha)) 
    {
        stringstream ss(linha);
        string valor;
        vector<double> linhaMatrizEntrada;
        vector<double> linhaSaidaDesejada;

        int colunaAtual = 0;

        while (getline(ss, valor, ',')) 
        {
            valor = limparEspacos(valor); // Remove espaços em torno do valor
            if (valor.empty()) continue; // Ignora valores vazios

            try 
            {
                double numero = std::stof(valor);

                if (colunaAtual < numEntradas) 
                {
                    // Adiciona às colunas de entrada
                    linhaMatrizEntrada.push_back(numero);
                } 
                else 
                {
                    // Adiciona às colunas de saída
                    linhaSaidaDesejada.push_back(numero);
                }
            } 
            catch (const invalid_argument &e) 
            {
                cerr << "Valor inválido encontrado: " << valor << endl;
                continue; // Pula valores inválidos
            }

            colunaAtual++;
        }

        // Adiciona os dados apenas se o tamanho das entradas estiver correto
        if ((int)linhaMatrizEntrada.size() == numEntradas) 
        {
            dadosEntrada.push_back(linhaMatrizEntrada);
            saidaDesejada.push_back(linhaSaidaDesejada);
        }
    }

    arquivoCSV.close();
}


void salvarCSV(const string &nomeArquivo, const string &nomesColunas,
               const vector<vector<double>> &dados)
{
    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        printf("Erro ao abrir o arquivo!!!");
        return;
    }

    arquivo << nomesColunas << "\n";

    // ----------- Escrever Dados no Arquivo ------------
    for (const auto &linha: dados)
    {
        for (size_t i = 0; i < linha.size(); i++)
        {
            arquivo << fixed << setprecision(10) << linha[i]; 

            if (i < (linha.size() - 1)) arquivo << ",";   
        }

        arquivo << "\n";
    }

    arquivo.close();
    // printf("Arquivo salvo com sucesso em: %s.csv", nomeArquivo);
    // --------------------------------------------------
}

void salvarCSV(const string &nomeArquivo, const string &nomesColunas,
               const vector<double> &dados)
{
    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        printf("Erro ao abrir o arquivo!!!");
        return;
    }

    arquivo << nomesColunas << "\n";

    // ----------- Escrever Dados no Arquivo ------------
    for (size_t i = 0; i < dados.size(); i++)
    {
        arquivo << fixed << setprecision(10) << dados[i] << "\n"; 
    }

    arquivo.close();
    // printf("Arquivo salvo com sucesso em: %s.csv", nomeArquivo);
    // --------------------------------------------------
}