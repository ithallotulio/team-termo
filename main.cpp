#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <cstdlib>

#define TAMANHO 5

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

/* --------------------------------------------------------------------- */
/*                         Declaração de funções                         */
/* --------------------------------------------------------------------- */

// Utility
bool isAlpha(string str);
bool containsLetter(char letter, string word);
void stringUpper(string *str);
void zeroArray(int array[], int size);
string removeSpaces(string word);

// Game Mechanics and Rules
void checkUserWord(string userInput, string randomWord, int userWordChecked[]);
bool isComplete(int userWordChecked[TAMANHO]);
bool isValidWord(string word);
string getUserWord();
string getRandomWord(vector<string>vecString);

// Game Interface
void showUserWordChecked(string userInput, int userWordChecked[], int delay);
void showGameScreen(vector<string> vecUserWord, string gameWord, int userWordChecked[]);
void instructionsGame();
// File
vector<string> getFileInfo(string fileName);

/* --------------------------------------------------------------------- */
/*                                 Main                                  */
/* --------------------------------------------------------------------- */

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
    instructionsGame();
    while (tentativa<=6) {
        cout << "Digite uma palavra: ";
        userWord = getUserWord();
        vecUserWord.push_back(userWord);
        showGameScreen(vecUserWord, gameWord, userWordChecked);
        tentativa++;
        if (isComplete(userWordChecked)){
            break;
        }
    }
    pontuacao = (6-tentativa) * 25;
    system("cls");
    cout << "Pontuação : " << pontuacao << endl;
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

string getRandomWord(vector<string>vecString) {
    srand(time(0));
    int RandomIndex = rand() % vecString.size();
    return vecString[RandomIndex];
}

//                  ==========   Game Interface   ==========

void showUserWordChecked(string userInput, int userWordChecked[], int delay = 0) {
    int count=0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
void instructionsGame(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    cout << "                Descubra a palavra certa em 6 tentativas                " << endl;
    cout << " Depois de cada tentativa, é mostrado o quão perto você está da solução " << endl;
    cout << " ---------------------" << endl;
    cout << "| ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "T";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << " | E | R | N | O |" << endl;
    cout << " ---------------------" << endl;
    cout << " A letra ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "T";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << " faz parte da palavra e está na posição correta " << endl << endl;
    cout << " ---------------------" << endl;
    cout << " | L | ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "A";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << " | S | E | R |" << endl;
    cout << " ---------------------" << endl;
    cout << " A letra ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "A";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    cout << " faz parte da palavra, mas em outra posição " << endl << endl;
    cout << " ---------------------" << endl;
    cout << " | S | U | M | I | U |" << endl;
    cout << " ---------------------" << endl;
    cout << " Nenhuma letra faz parte da palavra " << endl << endl;
    cout << " Os acentos não são considerados, nem nas tentativas, nem nas respostas " << endl;
    cout << " As palavras podem possuir letras repetidas" << endl << endl;
    system ("pause");
    system ("cls");
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