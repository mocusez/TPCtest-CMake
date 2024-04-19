#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>

template<typename T>
std::string typeName() {
    int status;
    std::unique_ptr<char, void (*)(void*)> res{
        abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status),
        std::free
    };
    return (status == 0) ? res.get() : "error occurred";
}