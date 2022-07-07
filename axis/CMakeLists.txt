cmake_minimum_required(VERSION 3.16)
project(axis CXX)


list(APPEND library_source
        account/_.h
        account/_account.h
        #account/account.cpp
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
        networking/_networking.h
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
        operating_system/ios/_.h
        operating_system/ios/_c.h
        operating_system/ios/_ios.h
        operating_system/ios/_m.h
        operating_system/ios/_mm.h
        operating_system/ios/application_system_run.cpp
        operating_system/ios/aura.cpp
        operating_system/ios/base_internal.h
        operating_system/ios/base_user.cpp
        operating_system/ios/cross_win.cpp
        operating_system/ios/cross_win_file.cpp
        operating_system/ios/cross_win_gdi.h
        operating_system/ios/crypt.cpp
        operating_system/ios/debug.cpp
        operating_system/ios/error.cpp
        operating_system/ios/exception_engine.cpp
        operating_system/ios/exception_engine.h
        operating_system/ios/file.cpp
        operating_system/ios/fontopus.cpp
        operating_system/ios/gen_1.h
        operating_system/ios/graphics.cpp
        operating_system/ios/implementation.h
        operating_system/ios/internal.h
        operating_system/ios/language.cpp
        operating_system/ios/launcher.cpp
        operating_system/ios/library.cpp
        operating_system/ios/lock.cpp
        operating_system/ios/MessageBoxA_W.mm
        operating_system/ios/mm.mm
        operating_system/ios/mm_cross_gdi.mm
        operating_system/ios/mm_graphics.h
        operating_system/ios/mm_graphics.mm
        operating_system/ios/mm_oswindow.h
        operating_system/ios/mm_thread.mm
        operating_system/ios/mm_user.mm
        operating_system/ios/multithreading.cpp
        operating_system/ios/multithreading.h
        operating_system/ios/oswindow_data.cpp
        operating_system/ios/oswindow_data.h
        operating_system/ios/process.cpp
        operating_system/ios/process.h
        operating_system/ios/process_pid.cpp
        operating_system/ios/simple_shell_launcher.cpp
        operating_system/ios/small_ipca_channel.cpp
        operating_system/ios/time.cpp
        operating_system/ios/user.cpp
        operating_system/ios/win_base.cpp
        operating_system/ios/window.cpp
        operating_system/ios/window.h
        "operating_system/ios/window_boot 2.h"
        operating_system/ios/window_boot.h
        operating_system/ios/window_impl.h
        operating_system/ios/windowing.cpp
        operating_system/ios/windowing.h
    )
endif()

if(MACOS)

    list(APPEND library_source
            #operating_system/macos/_.h
            #operating_system/macos/_factory.cpp
            #operating_system/macos/



            )



endif()

if(APPLE)
    list(APPEND library_source

            #operating_system/apple/_.cpp
            #operating_system/apple/_.h
            #operating_system/apple/_apple.h
            #operating_system/apple/_apple.mm
            #operating_system/apple/_c_mm.h
            #operating_system/apple/_mm.h
            #operating_system/apple/_mm_common.h
            #operating_system/apple/DDInvocationGrabber.h
            #operating_system/apple/DDInvocationGrabber.mm
            #operating_system/apple/debug.cpp
            #operating_system/apple/debug.h
            #operating_system/apple/exe_path.cpp
            #operating_system/apple/graphics.cpp
            #operating_system/apple/graphics.h
            #operating_system/apple/image_gif.cpp
            #operating_system/apple/main.cpp
            #operating_system/apple/main.h
            #operating_system/apple/multihreading.cpp
            #operating_system/apple/ns_exception.cpp
            #operating_system/apple/ns_exception.h
            #operating_system/apple/NSObject+DDExtensions.h
            #operating_system/apple/NSObject+DDExtensions.mm
            #operating_system/apple/NSString+SymlinksAndAliases.h
            #operating_system/apple/NSString+SymlinksAndAliases.mm
            #operating_system/apple/process.cpp
            #operating_system/apple/time.cpp
            #operating_system/apple/time.h
            #operating_system/apple/UncaughtExceptionHandler.h
            #operating_system/apple/UncaughtExceptionHandler.mm

            )

endif()


if(ANDROID)

    list(APPEND library_source
        operating_system/android/Kerr/kerr.h
        operating_system/android/Kerr/LocalMemory.h
        operating_system/android/_.h
        operating_system/android/_android.h
        operating_system/android/android.cpp
        operating_system/android/android1.cpp
        operating_system/android/android1.h
        operating_system/android/application.cpp
        operating_system/android/application.h
        operating_system/android/buffer.cpp
        operating_system/android/buffer.h
        operating_system/android/dir_context.cpp
        operating_system/android/dir_context.h
        operating_system/android/dir_system.cpp
        operating_system/android/dir_system.h
        operating_system/android/error.cpp
        operating_system/android/exception.cpp
        operating_system/android/_factory.cpp
        operating_system/android/
        operating_system/android/file.cpp
        operating_system/android/file.h
        operating_system/android/file_context.cpp
        operating_system/android/file_context.h
        operating_system/android/file_system.cpp
        operating_system/android/file_system.h
        operating_system/android/host_interaction.cpp
        operating_system/android/host_interaction.h
        operating_system/android/implementation.h
        operating_system/android/interaction_impl.cpp
        operating_system/android/interaction_impl.h
        operating_system/android/internal.h
        operating_system/android/main.cpp
        operating_system/android/os_context.cpp
        operating_system/android/os_context.h
        operating_system/android/process.cpp
        operating_system/android/shell.cpp
        operating_system/android/shell.h
        operating_system/android/thread.cpp
        operating_system/android/thread.h
        operating_system/android/trace.cpp
        operating_system/android/util.cpp
        operating_system/android/_.h
        operating_system/android/_android.h
        operating_system/android/_bind_app.cpp
        operating_system/android/_bind_impact.cpp
        operating_system/android/_c.h
        operating_system/android/_os_android.cpp
        operating_system/android/_os_impl.cpp
        operating_system/android/_os_impl.h
        operating_system/android/_os_local.h
        operating_system/android/_os_object.cpp
        operating_system/android/_os_object.h
        operating_system/android/_os_remote.h
        operating_system/android/application_system_run.cpp
        operating_system/android/aura.cpp
        operating_system/android/c.cpp
        operating_system/android/cairo_keep.h
        operating_system/android/cross_win_file.h
        operating_system/android/cross_win_gdi.h
        operating_system/android/cross_win_gdi_internal.h
        operating_system/android/debug.cpp
        operating_system/android/dir.cpp
        operating_system/android/exception_engine.cpp
        operating_system/android/exception_engine.h
        operating_system/android/file.cpp
        operating_system/android/file.h
        operating_system/android/graphics.cpp
        operating_system/android/graphics.h
        operating_system/android/internal.h
        operating_system/android/jni_launcher.cpp
        operating_system/android/language.cpp
        operating_system/android/launcher.cpp
        operating_system/android/library.cpp
        operating_system/android/locale.cpp
        operating_system/android/lock.cpp
        operating_system/android/main_android.cpp
        operating_system/android/message_loop.cpp
        operating_system/android/multithreading.cpp
        operating_system/android/process.cpp
        operating_system/android/process.h
        operating_system/android/process_pid.cpp
        operating_system/android/simple_shell_launcher.cpp
        operating_system/android/small_ipca_channel.cpp
        operating_system/android/view_bitmap.h
        operating_system/android/vsnord_native_app_glue.c
        operating_system/android/vsnord_native_app_glue.h
        operating_system/android/win_base.cpp
        operating_system/android/window_android.cpp
        operating_system/android/window_android.h
        operating_system/android/window_impl.cpp
        operating_system/android/windowing.cpp
        operating_system/android/windowing.h
        )

endif()

if(SOLARIS)

list(APPEND library_source
    operating_system/solaris/linux_internal.h
    operating_system/solaris/solaris.cpp
    operating_system/solaris/solaris.h
    operating_system/solaris/solaris_cairo_keep.cpp
    operating_system/solaris/solaris_cairo_keep.h
    operating_system/solaris/solaris_cross_win_file.cpp
    operating_system/solaris/solaris_cross_win_file.h
    operating_system/solaris/solaris_cross_win_gdi.cpp
    operating_system/solaris/solaris_cross_win_gdi.h
    operating_system/solaris/solaris_cross_win_gdi_internal.h
    operating_system/solaris/solaris_debug.h
    operating_system/solaris/solaris_display.cpp
    operating_system/solaris/solaris_file.cpp
    operating_system/solaris/solaris_file.h
    operating_system/solaris/solaris_file_watcher.cpp
    operating_system/solaris/solaris_file_watcher.h
    operating_system/solaris/solaris_graphics.h
    operating_system/solaris/solaris_http.cpp
    operating_system/solaris/solaris_http.h
    operating_system/solaris/solaris_http_lib.cpp
    operating_system/solaris/solaris_http_lib.h
    operating_system/solaris/solaris_internal.h
    operating_system/solaris/solaris_launcher.cpp
    operating_system/solaris/solaris_library.cpp
    operating_system/solaris/solaris_lock.cpp
    operating_system/solaris/solaris_message_loop.cpp
    operating_system/solaris/solaris_process.cpp
    operating_system/solaris/solaris_process.h
    operating_system/solaris/solaris_process_pid.cpp
    operating_system/solaris/solaris_simple_shell_launcher.cpp
    operating_system/solaris/solaris_simple_ui.cpp
    operating_system/solaris/solaris_simple_ui.h
    operating_system/solaris/solaris_small_ipca_channel.cpp
    operating_system/solaris/solaris_solaris.h
    operating_system/solaris/solaris_thread.cpp
    operating_system/solaris/solaris_user_impl.h
    operating_system/solaris/solaris_win_base.cpp
    operating_system/solaris/solaris_window.cpp
    operating_system/solaris/solaris_window_xlib.cpp
    operating_system/solaris/solaris_window_xlib.h
    )

endif()



if(UWP)

    list(APPEND library_source
        operating_system/universal_windows/_.h
        operating_system/universal_windows/_os_metrowin.cpp
        operating_system/universal_windows/_uwp.h
        operating_system/universal_windows/_winrt.h
        operating_system/universal_windows/application_system_run.cpp
        operating_system/universal_windows/axis.cpp
        operating_system/universal_windows/base_file.cpp
        operating_system/universal_windows/base_file.h
        operating_system/universal_windows/debug.cpp
        operating_system/universal_windows/direct2d_tls.cpp
        operating_system/universal_windows/dpi.cpp
        operating_system/universal_windows/dummy_ipc.cpp
        operating_system/universal_windows/exception_engine.cpp
        operating_system/universal_windows/exception_engine.h
        operating_system/universal_windows/file.cpp
        operating_system/universal_windows/file_memory_map.cpp
        operating_system/universal_windows/file_winrt.h
        operating_system/universal_windows/gdi_winrt.h
        operating_system/universal_windows/graphics.cpp
        operating_system/universal_windows/host_interaction.h
        operating_system/universal_windows/language.cpp
        operating_system/universal_windows/launcher.cpp
        operating_system/universal_windows/library.cpp
        operating_system/universal_windows/lock.cpp
        operating_system/universal_windows/main.cpp
        operating_system/universal_windows/metrowin_metrowin.h
        operating_system/universal_windows/multithreading.cpp
        operating_system/universal_windows/multithreading.h
        operating_system/universal_windows/multithreading_winrt.h
        operating_system/universal_windows/os_message_box.cpp
        operating_system/universal_windows/oswindow.h
        operating_system/universal_windows/process.cpp
        operating_system/universal_windows/process.h
        operating_system/universal_windows/simple_app.cpp
        operating_system/universal_windows/simple_hold_handle.h
        operating_system/universal_windows/simple_shell_launcher.cpp
        operating_system/universal_windows/simple_ui.h
        operating_system/universal_windows/small_ipca_channel.cpp
        operating_system/universal_windows/sockets.cpp
        operating_system/universal_windows/sockets.h
        operating_system/universal_windows/time.cpp
        operating_system/universal_windows/user.cpp
        operating_system/universal_windows/windowing.cpp
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


elseif(LINUX OR FREEBSD)


    target_compile_options(axis PRIVATE -fpermissive)
    target_link_libraries(axis PRIVATE ${library_references})
    target_link_options(axis PRIVATE -Wl,-z,defs)


endif()


target_include_directories(axis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(axis PRIVATE _AXIS_LIBRARY)



