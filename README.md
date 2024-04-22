# TPCtest

## Suggest Environment

GCC 11

CMake 3.22.1

Git

## Compile

```bash
mkdir build
cmake -B build -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
cmake --build build -j
```

## Test

```bash
cp -r data/ build/
ctest --test-dir build --verbose
rm -rf build/data/
```

