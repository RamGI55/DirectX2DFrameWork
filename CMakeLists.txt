cmake_minimum_required(VERSION 3.10)
project(DirectX2DFrameWork)

set(CMAKE_CXX_STANDARD 11)

# Specify the path to the Windows SDK if needed (change the version and path if necessary)
# Windows SDK default path, typically installed with Visual Studio or the Windows SDK.
set(WINDOWS_SDK_PATH "C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/um")

# Set your MinGW toolchain path (if required)
set(CMAKE_MINGW_PREFIX "C:/mingw-w64")

# Include Direct2D headers
include_directories("${WINDOWS_SDK_PATH}/d2d1")

# Add source files
add_executable(DirectX2DFrameWork
        main.cpp
        D2DFramework.cpp
)

# Link Direct2D and other required libraries
target_link_libraries(DirectX2DFrameWork
        -lkernel32
        -luser32
        -lgdi32
        -lwinspool
        -lshell32
        -lole32
        -loleaut32
        -luuid
        -lcomdlg32
        -ladvapi32
        -ld2d1
)

# Add the library path if Direct2D libraries are not in the default location
link_directories("C:/Program Files (x86)/Windows Kits/10/Lib/10.0.19041.0/um/x64")