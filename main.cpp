#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <cstdlib>

#define BGREEN  "\033[7;32m"
#define GREEN   "\033[32m"
#define BYELLOW "\033[7;33m"
#define BGREY    "\033[7;90m"
#define RESET   "\033[0m"
#define TAMANHO 5

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

/* --------------------------------------------------------------------- */
/*                         Declaração de funções                         */
/* --------------------------------------------------------------------- */

// Utility
bool isAlpha(string str);
bool isAlphanumeric(const std::string& str);
bool containsLetter(char letter, string word);
void stringUpper(string *str);
void zeroArray(int array[], int size);
string removeSpaces(string word);

// Game Mechanics and Rules
void checkUserWord(string userInput, string randomWord, int userWordChecked[]);
bool isComplete(int userWordChecked[TAMANHO]);
bool isValidWord(string word);
string getUserWord();
string getUserName();
string getRandomWord(vector<string>vecString);

// Game Interface
void showUserWordChecked(string userInput, int userWordChecked[], int delay);
void showGameScreen(vector<string> vecUserWord, string gameWord, int userWordChecked[], int pontuacao);
void instructionsGame();
void startMenu(int);

// File
vector<string> getFileInfo(string fileName);

/* --------------------------------------------------------------------- */
/*                                 Main                                  */
/* --------------------------------------------------------------------- */

int main() {
    // Declaração de variáveis
    vector<string> vecWordList = getFileInfo("wordlist.txt");
    vector<string> vecUserWord;
    string userWord = {0};
    string gameWord = {0};
    int userWordChecked[TAMANHO] = {0};
    int pontuacao=0;
    int tentativa=1;
    bool lose = false;
    // Código

    instructionsGame();
    cout << "Score: 0" << endl << endl;
    do {
        //gameWord = getRandomWord(vecWordList);
        gameWord = {"PAPAR"};
        startMenu(pontuacao);
        while (tentativa<=6) {
            cout << "\nDigite uma palavra: ";
            userWord = getUserWord();
            vecUserWord.push_back(userWord);
            showGameScreen(vecUserWord, gameWord, userWordChecked, pontuacao);
            tentativa++;
            if (isComplete(userWordChecked)){
                // tela de vitoria inserida aqui
                break;
            }
        }
        cout << endl;
        system("pause");
        system ("cls");
        cout << "Score: " << pontuacao << " + " << GREEN << (7-tentativa) * 25 << RESET << endl << endl;
        pontuacao += (7-tentativa) * 25;

        if (tentativa > 6 && !(isComplete(userWordChecked))){
            lose = true;
        }
        tentativa = 1;
        userWord = "";
        vecUserWord.clear();
        zeroArray(userWordChecked, TAMANHO);

    } while (!lose);
        //tela de derrota e inserção de nome do jogador aqui
        cout << "perdeu" << endl;
    return 0;
}

/* --------------------------------------------------------------------- */
/*                                Funções                                */
/* --------------------------------------------------------------------- */

//                  ==========   Utility   ==========

bool isAlpha(string str) {
    for (char c : str) {
        if (!isalpha(c))
            return false;
    }
    return true;
}

bool isAlphanumeric(const std::string& str){
    for (char c : str){
        if(!std::isalnum(c)){
            return false;
        }
    }
    return true;
}

bool containsLetter(char letter, string word) {
    for (int i = 0; i < word.length(); i++) {
        if (letter == word[i])
            return true;
    }
    return false;
}

void stringUpper(string *str) {
    for (char &c : *str) {
        c = toupper(c);
    }
}

void zeroArray(int array[], int size = 5) {
    for (int i = 0; i < size; i++)
        array[i]=0;
}

string removeSpaces(string word) {
    string wordNoSpaces;
    for (char c: word) {
        if (c != ' ') {
            wordNoSpaces += c;
        }
    }
    return wordNoSpaces;
}

//            ==========   Game Mechanics and rules   ==========

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

bool isComplete(int userWordChecked[TAMANHO]) {
    bool check;
    for (int i = 0;i<TAMANHO;i++) {
        if (userWordChecked[i] == 2) {
            check = true;
        } else {
            check = false;
            break;
        }
    }
    return check;
}

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

string getUserWord() {
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

string getUserName(){
    string name;
    getline(cin, name);
    while (!isAlphanumeric(name) || name.length() > 15){
        cout << "O nome digitado não é válido" << endl;
        getline(cin, name);
    }
    return name;
}

string getRandomWord(vector<string>vecString) {
    srand(time(0));
    int RandomIndex = rand() % vecString.size();
    return vecString[RandomIndex];
}
//                  ==========   Game Interface   ==========

void showUserWordChecked(string userInput, int userWordChecked[], int delay = 0) {
    int count=0;
    cout << "---------------------" << endl;
    for (count=0;count<TAMANHO;count++) {
        sleep_for(milliseconds(delay));
        cout << "|";
        if (userWordChecked[count]==2) {
            cout << BGREEN;
        } else if (userWordChecked[count]==1) {
            cout << BYELLOW;
        } else if (userWordChecked[count]==0) {
            cout << BGREY;
        }
        cout << " " << userInput[count] << " " << RESET;
    }
    cout << "|" << endl;
    cout << "---------------------" << endl;
}

void showGameScreen(vector<string> vecUserWord, string gameWord, int userWordChecked[], int pontuacao) {
    int i;
    system("cls");
    cout << "Score: " << pontuacao << endl << endl;
    for (i=0; i < vecUserWord.size()-1; i++){
        checkUserWord(vecUserWord[i], gameWord, userWordChecked);
        showUserWordChecked(vecUserWord[i], userWordChecked);
    }
    checkUserWord(vecUserWord[i], gameWord, userWordChecked);
    showUserWordChecked(vecUserWord[i], userWordChecked, 350);
    if (vecUserWord.size() < 6){
        for (i=0; i < 6-vecUserWord.size(); i++){
            cout << "---------------------" << endl;
            cout << "|   |   |   |   |   |" << endl;
            cout << "---------------------" << endl;
        }
    }
    sleep_for(milliseconds(300));
}

void instructionsGame() {
    system("cls");
    cout << "                Descubra a palavra certa em 6 tentativas!!                " << endl << endl;
    cout << " Depois de cada tentativa, é mostrado o quão perto você está da solução " << endl << endl;
    cout << " ---------------------" << endl;
    cout << " |" << BGREEN << " T " << RESET << "| E | R | N | O |" << endl;
    cout << " ---------------------" << endl << endl;
    cout << " A letra " << BGREEN << " T " << RESET << " faz parte da palavra e está na posição correta.\n" << endl;
    cout << " ---------------------" << endl;
    cout << " | L |" << BYELLOW << " A " << RESET << "| S | E | R |" << endl;
    cout << " ---------------------" << endl << endl;
    cout << " A letra " << BYELLOW << " A " << RESET << " faz parte da palavra, mas em outra posição." << endl << endl;
    cout << " ---------------------" << endl;
    cout << " | S | U | M | I | U |" << endl;
    cout << " ---------------------" << endl << endl;
    cout << " Nenhuma letra faz parte da palavra." << endl << endl;
    cout << " Os acentos não são considerados, nem nas tentativas, nem nas respostas." << endl;
    cout << " As palavras podem possuir letras repetidas.\n" << endl;
    cout << " " << system ("pause");
    system ("cls");
}

void startMenu(int pontuacao){
    int i=0;  
    for (i=0; i < 6; i++){
        cout << "---------------------" << endl;
        cout << "|   |   |   |   |   |" << endl;
        cout << "---------------------" << endl;
    }

}

//                      ==========   File   ==========

vector<string> getFileInfo(string fileName) {
    ifstream file(fileName);
    vector<string> fileInfo;
    string line;
    while(getline(file, line)){
        fileInfo.push_back(line);
    }
    return fileInfo;
}
