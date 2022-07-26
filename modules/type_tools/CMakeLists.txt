
include(${CMAKE_TOOL_DIR}/add_tool_module.cmake)

add_component(
    MODULE_NAME
        type_tools
    NAMESPACE
        ${PROJECT_NAMESPACE}
    INCLUDE_DIRS
        include
)
