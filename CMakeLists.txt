cmake_minimum_required (VERSION 2.6)
project (client_cv)

# ZeroMQ
find_package(ZeroMQ REQUIRED)
find_package(Libssh2 REQUIRED CONFIG)

include_directories(${ZeroMQ_INCLUDE_DIR})


add_executable(client_cv client_cv.cpp)

target_link_libraries( client_cv Libssh2::libssh2 ${ZeroMQ_LIBRARIES} jsoncpp )

add_subdirectory(jsoncpp)
