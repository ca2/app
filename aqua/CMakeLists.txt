cmake_minimum_required(VERSION 3.17)
project(aqua CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LINUX TRUE)
    set(PLATFORM_NAME "linux")
    include(FindPkgConfig)
elseif(WIN32)
    set(PLATFORM_NAME "windows")
endif()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)



list(APPEND aqua_source
        const/idpool.cpp
        const/idpool.h
        game/_.h
        game/_game.h
        game/estamira.cpp
        game/estamira.h
        game/game.cpp
        game/game.h
        include/_.h
        inline/__debug_box_clear_impl.h
        inline/__debug_box_set_impl.h
        inline/_acid_app_impl.h
        inline/_app_impl1.h
        inline/_application.h
        inline/_console_old.h
        inline/_draw2d_impl.h
        inline/_new_impl.h
        inline/application.h
        inline/application_common.h
        inline/console.h
        inline/console_common.h
        inline/library.h
        multimedia/audio/_.h
        multimedia/audio/audio_c.h
        multimedia/audio/audio_wave_out.cpp
        multimedia/audio/out.h
        multimedia/audio/sound_track_player.cpp
        multimedia/audio/sound_track_player.h
        multimedia/audio/speaker.cpp
        multimedia/audio/speaker.h
        multimedia/_.h
        multimedia/_c.h
        multimedia/audio.cpp
        multimedia/audio.h
        multimedia/decoder.cpp
        multimedia/decoder.h
        multimedia/decoder_plugin.cpp
        multimedia/decoder_plugin.h
        multimedia/exception.cpp
        multimedia/exception.h
        multimedia/file_application.cpp
        multimedia/file_application.h
        multimedia/multimedia.cpp
        multimedia/multimedia.h
        os/windows/audio.cpp
        os/_.h
        platform/_platform.h
        platform/application.cpp
        platform/application.h
        platform/session.cpp
        platform/session.h
        platform/system.cpp
        platform/system.h
        user/controller.cpp
        user/controller.h
        xml/_.h
        xml/_from.cpp
        xml/_impl.h
        xml/attr.cpp
        xml/attr.h
        xml/base_array.cpp
        xml/base_array.h
        xml/data.cpp
        xml/data.h
        xml/department.h
        xml/disp_option.cpp
        xml/disp_option.h
        xml/document.cpp
        xml/document.h
        xml/edit.cpp
        xml/edit.h
        xml/entity.cpp
        xml/entity.h
        xml/enum.h
        xml/exportable.cpp
        xml/exportable.h
        xml/glue.h
        xml/importable.cpp
        xml/importable.h
        xml/input_tree.cpp
        xml/input_tree.h
        xml/node.cpp
        xml/node.h
        xml/output_tree.cpp
        xml/output_tree.h
        xml/parse_info.cpp
        xml/parse_info.h
        xml/property_exchange.cpp
        xml/property_exchange.h
        xml/smart_pointer_array.h
        xml/stream.h
        xml/tree_base.cpp
        xml/tree_base.h
        xml/tree_schema.cpp
        xml/tree_schema.h
        xml/var_exchange.cpp
        xml/var_exchange.h
        xml/xml.cpp
        xml/xmlite.cpp
        xml/xmlite.h
        _.cpp
        _.h
        _defer.h
        console.h
        framework.cpp
        framework.h
        id.h
        library.h
        xml.h)

if(MACOS)
    list(APPEND aqua_source
            os/macos/graphics.cpp
            )
endif()



if (MSVC)
    set(LIBCXX_TARGETING_MSVC ON)
else()
    set(LIBCXX_TARGETING_MSVC OFF)
endif()


add_library(aqua SHARED ${aqua_source})

target_precompile_headers(aqua PRIVATE framework.h)

set_target_properties(aqua PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(aqua PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(aqua PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(aqua PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/aqua.lib")
    target_link_options(aqua PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/aqua.def")
    target_link_libraries(aqua PRIVATE acme apex)
elseif(LINUX)
    pkg_check_modules(PKGCONFIG glib-2.0 gtk+-3.0 libssl)
    #pkg_check_modules(PKGCONFIG glib-2.0 freetype2 gtk+-3.0 gdk-3.0)
    target_compile_options(aqua PRIVATE -fpermissive)
    target_compile_options(aqua PRIVATE ${PKGCONFIG_CFLAGS})

    #target_compile_options(aqua PRIVATE -std=c++14)
    #target_link_options(aqua PRIVATE ${GTK_LDFLAGS})
    target_link_options(aqua PRIVATE -Wl,-rpath=\$ORIGIN)
    #target_link_libraries(aqua PRIVATE )
    target_link_libraries(aqua PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(aqua PRIVATE acme apex)
    target_link_options(aqua PRIVATE -Wl,-z,defs)
    message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()

target_link_directories(aqua PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(apex PRIVATE .)
target_include_directories(aqua PRIVATE $ENV{HOME}/__config)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
target_include_directories(aqua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(aqua PRIVATE _AQUA_LIBRARY)
target_compile_definitions(aqua PRIVATE UNICODE)
target_compile_definitions(aqua PRIVATE _UNICODE)









