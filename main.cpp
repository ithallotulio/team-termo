// O Replit salva automaticamente, só escrever o código que ele ja deixa salvo
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <chrono>    //pra add delay
#include <thread>    //pra add delay
#include <windows.h> // para a mudança de cor do texto
#define TAMANHO 5

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

// Declaração de funções
bool isAlpha(string str);
bool isValidWord(string word);
bool containsLetter(char letter, string word);
void escritaUser(string userInput, int verificado[]);
void stringUpper(string *str);
void limpaVetor(int palavra[]);
void verificador(string userInput, string randomWord, int verificado[]);
string removeSpaces(string word);
string getUserInput();
string getRandomWord(vector<string>vecString);
vector<string> getFileInfo(string fileName);

// Main
int main() {
    // Declaração de variáveis
    vector<string> vecWordList = getFileInfo("wordlist.txt");
    string userWord, gameWord;
    int verificado[TAMANHO] = {0};

    // Código
    gameWord = getRandomWord(vecWordList);
    //gameWord = {"PAPAR"};
    cout << "Digite uma palavra: ";
    userWord = getUserInput();
    verificador(userWord, gameWord, verificado);

    cout << "\nVocê digitou: " << userWord << endl;
    cout << "A palavra sorteada foi: " << gameWord << endl;
    escritaUser(userWord, verificado);
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

//escreve a resposta do user com as cores diferentes
void escritaUser(string userInput, int verificado[]) {
    int count=0;


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //necessário para mudar as cores

    cout << "---------------------" << endl;
        for (count=0;count<TAMANHO;count++) {
            cout << "|";
            if (verificado[count]==2) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            } else if (verificado[count]==1) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
            }
            cout << " " << userInput[count] << " " ;
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
            sleep_for(300ms);
        }
        cout << "|" << endl;
        cout << "---------------------" << endl;
}

// Toda a string fica maiúscula
void stringUpper(string *str) {
    for (char &c : *str) {
        c = toupper(c);
    }
}

void limpaVetor(int palavra[]) {
    for (int i = 0; i < TAMANHO; i++)
        palavra[i]=0;
}

void verificador(string userWord, string gameWord, int verificado[]) {
    int countpalavra=0;
    int counttermo=0;

    limpaVetor(verificado);

    for(countpalavra=0;countpalavra<TAMANHO;countpalavra++) {
        if(userWord[countpalavra]==gameWord[countpalavra]) {
            verificado[countpalavra] = 2;
        }
    }

    for(counttermo=0;counttermo<TAMANHO;counttermo++) {
        if(verificado[counttermo]!=2) {
            for(countpalavra=0;countpalavra<TAMANHO;countpalavra++) {
                if(verificado[countpalavra]==0 && userWord[countpalavra]==gameWord[counttermo]) {
                    verificado[countpalavra] = 1;
                    break;
                }
            }
        }
    }
}

// Retorna a palavra sem espaços
string removeSpaces(string word) {
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
string getUserInput() {
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
string getRandomWord(vector<string>vecString) {
    srand(time(0));
    int RandomIndex = rand() % vecString.size();
    return vecString[RandomIndex];
}

// Retorna um vetor de string, onde cada index do vetor armazena uma linha do arquivo.txt
vector<string> getFileInfo(string fileName) {
    ifstream file(fileName);
    vector<string> fileInfo;
    string line;
    while(getline(file, line)){
        fileInfo.push_back(line);
    }
    return fileInfo;
}
