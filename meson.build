project(
    'ip-adapter-info',
    'cpp',
    version: '1.0.0',
    default_options: ['warning_level=3', 'werror=false', 'cpp_std=c++20'],
)
add_project_arguments('-Wfatal-errors', language: 'cpp')
add_project_arguments('-Wno-missing-field-initializers', language: 'cpp')

subdir('src')
dependencies = ip_adapter_deps

executable('example', files('src/example.cpp') + ip_adapter_files, dependencies: dependencies)