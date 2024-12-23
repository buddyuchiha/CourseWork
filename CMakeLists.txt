project ("AISD-HASH")

add_executable (AISD-HASH "src/main.cpp"  "algorithm/algorithm.h" "algorithm/hash_functions.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AISD-HASH PROPERTY CXX_STANDARD 20)
endif()