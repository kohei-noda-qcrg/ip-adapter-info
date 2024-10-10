#include <iostream>
#include <iphlpapi.h>
#include <winsock2.h>

int main() {
    auto             buffer_size  = ULONG(sizeof(IP_ADAPTER_INFO));
    IP_ADAPTER_INFO* adapter_info = (IP_ADAPTER_INFO*)malloc(buffer_size);
    if(GetAdaptersInfo(adapter_info, &buffer_size) == ERROR_BUFFER_OVERFLOW) {
        free(adapter_info);
        adapter_info = (IP_ADAPTER_INFO*)malloc(buffer_size);
    }

    if(GetAdaptersInfo(adapter_info, &buffer_size) == NO_ERROR) {
        while(adapter_info) {
            std::cout << "Adapter Name: " << adapter_info->AdapterName << std::endl;
            std::cout << "IP Address: " << adapter_info->IpAddressList.IpAddress.String << std::endl;
            adapter_info = adapter_info->Next;
        }
    }
    return 0;
}
