#include <cstdint>
#include <iostream>
#include <vector>

#include "macros/unwrap.hpp"

#include "nic-collector.hpp"

auto main() -> int {
    unwrap(adapters, get_adapters());
    for(const auto& adapter : adapters) {
        std::cout << "Adapter Name: " << adapter.adapter_name << std::endl;
        std::cout << "IP Address: " << adapter.address << std::endl;
    }
    return 0;
}
