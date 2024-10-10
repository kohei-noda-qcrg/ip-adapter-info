#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>

#include "macros/assert.hpp"

#include "nic-collector.hpp"

auto get_adapters() -> std::optional<std::vector<AdapterInfo>> {
    ifaddrs* addrs;
    ensure(getifaddrs(&addrs) == 0, "getifaddrs() failed: ", strerror(errno));

    auto adapters = std::vector<AdapterInfo>{};

    for(; addrs != nullptr; addrs = addrs->ifa_next) {
        if(addrs->ifa_addr == nullptr) {
            continue;
        }

        if(addrs->ifa_addr->sa_family == AF_INET) {
            auto adapter         = AdapterInfo{};
            adapter.adapter_name = addrs->ifa_name;
            // get IPV4 address from sockaddr_in struct
            auto addr       = reinterpret_cast<sockaddr_in*>(addrs->ifa_addr)->sin_addr.s_addr;
            adapter.address = {
                static_cast<uint8_t>((addr >> 0) & 0xFF),
                static_cast<uint8_t>((addr >> 8) & 0xFF),
                static_cast<uint8_t>((addr >> 16) & 0xFF),
                static_cast<uint8_t>((addr >> 24) & 0xFF),
            };
            adapters.emplace_back(adapter);
        }
    }

    return adapters.size() > 0 ? std::make_optional(adapters) : std::nullopt;
}
