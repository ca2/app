cmake_minimum_required(VERSION 3.17)
project(apex CXX)


if (LINUX)
   set(USE_OPENSSL TRUE)
   set(PTHREAD TRUE)
elseif (WIN32)
   set(USE_OPENSSL TRUE)
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
   compress/context.cpp
   compress/context.h
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
   crypto/hasher.cpp
   crypto/hasher.h
   crypto/hasher_algorithm.cpp
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
   database/id.cpp
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
   message/base.cpp
   message/base.h
   message/channel.cpp
   message/channel.h
   message/command_target.cpp
   message/command_ui_probe.cpp
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
   message/id.cpp
   message/id.h
   message/listener_smart_pointer_array.h
   message/message.cpp
   message/message.h
   message/receiver.cpp
   message/receiver.h
   #message/route.h
   message/sender.cpp
   message/simple_command.cpp
   message/simple_command.h
   networking/http/_.cpp
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
   networking/http/ostream.cpp
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
   networking/sockets/bsd/_strconv.cpp
   networking/sockets/bsd/_strconv.h
   networking/sockets/bsd/config.h
   networking/sockets/bsd/include.cpp
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
   networking/open_weather_city.h
   networking/port_forward.cpp
   networking/port_forward.h
   networking/sockets.cpp
   #node/_.h
   #node/_node.h
   node/operating_system/ansi/_.h
   node/operating_system/ansi/_ansi.h
   #os/ansios/_c.h
   node/operating_system/ansi/ansi_file.h
   node/operating_system/ansi/base.cpp
   # os/ansios/callstack.h
   #os/ansios/datetime.cpp
   #os/ansios/datetime_c.h
   # os/ansios/exception_engine.cpp
   # os/ansios/exception_engine.h
   node/operating_system/ansi/file.cpp
   node/operating_system/ansi/file.h
   #os/ansios/file_c.h
   node/operating_system/ansi/language.cpp
   node/operating_system/ansi/parallelization.h
   #os/ansios/process.cpp
   node/operating_system/ansi/win.cpp
   node/operating_system/_.h
   node/operating_system/_application.cpp
   node/operating_system/_application.h
   #node/operating_system/_c2.h
   node/operating_system/_impl.h
   node/operating_system/_operating_system.h
   node/operating_system/apex.h
   #os/argcargv.cpp
   node/operating_system/binreloc.h
   node/operating_system/cross.h
   node/operating_system/debug.cpp
   node/operating_system/file.h
   node/operating_system/graphics.h
   node/operating_system/http.cpp
   node/operating_system/openssl_crypt.cpp
   node/operating_system/operating_system.h
   node/operating_system/operating_system.cpp
   #node/operating_system/os_windowing2.h
   #os/process.h
   node/operating_system/text.h
   node/operating_system/thread.cpp
   node/operating_system/thread.h
   node/operating_system/windowing.h
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
   parallelization/thread_os.cpp
   parallelization/thread_os.h
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
   platform/apex_aura.h
   platform/apex_main_data.cpp
   platform/apex_main_data.h
   platform/apex_main_struct.cpp
   platform/apex_main_struct.h
   platform/app_core.cpp
   platform/app_core.h
   platform/app_launcher.cpp
   platform/app_launcher.h
   platform/application.cpp
   platform/application.h
   platform/application_array.cpp
   platform/application_array.h
   platform/application_consumer.h
   platform/application_container.cpp
   platform/application_container.h
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
   platform/build_debug.cpp
   platform/command_line.cpp
   platform/command_line.h
   platform/console_application.cpp
   platform/console_application.h
   platform/context.cpp
   platform/context.h
   platform/context_thread.cpp
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
   platform/net.cpp
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
   platform/static_start.cpp
   platform/static_start.h
   platform/static_start_apex.cpp
   platform/system.cpp
   platform/system.h
   platform/text.cpp
   platform/thread_set.h
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
   subject/context.cpp
   subject/context.h
   subject/manager.cpp
   subject/manager.h
   subject/process.cpp
   subject/promise.cpp
   subject/promise.h
   subject/routine.cpp
   subject/signal.cpp
   subject/signal.h
   subject/source.cpp
   subject/source.h
   template/list.h
   user/_.h
   user/_const_key.h
   user/command.cpp
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
   _.cpp
   _.h
   _defer.h
   aaa_want_to_move_xml.h
   application.h
   astr.h
   console.h
   console_slim.h
   context_glx.cpp
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
      #node/windows/_.h
      #node/windows/_node_windows.h
      #node/windows/_node_windows_private.h
      #node/windows/_windows.h
      #node/windows/a.h
      #node/windows/application.cpp
      #node/windows/crypto.cpp
      #node/windows/crypto.h
      #node/windows/dir_context.cpp
      #node/windows/dir_context.h
      #node/windows/dir_system.cpp
      #node/windows/dir_system.h
      #node/windows/_factory.cpp
      #node/windows/
      #node/windows/file_context.cpp
      #node/windows/file_context.h
      ##node/windows/file_os_watcher.cpp
      ##node/windows/file_os_watcher.h
      #node/windows/file_system.cpp
      #node/windows/file_system.h
      #node/windows/folder_watch.h
      #node/windows/ip_enum.cpp
      #node/windows/ip_enum.h
      ##node/windows/os_context.cpp
      ##node/windows/os_context.h
      #node/windows/process.cpp
      #node/windows/process.h
      #node/windows/thread.cpp
      #node/windows/thread.h
      #node/windows/timer.cpp
      #node/windows/trace.cpp
      #node/windows_common/application.cpp
      os/windows/_.cpp
      os/windows/_.h
      os/windows/_windows.h
      os/windows/application.cpp
      os/windows/application_system_run.cpp
      os/windows/dpi.cpp
      os/windows/gdi.cpp
      #os/windows/interprocess_communication.cpp
      #os/windows/launcher.cpp
      #os/windows/library.cpp
      os/windows/main.cpp
      os/windows/menu.cpp
      #os/windows/shell_launcher.cpp
      os/windows/thread.cpp
      os/windows/user.cpp
      os/windows/windowing.cpp
      os/windows/windowing.h
      os/windows_common/_.h
      os/windows_common/_windows_common.h
      os/windows_common/file.cpp
      #os/win32/_.h
      #os/win32/dialog.cpp
      #os/win32/dialog.h
      #os/win32/font.cpp
      #os/win32/font.h
      #os/win32/window.cpp
      #os/win32/window.h
      )
else ()

   list(APPEND apex_source
      node/operating_system/cross/windows/windows_thread.h
      node/operating_system/cross/windows/windows_thread_impl.h
      node/operating_system/cross/cross.h
      node/operating_system/winpr_input.h
      #os/winpr_keycode.cpp
      #os/winpr_scancode.cpp
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
      node/universal_windows/net/net_address.h
      node/universal_windows/_.h
      node/universal_windows/_aaa_want_to_remove_node_metrowin.cpp
      node/universal_windows/_uwp.h
      node/universal_windows/app_core.cpp
      node/universal_windows/application.cpp
      node/universal_windows/application.h
      node/universal_windows/command.cpp
      node/universal_windows/dir_context.cpp
      node/universal_windows/dir_context.h
      node/universal_windows/dir_system.cpp
      node/universal_windows/dir_system.h
      node/universal_windows/directx.cpp
      node/universal_windows/directx_application.cpp
      node/universal_windows/directx_impact.cpp
      node/universal_windows/directx_interaction.cpp
      node/universal_windows/error.cpp
      node/universal_windows/_factory.cpp
      node/universal_windows/
      node/universal_windows/file_context.cpp
      node/universal_windows/file_context.h
      node/universal_windows/file_find.cpp
      node/universal_windows/file_system.cpp
      node/universal_windows/file_system.h
      node/universal_windows/file_watcher.cpp
      node/universal_windows/file_watcher.h
      node/universal_windows/folder_watch.cpp
      node/universal_windows/graphics_buffer.cpp
      node/universal_windows/native_buffer.cpp
      node/universal_windows/os_context.cpp
      node/universal_windows/os_context.h
      node/universal_windows/registry.cpp
      node/universal_windows/shell.cpp
      node/universal_windows/shell_uwp.cpp
      node/universal_windows/thread.cpp
      node/universal_windows/thread.h
      node/universal_windows/timer.cpp
      node/universal_windows/trace.cpp
      node/universal_windows/tts_speaker.cpp
      node/universal_windows/uac_tools.cpp
      node/universal_windows/util.cpp
      os/universal_windows/_.h
      os/universal_windows/_uwp.h
      os/universal_windows/_winrt.h
      os/universal_windows/apex.cpp
      os/universal_windows/application_system_run.cpp
      os/universal_windows/base_file.h
      os/universal_windows/direct2d_tls.cpp
      os/universal_windows/dummy_ipc.cpp
      os/universal_windows/gdi_winrt.h
      os/universal_windows/host_interaction.h
      os/universal_windows/language.cpp
      os/universal_windows/launcher.cpp
      os/universal_windows/library.cpp
      os/universal_windows/lock.cpp
      os/universal_windows/main.cpp
      os/universal_windows/menu.cpp
      os/universal_windows/metrowin_metrowin.h
      os/universal_windows/parallelization.cpp
      os/universal_windows/parallelization.h
      #os/universal_windows/process.cpp
      #os/universal_windows/process.h
      os/universal_windows/simple_app.cpp
      os/universal_windows/simple_hold_handle.h
      os/universal_windows/simple_shell_launcher.cpp
      os/universal_windows/simple_ui.h
      os/universal_windows/small_ipca_channel.cpp
      os/universal_windows/sockets.cpp
      os/universal_windows/sockets.h
      os/universal_windows/time.cpp
      os/universal_windows/user.cpp)

else ()

   list(APPEND apex_source
      #node/operating_system/cross/universal_windows/cross_metrowin_user.cpp
      #node/operating_system/cross/universal_windows/metrowin_user.cpp
      )

endif ()


if (LINUX)

   list(APPEND apex_source
      node/linux/_.h
      node/linux/_linux.h
      node/linux/application.cpp
      node/linux/application.h
      #node/linux/dir_context.cpp
      #node/linux/dir_context.h
      #node/linux/dir_system.cpp
      #node/linux/dir_system.h
      node/linux/dumpinit.cpp
      node/linux/error.cpp
      node/linux/exception.cpp
      node/linux/_factory.cpp
      node/linux/
      #node/linux/file_context.cpp
      #node/linux/file_context.h
      #node/linux/file_system.cpp
      #node/linux/file_system.h
      #node/linux/frame_window.cpp
      node/linux/internal.h
      node/linux/linux.cpp
      #node/linux/os_context.cpp
      #node/linux/os_context.h
      #node/linux/process.cpp
      #node/linux/process.h
      node/linux/root_tools.cpp
      node/linux/root_tools.h
      node/linux/thread.cpp
      node/linux/parallelization.h
      node/linux/trace.cpp
      node/linux/util.cpp
      #node/posix/file_os_watcher.cpp
      #node/posix/file_os_watcher.cpp
      node/operating_system/posix/_posix.h
      node/operating_system/posix/_.h
      node/operating_system/linux/_.h
      node/operating_system/linux/_c.h
      node/operating_system/linux/_linux.h
      node/operating_system/linux/_user.h
      node/operating_system/linux/apex.cpp
      node/operating_system/linux/application_system_run.cpp
      node/operating_system/linux/callstack.cpp
      node/operating_system/linux/cross_win_file.cpp
      node/operating_system/linux/cross_win_file.h
      node/operating_system/linux/cross_win_gdi.cpp
      node/operating_system/linux/cross_win_gdi.h
      node/operating_system/linux/cross_win_gdi_internal.h
      node/operating_system/linux/debug.cpp
      node/operating_system/linux/debug.h
      # os/linux/exception_engine.cpp
      # os/linux/exception_engine.h
      node/operating_system/linux/file.cpp
      node/operating_system/linux/file.h
      node/operating_system/linux/graphics.cpp
      node/operating_system/linux/graphics.h
      node/operating_system/linux/graphics2.h
      node/operating_system/linux/language.cpp
      #os/linux/library.cpp
      node/operating_system/linux/linux_linux.h
      #node/operating_system/linux/lock.cpp
      node/operating_system/linux/menu.cpp
      node/operating_system/linux/message_loop.cpp
      node/operating_system/linux/parallelization.cpp
      node/operating_system/linux/os.cpp
      #os/linux/process.cpp
      #os/linux/process.h
      #os/linux/process_pid.cpp
      node/operating_system/linux/simple_app.cpp
      node/operating_system/linux/shell_launcher.cpp
      node/operating_system/linux/shell_launcher.h
      node/operating_system/linux/standard_exception.cpp
      #node/linux/interprocess_communication.cpp
      node/operating_system/linux/time.cpp
      node/operating_system/linux/user.cpp
      node/operating_system/linux/user.h
      node/operating_system/linux/user_private.h
      node/operating_system/linux/win_base.cpp)
endif ()


if (MACOS)

   list(APPEND apex_source
      crypto/macos/rsa.cpp
      crypto/macos/rsa.h
           #node/macos/_.h
           #node/macos/_macos.h
      #node/macos/_mm.h
      #node/macos/apex_window.h
      #node/macos/apex_window.mm
      #node/macos/ApexWindow.h
      #node/macos/ApexWindow.mm
      #node/macos/ApexWindowApp.h
      #node/macos/ApexWindowApp.mm
      #node/macos/ApexWindowController.h
      #node/macos/ApexWindowController.mm
      #node/macos/ApexWindowFrameView.h
      #node/macos/ApexWindowFrameView.mm
      #node/macos/app.mm
      #node/macos/application.cpp
      #node/macos/application.h
      #node/macos/dir_context.cpp
      #node/macos/dir_context.h
      #node/macos/dir_system.cpp
      #node/macos/dir_system.h
      #node/macos/_factory.cpp
      #node/macos/
      #node/macos/file.cpp
      #node/macos/file_context.cpp
      #node/macos/file_context.h
      #node/macos/file_os_watcher.cpp
      #node/macos/file_os_watcher.h
      #node/macos/file_system.cpp
      #node/macos/file_system.h
      #node/macos/keyboard.cpp
      #node/macos/keyboard.h
      #node/macos/keyboard_mm.mm
      #node/macos/main.cpp
      #node/macos/os_context.cpp
      #node/macos/os_context.h
      #node/macos/shell_macos_mm.mm
      #node/macos/stdio_file.cpp
      #node/macos/stdio_file.h
      #node/macos/thread.cpp
      #node/macos/thread.h
      #node/macos/trace.cpp
      #node/macos/user.h
      #node/macos/util.cpp
      #os/macos/_.h
      #os/macos/_c.h
      #os/macos/_macos.h
      #os/macos/_mm.h
      #os/macos/application_system_run.cpp
      #os/macos/aura.cpp
      #os/macos/clipboard.cpp
      #os/macos/cross_win.cpp
      #os/macos/cross_win_file.cpp
      #os/macos/cross_win_gdi.h
      #os/macos/debug.cpp
      #os/macos/exception_engine.cpp
      #os/macos/exception_engine.h
      #os/macos/file.cpp
      #os/macos/file.h
      #os/macos/file.mm
      #os/macos/graphics_mm.h
      #os/macos/internal.h
      #os/macos/keyboard.cpp
      #os/macos/language.cpp
      #os/macos/launcher.cpp
      #os/macos/library.cpp
      #os/macos/list_serial_ports.cpp
      #os/macos/lock.cpp
      #os/macos/macos.h
      #os/macos/main.h
      #os/macos/MessageBoxA.cpp
      #os/macos/mm.mm
      #os/macos/mm_graphics.mm
      #os/macos/mm_oswindow.h
      #os/macos/parallelization.cpp
      #os/macos/parallelization.h
      #os/macos/NSPasteboard++.mm
      #os/macos/os.cpp
      #os/macos/os.h
      ##os/macos/process.cpp
      ##os/macos/process_c.h
      ##os/macos/process_pid.cpp
      #os/macos/simple_app.cpp
      #os/macos/simple_shell_launcher.cpp
      #os/macos/small_ipca_channel.cpp
      #os/macos/time.cpp
      #os/macos/user.cpp
      #os/macos/user.h
      #os/macos/win_base.cpp
      #os/macos/window_impl.h
      #os/macos/windowing.h
      #os/macos/windowing_c.h
      #os/macos/winpr_keycode.cpp

      )


endif ()


if (IOS)
   list(APPEND apex_source
      ios_aura/ios_aura.h
      ios_aura/ios_aura.m
      node/ios/_.h
      node/ios/_ios.h
      node/ios/_m.h
      node/ios/_mm.h
      node/ios/application.cpp
      node/ios/application.h
      node/ios/dir_context.cpp
      node/ios/dir_context.h
      node/ios/dir_system.cpp
      node/ios/dir_system.h
      node/ios/exception.cpp
      node/ios/_factory.cpp
      node/ios/
      node/ios/file.cpp
      node/ios/file.h
      node/ios/file_context.cpp
      node/ios/file_context.h
      node/ios/file_os_watcher.cpp
      node/ios/file_os_watcher.h
      node/ios/file_system.cpp
      node/ios/file_system.h
      node/ios/host_interaction.cpp
      node/ios/implementation.h
      node/ios/internal.h
      node/ios/ios.cpp
      node/ios/ip_enum.cpp
      node/ios/ip_enum.h
      node/ios/main.cpp
      node/ios/os_context.cpp
      node/ios/os_context.h
      node/ios/plane_system.cpp
      node/ios/plane_system.h
      node/ios/round_window.mm
      node/ios/RoundCaretView.h
      node/ios/RoundWindow.mm
      node/ios/RoundWindowApp.h
      node/ios/RoundWindowApp.mm
      node/ios/state.h
      node/ios/thread.cpp
      node/ios/thread.h
      node/ios/trace.cpp
      node/ios/util.cpp
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
      os/ios/mm_oswindow.h
      os/ios/mm_thread.mm
      os/ios/mm_user.mm
      os/ios/parallelization.cpp
      os/ios/parallelization.h
      os/ios/oswindow_data.cpp
      os/ios/oswindow_data.h
      #os/ios/process.cpp
      #os/ios/process.h
      #os/ios/process_pid.cpp
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
      os/ios/windowing.h)

endif ()


if (ANDROID)
   list(APPEND apex_source
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
      node/android/_factory.cpp
      node/android/
      node/android/file.cpp
      node/android/file.h
      node/android/file_context.cpp
      node/android/file_context.h
      node/android/file_system.cpp
      node/android/file_system.h
      node/android/host_interaction.cpp
      node/android/host_interaction.h
      node/android/implementation.h
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
      os/android/parallelization.cpp
      #os/android/process.cpp
      #os/android/process.h
      #os/android/process_pid.cpp
      os/android/simple_shell_launcher.cpp
      os/android/small_ipca_channel.cpp
      os/android/view_bitmap.h
      os/android/win_base.cpp
      os/android/window_android.cpp
      os/android/window_android.h
      os/android/window_impl.cpp
      os/android/windowing.cpp
      os/android/windowing.h
      )

endif ()


if (APPLE)
   list(APPEND apex_source
      #timer.mm
      #node/apple/apple_timer.cpp
      #node/apple/process.cpp
      #node/apple/process.h
      #os/apple/_.cpp
      #os/apple/_.h
      #os/apple/_apple.h
      #os/apple/_apple.mm
      #os/apple/_c_mm.h
      #os/apple/_mm.h
      #os/apple/_mm_common.h
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
      ##os/apple/process.cpp
      #os/apple/time.cpp
      #os/apple/time.h
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
      #os/solaris/solaris_process.cpp
      #os/solaris/solaris_process.h
      #os/solaris/solaris_process_pid.cpp
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

endif ()


if (PTHREAD)

   list(APPEND apex_source
      node/operating_system/posix/pthread.cpp
      )

endif ()


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


add_library(apex SHARED ${apex_source})

target_precompile_headers(apex PRIVATE framework.h)

set_target_properties(apex PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(apex PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(apex PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(apex PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/apex.lib")
   target_link_options(apex PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/apex.def")
   target_link_libraries(apex PRIVATE acme zlib libcrypto libssl dwrite d2d1 d3d11 dxgi Dxva2 dbghelp imagehlp dwmapi Setupapi Windowscodecs Winmm ws2_32 Crypt32 Normaliz version Secur32 gdiplus Shlwapi Imm32)
elseif(LINUX OR FREEBSD)
   pkg_check_modules(PKGCONFIG libcrypto libssl)
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
target_include_directories(apex PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(apex PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(apex PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(apex PRIVATE _APEX_LIBRARY)


