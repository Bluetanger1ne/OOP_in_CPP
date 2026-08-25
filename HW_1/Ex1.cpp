#include <iostream>
#include <vector>
#include <iomanip>


int main() {
    std::cout << "How many numbers do you want to enter?" << std::endl;
    int size = 0;
    double sum = 0;
    while (!(std::cin >> size)) { // Validating user input
        std::cout << "Invalid input. How many numbers would you like to input?: " << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::vector<double> number(size, 0.0);


    for (int i = 0; i < size; i++) { // Loop for asking user to input numbers according to amount specified earlier
        std::cout << "Please enter No.[" << i + 1 << "]: " << std::endl;
        double element;
        while (!(std::cin >> element)) { // Validating user input
            std::cout << "Invalid input. Please enter a number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        sum += element;
        number[i] = element;
    }

    std::cout << "You entered: ";
    for (int i = 0; i < size; i++) {
        std::cout << std::fixed << std::setprecision(4);;
        std::cout << number[i] << ", ";
    }
    std::cout << "Sum = " << sum << std::endl;

    return 0;
}
