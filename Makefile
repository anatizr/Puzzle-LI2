CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g -fprofile-arcs -ftest-coverage -Isrc
LDFLAGS = -lcunit


jogo: 
	$(CC) $(CFLAGS) src/jogo_main.c src/jogo_funcoes.c -o jogo $(LDFLAGS)

testar: 
	rm -f *.gcda
	$(CC) $(CFLAGS) testes/teste.c src/jogo_funcoes.c -o testar $(LDFLAGS)
	./testar

clean:
	rm -f jogo testar *.gcda *.gcno *.gcov *.o
