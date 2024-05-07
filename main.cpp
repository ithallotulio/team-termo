// O Replit salva automaticamente, só escrever o código que ele ja deixa salvo
#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

// Declaração de funções
bool isAlpha(string str);
bool isValidWord(string word);
bool containsLetter(char letter, string word);
void stringUpper(string *str);
string removeSpaces(string word);
string getUserInput();
string getRandomWord(vector<string>vecString);
vector<string> getFileInfo(string fileName);

// Main
int main() {
    // Declaração de variáveis
    string userInput, randomWord;
    vector<string> vecWordList = getFileInfo("wordlist.txt");

    // Código
    randomWord = getRandomWord(vecWordList);
    cout << "Digite uma palavra: ";
    userInput = getUserInput();

    cout << "A palavra sorteada foi: " << randomWord << endl;
    cout << "Você digitou: " << userInput << endl;

    return 0;
}

// Funções

// Verifica se uma string contém apenas char alfabéticos (alfabeto inglês)
bool isAlpha(string str) {
    for (char c : str) {
        if (!isalpha(c))
            return false;
    }
    return true;
}

/*
 * Verifica se uma palavra é válida, retornando:
 * Falso, char não alfabetico
 * Falso, tem espaço
 * Falso, não tem 5 letras
 * Falso, todas letras vogais (5 vogais)
 * Falso, todas letras consoantes (0 vogais)
 * Verdadeiro, qualquer outra situação
 */
bool isValidWord(string word) {
    string vowels = {"AEIOU"};
    int i, vowelCount = 0;

    if (!isAlpha(word) || word.length() != 5) 
        return false;

    stringUpper(&word);
    for (i = 0; i < 5; i++) {
        if (containsLetter(word[i], vowels))
            vowelCount++;
    }
    if (vowelCount == 5 || vowelCount == 0) {
        return false;
    }
    return true;
}

// Verifica se uma letra está contida em uma palavra
bool containsLetter(char letter, string word) {
    for (int i = 0; i < word.length(); i++) {
        if (letter == word[i])
            return true;
    }
    return false;
}

// Toda a string fica maiúscula
void stringUpper(string *str) {
    for (char &c : *str) {
        c = toupper(c);
    }
}

// Retorna a palavra sem espaços
string removeSpaces(string word){
    string wordNoSpaces;
    for (char c: word) {
        if (c != ' ') {
            wordNoSpaces += c;
        }
    }
    return wordNoSpaces;
}

/*
* Coleta e retorna a entrada do usuário após validação
* Remove espaços da entrada
* Retorna a string maiúscula 
*/
string getUserInput(){
    string input;

    getline(cin, input);
    input = removeSpaces(input);
    while (!isValidWord(input)) {
        cout << "A palavra digitada não é válida" << endl;
        getline(cin, input);
    }
    stringUpper(&input);
    return input;
}

// Retorna uma palavra aleatória de um vetor de palavras
string getRandomWord(vector<string>vecString){
    srand(time(0));
    int RandomIndex = rand() % vecString.size();
    return vecString[RandomIndex];
}

/* 
* Retorna um vetor de string, tendo em cada índice uma linha do fileName.txt
* Indice 0 armazena 1º linha 
* Indice 1 armazena 2º linha
* Indice 2 armazena 3º linha, e assim por diante...
*/
vector<string> getFileInfo(string fileName){
    ifstream file(fileName);
    vector<string> fileInfo;
    string line;
    while(getline(file, line)){
        fileInfo.push_back(line);
    }
    return fileInfo;
}

