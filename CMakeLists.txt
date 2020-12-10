project(Boids)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.1)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_BUILD_TYPE Release CACHE STRING "Release build" FORCE)

set(APP_NAME BoidsGui)

set(SOURCES_DIR src)
set(HEADERS_DIR include)
set(SOURCES_CORE_DIR ${SOURCES_DIR}/core)
set(HEADERS_CORE_DIR ${HEADERS_DIR}/core)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wno-unused-result -Wno-reorder -Wno-cpp -Wno-unused-value -Wno-unused-variable -Wno-unused-parameter" CACHE STRING "Flags used by the compiler during all build types." FORCE)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
add_definitions(-DQT5)

#set(CMAKE_AUTORCC ON)



set(WITH_STATIC_LIBRARY OFF)


include_directories(${HEADERS_DIR} ${HEADERS_CORE_DIR})


qt5_wrap_cpp(MAIN_MOC_FILES
	${HEADERS_DIR}/QSFMLCanvas.h
	${HEADERS_DIR}/MainWidget.h
)

set(CORE_SOURCES 
	${SOURCES_CORE_DIR}/Boid.cpp
	${SOURCES_CORE_DIR}/Flock.cpp
	${SOURCES_CORE_DIR}/Pvector.cpp
)


set(MAIN_SOURCES
	${MAIN_RESOURCES}
    ${MAIN_MOC_FILES}
    ${SOURCES_DIR}/QSFMLCanvas.cpp
	${SOURCES_DIR}/MainWidget.cpp
	${SOURCES_DIR}/main.cpp
)


if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to Release as none was specified.")
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Default build type: Release." FORCE)
endif()



# add_definitions(-DSTATICLIBS)

add_executable(${APP_NAME} ${MAIN_SOURCES} ${CORE_SOURCES})
if(WITH_STATIC_LIBRARY)
	target_link_libraries(${APP_NAME} Qt5::Core Qt5::Gui Qt5::Widgets pthread sfml-graphics sfml-window sfml-system)
else()
	target_link_libraries(${APP_NAME} Qt5::Core Qt5::Gui Qt5::Widgets pthread sfml-graphics sfml-window sfml-system)
endif()
set_target_properties(${APP_NAME} PROPERTIES VERSION ${VERSION})


set(CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")
