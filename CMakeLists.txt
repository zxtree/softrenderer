cmake_minimum_required()
project(softrender)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
include_directories(/usr/include)
link_directories(/usr/local/lib)
link_directories(/usr/lib)
link_libraries(SDL2 SDL2_image m tcmalloc profiler assimp)
aux_source_directory(./src DIR_SRC)
add_executable(softrender ${DIR_SRC})
add_definitions("-Wall -ggdb -g -O0")
