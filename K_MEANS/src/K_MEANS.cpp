#include "../include/K_MEANS.h"

kMeans::kMeans(int numEntradas, int numAgrupamentos, vector<vector<double>> &dadosEntrada) : 
               numEntradas(numEntradas),
               numAgrupamentos(numAgrupamentos),
               dadosEntrada(dadosEntrada)
{
    this->aglomeradosFormados = false;    
    this->agrupamentos.resize(numAgrupamentos);
    this->variancias.resize(numAgrupamentos);
}

void kMeans::atualizarCentros()
{
    if (this->centros.empty())
    {
        for (int i = 0; i < numAgrupamentos; i++) centros.push_back(this->dadosEntrada[i]);
    }
    else
    {
        vector<double> somaPontosEntrada;
        vector<double> novoCentro(this->numEntradas);

        int countAgrupamento = 0;
        for (auto &agrupamento : this->agrupamentos)
        {
            somaPontosEntrada.clear();
            somaPontosEntrada.resize(this->numEntradas);

            for (auto &ponto : agrupamento)
            {
                for (int i = 0; i < int(ponto.size()); i++) somaPontosEntrada[i] += ponto[i];
            }

            for (int i = 0; i < int(agrupamento[0].size()); i++) novoCentro[i] = somaPontosEntrada[i] / this->numAgrupamentos;
            
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
    int indiceAgrupamento = 0;
    for (auto &agrupamento : this->agrupamentos)
    {
        
        for (auto &ponto : agrupamento)
        {
            vector<double> diferenca(ponto.size());

            transform(ponto.begin(), ponto.end(), this->centros[indiceAgrupamento].begin(), diferenca.begin(), []
                     (double Xi, double Wi) { return Xi - Wi; });

            this->variancias[indiceAgrupamento] += inner_product(diferenca.begin(), diferenca.end(), 
                                                                 diferenca.begin(), 0.0);
        }
        indiceAgrupamento++;
    }
}

void kMeans::mostrarVariancias()
{
    int indiceVariancia = 0;
    for (auto &variancia : this->variancias)
    { 
        printf("Variância do Neurônio Oculto %d: %.3f\n", indiceVariancia+1, variancia);
        indiceVariancia++;
    }
}

void kMeans::mostrarCentrosObtidos()
{
    printf("\n");

    int indiceCentro = 0;
    for (auto &centro : this->centros)
    {
        printf("A centroide %d está em ", indiceCentro+1);
        
        for (auto &valor : centro)
        {
            if (valor == centro.back()) printf("%.2f)", valor);
            else                        printf("(%.2f, ", valor);
        } 
        printf("\n");
        indiceCentro++;
    }
}

