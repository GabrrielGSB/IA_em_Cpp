DADOS_TREINAMENTO := Dados
DADOS_VALIDACAO   := Dados

# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -I$(COMUM_INCLUDE)

# Diretórios
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
COMUM_INCLUDE = ../Comum/include
COMUM_SRC = ../Comum/src

# Nome do executável
TARGET = $(BIN_DIR)/mainMLP

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(COMUM_SRC)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%, $(SRCS))) \
       $(patsubst $(COMUM_SRC)/%.cpp, $(OBJ_DIR)/%.o, $(filter $(COMUM_SRC)/%, $(SRCS)))

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Executável criado em: $(TARGET)"

# Regra genérica para criar os objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(COMUM_SRC)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Arquivos temporários removidos."

# Limpeza completa
clean_all: clean
	rm -f $(TARGET)
	@echo "Tudo limpo!"

# Executar o programa
run: $(TARGET)
	DADOS_VALIDACAO=$(DADOS_VALIDACAO) DADOS_TREINAMENTO=$(DADOS_TREINAMENTO) ./$(TARGET)

# Regra para garantir que 'clean' seja chamada antes de compilar
rebuild: clean all
