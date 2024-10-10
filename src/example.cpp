#include <cstdint>
#include <iostream>
#include <vector>

#include "nic-collector.hpp"

int main() {
    auto adapters = get_adapters();
    for (const auto& adapter : adapters) {
        std::cout << "Adapter Name: " << adapter.adapter_name << std::endl;
        std::cout << "IP Address: " << int(adapter.address[0]) << "." << int(adapter.address[1]) << "." << int(adapter.address[2]) << "." << int(adapter.address[3]) << std::endl;
    }
    return 0;
}
