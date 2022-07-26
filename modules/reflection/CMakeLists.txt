
include(${CMAKE_TOOL_DIR}/add_tool_module.cmake)

add_component(
    MODULE_NAME
        reflection
    NAMESPACE
        ${PROJECT_NAMESPACE}
    INCLUDE_DIRS
        include
    DEPENDENCIES
        ${PROJECT_NAMESPACE}::string
        ${PROJECT_NAMESPACE}::type_tools
)

module_test(
    MODULE_NAME
        reflection
    NAMESPACE
        ${PROJECT_NAMESPACE}
    SOURCE_FILES
        test.cpp
)
