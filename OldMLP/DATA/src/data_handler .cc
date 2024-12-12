#include "data_handler.hpp"
#include <algorithm>
#include <random>

using namespace std;


  
data_handler::data_handler()
{
	// Essa linha aloca dinamicamente um novo vetor que será usado para armazenar ponteiros...
	// para objetos da classe "data". O ponteiro para esse vetor é então atribuído à variável "lista_de_dados".
	vetor_de_dados 	     = new vector<data*>; // inicializa as variáveis definidas no arquivo "hpp".
	dados_de_teste       = new vector<data*>; // Aloca espaço na memória que pode ser expandido e contraído dinamicamente.
	dados_de_treinamento = new vector<data*>;
    dados_de_validacao   = new vector<data*>; 
}

data_handler::~data_handler(){};

// Guarda as imagens das letras (pixels) em "vetor de dados"
void data_handler::guardarLetra(string path)
{
	uint32_t      header[4]; // guarda o "magic number", "numero de imagens", "numero de linhas" e "numero de colunas"...
	  						 // do arquivo a ser lido.
	unsigned char bytes[4];  // está assim pq cada um dos elementos de "header" tem 32 bits/4 bytes. Vai ler um elemento de "header"

	// path.c_str(): Se path for uma variável do tipo std::string (como é comum em C++), o método c_str() converte a "std::string"...
	// para um array de caracteres (const char*) que pode ser passado para funções da biblioteca C, como fopen.
	FILE *f = fopen(path.c_str(), "r"); // "r" arquivo aberto no modo de leitura, não pode ser modificado.
	
	if(f) // checa se o arquivo conseguiu ser aberto e lido.
	{
		// "if(fread(bytes, sizeof(bytes), 1, f))" lê "1" bloco de dados de "f" de tamanho "sizeof(bytes)" e guarda em "bytes"
		// Esse loop lê cada linha do cabeçalho e inclui ela na variável "header" onde cada elemento equivale a uma linha
		for (int i = 0; i < 4; i++) { if (fread(bytes, sizeof(bytes), 1, f)) { header[i] = conv_p_little_endian(bytes); } }
		printf("Termino da obtenção do cabeçalho do arquivo.\n");

		int tamanho_da_imagem = header[2]*header[3]; // Produto do número de linhas pelo número de colunas em pixels...
										             // de uma imagem.
		// iteração sobre as letras do arquivo, a fim de preencher a variável "vetor de dados". 
		for (int i = 0; i < header[1]; i++) 
		{
			data *img = new data(); // Alocando espaço na memória para um objeto da classe "data" e referindo um ponteiro para ele.
			uint8_t pixel[1];       // Variável para guardar um pixel de forma temporária.

			for(int j = 0; j < tamanho_da_imagem; j++) // itera sobre o tamanho da imagem para ler pixel por pixel
			{
				// lê um pixel no arquivo e inclui ele no vetor de recurso
				if (fread(pixel, sizeof(pixel), 1, f)) { img -> incluir_no_vec_de_pixels(pixel[0]); } 												
				else 
				{
					printf("Erro na leitura do arquivo!!!\n");
					exit(1); // Encerra o programa prematuramente para indicar erro.
				}		
			}
			// "img" representa um objeto da classe Letra, logo uma letra do alfabeto. 
		  	vetor_de_dados -> push_back(img); // Guarda os dados (Letras) no "vetor de dados"
		}
		printf("A leitura e salvamento das %u letras foi um sucesso.\n", vetor_de_dados -> size());
	} 
	else 
	{
		printf("Arquivo não encontrado!!!\n");
		exit(1); // Encerra o programa prematuramente para indicar erro.
	}
}

void data_handler::lerLabels(string path)
{
	uint32_t      header[2]; // Magic num / Num imgs
	unsigned char bytes[4];
	FILE *f = fopen(path.c_str(), "r"); // "r" arquivo aberto no modo de leitura, não pode ser modificado.
	
	if (f) // Se o arquivo conseguiu ser lido.
	{
		for (int i = 0; i < 2; i++) { if (fread(bytes, sizeof(bytes), 1, f)) { header[i] = conv_p_little_endian(bytes); } }
		printf("Termino da obtenção do cabeçalho do arquivo.\n");

		for (int i = 0; i < header[1] ; i++) // Itera sobre o número de labels.
		{	
			uint8_t label[1]; // Uma label tem 1 byte.

			if (fread(label, sizeof(label), 1, f)) // Obtem uma label por vez, do conjunto, por iteração.
			{
				//A função at(i) é um método da classe std::vector que retorna a label na posição i do vetor
				//Como "vetor_de_dados" é um vetor de ponteiros at(i) vai pegar um ponteiro e aplicar a função "definir_label"
				vetor_de_dados -> at(i) -> definir_label(label[0]);
			}	
			else 
			{
				printf("Erro na leitura do arquivo!!!\n");
				exit(1);
			}		
		}
		printf("A leitura e salvamento da label foi um sucesso.\n");
	} 
	else 
	{
		printf("Arquivo não encontrado!!!\n");
		exit(1);
	}
}

map<uint8_t, int> data_handler::getClassMap() {return classFromInt;}

void data_handler::dividirDados()
{
	unordered_set<int> indices_usados;
	int tamanho_do_treinamento = vetor_de_dados->size() * PERC_DE_TREINAMENTO;
	int tamanho_do_teste       = vetor_de_dados->size() * PERC_DO_TESTE;
	int tamanho_da_validacao   = vetor_de_dados->size() * PERC_DE_VALIDACAO;

	// Dados de Treinamento
	int count = 0;
	while(count < tamanho_do_treinamento)
	{
		//Gera um índice aleatório entre 0 e o tamanho total de vetor_de_dados menos um. 
		//Isso garante que o índice seja válido para acessar um elemento no vetor de dados.
		int indice_aleatorio = rand() % vetor_de_dados->size();

		//Procura "indice_aleatorio" em "indices_usados" se não achar insere a imagem em dados de treinamento.
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
		int indice_aleatorio = rand() % vetor_de_dados	-> size();

		if(indices_usados.find(indice_aleatorio) == indices_usados.end())
		{
			dados_de_validacao -> push_back(vetor_de_dados -> at(indice_aleatorio));
			indices_usados.insert(indice_aleatorio);
			count++;
		}
	}

	printf("Tamanho dos dados de treinamento %u.\n", dados_de_treinamento);
	printf("Tamanho dos dados de teste %u.\n",       dados_de_teste);
	printf("Tamanho dos dados de validação %u.\n",   dados_de_validacao);
}

void data_handler::contarClasses()
{
	int count = 0;
	for (unsigned i = 0; i < vetor_de_dados->size(); i++)
	{
		if (vetor_de_dados[label].find(vetor_de_dados -> at(i) -> obter_label()) == mapa_classes.end())
		{
			mapa_classes[vetor_de_dados -> at(i) -> obter_label()] = count;
			vetor_de_dados -> at(i) -> definir_enum_label(count);
			count++;
		}
	}
	num_classes = count;
	printf("Foram obtidicas %u classes únicas.\n", num_classes);
}

//Converte a organização dos bytes para pequeno endian, na qual o byte menos significativo vem primeiro na memória
uint32_t data_handler::conv_p_little_endian(const unsigned char* bytes)
{
	return(uint32_t) ((byte[0] << 24) |
					  (byte[1] << 16) |
					  (byte[2] << 8 ) |
					  (byte[3]));
}
  
vector<data *> * data_handler::obter_dados_de_treinamento() {return dados_de_treinamento;}
vector<data *> * data_handler::obter_dados_de_teste()       {return dados_de_teste;}
vector<data *> * data_handler::obter_dados_de_validacao()   {return dados_de_validacao;}

int main()
{
	data_handler *dh = new data_handler();
	dh->ler_vec_de_pixels("./NOME_DO_ARQUIVO");
	dh->ler_labels_de_recursos("./NOME_DO_ARQUIVO");
	dh->dividir_dados();
	dh->contar_classes();
}
