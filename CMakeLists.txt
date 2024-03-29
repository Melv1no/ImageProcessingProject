cmake_minimum_required(VERSION 3.10)

project(ImageProcessingProject C)


    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")
    FIND_PACKAGE(PkgConfig REQUIRED)
    PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
    INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
    LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
    ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})


set(SOURCES
        src/main.c
        src/image.c
        src/effects.c
        src/file_io.c
        src/menu.c
        src/gui.c
)

set(HEADERS
        include/image.h
        include/effects.h
        include/file_io.h
        include/menu.h
        include/gui.h
)

include_directories(include)

add_executable(image_processing ${SOURCES} ${HEADERS})

set_target_properties(image_processing PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS NO
)

    TARGET_LINK_LIBRARIES(image_processing ${GTK3_LIBRARIES})


file(COPY ./images DESTINATION ${CMAKE_BINARY_DIR})
target_link_libraries(image_processing m)
