#include <bit>

#include <iphlpapi.h>
#include <winsock2.h>

#include "macros/assert.hpp"
#include "nic-collector.hpp"

auto get_adapters() -> std::optional<std::vector<AdapterInfo>> {
    auto adapters    = std::vector<AdapterInfo>{};
    auto buffer_size = ULONG{0};

    ensure(GetAdaptersInfo(NULL, &buffer_size) == ERROR_BUFFER_OVERFLOW);
    auto buffer = std::vector<std::byte>(buffer_size);

    const auto ret = GetAdaptersInfo(std::bit_cast<PIP_ADAPTER_INFO>(buffer.data()), &buffer_size);
    ensure(ret == NO_ERROR, "GetAdaptersInfo failed, return code: ", ret);
    auto adapter_info = std::bit_cast<PIP_ADAPTER_INFO>(buffer.data());
    while(adapter_info) {
        adapters.emplace_back(AdapterInfo{adapter_info->AdapterName, adapter_info->IpAddressList.IpAddress.String});
        adapter_info = adapter_info->Next;
    }

    return adapters;
}
