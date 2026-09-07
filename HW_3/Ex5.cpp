#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <compare>


class Item {
public:
    Item() {}; //Default constructor
    Item(std::string name, int weight, double price, int discount) { // Constructor
        this->name = name;
        this->weight = weight;
        this->price = price;
        this->discount = discount;
    }

    friend std::ostream &operator<<(std::ostream &out, const Item &item); // Output operator
    friend std::istream &operator>>(std::istream &in, Item &item); // Input operator

    int getDiscount() const {
        return discount;
    }
    void setDiscount(int d) {
        if (d >= 0 && d <= 100) {
            discount = d;
        }
    }
    double getPrice() const {
        return price * (100 - getDiscount()) / 100.0;
    }
    void setPrice(double p) {
        price = p;
    }

    auto operator<=>(const Item &other) const {
        return (getPrice() / (weight / 1000.0)) <=> (other.getPrice() / (other.weight / 1000.0));
    }

    bool operator==(const Item &other) const {
        double pricePerKg = getPrice() / (weight / 1000.0);
        double otherPricePerKg = other.getPrice() / (other.weight / 1000.0);

        return pricePerKg == otherPricePerKg;
    }

private:
    std::string name;
    int weight = 0;
    double price = 0.0;
    int discount = 0;
};


std::ostream &operator<<(std::ostream &out, const Item &item) {
    out << "{ \"Name\":\"" << item.name
            << "\", \"Weight\":" << item.weight
            << ", \"Price\":" << item.price
            << ", \"Discount\": " << item.discount
            << " }";

    return out;
}

std::istream &operator>>(std::istream &in, Item &item) {
    std::string line;
    std::getline(in >> std::ws, line); // get line and ignore white space.

    std::size_t nameStart = line.find("\"Name\":\""); // find name location
    std::size_t nameEnd = line.find("\",", nameStart);

    std::size_t weightStart = line.find("\"Weight\":", nameEnd); // find weight location
    std::size_t weightEnd = line.find(",", weightStart);

    std::size_t priceStart = line.find("\"Price\":", weightEnd); //find price location
    std::size_t priceEnd = line.find(",", priceStart);

    std::size_t discountStart = line.find("\"Discount\":", priceEnd); // find discount location
    std::size_t discountEnd = line.find("}", discountStart);

    if (nameStart == std::string::npos || // Check that data is formatted correctly
        nameEnd == std::string::npos ||
        weightStart == std::string::npos ||
        weightEnd == std::string::npos ||
        priceStart == std::string::npos ||
        priceEnd == std::string::npos ||
        discountStart == std::string::npos ||
        discountEnd == std::string::npos) {

        in.setstate(std::ios::failbit);
        return in;
        }

    std::string name = line.substr(nameStart + 8,nameEnd - (nameStart + 8));

    try {
        int weight = std::stoi(line.substr(weightStart + 9,weightEnd - (weightStart + 9)));
        double price = std::stod(line.substr(priceStart + 8,priceEnd - (priceStart + 8)));
        int discount = std::stoi(line.substr(discountStart + 11,discountEnd - (discountStart + 11)));
        item = Item(name, weight, price, discount);
    }
    catch (...) {
        in.setstate(std::ios::failbit);
    }
    return in;
}


int main() {
    std::vector<Item> items;
    std::string name;
    bool asking = true;
    int weight;
    double price;
    int discount;
    while (asking) {
        std::cout << "please enter the name of the item, \"json\" for JSON formatted data, or \"stop\" to stop: " << std::endl;
        std::getline(std::cin,name,'\n');
        if (!std::cin) {
            std::cout << "Input failed!" << std::endl;
            break;
        }
        if (name == "stop") {
            asking = false;

        } else if (name == "json") {
            std::cout << "Please enter the JSON string: \n" << std::endl;
            Item item;
            std::cin >> item;
            if (!std::cin) {
                std::cout << "Input failed!" << std::endl;
                std::cin.clear();
            } else {
                items.push_back(item);
            }
        } else {
            std::cout << "please enter the weight of the item: " << std::endl;
            std::cin >> weight;

            std::cout << "please enter the price of the item: " << std::endl;
            std::cin >> price;

            std::cout << "please enter discount of the item: " << std::endl;
            std::cin >> discount;

            Item item(name, weight, price, discount);
            items.push_back(item);
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
    std::sort(items.begin(), items.end()); // Sort the items and display them with index numbers.
    for (int i = 0; i < items.size(); i++) {
        std::cout << i+1 << ": " << items[i] << std::endl;
    }
    double total = 0;

    for (auto &item: items) { // Get the prices for each item and them to the net worth.
        double p = item.getPrice();
        total += p;
    }
    std::cout << "\nNet worth: " << total << "\n" <<std::endl;

    while (true) {
        std::string choice;

        std::cout << "Choose an item by index or enter \"stop\" to stop: ";
        std::cin >> choice;
        if (choice == "stop") {
            return 0;
        }
        int index = std::stoi(choice);
        if (index < 1 || index > items.size()) {
            std::cout << "Enter a valid index please..!" << std:: endl;
        } else {
            int disc;

            std::cout << "Enter discount percentage: ";
            std::cin >> disc;

            items[index-1].setDiscount(disc);

            std::sort(items.begin(), items.end());
        }
        for (int i = 0; i < items.size(); i++) {
            std::cout << i+1 << ": " << items[i] << std::endl;
        }
        double total2 = 0;

        for (const auto &item : items) {
            total2 += item.getPrice();
        }

        std::cout << "\nNet worth: " << total2 << "\n" << std::endl;
    }

}
