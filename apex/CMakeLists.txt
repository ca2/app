cmake_minimum_required(VERSION 3.16)
project(apex CXX)


if (LINUX)
   set(USE_OPENSSL TRUE)
   set(PTHREAD TRUE)
elseif (WIN32)
   set(USE_OPENSSL TRUE)
elseif(FREEBSD)
   set(USE_OPENSSL TRUE)
   set(PTHREAD TRUE)
endif ()


list(APPEND apex_source
   asset/cube_new.inl
   asset/new.inl
   axispolicy/_.h
   axispolicy/_c.h
   axispolicy/policy_objc.h
   axispolicy/policy_objcpp.h
   axispolicy/policy_winrt.h
   compress/_.h
   #compress/context.cpp
   #compress/context.h
   compress/is_dir.cpp
   compress/is_dir.h
   compress/not_dir.cpp
   compress/not_dir.h
   #compress/zip/_.h
   #compress/zip/context.cpp
   #compress/zip/context.h
   #const/_const.h
   #const/charset.h
   #const/id.h
   constant/idpool.cpp
   constant/idpool.h
   #const/impact.h
   constant/method.h
   #const/status.h
   #const/status_range_authentication.h
   #const/thread.h
   #const/timer.h
   #crypto/openssl/_.cpp
   #crypto/openssl/_openssl.h
   #crypto/openssl/crypto.cpp
   #crypto/openssl/hasher.cpp
   #crypto/openssl/hasher.h
   #crypto/openssl/hasher_algorithm.cpp
   #crypto/openssl/hasher_algorithm.h
   #crypto/openssl/hasher_algorithm.h
   #crypto/openssl/rsa.cpp
   #crypto/openssl/rsa.h
   crypto/_.h
   crypto/_crypto.h
   crypto/crypto.cpp
   crypto/crypto.h
   #crypto/hasher.cpp
   crypto/hasher.h
   #crypto/hasher_algorithm.cpp
   crypto/hasher_algorithm.h
   crypto/initializer.cpp
   crypto/initializer.h
   crypto/rsa.cpp
   crypto/rsa.h
   database/_.h
   database/_impl.h
   database/change_event.h
   database/client.cpp
   database/client.h
   database/const.h
   database/event_change.cpp
   #database/id.cpp
   database/key.cpp
   database/key.h
   database/selection.cpp
   database/selection.h
   database/selection_item.cpp
   database/selection_item.h
   database/server.cpp
   database/server.h
   database/stringhelper.cpp
   database/stringhelper.h
   #filesystem/file/_.h
   filesystem/file/_data.h
   filesystem/file/_file.h
   filesystem/file/edit_file.cpp
   filesystem/file/edit_file.h
   filesystem/file/html_file.cpp
   filesystem/file/html_file.h
   filesystem/file/set.cpp
   filesystem/file/set.h
   filesystem/filesystem/_.h
   filesystem/filesystem/_impl.h
   filesystem/filesystem/dir_context.cpp
   filesystem/filesystem/dir_context.h
   filesystem/filesystem/dir_system.cpp
   filesystem/filesystem/dir_system.h
   filesystem/filesystem/dir_system_heap.h
   filesystem/filesystem/file_context.cpp
   filesystem/filesystem/file_context.h
   filesystem/filesystem/file_system.cpp
   filesystem/filesystem/file_system.h
   filesystem/filesystem/file_watcher.cpp
   filesystem/filesystem/file_watcher.h
   filesystem/filesystem/file_listener.h
   #filesystem/filesystem/path.h
   filesystem/fs/_.h
   filesystem/fs/_fs.h
   filesystem/fs/data.cpp
   filesystem/fs/data.h
   filesystem/fs/fs.cpp
   filesystem/fs/fs.h
   filesystem/fs/ifs.cpp
   filesystem/fs/ifs.h
   filesystem/fs/ifs_file.cpp
   filesystem/fs/ifs_file.h
   filesystem/fs/item.h
   filesystem/fs/item_array.h
   filesystem/fs/link.cpp
   filesystem/fs/link.h
   filesystem/fs/native_fs.cpp
   filesystem/fs/native_fs.h
   filesystem/fs/net.h
   filesystem/fs/remote_native_file.cpp
   filesystem/fs/remote_native_file.h
   filesystem/fs/remote_native_fs.cpp
   filesystem/fs/remote_native_fs.h
   filesystem/fs/set.cpp
   filesystem/fs/set.h
   filesystem/_impl.h
   filesystem/filesystem.h
   handler/context.cpp
   handler/context.h
   handler/manager.cpp
   handler/manager.h
   #handler/process.cpp
   #handler/promise.cpp
   handler/promise.h
   #handler/routine.cpp
   handler/signal.cpp
   handler/signal.h
   handler/source.cpp
   handler/source.h
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
   inline/application/android.h
   inline/application/ios.h
   inline/application/linux.h
   inline/application/macos.h
   inline/application/universal_windows.h
   inline/application/windows.h
   inline/console/linux.h
   inline/console/macos.h
   inline/console/windows.h
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
   message/_.cpp
   message/_.h
   message/_impl.h
   message/_message.h
   message/application.cpp
   message/application.h
   #message/base.cpp
   message/base.h
   message/channel.cpp
   message/channel.h
   #message/command_target.cpp
   #message/command_ui_probe.cpp
   message/command_ui_probe.h
   message/command.cpp
   message/command.h
   message/const.h
   message/cross_windows.h
   message/debug.cpp
   message/definition.h
   message/dispatcher.cpp
   message/dispatcher.h
   message/global.h
   #message/id.cpp
   #message/id.h
   message/listener_smart_pointer_array.h
   message/message.cpp
   message/message.h
   #message/receiver.cpp
   message/receiver.h
   #message/route.h
   #message/sender.cpp
   message/simple_command.cpp
   message/simple_command.h
   #networking/http/_.cpp
   networking/http/_.h
   networking/http/context.cpp
   networking/http/context.h
   networking/http/cookie.cpp
   networking/http/cookie.h
   networking/http/form.cpp
   networking/http/form.h
   networking/http/get_socket.cpp
   networking/http/get_socket.h
   networking/http/listener.h
   #networking/http/ostream.cpp
   networking/http/request.cpp
   networking/http/request.h
   networking/http/response.cpp
   networking/http/response.h
   networking/http/signal.cpp
   networking/http/signal.h
   networking/http/status.cpp
   networking/http/status.h
   networking/http/stream.h
   networking/http/transaction.cpp
   networking/http/transaction.h
   networking/netserver/_.h
   networking/netserver/socket.cpp
   networking/netserver/socket.h
   networking/netserver/socket_handler.cpp
   networking/netserver/socket_handler.h
   networking/netserver/socket_thread.cpp
   networking/netserver/socket_thread.h
   networking/sockets/base/base_socket.cpp
   networking/sockets/base/base_socket.h
   networking/sockets/base/base_socket_handler.cpp
   networking/sockets/base/base_socket_handler.h
   networking/sockets/base/socket_thread.cpp
   networking/sockets/base/socket_thread.h
   networking/sockets/bsd/basic/_.h
   networking/sockets/bsd/basic/basic_net.cpp
   networking/sockets/bsd/basic/listen_socket.cpp
   networking/sockets/bsd/basic/listen_socket.h
   #net/sockets/bsd/basic/net.cpp
   #net/sockets/bsd/basic/net.h
   networking/sockets/bsd/basic/sctp_socket.cpp
   networking/sockets/bsd/basic/sctp_socket.h
   networking/sockets/bsd/basic/socket.cpp
   networking/sockets/bsd/basic/socket.h
   networking/sockets/bsd/basic/socket_handler.cpp
   networking/sockets/bsd/basic/socket_handler.h
   networking/sockets/bsd/basic/stream_socket.cpp
   networking/sockets/bsd/basic/stream_socket.h
   networking/sockets/bsd/basic/sync_socket_handler.cpp
   networking/sockets/bsd/basic/sync_socket_handler.h
   networking/sockets/bsd/basic/tcp_socket.cpp
   networking/sockets/bsd/basic/tcp_socket.h
   networking/sockets/bsd/basic/tls_socket.cpp
   networking/sockets/bsd/basic/tls_socket.h
   networking/sockets/bsd/basic/udp_socket.cpp
   networking/sockets/bsd/basic/udp_socket.h
   networking/sockets/bsd/dns/resolv_server.cpp
   networking/sockets/bsd/dns/resolv_server.h
   networking/sockets/bsd/dns/resolv_socket.cpp
   networking/sockets/bsd/dns/resolv_socket.h
   networking/sockets/bsd/ssl/client_context.cpp
   networking/sockets/bsd/ssl/client_context.h
   networking/sockets/bsd/ssl/client_context_map.cpp
   networking/sockets/bsd/ssl/client_context_map.h
   networking/sockets/bsd/ssl/context.cpp
   networking/sockets/bsd/ssl/context.h
   networking/sockets/bsd/ssl/initializer.cpp
   networking/sockets/bsd/ssl/initializer.h
   networking/sockets/bsd/ssl/ticket_key.h
   networking/sockets/bsd/webserver/httpd_socket.cpp
   networking/sockets/bsd/webserver/httpd_socket.h
   networking/sockets/bsd/_.h
   #networking/sockets/bsd/_strconv.cpp
   networking/sockets/bsd/_strconv.h
   networking/sockets/bsd/config.h
   #networking/sockets/bsd/include.cpp
   networking/sockets/bsd/socket_id_list.h
   networking/sockets/bsd/sockets.cpp
   networking/sockets/bsd/sockets.h
   networking/sockets/http/_.h
   networking/sockets/http/client_socket.cpp
   networking/sockets/http/client_socket.h
   networking/sockets/http/debug_socket.cpp
   networking/sockets/http/debug_socket.h
   networking/sockets/http/get_socket.cpp
   networking/sockets/http/get_socket.h
   networking/sockets/http/http_base_socket.cpp
   networking/sockets/http/http_base_socket.h
   networking/sockets/http/listener.cpp
   networking/sockets/http/listener.h
   networking/sockets/http/post_socket.cpp
   networking/sockets/http/post_socket.h
   networking/sockets/http/put_socket.cpp
   networking/sockets/http/put_socket.h
   networking/sockets/http/session.cpp
   networking/sockets/http/session.h
   networking/sockets/http/socket.cpp
   networking/sockets/http/socket.h
   networking/sockets/http/tunnel.cpp
   networking/sockets/http/tunnel.h
   networking/sockets/_.h
   networking/sockets/_system_sockets.cpp
   networking/sockets/http_batch_buffer.cpp
   networking/sockets/http_batch_buffer.h
   networking/sockets/http_buffer.h
   networking/sockets/link_in_socket.cpp
   networking/sockets/link_in_socket.h
   networking/sockets/link_out_socket.cpp
   networking/sockets/link_out_socket.h
   networking/sockets/logger.h
   networking/sockets/sockets_base.cpp
   networking/sockets/sockets_base.h
   #networking/sockets/trace_interface.cpp
   #networking/sockets/trace_interface.h
   networking/sockets/transfer_socket.cpp
   networking/sockets/transfer_socket.h
   networking/sockets/websocket_client.cpp
   networking/sockets/websocket_client.h
   networking/_.cpp
   networking/_.h
   networking/_impl.h
   networking/_networking_impl.h
   networking/address.cpp
   networking/address.h
   networking/address_department.cpp
   networking/address_department.h
   networking/byte_order.h
   networking/email.cpp
   networking/email.h
   networking/email_address.cpp
   networking/email_address.h
   networking/ip_enum.cpp
   networking/ip_enum.h
   networking/net.h
   networking/networking_application.cpp
   networking/networking_application.h
   networking/networking_application_handler.cpp
   networking/networking_application_handler.h
   networking/networking_application_socket.cpp
   networking/networking_application_socket.h
   networking/open_weather_city.h
   networking/port_forward.cpp
   networking/port_forward.h
   networking/sockets.cpp
   #operating_system/_.h
   #operating_system/_node.h
   operating_system/ansi/_.h
   operating_system/ansi/_ansi.h
   #operating_system/ansios/_c.h
   operating_system/ansi/ansi_file.h
   #operating_system/ansi/base.cpp
   # operating_system/ansios/callstack.h
   #operating_system/ansios/datetime.cpp
   #operating_system/ansios/datetime_c.h
   # operating_system/ansios/exception_engine.cpp
   # operating_system/ansios/exception_engine.h
   operating_system/ansi/file.cpp
   operating_system/ansi/file.h
   #operating_system/ansios/file_c.h
   #operating_system/ansi/language.cpp
   operating_system/ansi/parallelization.h
   #operating_system/ansios/process.cpp
   #operating_system/ansi/win.cpp
   operating_system/_.h
   operating_system/_application.cpp
   operating_system/_application.h
   #operating_system/_c2.h
   operating_system/_impl.h
   operating_system/_operating_system.h
   operating_system/apex.h
   #operating_system/argcargv.cpp
   operating_system/binreloc.h
   operating_system/cross.h
   operating_system/debug.cpp
   operating_system/file.h
   operating_system/graphics.h
   operating_system/http.cpp
   operating_system/openssl_crypt.cpp
   #operating_system/operating_system.h
   operating_system/operating_system.cpp
   #operating_system/os_windowing2.h
   #operating_system/process.h
   operating_system/text.h
   operating_system/thread.cpp
   operating_system/thread.h
   operating_system/windowing.h
   parallelization/_.cpp
   parallelization/_.h
   parallelization/_impl.h
   parallelization/common.h
   parallelization/create_thread.h
   parallelization/data.h
   parallelization/delay_thread.h
   parallelization/handler_manager.cpp
   parallelization/handler_manager.cpp
   parallelization/retry.h
   parallelization/service.cpp
   parallelization/service.h
   parallelization/service_handler.cpp
   parallelization/service_handler.h
   parallelization/service_status.h
   parallelization/thread.cpp
   parallelization/thread.h
   parallelization/thread_impl.h
   #parallelization/thread_os.cpp
   #parallelization/thread_os.h
   parallelization/threading.cpp
   parallelization/threading.h
   platform/_.cpp
   platform/_application_service.cpp
   platform/_impl.h
   platform/_platform.h
   #platform/_system_id_impl.h
   #platform/_system_object_impl.h
   #platform/_system_smart_pointer_impl.h
   #platform/_system_var_impl.h
   #platform/all.h
   platform/api.cpp
   platform/api.h
   platform/api_client.cpp
   platform/api_client.h
   platform/apex.cpp
   platform/apex.h
   platform/apex_aura.h
   #platform/apex_main_data.cpp
   #platform/apex_main_data.h
   #platform/apex_main_struct.cpp
   #platform/apex_main_struct.h
   #platform/app_core.cpp
   #platform/app_core.h
   platform/app_consumer.h
   platform/app_container.cpp
   platform/app_container.h
   platform/app_launcher.cpp
   platform/app_launcher.h
   platform/application.cpp
   platform/application.h
   platform/application_array.cpp
   platform/application_array.h
   platform/application_exit.cpp
   platform/application_exit.h
   platform/application_heap.h
   platform/application_impl.h
   platform/application_menu.cpp
   platform/application_menu.h
   platform/application_signal_details.h
   platform/assert_running_task.cpp
   platform/assert_running_task.h
   platform/async.h
   platform/aura_regex.h
   #platform/build_debug.cpp
   #platform/command_line.cpp
   #platform/command_line.h
   platform/console_application.cpp
   platform/console_application.h
   platform/context.cpp
   platform/context.h
   #platform/context_thread.cpp
   #platform/context_thread.h
   platform/create.cpp
   platform/create.h
   #platform/debug.cpp
   #platform/debug.h
   #platform/definition.h
   platform/display.h
   #platform/error.h
   platform/history.cpp
   platform/history.h
   #platform/hyperlink.h
   platform/interprocess_call.cpp
   platform/interprocess_call.h
   platform/interprocess_communication.cpp
   platform/interprocess_communication.h
   platform/interprocess_intercommunication.cpp
   platform/interprocess_intercommunication.h
   platform/interprocess_task.cpp
   platform/interprocess_task.h
   #platform/keep.h
   platform/launcher.cpp
   platform/launcher.h
   #platform/library_object_allocator.h
   platform/log.cpp
   platform/log.h
   platform/machine_event.cpp
   platform/machine_event.h
   platform/machine_event_central.cpp
   platform/machine_event_central.h
   platform/machine_event_data.cpp
   platform/machine_event_data.h
   #platform/main.cpp
   platform/message_box.h
   #platform/net.cpp
   #platform/net.h
   platform/node.cpp
   platform/node.h
   platform/os_context.cpp
   platform/os_context.h
   platform/os_history.cpp
   platform/os_history.h
   platform/savings.cpp
   platform/savings.h
   platform/session.cpp
   platform/session.h
   platform/shell_launcher.cpp
   platform/shell_launcher.h
   platform/simple_app.h
   #platform/simple_log.cpp
   #platform/simple_log.h
   #platform/static_start.cpp
   #platform/static_start.h
   #platform/static_start_apex.cpp
   platform/system.cpp
   platform/system.h
   #platform/text.cpp
   #platform/thread_set.h
   process/_.h
   process/department.cpp
   process/department.h
   process/process.cpp
   process/process.h
   progress/integer.cpp
   progress/integer.h
   progress/listener.cpp
   progress/listener.h
   progress/progress.cpp
   progress/progress.h
   progress/real.cpp
   progress/real.h
   progress/_.h
   template/list.h
   user/_.h
   user/_const_key.h
   #user/command.cpp
   user/command.h
   #user/control_event.cpp
   #user/control_event.h
   user/language.cpp
   user/language.h
   user/language_map.cpp
   user/language_map.h
   user/menu_shared.cpp
   user/menu_shared.h
   user/menu_shared_commnand.cpp
   user/menu_shared_command.h
   user/notify_icon_bridge.h
   user/primitive.cpp
   user/primitive.h
   version/version.config.h
   version/version.h
   #_.cpp
   _.h
   _defer.h
   aaa_want_to_move_xml.h
   application.h
   astr.h
   console.h
   console_slim.h
#   context_glx.cpp
   framework.cpp
   framework.h
   framework_c.h
   future.h
   id.h
   library.h
   message.h
   procedure.h
   #update.h
   user.h)


if (WIN32)

   list(APPEND apex_source
      #operating_system/windows/_.h
      #operating_system/windows/_node_windows.h
      #operating_system/windows/_node_windows_private.h
      #operating_system/windows/_windows.h
      #operating_system/windows/a.h
      #operating_system/windows/application.cpp
      #operating_system/windows/crypto.cpp
      #operating_system/windows/crypto.h
      #operating_system/windows/dir_context.cpp
      #operating_system/windows/dir_context.h
      #operating_system/windows/dir_system.cpp
      #operating_system/windows/dir_system.h
      #operating_system/windows/_factory.cpp
      #operating_system/windows/
      #operating_system/windows/file_context.cpp
      #operating_system/windows/file_context.h
      ##operating_system/windows/file_os_watcher.cpp
      ##operating_system/windows/file_os_watcher.h
      #operating_system/windows/file_system.cpp
      #operating_system/windows/file_system.h
      #operating_system/windows/folder_watch.h
      #operating_system/windows/ip_enum.cpp
      #operating_system/windows/ip_enum.h
      ##operating_system/windows/os_context.cpp
      ##operating_system/windows/os_context.h
      #operating_system/windows/process.cpp
      #operating_system/windows/process.h
      #operating_system/windows/thread.cpp
      #operating_system/windows/thread.h
      #operating_system/windows/timer.cpp
      #operating_system/windows/trace.cpp
      #operating_system/windows_common/application.cpp
#      operating_system/windows/_.cpp
#      operating_system/windows/_.h
#      operating_system/windows/_windows.h
#      operating_system/windows/application.cpp
#      operating_system/windows/application_system_run.cpp
#      operating_system/windows/dpi.cpp
#      operating_system/windows/gdi.cpp
      #operating_system/windows/interprocess_communication.cpp
      #operating_system/windows/launcher.cpp
      #operating_system/windows/library.cpp
#      operating_system/windows/main.cpp
#      operating_system/windows/menu.cpp
      #operating_system/windows/shell_launcher.cpp
#      operating_system/windows/thread.cpp
#      operating_system/windows/user.cpp
#      operating_system/windows/windowing.cpp
#      operating_system/windows/windowing.h
#      operating_system/windows_common/_.h
#      operating_system/windows_common/_windows_common.h
#      operating_system/windows_common/file.cpp
      #operating_system/win32/_.h
      #operating_system/win32/dialog.cpp
      #operating_system/win32/dialog.h
      #operating_system/win32/font.cpp
      #operating_system/win32/font.h
      #operating_system/win32/window.cpp
      #operating_system/win32/window.h
      )
else ()

   list(APPEND apex_source
      operating_system/cross/windows/windows_thread.h
      operating_system/cross/windows/windows_thread_impl.h
      operating_system/cross/cross.h
      operating_system/winpr_input.h
      #operating_system/winpr_keycode.cpp
      #operating_system/winpr_scancode.cpp
      )

endif ()


if (UWP)
   list(APPEND apex_source
      crypto/winrt/_winrt.h
      crypto/winrt/crypto.cpp
      crypto/winrt/hasher.cpp
      crypto/winrt/hasher.h
      crypto/winrt/hasher_algorithm.cpp
      crypto/winrt/hasher_algorithm.h
      crypto/winrt/rsa.cpp
      crypto/winrt/rsa.h
      net/sockets/winrt/asynch_dns/resolv_server.cpp
      net/sockets/winrt/asynch_dns/resolv_server.h
      net/sockets/winrt/asynch_dns/resolv_socket.cpp
      net/sockets/winrt/asynch_dns/resolv_socket.h
      net/sockets/winrt/basic/listen_socket.cpp
      net/sockets/winrt/basic/listen_socket.h
      net/sockets/winrt/basic/net.cpp
      net/sockets/winrt/basic/net.h
      net/sockets/winrt/basic/sctp_socket.cpp
      net/sockets/winrt/basic/sctp_socket.h
      net/sockets/winrt/basic/Socket.cpp
      net/sockets/winrt/basic/socket.h
      net/sockets/winrt/basic/socket_handler.cpp
      net/sockets/winrt/basic/socket_handler.h
      net/sockets/winrt/basic/stream_socket.cpp
      net/sockets/winrt/basic/stream_socket.h
      net/sockets/winrt/basic/sync_socket_handler.cpp
      net/sockets/winrt/basic/sync_socket_handler.h
      net/sockets/winrt/basic/tcp_socket.cpp
      net/sockets/winrt/basic/tcp_socket.h
      net/sockets/winrt/basic/tls_socket.cpp
      net/sockets/winrt/basic/tls_socket.h
      net/sockets/winrt/basic/udp_socket.cpp
      net/sockets/winrt/basic/udp_socket.h
      net/sockets/winrt/sip/base.cpp
      net/sockets/winrt/sip/base.h
      net/sockets/winrt/sip/base_client_socket.cpp
      net/sockets/winrt/sip/base_client_socket.h
      net/sockets/winrt/sip/callback.cpp
      net/sockets/winrt/sip/callback.h
      net/sockets/winrt/sip/client.cpp
      net/sockets/winrt/sip/client.h
      net/sockets/winrt/sip/event.h
      net/sockets/winrt/sip/request.cpp
      net/sockets/winrt/sip/request.h
      net/sockets/winrt/sip/response.cpp
      net/sockets/winrt/sip/response.h
      net/sockets/winrt/sip/server.cpp
      net/sockets/winrt/sip/server.h
      net/sockets/winrt/sip/socket.h
      net/sockets/winrt/sip/tcp_client_socket.cpp
      net/sockets/winrt/sip/tcp_client_socket.h
      net/sockets/winrt/sip/transaction.cpp
      net/sockets/winrt/sip/transaction.h
      net/sockets/winrt/sip/udp_client_socket.cpp
      net/sockets/winrt/sip/udp_client_socket.h
      net/sockets/winrt/smtp/smtpd_socket.cpp
      net/sockets/winrt/smtp/smtpd_socket.h
      net/sockets/winrt/smtp/socket.cpp
      net/sockets/winrt/smtp/socket.h
      net/sockets/winrt/timer/Event.cpp
      net/sockets/winrt/timer/event.h
      net/sockets/winrt/timer/event_handler.h
      net/sockets/winrt/timer/event_time.h
      net/sockets/winrt/timer/EventHandler.cpp
      net/sockets/winrt/timer/EventTime.cpp
      net/sockets/winrt/timer/ievent_handler.h
      net/sockets/winrt/timer/ievent_owner.h
      net/sockets/winrt/timer/IEventOwner.cpp
      net/sockets/winrt/webserver/ajp13.h
      net/sockets/winrt/webserver/ajp13_socket.h
      net/sockets/winrt/webserver/Ajp13Socket.cpp
      net/sockets/winrt/webserver/ajp_base_socket.h
      net/sockets/winrt/webserver/AjpBaseSocket.cpp
      net/sockets/winrt/webserver/httpd_socket.cpp
      net/sockets/winrt/webserver/httpd_socket.h
      net/sockets/winrt/_.h
      net/sockets/winrt/config.h
      net/sockets/winrt/include.cpp
      net/sockets/winrt/sockets.cpp
      net/sockets/winrt/sockets.h
      operating_system/universal_windows/net/net_address.h
      operating_system/universal_windows/_.h
      operating_system/universal_windows/_aaa_want_to_remove_node_metrowin.cpp
      operating_system/universal_windows/_uwp.h
      operating_system/universal_windows/app_core.cpp
      operating_system/universal_windows/application.cpp
      operating_system/universal_windows/application.h
      operating_system/universal_windows/command.cpp
      operating_system/universal_windows/dir_context.cpp
      operating_system/universal_windows/dir_context.h
      operating_system/universal_windows/dir_system.cpp
      operating_system/universal_windows/dir_system.h
      operating_system/universal_windows/directx.cpp
      operating_system/universal_windows/directx_application.cpp
      operating_system/universal_windows/directx_impact.cpp
      operating_system/universal_windows/directx_interaction.cpp
      operating_system/universal_windows/error.cpp
      operating_system/universal_windows/_factory.cpp
      operating_system/universal_windows/
      operating_system/universal_windows/file_context.cpp
      operating_system/universal_windows/file_context.h
      operating_system/universal_windows/file_find.cpp
      operating_system/universal_windows/file_system.cpp
      operating_system/universal_windows/file_system.h
      operating_system/universal_windows/file_watcher.cpp
      operating_system/universal_windows/file_watcher.h
      operating_system/universal_windows/folder_watch.cpp
      operating_system/universal_windows/graphics_buffer.cpp
      operating_system/universal_windows/native_buffer.cpp
      operating_system/universal_windows/os_context.cpp
      operating_system/universal_windows/os_context.h
      operating_system/universal_windows/registry.cpp
      operating_system/universal_windows/shell.cpp
      operating_system/universal_windows/shell_uwp.cpp
      operating_system/universal_windows/thread.cpp
      operating_system/universal_windows/thread.h
      operating_system/universal_windows/timer.cpp
      operating_system/universal_windows/trace.cpp
      operating_system/universal_windows/tts_speaker.cpp
      operating_system/universal_windows/uac_tools.cpp
      operating_system/universal_windows/util.cpp
      operating_system/universal_windows/_.h
      operating_system/universal_windows/_uwp.h
      operating_system/universal_windows/_winrt.h
      operating_system/universal_windows/apex.cpp
      operating_system/universal_windows/application_system_run.cpp
      operating_system/universal_windows/base_file.h
      operating_system/universal_windows/direct2d_tls.cpp
      operating_system/universal_windows/dummy_ipc.cpp
      operating_system/universal_windows/gdi_winrt.h
      operating_system/universal_windows/host_interaction.h
      operating_system/universal_windows/language.cpp
      operating_system/universal_windows/launcher.cpp
      operating_system/universal_windows/library.cpp
      operating_system/universal_windows/lock.cpp
      operating_system/universal_windows/main.cpp
      operating_system/universal_windows/menu.cpp
      operating_system/universal_windows/metrowin_metrowin.h
      operating_system/universal_windows/parallelization.cpp
      operating_system/universal_windows/parallelization.h
      #operating_system/universal_windows/process.cpp
      #operating_system/universal_windows/process.h
      operating_system/universal_windows/simple_app.cpp
      operating_system/universal_windows/simple_hold_handle.h
      operating_system/universal_windows/simple_shell_launcher.cpp
      operating_system/universal_windows/simple_ui.h
      operating_system/universal_windows/small_ipca_channel.cpp
      operating_system/universal_windows/sockets.cpp
      operating_system/universal_windows/sockets.h
      operating_system/universal_windows/time.cpp
      operating_system/universal_windows/user.cpp)

else ()

   list(APPEND apex_source
      #operating_system/cross/universal_windows/cross_metrowin_user.cpp
      #operating_system/cross/universal_windows/metrowin_user.cpp
      )

endif ()


if (LINUX)

   list(APPEND apex_source
      operating_system/linux/
      operating_system/linux/_.h
      operating_system/linux/_.h
      operating_system/linux/_c.h
      operating_system/linux/_factory.cpp
      operating_system/linux/_linux.h
      operating_system/linux/_linux.h
      operating_system/linux/_user.h
      operating_system/linux/apex.cpp
      operating_system/linux/application.cpp
      operating_system/linux/application.h
      operating_system/linux/application_system_run.cpp
      operating_system/linux/callstack.cpp
      operating_system/linux/cross_win_file.cpp
      operating_system/linux/cross_win_file.h
      operating_system/linux/cross_win_gdi.cpp
      operating_system/linux/cross_win_gdi.h
      operating_system/linux/cross_win_gdi_internal.h
      operating_system/linux/debug.cpp
      operating_system/linux/debug.h
      operating_system/linux/dumpinit.cpp
      operating_system/linux/error.cpp
      operating_system/linux/exception.cpp
      operating_system/linux/file.cpp
      operating_system/linux/file.h
      operating_system/linux/graphics.cpp
      operating_system/linux/graphics.h
      operating_system/linux/graphics2.h
      operating_system/linux/internal.h
      #operating_system/linux/language.cpp
      operating_system/linux/linux.cpp
      operating_system/linux/linux_linux.h
      operating_system/linux/menu.cpp
      operating_system/linux/message_loop.cpp
      operating_system/linux/os.cpp
      operating_system/linux/parallelization.cpp
      operating_system/linux/parallelization.h
      operating_system/linux/root_tools.cpp
      operating_system/linux/root_tools.h
      operating_system/linux/shell_launcher.cpp
      operating_system/linux/shell_launcher.h
      operating_system/linux/simple_app.cpp
      operating_system/linux/standard_exception.cpp
      operating_system/linux/thread.cpp
      operating_system/linux/time.cpp
      operating_system/linux/trace.cpp
      operating_system/linux/user.cpp
      operating_system/linux/user.h
      operating_system/linux/user_private.h
      operating_system/linux/util.cpp
      operating_system/linux/win_base.cpp
      operating_system/posix/_.h
      operating_system/posix/_posix.h
      )
endif ()


if (MACOS)

   list(APPEND apex_source
      crypto/macos/rsa.cpp
      crypto/macos/rsa.h
      #operating_system/macos/_.h
      #operating_system/macos/_macos.h
      #operating_system/macos/_mm.h
      #operating_system/macos/apex_window.h
      #operating_system/macos/apex_window.mm
      #operating_system/macos/ApexWindow.h
      #operating_system/macos/ApexWindow.mm
      #operating_system/macos/ApexWindowApp.h
      #operating_system/macos/ApexWindowApp.mm
      #operating_system/macos/ApexWindowController.h
      #operating_system/macos/ApexWindowController.mm
      #operating_system/macos/ApexWindowFrameView.h
      #operating_system/macos/ApexWindowFrameView.mm
      #operating_system/macos/app.mm
      #operating_system/macos/application.cpp
      #operating_system/macos/application.h
      #operating_system/macos/dir_context.cpp
      #operating_system/macos/dir_context.h
      #operating_system/macos/dir_system.cpp
      #operating_system/macos/dir_system.h
      #operating_system/macos/_factory.cpp
      #operating_system/macos/
      #operating_system/macos/file.cpp
      #operating_system/macos/file_context.cpp
      #operating_system/macos/file_context.h
      #operating_system/macos/file_os_watcher.cpp
      #operating_system/macos/file_os_watcher.h
      #operating_system/macos/file_system.cpp
      #operating_system/macos/file_system.h
      #operating_system/macos/keyboard.cpp
      #operating_system/macos/keyboard.h
      #operating_system/macos/keyboard_mm.mm
      #operating_system/macos/main.cpp
      #operating_system/macos/os_context.cpp
      #operating_system/macos/os_context.h
      #operating_system/macos/shell_macos_mm.mm
      #operating_system/macos/stdio_file.cpp
      #operating_system/macos/stdio_file.h
      #operating_system/macos/thread.cpp
      #operating_system/macos/thread.h
      #operating_system/macos/trace.cpp
      #operating_system/macos/user.h
      #operating_system/macos/util.cpp
      #operating_system/macos/_.h
      #operating_system/macos/_c.h
      #operating_system/macos/_macos.h
      #operating_system/macos/_mm.h
      #operating_system/macos/application_system_run.cpp
      #operating_system/macos/aura.cpp
      #operating_system/macos/clipboard.cpp
      #operating_system/macos/cross_win.cpp
      #operating_system/macos/cross_win_file.cpp
      #operating_system/macos/cross_win_gdi.h
      #operating_system/macos/debug.cpp
      #operating_system/macos/exception_engine.cpp
      #operating_system/macos/exception_engine.h
      #operating_system/macos/file.cpp
      #operating_system/macos/file.h
      #operating_system/macos/file.mm
      #operating_system/macos/graphics_mm.h
      #operating_system/macos/internal.h
      #operating_system/macos/keyboard.cpp
      #operating_system/macos/language.cpp
      #operating_system/macos/launcher.cpp
      #operating_system/macos/library.cpp
      #operating_system/macos/list_serial_ports.cpp
      #operating_system/macos/lock.cpp
      #operating_system/macos/macos.h
      #operating_system/macos/main.h
      #operating_system/macos/MessageBoxA.cpp
      #operating_system/macos/mm.mm
      #operating_system/macos/mm_graphics.mm
      #operating_system/macos/mm_oswindow.h
      #operating_system/macos/parallelization.cpp
      #operating_system/macos/parallelization.h
      #operating_system/macos/NSPasteboard++.mm
      #operating_system/macos/os.cpp
      #operating_system/macos/os.h
      ##operating_system/macos/process.cpp
      ##operating_system/macos/process_c.h
      ##operating_system/macos/process_pid.cpp
      #operating_system/macos/simple_app.cpp
      #operating_system/macos/simple_shell_launcher.cpp
      #operating_system/macos/small_ipca_channel.cpp
      #operating_system/macos/time.cpp
      #operating_system/macos/user.cpp
      #operating_system/macos/user.h
      #operating_system/macos/win_base.cpp
      #operating_system/macos/window_impl.h
      #operating_system/macos/windowing.h
      #operating_system/macos/windowing_c.h
      #operating_system/macos/winpr_keycode.cpp

      )


endif ()


if(LINUX OR FREEBSD OR MACOS)

   list(APPEND apex_source
     operating_system/freedesktop/desktop_file.cpp
     operating_system/freedesktop/desktop_file.h
     )

endif()


if (IOS)
   list(APPEND apex_source
      ios_aura/ios_aura.h
      ios_aura/ios_aura.m
      operating_system/ios/_.h
      operating_system/ios/_ios.h
      operating_system/ios/_m.h
      operating_system/ios/_mm.h
      operating_system/ios/application.cpp
      operating_system/ios/application.h
      operating_system/ios/dir_context.cpp
      operating_system/ios/dir_context.h
      operating_system/ios/dir_system.cpp
      operating_system/ios/dir_system.h
      operating_system/ios/exception.cpp
      operating_system/ios/_factory.cpp
      operating_system/ios/
      operating_system/ios/file.cpp
      operating_system/ios/file.h
      operating_system/ios/file_context.cpp
      operating_system/ios/file_context.h
      operating_system/ios/file_os_watcher.cpp
      operating_system/ios/file_os_watcher.h
      operating_system/ios/file_system.cpp
      operating_system/ios/file_system.h
      operating_system/ios/host_interaction.cpp
      operating_system/ios/implementation.h
      operating_system/ios/internal.h
      operating_system/ios/ios.cpp
      operating_system/ios/ip_enum.cpp
      operating_system/ios/ip_enum.h
      operating_system/ios/main.cpp
      operating_system/ios/os_context.cpp
      operating_system/ios/os_context.h
      operating_system/ios/plane_system.cpp
      operating_system/ios/plane_system.h
      operating_system/ios/round_window.mm
      operating_system/ios/RoundCaretView.h
      operating_system/ios/RoundWindow.mm
      operating_system/ios/RoundWindowApp.h
      operating_system/ios/RoundWindowApp.mm
      operating_system/ios/state.h
      operating_system/ios/thread.cpp
      operating_system/ios/thread.h
      operating_system/ios/trace.cpp
      operating_system/ios/util.cpp
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
      operating_system/ios/mm_oswindow.h
      operating_system/ios/mm_thread.mm
      operating_system/ios/mm_user.mm
      operating_system/ios/parallelization.cpp
      operating_system/ios/parallelization.h
      operating_system/ios/oswindow_data.cpp
      operating_system/ios/oswindow_data.h
      #operating_system/ios/process.cpp
      #operating_system/ios/process.h
      #operating_system/ios/process_pid.cpp
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
      operating_system/ios/windowing.h)

endif ()


if (ANDROID)
   list(APPEND apex_source
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
      operating_system/android/parallelization.cpp
      #operating_system/android/process.cpp
      #operating_system/android/process.h
      #operating_system/android/process_pid.cpp
      operating_system/android/simple_shell_launcher.cpp
      operating_system/android/small_ipca_channel.cpp
      operating_system/android/view_bitmap.h
      operating_system/android/win_base.cpp
      operating_system/android/window_android.cpp
      operating_system/android/window_android.h
      operating_system/android/window_impl.cpp
      operating_system/android/windowing.cpp
      operating_system/android/windowing.h
      )

endif ()



if (FREEBSD)

   list(APPEND apex_source
      operating_system/freebsd/_.h
      operating_system/freebsd/_freebsd.h
      operating_system/freebsd/application.cpp
      operating_system/freebsd/application.h
      #operating_system/freebsd/dir_context.cpp
      #operating_system/freebsd/dir_context.h
      #operating_system/freebsd/dir_system.cpp
      #operating_system/freebsd/dir_system.h
      operating_system/freebsd/dumpinit.cpp
      operating_system/freebsd/error.cpp
      operating_system/freebsd/exception.cpp
      operating_system/freebsd/_factory.cpp
      operating_system/freebsd/
      #operating_system/freebsd/file_context.cpp
      #operating_system/freebsd/file_context.h
      #operating_system/freebsd/file_system.cpp
      #operating_system/freebsd/file_system.h
      #operating_system/freebsd/frame_window.cpp
      operating_system/freebsd/internal.h
      operating_system/freebsd/freebsd.cpp
      #operating_system/freebsd/os_context.cpp
      #operating_system/freebsd/os_context.h
      #operating_system/freebsd/process.cpp
      #operating_system/freebsd/process.h
      operating_system/freebsd/root_tools.cpp
      operating_system/freebsd/root_tools.h
      operating_system/freebsd/thread.cpp
      operating_system/freebsd/parallelization.h
      operating_system/freebsd/trace.cpp
      operating_system/freebsd/util.cpp
      #operating_system/posix/file_os_watcher.cpp
      #operating_system/posix/file_os_watcher.cpp
      operating_system/posix/_posix.h
      operating_system/posix/_.h
      operating_system/freebsd/_.h
      operating_system/freebsd/_c.h
      operating_system/freebsd/_freebsd.h
      operating_system/freebsd/_user.h
      operating_system/freebsd/apex.cpp
      operating_system/freebsd/application_system_run.cpp
      operating_system/freebsd/callstack.cpp
      operating_system/freebsd/cross_win_file.cpp
      operating_system/freebsd/cross_win_file.h
      operating_system/freebsd/cross_win_gdi.cpp
      operating_system/freebsd/cross_win_gdi.h
      operating_system/freebsd/cross_win_gdi_internal.h
      operating_system/freebsd/debug.cpp
      operating_system/freebsd/debug.h
      # operating_system/freebsd/exception_engine.cpp
      # operating_system/freebsd/exception_engine.h
      operating_system/freebsd/file.cpp
      operating_system/freebsd/file.h
      operating_system/freebsd/graphics.cpp
      operating_system/freebsd/graphics.h
      operating_system/freebsd/graphics2.h
      operating_system/freebsd/language.cpp
      #operating_system/freebsd/library.cpp
      operating_system/freebsd/freebsd_freebsd.h
      #operating_system/freebsd/lock.cpp
      operating_system/freebsd/menu.cpp
      operating_system/freebsd/message_loop.cpp
      operating_system/freebsd/parallelization.cpp
      operating_system/freebsd/os.cpp
      #operating_system/freebsd/process.cpp
      #operating_system/freebsd/process.h
      #operating_system/freebsd/process_pid.cpp
      operating_system/freebsd/simple_app.cpp
      operating_system/freebsd/shell_launcher.cpp
      operating_system/freebsd/shell_launcher.h
      operating_system/freebsd/standard_exception.cpp
      #operating_system/freebsd/interprocess_communication.cpp
      operating_system/freebsd/time.cpp
      operating_system/freebsd/user.cpp
      operating_system/freebsd/user.h
      operating_system/freebsd/user_private.h
      operating_system/freebsd/win_base.cpp)
endif ()



if (APPLE)
   list(APPEND apex_source
      #timer.mm
      #operating_system/apple/apple_timer.cpp
      #operating_system/apple/process.cpp
      #operating_system/apple/process.h
      #operating_system/apple/_.cpp
      #operating_system/apple/_.h
      #operating_system/apple/_apple.h
      #operating_system/apple/_apple.mm
      #operating_system/apple/_c_mm.h
      #operating_system/apple/_mm.h
      #operating_system/apple/_mm_common.h
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
      ##operating_system/apple/process.cpp
      #operating_system/apple/time.cpp
      #operating_system/apple/time.h
      )

endif ()

#if (USE_OPENSSL)
#   list(APPEND apex_source
#      crypto/openssl/_.cpp
#      crypto/openssl/_openssl.h
#      crypto/openssl/crypto.cpp
#      crypto/openssl/hasher.cpp
#      crypto/openssl/hasher.h
#      crypto/openssl/hasher_algorithm.cpp
#      crypto/openssl/hasher_algorithm.h
#      crypto/openssl/rsa.cpp
#      crypto/openssl/rsa.h
#      )
#endif ()


if (SOLARIS)
   list(APPEND apex_source
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
      #operating_system/solaris/solaris_process.cpp
      #operating_system/solaris/solaris_process.h
      #operating_system/solaris/solaris_process_pid.cpp
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

endif ()


if (PTHREAD)

   list(APPEND apex_source
      #operating_system/posix/pthread.cpp
      )

endif ()


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


add_library(apex SHARED ${apex_source} )

target_precompile_headers(apex PRIVATE framework.h)

set_target_properties(apex PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(apex PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(apex PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(apex PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/apex.lib")
   target_link_options(apex PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/apex.def")
   target_link_libraries(apex PRIVATE acme zlib libcrypto libssl dwrite d2d1 d3d11 dxgi Dxva2 dbghelp imagehlp dwmapi Setupapi Windowscodecs Winmm ws2_32 Crypt32 Normaliz version Secur32 gdiplus Shlwapi Imm32)
elseif(LINUX OR FREEBSD)

   if(NOT DONT_USE_PKG_CONFIG)
      pkg_check_modules(PKGCONFIG libcrypto libssl)
   endif()
   target_compile_options(apex PRIVATE -fpermissive)
   target_compile_options(apex PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(apex PRIVATE ${PKGCONFIG_LDFLAGS})
   #target_link_options(apex PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(apex PRIVATE dl pthread idn z)
   target_link_libraries(apex PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(apex PRIVATE acme)
   target_link_options(apex PRIVATE -Wl,-z,defs)
   message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif ()


target_include_directories(apex PRIVATE .)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(apex PRIVATE _APEX_LIBRARY)


