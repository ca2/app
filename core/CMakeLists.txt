cmake_minimum_required(VERSION 3.17)
project(core CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)


message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")


if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
   set(LINUX TRUE)
   set(PLATFORM_NAME "linux")
   message("System is Linux")
   include(FindPkgConfig)
elseif (WIN32)
   set(PLATFORM_NAME "windows")
elseif (UWP)
   set(PLATFORM_NAME "uwp")
   set(WINDOWS_TSF TRUE)
endif ()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND core_source
   asset/cube_new.cpp
   #asset/new.cpp
   axispolicy/_.h
   axispolicy/_c.h
   axispolicy/policy_objc.h
   axispolicy/policy_objcpp.h
   axispolicy/policy_winrt.h
   const/_const.h
   const/charset.h
   const/check.h
   const/context.h
   const/id.h
   const/idpool.cpp
   const/idpool.h
   const/impact.h
   const/procedure.h
   const/simple_command.h
   const/source.h
   const/status.h
   const/status_range_authentication.h
   const/thread.h
   const/timer.h
   filesystem/filehandler/_.h
   filesystem/filehandler/_data.h
   filesystem/filehandler/_filehandler.h
   filesystem/filehandler/handler.cpp
   filesystem/filehandler/handler.h
   filesystem/filehandler/item.cpp
   filesystem/filehandler/item.h
   filesystem/filehandler/library.cpp
   filesystem/filehandler/library.h
   filesystem/filehandler/menu_library.cpp
   filesystem/filehandler/menu_library.h
   filesystem/filehandler/tree_interface.cpp
   filesystem/filehandler/tree_interface.h
   filesystem/filemanager/_.cpp
   filesystem/filemanager/_.h
   filesystem/filemanager/_data.h
   filesystem/filemanager/_filemanager.h
   filesystem/filemanager/_tree.h
   filesystem/filemanager/child_frame.cpp
   filesystem/filemanager/child_frame.h
   filesystem/filemanager/component.cpp
   filesystem/filemanager/component.h
   filesystem/filemanager/const.h
   filesystem/filemanager/context_menu.cpp
   filesystem/filemanager/context_menu.h
   filesystem/filemanager/data.cpp
   filesystem/filemanager/data.h
   filesystem/filemanager/document.cpp
   filesystem/filemanager/document.h
   filesystem/filemanager/file_list.cpp
   filesystem/filemanager/file_list.h
   filesystem/filemanager/file_list_callback.cpp
   filesystem/filemanager/file_list_callback.h
   filesystem/filemanager/file_properties_form.cpp
   filesystem/filemanager/file_properties_form.h
   filesystem/filemanager/folder_list.cpp
   filesystem/filemanager/folder_list.h
   filesystem/filemanager/folder_list_data.cpp
   filesystem/filemanager/folder_list_data.h
   filesystem/filemanager/folder_list_view.cpp
   filesystem/filemanager/folder_list_view.h
   filesystem/filemanager/folder_selection_list_view.cpp
   filesystem/filemanager/folder_selection_list_view.h
   filesystem/filemanager/form.cpp
   filesystem/filemanager/form.h
   filesystem/filemanager/form_child_frame.cpp
   filesystem/filemanager/form_child_frame.h
   filesystem/filemanager/form_document.cpp
   filesystem/filemanager/form_document.h
   filesystem/filemanager/frame.cpp
   filesystem/filemanager/frame.h
   filesystem/filemanager/fs_simple_list_view.cpp
   filesystem/filemanager/fs_simple_list_view.h
   filesystem/filemanager/fs_simple_tree.cpp
   filesystem/filemanager/fs_simple_tree.h
   filesystem/filemanager/fs_simple_view.cpp
   filesystem/filemanager/fs_simple_view.h
   filesystem/filemanager/icon.cpp
   filesystem/filemanager/icon.h
   filesystem/filemanager/iconoverlayer.cpp
   filesystem/filemanager/iconoverlayer.h
   filesystem/filemanager/impact.cpp
   filesystem/filemanager/impact.h
   filesystem/filemanager/left_view.cpp
   filesystem/filemanager/left_view.h
   filesystem/filemanager/main_frame.cpp
   filesystem/filemanager/main_frame.h
   filesystem/filemanager/main_view.cpp
   filesystem/filemanager/main_view.h
   filesystem/filemanager/operation.cpp
   filesystem/filemanager/operation.h
   filesystem/filemanager/operation_child_frame.cpp
   filesystem/filemanager/operation_child_frame.h
   filesystem/filemanager/operation_document.cpp
   filesystem/filemanager/operation_document.h
   filesystem/filemanager/operation_info_view.cpp
   filesystem/filemanager/operation_info_view.h
   filesystem/filemanager/operation_list_view.cpp
   filesystem/filemanager/operation_list_view.h
   filesystem/filemanager/operation_thread.cpp
   filesystem/filemanager/operation_thread.h
   filesystem/filemanager/operation_view.cpp
   filesystem/filemanager/operation_view.h
   filesystem/filemanager/path_view.cpp
   filesystem/filemanager/path_view.h
   filesystem/filemanager/preview.cpp
   filesystem/filemanager/preview.h
   filesystem/filemanager/save_as_name_view.cpp
   filesystem/filemanager/save_as_name_view.h
   filesystem/filemanager/tab_view.cpp
   filesystem/filemanager/tab_view.h
   filesystem/filemanager/tree.cpp
   filesystem/filemanager/tree.h
   filesystem/filemanager/update_hint.cpp
   filesystem/filemanager/update_hint.h
   filesystem/filemanager/view.cpp
   filesystem/filemanager/view.h
   filesystem/fs/_.h
   filesystem/fs/_fs.h
   filesystem/fs/ftp_file.cpp
   filesystem/fs/ftp_file.h
   filesystem/fs/ftp_net.h
   filesystem/fs/ftpfs.cpp
   filesystem/fs/ftpfs.h
   filesystem/userfs/_.h
   filesystem/userfs/_data.h
   filesystem/userfs/_tree.h
   filesystem/userfs/_userfs.h
   filesystem/userfs/const.h
   filesystem/userfs/document.cpp
   filesystem/userfs/document.h
   filesystem/userfs/item.cpp
   filesystem/userfs/item.h
   filesystem/userfs/list.cpp
   filesystem/userfs/list.h
   filesystem/userfs/list_data.cpp
   filesystem/userfs/list_data.h
   filesystem/userfs/list_item.cpp
   filesystem/userfs/list_item.h
   filesystem/userfs/list_item_array.cpp
   filesystem/userfs/list_item_array.h
   filesystem/userfs/main_view.cpp
   filesystem/userfs/main_view.h
   filesystem/userfs/tree.cpp
   filesystem/userfs/tree.h
   filesystem/userfs/userfs.cpp
   filesystem/userfs/userfs.h
   filesystem/_impl.h
   filesystem/filesystem.h
   html/element/_.h
   html/element/_element.h
   html/element/element.cpp
   html/element/element.h
   html/graphics/_.h
   html/graphics/_graphics.h
   html/graphics/attribute.cpp
   html/graphics/attribute.h
   html/graphics/base.cpp
   html/graphics/base.h
   html/graphics/border.h
   html/graphics/box.h
   html/graphics/font.cpp
   html/graphics/font.h
   html/graphics/form.cpp
   html/graphics/form.h
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
   html/hi5/hi5_twitter_authorization.cpp
   html/hi5/hi5_twitter_authorization.h
   html/html/_.h
   html/html/_html.h
   html/html/core_data.cpp
   html/html/core_data.h
   html/html/data.cpp
   html/html/data.h
   html/impl/_.cpp
   html/impl/_.h
   html/impl/_impl.h
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
   html/user/_.h
   html/user/_user.h
   html/user/child_frame.cpp
   html/user/child_frame.h
   html/user/document.cpp
   html/user/document.h
   html/user/form.cpp
   html/user/form.h
   html/user/form_view.cpp
   html/user/form_view.h
   html/user/frame.cpp
   html/user/frame.h
   html/user/user.cpp
   html/user/view.cpp
   html/user/view.h
   include/_.cpp
   include/_.h
   include/_c.h
   include/_c_bridge.h
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
   net/ftp/_.h
   net/ftp/client_socket.cpp
   net/ftp/client_socket.h
   net/ftp/data_types.cpp
   net/ftp/data_types.h
   net/ftp/file.cpp
   net/ftp/file.h
   net/ftp/file_list_parser.cpp
   net/ftp/file_list_parser.h
   net/ftp/file_status.cpp
   net/ftp/file_status.h
   net/ftp/interface.h
   net/ftp/output.cpp
   net/ftp/output.h
   net/ftp/output_stream.cpp
   net/ftp/output_stream.h
   net/ftp/transfer_notification.h
   net/_.h
   net/_impl.h
   node/dummy/frame_window.cpp
   node/_.h
   node/_node.h
   node/serial.h
   os/_.h
   os/_application.h
   os/_c.h
   os/_impl.h
   os/_os.h
   os/binreloc.h
   os/chronometer.h
   os/console.h
   os/core.h
   os/cross.h
   os/file.h
   os/graphics.h
   os/os_windowing2.h
   os/process.h
   os/text.h
   os/threading.h
   os/time.h
   os/windowing.h
   os/winpr_input.h
   papaya/papaya_zoneing.h
   platform/application.cpp
   platform/application.h
   platform/session.cpp
   platform/session.h
   platform/system.cpp
   platform/system.h
   platform/user.h
   template/list.h
   user/account/_.h
   user/account/_account.h
   user/account/account.cpp
   user/account/account_dialog.cpp
   user/account/account_login.cpp
   user/account/account_simple_ui.cpp
   user/account/dialog.h
   user/account/login.h
   user/account/simple_ui.h
   user/account/simple_ui_style.h
   user/account/view.cpp
   user/account/view.h
   user/databaseuser/_.h
   user/databaseuser/_databaseuser.h
   user/databaseuser/key_mesh_data.cpp
   user/databaseuser/key_mesh_data.h
   user/databaseuser/mesh_data.cpp
   user/databaseuser/mesh_data.h
   #user/hotplugin/hotplugin.cpp
   #user/hotplugin/hotplugin.h
   #user/hotplugin/hotplugin_bare_paint_discreet.cpp
   #user/hotplugin/hotplugin_bare_paint_full_screen.cpp
   #user/hotplugin/hotplugin_bare_paint_veri_discreet.cpp
   #user/hotplugin/hotplugin_composer.cpp
   #user/hotplugin/hotplugin_composer.h
   #user/hotplugin/hotplugin_container_launcher.cpp
   #user/hotplugin/hotplugin_container_launcher.h
   #user/hotplugin/hotplugin_host.cpp
   #user/hotplugin/hotplugin_host.h
   #user/hotplugin/hotplugin_plugin.cpp
   #user/hotplugin/hotplugin_plugin.h
   #user/hotplugin/hotplugin_windows.cpp
   user/netuser/_.h
   user/netuser/_netuser.h
   user/netuser/netuser_network_configuration.cpp
   user/netuser/network_configuration.h
   user/rich_text/_const.h
   user/rich_text/_impl.h
   user/rich_text/_rich_text.h
   user/rich_text/box.cpp
   user/rich_text/box.h
   user/rich_text/data.cpp
   user/rich_text/data.h
   user/rich_text/document.cpp
   user/rich_text/document.h
   user/rich_text/edit.cpp
   user/rich_text/edit.h
   user/rich_text/edit_impl.cpp
   user/rich_text/edit_impl.h
   user/rich_text/format.cpp
   user/rich_text/format.h
   user/rich_text/format_tool.cpp
   user/rich_text/format_tool.h
   user/rich_text/global.cpp
   user/rich_text/global.h
   user/rich_text/layout.h
   user/rich_text/line.cpp
   user/rich_text/line.h
   user/rich_text/rich_text.h
   user/rich_text/span.cpp
   user/rich_text/span.h
   user/rich_text/text_format.cpp
   user/rich_text/text_format.h
   user/rich_text/text_format_object.cpp
   user/rich_text/text_format_object.h
   user/simple/_.cpp
   user/simple/_.h
   user/simple/_impl.h
   user/simple/_simple.h
   user/simple/_tree.h
   user/simple/child_frame.cpp
   user/simple/child_frame.h
   user/simple/form_list_view.cpp
   user/simple/form_list_view.h
   user/simple/form_view.cpp
   user/simple/form_view.h
   user/simple/list_control.cpp
   user/simple/list_control.h
   user/simple/list_data.cpp
   user/simple/list_data.h
   user/simple/list_header_control.cpp
   user/simple/list_header_control.h
   user/simple/list_view.cpp
   user/simple/list_view.h
   user/simple/menu_bar.cpp
   user/simple/menu_bar.h
   user/simple/mesh_data.cpp
   user/simple/mesh_data.h
   user/simple/message_box.cpp
   user/simple/message_box.h
   user/simple/pane_document.cpp
   user/simple/pane_document.h
   user/simple/printer_list_view.cpp
   user/simple/printer_list_view.h
   user/simple/simple.h
   user/simple/static.cpp
   user/simple/static.h
   user/simple/status_bar.cpp
   user/simple/status_bar.h
   user/simple/tab_control.cpp
   user/simple/tab_control.h
   user/simple/tab_view.cpp
   user/simple/tab_view.h
   user/simple/toolbar.cpp
   user/simple/toolbar.h
   user/simple/tree_view.cpp
   user/simple/tree_view.h
   user/simple_ui/_.h
   user/simple_ui/_simple_ui.h
   user/simple_ui/edit_box.cpp
   user/simple_ui/edit_box.h
   user/simple_ui/interaction.cpp
   user/simple_ui/interaction.h
   user/simple_ui/label.cpp
   user/simple_ui/label.h
   user/simple_ui/message_box.cpp
   user/simple_ui/message_box.h
   user/simple_ui/password.cpp
   user/simple_ui/password.h
   user/simple_ui/style.cpp
   user/simple_ui/style.h
   user/simple_ui/tap.cpp
   user/simple_ui/tap.h
   user/simple_ui/top.cpp
   user/simple_ui/top.h
   user/user/00.h
   user/user/_.cpp
   user/user/_.h
   user/user/_const.h
   user/user/_data.h
   user/user/_impl.h
   user/user/_tree.h
   user/user/_user.h
   user/user/color_combo_box.cpp
   user/user/color_combo_box.h
   user/user/control_ddx_dbflags.h
   user/user/elastic_slider.cpp
   user/user/elastic_slider.h
   user/user/font_combo_box.cpp
   user/user/font_combo_box.h
   user/user/font_list.cpp
   user/user/font_list.h
   user/user/form_list.cpp
   user/user/form_list.h
   user/user/form_list_view.cpp
   user/user/form_list_view.h
   user/user/form_mesh.cpp
   user/user/form_mesh.h
   user/user/form_update_hint.h
   user/user/image_manager.cpp
   user/user/image_manager.h
   user/user/inline.h
   user/user/list.cpp
   user/user/list.h
   user/user/list_cache.cpp
   user/user/list_cache.h
   user/user/list_column.h
   user/user/list_column_array.h
   user/user/list_data.cpp
   user/user/list_data.h
   user/user/list_header.cpp
   user/user/list_header.h
   user/user/list_item.h
   user/user/list_view.cpp
   user/user/list_view.h
   user/user/listing.h
   user/user/main_frame.h
   user/user/mesh.cpp
   user/user/mesh.h
   user/user/mesh_cache.cpp
   user/user/mesh_cache.h
   user/user/mesh_cache_interface.cpp
   user/user/mesh_cache_interface.h
   user/user/mesh_data.cpp
   user/user/mesh_data.h
   user/user/mesh_item.h
   user/user/shell.cpp
   user/user/shell.h
   user/user/statusbar.cpp
   user/user/statusbar.h
   user/user/step_slider.cpp
   user/user/step_slider.h
   user/user/toggle_switch.cpp
   user/user/toggle_switch.h
   user/user/tool_command.cpp
   user/user/tool_command.h
   user/user/tool_tip_tool.cpp
   user/user/tool_tip_tool.h
   user/user/tool_tip_window.cpp
   user/user/tool_tip_window.h
   user/user/toolbar_control.h
   user/user/toolbar_ctrl.cpp
   user/user/tooltip.cpp
   user/user/tooltip.h
   user/user/tree.cpp
   user/user/tree.h
   user/user/tree_data.cpp
   user/user/tree_data.h
   user/user/tree_window.cpp
   user/user/xfplayer_view_line.cpp
   user/user/xfplayer_view_line.h
   user/user/xfplayer_view_line_selection.cpp
   user/user/xfplayer_view_line_selection.h
   user/user/xfplayer_view_lines.cpp
   user/user/xfplayer_view_lines.h
   user/userex/-ehrror_dialog.cpp
   user/userex/_.h
   user/userex/_impl.h
   user/userex/_userex.h
   user/userex/calculator_edit_view.cpp
   user/userex/calculator_edit_view.h
   user/userex/color_view.cpp
   user/userex/color_view.h
   user/userex/const.h
   user/userex/dialog.cpp
   user/userex/dialog.h
   user/userex/error_dialog.h
   user/userex/font_view.cpp
   user/userex/font_view.h
   user/userex/form_child_frame.cpp
   user/userex/form_child_frame.h
   user/userex/form_document.h
   user/userex/form_frame.cpp
   user/userex/form_frame.h
   user/userex/form_view.h
   user/userex/group_image_list.cpp
   user/userex/group_image_list.h
   user/userex/home_view.cpp
   user/userex/home_view.h
   user/userex/image_list.cpp
   user/userex/image_list.h
   user/userex/impact_host.cpp
   user/userex/impact_host.h
   user/userex/menu_document.cpp
   user/userex/menu_document.h
   user/userex/menu_frame.cpp
   user/userex/menu_frame.h
   user/userex/menu_view.cpp
   user/userex/menu_view.h
   user/userex/message_box.cpp
   user/userex/message_box.h
   user/userex/mini_dock_frame_window.h
   user/userex/pane_split_view.cpp
   user/userex/pane_split_view.h
   user/userex/pane_tab_view.cpp
   user/userex/pane_tab_view.h
   user/userex/pane_view.cpp
   user/userex/pane_view.h
   user/userex/progress.cpp
   user/userex/progress.h
   user/userex/property_page.cpp
   user/userex/property_page.h
   user/userex/property_sheet.cpp
   user/userex/property_sheet.h
   user/userex/split_view.cpp
   user/userex/split_view.h
   user/userex/top_edit_view.cpp
   user/userex/top_edit_view.h
   user/userex/top_toggle_view.cpp
   user/userex/top_toggle_view.h
   user/userex/top_view.cpp
   user/userex/top_view.h
   user/userex/user.cpp
   user/userex/user.h
   user/userex/wait_message_dialog.cpp
   user/userex/wait_message_dialog.h
   user/userpresence/_.h
   user/userpresence/department.cpp
   user/userpresence/department.h
   user/userpresence/presence.cpp
   user/userpresence/presence.h
   user/_.h
   user/prelude.h
   version/version.config.h
   version/version.h
   _.cpp
   _.h
   __matter_ca2.cpp
   _defer.h
   application.h
   astr.h
   callback.h
   console.h
   context_glx.cpp
   framework.cpp
   framework.h
   framework_c.h
   id.h
   library.h
   message.h
   procedure.h
   timer.mm
   update.h
   user.h
   xml.h)

if (WIN32)
   list(APPEND core_source
      #node/windows/base/_windows.h
      #node/windows/base/_windows_node.cpp
      #node/windows/base/factory_exchange.cpp
      #node/windows/base/factory_exchange.h
      #node/windows/base/implementation.h
      #node/windows/base/print_job.cpp
      #node/windows/base/print_job.h
      node/windows/_.h
      node/windows/_node_windows.h
      node/windows/_windows.h
      node/windows/shell.cpp
      node/windows/shell.h
      node/windows_common/application.cpp
      os/windows/_windows_impl.h
      os/windows_common/_.h
      os/windows_common/_c.h
      os/windows_common/_default_dll_impl.h
      os/windows_common/_file_c.h
      os/windows_common/_unicode_c.h
      os/windows_common/bstring.h
      os/windows_common/comptr.h
      os/windows_common/cotaskptr.h
      os/windows_common/draw2d_direct2d_global.h
      os/windows_common/file.h
      os/windows_common/graphics.h
      os/windows_common/multithreading.h
      os/windows_common/new_api.h
      os/windows_common/variant.h

      )
endif ()

if (UWP)
   list(APPEND core_source
      #node/uwp/_.h
      #node/uwp/_uwp.h
      #node/uwp/shell_uwp.cpp
      #node/uwp/shell_uwp.h
      #os/uwp/_.h
      #os/uwp/_os_metrowin.cpp
      #os/uwp/_uwp.h
      #os/uwp/_winrt.h
      #os/uwp/application_system_run.cpp
      #os/uwp/aura.cpp
      #os/uwp/base_file.cpp
      #os/uwp/base_file.h
      #os/uwp/debug.cpp
      #os/uwp/direct2d_tls.cpp
      #os/uwp/dpi.cpp
      #os/uwp/dummy_ipc.cpp
      #os/uwp/exception_engine.cpp
      #os/uwp/exception_engine.h
      #os/uwp/file.cpp
      #os/uwp/file_memory_map.cpp
      #os/uwp/file_winrt.h
      #os/uwp/gdi_winrt.h
      #os/uwp/graphics.cpp
      #os/uwp/host_interaction.h
      #os/uwp/language.cpp
      #os/uwp/launcher.cpp
      #os/uwp/library.cpp
      #os/uwp/lock.cpp
      #os/uwp/main.cpp
      #os/uwp/metrowin_metrowin.h
      #os/uwp/multithreading.cpp
      #os/uwp/multithreading.h
      #os/uwp/multithreading_winrt.h
      #os/uwp/os_message_box.cpp
      #os/uwp/oswindow.h
      #os/uwp/process.cpp
      #os/uwp/process.h
      #os/uwp/simple_app.cpp
      #os/uwp/simple_hold_handle.h
      #os/uwp/simple_shell_launcher.cpp
      #os/uwp/simple_ui.h
      #os/uwp/small_ipca_channel.cpp
      #os/uwp/sockets.cpp
      #os/uwp/sockets.h
      #os/uwp/time.cpp
      #os/uwp/user.cpp
      #os/uwp/windowing.cpp

      )
endif ()


if (LINUX)
   list(APPEND core_source
      node/linux/_.h
      node/linux/_linux.h
      node/linux/application.cpp
      node/linux/application.h
      node/linux/console_window.cpp
      node/linux/console_window.h
      node/linux/copydesk.cpp
      node/linux/copydesk.h
      node/linux/dir_context.cpp
      node/linux/dir_context.h
      node/linux/dir_system.cpp
      node/linux/dir_system.h
      node/linux/dumpinit.cpp
      node/linux/error.cpp
      node/linux/exception.cpp
      node/linux/factory_exchange.cpp
      node/linux/factory_exchange.h
      node/linux/file.cpp
      node/linux/file.h
      node/linux/file_context.cpp
      node/linux/file_context.h
      node/linux/file_system.cpp
      node/linux/file_system.h
      node/linux/frame_window.cpp
      node/linux/interaction_impl.cpp
      node/linux/interaction_impl.h
      node/linux/internal.h
      node/linux/linux.cpp
      node/linux/os_context.cpp
      node/linux/os_context.h
      node/linux/process.cpp
      node/linux/process.h
      node/linux/root_tools.cpp
      node/linux/root_tools.h
      node/linux/shell.cpp
      node/linux/shell.h
      node/linux/shell_linux.cpp
      node/linux/shell_linux.h
      node/linux/stdio_file.cpp
      node/linux/stdio_file.h
      node/linux/thread.cpp
      node/linux/thread.h
      node/linux/trace.cpp
      node/linux/util.cpp
      os/cairo/_.h
      os/cairo/_impl.h
      os/cross/uwp/cross_metrowin_user.cpp
      os/cross/uwp/metrowin_user.cpp
      os/cross/windows/_.h
      os/cross/cross.h
      os/gdk/aura_gdk.cpp
      os/gdk/aura_gdk.h
      os/linux/_.h
      os/linux/_c.h
      os/linux/_linux.h
      os/linux/_user.h
      os/linux/appindicator.h
      os/linux/application_system_run.cpp
      os/linux/aura.cpp
      os/linux/bloat_pad.h
      os/linux/callstack.cpp
      os/linux/cross_win_file.cpp
      os/linux/cross_win_file.h
      os/linux/cross_win_gdi.cpp
      os/linux/cross_win_gdi.h
      os/linux/cross_win_gdi_internal.h
      os/linux/debug.cpp
      os/linux/debug.h
      os/linux/desktop_file.cpp
      os/linux/desktop_file.h
      os/linux/exception_engine.cpp
      os/linux/exception_engine.h
      os/linux/file.cpp
      os/linux/file.h
      os/linux/gnome.cpp
      os/linux/gnome.h
      os/linux/gnome_bloat_pad.cpp
      os/linux/gnome_direct.cpp
      os/linux/gnome_gnome.h
      os/linux/gnome_internal_glue.h
      os/linux/gnome_shared.h
      os/linux/gnu_source.cpp
      os/linux/graphics.cpp
      os/linux/graphics.h
      os/linux/graphics2.h
      os/linux/language.cpp
      os/linux/linux.inl
      os/linux/linux_linux.h
      os/linux/user.h
      os/linux/user_private.h
      os/linux/x11.h
      os/x11/debug.cpp
      os/x11/x11.h
      os/x11/x11_exception.h
      os/x11/x11_keyboard.cpp
      os/x11/x11_keyboard.h
      os/x11/x11_windowing.cpp
      os/x11/x11_xrender.cpp

      )
endif ()


if (MACOS)
   list(APPEND core_source
      node/macos/_.h
      node/macos/_macos.h
      node/macos/_mm.h
      node/macos/shell.cpp
      node/macos/shell.h
      node/macos/shell_macos.cpp
      node/macos/shell_macos.h

      )
endif ()

if (IOS)
   list(APPEND core_source
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
      node/ios/factory_exchange.cpp
      node/ios/factory_exchange.h
      node/ios/file.cpp
      node/ios/file.h
      node/ios/file_context.cpp
      node/ios/file_context.h
      node/ios/file_os_watcher.cpp
      node/ios/file_os_watcher.h
      node/ios/file_system.cpp
      node/ios/file_system.h
      node/ios/host_interaction.cpp
      node/ios/host_interaction.h
      node/ios/implementation.h
      node/ios/interaction_impl.cpp
      node/ios/interaction_impl.h
      node/ios/internal.h
      node/ios/ios.cpp
      node/ios/ip_enum.cpp
      node/ios/ip_enum.h
      node/ios/main.cpp
      node/ios/os_context.cpp
      node/ios/os_context.h
      node/ios/plane_system.cpp
      node/ios/plane_system.h
      node/ios/round_window.h
      node/ios/round_window.mm
      node/ios/RoundCaretView.h
      node/ios/RoundCaretView.mm
      node/ios/RoundEditView.h
      node/ios/RoundEditView.mm
      node/ios/RoundTextPosition.h
      node/ios/RoundTextPosition.mm
      node/ios/RoundTextRange.h
      node/ios/RoundTextRange.mm
      node/ios/RoundTextView.h
      node/ios/RoundTextView.mm
      node/ios/RoundViewController.h
      node/ios/RoundViewController.mm
      node/ios/RoundWindow.h
      node/ios/RoundWindow.mm
      node/ios/RoundWindowApp.h
      node/ios/RoundWindowApp.mm
      node/ios/RoundWindowFrameView.h
      node/ios/RoundWindowFrameView.mm
      node/ios/shell.cpp
      node/ios/shell.h
      node/ios/state.h
      node/ios/thread.cpp
      node/ios/thread.h
      node/ios/trace.cpp
      node/ios/util.cpp

      )
endif ()

if (APPLE)
   list(APPEND core_source

      )
endif ()


if (ANDROID)
   list(APPEND core_source

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
      os/android/win_base.cpp
      os/android/window_android.cpp
      os/android/window_android.h
      os/android/window_impl.cpp
      os/android/windowing.cpp
      os/android/windowing.h
      )
endif ()


if (WIN32 OR LINUX OR APPLE)
   list(APPEND core_source

      #os/ansios/_.h
      #os/ansios/_ansios.h
      #os/ansios/_c.h
      #os/ansios/ansios_file.h
      #os/ansios/base.cpp
      #os/ansios/callstack.h
      #os/ansios/datetime.cpp
      #os/ansios/datetime_c.h
      #os/ansios/exception_engine.cpp
      #os/ansios/exception_engine.h
      #os/ansios/file.cpp
      #os/ansios/file.h
      #os/ansios/file_c.h
      #os/ansios/file_raw.cpp
      #os/ansios/file_raw.h
      #os/ansios/file_std.cpp
      #os/ansios/language.cpp
      #os/ansios/memory.cpp
      #os/ansios/multithreading.h
      #os/ansios/process.cpp
      #os/ansios/user.cpp
      #os/ansios/win.cpp
      #os/posix/base_file.cpp
      #os/posix/local_memory_map.cpp
      #os/posix/pthread.cpp
      #os/posix/thread.cpp
      #os/posix/time.cpp
      #os/posix/timer.cpp
      )
endif ()

if (SOLARIS)
   list(APPEND core_source

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

endif ()

if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


add_library(core SHARED ${core_source})


target_precompile_headers(core PRIVATE framework.h)


set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)

list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   base
   bred
   )

if (MSVC)
   target_compile_options(core PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_compile_options(core PRIVATE "/bigobj")
   target_link_options(core PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(core PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/core.lib")
   target_link_options(core PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/core.def")
   target_link_libraries(core PRIVATE ${library_references})
elseif (LINUX)
   pkg_check_modules(PKGCONFIG glib-2.0 gdk-3.0 gtk+-3.0 appindicator3-0.1)
   #pkg_check_modules(PKGCONFIG freetype2  )
   target_compile_options(core PRIVATE -fpermissive)
   target_compile_options(core PRIVATE ${PKGCONFIG_CFLAGS})

   #target_compile_options(core PRIVATE -std=c++14)
   #target_link_options(core PRIVATE ${GTK_LDFLAGS})
   target_link_options(core PRIVATE -Wl,-rpath=\$ORIGIN)
   #target_link_libraries(core PRIVATE z  dl  rt  bfd  X11  X11-xcb  xcb  xcb-util  Xinerama  Xmu  Xrandr  Xext  Xxf86vm  Xrender  Xi  ncurses  idn  pthread  sn)
   target_link_libraries(core PRIVATE dl pthread X11 Xrandr Xrender Xinerama Xi ncurses sn)
   target_link_libraries(core PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(core PRIVATE ${library_references})
   target_link_options(core PRIVATE -Wl,-z,defs)
   ##message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif ()


target_link_directories(core PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis)
target_link_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis)


target_include_directories(core PRIVATE .)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(core PRIVATE $ENV{HOME}/__config)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME})
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include)


target_compile_definitions(core PRIVATE _CORE_LIBRARY)
target_compile_definitions(core PRIVATE UNICODE)
target_compile_definitions(core PRIVATE _UNICODE)



