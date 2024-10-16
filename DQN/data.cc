#include "data.hpp"
using namespace std;

// vec == vetor; rec == recurso; pont == ponteiro

data::data() { vec_de_rec = new vector<uint8_t>; }

data::~data(){	}


void data::def_pont_para_vec_de_rec(vector<uint8_t> * vect) { vec_de_rec = vect; }

// O operador "->" é usado para acessar membros (como métodos, "push_back", ou atributos) de um objeto, "vector", ...
// quando você tem um ponteiro para esse objeto.
// O método "push_back()" é uma função membro da classe "std::vector" que adiciona um novo elemento ao final do vetor.

void data::incluir_no_vec_de_rec(uint8_t val) { vec_de_rec -> push_back(val); }

void data::definir_label(uint8_t val) { label = val; }

void data::definir_enum_label(int val) { enum_label = val; }

int data::obter_tamanho_do_vec_de_rec() {return vec_de_rec -> size();}

uint8_t data::obter_label() { return label; }

uint8_t data::obter_enum_label() { return enum_label; }

vector<uint8_t> * data::obter_vetor_de_recursos() { return vetor_de_recursos; }

