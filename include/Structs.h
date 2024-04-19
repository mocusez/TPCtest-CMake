// Structs.h
#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <sstream>

/*
    * Structs.h
    * 定义一些结构体，用于模仿数据库建表
    * 该文件还需要定义模板函数，用于将字符串转换为特定类型
*/


// 定义一个结构体模仿数据库建表
struct MyStruct {
    int id;
    std::string name;
};

struct Customer {
    int C_CUSTKEY;
    std::string C_NAME;
    std::string C_ADDRESS;
    int C_NATIONKEY;
    std::string C_PHONE;
    float C_ACCTBAL;
    std::string C_MKTSEGMENT;
    std::string C_COMMENT;
};

struct LineItem {
    int L_ORDERKEY;
    int L_PARTKEY;
    int L_SUPPKEY;
    int L_LINENUMBER;
    float L_QUANTITY;
    float L_EXTENDEDPRICE;
    float L_DISCOUNT;
    float L_TAX;
    char L_RETURNFLAG;
    char L_LINESTATUS;
    std::string L_SHIPDATE;  // DATE
    std::string L_COMMITDATE; // DATE
    std::string L_RECEIPTDATE; // DATE
    std::string L_SHIPINSTRUCT;
    std::string L_SHIPMODE;
    std::string L_COMMENT;
};

struct Nation {
    int N_NATIONKEY;
    std::string N_NAME;
    int N_REGIONKEY;
    std::string N_COMMENT;
};

struct Orders {
    int O_ORDERKEY;
    int O_CUSTKEY;
    char O_ORDERSTATUS;
    float O_TOTALPRICE;
    std::string O_ORDERDATE;  // DARE
    std::string O_ORDERPRIORITY;
    std::string O_CLERK;
    int O_SHIPPRIORITY;
    std::string O_COMMENT;
};

struct Part {
    int P_PARTKEY;
    std::string P_NAME;
    std::string P_MFGR;
    std::string P_BRAND;
    std::string P_TYPE;
    int P_SIZE;
    std::string P_CONTAINER;
    float P_RETAILPRICE;
    std::string P_COMMENT;
};

struct PartSupp {
    int PS_PARTKEY;
    int PS_SUPPKEY;
    int PS_AVAILQTY;
    float PS_SUPPLYCOST;
    std::string PS_COMMENT;
};

struct Region {
    int R_REGIONKEY;
    std::string R_NAME;
    std::string R_COMMENT;
};

struct Supplier {
    int S_SUPPKEY;
    std::string S_NAME;
    std::string S_ADDRESS;
    int S_NATIONKEY;
    std::string S_PHONE;
    float S_ACCTBAL;
    std::string S_COMMENT;
};

// 定义一个模板函数，用于将特定类型转换为字符串 -----------------------------------------------------------

// 定义一个模板函数，用于将字符串转换为特定类型
template<typename T>
T convertToT(const std::string& value);

template<>
MyStruct convertToT<MyStruct>(const std::string& value) {
    std::istringstream iss(value);
    MyStruct ms;

    std::string part;
    std::getline(iss, part, '|');
    ms.id = std::stoi(part);
    std::getline(iss, ms.name, '|');
    return ms;
}


// 特化模板函数为 Nation 类型
template<>
Nation convertToT<Nation>(const std::string& value) {
    std::istringstream iss(value);
    Nation n;

    std::string part;
    std::getline(iss, part, '|');
    n.N_NATIONKEY = std::stoi(part);
    std::getline(iss, n.N_NAME, '|');
    std::getline(iss, part, '|');
    n.N_REGIONKEY = std::stoi(part);
    std::getline(iss, n.N_COMMENT, '|');

    return n;
}

// 特化模板函数为 Customer 类型
template<>
Customer convertToT<Customer>(const std::string& value) {
    std::istringstream iss(value);
    Customer c;
    std::string part;

    std::getline(iss, part, '|');
    c.C_CUSTKEY = std::stoi(part);
    std::getline(iss, c.C_NAME, '|');
    std::getline(iss, c.C_ADDRESS, '|');
    std::getline(iss, part, '|');
    c.C_NATIONKEY = std::stoi(part);
    std::getline(iss, c.C_PHONE, '|');
    std::getline(iss, part, '|');
    c.C_ACCTBAL = std::stof(part);
    std::getline(iss, c.C_MKTSEGMENT, '|');
    std::getline(iss, c.C_COMMENT, '|');

    return c;
}

// 特化模板函数为 LineItem 类型
template<>
LineItem convertToT<LineItem>(const std::string& value) {
    std::istringstream iss(value);
    LineItem l;
    std::string part;

    std::getline(iss, part, '|');
    l.L_ORDERKEY = std::stoi(part);
    std::getline(iss, part, '|');
    l.L_PARTKEY = std::stoi(part);
    std::getline(iss, part, '|');
    l.L_SUPPKEY = std::stoi(part);
    std::getline(iss, part, '|');
    l.L_LINENUMBER = std::stoi(part);
    std::getline(iss, part, '|');
    l.L_QUANTITY = std::stof(part);
    std::getline(iss, part, '|');
    l.L_EXTENDEDPRICE = std::stof(part);
    std::getline(iss, part, '|');
    l.L_DISCOUNT = std::stof(part);
    std::getline(iss, part, '|');
    l.L_TAX = std::stof(part);
    std::getline(iss, part, '|');
    l.L_RETURNFLAG = part[0];
    std::getline(iss, part, '|');
    l.L_LINESTATUS = part[0];
    std::getline(iss, l.L_SHIPDATE, '|');
    std::getline(iss, l.L_COMMITDATE, '|');
    std::getline(iss, l.L_RECEIPTDATE, '|');
    std::getline(iss, l.L_SHIPINSTRUCT, '|');
    std::getline(iss, l.L_SHIPMODE, '|');
    std::getline(iss, l.L_COMMENT, '|');

    return l;
}

// 特化模板函数为 Orders 类型
template<>
Orders convertToT<Orders>(const std::string& value) {
    std::istringstream iss(value);
    Orders o;
    std::string part;

    std::getline(iss, part, '|');
    o.O_ORDERKEY = std::stoi(part);
    std::getline(iss, part, '|');
    o.O_CUSTKEY = std::stoi(part);
    std::getline(iss, part, '|');
    o.O_ORDERSTATUS = part[0];
    std::getline(iss, part, '|');
    o.O_TOTALPRICE = std::stof(part);
    std::getline(iss, o.O_ORDERDATE, '|');
    std::getline(iss, o.O_ORDERPRIORITY, '|');
    std::getline(iss, o.O_CLERK, '|');
    std::getline(iss, part, '|');
    o.O_SHIPPRIORITY = std::stoi(part);
    std::getline(iss, o.O_COMMENT, '|');

    return o;
}

// 特化模板函数为 Part 类型
template<>
Part convertToT<Part>(const std::string& value) {
    std::istringstream iss(value);
    Part p;
    std::string part;

    std::getline(iss, part, '|');
    p.P_PARTKEY = std::stoi(part);
    std::getline(iss, p.P_NAME, '|');
    std::getline(iss, p.P_MFGR, '|');
    std::getline(iss, p.P_BRAND, '|');
    std::getline(iss, p.P_TYPE, '|');
    std::getline(iss, part, '|');
    p.P_SIZE = std::stoi(part);
    std::getline(iss, p.P_CONTAINER, '|');
    std::getline(iss, part, '|');
    p.P_RETAILPRICE = std::stof(part);
    std::getline(iss, p.P_COMMENT, '|');

    return p;
}

// 特化模板函数为 PartSupp 类型
template<>
PartSupp convertToT<PartSupp>(const std::string& value) {
    std::istringstream iss(value);
    PartSupp ps;
    std::string part;

    std::getline(iss, part, '|');
    ps.PS_PARTKEY = std::stoi(part);
    std::getline(iss, part, '|');
    ps.PS_SUPPKEY = std::stoi(part);
    std::getline(iss, part, '|');
    ps.PS_AVAILQTY = std::stoi(part);
    std::getline(iss, part, '|');
    ps.PS_SUPPLYCOST = std::stof(part);
    std::getline(iss, ps.PS_COMMENT, '|');

    return ps;
}

// 特化模板函数为 Region 类型
template<>
Region convertToT<Region>(const std::string& value) {
    std::istringstream iss(value);
    Region r;
    std::string part;

    std::getline(iss, part, '|');
    r.R_REGIONKEY = std::stoi(part);
    std::getline(iss, r.R_NAME, '|');
    std::getline(iss, r.R_COMMENT, '|');

    return r;
}

// 特化模板函数为 Supplier 类型
template<>
Supplier convertToT<Supplier>(const std::string& value) {
    std::istringstream iss(value);
    Supplier s;
    std::string part;

    std::getline(iss, part, '|');
    s.S_SUPPKEY = std::stoi(part);
    std::getline(iss, s.S_NAME, '|');
    std::getline(iss, s.S_ADDRESS, '|');
    std::getline(iss, part, '|');
    s.S_NATIONKEY = std::stoi(part);
    std::getline(iss, s.S_PHONE, '|');
    std::getline(iss, part, '|');
    s.S_ACCTBAL = std::stof(part);
    std::getline(iss, s.S_COMMENT, '|');

    return s;
}

// 定义一个模板函数，用于将特定类型转换为字符串 -----------------------------------------------------------
#endif // STRUCTS_H
