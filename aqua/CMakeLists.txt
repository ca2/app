cmake_minimum_required(VERSION 3.17)
project(aqua)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-D_AQUA_LIBRARY)
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_library(aqua)


if(WIN32)
    set(PLATFORM_NAME "windows")
endif()



include_directories(${CMAKE_SOURCE_DIR}/../..)
include_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${CMAKE_SOURCE_DIR}/../../../source/app)
include_directories(${CMAKE_SOURCE_DIR}/../../../source/app/_include)
include_directories(${CMAKE_SOURCE_DIR}/../../../source/include)
include_directories(${CMAKE_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
include_directories(${CMAKE_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
include_directories(${CMAKE_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
include_directories(${CMAKE_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)
include_directories(.)


if(WIN32)
    target_precompile_headers(aqua PUBLIC framework.h)
endif()

set(aqua_source
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
        os/macos/graphics.cpp
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





add_library(aqua MODULE
        ${aqua_source})

if(WIN32)
    target_precompile_headers(aqua PUBLIC framework.h)
endif()


set_target_properties(aqua PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(aqua PUBLIC "/MD$<$<CONFIG:Debug>:D>")
    target_link_options(aqua PUBLIC /DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>)
endif()


target_link_libraries(apex PUBLIC acme apex)



