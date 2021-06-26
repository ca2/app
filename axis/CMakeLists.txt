cmake_minimum_required(VERSION 3.17)
project(axis CXX)


list(APPEND library_source
        account/_.h
        account/_account.h
        account/account.cpp
        account/authenticator.cpp
        account/authenticator.h
        account/const.h
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
        account/storage.cpp
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
        compress/_.h
        compress/bz.cpp
        compress/bz.h
        compress/bzip.h
        #const/_const.h
   #const/callback.h
   #const/charset.h
   #const/check.h
   #    const/context.h
   #    const/GLOBAL_ID.h
   #    const/id.h
        const/idpool.cpp
        const/idpool.h
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
        database/database/const.h
        database/database/database.cpp
        database/database/database.h
        database/database/database_composite.cpp
        database/database/database_composite.h
        database/database/database_impl.cpp
        database/database/database_impl.h
        database/database/dataset.cpp
        database/database/dataset.h
        database/database/definition.cpp
        database/database/definition.h
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
        geoip/_.h
        geoip/city.cpp
        geoip/city.h
        geoip/geoip.cpp
        geoip/global.h
        geoip/internal.h
        geoip/region_name.cpp
        geoip/time_zone.cpp
        geoip/update.cpp
        geoip/update.h
        graphics/render/water_routine.cpp
        graphics/render/water_routine.h
        html/html/_.h
        html/html/_const.h
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
        include/_.cpp
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
        math/calculator/_.h
        #math/calculator/_update.cpp
        math/calculator/calculator.cpp
        math/calculator/calculator.h
        math/calculator/element.cpp
        math/calculator/element.h
        math/calculator/parser.cpp
        math/calculator/parser.h
        math/calculator/parser_exception.cpp
        math/calculator/parser_exception.h
        math/calculator/result.cpp
        math/calculator/result.h
        math/calculator/scanner.cpp
        math/calculator/scanner.h
        math/calculator/token.h
        math/kissfft/_.h
        math/kissfft/fft.cpp
        math/kissfft/fft.h
        math/kissfft/fft_guts.h
        math/kissfft/fft_shared.cpp
        math/kissfft/fftd.cpp
        math/kissfft/fftd.h
        math/kissfft/ifft.cpp
        math/kissfft/ifft.h
        math/kissfft/ifftd.cpp
        math/kissfft/ifftd.h
        math/_.h
        net/netserver/_.h
        net/netserver/socket.cpp
        net/netserver/socket.h
        net/netserver/socket_handler.cpp
        net/netserver/socket_handler.h
        net/netserver/socket_thread.cpp
        net/netserver/socket_thread.h
        net/sockets/bsd/smtp/smtp_socket.cpp
        net/sockets/bsd/smtp/smtp_socket.h
        net/sockets/bsd/smtp/smtpd_socket.cpp
        net/sockets/bsd/smtp/smtpd_socket.h
        net/sockets/bsd/timer/_.h
        net/sockets/bsd/timer/Event.cpp
        net/sockets/bsd/timer/event.h
        net/sockets/bsd/timer/event_handler.h
        net/sockets/bsd/timer/event_time.h
        net/sockets/bsd/timer/EventHandler.cpp
        net/sockets/bsd/timer/EventTime.cpp
        net/sockets/bsd/timer/ievent_handler.h
        net/sockets/bsd/timer/ievent_owner.h
        net/sockets/bsd/timer/IEventOwner.cpp
        net/sockets/bsd/webserver/ajp13.h
        net/sockets/bsd/webserver/ajp13_socket.h
        net/sockets/bsd/webserver/ajp_base_socket.h
        net/sockets/bsd/_.h
        net/sockets/bsd/_strconv.h
        net/sockets/bsd/config.h
        net/sockets/bsd/socket_id_list.h
        net/sockets/bsd/sockets.h
        net/sockets/_sockets.h
        net/_.h
        net/_impl.h
        net/_net.h
        net/email_department.cpp
        net/email_department.h
        platform/_.cpp
        platform/_features.h
        platform/_generic_object_constructor_impl.h
        platform/_impl.h
        platform/_platform.h
        platform/_system_xml_impl.h
        platform/all.h
        platform/application.cpp
        platform/application.h
        platform/checked.cpp
        platform/cregexp.cpp
        platform/cregexp_util.cpp
        platform/geo_department.cpp
        platform/geo_department.h
        platform/muldiv64.cpp
        platform/openweather_city.h
        platform/session.cpp
        platform/session.h
        platform/system.cpp
        platform/system.h
        user/_.h
        user/_user.h
        #user/button.cpp
        #user/button.h
        #user/check_box.cpp
        #user/check_box.h
        user/combo_box.cpp
        user/combo_box.h
        user/list_box.cpp
        user/list_box.h
        user/simple_ui_draw.cpp
        user/simple_ui_draw.h
        user/slider.cpp
        user/slider.h
        #user/still.cpp
        #user/still.h
        user/style.cpp
        user/style.h
        user/user.cpp
        user/user.h
        user/validate.cpp
        user/validate.h
        version/version.config.h
        version/version.h
        _.cpp
        _.h
        __matter_ca2.cpp
        _defer.h
        _to.cpp
        aaa_want_to_move_xml.h
        application.h
        astr.h
        callback.h
        console.h
        console_slim.h
        context_glx.cpp
        framework.cpp
        framework.h
        framework_c.h
        id.h
        library.h
        message.h
        procedure.h
        update.h)


if(WIN32)

    list(APPEND library_source

    )
    else()

    list(APPEND library_source



            )

endif()



if(IOS)

    list(APPEND library_source
        os/ios/_.h
        os/ios/_c.h
        os/ios/_ios.h
        os/ios/_m.h
        os/ios/_mm.h
        os/ios/application_system_run.cpp
        os/ios/aura.cpp
        os/ios/base_internal.h
        os/ios/base_user.cpp
        os/ios/cross_win.cpp
        os/ios/cross_win_file.cpp
        os/ios/cross_win_gdi.h
        os/ios/crypt.cpp
        os/ios/debug.cpp
        os/ios/error.cpp
        os/ios/exception_engine.cpp
        os/ios/exception_engine.h
        os/ios/file.cpp
        os/ios/fontopus.cpp
        os/ios/gen_1.h
        os/ios/graphics.cpp
        os/ios/implementation.h
        os/ios/internal.h
        os/ios/language.cpp
        os/ios/launcher.cpp
        os/ios/library.cpp
        os/ios/lock.cpp
        os/ios/MessageBoxA_W.mm
        os/ios/mm.mm
        os/ios/mm_cross_gdi.mm
        os/ios/mm_graphics.h
        os/ios/mm_graphics.mm
        os/ios/mm_oswindow.h
        os/ios/mm_thread.mm
        os/ios/mm_user.mm
        os/ios/multithreading.cpp
        os/ios/multithreading.h
        os/ios/oswindow_data.cpp
        os/ios/oswindow_data.h
        os/ios/process.cpp
        os/ios/process.h
        os/ios/process_pid.cpp
        os/ios/simple_shell_launcher.cpp
        os/ios/small_ipca_channel.cpp
        os/ios/time.cpp
        os/ios/user.cpp
        os/ios/win_base.cpp
        os/ios/window.cpp
        os/ios/window.h
        "os/ios/window_boot 2.h"
        os/ios/window_boot.h
        os/ios/window_impl.h
        os/ios/windowing.cpp
        os/ios/windowing.h
    )
endif()

if(MACOS)

    list(APPEND library_source
            #node/macos/_.h
            #node/macos/factory_exchange.cpp
            #node/macos/factory_exchange.h



            )



endif()

if(APPLE)
    list(APPEND library_source

            #os/apple/_.cpp
            #os/apple/_.h
            #os/apple/_apple.h
            #os/apple/_apple.mm
            #os/apple/_c_mm.h
            #os/apple/_mm.h
            #os/apple/_mm_common.h
            #os/apple/DDInvocationGrabber.h
            #os/apple/DDInvocationGrabber.mm
            #os/apple/debug.cpp
            #os/apple/debug.h
            #os/apple/exe_path.cpp
            #os/apple/graphics.cpp
            #os/apple/graphics.h
            #os/apple/image_gif.cpp
            #os/apple/main.cpp
            #os/apple/main.h
            #os/apple/multihreading.cpp
            #os/apple/ns_exception.cpp
            #os/apple/ns_exception.h
            #os/apple/NSObject+DDExtensions.h
            #os/apple/NSObject+DDExtensions.mm
            #os/apple/NSString+SymlinksAndAliases.h
            #os/apple/NSString+SymlinksAndAliases.mm
            #os/apple/process.cpp
            #os/apple/time.cpp
            #os/apple/time.h
            #os/apple/UncaughtExceptionHandler.h
            #os/apple/UncaughtExceptionHandler.mm

            )

endif()


if(ANDROID)

    list(APPEND library_source
        node/android/Kerr/kerr.h
        node/android/Kerr/LocalMemory.h
        node/android/_.h
        node/android/_android.h
        node/android/android.cpp
        node/android/android1.cpp
        node/android/android1.h
        node/android/application.cpp
        node/android/application.h
        node/android/buffer.cpp
        node/android/buffer.h
        node/android/dir_context.cpp
        node/android/dir_context.h
        node/android/dir_system.cpp
        node/android/dir_system.h
        node/android/error.cpp
        node/android/exception.cpp
        node/android/factory_exchange.cpp
        node/android/factory_exchange.h
        node/android/file.cpp
        node/android/file.h
        node/android/file_context.cpp
        node/android/file_context.h
        node/android/file_system.cpp
        node/android/file_system.h
        node/android/host_interaction.cpp
        node/android/host_interaction.h
        node/android/implementation.h
        node/android/interaction_impl.cpp
        node/android/interaction_impl.h
        node/android/internal.h
        node/android/main.cpp
        node/android/os_context.cpp
        node/android/os_context.h
        node/android/process.cpp
        node/android/shell.cpp
        node/android/shell.h
        node/android/thread.cpp
        node/android/thread.h
        node/android/trace.cpp
        node/android/util.cpp
        os/android/_.h
        os/android/_android.h
        os/android/_bind_app.cpp
        os/android/_bind_impact.cpp
        os/android/_c.h
        os/android/_os_android.cpp
        os/android/_os_impl.cpp
        os/android/_os_impl.h
        os/android/_os_local.h
        os/android/_os_object.cpp
        os/android/_os_object.h
        os/android/_os_remote.h
        os/android/application_system_run.cpp
        os/android/aura.cpp
        os/android/c.cpp
        os/android/cairo_keep.h
        os/android/cross_win_file.h
        os/android/cross_win_gdi.h
        os/android/cross_win_gdi_internal.h
        os/android/debug.cpp
        os/android/dir.cpp
        os/android/exception_engine.cpp
        os/android/exception_engine.h
        os/android/file.cpp
        os/android/file.h
        os/android/graphics.cpp
        os/android/graphics.h
        os/android/internal.h
        os/android/jni_launcher.cpp
        os/android/language.cpp
        os/android/launcher.cpp
        os/android/library.cpp
        os/android/locale.cpp
        os/android/lock.cpp
        os/android/main_android.cpp
        os/android/message_loop.cpp
        os/android/multithreading.cpp
        os/android/process.cpp
        os/android/process.h
        os/android/process_pid.cpp
        os/android/simple_shell_launcher.cpp
        os/android/small_ipca_channel.cpp
        os/android/view_bitmap.h
        os/android/vsnord_native_app_glue.c
        os/android/vsnord_native_app_glue.h
        os/android/win_base.cpp
        os/android/window_android.cpp
        os/android/window_android.h
        os/android/window_impl.cpp
        os/android/windowing.cpp
        os/android/windowing.h
        )

endif()

if(SOLARIS)

list(APPEND library_source
    os/solaris/linux_internal.h
    os/solaris/solaris.cpp
    os/solaris/solaris.h
    os/solaris/solaris_cairo_keep.cpp
    os/solaris/solaris_cairo_keep.h
    os/solaris/solaris_cross_win_file.cpp
    os/solaris/solaris_cross_win_file.h
    os/solaris/solaris_cross_win_gdi.cpp
    os/solaris/solaris_cross_win_gdi.h
    os/solaris/solaris_cross_win_gdi_internal.h
    os/solaris/solaris_debug.h
    os/solaris/solaris_display.cpp
    os/solaris/solaris_file.cpp
    os/solaris/solaris_file.h
    os/solaris/solaris_file_watcher.cpp
    os/solaris/solaris_file_watcher.h
    os/solaris/solaris_graphics.h
    os/solaris/solaris_http.cpp
    os/solaris/solaris_http.h
    os/solaris/solaris_http_lib.cpp
    os/solaris/solaris_http_lib.h
    os/solaris/solaris_internal.h
    os/solaris/solaris_launcher.cpp
    os/solaris/solaris_library.cpp
    os/solaris/solaris_lock.cpp
    os/solaris/solaris_message_loop.cpp
    os/solaris/solaris_process.cpp
    os/solaris/solaris_process.h
    os/solaris/solaris_process_pid.cpp
    os/solaris/solaris_simple_shell_launcher.cpp
    os/solaris/solaris_simple_ui.cpp
    os/solaris/solaris_simple_ui.h
    os/solaris/solaris_small_ipca_channel.cpp
    os/solaris/solaris_solaris.h
    os/solaris/solaris_thread.cpp
    os/solaris/solaris_user_impl.h
    os/solaris/solaris_win_base.cpp
    os/solaris/solaris_window.cpp
    os/solaris/solaris_window_xlib.cpp
    os/solaris/solaris_window_xlib.h
    )

endif()



if(UWP)

    list(APPEND library_source
        os/uwp/_.h
        os/uwp/_os_metrowin.cpp
        os/uwp/_uwp.h
        os/uwp/_winrt.h
        os/uwp/application_system_run.cpp
        os/uwp/axis.cpp
        os/uwp/base_file.cpp
        os/uwp/base_file.h
        os/uwp/debug.cpp
        os/uwp/direct2d_tls.cpp
        os/uwp/dpi.cpp
        os/uwp/dummy_ipc.cpp
        os/uwp/exception_engine.cpp
        os/uwp/exception_engine.h
        os/uwp/file.cpp
        os/uwp/file_memory_map.cpp
        os/uwp/file_winrt.h
        os/uwp/gdi_winrt.h
        os/uwp/graphics.cpp
        os/uwp/host_interaction.h
        os/uwp/language.cpp
        os/uwp/launcher.cpp
        os/uwp/library.cpp
        os/uwp/lock.cpp
        os/uwp/main.cpp
        os/uwp/metrowin_metrowin.h
        os/uwp/multithreading.cpp
        os/uwp/multithreading.h
        os/uwp/multithreading_winrt.h
        os/uwp/os_message_box.cpp
        os/uwp/oswindow.h
        os/uwp/process.cpp
        os/uwp/process.h
        os/uwp/simple_app.cpp
        os/uwp/simple_hold_handle.h
        os/uwp/simple_shell_launcher.cpp
        os/uwp/simple_ui.h
        os/uwp/small_ipca_channel.cpp
        os/uwp/sockets.cpp
        os/uwp/sockets.h
        os/uwp/time.cpp
        os/uwp/user.cpp
        os/uwp/windowing.cpp
        )
else()

    list(APPEND library_source



            )

endif()


if(LINUX)

    list(APPEND library_source)

endif()


if(LINUX OR APPLE OR SOLARIS)

    list(APPEND library_source)

endif()


list(APPEND library_references
   acme
   apex
   aqua
   aura)


add_library(axis SHARED ${library_source})


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
elseif(LINUX)
    target_compile_options(axis PRIVATE -fpermissive)
    target_link_options(axis PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(axis PRIVATE bz2 ${PKGCONFIG_LIBRARIES} ${library_references})
    target_link_options(axis PRIVATE -Wl,-z,defs)
endif()


target_include_directories(axis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(axis PRIVATE _AXIS_LIBRARY)



