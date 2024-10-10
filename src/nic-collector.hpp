#pragma once
#include <array>
#include <optional>
#include <string>
#include <vector>

struct AdapterInfo {
    std::string            adapter_name;
    std::array<uint8_t, 4> address;
};

auto get_adapters() -> std::optional<std::vector<AdapterInfo>>;