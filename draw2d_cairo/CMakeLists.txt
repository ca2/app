cmake_minimum_required(VERSION 3.16)
project(draw2d_cairo CXX)
message(STATUS "Project is " ${PROJECT_NAME})


list(APPEND library_source
   _.cpp
   _cairo.cpp
   _.h
   _impl.h
   bitmap.cpp
   bitmap.h
   brush.cpp
   brush.h
   cairo.cpp
   draw2d.cpp
   draw2d.h
   _factory.cpp
   font.cpp
   font.h
   framework.cpp
   framework.h
   graphics.cpp
   graphics.h
   image.cpp
   image.h
   keep.cpp
   keep.h
   object.cpp
   object.h
   palette.cpp
   palette.h
   path.cpp
   path.h
   pen.cpp
   pen.h
   thumbnail_dc.cpp
   region.cpp
   region.h)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


list(APPEND library_references acme apex aqua aura)


list(APPEND static_library_references ${library_references})
list(TRANSFORM static_library_references PREPEND static_)



target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)


set_target_properties(draw2d_cairo PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(draw2d_cairo PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_cairo PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_cairo PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/draw2d_cairo.lib")
    target_link_options(draw2d_cairo PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/draw2d_cairo.def")
    target_link_libraries(draw2d_cairo PRIVATE acme)


elseif(LINUX OR FREEBSD)


    #if(USE_PKGCONFIG)
        pkg_check_modules(PKGCONFIG freetype2 pango cairo pangocairo)
    #endif()


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(draw2d_cairo PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


    message(STATUS "PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(draw2d_cairo PRIVATE _DRAW2D_CAIRO_LIBRARY)



