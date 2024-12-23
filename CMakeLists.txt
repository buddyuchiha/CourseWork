project ("AISD-HASH")

add_executable (AISD-HASH "src/main.cpp"  "algorithm/chain_hash_table.h" "algorithm/hash_functions.h"  "algorithm/adress_hash_table.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AISD-HASH PROPERTY CXX_STANDARD 20)
endif()