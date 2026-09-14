#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <compare>

// -----------------------------------------------------CLASSES-------------------------------------------------------------------------
class Passenger;
class Flight;

class Flight {
public:
    Flight(std::string flight_no_and_name, int max_passengers) {
        this->flight_no_and_name = std::move(flight_no_and_name);
        this->max_passengers = max_passengers;
    }

    bool addPassenger(const std::shared_ptr<Passenger> &passenger);

    bool removePassenger(const std::string &first_name, const std::string &last_name);

    void printPassengers();

    friend std::ostream &operator<<(std::ostream &out, const Flight &flight);

    friend std::ostream &operator<<(std::ostream &out, const Passenger &passenger);

    friend class Passenger;

    auto operator<=>(const Flight &other) const {
        return (max_passengers - passengers.size()) <=>
               (other.max_passengers - other.passengers.size());
    }

private:
    std::string flight_no_and_name;
    int max_passengers;
    std::vector<std::shared_ptr<Passenger> > passengers;
};


class Passenger {
public:
    Passenger(std::string first_name, std::string last_name, int no_of_bags) {
        this->first_name = std::move(first_name);
        this->last_name = std::move(last_name);
        this->no_of_bags = no_of_bags;
    }

    void print_info();

    bool hasName(std::string first_name, std::string last_name) {
        return this->first_name == first_name &&
               this->last_name == last_name;
    }

    void addFlight(const std::shared_ptr<Flight> &flight);

    friend std::ostream &operator<<(std::ostream &out, const Passenger &passenger);

    friend class Flight;

    auto operator<=>(const Passenger &other) const {
        if (auto result = last_name <=> other.last_name; result != 0) {
            return result;
        }
        return first_name <=> other.first_name;
    }

private:
    std::string first_name;
    std::string last_name;
    int no_of_bags;
    std::vector<std::shared_ptr<Flight> > flights;
};

// --------------------------------------------------------------FUNCTIONS ETC---------------------------------------------------

bool Flight::addPassenger(const std::shared_ptr<Passenger> &passenger) {
    if ((this->max_passengers - this->passengers.size()) > 0) {
        passengers.push_back(passenger);
        return true;
    }
    return false;
}

void Passenger::addFlight(const std::shared_ptr<Flight> &flight) {
    flights.push_back(flight);
}

bool Flight::removePassenger(const std::string &first_name, const std::string &last_name) {
    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if ((*it)->hasName(first_name, last_name)) {
            passengers.erase(it);
            return true;
        }
    }
    return false;
}

void Flight::printPassengers() {
    for (const auto &passenger: passengers) {
        std::cout << "\n   Name: " << passenger->first_name
                << " " << passenger->last_name
                << "\n   Number of bags: " << passenger->no_of_bags
                << "\n   Flights on: " << passenger->flights.size()
                << "\n";
    }
}

void Passenger::print_info() {
    std::cout << "   Name: " << first_name;
    std::cout << " " << last_name << "\n";
    std::cout << "   Number of bags: " << no_of_bags << "\n";
    std::cout << "   Flights on:";

    for (const auto &flight: flights) {
        std::cout << " " << flight->flight_no_and_name << ";";
    }

    std::cout << "\n";
}

std::ostream &operator<<(std::ostream &out, const Flight &flight) {
    // Overloaded output operator
    out << "\nName :" << flight.flight_no_and_name << "\n"
            << "Max passengers: " << flight.max_passengers << "\n"
            << "Passengers on flight: " << flight.passengers.size();

    return out;
}

std::ostream &operator<<(std::ostream &out, const Passenger &passenger) {
    // Overloaded output operator
    out << "\n   Name :" << passenger.first_name << " " << passenger.last_name << "\n"
            << "   Number of bags: " << passenger.no_of_bags << "\n"
            << "   Flights on:";

    for (int i = 0; i < passenger.flights.size(); i++) {
        out << " " << passenger.flights[i]->flight_no_and_name;
        if (i < passenger.flights.size() - 1) {
            out << ",";
        }
    }

    return out;
}

// ------------------------------------------------------------------------MAIN--------------------------------------------------------------------
int main() {
    std::vector<std::shared_ptr<Flight> > flights;
    std::vector<std::shared_ptr<Passenger> > passengers;

    int flight_amt;
    int passenger_amt;
    std::string no_and_name;
    int max_pas;

    std::string f_name;
    std::string l_name;
    int bags;

    int flight_to_be_booked_on;

    std::cout << "Please enter number of flights: " << std::endl;
    std::cin >> flight_amt;
    std::cin.clear();
    std::cin.ignore(10000, '\n');

    for (int counter = 0; counter < flight_amt; counter++) {
        std::cout << "Enter the flight number and name for flight no." << counter + 1 << ": ";
        std::getline(std::cin, no_and_name, '\n');

        std::cout << "Enter max passenger amount for flight no." << counter + 1 << ": " << std::endl;
        std::cin >> max_pas;
        std::cin.ignore(10000, '\n');

        flights.push_back(std::make_shared<Flight>(no_and_name, max_pas));
    }

    std::cout << "Please enter number of passengers: " << std::endl;
    std::cin >> passenger_amt;

    for (int passenger = 0; passenger < passenger_amt; passenger++) {
        std::cout << "Please enter first name for passenger no." << passenger + 1 << ": " << std::endl;
        std::cin >> f_name;

        std::cout << "Please enter last name for passenger no." << passenger + 1 << ": " << std::endl;
        std::cin >> l_name;

        std::cout << "Please enter number of bags for passenger no." << passenger + 1 << ": " << std::endl;
        std::cin >> bags;

        passengers.push_back(std::make_shared<Passenger>(f_name, l_name, bags));

        for (int i = 0; i < flights.size(); i++) {
            std::cout << i + 1 << ": " << *flights[i] << std::endl;
        }

        std::cout << "Which flight(s) should " << f_name
                << " be booked on? (Index or press \"0\" to finish): "
                << std::endl;
        std::cin >> flight_to_be_booked_on;

        while (flight_to_be_booked_on != 0) {
            const std::shared_ptr<Passenger> &passenger_ptr = passengers.back();
            const std::shared_ptr<Flight> &flight_ptr = flights[flight_to_be_booked_on - 1];

            if (flight_ptr->addPassenger(passenger_ptr)) {
                std::cout << "Passenger added.\n";
                passenger_ptr->addFlight(flight_ptr);
            } else {
                std::cout << "Flight is full.\n";
            }

            std::cout << "Enter another flight (0 to finish): ";
            std::cin >> flight_to_be_booked_on;
        }
    }

    std::sort(flights.begin(), flights.end(), [](auto &a, auto &b) {
        return *a > *b;
    });
    std::sort(passengers.begin(), passengers.end(), [](auto &a, auto &b) {
        return *a < *b;
    });

    std::cout << "---------Flight information---------" << "\n";

    for (int i = 0; i < flights.size(); i++) {
        std::cout << i + 1 << ". " << *flights[i] << "\n";
        flights[i]->printPassengers();
    }

    std::cout << "---------Passenger information---------" << "\n";

    for (int i = 0; i < passengers.size(); i++) {
        std::cout << i + 1 << ". " << *passengers[i] << "\n";
    }

    return 0;
}
