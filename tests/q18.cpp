#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include "Table.h"
#include "Structs.h"

void q18() {
    // Loading data from tables
    Table<Customer> customerTable;
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;

    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    // Get data references
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();
    auto& lineitems = lineItemTable.getData();

    // Subquery equivalent: Finding orders with total quantity > 314
    std::map<int, double> orderQuantities;
    for (const auto& lineitem : lineitems) {
        orderQuantities[lineitem.L_ORDERKEY] += lineitem.L_QUANTITY;
    }

    std::set<int> qualifyingOrderKeys;
    for (const auto& entry : orderQuantities) {
        if (entry.second > 314) {
            qualifyingOrderKeys.insert(entry.first);
        }
    }

    // Grouping data based on order key with the required details
    struct OrderInfo {
        std::string customerName;
        int customerKey;
        int orderKey;
        std::string orderDate;
        double totalPrice;
        double totalQuantity;
    };

    std::map<int, OrderInfo> results;

    for (const auto& order : orders) {
        if (qualifyingOrderKeys.find(order.O_ORDERKEY) != qualifyingOrderKeys.end()) {
            OrderInfo info;
            info.orderKey = order.O_ORDERKEY;
            info.orderDate = order.O_ORDERDATE;
            info.totalPrice = order.O_TOTALPRICE;
            for (const auto& lineitem : lineitems) {
                if (lineitem.L_ORDERKEY == order.O_ORDERKEY) {
                    info.totalQuantity += lineitem.L_QUANTITY;
                }
            }
            for (const auto& customer : customers) {
                if (customer.C_CUSTKEY == order.O_CUSTKEY) {
                    info.customerName = customer.C_NAME;
                    info.customerKey = customer.C_CUSTKEY;
                    break;
                }
            }
            results[order.O_ORDERKEY] = info;
        }
    }

    // Preparing sorted result based on total price and order date
    std::vector<OrderInfo> sortedResults;
    for (const auto& entry : results) {
        sortedResults.push_back(entry.second);
    }

    std::sort(sortedResults.begin(), sortedResults.end(), [](const OrderInfo& a, const OrderInfo& b) {
        if (a.totalPrice != b.totalPrice) return a.totalPrice > b.totalPrice;
        return a.orderDate < b.orderDate;
    });

    // Display top 100 results
    int count = 0;
    for (const auto& result : sortedResults) {
        if (++count > 100) break;
        std::cout << result.customerName << ", " << result.customerKey << ", "
                  << result.orderKey << ", " << result.orderDate << ", "
                  << result.totalPrice << ", " << result.totalQuantity << std::endl;
    }
}

int main(){
    q18();
}