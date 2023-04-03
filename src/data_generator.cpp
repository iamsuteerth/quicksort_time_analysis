#include <iostream>
#include <fstream>
#include <random>

int main() {
    // Define the range of random numbers
    int lower = 1;
    int upper = 100000;

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(lower, upper);

    // Create and open a CSV file for writing
    std::ofstream outputFile("..\\data\\random_numbers_1010k.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open output file!" << std::endl;
        return 1;
    }

    // Generate and write the random numbers to the file
    for (int i = 0; i < 100000; i++) {
        int num = dist(gen);
        outputFile << num << ",";
    }

    // Close the output file
    outputFile.close();

    std::cout << "Random numbers written to file!" << std::endl;

    return 0;
}