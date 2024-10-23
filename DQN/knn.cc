    #include "knn.hpp"
    #include <cmath>
    #include <limits>
    #include <map>
    #include "stdint.h"
    #include "data_handler.hpp"
    
    knn::knn(int val) { k = val; }
    knn::knn(){}
    knn::~knn(){}

    void knn::achar_Kproximos(data *ponto_ref)
    {
        vizinhos         = new vector<data*>;
        double min       = numeric_limits<double>::max();
        double min_velho = min;
        int index        = 0;

        for(int i = 0; i < k; i++)
        {
            if(i==0)
            {
                for(int j = 0; j < dados_de_treinamento->size(); j++)
                {
                    double dist = calcular_dist(ponto_ref, dados_de_treinamento->at(j));
                    dados_de_treinamento->at(j)->definir_dist(dist);

                    if(dist < min)
                    {
                        
                        min   = dist;
                        index = j;
                    }
                }
                vizinhos->push_back(dados_de_treinamento->at(index));
                min_velho = min;
                min       = numeric_limits<double>::max();
            }
            else
            {
                for(int j = 0; j < dados_de_treinamento->size(); j++)
                    {
                        double dist = calcular_dist(ponto_ref, dados_de_treinamento->at(j));
                        dados_de_treinamento->at(j)->definir_dist(dist);

                        if(dist > min_velho && dist < min)
                        {
                            min   = dist;
                            index = j;
                        }
                    }
                    vizinhos->push_back(dados_de_treinamento->at(index));
                    min_velho = min;
                    min       = numeric_limits<double>::max();
            }
        }
        
    }

    void knn::def_dados_de_treinamento(vector<data*> * vetor) { dados_de_treinamento = vetor; }
    void knn::def_dados_de_teste(vector<data *> * vetor)      { dados_de_teste       = vetor; }
    void knn::def_dados_de_validacao(vector<data *> * vetor)  { dados_de_validacao   = vetor; }
    void knn::def_k(int val)                                  { k                    = val;   }

    int knn::prever()
    {
        //O objetivo é contar quantas vezes cada classe aparece entre os vizinhos e retornar a classe que aparece com maior frequência.
        map<uint8_t, int> freq_classe;

        for(int i =0; i < vizinhos->size(); i++)
        {
            if(freq_classe.find(vizinhos->at(i)->obter_label()) == freq_classe.end()) { freq_classe[vizinhos->at(i)->obter_label()] = 1; }
            else                                                                      { freq_classe[vizinhos->at(i)->obter_label()]++; }
        }
        int melhor = 0; // A variável que irá armazenar a classe mais frequente.
        int max    = 0; // A variável que irá armazenar o valor máximo de frequência. 
        // vc == valor-chave.
        // vc vai assumir todos os valores de chave-valor do map.
        for(auto vc : freq_classe) // A sintaxe for(declaracao : coleção) é usada para iterar sobre todos os elementos de uma coleção de forma simples.
        {
            //O loop percorre todas as classes e suas frequências no mapa "freq_classe".
            if(vc.second > max)
            {
                max = vc.second;   //vc.second é a frequência (valor).
                melhor = vc.first; //vc.first é a classe (chave).
            }
        }
        delete vizinhos;
        return melhor;
    }

    double knn::calcular_dist(data* ponto_ref, data* entrada)
    {
        double dist = 0.0;
        if (ponto_ref->obter_tamanho_do_vec_de_rec() != entrada->obter_tamanho_do_vec_de_rec())
        {
            printf("Tamanho do vetor não bate!!!");
            exit(1);
        }

    #ifndef EUCLID
        for(unsigned i = 0; i < ponto_ref -> obter_tamanho_do_vec_de_rec(); i++)
        {
            dist = pow(ponto_ref->obter_vec_de_rec()->at(i) - entrada->obter_vec_de_rec()->at(i), 2);
            dist = sqrt(dist);
        }    


    #elif defined MANHATTAN

    #endif
    return dist;
    }

    double knn::validar_performance()
    {
        double performance_atual = 0; //Inicializada como 0, esta variável armazenará a performance final (acurácia) em porcentagem.
        int count                = 0; //Conta o número de predições corretas.
        int data_index           = 0; //Mantém o índice do dado de validação atual, usado para calcular a performance até o momento.

        //Para cada ponto de dados (ponto_ref) no vetor de validação (dados_de_validacao), o algoritmo realiza os seguintes passos
        for(data *ponto_ref : *dados_de_validacao)
        {
            achar_Kproximos(ponto_ref);
            int predicao = prever();

            if(predicao == ponto_ref->obter_label()) { count++; }
            data_index++; 

            printf("Performance da Atual = %.3f %%\n", (((double)count*100.0)/((double)data_index)));
        }
        performance_atual = (((double)count*100.0)/((double)dados_de_validacao->size())); 
        printf("Performance de Validação para K = %d: = %.3f %%\n", k, performance_atual);
        return performance_atual;
    }

    double knn::testar_performance()
    {
        double performance_atual = 0;
        int count                = 0;

        for(data *ponto_ref : *dados_de_validacao)
        {
            achar_Kproximos(ponto_ref);
            int predicao = prever();

            if(predicao == ponto_ref->obter_label()) { count++; }
        }
        performance_atual = (((double)count*100.0)/((double)dados_de_teste->size())); 
        printf("Performance testada %.3f %%\n", performance_atual);
    }