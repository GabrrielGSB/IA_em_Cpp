# Nome do compilador
CXX = g++

# Flags de compilação (opcionalmente, adicione -g para depuração ou -O2 para otimização)
# CXXFLAGS = 

# Arquivo executável final
TARGET = main

# Lista de arquivos fonte
SRCS = mainPerceptron.cpp Neuronio.cpp Perceptron.ccp

# Gera os objetos substituindo a extensão .cpp/.ccp por .o
OBJS = $(SRCS:.cpp=.o)

# Regra padrão: compila tudo
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

# Regra genérica para criar os arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)
