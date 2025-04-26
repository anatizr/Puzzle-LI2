CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g -fprofile-arcs -ftest-coverage -Isrc
LDFLAGS = -lcunit

JOGO_SRC = src/jogo_main.c src/jogo_funcoes.c
TESTES = test_desfazer test_lerGuardar test_riscarPintar test_verificar test_vizualizar

$(TESTES): test_%: testes/test_%.c
	rm -f *.gcda
	$(CC) $(CFLAGS) $< src/jogo_funcoes.c -o $@ $(LDFLAGS)
	./$@

jogo:
	$(CC) $(CFLAGS) $(JOGO_SRC) -o jogo $(LDFLAGS)
	./jogo

testar: $(TESTES)

clean:
	rm -f jogo $(TESTES) *.gcda *.gcno *.gcov *.o