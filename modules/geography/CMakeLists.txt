include(${CMAKE_TOOL_DIR}/add_tool_module.cmake)
include(${CMAKE_TOOL_DIR}/module_test.cmake)

add_component(
    MODULE_NAME
        geography
    NAMESPACE
        ${PROJECT_NAMESPACE}
    INCLUDE_DIRS
        include
    SOURCE_FILES
        src/haversine.c
        src/vincenty.c
    DEPENDENCIES
        ${PROJECT_NAMESPACE}::math
        ${PROJECT_NAMESPACE}::core
)

module_test(
    MODULE_NAME
        geography
    NAMESPACE
        ${PROJECT_NAMESPACE}
    SOURCE_FILES
        test.cpp
)