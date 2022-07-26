project(lux)
cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMAKE TOOL DIRECTORY
set(CMAKE_TOOL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tools)
set(PROJECT_NAMESPACE lux)

add_subdirectory(modules)

# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)

set(LIB_INSTALL_DIR lib/)
set(config_targets_file "lux-config-targets.cmake")

set(LUX_VERSION 0.0.1)

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/lux-config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/lux-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/lux
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/lux-config-version.cmake
  VERSION ${LUX_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
	EXPORT		lux
	DESTINATION ${CMAKE_INSTALL_PREFIX}/share/lux
	NAMESPACE   ${PROJECT_NAMESPACE}:: 
	FILE		${config_targets_file}
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/lux-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/lux-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/lux
)

