#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <ctime>

#include "Table.h" 
#include "Structs.h"
#include "Tool.h"


int extractYear(const std::string& dateStr) {
    // Assuming dateStr is in the format "YYYY-MM-DD"
    return std::stoi(dateStr.substr(0, 4));
}

void q8() {
    Table<Part> partTable;
    Table<Supplier> supplierTable;
    Table<LineItem> lineItemTable;
    Table<Orders> ordersTable;
    Table<Customer> customerTable;
    Table<Nation> nationTable;
    Table<Region> regionTable;

    partTable.importData("../data/part.tbl");
    supplierTable.importData("../data/supplier.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    ordersTable.importData("../data/orders.tbl");
    customerTable.importData("../data/customer.tbl");
    nationTable.importData("../data/nation.tbl");
    regionTable.importData("../data/region.tbl");

    // time
    clock_t start = clock();

    // from
    auto& parts = partTable.getData();
    auto& suppliers = supplierTable.getData();
    auto& lineitems = lineItemTable.getData();
    auto& orders = ordersTable.getData();
    auto& customers = customerTable.getData();
    auto& nations = nationTable.getData();
    auto& regions = regionTable.getData();

    std::unordered_map<int, std::string> nationMap;
    for (const auto& n : nations) {
        nationMap[n.N_NATIONKEY] = n.N_NAME;
    }

    std::unordered_map<int, std::string> regionMap;
    for (const auto& r : regions) {
        regionMap[r.R_REGIONKEY] = r.R_NAME;
    }

    std::vector<std::tuple<int, double, std::string>> tempResults;
    for (const auto& p : parts) {
        if (p.P_TYPE == "SMALL PLATED TIN") {
            for (const auto& l : lineitems) {
                if (p.P_PARTKEY == l.L_PARTKEY) {
                    for (const auto& s : suppliers) {
                        if (s.S_SUPPKEY == l.L_SUPPKEY) {
                            for (const auto& o : orders) {
                                if (o.O_ORDERKEY == l.L_ORDERKEY && l.L_SHIPDATE >= "1995-01-01" && l.L_SHIPDATE <= "1996-12-31") {
                                    for (const auto& c : customers) {
                                        if (c.C_CUSTKEY == o.O_CUSTKEY && nationMap[c.C_NATIONKEY] == nationMap[s.S_NATIONKEY] && regionMap[nations[c.C_NATIONKEY].N_REGIONKEY] == "MIDDLE EAST") {
                                            int year = std::stoi(o.O_ORDERDATE.substr(0, 4));
                                            double volume = l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
                                            std::string nation = nationMap[s.S_NATIONKEY];
                                            tempResults.emplace_back(year, volume, nation);
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

    std::map<int, std::pair<double, double>> results; // year, (IRAQ_volume_sum, total_volume_sum)
    for (const auto& result : tempResults) {
        int year = std::get<0>(result);
        double volume = std::get<1>(result);
        std::string nation = std::get<2>(result);
        results[year].second += volume; // sum
        if (nation == "IRAQ") {
            results[year].first += volume; // IRAQ sum
        }
    }

    // time off
    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

    std::cout << "q8 results\n";
    std::cout << "O_Year\tMarket_Share\n";
    for (const auto& res : results) {
        double mkt_share = (res.second.first / res.second.second) * 100;
        std::cout << res.first << "\t" << mkt_share << "%\n";
    }
}


int main() {
    q8();
    return 0;
}
