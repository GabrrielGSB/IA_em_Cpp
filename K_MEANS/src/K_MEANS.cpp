#include "../include/K_MEANS.h"

kMeans::kMeans(int numAgrupamentos, vector<vector<double>> &dadosEntrada) : 
               numAgrupamentos(numAgrupamentos),
               dadosEntrada(dadosEntrada)
{
    this->aglomeradosFormados = false;    
    this->agrupamentos.resize(numAgrupamentos);
}

void kMeans::atualizarCentros()
{
    if (this->centros.empty())
    {
        for (int i = 0; i < numAgrupamentos; i++) centros.push_back(this->dadosEntrada[i]);
    }
    else
    {
        int countAgrupamento = 0;
        for (auto &agrupamento : this->agrupamentos)
        {
            double sumX = 0, sumY = 0;
            for (auto &ponto : agrupamento)
            {
                sumX += ponto[0];
                sumY += ponto[1];
            }
            vector<double> novoCentro = {sumX/this->numAgrupamentos, sumY/this->numAgrupamentos};
            this->centros[countAgrupamento] = novoCentro;

            countAgrupamento++;
        }
    }
}

void kMeans::preencherAgrupamentos()
{
    vector<vector<vector<double>>> agrupamentosOLD = this->agrupamentos;
    this->agrupamentos.clear();
    this->agrupamentos.resize(this->numAgrupamentos);
    
    for (vector<double> &dado : this->dadosEntrada)
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
    if (this->agrupamentos == agrupamentosOLD) this->aglomeradosFormados = true;
}

void kMeans::aplicarAlgoritmo()
{
    while (this->aglomeradosFormados == false)
    {
        atualizarCentros();
        preencherAgrupamentos();
    }
    calcularVariancia();
}

void kMeans::calcularVariancia()
{
    vector<double> distancias(this->numAgrupamentos);
    
    for (vector<double> &dado : this->dadosEntrada)
    {
        int indiceCentro = 0;
        for (vector<double> &centro : this->centros)
        {
            vector<double> diferenca(dado.size());

            transform(dado.begin(), dado.end(), centro.begin(), diferenca.begin(), []
                     (double Xi, double Wi) { return Xi - Wi; });

            distancias[indiceCentro] = inner_product(diferenca.begin(), diferenca.end(), 
                                                     diferenca.begin(), 0.0);
            
            indiceCentro++;
        }
    }
    for (auto i : distancias) printf("%.3f\n", i);
}


