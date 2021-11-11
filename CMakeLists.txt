cmake_minimum_required(VERSION 3.8)
project(OrderBook)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

file(GLOB HEADER
        "include"
        )
file(GLOB SOURCE
        "src/book/order_book.cc"
        "src/book/sse.cc"
        "src/dat/reader.cc"
        )

include_directories("include")

add_executable(ob "main.cc" ${HEADER} ${SOURCE})
find_package(fmt CONFIG REQUIRED)
target_link_libraries(ob PRIVATE fmt::fmt)