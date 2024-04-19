#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <numeric>
#include "Table.h"
#include "Structs.h"

void q22() {
    // Load data
    Table<Customer> customerTable;
    Table<Orders> ordersTable;

    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");

    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();

    // Step 1: Find customers with no orders
    std::set<int> customerWithOrders;
    for (const auto& order : orders) {
        customerWithOrders.insert(order.O_CUSTKEY);
    }

    // Step 2: Calculate the average account balance for each country code
    std::map<std::string, std::vector<double>> balancesForAvg;
    for (const auto& customer : customers) {
        std::string countryCode = customer.C_PHONE.substr(0, 2);
        if (countryCode == "22" || countryCode == "25" || countryCode == "11" ||
            countryCode == "33" || countryCode == "32" || countryCode == "13" || countryCode == "20") {
            if (customer.C_ACCTBAL > 0) {
                balancesForAvg[countryCode].push_back(customer.C_ACCTBAL);
            }
        }
    }

    std::map<std::string, double> avgBalance;
    for (const auto& entry : balancesForAvg) {
        avgBalance[entry.first] = std::accumulate(entry.second.begin(), entry.second.end(), 0.0) / entry.second.size();
    }

    // Step 3: Select customers based on the average account balance and absence of orders
    std::map<std::string, std::pair<int, double>> results;
    for (const auto& customer : customers) {
        std::string countryCode = customer.C_PHONE.substr(0, 2);
        if ((countryCode == "22" || countryCode == "25" || countryCode == "11" ||
             countryCode == "33" || countryCode == "32" || countryCode == "13" || countryCode == "20") &&
            customer.C_ACCTBAL > avgBalance[countryCode] &&
            customerWithOrders.find(customer.C_CUSTKEY) == customerWithOrders.end()) {
            results[countryCode].first += 1;
            results[countryCode].second += customer.C_ACCTBAL;
        }
    }

    // Step 4: Output results
    for (const auto& result : results) {
        std::cout << result.first << " - " << result.second.first << " customers, "
                  << result.second.second << " total account balance" << std::endl;
    }
}

int main(){
    q22();
}

