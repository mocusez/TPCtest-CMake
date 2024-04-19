#include <iostream>
#include <algorithm>
#include <map>

//表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"
#include "Tool.h"


void q3() {

    // begin
    Table<Customer> customerTable;
    Table<Orders> ordersTable;
    Table<LineItem> lineItemTable;
    customerTable.importData("../data/customer.tbl");
    ordersTable.importData("../data/orders.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    // from
    auto& customer = customerTable.getData();
    auto& orders = ordersTable.getData();
    auto& lineitem = lineItemTable.getData();

    //where
    std::vector<Customer> customer_new;
    std::vector<Orders> orders_new;
    std::vector<LineItem> lineitem_new;

    for(auto& c : customer) {
        if (c.C_MKTSEGMENT == "AUTOMOBILE") {
            customer_new.push_back(c);
        }
    }

    for (auto& o : orders) {
        if (o.O_ORDERDATE < "1995-03-14") {
            orders_new.push_back(o);
        }
    }

    for (auto& l : lineitem) {
        if (l.L_SHIPDATE > "1995-03-14") {
            lineitem_new.push_back(l);
        }
    }

    //join
    // 建立哈希表1
    std::unordered_map<int, Orders> orderKeyMap;
    for (auto& o : orders_new) {
        orderKeyMap[o.O_ORDERKEY] = o;
    }

    std::vector<std::pair<Orders, LineItem>> join_1;
    for (auto& l : lineitem_new) {
        auto it = orderKeyMap.find(l.L_ORDERKEY);
        if (it != orderKeyMap.end()) {
            join_1.push_back({it->second, l});
        }
    }

    // 建立哈希表2
    std::unordered_map<int, Customer> custKeyMap;
    for (auto& c : customer_new) {
        custKeyMap[c.C_CUSTKEY] = c;
    }

    std::vector<std::tuple<Customer, Orders, LineItem>> join_2;
    for (auto& [o, l] : join_1) {
        auto it = custKeyMap.find(o.O_CUSTKEY);
        if (it != custKeyMap.end()) {
            join_2.push_back({it->second, o, l});
        }
    }

    //group by
    struct AggregateResults {
        double revenue = 0.0;
    };

    std::map<std::tuple<int, std::string, std::string>, AggregateResults> aggregates;
    for (auto& [c, o, l] : join_2) {
        auto key = std::make_tuple(c.C_NATIONKEY, o.O_ORDERDATE, l.L_SHIPDATE);
        auto& agg = aggregates[key];
        agg.revenue += l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
    }


    // avg


    //select
    std::vector<std::tuple<int, double, std::string, std::string>> results;
    for (auto& [key, agg] : aggregates) {
        results.push_back({std::get<0>(key), agg.revenue, std::get<1>(key), std::get<2>(key)});
    }

    //order by
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        if (std::get<1>(a) != std::get<1>(b)) {
            return std::get<1>(a) > std::get<1>(b); // revenue 降序
        }
        return std::get<2>(a) < std::get<2>(b); // 字符串字段升序
    });


    //打印results是啥类型
    std::cout << "数据类型:\t" <<  typeName<decltype(results)>() << std::endl;

    //print
    std::cout << "---------打印结果-------\n" << std::endl;
    for (auto& item : results) {
        int col1 = std::get<0>(item);
        double col2 = std::get<1>(item);
        std::string col3 = std::get<2>(item);
        std::string col4 = std::get<3>(item);
        std::cout << col1 << "\t" << col2 << "\t" << col3 << "\t" << col4 << std::endl;
    }
}

int main(){
    q3();
}
