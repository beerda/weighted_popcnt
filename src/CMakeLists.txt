set(HEADER_LIST
    "${weighted_popcnt_SOURCE_DIR}/include/Chain.h")

add_library(weighted_popcnt_lib INTERFACE)
target_sources(weighted_popcnt_lib INTERFACE "${HEADER_LIST}")
target_include_directories(weighted_popcnt_lib INTERFACE "${weighted_popcnt_SOURCE_DIR}/include/")
