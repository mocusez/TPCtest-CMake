#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <tuple>
#include <algorithm>

//表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"
//扩展的工具函数
#include "Tool.h"

void q7() {
    // Import the tables
    Table<Supplier> supplierTable;
    Table<LineItem> lineItemTable;
    Table<Orders> ordersTable;
    Table<Customer> customerTable;
    Table<Nation> nationTable;

    // Import 
    supplierTable.importData("../data/supplier.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    ordersTable.importData("../data/orders.tbl");
    customerTable.importData("../data/customer.tbl");
    nationTable.importData("../data/nation.tbl");

    //from 
    auto& suppliers = supplierTable.getData();
    auto& lineitems = lineItemTable.getData();
    auto& orders = ordersTable.getData();
    auto& customers = customerTable.getData();
    auto& nations = nationTable.getData();

    // join
    std::unordered_map<int, std::string> nationMap;
    for (const auto& n : nations) {
        nationMap[n.N_NATIONKEY] = n.N_NAME;
    }

    // Join and where
    std::vector<std::tuple<std::string, std::string, int, double>> results;
    for (const auto& s : suppliers) {
        for (const auto& l : lineitems) {
            if (s.S_SUPPKEY == l.L_SUPPKEY) {
                for (const auto& o : orders) {
                    if (o.O_ORDERKEY == l.L_ORDERKEY) {
                        for (const auto& c : customers) {
                            if (c.C_CUSTKEY == o.O_CUSTKEY) {
                                std::string suppNation = nationMap[s.S_NATIONKEY];
                                std::string custNation = nationMap[c.C_NATIONKEY];
                                if (((suppNation == "ARGENTINA" && custNation == "IRAQ") || 
                                     (suppNation == "IRAQ" && custNation == "ARGENTINA")) && 
                                     (l.L_SHIPDATE >= "1995-01-01" && l.L_SHIPDATE <= "1996-12-31")) {
                                    int year = std::stoi(l.L_SHIPDATE.substr(0, 4));
                                    double volume = l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
                                    results.emplace_back(suppNation, custNation, year, volume);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Group by 
    std::map<std::tuple<std::string, std::string, int>, double> aggregates;
    for (const auto& r : results) {
        auto key = std::make_tuple(std::get<0>(r), std::get<1>(r), std::get<2>(r));
        aggregates[key] += std::get<3>(r);
    }

    // order by
    std::vector<std::tuple<std::string, std::string, int, double>> finalResults;
    for (const auto& agg : aggregates) {
        finalResults.emplace_back(std::get<0>(agg.first), std::get<1>(agg.first), std::get<2>(agg.first), agg.second);
    }
    std::sort(finalResults.begin(), finalResults.end());

    // Output the results
    std::cout << "Supp_Nation\tCust_Nation\tYear\tRevenue\n";
    for (const auto& res : finalResults) {
        std::cout << std::get<0>(res) << "\t" << std::get<1>(res) << "\t" << std::get<2>(res) << "\t" << std::get<3>(res) << std::endl;
    }
}

int main(){
    q7();
}
