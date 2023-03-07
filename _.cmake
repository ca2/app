# Created by camilo on 2023-02 <3ThomasBorregaardSorensen!!


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
set(ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(WORKSPACE_FOLDER ${ROOT_SOURCE_DIR})


# In include(source/_.cmake) set variables like below
#set(INCLUDE_DRAW2D_CAIRO TRUE)
#set(INCLUDE_IMAGING_FREEIMAGE TRUE)
#set(INCLUDE_AUDIO TRUE)
include(source/_.cmake)



include(operating_system/_.cmake)
add_subdirectory(source/app)
add_subdirectory(operating_system)
add_subdirectory(port)
add_subdirectory(source)



