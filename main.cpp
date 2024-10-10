#include <array>
#include <cstdint>
#include <iostream>
#include <iphlpapi.h>
#include <vector>
#include <winsock2.h>

struct AdapterInfo {
    std::string            adapter_name;
    std::array<uint8_t, 4> address;
};

int main() {
    auto             buffer_size  = ULONG(sizeof(IP_ADAPTER_INFO));
    IP_ADAPTER_INFO* adapter_info = (IP_ADAPTER_INFO*)malloc(buffer_size);
    if(GetAdaptersInfo(adapter_info, &buffer_size) == ERROR_BUFFER_OVERFLOW) {
        free(adapter_info);
        adapter_info = (IP_ADAPTER_INFO*)malloc(buffer_size);
    }

    std::vector<AdapterInfo> adapters;
    if(GetAdaptersInfo(adapter_info, &buffer_size) == NO_ERROR) {
        while(adapter_info) {
            auto address = std::array<uint8_t, 4>{};
            sscanf(adapter_info->IpAddressList.IpAddress.String, "%hhu.%hhu.%hhu.%hhu", &address[0], &address[1], &address[2], &address[3]);
            adapters.emplace_back(AdapterInfo{adapter_info->AdapterName, address});
            adapter_info = adapter_info->Next;
        }
    }

    for(const auto& adapter : adapters) {
        std::cout << "Adapter Name: " << adapter.adapter_name << std::endl;
        std::cout << "IP Address: " << int(adapter.address[0]) << "." << int(adapter.address[1]) << "." << int(adapter.address[2]) << "." << int(adapter.address[3]) << std::endl;
    }
    return 0;
}
