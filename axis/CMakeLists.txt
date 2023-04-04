cmake_minimum_required(VERSION 3.16)
project(axis CXX)


list(APPEND library_source
        account/_.h
        #account/_account.h
        #account/account.cpp
        account/authenticator.cpp
        account/authenticator.h
        #account/const.h
        account/contact_list.cpp
        account/contact_list.h
        account/credentials.cpp
        account/credentials.h
        account/department.cpp
        account/department.h
        account/e_status.h
        account/interactive.cpp
        account/interactive.h
        account/network_authenticator.cpp
        account/network_authenticator.h
        account/product.cpp
        account/product.h
        account/product_array.cpp
        account/product_array.h
        #account/storage.cpp
        account/storage.h
        account/storage_client.cpp
        account/storage_client.h
        account/system_storage.cpp
        account/system_storage.h
        account/user.cpp
        account/user.h
        account/user_array.cpp
        account/user_array.h
        account/user_set.cpp
        account/user_set.h
        account/usera.cpp
        account/usera.h
        asset/cube_new.inl
        asset/new.inl
        axispolicy/_.h
        axispolicy/_c.h
        axispolicy/policy_objc.h
        axispolicy/policy_objcpp.h
        axispolicy/policy_winrt.h
        #        compress/_.h
        #        compress/bz.cpp
        #        compress/bz.h
        #        compress/bzip.h
        #const/_const.h
        #const/callback.h
        #const/charset.h
        #const/check.h
        #    const/context.h
        #    const/GLOBAL_ID.h
        #    const/id.h
        constant/idpool.cpp
        constant/idpool.h
        #       const/impact.h
        #  const/message.h
        #    const/procedure.h
        #     const/simple_command.h
        #    const/source.h
        #const/status.h
        #     const/status_range_authentication.h
        #    const/thread.h
        #    const/timer.h
        database/database/_.h
        database/database/_impl.h
        #database/database/const.h
        database/database/composite.cpp
        database/database/composite.h
        database/database/database.cpp
        database/database/database.h
        database/database/database_impl.cpp
        database/database/database_impl.h
        database/database/dataset.cpp
        database/database/dataset.h
        database/database/definition.cpp
        #database/database/definition.h
        database/database/field_definition.cpp
        database/database/field_definition.h
        database/database/template.h
        database/database/transaction.cpp
        database/database/transaction.h
        database/simpledb/_.h
        database/simpledb/_simpledb.h
        database/simpledb/file_set.cpp
        database/simpledb/file_set.h
        database/simpledb/item.cpp
        database/simpledb/item.h
        database/simpledb/queue_item.h
        database/simpledb/server.cpp
        database/simpledb/server.h
        database/simpledb/simpledb.cpp
        database/simpledb/simpledb.h
        database/simpledb/storage.cpp
        database/simpledb/storage.h
        database/simpledb/thread.cpp
        database/simpledb/thread.h
        database/simpledb/thread_localdatabase.cpp
        database/simpledb/thread_localdatabase.h
        database/simpledb/veiev_post.h
        database/_.h
        #geoip/_.h
        #geoip/city.cpp
        #geoip/city.h
        #geoip/geoip.cpp
        #geoip/global.h
        #geoip/internal.h
        #geoip/region_name.cpp
        #geoip/time_zone.cpp
        #geoip/update.cpp
        #geoip/update.h
        graphics/render/water_routine.cpp
        graphics/render/water_routine.h
        html/html/_.h
        #html/html/_const.h
        html/html/html.cpp
        html/html/html.h
        html/html_lite/_.h
        html/html_lite/attributes.cpp
        html/html_lite/attributes.h
        html/html_lite/common.h
        html/html_lite/entity_resolver.cpp
        html/html_lite/entity_resolver.h
        html/html_lite/reader.cpp
        html/html_lite/reader.h
        html/html_lite/tag.cpp
        html/html_lite/tag.h
        html/element/_.h
        #html/element/_element.h
        html/element/element.cpp
        html/element/element.h
        html/graphics/_.h
        #html/graphics/_graphics.h
        html/graphics/attribute.cpp
        html/graphics/attribute.h
        html/graphics/base.cpp
        html/graphics/base.h
        html/graphics/border.h
        html/graphics/box.h
        html/graphics/font.cpp
        html/graphics/font.h
        #html/graphics/form.cpp
        #html/graphics/form.h
        html/graphics/message.cpp
        html/graphics/message.h
        html/graphics/point.h
        html/graphics/reader.cpp
        html/graphics/reader.h
        html/graphics/size.h
        html/graphics/style.cpp
        html/graphics/style.h
        html/graphics/style_sheet.cpp
        html/graphics/style_sheet.h
        html/graphics/style_sheet_array.cpp
        html/graphics/style_sheet_array.h
        html/graphics/tag.cpp
        html/graphics/tag.h
        html/graphics/value.cpp
        html/graphics/value.h
        #html/hi5/hi5_twitter_authorization.cpp
        #html/hi5/hi5_twitter_authorization.h
        html/html/_.h
        #html/html/_html.h
        html/html/core_data.cpp
        html/html/core_data.h
        html/html/data.cpp
        html/html/data.h
        html/impl/_.cpp
        html/impl/_.h
        #html/impl/_impl.h
        html/impl/cell.cpp
        html/impl/cell.h
        html/impl/element.cpp
        html/impl/element.h
        html/impl/form.cpp
        html/impl/form.h
        html/impl/image.cpp
        html/impl/image.h
        html/impl/input_button.cpp
        html/impl/input_button.h
        html/impl/input_checkbox.cpp
        html/impl/input_checkbox.h
        html/impl/input_text.cpp
        html/impl/input_text.h
        html/impl/select.cpp
        html/impl/select.h
        html/impl/table.cpp
        html/impl/table.h
        html/impl/table_elemental.cpp
        html/impl/table_elemental.h
        html/impl/table_row.cpp
        html/impl/table_row.h
        html/impl/text.cpp
        html/impl/text.h
        #html/user/_.h
        #html/user/_user.h
        #html/user/child_frame.cpp
        #html/user/child_frame.h
        #html/user/document.cpp
        #html/user/document.h
        html/user/form.cpp
        html/user/form.h
        #html/user/form_impact.cpp
        #html/user/form_impact.h
        #html/user/frame.cpp
        #html/user/frame.h
        #html/user/user.cpp
        #html/user/impact.cpp
        #html/user/impact.h
        #include/_.cpp
        include/_.h
        include/_c.h
        include/_c_bridge.h
        include/_include.h
        include/_no_templates.h
        include/_setup.h
        include/objc.h
        include/objcpp.h
        include/winrt.h
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
        mathematics/calculator/_.h
        #math/calculator/_update.cpp
        mathematics/calculator/calculator.cpp
        mathematics/calculator/calculator.h
        mathematics/calculator/element.cpp
        mathematics/calculator/element.h
        mathematics/calculator/parser.cpp
        mathematics/calculator/parser.h
        mathematics/calculator/parser_exception.cpp
        mathematics/calculator/parser_exception.h
        mathematics/calculator/result.cpp
        mathematics/calculator/result.h
        mathematics/calculator/scanner.cpp
        mathematics/calculator/scanner.h
        mathematics/calculator/token.h
        mathematics/kissfft/_.h
        mathematics/kissfft/fft.cpp
        mathematics/kissfft/fft.h
        mathematics/kissfft/fft_guts.h
        mathematics/kissfft/fft_shared.cpp
        mathematics/kissfft/fftd.cpp
        mathematics/kissfft/fftd.h
        mathematics/kissfft/ifft.cpp
        mathematics/kissfft/ifft.h
        mathematics/kissfft/ifftd.cpp
        mathematics/kissfft/ifftd.h
        mathematics/_.h
        networking/sockets/bsd/smtp/smtp_socket.cpp
        networking/sockets/bsd/smtp/smtp_socket.h
        networking/sockets/bsd/smtp/smtpd_socket.cpp
        networking/sockets/bsd/smtp/smtpd_socket.h
        networking/sockets/bsd/timer/_.h
        networking/sockets/bsd/timer/Event.cpp
        networking/sockets/bsd/timer/event.h
        networking/sockets/bsd/timer/event_handler.h
        networking/sockets/bsd/timer/event_time.h
        networking/sockets/bsd/timer/EventHandler.cpp
        networking/sockets/bsd/timer/EventTime.cpp
        networking/sockets/bsd/timer/ievent_handler.h
        networking/sockets/bsd/timer/ievent_owner.h
        networking/sockets/bsd/timer/IEventOwner.cpp
        networking/sockets/bsd/webserver/ajp13.h
        networking/sockets/bsd/webserver/ajp13_socket.h
        networking/sockets/bsd/webserver/ajp_base_socket.h
        networking/sockets/bsd/_.h
        networking/sockets/bsd/_strconv.h
        networking/sockets/bsd/config.h
        networking/sockets/bsd/socket_id_list.h
        networking/sockets/bsd/sockets.h
        networking/sockets/_sockets.h
        networking/_.h
        networking/_impl.h
        #networking/_networking.h
        networking/email_department.cpp
        networking/email_department.h
        #platform/_.cpp
        platform/_features.h
        platform/_generic_object_constructor_impl.h
        platform/_impl.h
        platform/_platform.h
        platform/_system_xml_impl.h
        platform/all.h
        platform/application.cpp
        platform/application.h
        platform/checked.cpp
        #platform/cregexp.cpp
        #platform/cregexp_util.cpp
        platform/geo_department.cpp
        platform/geo_department.h
        platform/muldiv64.cpp
        platform/openweather_city.h
        platform/session.cpp
        platform/session.h
        platform/system.cpp
        platform/system.h
        user/_.h
        #user/_user.h
        #user/user/button.cpp
        #user/user/button.h
        #user/user/check_box.cpp
        #user/user/check_box.h
        user/form/control.cpp
        user/form/control.h
        user/form/data.cpp
        user/form/data.h
        user/form/window.cpp
        user/form/window.h
        user/user/combo_box.cpp
        user/user/combo_box.h
        user/user/list_box.cpp
        user/user/list_box.h
        user/user/simple_ui_draw.cpp
        user/user/simple_ui_draw.h
        user/user/slider.cpp
        user/user/slider.h
        #user/user/step_slider.cpp
        #user/user/step_slider.h
        #user/still.cpp
        #user/still.h
        user/user/style.cpp
        user/user/style.h
        user/user/user.cpp
        user/user/user.h
        user/user/validate.cpp
        user/user/validate.h
        version/version.config.h
        version/version.h
        _.cpp
        _.h
        #__matter_ca2.cpp
        _defer.h
        #_to.cpp
        aaa_want_to_move_xml.h
        application.h
        astr.h
        callback.h
        console.h
        console_slim.h
        #context_glx.cpp
        framework.cpp
        framework.h
        framework_c.h
        #id.h
        library.h
        #message.h
        procedure.h
        update.h)


list(APPEND library_references
   acme
   apex
   aqua
   aura)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})





target_precompile_headers(axis PRIVATE framework.h)


set_target_properties(axis PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(axis PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(axis PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(axis PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/axis.lib")
    target_link_options(axis PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/axis.def")
    #target_link_libraries(axis PRIVATE acme apex aqua aura pcre bzip2 ws2_32 kernel32 user32 gdi32 winspool comdlg32 advapi32 shell32 ole32 oleaut32 uuid odbc32 odbccp32)
    #target_link_libraries(axis PRIVATE acme apex aqua aura bzip2 ws2_32 kernel32 user32 gdi32 winspool comdlg32 advapi32 shell32 ole32 oleaut32 uuid odbc32 odbccp32)
    target_link_libraries(axis PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


    target_compile_options(axis PRIVATE -fpermissive)
    target_link_libraries(axis PRIVATE ${library_references})
    target_link_options(axis PRIVATE -Wl,-z,defs)


endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(axis PRIVATE _AXIS_LIBRARY)



