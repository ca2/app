cmake_minimum_required(VERSION 3.17)
project(tts_sapi CXX)


list(APPEND library_source
        _.cpp
        _.h
        bitmap.cpp
        bitmap.h
        brush.cpp
        brush.h
        factory_exchange.cpp
        font.cpp
        font.h
        framework.cpp
        framework.h
        graphics.cpp
        graphics.h
        image.cpp
        image.h
        object.cpp
        object.h
        path.cpp
        path.h
        pen.cpp
        pen.h
        preview_dc.cpp
        region.cpp
        region.h
        text.cpp)



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(tts_sapi SHARED ${library_source})

target_precompile_headers(tts_sapi PRIVATE framework.h)

set_target_properties(tts_sapi PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(tts_sapi PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(tts_sapi PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(tts_sapi PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/tts_sapi.lib")
    target_link_options(tts_sapi PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/tts_sapi.def")
    target_link_libraries(tts_sapi PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)
    target_compile_options(tts_sapi PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(tts_sapi PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(tts_sapi PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_options(tts_sapi PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


target_include_directories(tts_sapi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(tts_sapi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(tts_sapi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(tts_sapi PRIVATE _TTS_SAPI_LIBRARY)
