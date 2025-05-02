# Puzzle de Letras 

## 📚 Contexto 

Este projeto foi realizado no âmbito da cadeira LI2 (Laboratórios de Informática II). Consiste no desenvolvimento de um jogo de puzzle em que o jogador tem de resolver um tabuleiro seguindo regras de lógica e conectividade entre casas.

## ✏️ Regras do Jogo

- Em cada linha e coluna só pode haver uma única instância branca (letra maiúscula) de cada símbolo.
- As restantes repetições desse símbolo devem ser riscadas com o caracter #.
- Se uma célula for riscada, todas as suas vizinhas ortogonais (acima, abaixo, esquerda e direita) têm de ser brancas.
- Todas as células brancas devem estar ligadas entre si por um caminho ortogonal contínuo (sem diagonais).
- O jogador pode aplicar regras de inferência para deduzir automaticamente o estado de certas células com base no estado atual do tabuleiro.

## ⚙️ Etapas de Desenvolvimento

1. Motor básico de jogo.
2. Verificação de restrições e funcionalidade de desfazer.
3. Verificação de conectividade das casas brancas.
4. Sistema de dicas.
5. Resolução automática do puzzle.

## 🕹️ Comandos 

| Comando        | Descrição                                              |
|----------------|--------------------------------------------------------|
| g (ficheiro)   | Guarda o estado atual do jogo num ficheiro             |
| l (ficheiro)   | Carrega o estado do jogo a partir de um ficheiro       |
| (coordenada)   | Formato : número(linha) letra(coluna)  ex : 1a         |
| b (coordenada) | Pinta a casa a branco (letra maiúscula)                |
| r (coordenada) | Risca a casa (substitui por '#')                       |
| v              | Verifica o estado atual e mostra violações das regras  |
| a              | Aplica inferências automáticas com base nas regras     |
| A              | Repete o comando 'a' até não haver mais alterações     |
| R              | Resolve automaticamente o puzzle (se possível)         |
| d              | Desfaz o último comando executado                      |
| s              | Sai do jogo                                            |
| ?              | Mostra todos os comandos possíveis                     |

## 🛠️ Como Instalar

### Pré-requisitos

Certifique-se de ter as seguintes ferramentas instaladas no seu sistema:

- **GCC** (GNU Compiler Collection) para compilar o código C.
- **CUnit** para a execução de testes.

### Compilação
Para compilar o projeto e gerar o executável jogo, execute:
```bash
make jogo
```
### Testes
Para compilar e executar os testes com CUnit, execute:
```bash
make testar
```

### Executar o jogo 
Após a compilação, execute o jogo com o seguinte comando : 
```bash
./jogo
```
