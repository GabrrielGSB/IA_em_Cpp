#include "data_handler.hpp"
using namespace std;
  
data_handler::data_handler()
{
	lista_de_dados 			 = new vector<data *>;
	dados_de_teste       = new vector<data *>;
	dados_de_treinamento = new vector<data *>;
  dados_de_validacao   = new vector<data *>; 
};

data_handler::~data_handler()
{

};

void data_handler::ler_vetor_de_recursos(string path)
{
	uint8_t header[4];
	unsigned char bytes[4];
	FILE *f = fopen(path.c_str(), "r");
	
	if(f)
	{
		for(int i=0;i<4;i++)
		{
			if(fread(bytes, sizeof(bytes), 1, f))
			{
				header[i] = converta_para_pequeno_indian(bytes);			
			};
		};
		printf("Termino da obtenção do cabeçalho do arquivo de entrada.\n");
		int tamanho_da_imagem = header[2]*header[3];
		for(int i=0;i<header[1];i++)
		{
			data *d = new data();
			uint8_t elemento[1];
			for(int j=0;j<tamanho_da_imagem;j++)
			{
				if(fread(elemento, sizeof(elemento, 1, f)))
				{
					d->incluir_no_vetor_de_recursos(elemento[0]);
				}	else 
				{
					printf("Erro na leitura do arquivo!!!\n");
					exit(1);
				}		
			}
		  lista_de_dados->push_back(d);
		}
		prinf("A leitura e salvamento dos %lu vetores de recurso foi um sucesso.\n", lista_de_dados->size());
	} else 
	{
		prinf("Arquivo não encontrado!!!\n");
		exit(1);
	}
}
void data_handler::ler_labels_de_recursos(string path)
{
uint8_t header[2];
	unsigned char bytes[2];
	FILE *f = fopen(path.c_str(), "r");
	
	if(f)
	{
		for(int i=0;i<2;i++)
		{
			if(fread(bytes, sizeof(bytes), 1, f))
			{
				header[i] = converta_para_pequeno_indian(bytes);			
			}
		}
		printf("Termino da obtenção da label do cabeçalho do arquivo.\n");
		for(int i=0;i<header[1];i++)
		{	
			uint8_t elemento[1];
			if(fread(elemento, sizeof(elemento, 1, f)))
			{
				vetor_de_dados->at(i)->definir_label(elemento[0]);
			}	else 
			{
				printf("Erro na leitura do arquivo!!!\n");
				exit(1);
			}		
		}
		prinf("A leitura e salvamento da label foi um sucesso.\n");
	} else 
	{
		prinf("Arquivo não encontrado!!!\n");
		exit(1);
	}
}

void data_handler::dividir_dados()
{
	unordered_set<int> indices_usados;
	int tamanho_do_treinamento = vetor_de_dados->size() * PORCENTAGEM_DE_TREINAMENTO
	int tamanho_do_teste       = vetor_de_dados->size() * PORCENTAGEM_DO_TESTE
	int tamanho_da_validacao   = vetor_de_dados->size() * PORCENTAGEM_DE_VALIDACAO

	// Dados de Treinamento

	int count = 0;
	while(count < tamanho_do_treinamento)
	{
		int rand_indice = rand() % vetor_de_dados	->size();
		if(indices_usados.find(rand_indice) == indices_usados.end())
		{
			dados_de_treinamento->push_back(vetor_de_dados->at(rand_indice));
			indices_usados.insert(rand_indice);
			count++;	
		}
	}

	// Dados de Teste

	int count = 0;
	while(count < tamanho_do_teste)
	{
		int rand_indice = rand() % vetor_de_dados	->size();
		if(indices_usados.find(rand_indice) == indices_usados.end())
		{
			dados_de_teste->push_back(vetor_de_dados->at(rand_indice));
			indices_usados.insert(rand_indice);
			count++;
		}
	}

	// Dados de Validação

	int count = 0;
	while(count < tamanho_da_validacao)
	{
		int rand_indice = rand() % vetor_de_dados	->size();
		if(indices_usados.find(rand_indice) == indices_usados.end())
		{
			dados_de_validacao->push_back(vetor_de_dados->at(rand_indice));
			indices_usados.insert(rand_indice);
			count++;
		}
	}

	printf("Tamanho dos dados de treinamento %lu.\n", dados_de_treinamento);
	printf("Tamanho dos dados de teste %lu.\n",       dados_de_teste);
	printf("Tamanho dos dados de validação %lu.\n",   dados_de_validação);
}
void data_handler::contar_classes()
{
	int count = 0;
	for (unsigned i = 0; i < lista_de_dados->size(); i++)
	{
		if(class_map.find(lista_de_dados->(i)->obter_label()) == class_map.end())
		{
			class_map[lista_de_dados->at(i)->obter_label()] = count;
			lista_de_dados->at(i)->definir_label_numerada(count);
			count++;
		}
	}
	num_classes = count;
	printf("Foram obtidicas %d classes únicas.\n", num_classes);
}

uint32_t data_handler::converta_para_pequeno_endian(const unsigned char* bytes)
{
	return(uint32_t) ((byte[0] << 24) |
										(byte[1] << 16) |
										(byte[2] << 8 ) |
										(byte[3]));
}
  
vector<data *> * data_handler::obter_dados_de_treinamento()
{
	return dados_de_treinamento;
}

vector<data *> * data_handler::obter_dados_de_teste()
{
	return dados_de_teste;
}
vector<data *> * data_handler::obter_dados_de_validacao()
{
	return dados_de_validacao;
}

int main()
{
	data_handler *dh = new data_handler();
	dh->ler_vetor_de_recursos("../NOME_DO_ARQUIVO");
	dh->ler_labels_de_recursos("../NOME_DO_ARQUIVO");
	dh->dividir_dados();
	dh->contar_classes();
}
