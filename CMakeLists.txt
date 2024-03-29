cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CPM)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

CPMAddPackage(
    NAME 			SFML
    GIT_REPOSITORY 	git@github.com:Seif-Sallam/SFML.git
    GIT_TAG 		2.5.x
)

project(
	Reloader
	VERSION
	0.1
	LANGUAGES
	CXX
)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_subdirectory(Thirdparty/fmt)
include_directories(AFTER Thirdparty/fmt/include)
add_subdirectory(Thirdparty/imgui)
include_directories(AFTER Thirdparty/imgui)
add_subdirectory(Utils)
add_subdirectory(Reloader)
