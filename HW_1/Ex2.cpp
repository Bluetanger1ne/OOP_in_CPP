#include <iostream>
#include <string>
#include <cctype>

int validate_string(const std::string &input);
int validate_character(char c);
bool replacement(std::string &input, char target, char replacement);

int main() {
    std::string command;
    char character_to_find;
    char replacement_character;

    while (true) { // Loop until user enters "Stop" or "stop"
        auto valid_character = false;
        auto valid_replacement = false;
        auto valid_command = false;
        while (!valid_command) { // --------------------------------------------------------------------------- Command validation and saving---------------------
            std::cout << "Please enter a string or \"stop\" to stop" << std::endl;
            std::getline(std::cin, command);
            if (!validate_string(command)) {
                std::cout << "Please only input letters!" << std::endl;
            } else {
                valid_command = true;
            }
        }
        if (command == "stop" || command == "Stop") { // Check if "stop" or "Stop" was entered
            return 0;
        }
        while (!valid_character) { // --------------------------------------------------------------------------- Target character validation and saving---------------------
            std::cout << "Enter a character to find: " << std::endl;
            std::cin >> character_to_find;

            if (!validate_character(character_to_find)) {
                std::cout << "Please only input letters!" << std::endl;
            } else {
                valid_character = true;
            }
        }
        while (!valid_replacement) { // --------------------------------------------------------------- substitute character validation and saving---------------------
            std::cout << "Enter a replacement character " << std::endl;
            std::cin >> replacement_character;
            if (!validate_character(replacement_character)) {
                std::cout << "Please only input letters!" << std::endl;
            } else {
                valid_replacement = true;
            }
        }

        if (replacement(command, character_to_find, replacement_character)) { //Once everything has been verified, perform replacement.
                                                                                      //Print result if any characters were changed
            std::cout << "Result: " << command << std::endl;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}


bool replacement(std::string &input, char target, char replacement) {
    bool swap_happened = false;
    for (char &c: input) {
        if (c == target) {
            c = replacement;
            swap_happened = true;
        }
    }
    return swap_happened;
}

int validate_string(const std::string &input) {
    for (const char c: input) {
        if (!isalpha(c) && c != ' ') {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return 0;
        }
    }
    return 1;
}

int validate_character(char c) {
    if (!isalpha(c)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return 0;
    }
    return 1;
}
