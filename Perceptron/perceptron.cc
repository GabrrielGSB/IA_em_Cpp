#include "perceptron.hpp"

vector<vector<double>> entradas   = {{0,0},{0,1},{1,0},{1,1}}; 
vector<double> saidasDesejadas = { 0.0 , 0.0 , 0.0 , 1.0 };
vector<double> erros           = { 0.0 , 0.0 , 0.0 , 0.0};
vector<double> pesos           = { -1   , 0   , 0};

double taxaAprendizado = 0.1;

Perceptron p(entradas, saidasDesejadas, pesos, erros, taxaAprendizado);

int main()
{
    for(int i = 0; i < 20; i++)
    {
        printf("\n");
        p.transferencia();
        for(int i = 0; i < p.saidasObtidas.size(); i++) printf("%d ", p.saidasObtidas[i]);
        printf("\n");

        p.calcularErro();
        for(int i = 0; i < p.erros.size(); i++) printf("%.2f ",p.erros[i]);
        printf("\n");
        printf("\n");

        for(double w : p.pesos) 
        {
            printf("%.2f ", w);
            printf("\n");
        }
    }
    

    return 0;
}