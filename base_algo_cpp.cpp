#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>
#include <ctime>
#include <random>


class OrdersManager
{
private:
    // Create a vector of tuples to store the orders in the format (order_id, order_number)
    std::vector<std::tuple<std::string, int>> __orders;

    // Initialise number of orders processed
    int __orders_processed = 0;

    // Initialise last printed log time
    std::time_t __last_printed_log = std::time(0);

public:
    OrdersManager()
    {
        // Initialise the vector of tuples with 1000 orders
        this->__generate_fake_orders(1000);
    }

    void __generate_fake_orders(int quantity)
    {
        this->__log("Generating fake orders");

        // Iterate through loop and generate the vector of tuples <(order_id, order_number)>
        // NOTE: Cannot get UUID without including external library, hence string of
        //       order_number is used instead
        for (int x = 0; x < quantity; x++)
        {
            this->__orders.push_back(std::make_tuple(std::to_string(x), x));
        }

        // Log how many orders were generated 
        this->__log(std::to_string(this->__orders.size()) + " generated...");
    }

    // Logging function to display to console
    void __log(std::string message)
    {
        std::cout << std::to_string(std::time(0)) << " > " << message << std::endl;
    }

    // Process single order function
    // @param
    //      order - tuple of order_id(string) and order_number(int)
    void __fake_save_on_db(std::tuple<std::string, int> order)
    {
        // Destructure tuple to get id and number
        std::string id = std::get<0>(order);
        int number = std::get<1>(order);

        // "Process" the order and log to console
        this->__log("Order [" + id + "] " + std::to_string(number) + " was successfully prosecuted.");

        // Sleep for between 0-1 seconds to simulate processing time
        // NOTE: This uses thread module, however does not do anything with threads
        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 1000));
    }

    // NOTE: Algorithm implementation goes here
    // Process the orders
    void process_orders()
    {
        // Iterate through the vector of tuples
        for (std::tuple<std::string, int> order : this->__orders)
        {  
            // Process the order
            this->__fake_save_on_db(order);

            // Increment the number of orders processed
            this->__orders_processed += 1;

            // Check if 5 seconds have passed since last log
            if (std::time(0) > this->__last_printed_log)
            {
                // Add 5 seconds to last printed log variable
                this->__last_printed_log = std::time(0) + 5;

                // Log total number of orders processed
                this->__log("Total orders executed: " + std::to_string(this->__orders_processed) + "/" + std::to_string(this->__orders.size()));
            }
        }
    }
};

int main()
{
    // Initialise random seed
    std::srand(std::time(0));

    // Initialise orders manager object
    // This runs the constructor which generates the list of fake orders
    OrdersManager orders_manager;

    // Start a timer
    auto start_time = std::time(0);

    // Run the order processing algorithm
    orders_manager.process_orders();

    // End the timer
    auto delay = std::time(0) - start_time;

    // Log the total time taken
    std::cout << std::to_string(std::time(0)) << " > Tiempo de ejecucion: " << std::to_string(delay) << " segundos..." << std::endl;

    // End the program
    return 0;
}
