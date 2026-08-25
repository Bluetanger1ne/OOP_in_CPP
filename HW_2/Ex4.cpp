#include <iostream>
#include <deque>


class RunningAverage {
    public:
        RunningAverage(int size);
        void add_value(int value);
        double get_average();
    private:
        std::deque<int> d;
        int max_size;

};

//-------------------------------------------------------------Member function definitions------------------------------
RunningAverage::RunningAverage(int size) : max_size(size) {
}

void RunningAverage::add_value(int value) {
    if (d.size() == max_size) {
        d.pop_front();
    }
    d.push_back(value);
}

double RunningAverage::get_average(){
    double sum = 0.0;
    int amount = 0;
    for (int digit: d) {
        sum += digit;
        amount ++;
    }
    double average = sum /amount;

    return average;
}
//-------------------------------------------------------------Main program loop----------------------------------------
int main() {
    RunningAverage Average(5);
    while (true) { // Loop until user enters "0"
        int number = 0;
        std::cout << "Enter numbers or  \"0\" to stop" << std::endl;
        std::cin >> number;
        if (number == 0) { // Check if the number is 0
            std::cout << "Current average: " << Average.get_average() << std::endl;
            return 0;
        }
        Average.add_value(number); // If non 0, add to deque
        std::cout << "Current average: " << Average.get_average() << std::endl;

    }
}