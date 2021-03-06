cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(Arkanoid LANGUAGES CXX)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PUBLIC arkanoid.cpp)
target_sources(${PROJECT_NAME} PUBLIC game.cpp)
target_sources(${PROJECT_NAME} PUBLIC menu.cpp)
target_sources(${PROJECT_NAME} PUBLIC button.cpp)
target_sources(${PROJECT_NAME} PUBLIC libelle.cpp)
target_sources(${PROJECT_NAME} PUBLIC picture.cpp)
target_sources(${PROJECT_NAME} PUBLIC vault.cpp)
target_sources(${PROJECT_NAME} PUBLIC ball.cpp)
target_sources(${PROJECT_NAME} PUBLIC bonus.cpp)
target_sources(${PROJECT_NAME} PUBLIC brick.cpp)
target_sources(${PROJECT_NAME} PUBLIC rocket.cpp)
target_sources(${PROJECT_NAME} PUBLIC enemy.cpp)
target_sources(${PROJECT_NAME} PUBLIC objsdl.cpp)
target_sources(${PROJECT_NAME} PUBLIC util.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_nullptr)

if (MSVC)
	file(COPY ${SDL2_DIR}/${VC_LIB_PATH_SUFFIX}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
	file(COPY ${SDL2_DIR}/${VC_LIB_PATH_SUFFIX}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()
