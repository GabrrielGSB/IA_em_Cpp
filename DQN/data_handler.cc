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
		printf("Termino da obtenção do cabeçalho do arquivo.\n");
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
void data_handler::ler_labels_de_recursos(string path);
void data_handler::dividir_dados();
void data_handler::contar_classes();

uint32_t data_handler::converta_para_pequeno_endian(const unsigned char* bytes);
  
vector<data *> * data_handler::obter_dados_de_treinamento();	
vector<data *> * data_handler::obter_dados_de_teste();
vector<data *> * data_handler::obter_dados_de_validacao();
