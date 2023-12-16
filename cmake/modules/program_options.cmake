# Set download timestamp policy
cmake_policy(SET CMP0135 NEW)

# Enable FetchContent CMake module
include(FetchContent)

# Build program options and make the cmake targets available
FetchContent_Declare(
        program_options
        URL
        # program_options
        # git@github.com:boostorg/program_options.git
        ${PROJECT_SOURCE_DIR}/libs/program_options.zip
        URL_HASH MD5=4d13e42b26a3598484e833ffa8c81612
)

FetchContent_MakeAvailable(program_options)

