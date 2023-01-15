cmake_minimum_required(VERSION 3.16)
project(app_simple_drawing CXX)


list(APPEND library_source
   _.cpp
   _.h
   ##_library.h
   #_factory.cpp
   application.cpp
   application.h
   document.cpp
   document.h
   framework.cpp
   framework.h
   frame.cpp
   frame.h
   main_frame.cpp
   main_frame.h
   render.cpp
   render.h
   render_1through3.cpp
   render_arcs.cpp
   render_box.cpp
   render_circle_path.cpp
   tab_impact.cpp
   tab_impact.h
   impact.cpp
   impact.h
   )


add_library(${PROJECT_NAME} SHARED ${library_source})

target_precompile_headers(app_simple_drawing PRIVATE framework.h)

set_target_properties(app_simple_drawing PROPERTIES LINKER_LANGUAGE CXX)


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   base
   )


if (MSVC)

   target_compile_options(app_simple_drawing PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(app_simple_drawing PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(app_simple_drawing PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(app_simple_drawing PRIVATE ${library_references})

elseif(LINUX OR FREEBSD)

   target_compile_options(app_simple_drawing PRIVATE -fpermissive)
   #target_link_options(app_simple_drawing PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(app_simple_drawing PRIVATE ${library_references})
   target_link_options(app_simple_drawing PRIVATE -Wl,-z,defs)

endif ()




target_link_directories(app_simple_drawing PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(app_simple_drawing PRIVATE _APP_SIMPLE_DRAWING_LIBRARY)


add_subdirectory(__implement)

