# Diretórios
SRC_DIR = src
TEST_DIR = testes
BIN_DIR = bin
COVERAGE_DIR = coverage-report

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g -fsanitize=address -fprofile-arcs -ftest-coverage -Isrc
LDFLAGS = -lcunit -fsanitize=address -fprofile-arcs -ftest-coverage

SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRC))

# Executáveis 
EXEC = $(BIN_DIR)/jogo
TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.c)
TEST_EXEC = $(patsubst $(TEST_DIR)/test_%.c, $(BIN_DIR)/test_%, $(TEST_SRCS))

# Garantir que a pasta bin existe
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compilar o jogo 
$(EXEC): $(SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

jogo: $(EXEC)
	$(EXEC)

# Compilar os testes
$(BIN_DIR)/test_%: $(SRC_NO_MAIN) $(TEST_DIR)/test_%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

testar: $(TEST_EXEC)
	@for test in $(TEST_EXEC); do ./$$test; done

 coverage: 
	@echo "Gerando relatório de cobertura..."
	@mkdir -p $(COVERAGE_DIR)
	@lcov --capture --no-external --directory . --output-file $(COVERAGE_DIR)/coverage.info --quiet
	@lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' '*/$(TEST_DIR)/*' --output-file $(COVERAGE_DIR)/coverage_filtered.info --quiet
	@genhtml $(COVERAGE_DIR)/coverage_filtered.info --output-directory $(COVERAGE_DIR) --title "Cobertura de Código" --quiet
	@echo "Resumo da cobertura:"
	@lcov --summary $(COVERAGE_DIR)/coverage_filtered.info | grep -v 'branches'

clean: 
	rm -rf $(BIN_DIR) *.gcno *.gcda $(COVERAGE_DIR)