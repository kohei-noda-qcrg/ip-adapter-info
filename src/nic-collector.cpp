#include <array>

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>

#include "macros/assert.hpp"
#include "nic-collector.hpp"

auto sockaddr_to_str(const sockaddr& addr) -> std::string {
    // in order to avoid extra nulls in the conversion result, store it once in a buffer and convert it to a string.
    switch(addr.sa_family) {
    case AF_INET: {
        auto buf = std::array<char, INET_ADDRSTRLEN>();
        inet_ntop(AF_INET, &((sockaddr_in*)&addr)->sin_addr, buf.data(), buf.size());
        return std::string(buf.data());
    }
    case AF_INET6: {
        auto buf = std::array<char, INET6_ADDRSTRLEN>();
        inet_ntop(AF_INET6, &((sockaddr_in6*)&addr)->sin6_addr, buf.data(), buf.size());
        return std::string(buf.data());
    }
    default: {
        return {};
    }
    }
}

auto get_adapters() -> std::optional<std::vector<AdapterInfo>> {
    auto head = (ifaddrs*)(nullptr);
    ensure(getifaddrs(&head) == 0, "getifaddrs() failed: ", strerror(errno));
    auto adapters = std::vector<AdapterInfo>{};

    auto addrs = head;
    for(; addrs != nullptr; addrs = addrs->ifa_next) {
        if(addrs->ifa_addr == nullptr) {
            continue;
        }
        auto addr = sockaddr_to_str(*addrs->ifa_addr);
        if(addr.empty()) {
            continue;
        }
        adapters.emplace_back(AdapterInfo{
            .adapter_name = addrs->ifa_name,
            .address      = std::move(addr),
        });
    }

    freeifaddrs(head);
    return adapters;
}
