cmake_minimum_required (VERSION 3.8)
project (test LANGUAGES C)

set (${PROJECT_NAME}_C_STANDARD 99)
set (${PROJECT_NAME}_C_STANDARD_REQUIRED ON)

set (${PROJECT_NAME}_sources
        "test.h"
        "test.c"
)

add_library (${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources})
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options (${PROJECT_NAME}
        PRIVATE
            $<$<OR:
                $<C_COMPILER_ID:GNU>,
                $<C_COMPILER_ID:Clang>,
                $<C_COMPILER_ID:MinGW>:-w
                                       -Wall
                                       -Werror>
            $<$<C_COMPILER_ID:MSVC>:/Werror>
)

