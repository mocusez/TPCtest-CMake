# TPCtest

## Suggest Environment

LLVM

Clang 14 or G++ 11

CMake 3.22.1

Git

Python3

## Compile&Build
### Clang
```bash
mkdir build
cmake -B build -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
cmake --build build -j
```

### G++
```bash
mkdir build
cmake -B build -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++
cmake --build build -j
```

## AOT-Test

```bash
cp -r data/ build/
ctest --test-dir build --verbose
rm -rf build/data/
```

## JIT-Test

```bash
python3 jit/compile_bc.py
python3 jit/compile_bc.py
```

