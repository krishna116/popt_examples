cmake_minimum_required(VERSION 3.15)

project(popt_example LANGUAGES C CXX)

set(targets test1 test2)

find_package(PkgConfig REQUIRED)
pkg_check_modules(POPT REQUIRED popt)

set(POPT_VERSION_REQUIRED 1.18)

if(${POPT_VERSION} VERSION_LESS ${POPT_VERSION_REQUIRED})
    message("popt current version = ${POPT_VERSION}")
    message(FATAL_ERROR "popt version required = ${POPT_VERSION_REQUIRED}")
endif()

foreach(tgt ${targets})
    add_executable(${tgt} "${tgt}.cpp")
    target_link_libraries(${tgt} ${POPT_LIBRARIES})
    target_include_directories(${tgt} PUBLIC ${POPT_INCLUDE_DIRS})
    target_compile_options(${tgt} PUBLIC ${POPT_CFLAGS_OTHER})
endforeach()
