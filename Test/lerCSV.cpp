#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<string>> ler_csv(string nome_arquivo) {
    vector<vector<string>> dados;
    ifstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << nome_arquivo << endl;
        return dados;
    }

    string linha;
    while (getline(arquivo, linha)) {
        vector<string> registro;
        stringstream ss(linha);
        string celula;

        while (getline(ss, celula, ',')) {
            registro.push_back(celula);
        }

        dados.push_back(registro);
    }

    arquivo.close();
    return dados;
}

int main() {
    string nome_arquivo = "MLP/Dados/dados_treinamento.csv";
    vector<vector<string>> dados = ler_csv(nome_arquivo);

    // Imprimindo os dados (exemplo)
    for (const auto& linha : dados) {
        for (const auto& celula : linha) {
            cout << celula << " ";
        }
        cout << endl;
    }

    return 0;
}