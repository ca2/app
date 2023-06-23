cmake_minimum_required(VERSION 3.16)
project(base CXX)


list(APPEND library_source
        #const/charset.h
        #const/GLOBAL_ID.h
        constant/idpool.cpp
        constant/idpool.h
        #    const/procedure.h
        #include/_.cpp
        html/user/document.cpp
        #html/user/form/impact.cpp
        html/user/impact.cpp
        html/user/user.cpp
        include/_.h
        include/_c.h
        include/_c_bridge.h
        include/_include.h
        include/_no_templates.h
        include/_setup.h
        include/objc.h
        include/objcpp.h
        include/winrt.h
        #inline/__debug_box_clear_impl.h
        #inline/__debug_box_set_impl.h
        #inline/_acid${PROJECT_NAME}.h
        #inline/${PROJECT_NAME}.h
        #inline/_application.h
        #inline/_console_old.h
        #inline/_draw2d_impl.h
        #inline/_new_impl.h
        #inline/application.h
        #inline/application_common.h
        #inline/console.h
        #inline/console_common.h
        #inline/library.h
        platform/_features.h
        platform/_impl.h
        platform/_platform.h
        platform/application.cpp
        platform/application.h
        platform/session.cpp
        platform/session.h
        platform/system.cpp
        platform/system.h
        user/experience/_.h
        user/experience/_constant.h
        #user/experience/_experience.h
        user/experience/button.cpp
        user/experience/button.h
        user/experience/control_box.cpp
        user/experience/control_box.h
        user/experience/department.cpp
        user/experience/department.h
        user/experience/dock_manager.cpp
        user/experience/dock_manager.h
        user/experience/experience.cpp
        user/experience/experience.h
        user/experience/experience_updown.cpp
        user/experience/experience_updown.h
        user/experience/frame.cpp
        user/experience/frame.h
        user/experience/frame_window.cpp
        user/experience/frame_window.h
        user/experience/menu_manager.cpp
        user/experience/menu_manager.h
        user/experience/move_manager.cpp
        user/experience/move_manager.h
        user/experience/orto_button.cpp
        user/experience/orto_button.h
        user/experience/size_manager.cpp
        user/experience/size_manager.h
        user/menu/_.h
        #user/menu/_menu.h
        user/menu/button.cpp
        user/menu/button.h
        user/menu/central.cpp
        user/menu/central.h
        user/menu/list_impact.cpp
        user/menu/list_impact.h
        user/menu/list_window.cpp
        user/menu/list_window.h
        user/menu/impact.cpp
        user/menu/impact.h
        user/simple/_.h
        user/simple/_impl.h
        #user/simple/_component.h
        user/simple/frame_window.cpp
        user/simple/frame_window.h
        user/simple/main_frame.cpp
        user/simple/main_frame.h
        user/simple/scroll_bar.cpp
        user/simple/scroll_bar.h
        user/simple/status_bar.cpp
        user/simple/status_bar.h
        user/simple/tab_document.cpp
        user/simple/tab_document.h
        user/simple/toolbar.cpp
        user/simple/toolbar.h
        #user/user/_.cpp
        user/user/_.h
        #user/user/_constant.h
        user/user/_data.h
        user/user/_impl.h
        user/user/_tree.h
        #user/user/_component.h
        user/user/composition_imm_client.h
        #user/user/control.cpp
        #user/user/control.h
        user/user/control_bar.cpp
        user/user/control_bar.h
        user/user/control_ddx_dbflags.h
        #user/user/control_descriptor_set.cpp
        #user/user/control_descriptor_set.h
        user/user/control_property.cpp
        user/user/control_property.h
        user/user/data_exchange.cpp
        user/user/data_exchange.h
        user/user/document.cpp
        user/user/document.h
        user/user/document_data_map.h
        user/user/document_manager.cpp
        user/user/document_manager.h
        user/user/document_manager_container.cpp
        user/user/document_manager_container.h
        #user/user/edit_plain_text_impact.cpp
        #user/user/edit_plain_text_impact.h
        user/user/edit_window.h
        user/form/document.cpp
        user/form/document.h
        user/form/update_hint.h
        user/form/impact.cpp
        user/form/impact.h
        user/simple/child_frame.cpp
        user/simple/child_frame.h
        user/simple/impact.cpp
        user/simple/impact.h
        #user/simple/pane_document.cpp
        #user/simple/pane_document.h
        user/user/frame_window.cpp
        user/user/frame_window.h
        user/user/hotplugin.cpp
        user/user/image_list.cpp
        user/user/image_list.h
        #user/user/image_manager.h
        user/user/impact.cpp
        user/user/impact.h
        user/user/impact_creator.cpp
        user/user/impact_creator.h
        user/user/impact_data.cpp
        user/user/impact_data.h
        user/user/impact_host.cpp
        user/user/impact_host.h
        user/user/impact_kit.cpp
        user/user/impact_kit.h
        user/user/impact_system.cpp
        user/user/impact_system.h
        user/user/impact_update_hint.h
        #user/user/main_frame.h
        user/user/margin.cpp
        user/user/margin.h
        user/menu/menu.cpp
        user/menu/menu.h
        #user/user/menu_command.cpp
        #user/user/menu_command.h
        user/menu/interaction.cpp
        user/menu/interaction.h
        user/menu/item.cpp
        user/menu/item.h
        user/user/multiple_document_template.cpp
        user/user/multiple_document_template.h
        user/user/network_configuration.cpp
        user/user/network_configuration.h
        #user/user/notification_area.cpp
        #user/user/notification_area.h
        user/user/picture.cpp
        user/user/picture.h
        user/user/picture_interaction.cpp
        user/user/picture_interaction.h
        user/user/place_holder.cpp
        user/user/place_holder.h
        user/user/place_holder_container.cpp
        user/user/place_holder_container.h
        user/user/print_task.cpp
        user/user/print_task.h
        user/user/server.cpp
        user/user/server.h
        user/user/single_document_template.cpp
        user/user/single_document_template.h
        user/user/split_bar.cpp
        user/user/split_bar.h
        user/user/split_layout.cpp
        user/user/split_layout.h
        user/user/split_pane.cpp
        user/user/split_pane.h
        user/user/split_impact.cpp
        user/user/split_impact.h
        #user/user/static_control.cpp
        #user/user/static_control.h
        user/user/statusbar.cpp
        user/user/statusbar.h
        user/user/style.cpp
        user/user/style.h
        user/user/tab.cpp
        user/user/tab.h
        user/user/tab_callback.cpp
        user/user/tab_callback.h
        user/user/tab_data.cpp
        user/user/tab_data.h
        user/user/tab_drop_target_window.cpp
        user/user/tab_drop_target_window.h
        user/user/tab_graphics.cpp
        user/user/tab_pane.cpp
        user/user/tab_pane.h
        user/user/tab_pane_array.cpp
        user/user/tab_pane_array.cpp
        user/user/tab_impact.cpp
        user/user/tab_impact.h
        user/user/toolbar.cpp
        user/user/toolbar.h
        user/user/user.cpp
        user/user/user.h
        #user/user/validate.cpp
        user/_.h
        user/prelude.h
        version/version.config.h
        version/version.h
        _.cpp
        _.h
        #__matter_ca2.cpp
        _defer.h
        #$aaa_want_to_move_xml.h
        application.h
        #astr.h
        callback.h
        console.h
        #context_glx.cpp
        framework.cpp
        framework.h
        #framework_c.h
        id.h
        library.h
        #message.h
        procedure.h
        #timer.mm
        #update.h
        user.h)

if (WIN32)

    list(APPEND library_source
            operating_system/windows/frame_window.cpp
            )

endif ()

if (LINUX)

    list(APPEND library_source
            operating_system/linux/frame_window.cpp
            )

endif ()

if (APPLE)

    list(APPEND library_source

            #user/user/notify_icon.mm
            #user/user/notify_icon_mm.h
            #user/user/notify_icon_mm_bridge.h
            #user/user/notify_icon_mm_bridge.mm

            )

endif ()


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


list(APPEND library_references acme apex aqua aura axis)


list(APPEND static_library_references ${library_references})
list(TRANSFORM static_library_references PREPEND static_)


target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(static_${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/base.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/base.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura axis)


elseif (LINUX OR FREEBSD)


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references})


    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _BASE_LIBRARY)



