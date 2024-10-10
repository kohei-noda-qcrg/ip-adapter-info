project(
    'win-ip-adapter-info',
    'cpp',
    version: '1.0.0',
    default_options: ['warning_level=3', 'werror=false', 'cpp_std=c++20'],
)
add_project_arguments('-Wfatal-errors', language: 'cpp')
add_project_arguments('-Wno-missing-field-initializers', language: 'cpp')

dependencies = []
if host_machine.system() == 'windows'
    cpp = meson.get_compiler('cpp')
    ws_deps = [
        cpp.find_library('ws2_32'),
        cpp.find_library('IPHLPAPI'),
    ]
    dependencies += ws_deps
endif

executable('adapter', 'main.cpp', dependencies: dependencies)