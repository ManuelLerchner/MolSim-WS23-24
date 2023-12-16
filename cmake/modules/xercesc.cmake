# Set download timestamp policy
cmake_policy(SET CMP0135 NEW)

# Enable FetchContent CMake module
include(FetchContent)

# Build xerces and make the cmake targets available
FetchContent_Declare(
        xercesc
        URL
        # xerces-c-3.2.4.zip
        # https://xerces.apache.org/xerces-c/download.cgi
        ${PROJECT_SOURCE_DIR}/libs/libxerces-c-dev_3.2.4-2.zip
        URL_HASH MD5=8a8fb15d71cacee4b91d6fea5454a240
)

FetchContent_MakeAvailable(xercesc)

