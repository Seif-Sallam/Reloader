cmake_minimum_required(VERSION 3.16)

add_executable(Reloader
	src/Reloader/main.cpp
	include/Reloader/ID.h
	include/Reloader/Entity.h

)

target_link_libraries(Reloader
	PUBLIC
	opengl32
	sfml-graphics
	sfml-window
	sfml-system
	sfml-audio
	Utils
)

target_include_directories(Reloader
	PUBLIC
	./include/
)

add_compile_definitions(
	RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
)