

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
set(ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(WORKSPACE_FOLDER ${ROOT_SOURCE_DIR})


include(operating-system/_.cmake)
add_subdirectory(source/app)
add_subdirectory(operating-system)
add_subdirectory(source)



