cmake_minimum_required(VERSION 3.27)
project(kiRenderer)

set(CMAKE_CXX_STANDARD 20)

link_directories(./3rd_party/SDL2-2.0.12/x86_64-w64-mingw32/lib)
set(SDL2_INCLUDE_DIRS ./3rd_party/SDL2-2.0.12/x86_64-w64-mingw32/include)
set(SDL2_LIBRARIES SDL2main SDL2)

include_directories(./include)
include_directories(${SDL2_INCLUDE_DIRS})

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
)


add_executable(kiRenderer
        ${SOURCES}
)

