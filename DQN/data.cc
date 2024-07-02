#include "data.hpp"
using namespace std;

data::data()
{
	vetor_de_recursos = new vector<uint8_t>;
}

data::~data()
{
	
}

void data::definir_vetor_de_recursos(vector<uint8_t> *vect)
{
  vetor_de_recursos = vect;
}

void data::incluir_no_vetor_de_recursos(uint8_t val)
{
	vetor_de_recursos->push_back(val); 
}

void data::definir_label(uint8_t val)
{
	label = val;
}

void data::definir_label_enumerada(int val)
{
	enum_label = val;
}

int data::obter_tamanho_do_vetor_de_recursos()
{
	return vetor_de_recursos->size();
}

uint8_t data::obter_label()
{
	return label;
}

uint8_t data::obter_enum_label()
{
	return enum_label;
}

vector<uint8_t> * data::obter_vetor_de_recursos()
{
	return vetor_de_recursos;
}

