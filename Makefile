# Nome do executável
TARGET = bin/meu_programa

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Diretórios de origem e binários
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

# Obtém todos os arquivos .cpp em src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Gera os arquivos .o correspondentes na pasta bin
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SOURCES))

# Arquivo principal
MAIN = main.cpp

# Regra padrão
all: $(TARGET)

# Compila o programa principal com os módulos auxiliares
$(TARGET): $(OBJECTS) $(MAIN) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regra para compilar arquivos .cpp em .o na pasta bin
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar a pasta bin se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Limpa arquivos compilados
clean:
	rm -rf $(BIN_DIR) $(TARGET)

# Regra para reconstruir tudo do zero
rebuild: clean all
