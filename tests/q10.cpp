#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <tuple>
#include <algorithm>
#include <ctime>

#include "Table.h"
#include "Structs.h"
#include "Tool.h"


void q10() {
    // Import the tables
    Table<Customer> customerTable;
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;
    Table<Nation> nationTable;

    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");
    nationTable.importData("../data/nation.tbl");

    // time
    clock_t start = clock();

    // from
    auto& customers = customerTable.getData();
    auto& orders = ordersTable.getData();
    auto& lineitems = lineItemTable.getData();
    auto& nations = nationTable.getData();

    // Create a nation map for quick access
    std::unordered_map<int, std::string> nationMap;
    for (const auto& n : nations) {
        nationMap[n.N_NATIONKEY] = n.N_NAME;
    }

    // Join and where conditions
    std::vector<std::tuple<int, std::string, double, double, std::string, std::string, std::string, std::string>> results;
    for (const auto& c : customers) {
        for (const auto& o : orders) {
            if (c.C_CUSTKEY == o.O_CUSTKEY &&
                o.O_ORDERDATE >= "1994-05-01" &&
                o.O_ORDERDATE < "1994-08-01") { // 3 months after 1994-05-01
                for (const auto& l : lineitems) {
                    if (l.L_ORDERKEY == o.O_ORDERKEY && l.L_RETURNFLAG == 'R') {
                        double revenue = l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
                        results.emplace_back(c.C_CUSTKEY, c.C_NAME, revenue, c.C_ACCTBAL,
                                             nationMap[c.C_NATIONKEY], c.C_ADDRESS, c.C_PHONE, c.C_COMMENT);
                    }
                }
            }
        }
    }

    // Group by and sum revenues
    std::map<std::tuple<int, std::string, double, std::string, std::string, std::string, std::string>, double> groupedResults;
    for (const auto& r : results) {
        auto key = std::make_tuple(std::get<0>(r), std::get<1>(r), std::get<3>(r), std::get<4>(r),
                                   std::get<5>(r), std::get<6>(r), std::get<7>(r));
        groupedResults[key] += std::get<2>(r);
    }

    // Prepare final sorted results
    std::vector<std::tuple<int, std::string, double, double, std::string, std::string, std::string, std::string>> finalResults;
    for (const auto& grp : groupedResults) {
        finalResults.emplace_back(std::get<0>(grp.first), std::get<1>(grp.first), grp.second, std::get<2>(grp.first),
                                  std::get<3>(grp.first), std::get<4>(grp.first), std::get<5>(grp.first), std::get<6>(grp.first));
    }

    // Sort results by revenue descending
    std::sort(finalResults.begin(), finalResults.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) > std::get<2>(b);
    });

    // time off
    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

    // Output the results
    std::cout << "Results for q10" << std::endl;
    std::cout << "C_CustKey\tC_Name\tRevenue\tC_AcctBal\tN_Name\tC_Address\tC_Phone\tC_Comment\n";
    for (const auto& res : finalResults) {
        std::cout << std::get<0>(res) << "\t" << std::get<1>(res) << "\t" << std::get<2>(res) << "\t"
                  << std::get<3>(res) << "\t" << std::get<4>(res) << "\t" << std::get<5>(res) << "\t"
                  << std::get<6>(res) << "\t" << std::get<7>(res) << std::endl;
    }
}

int main() {
    q10();
    return 0;
}