// O Replit salva automaticamente, só escrever o código que ele ja deixa salvo
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <chrono>    //pra add delay
#include <thread>    //pra add delay
#include <windows.h> // para a mudança de cor do texto
#include <cstdlib>

#define TAMANHO 5

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono;         // miliseconds

// Declaração de funções
bool isAlpha(string str);
bool isValidWord(string word);
bool containsLetter(char letter, string word);
bool isComplete(int userWordChecked[TAMANHO]);
void showUserWordChecked(string userInput, int userWordChecked[], int delay);
void stringUpper(string *str);
void zeroArray(int array[], int size);
void checkUserWord(string userInput, string randomWord, int userWordChecked[]);
void showGameScreen(vector<string> vecUserWord, string gameWord, int userWordChecked[]);
string removeSpaces(string word);
string getUserInput();
string getRandomWord(vector<string>vecString);
vector<string> getFileInfo(string fileName);

// Main
int main() {
    // Declaração de variáveis
    vector<string> vecWordList = getFileInfo("wordlist.txt");
    vector<string> vecUserWord;
    string userWord, gameWord;
    int userWordChecked[TAMANHO] = {0};
    int pontuacao=0;
    int tentativa=0;

    // Código
    //gameWord = getRandomWord(vecWordList);
    gameWord = {"PAPAR"};
    while (tentativa<=6) {
        cout << "Digite uma palavra: ";
        userWord = getUserInput();
        vecUserWord.push_back(userWord);
        showGameScreen(vecUserWord, gameWord, userWordChecked);
        tentativa++;
        if (isComplete( userWordChecked )){
            break;
        }
    }
    pontuacao = (6-tentativa) * 25;
    system("cls");
    cout << "Pontuação : " << pontuacao << endl;
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

bool isComplete(int userWordChecked[TAMANHO]){
    bool check;
    for (int i = 0;i<TAMANHO;i++){
        if( userWordChecked[i] == 2 ){
            check = true;
        }else{
            check = false;
            break;
        }
    }
    return check;
}

// Toda a string fica maiúscula
void stringUpper(string *str) {
    for (char &c : *str) {
        c = toupper(c);
    }
}

// Zera o array
void zeroArray(int array[], int size = 5) {
    for (int i = 0; i < size; i++)
        array[i]=0;
}

void checkUserWord(string userWord, string gameWord, int userWordChecked[]) {
    int countpalavra=0;
    int counttermo=0;

    zeroArray(userWordChecked);

    for(countpalavra=0;countpalavra<TAMANHO;countpalavra++) {
        if(userWord[countpalavra]==gameWord[countpalavra]) {
            userWordChecked[countpalavra] = 2;
        }
    }

    for(counttermo=0;counttermo<TAMANHO;counttermo++) {
        if(userWordChecked[counttermo]!=2) {
            for(countpalavra=0;countpalavra<TAMANHO;countpalavra++) {
                if(userWordChecked[countpalavra]==0 && userWord[countpalavra]==gameWord[counttermo]) {
                    userWordChecked[countpalavra] = 1;
                    break;
                }
            }
        }
    }
}

//escreve a resposta do user com as cores diferentes
void showUserWordChecked(string userInput, int userWordChecked[], int delay = 0) {
    int count=0;


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //necessário para mudar as cores

    cout << "---------------------" << endl;
        for (count=0;count<TAMANHO;count++) {
            sleep_for(milliseconds(delay));
            cout << "|";
            if (userWordChecked[count]==2) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            } else if (userWordChecked[count]==1) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
            }
            cout << " " << userInput[count] << " " ;
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        }
        cout << "|" << endl;
        cout << "---------------------" << endl;
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

void showGameScreen(vector<string> vecUserWord, string gameWord, int userWordChecked[]) {
    int i;
    system("cls");
    for (i=0; i < vecUserWord.size()-1; i++){
        checkUserWord(vecUserWord[i], gameWord, userWordChecked);
        showUserWordChecked(vecUserWord[i], userWordChecked);
    }
    checkUserWord(vecUserWord[i], gameWord, userWordChecked);
    showUserWordChecked(vecUserWord[i], userWordChecked, 300);
    if (vecUserWord.size() < 6){
        for (i=0; i < 6-vecUserWord.size(); i++){
            cout << "---------------------" << endl;
            cout << "|   |   |   |   |   |" << endl;
            cout << "---------------------" << endl;
        }
    }
}
