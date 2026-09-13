#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

double englishLetters[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015,
    6.094, 6.966, 0.153, 0.772, 4.025,  2.406, 6.749,
    7.507, 1.929, 0.095, 5.987, 6.327,  9.056, 2.758,
    0.978, 2.360, 0.150, 1.974, 0.074
};

string caesarCipher(string text, int shift) {
    string result = "";
    shift = ((shift % 26) + 26) % 26;

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + shift) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + shift) % 26;
        }
        result += c;
    }
    return result;
}

string atbashCipher(string text) {
    string result = "";
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') {
            c = 'z' - (c - 'a');
        } else if (c >= 'A' && c <= 'Z') {
            c = 'Z' - (c - 'A');
        }
        result += c;
    }
    return result;
}

string rot47Cipher(string text) {
    string result = "";
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c >= 33 && c <= 126) {
            c = 33 + (c - 33 + 47) % 94;
        }
        result += c;
    }
    return result;
}

string vigenereCipher(string text, string key, bool decode) {
    string cleanKey = "";
    for (size_t i = 0; i < key.length(); i++) {
        char c = key[i];
        if (c >= 'A' && c <= 'Z') c = c + 32;
        if (c >= 'a' && c <= 'z') cleanKey += c;
    }
    if (cleanKey == "") return text;

    string result = "";
    int keyIndex = 0;

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        int shift = cleanKey[keyIndex % cleanKey.length()] - 'a';
        if (decode) {
            shift = (26 - shift) % 26;
        }

        if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + shift) % 26;
            keyIndex++;
        } else if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + shift) % 26;
            keyIndex++;
        }
        result += c;
    }
    return result;
}

double getChiScore(string text) {
    int counts[26] = {0};
    int totalLetters = 0;

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z') c = c + 32;
        if (c >= 'a' && c <= 'z') {
            counts[c - 'a']++;
            totalLetters++;
        }
    }

    if (totalLetters == 0) return 999999;

    double score = 0.0;
    for (int i = 0; i < 26; i++) {
        double expected = (englishLetters[i] / 100.0) * totalLetters;
        double diff = counts[i] - expected;
        score += (diff * diff) / expected;
    }
    return score;
}

void crackCaesar(string text, bool showAll) {
    int bestShift = 0;
    double bestScore = 999999;
    string bestText = "";

    for (int shift = 0; shift < 26; shift++) {
        string decrypted = caesarCipher(text, -shift);
        double score = getChiScore(decrypted);

        if (showAll) {
            cout << "Shift " << shift << ": " << decrypted << "\n";
        }

        if (score < bestScore) {
            bestScore = score;
            bestShift = shift;
            bestText = decrypted;
        }
    }

    if (!showAll) {
        cout << "Best Shift: " << bestShift << "\n";
        cout << "Decrypted Text: " << bestText << "\n";
    }
}

void runMenu() {
    int choice = -1;

    while (choice != 0) {
        cout << "\n=== Cipher Program ===\n";
        cout << "1. Caesar Cipher (Encode)\n";
        cout << "2. Caesar Cipher (Decode)\n";
        cout << "3. Auto-Crack Caesar\n";
        cout << "4. Brute-Force Caesar (All 26 shifts)\n";
        cout << "5. Vigenere Cipher\n";
        cout << "6. ROT13 / ROT47\n";
        cout << "7. Atbash Cipher\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Bye!\n";
            break;
        }

        cin.ignore();
        string text = "";
        int shift = 0;

        if (choice == 1 || choice == 2) {
            cout << "Enter text: ";
            getline(cin, text);
            cout << "Enter shift: ";
            cin >> shift;
            if (choice == 2) shift = -shift;
            cout << "Result: " << caesarCipher(text, shift) << "\n";
        } else if (choice == 3) {
            cout << "Enter ciphertext: ";
            getline(cin, text);
            crackCaesar(text, false);
        } else if (choice == 4) {
            cout << "Enter ciphertext: ";
            getline(cin, text);
            crackCaesar(text, true);
        } else if (choice == 5) {
            string key = "";
            int opt = 1;
            cout << "1. Encode  2. Decode: ";
            cin >> opt;
            cin.ignore();
            cout << "Enter key: ";
            getline(cin, key);
            cout << "Enter text: ";
            getline(cin, text);
            cout << "Result: " << vigenereCipher(text, key, opt == 2) << "\n";
        } else if (choice == 6) {
            int opt = 1;
            cout << "1. ROT13  2. ROT47: ";
            cin >> opt;
            cin.ignore();
            cout << "Enter text: ";
            getline(cin, text);
            if (opt == 2) {
                cout << "Result: " << rot47Cipher(text) << "\n";
            } else {
                cout << "Result: " << caesarCipher(text, 13) << "\n";
            }
        } else if (choice == 7) {
            cout << "Enter text: ";
            getline(cin, text);
            cout << "Result: " << atbashCipher(text) << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        runMenu();
        return 0;
    }

    string mode = "encode";
    string cipherType = "caesar";
    string text = "";
    string key = "";
    string inputFile = "";
    string outputFile = "";
    int shift = 3;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-e" || arg == "--encode") mode = "encode";
        else if (arg == "-d" || arg == "--decode") mode = "decode";
        else if (arg == "-c" || arg == "--crack") mode = "crack";
        else if (arg == "-b" || arg == "--bruteforce") mode = "bruteforce";
        else if (arg == "-k" && i + 1 < argc) {
            key = argv[++i];
            try { shift = stoi(key); } catch (...) { shift = 3; }
        } else if (arg == "-t" && i + 1 < argc) {
            cipherType = argv[++i];
        } else if (arg == "-m" && i + 1 < argc) {
            text = argv[++i];
        } else if (arg == "-f" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        }
    }

    if (text == "" && inputFile != "") {
        ifstream file(inputFile);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                text += line + "\n";
            }
            if (text.length() > 0 && text.back() == '\n') {
                text.pop_back();
            }
            file.close();
        }
    }

    if (text == "") {
        string line;
        while (getline(cin, line)) {
            text += line + "\n";
        }
        if (text.length() > 0 && text.back() == '\n') {
            text.pop_back();
        }
    }

    if (text == "") {
        cout << "No text provided!\n";
        return 1;
    }

    string output = "";
    if (mode == "crack") {
        crackCaesar(text, false);
        return 0;
    } else if (mode == "bruteforce") {
        crackCaesar(text, true);
        return 0;
    } else {
        bool decode = (mode == "decode");
        if (cipherType == "caesar") {
            output = caesarCipher(text, decode ? -shift : shift);
        } else if (cipherType == "vigenere") {
            output = vigenereCipher(text, key, decode);
        } else if (cipherType == "atbash") {
            output = atbashCipher(text);
        } else if (cipherType == "rot13") {
            output = caesarCipher(text, 13);
        } else if (cipherType == "rot47") {
            output = rot47Cipher(text);
        }
    }

    if (outputFile != "") {
        ofstream file(outputFile);
        if (file.is_open()) {
            file << output;
            file.close();
        }
    } else {
        cout << output << "\n";
    }

    return 0;
}
