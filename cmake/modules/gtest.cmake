message(STATUS "Building tests is enabled")

if(CMAKE_MINOR_VERSION GREATER_EQUAL 24) 
        # Set download timestamp policy
        cmake_policy(SET CMP0135 NEW)
endif()

# Enable FetchContent CMake module
include(FetchContent)

# Build googletest and make the cmake targets available
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b10fad38c4026a29ea6561ab15fc4818170d1c10.zip
)

FetchContent_MakeAvailable(googletest)
