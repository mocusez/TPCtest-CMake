#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <tuple>
#include <algorithm>

// Include the necessary header files
#include "Table.h"
#include "Structs.h"

void q9() {
    // Import
    Table<Part> partTable;
    Table<Supplier> supplierTable;
    Table<LineItem> lineItemTable;
    Table<PartSupp> partSuppTable;
    Table<Orders> ordersTable;
    Table<Nation> nationTable;

    // Import the tables
    partTable.importData("../data/part.tbl");
    supplierTable.importData("../data/supplier.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    partSuppTable.importData("../data/partsupp.tbl");
    ordersTable.importData("../data/orders.tbl");
    nationTable.importData("../data/nation.tbl");

    // fromS
    auto& parts = partTable.getData();
    auto& suppliers = supplierTable.getData();
    auto& lineitems = lineItemTable.getData();
    auto& partsupps = partSuppTable.getData();
    auto& orders = ordersTable.getData();
    auto& nations = nationTable.getData();

    // Results vector to store tuples of nation, year, and profit amount
    std::vector<std::tuple<std::string, int, double>> results;

    // where and join
    for (const auto& p : parts) {
        if (p.P_NAME.find("dark") != std::string::npos) {
            for (const auto& l : lineitems) {
                if (p.P_PARTKEY == l.L_PARTKEY) {
                    for (const auto& o : orders) {
                        if (o.O_ORDERKEY == l.L_ORDERKEY) {
                            int year = std::stoi(o.O_ORDERDATE.substr(0, 4));
                            for (const auto& s : suppliers) {
                                if (s.S_SUPPKEY == l.L_SUPPKEY) {
                                    for (const auto& ps : partsupps) {
                                        if (ps.PS_SUPPKEY == s.S_SUPPKEY && ps.PS_PARTKEY == p.P_PARTKEY) {
                                            for (const auto& n : nations) {
                                                if (n.N_NATIONKEY == s.S_NATIONKEY) {
                                                    double amount = l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT) - ps.PS_SUPPLYCOST * l.L_QUANTITY;
                                                    results.emplace_back(n.N_NAME, year, amount);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // group by
    std::map<std::tuple<std::string, int>, double> aggregates;
    for (const auto& result : results) {
        auto key = std::make_tuple(std::get<0>(result), std::get<1>(result));
        aggregates[key] += std::get<2>(result);
    }

    // order by
    std::vector<std::tuple<std::string, int, double>> finalResults;
    for (const auto& agg : aggregates) {
        finalResults.emplace_back(std::get<0>(agg.first), std::get<1>(agg.first), agg.second);
    }

    std::sort(finalResults.begin(), finalResults.end(), [](const auto& a, const auto& b) {
        if (std::get<0>(a) == std::get<0>(b))
            return std::get<1>(a) > std::get<1>(b);  // Descending year
        return std::get<0>(a) < std::get<0>(b);
    });

    // Output the results
    std::cout << "Nation\tYear\tSum_Profit\n";
    for (const auto& res : finalResults) {
        std::cout << std::get<0>(res) << "\t" << std::get<1>(res) << "\t" << std::get<2>(res) << std::endl;
    }
}

int main(){
    q9();
}
