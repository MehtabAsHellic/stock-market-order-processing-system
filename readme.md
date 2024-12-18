## Project Overview
This project is a simulation of a stock market order processing system. It is designed to handle trade orders for a specific company's shares, allowing users to place buy and sell orders, which are then matched and executed based on predefined rules. The program emphasizes file handling, the use of STL containers, and general C++ programming skills.

## Purpose
The purpose of this assignment is to assess students' understanding of file handling, data structures, and algorithm design in C++. By simulating a simplified stock market, students will gain practical experience in managing orders, executing trades, and handling various order types (limit and market orders).

## Key Features
- **Order Types**: Supports both buying and selling orders, including limit and market orders.
- **Order Matching**: Implements a matching algorithm that pairs buy and sell orders based on price and arrival time.
- **Execution Logic**: Determines execution prices based on the type of orders matched and updates the order book accordingly.
- **File Input/Output**: Reads orders from an input file and writes execution results and unexecuted orders to an output file.

## How to Run the Program
1. Compile the program using the provided Makefile:

   make

   g++ -std=c++11 -o main main.cpp Order.cpp OrderBook.cpp OrderMatcher.cpp

2. Run the executable with an input file:

    ./main input1.txt
    [Replace input1.txt with the desired input file name.]

## Input Format
The input file should contain:

The first line: A floating-point number representing the last traded price.
Subsequent lines: Each line represents an order with the following format:

    <order_id> <B/S> <quantity> [<limit_price>]

<order_id>: Unique identifier for the order.
<B/S>: Indicates whether the order is a buy (B) or sell (S).
<quantity>: Number of shares to buy/sell.
<limit_price>: (Optional) The price limit for the order. If omitted, the order is treated as a market order.

## Output Format
The program generates an output file named output#.txt, where # corresponds to the input file number. The output includes:

Details of executed orders.
The latest trading price.
Any unexecuted orders at the end of processing.