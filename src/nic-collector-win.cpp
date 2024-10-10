#include <cstdint>
#include <iphlpapi.h>
#include <winsock2.h>

#include "nic-collector.hpp"

auto get_adapters() -> std::vector<AdapterInfo> {
    auto adapters    = std::vector<AdapterInfo>{};
    auto buffer_size = ULONG(sizeof(IP_ADAPTER_INFO));

    IP_ADAPTER_INFO* adapter_info = (IP_ADAPTER_INFO*)malloc(buffer_size);
    if(GetAdaptersInfo(adapter_info, &buffer_size) == ERROR_BUFFER_OVERFLOW) {
        free(adapter_info);
        adapter_info = (IP_ADAPTER_INFO*)malloc(buffer_size);
    }

    if(GetAdaptersInfo(adapter_info, &buffer_size) == NO_ERROR) {
        while(adapter_info) {
            auto address = std::array<uint8_t, 4>{};
            sscanf(adapter_info->IpAddressList.IpAddress.String, "%hhu.%hhu.%hhu.%hhu", &address[0], &address[1], &address[2], &address[3]);
            adapters.emplace_back(AdapterInfo{adapter_info->AdapterName, address});
            adapter_info = adapter_info->Next;
        }
    }

    return adapters;
}