cmake_minimum_required(VERSION 3.0)

set(APP_NAME bes_ias)

project(${APP_NAME})

set(SRC_FILES 
    ./src/main.c
    ./src/memory.c
    ./src/ual.c
    ./src/uc.c
    ./src/translator.c
    ./src/io.c
    )

set(INCLUDE_FILES
    ./include/memory.h
    ./include/ual.h
    ./include/uc.h
    ./include/iastype.h
    ./include/translator.h
    ./include/macro.h
    ./include/io.h
    )

include_directories(./include)

add_executable(${APP_NAME} ${SRC_FILES} ${INCLUDE_FILES})