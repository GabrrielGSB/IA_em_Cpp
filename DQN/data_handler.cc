#include "data_handler.hpp"
using namespace std;
  
data_handler::data_handler()
{
	// Essa linha aloca dinamicamente um novo vetor que será usado para armazenar ponteiros...
	// para objetos da classe "data". O ponteiro para esse vetor é então atribuído à variável "lista_de_dados".
	lista_de_dados 	     = new vector<data*>; // inicializa as variáveis definidas no arquivo "hpp".
	dados_de_teste       = new vector<data*>; // Aloca espaço na memória que pode ser expandido e contraído dinamicamente.
	dados_de_treinamento = new vector<data*>;
    dados_de_validacao   = new vector<data*>; 
}

data_handler::~data_handler(){};

void data_handler::ler_vec_de_rec(string path)
{
	uint32_t header[4]; // guarda o "magic number", "numero de imagens", "numero de linhas" e "numero de colunas" do arquivo a ser lido.
	unsigned char bytes[4];
	// path.c_str(): Se path for uma variável do tipo std::string (como é comum em C++), o método c_str() converte a "std::string"...
	// para um array de caracteres (const char*) que pode ser passado para funções da biblioteca C, como fopen.
	FILE *f = fopen(path.c_str(), "r"); // "r" arquivo aberto no modo de leitura, não pode ser modificado.
	
	if(f) // checa se o arquivo conseguiu ser aberto e lido.
	{
		for(int i = 0; i < 4; i++)
		{
			if(fread(bytes, sizeof(bytes), 1, f))
			{
				header[i] = converta_para_pequeno_indian(bytes);			
			}
		}

		printf("Termino da obtenção do cabeçalho do arquivo.\n");
		int tamanho_da_imagem = header[2]*header[3]; // produto do número de linhas pelo número de colunas em pixels.

		for(int i = 0; i < header[1]; i++) // iteração sobre o num de imagens
		{
			data *d = new data(); // alocando espaço na memória para um objeto da classe "data" e referindo um ponteiro para ele.
			uint8_t elemento[1];

			for(int j = 0; j < tamanho_da_imagem; j++) // itera sobre o tamanho da imagem para ler pixel por pixel
			{
				if(fread(elemento, sizeof(elemento), 1, f)) {d -> incluir_no_vec_de_rec(elemento[0]);} // lê um pixel no arquivo
				else 
				{
					printf("Erro na leitura do arquivo!!!\n");
					exit(1);
				}		
			}
		  	lista_de_dados -> push_back(d);
		}
		prinf("A leitura e salvamento dos %lu vetores de recurso foi um sucesso.\n", lista_de_dados -> size());
	} 
	else 
	{
		prinf("Arquivo não encontrado!!!\n");
		exit(1);
	}
}
void data_handler::ler_labels_de_recursos(string path)
{
	uint32_t header[2]; //Magic num / Num imgs
	unsigned char bytes[2];
	FILE *f = fopen(path.c_str(), "r");
	
	if(f)
	{
		for(int i = 0; i < 2; i++)
		{
			if(fread(bytes, sizeof(bytes), 1, f))
			{
				header[i] = conv_p_little_endian(bytes);			
			}
		}
		printf("Termino da obtenção da label do cabeçalho do arquivo.\n");
		for(int i = 0; i < header[1] ; i++)
		{	
			uint8_t elemento[1];
			if(fread(elemento, sizeof(elemento, 1, f)))
			{
				//A função at(i) é um método da classe std::vector que retorna o elemento na posição i do vetor
				//Como "vetor_de_dados" é um vetor de ponteiros at(i) vai pegar um ponteiro e aplicar a função "definir_label"
				vetor_de_dados -> at(i) -> definir_label(elemento[0]);
			}	
			else 
			{
				printf("Erro na leitura do arquivo!!!\n");
				exit(1);
			}		
		}
		prinf("A leitura e salvamento da label foi um sucesso.\n");
	} 
	else 
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
		//Gera um índice aleatório entre 0 e o tamanho total de vetor_de_dados menos um. 
		//Isso garante que o índice seja válido para acessar um elemento no vetor de dados.
		int indice_aleatorio = rand() % vetor_de_dados->size();

		if(indices_usados.find(indice_aleatorio) == indices_usados.end()) // Aqui o .end() não aponta para elemento válido, 
		{         														  // apenas indica fim do vetor
	        // Insere  o elemento indicado por "indice_aleatorio" do "vetor_de_dados" em "dados_de_treinamento"
			dados_de_treinamento -> push_back(vetor_de_dados -> at(indice_aleatorio));
			indices_usados.insert(indice_aleatorio);
			count++;	
		}
	}

	// Dados de Teste
	int count = 0;
	while(count < tamanho_do_teste)
	{
		int indice_aleatorio = rand() % vetor_de_dados->size();
		if(indices_usados.find(indice_aleatorio) == indices_usados.end())
		{
			dados_de_teste -> push_back(vetor_de_dados -> at(indice_aleatorio));
			indices_usados.insert(indice_aleatorio);
			count++;
		}
	}

	// Dados de Validação
	int count = 0;
	while(count < tamanho_da_validacao)
	{
		int indice_aleatorio = rand() % vetor_de_dados	->size();
		if(indices_usados.find(indice_aleatorio) == indices_usados.end())
		{
			dados_de_validacao -> push_back(vetor_de_dados -> at(indice_aleatorio));
			indices_usados.insert(indice_aleatorio);
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
			class_map[lista_de_dados -> at(i) -> obter_label()] = count;
			lista_de_dados -> at(i) -> definir_label_numerada(count);
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
	dh->ler_vetor_de_recursos("./NOME_DO_ARQUIVO");
	dh->ler_labels_de_recursos("./NOME_DO_ARQUIVO");
	dh->dividir_dados();
	dh->contar_classes();
}
