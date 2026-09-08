set(HEADER_LIST
    #"${weighted_popcnt_SOURCE_DIR}/include/Chain.h"
    "${weighted_popcnt_SOURCE_DIR}/include/SparseChain.h"
    "${weighted_popcnt_SOURCE_DIR}/include/VectorChain.h"
    "${weighted_popcnt_SOURCE_DIR}/include/BitChain.h")

add_library(weighted_popcnt_lib INTERFACE)
target_sources(weighted_popcnt_lib INTERFACE "${HEADER_LIST}")
target_include_directories(weighted_popcnt_lib INTERFACE "${weighted_popcnt_SOURCE_DIR}/include/")
