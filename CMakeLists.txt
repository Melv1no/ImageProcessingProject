cmake_minimum_required(VERSION 3.10)

project(ImageProcessingProject C)

if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")
    FIND_PACKAGE(PkgConfig REQUIRED)
    PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
    INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
    LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
    ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})
endif (UNIX)

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

if (UNIX)
    TARGET_LINK_LIBRARIES(image_processing ${GTK3_LIBRARIES})
endif (UNIX)

# Link with the math library
target_link_libraries(image_processing m)
