cmake_minimum_required(VERSION 3.16)

add_executable(Reloader
	src/Reloader/main.cpp
	src/Reloader/MainCharacter.cpp
	include/Reloader/ID.h
	include/Reloader/Entity.h
	include/Reloader/MainCharacter.h
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_link_libraries(imgui
		PRIVATE
		GL
	)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(imgui
		PRIVATE
		opengl32
	)
endif()

target_link_libraries(Reloader
	PRIVATE
	sfml-graphics
	sfml-window
	sfml-system
	sfml-audio
	Utils
	imgui
)

target_include_directories(Reloader
	PUBLIC
	./include/
)

add_compile_definitions(
	RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
)