#include <iostream>
#include <algorithm>
#include <map>

//表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"
#include "Tool.h"

void q5() {
    // init
    Table<Customer> customerTable;
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;
    Table<Supplier> supplierTable;
    Table<Nation> nationTable;
    Table<Region> regionTable;

    // import
    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    supplierTable.importData("../data/supplier.tbl");
    nationTable.importData("../data/nation.tbl");
    regionTable.importData("../data/region.tbl");

    // from
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();
    auto& lineitems = lineItemTable.getData();
    auto& suppliers = supplierTable.getData();
    auto& nations = nationTable.getData();
    auto& regions = regionTable.getData();

    // join
    std::unordered_map<int, Customer> customerMap;
    for (auto& c : customers) {
        customerMap[c.C_CUSTKEY] = c;
    }

    std::unordered_map<int, std::vector<Orders>> ordersMap;
    for (auto& o : orders) {
        if (o.O_ORDERDATE >= "1995-01-01" && o.O_ORDERDATE < "1996-01-01") {
            ordersMap[o.O_CUSTKEY].push_back(o);
        }
    }

    std::unordered_map<int, std::vector<LineItem>> lineitemMap;
    for (auto& l : lineitems) {
        lineitemMap[l.L_ORDERKEY].push_back(l);
    }

    std::unordered_map<int, Supplier> supplierMap;
    for (auto& s : suppliers) {
        supplierMap[s.S_SUPPKEY] = s;
    }

    std::unordered_map<int, Nation> nationMap;
    for (auto& n : nations) {
        nationMap[n.N_NATIONKEY] = n;
    }

    std::unordered_map<int, Region> regionMap;
    for (auto& r : regions) {
        if (r.R_NAME == "EUROPE") {
            regionMap[r.R_REGIONKEY] = r;
        }
    }

    // 结构体用于存储聚合结果
    struct AggregateResults {
        double revenue = 0.0;
    };

    std::map<std::string, AggregateResults> aggregates;

    // where
    for (auto& s : suppliers) {
        if (regionMap.count(nationMap[s.S_NATIONKEY].N_REGIONKEY)) {
            for (auto& l : lineitemMap[s.S_SUPPKEY]) {
                for (auto& o : ordersMap[customerMap[l.L_PARTKEY].C_CUSTKEY]) {
                    if (o.O_ORDERKEY == l.L_ORDERKEY) {
                        auto& n = nationMap[s.S_NATIONKEY];
                        auto& agg = aggregates[n.N_NAME];
                        agg.revenue += l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
                    }
                }
            }
        }
    }

    // order by
    std::vector<std::pair<std::string, double>> results;
    for (auto& [key, agg] : aggregates) {
        results.emplace_back(key, agg.revenue);
    }
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // print
    std::cout << "aaaa" << std::endl;
    for (auto& [name, revenue] : results) {
        std::cout << name << "\t" << revenue << std::endl;
    }
}

int main(){
    q5();
}
