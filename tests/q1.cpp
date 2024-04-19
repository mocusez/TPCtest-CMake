#include <iostream>
#include <algorithm>
#include <map>

#include "Table.h"
#include "Structs.h"

#include "Tool.h"


void q1() {

    // begin
    Table<LineItem> lineitemTable;
    lineitemTable.setColumnNames({"L_ORDERKEY", "L_PARTKEY", "L_SUPPKEY", "L_LINENUMBER", "L_QUANTITY", "L_EXTENDEDPRICE", "L_DISCOUNT", "L_TAX", "L_RETURNFLAG", "L_LINESTATUS", "L_SHIPDATE", "L_COMMITDATE", "L_RECEIPTDATE", "L_SHIPINSTRUCT", "L_SHIPMODE", "L_COMMENT"});
    lineitemTable.importData("../data/lineitem.tbl");

    // from
    auto& lineitem = lineitemTable.getData();


    //where
    std::vector<LineItem> lineitem_new;
    for (auto& l : lineitem) {
        if (l.L_SHIPDATE <= "1998-09-02") {
            lineitem_new.push_back(l);
        }
    }

    //group by
    struct AggregateResults {
        double sum_qty = 0.0;
        double sum_base_price = 0.0;
        double sum_disc_price = 0.0;
        double sum_charge = 0.0;
        double sum_discount = 0.0;
        int count_order = 0;
        //后算的
        double avg_qty = 0.0;
        double avg_price = 0.0;
        double avg_disc = 0.0;
    };

    std::map<std::tuple<char, char>, AggregateResults> aggregates;
    for (auto& l : lineitem_new) {
        auto key = std::make_tuple(l.L_RETURNFLAG, l.L_LINESTATUS);
        auto& agg = aggregates[key];
        agg.sum_qty += l.L_QUANTITY;
        agg.sum_base_price += l.L_EXTENDEDPRICE;
        agg.sum_disc_price += l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT);
        agg.sum_charge += l.L_EXTENDEDPRICE * (1 - l.L_DISCOUNT) * (1 + l.L_TAX);
        agg.count_order++;
    }

    // avg
    for (auto& [key, agg] : aggregates) {
        agg.avg_qty = agg.sum_qty/agg.count_order;
        agg.avg_price = agg.sum_base_price/agg.count_order;
        agg.avg_disc = agg.sum_discount/agg.count_order;
    }

    //select
    std::vector<std::tuple<char, char, AggregateResults>> results;
    for (auto& [key, agg] : aggregates) {
        results.push_back({std::get<0>(key), std::get<1>(key), agg});
    }

    //order by
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        if (std::get<0>(a) != std::get<0>(b)) {
            return std::get<0>(a) < std::get<0>(b); // 升序
        }
        return std::get<1>(a) < std::get<1>(b);
    });


    //results是啥类型
    std::cout << "数据类型:\t" <<  typeName<decltype(results)>() << std::endl;

    //print
    for (auto& item : results) {
        char col1 = std::get<0>(item);
        char col2 = std::get<1>(item);
        auto agg = std::get<2>(item);

        std::cout << col1 << " " << col2 << " " << agg.sum_qty << " " << agg.sum_base_price << " " \
        << agg.sum_disc_price << " " << agg.sum_charge << " " << agg.avg_qty << " " << agg.avg_price << " " \
        << agg.avg_disc << " " << agg.count_order << std::endl;
    }
    
}

int main(){
    q1();
}
