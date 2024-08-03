cmake_minimum_required(VERSION 3.27)
project(kiRenderer)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(SDL2_DIR ./3rd_party/SDL2-2.30.6/x86_64-w64-mingw32)
    link_directories(${SDL2_DIR}/lib)
    set(SDL2_INCLUDE_DIRS ${SDL2_DIR}/include)
    set(SDL2_LIBRARIES SDL2main SDL2)
elseif(UNIX)
    find_package(SDL2 REQUIRED)
endif()


include_directories(./include)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(./3rd_party/stb)

message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_DIR: ${SDL2_DIR}")
set(LINK_LIBRARIES ${SDL2_LIBRARIES})
if(WIN32)
    set(LINK_LIBRARIES mingw32 ${LINK_LIBRARIES})
endif()
message(STATUS "LINK_LIBRARIES: ${LINK_LIBRARIES}")

set(SOURCES
        src/main.cpp
        src/kiColor.cpp
        src/kiDisplay.cpp
        src/kiError.cpp
        src/kiRenderer.cpp
        src/kiTexture.cpp
#        src/PNGLib.cpp
#        src/zlib.cpp
        src/Math.cpp
        src/Timer.cpp
        3rd_party/stb/stb_image.h
)


add_executable(kiRenderer
        ${SOURCES}
)

target_link_libraries(kiRenderer ${LINK_LIBRARIES})


