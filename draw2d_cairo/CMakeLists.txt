cmake_minimum_required(VERSION 3.17)
project(draw2d_cairo CXX)


list(APPEND library_source
        _.cpp
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
        factory_exchange.h
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
        preview_dc.cpp
        region.cpp
        region.h)


add_library(draw2d_cairo SHARED ${library_source})


target_precompile_headers(draw2d_cairo PRIVATE framework.h)


set_target_properties(draw2d_cairo PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(draw2d_cairo PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_cairo PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_cairo PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/draw2d_cairo.lib")
    target_link_options(draw2d_cairo PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/draw2d_cairo.def")
    target_link_libraries(draw2d_cairo PRIVATE acme)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG freetype2 pango cairo pangocairo)
    target_compile_options(draw2d_cairo PRIVATE -fpermissive)
    target_compile_options(draw2d_cairo PRIVATE ${PKGCONFIG_CFLAGS})
    #target_link_options(draw2d_cairo PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(draw2d_cairo PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(draw2d_cairo PRIVATE acme apex aqua aura)
    target_link_options(draw2d_cairo PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(draw2d_cairo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(draw2d_cairo PRIVATE _DRAW2D_CAIRO_LIBRARY)



