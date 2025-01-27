#include "../include/K_MEANS.h"

kMeans::kMeans(int numAgrupamentos) : numAgrupamentos(numAgrupamentos){}

void kMeans::atualizarCentros(vector<vector<double>> &dadosEntrada)
{
    if (this->centros.empty())
    {
        for (int i = 0; i < numAgrupamentos; i++) centros.push_back(dadosEntrada[i]);
    }
}

void kMeans::preencherAgrupamentos(vector<vector<double>> &dadosEntrada)
{
    for (vector<double> &dado : dadosEntrada)
    {
        int indiceCentro = 0;
        vector<double> distancias(this->numAgrupamentos);

        for (vector<double> &centro : this->centros)
        {
            vector<double> diferenca(dado.size());
            transform(dado.begin(), dado.end(), centro.begin(), diferenca.begin(), []
                     (double Xi, double Wi) { return Xi - Wi; });

            distancias[indiceCentro] = inner_product(diferenca.begin(), diferenca.end(), 
                                                     diferenca.begin(), 0.0);
            
            indiceCentro++;
        }

        auto menordistancia      = min_element(distancias.begin(), distancias.end());
        int indiceMenorDistancia = distance(distancias.begin(), menordistancia);

        this->agrupamentos[indiceMenorDistancia].push_back(dado);
    }
}