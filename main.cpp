#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "OrderMatcher.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error: Unable to open input file.\n";
        return 1;
    }

    std::string outputFile = "output" + std::string(argv[1]).substr(5);
    std::ofstream outfile(outputFile);
    if (!outfile) {
        std::cerr << "Error: Unable to open output file.\n";
        return 1;
    }

    double lastTradedPrice;
    infile >> lastTradedPrice;

    OrderMatcher matcher(lastTradedPrice);

    std::string line;
    std::getline(infile, line); // Skip the first line

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string id, type;
        int quantity;
        double price;

        iss >> id >> type >> quantity;
        if (iss >> price) {
            matcher.processOrder(Order(id, type[0], quantity, price, false));
        } else {
            matcher.processOrder(Order(id, type[0], quantity, 0, true));
        }

        std::cout << "Current Order Book:\n";
        matcher.displayOrderBook();
        std::cout << "Last Traded Price: " << std::fixed << std::setprecision(2) << matcher.getLastTradedPrice() << "\n\n";
    }

    matcher.writeExecutionResults(outfile);
    matcher.writeUnexecutedOrders(outfile);

    return 0;
}