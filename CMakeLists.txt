cmake_minimum_required(VERSION 3.10)

project(ImageProcessingProject C)

# Add your source files
set(SOURCES
        src/main.c
        src/image.c
        src/effects.c
        src/file_io.c
        src/menu.c
)

# Add your header files
set(HEADERS
        include/image.h
        include/effects.h
        include/file_io.h
        include/menu.h
)

# Set the include directories
include_directories(include)

# Add an executable target
add_executable(image_processing ${SOURCES} ${HEADERS})

# Optionally, you can link libraries if needed
# target_link_libraries(image_processing some_library)

# Specify C standard
set_target_properties(image_processing PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS NO
)
