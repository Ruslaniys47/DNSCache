cmake_minimum_required(VERSION 3.5)

project(DNSCache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DNSCache main.cpp
    DNSCache.h DNSCache.cpp)

include(GNUInstallDirs)
install(TARGETS DNSCache
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
