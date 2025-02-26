# Nome do executável
EXECUTABLE = $(BIN_DIR)/tp1.out

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -I $(INCLUDE_DIR)

# Arquivos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Regra padrão
all: criar_diretorios $(EXECUTABLE)

# Cria as pastas bin e obj, se não existirem
criar_diretorios:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compila o executável
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compila os arquivos .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

# Limpeza apenas dos objetos
clean_obj:
	@rm -rf $(OBJ_DIR)
