# File:
```
TPCtest
├── README.md
├── TPC-H V3.0.1    ptch数据生成，sql生成模块
├── build_support   一些脚本
├── data            数据文件 .tbl 格式
├── help            参考资料
├── other           老旧代码，暂不使用
├── query           查询文件 .sql 格式
├── self_git.sh     git提交脚本 $1 提交信息 $2 push?
├── src             c++代码
└── test            psql测试
```

# Outlines

## 1. Generate data
通过使用dbgen工具生成TPC-H测试数据8个表 .tbl文件 存入data文件夹下。

通过使用qgen工具生成TPC-H测试的22个查询 .sql文件 存入query文件夹下。

## 2. Select some queries
目前选择了query1.sql

## 3. Hardcode code VS psql run
1.将query1.sql中的查询语句 以及需要的表 硬编码到代码中 src/q1.cpp

2.在psql导入表数据，运行new_query1.sql （.tbl格式问题，需要预处理）

3.运行代码，输出结果（需要将结果与psql的结果进行比对，以验证代码的正确性）

## 4. Compile/JIT the code
llvm编译器编译代码


#about TPC-H file
```
├── EULA.txt: TPC-H测试的最终用户许可协议。
├── dbgen: 数据库生成工具的源代码。
├── dev-tools: 用于生成TPC-H测试数据的工具。
├── ref_data: 用于验证TPC-H测试结果的参考数据。
├── specification.docx: TPC-H测试的基准规范。
└── specification.pdf: TPC-H测试的基准规范-pdf。
```

# Flow path
1 进入TPCtest/TPC-H V3.0.1/dbgen 目录编译dbgen工具，
你需要进入Makefile文件中的100行来调整你的编译时各个参数来确保代码正确编译（我已调整参数基于linux的gcc编译模式）。
完成相应的参数配置后即可运行make命令编译dbgen工具。
```
cd TPCtest/TPC-H V3.0.1/dbgen
make
```

2 生成数据
通过使用dbgen工具生成TPC-H测试数据，8个表
其中-s参数指定生成数据的规模，这里我们暂时生成规模为0.001 （总计3000左右数据）
```
./dbgen -s 0.001
```
生成文件在dbgen目录下 *.tbl

3 生成query
使用qgen工具生成TPC-H测试的22个查询，
其中-q参数指定生成查询的编号，这里我们生成查询编号为1的查询。
```
cd TPCtest/TPC-H V3.0.1
./qgen
```
生成文件在dbgen目录下 *.sql
