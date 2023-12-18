cmake_minimum_required(VERSION 3.10)

project(ImageProcessingProject C)

set(SOURCES
        src/main.c
        src/image.c
        src/effects.c
        src/file_io.c
        src/menu.c
)

set(HEADERS
        include/image.h
        include/effects.h
        include/file_io.h
        include/menu.h
)

include_directories(include)

add_executable(image_processing ${SOURCES} ${HEADERS})

set_target_properties(image_processing PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS NO
)
