cmake_minimum_required (VERSION 3.8)
project (pest VERSION 0.0.0 LANGUAGES C)

set (${PROJECT_NAME}_C_STANDARD 99)
set (${PROJECT_NAME}_C_STANDARD_REQUIRED ON)

add_library (${PROJECT_NAME} STATIC
        "pest.h"
        "pest.c"
)
target_include_directories (${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)
target_compile_options (${PROJECT_NAME}
        PRIVATE
            $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:MinGW>>: -Wall -Werror>
            $<$<C_COMPILER_ID:MSVC>: /W4 /Wall>
)

include (CMakePackageConfigHelpers)
write_basic_package_version_file (
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${${PROJECT_NAME}_VERSION}
        COMPATIBILITY ExactVersion
)

install (TARGETS "${PROJECT_NAME}" EXPORT "${PROJECT_NAME}Targets"
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
)
install (EXPORT "${PROJECT_NAME}Targets" DESTINATION "lib/cmake/${PROJECT_NAME}")
install (FILES "pest.h" DESTINATION "include")
install (
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/pestConfig.cmake
        DESTINATION "lib/cmake/${PROJECT_NAME}"
)

enable_testing ()

add_executable (${PROJECT_NAME}_test "pest_test.c")
target_link_libraries (${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})
add_test (${PROJECT_NAME}_test ${PROJECT_NAME}_test)

