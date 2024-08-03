cmake_minimum_required(VERSION 3.27)
project(kiRenderer)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_DIR ./3rd_party/SDL2-2.30.6/x86_64-w64-mingw32)

link_directories(${SDL2_DIR}/lib)
set(SDL2_INCLUDE_DIRS ${SDL2_DIR}/include)
set(SDL2_LIBRARIES SDL2main SDL2)

include_directories(./include)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(./3rd_party/stb)

link_libraries(mingw32 ${SDL2_LIBRARIES})

#add_compile_options(-Wall -Wextra -Werror)
#add_compile_options(-Wall)


set(SOURCES
        src/main.cpp
        src/kiColor.cpp
        src/kiDisplay.cpp
        src/kiError.cpp
        src/kiRenderer.cpp
        src/kiTexture.cpp
        src/PNGLib.cpp
        src/zlib.cpp
        src/Math.cpp
        src/Timer.cpp
        3rd_party/stb/stb_image.h
        include/kiTexture.h
)


add_executable(kiRenderer
        ${SOURCES}
)

