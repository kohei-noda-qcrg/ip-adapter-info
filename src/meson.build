ip_adapter_deps = []
if host_machine.system() == 'windows'
    cpp = meson.get_compiler('cpp')
    ip_adapter_deps += [
        cpp.find_library('ws2_32'),
        cpp.find_library('IPHLPAPI'),
    ]
    ip_adapter_files = files('nic-collector-win.cpp')
else
    ip_adapter_files = files('nic-collector.cpp')
endif