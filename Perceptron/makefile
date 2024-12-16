DADOS_TREINAMENTO := C:/Users/MIroxo/Desktop/IA_em_Cpp/MLP/Dados
DADOS_VALIDACAO   := C:/Users/MIroxo/Desktop/IA_em_Cpp/MLP/Dados
# Nome do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Nome do executável
TARGET = $(BIN_DIR)/mainPerceptron

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Executavel criado em: $(TARGET)"

# Regra para criar os objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Arquivos temporarios removidos."

# Limpeza completa
clean_all: clean
	rm -f $(TARGET)
	@echo "Tudo limpo!"

# Executar o programa
run: $(TARGET)
	DADOS_VALIDACAO=$(DADOS_VALIDACAO) DADOS_TREINAMENTO=$(DADOS_TREINAMENTO) ./$(TARGET)

# Regra para garantir que 'clean' seja chamada antes de compilar
rebuild: clean all
