#pragma once
#include <array>
#include <string>
#include <vector>

struct AdapterInfo {
    std::string            adapter_name;
    std::array<uint8_t, 4> address;
};

auto get_adapters() -> std::vector<AdapterInfo>;