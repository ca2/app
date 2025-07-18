cmake_minimum_required(VERSION 3.16)
project(aqua CXX)


list(APPEND library_source
   constant/idpool.cpp
   constant/idpool.h
   game/_.h
   #game/_game.h
   game/estamira.cpp
   game/estamira.h
   game/game.cpp
   game/game.h
   include/_.h
   inline/__debug_box_clear_impl.h
   inline/__debug_box_set_impl.h
   #inline/_acid${PROJECT_NAME}.h
   #inline/${PROJECT_NAME}.h
   inline/_application.h
   inline/_console_old.h
   inline/_draw2d_impl.h
   inline/_new_impl.h
   inline/application.h
   inline/application_common.h
   inline/console.h
   inline/console_common.h
   inline/library.h
   audio/_.h
   audio/_c.h
   audio/audio.cpp
   audio/audio.h
   audio/audio_mixer.cpp
   audio/audio_mixer.h
   audio/audio_mixer_user.cpp
   audio/audio_mixer_user.h
   audio/audio_wave_out.cpp
   audio/out.h
   audio/sound_track_player.cpp
   audio/sound_track_player.h
   audio/text_to_speech_client.cpp
   audio/text_to_speech_client.h
   audio/speaker.cpp
   audio/speaker.h
   multimedia/_.h
   multimedia/_c.h
   multimedia/decoder.cpp
   multimedia/decoder.h
   multimedia/decoder_plugin.cpp
   multimedia/decoder_plugin.h
   multimedia/exception.cpp
   multimedia/exception.h
   multimedia/file_application.cpp
   multimedia/file_application.h
   multimedia/information.h
   multimedia/media_item.cpp
   multimedia/media_item.h
   multimedia/media_item_picker.cpp
   multimedia/media_item_picker.h
   multimedia/media_item_picker_callback.cpp
   multimedia/media_item_picker_callback.h
   multimedia/media_player.cpp
   multimedia/media_player.h
   multimedia/media_player_command.cpp
   multimedia/media_player_command.h
   multimedia/multimedia.cpp
   multimedia/multimedia.h
   #operating_system/windows/audio.cpp
   #operating_system/_.h
   platform/_platform.h
   platform/application.cpp
   platform/application.h
   platform/session.cpp
   platform/session.h
   platform/system.cpp
   platform/system.h
   platform/tinyexpr.cpp
   platform/tinyexpr.h
   #        user/controller.cpp
   #        user/controller.h
   xml/_.h
   xml/_constant.h

   #xml/_from.cpp
   xml/_geometry2d_impl.h
   xml/_impl.h
   #xml/attr.cpp
   #xml/attr.h
   #xml/base_array.cpp
   xml/base_array.h
   xml/data.cpp
   xml/data.h
   xml/xml.h
   xml/disp_option.cpp
   xml/disp_option.h
   xml/document.cpp
   xml/document.h
   xml/edit.cpp
   xml/edit.h
   xml/entity.cpp
   xml/entity.h
   xml/exception.cpp
   xml/exception.h
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
   #_defer.h
   console.h
   framework.cpp
   framework.h
   id.h
   library.h
   #xml.h
)

if (MACOS)
   list(APPEND ${PROJECT_NAME}_source
      operating_system/macos/graphics.cpp
   )
endif ()


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_references
   acme
   apex)


list(APPEND static_library_references ${library_references})
list(TRANSFORM static_library_references PREPEND static_)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

if (MSVC)
   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
   #target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
   target_link_libraries(${PROJECT_NAME} PRIVATE acme apex)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})
   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

   target_link_libraries(${PROJECT_NAME} PRIVATE)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

   message(STATUS "(6) PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
endif ()




list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
