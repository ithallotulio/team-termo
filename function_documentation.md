# Function documentation
## Este documento tem como propósito explicar as funções do main.cpp

### Utility
- **isAlpha()**, verifica se uma string contém apenas char alfabéticos (alfabeto inglês)
- **containsLetter()**, verifica se uma letra está contida em uma palavra
- **stringUpper()**, toda a string fica maiúscula
- **zeroArray()**, zera o array
- **removeSpaces()**, retorna a palavra sem espaços

### Game mechanics and rules
- **checkUserWord()**
    - Verifica o quão parecida é a palavra digitada pelo usuário com a palavra do jogo
    - a verificação é armazenada no array userWordChecked[]
    - cada posição do array representa uma letra do userWord
    - 0 = não existe a letra na palavra
    - 1 = existe a letra na palavra, mas está na posição errada
    - 2 = existe a letra na palavra e está na posição correta
- **isComplete()**
- **isValidWord()**
    - Verifica se uma palavra é válida, retornando:
    - Falso, char não alfabetico
    - Falso, tem espaço
    - Falso, não tem 5 letras
    - Falso, todas letras vogais (5 vogais)
    - Falso, todas letras consoantes (0 vogais)
    - Verdadeiro, qualquer outra situação
- **getUserInput()**
    - Coleta e retorna a entrada do usuário após validação
    - Remove espaços da entrada
    - Retorna a string maiúscula
- **getRandomWord()**, retorna uma palavra aleatória de um vetor de palavras

### Game Interface
- **showUserWordChecked()**, exibe no console a palavra do user colorida após verificação
- **showGameScreen()**, exibe no console as palavras digitadas e os blocos de palavras vazios das tentativas restantes

### File
- **getFileInfo()**, retorna um vetor de string, onde cada index do vetor armazena uma linha do arquivo.txt