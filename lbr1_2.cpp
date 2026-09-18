#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <clocale>

using namespace std;

bool isVowel(char c) {
    string vowels = "аеёиоуыэюяАЕЁИОУЫЭЮЯ";
    return vowels.find(c) != string::npos;
}

bool isConsonant(char c) {
    string consonants = "бвгджзйклмнпрстфхцчшщБВГДЖЗЙКЛМНПРСТФХЦЧШЩ";
    return consonants.find(c) != string::npos;
}

bool isDigitChar(char c) {
    return isdigit(static_cast<unsigned char>(c));
}

bool isSymbol(char c) {
    return !isVowel(c) && !isConsonant(c) && !isDigitChar(c) && c != '@';
}

bool contains(const vector<char>& vec, char c) {
    for (char el : vec) {
        if (el == c) return true;
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    cout << "Введите строку: \n";
    string input;
    getline(cin, input);

    if (input.length() > 50) {
        input = input.substr(0, 50);
    }

    vector<vector<char>> jaggedArray(4);

    for (char c : input) {
        if (isVowel(c)) {
            if (!contains(jaggedArray[0], c)) jaggedArray[0].push_back(c);
        } else if (isConsonant(c)) {
            if (!contains(jaggedArray[1], c)) jaggedArray[1].push_back(c);
        } else if (isDigitChar(c)) {
            if (!contains(jaggedArray[2], c)) jaggedArray[2].push_back(c);
        } else if (isSymbol(c)) {
            if (!contains(jaggedArray[3], c)) jaggedArray[3].push_back(c);
        }
    }

    /*
    char** jaggedC = (char**)malloc(4 * sizeof(char*));
    int sizes[4] = {0};
    for (int i = 0; i < 4; i++) jaggedC[i] = nullptr;

    for (char c : input) {
        int row = -1;
        if (isVowel(c)) row = 0;
        else if (isConsonant(c)) row = 1;
        else if (isDigitChar(c)) row = 2;
        else if (isSymbol(c)) row = 3;

        if (row != -1) {
            bool found = false;
            for (int i = 0; i < sizes[row]; i++) {
                if (jaggedC[row][i] == c) { found = true; break; }
            }
            if (!found) {
                sizes[row]++;
                jaggedC[row] = (char*)realloc(jaggedC[row], sizes[row] * sizeof(char));
                jaggedC[row][sizes[row] - 1] = c;
            }
        }
    }
    for (int i = 0; i < 4; i++) free(jaggedC[i]);
    free(jaggedC);
    */

    cout << "Массив:\n";
    for (int i = 0; i < 4; i++) {
        for (char c : jaggedArray[i]) {
            cout << c << " ";
        }
        cout << "\n";
    }

    string resultStr = input + "+123АБВ";

    cout << "Результат:\n";
    for (char c : resultStr) {
        if (contains(jaggedArray[0], c)) {
            cout << "\033[91m" << c;
        } else if (contains(jaggedArray[1], c)) {
            cout << "\033[96m" << c;
        } else if (contains(jaggedArray[2], c)) {
            cout << "\033[92m" << c;
        } else if (contains(jaggedArray[3], c)) {
            cout << "\033[93m" << c;
        } else {
            cout << "\033[0m" << c;
        }
    }
    cout << "\033[0m\n";

    return 0;
}
