include_directories(${client_cv_SOURCE_DIR}/jsoncpp)
link_directories(${client_cv_BINARY_DIR}/jsoncpp)

#building just a library.
add_library(jsoncpp jsoncpp.cpp)

