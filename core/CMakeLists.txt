cmake_minimum_required(VERSION 3.16)
project(core CXX)


list(APPEND library_source
   #asset/cube_new.cpp
   #asset/new.cpp
   axispolicy/_.h
   axispolicy/_c.h
   axispolicy/policy_objc.h
   axispolicy/policy_objcpp.h
   axispolicy/policy_winrt.h
   #const/_const.h
   #const/charset.h
   #const/check.h
   #const/context.h
   #const/id.h
   #constant/idpool.cpp
   #constant/idpool.h
   #const/impact.h
   #const/procedure.h
   #const/simple_command.h
   #const/source.h
   #const/status.h
   #const/status_range_authentication.h
   #const/thread.h
   #const/timer.h
   filesystem/filehandler/_.h
   #filesystem/filehandler/_data.h
   #filesystem/filehandler/_filehandler.h
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
   filesystem/filemanager/folder/document.cpp
   filesystem/filemanager/folder/document.h
   filesystem/filemanager/folder/list.cpp
   filesystem/filemanager/folder/list.h
   filesystem/filemanager/folder/list_data.cpp
   filesystem/filemanager/folder/list_data.h
   filesystem/filemanager/folder/list_impact.cpp
   filesystem/filemanager/folder/list_impact.h
   filesystem/filemanager/folder/selection_list_impact.cpp
   filesystem/filemanager/folder/selection_list_impact.h
   filesystem/filemanager/fs/simple/impact.cpp
   filesystem/filemanager/fs/simple/impact.h
   filesystem/filemanager/fs/simple/list_impact.cpp
   filesystem/filemanager/fs/simple/list_impact.h
   filesystem/filemanager/fs/simple/tree.cpp
   filesystem/filemanager/fs/simple/tree.h
   filesystem/filemanager/operation/operation.cpp
   filesystem/filemanager/operation/operation.h
   filesystem/filemanager/operation/child_frame.cpp
   filesystem/filemanager/operation/child_frame.h
   filesystem/filemanager/operation/document.cpp
   filesystem/filemanager/operation/document.h
   filesystem/filemanager/operation/info_impact.cpp
   filesystem/filemanager/operation/info_impact.h
   filesystem/filemanager/operation/list_impact.cpp
   filesystem/filemanager/operation/list_impact.h
   filesystem/filemanager/operation/thread.cpp
   filesystem/filemanager/operation/thread.h
   filesystem/filemanager/operation/impact.cpp
   filesystem/filemanager/operation/impact.h
   #filesystem/filemanager/_.cpp
   filesystem/filemanager/_.h
   #filesystem/filemanager/_data.h
   #filesystem/filemanager/_filemanager.h
   #filesystem/filemanager/_tree.h
   filesystem/filemanager/child_frame.cpp
   filesystem/filemanager/child_frame.h
   #filesystem/filemanager/const.h
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
   filesystem/filemanager/filemanager.cpp
   filesystem/filemanager/filemanager.h
   filesystem/filemanager/form.cpp
   filesystem/filemanager/form.h
   filesystem/filemanager/form_child_frame.cpp
   filesystem/filemanager/form_child_frame.h
   #filesystem/filemanager/form_document.cpp
   #filesystem/filemanager/form_document.h
   filesystem/filemanager/frame.cpp
   filesystem/filemanager/frame.h
   #filesystem/filemanager/fs_simple_list_impact.cpp
   #filesystem/filemanager/fs_simple_list_impact.h
   #filesystem/filemanager/fs_simple_tree.cpp
   #filesystem/filemanager/fs_simple_tree.h
   #filesystem/filemanager/fs_simple_impact.cpp
   #filesystem/filemanager/fs_simple_impact.h
   filesystem/filemanager/icon.cpp
   filesystem/filemanager/icon.h
   filesystem/filemanager/iconoverlayer.cpp
   filesystem/filemanager/iconoverlayer.h
   filesystem/filemanager/impact_base.cpp
   filesystem/filemanager/impact_base.h
   filesystem/filemanager/impact.cpp
   filesystem/filemanager/impact.h
   filesystem/filemanager/left_impact.cpp
   filesystem/filemanager/left_impact.h
   filesystem/filemanager/main_frame.cpp
   filesystem/filemanager/main_frame.h
   filesystem/filemanager/main_impact.cpp
   filesystem/filemanager/main_impact.h
   filesystem/filemanager/path_impact.cpp
   filesystem/filemanager/path_impact.h
   filesystem/filemanager/thumbnail.cpp
   filesystem/filemanager/thumbnail.h
   filesystem/filemanager/save_as_button_impact.cpp
   filesystem/filemanager/save_as_button_impact.h
   filesystem/filemanager/save_as_edit_impact.cpp
   filesystem/filemanager/save_as_edit_impact.h
   filesystem/filemanager/save_as_impact.cpp
   filesystem/filemanager/save_as_impact.h
   filesystem/filemanager/tab_impact.cpp
   filesystem/filemanager/tab_impact.h
   filesystem/filemanager/tree_data.cpp
   filesystem/filemanager/tree_data.h
   #filesystem/filemanager/update_hint.cpp
   #filesystem/filemanager/update_hint.h
   filesystem/filemanager/impact.cpp
   filesystem/filemanager/impact.h
   filesystem/fs/_.h
   #filesystem/fs/_fs.h
   filesystem/fs/ftp_file.cpp
   filesystem/fs/ftp_file.h
   filesystem/fs/ftpfs.cpp
   filesystem/fs/ftpfs.h
   filesystem/fs/ftpnet.cpp
   filesystem/fs/ftpnet.h
   filesystem/userfs/_.h
   filesystem/userfs/data.cpp
   filesystem/userfs/data.h
   #filesystem/userfs/_data.h
   #filesystem/userfs/_tree.h
   #filesystem/userfs/_userfs.h
   #filesystem/userfs/const.h
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
   filesystem/userfs/main_impact.cpp
   filesystem/userfs/main_impact.h
   filesystem/userfs/tree_data.cpp
   filesystem/userfs/tree_data.h
   filesystem/userfs/userfs.cpp
   filesystem/userfs/userfs.h
   filesystem/_impl.h
   filesystem/filesystem.h
   graphics/color_selector.cpp
   graphics/color_selector.h
   #include/_.cpp
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
   networking/ftp/_.h
   networking/ftp/client_socket.cpp
   networking/ftp/client_socket.h
   networking/ftp/data_types.cpp
   networking/ftp/data_types.h
   networking/ftp/file.cpp
   networking/ftp/file.h
   networking/ftp/file_list_parser.cpp
   networking/ftp/file_list_parser.h
   networking/ftp/file_status.cpp
   networking/ftp/file_status.h
   networking/ftp/interface.h
   networking/ftp/output.cpp
   networking/ftp/output.h
   networking/ftp/output_stream.cpp
   networking/ftp/output_stream.h
   networking/ftp/transfer_notification.h
   networking/_.h
   networking/_impl.h
#   operating_system/dummy/frame_window.cpp
#   operating_system/_.h
#   operating_system/_node.h
#   operating_system/serial.h
#   operating_system/_.h
#   operating_system/_application.h
#   operating_system/_c.h
#   operating_system/_impl.h
#   operating_system/_os.h
#   operating_system/binreloc.h
#   operating_system/chronometer.h
#   operating_system/console.h
#   operating_system/core.h
#   operating_system/cross.h
#   operating_system/file.h
#   operating_system/graphics.h
#   operating_system/os_windowing2.h
#   #   operating_system/process.h
#   operating_system/text.h
#   operating_system/threading.h
#   operating_system/time.h
#   operating_system/windowing.h
#   operating_system/winpr_input.h
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
   #user/account/_account.h
   #user/account/account.cpp
   #user/account/account_dialog.cpp
   #user/account/account_login.cpp
   #user/account/account_simple_ui.cpp
   user/account/dialog.h
   user/account/login.h
   user/account/impact.cpp
   user/account/impact.h
   user/databaseuser/_.h
   #user/databaseuser/_databaseuser.h
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
   #user/netuser/netuser_network_configuration.cpp
   user/netuser/network_configuration.h
   #user/rich_text/_const.h
   user/rich_text/_factory.cpp
   user/rich_text/_impl.h
   #user/rich_text/_rich_text.h
   user/rich_text/box.cpp
   user/rich_text/box.h
   user/rich_text/data.cpp
   user/rich_text/data.h
   #user/rich_text/document.cpp
   #user/rich_text/document.h
   user/rich_text/edit.cpp
   user/rich_text/edit.h
   user/rich_text/edit_impl.cpp
   user/rich_text/edit_impl.h
   user/rich_text/format.cpp
   user/rich_text/format.h
   user/rich_text/format_host.cpp
   user/rich_text/format_host.h
   user/rich_text/format_tool.cpp
   user/rich_text/format_tool.h
   user/rich_text/global.cpp
   user/rich_text/global.h
   #user/rich_text/layout.h
   user/rich_text/line.cpp
   user/rich_text/line.h
   user/rich_text/rich_text.h
   user/rich_text/selection.cpp
   user/rich_text/span.cpp
   user/rich_text/span.h
   user/rich_text/text_format.cpp
   user/rich_text/text_format.h
   #user/rich_text/text_format_object.cpp
   #user/rich_text/text_format_object.h
   #user/simple/_.cpp
   user/simple/_.h
   user/simple/_impl.h
   #user/simple/_component.h
   user/simple/_tree.h
   #user/simple/child_frame.cpp
   #user/simple/child_frame.h
   user/simple/form_list_impact.cpp
   user/simple/form_list_impact.h
   user/simple/form_impact.cpp
   user/simple/form_impact.h
   user/simple/list_control.cpp
   user/simple/list_control.h
   user/simple/list_data.cpp
   user/simple/list_data.h
   user/simple/list_header_control.cpp
   user/simple/list_header_control.h
   user/simple/list_impact.cpp
   user/simple/list_impact.h
   user/simple/menu_bar.cpp
   user/simple/menu_bar.h
   user/simple/mesh_data.cpp
   user/simple/mesh_data.h
   #user/simple/message_box.cpp
   user/simple/message_box.h
   user/simple/pane_document.cpp
   user/simple/pane_document.h
   user/simple/printer_list_impact.cpp
   user/simple/printer_list_impact.h
   user/simple/simple.h
   #user/simple/static.cpp
   #user/simple/static.h
   #user/simple/status_bar.cpp
   #user/simple/status_bar.h
   user/simple/still.cpp
   user/simple/still.h
   user/simple/tab_control.cpp
   user/simple/tab_control.h
   user/simple/tab_impact.cpp
   user/simple/tab_impact.h
   #user/simple/toolbar.cpp
   #user/simple/toolbar.h
   user/simple/tree_impact.cpp
   user/simple/tree_impact.h
   #user/user/00.h
   #user/user/_.cpp
   user/user/_.h
   #user/user/_const.h
   #user/user/_data.h
   #user/user/_impl.h
   #user/user/_tree.h
   #user/user/_user.h
   user/user/color_selector_combo_box.cpp
   user/user/color_selector_combo_box.h
   user/user/color_selector_control.cpp
   user/user/color_selector_control.h
   user/user/color_selector_impact.cpp
   user/user/color_selector_impact.h
   user/user/color_selector_popup.cpp
   user/user/color_selector_popup.h
   user/user/control_ddx_dbflags.h
   user/user/elastic_slider.cpp
   user/user/elastic_slider.h
   user/user/font_combo_box.cpp
   user/user/font_combo_box.h
   user/user/font_list.cpp
   user/user/font_list.h
   user/user/font_list_impact.cpp
   user/user/font_list_impact.h
   user/user/form_list.cpp
   user/user/form_list.h
   user/user/form_list_impact.cpp
   user/user/form_list_impact.h
   user/user/form_mesh.cpp
   user/user/form_mesh.h
   user/user/form_update_hint.h
   user/user/image_manager.cpp
   user/user/image_manager.h
   #user/user/inline.h
   user/user/list.cpp
   user/user/list.h
   user/user/list_cache.cpp
   user/user/list_cache.h
   user/user/list_column.cpp
   user/user/list_column.h
   user/user/list_column_array.h
   user/user/list_data.cpp
   user/user/list_data.h
   user/user/list_header.cpp
   user/user/list_header.h
   user/user/list_item.cpp
   user/user/list_item.h
   user/user/list_impact.cpp
   user/user/list_impact.h
   user/user/list2.cpp
   user/user/list2.h
   user/user/listing.h
   user/user/main_frame.cpp
   user/user/main_frame.h
   user/user/mesh.cpp
   user/user/mesh.h
   user/user/mesh_cache.h
   user/user/mesh_cache_interface.cpp
   user/user/mesh_cache_interface.h
   user/user/mesh_data.cpp
   user/user/mesh_data.h
   user/user/mesh_item.cpp
   user/user/mesh_item.h
   user/user/popup.cpp
   user/user/popup.h
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
   user/user/tree_data_base.cpp
   user/user/tree.h
   user/user/tree.cpp
   user/user/tree_data.h
   user/user/tree_window.cpp
   user/user/user.cpp
   user/user/user.h
   user/user/xfplayer_impact_line.cpp
   user/user/xfplayer_impact_line.h
   user/user/xfplayer_impact_line_selection.cpp
   user/user/xfplayer_impact_line_selection.h
   user/user/xfplayer_impact_lines.cpp
   user/user/xfplayer_impact_lines.h
   user/userex/_.h
   user/userex/_impl.h
   user/userex/const.h
   user/userex/dialog.cpp
   user/userex/dialog.h
   user/userex/dialog_frame.cpp
   user/userex/dialog_frame.h
   user/userex/font_impact.cpp
   user/userex/font_impact.h
   user/userex/form_child_frame.cpp
   user/userex/form_child_frame.h
   user/userex/form_document.h
   user/userex/form_frame.cpp
   user/userex/form_frame.h
   user/userex/form_impact.h
   user/userex/group_image_list.cpp
   user/userex/group_image_list.h
   user/userex/home_impact.cpp
   user/userex/home_impact.h
   user/userex/image_list.cpp
   user/userex/image_list.h
   user/userex/impact_host.cpp
   user/userex/impact_host.h
   user/userex/menu_document.cpp
   user/userex/menu_document.h
   user/userex/menu_frame.cpp
   user/userex/menu_frame.h
   user/userex/message_box.cpp
   user/userex/message_box.h
   user/userex/mini_dock_frame_window.h
   user/userex/pane_split_impact.cpp
   user/userex/pane_split_impact.h
   user/userex/pane_tab_impact.cpp
   user/userex/pane_tab_impact.h
   user/userex/pane_impact.cpp
   user/userex/pane_impact.h
   user/userex/progress.cpp
   user/userex/progress.h
   user/userex/property_page.cpp
   user/userex/property_page.h
   user/userex/property_sheet.cpp
   user/userex/property_sheet.h
   user/userex/split_impact.cpp
   user/userex/split_impact.h
   user/userex/top_edit_impact.cpp
   user/userex/top_edit_impact.h
   user/userex/top_toggle_impact.cpp
   user/userex/top_toggle_impact.h
   user/userex/top_impact.cpp
   user/userex/top_impact.h
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
   framework.cpp
   framework.h
)

if (WIN32)
   list(APPEND core_source
      operating_system/windows/_.h
      operating_system/windows/_node_windows.h
      operating_system/windows/_windows.h
      operating_system/windows_common/application.cpp
      operating_system/windows/_windows_impl.h
      operating_system/windows_common/_.h
      operating_system/windows_common/_c.h
      operating_system/windows_common/_default_dll_impl.h
      operating_system/windows_common/_file_c.h
      operating_system/windows_common/_unicode_c.h
      operating_system/windows_common/bstring.h
      operating_system/windows_common/comptr.h
      operating_system/windows_common/cotaskptr.h
      operating_system/windows_common/draw2d_direct2d_global.h
      operating_system/windows_common/file.h
      operating_system/windows_common/graphics.h
      operating_system/windows_common/multithreading.h
      operating_system/windows_common/new_api.h
      operating_system/windows_common/variant.h
   )
endif ()


if (${LINUX})
   list(APPEND core_source
      operating_system/linux/_.h
      operating_system/linux/_linux.h
      operating_system/linux/_factory.cpp
      operating_system/linux/
      operating_system/linux/internal.h
      operating_system/linux/linux.cpp
      operating_system/linux/root_tools.cpp
      operating_system/linux/root_tools.h
      operating_system/linux/shell.cpp
      operating_system/linux/shell.h
   )
endif ()


if (MACOS)
   list(APPEND core_source
      operating_system/macos/_.h
      operating_system/macos/_macos.h
      operating_system/macos/_mm.h
      operating_system/macos/shell.cpp
      operating_system/macos/shell.h
      operating_system/macos/shell_macos.cpp
      operating_system/macos/shell_macos.h

   )
endif ()

if (IOS)
   list(APPEND core_source
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
      operating_system/ios/host_interaction.h
      operating_system/ios/implementation.h
      operating_system/ios/interaction_impl.cpp
      operating_system/ios/interaction_impl.h
      operating_system/ios/internal.h
      operating_system/ios/ios.cpp
      operating_system/ios/ip_enum.cpp
      operating_system/ios/ip_enum.h
      operating_system/ios/main.cpp
      operating_system/ios/os_context.cpp
      operating_system/ios/os_context.h
      operating_system/ios/plane_system.cpp
      operating_system/ios/plane_system.h
      operating_system/ios/round_window.h
      operating_system/ios/round_window.mm
      operating_system/ios/RoundCaretImpact.h
      operating_system/ios/RoundCaretImpact.mm
      operating_system/ios/RoundEditImpact.h
      operating_system/ios/RoundEditImpact.mm
      operating_system/ios/RoundTextPosition.h
      operating_system/ios/RoundTextPosition.mm
      operating_system/ios/RoundTextRange.h
      operating_system/ios/RoundTextRange.mm
      operating_system/ios/RoundTextImpact.h
      operating_system/ios/RoundTextImpact.mm
      operating_system/ios/RoundImpactController.h
      operating_system/ios/RoundImpactController.mm
      operating_system/ios/RoundWindow.h
      operating_system/ios/RoundWindow.mm
      operating_system/ios/RoundWindowApp.h
      operating_system/ios/RoundWindowApp.mm
      operating_system/ios/RoundWindowFrameImpact.h
      operating_system/ios/RoundWindowFrameImpact.mm
      operating_system/ios/shell.cpp
      operating_system/ios/shell.h
      operating_system/ios/state.h
      operating_system/ios/thread.cpp
      operating_system/ios/thread.h
      operating_system/ios/trace.cpp
      operating_system/ios/util.cpp

   )
endif ()

if (APPLE)
   list(APPEND core_source

   )
endif ()


if (ANDROID)
   list(APPEND core_source

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
      #      operating_system/android/process.cpp
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
      #      operating_system/android/process.cpp
      #      operating_system/android/process.h
      #      operating_system/android/process_pid.cpp
      operating_system/android/simple_shell_launcher.cpp
      operating_system/android/small_ipca_channel.cpp
      operating_system/android/impact_bitmap.h
      operating_system/android/win_base.cpp
      operating_system/android/window_android.cpp
      operating_system/android/window_android.h
      operating_system/android/window_impl.cpp
      operating_system/android/windowing.cpp
      operating_system/android/windowing.h
   )
endif ()


if (WIN32 OR LINUX OR APPLE)
   list(APPEND core_source

      #operating_system/ansios/_.h
      #operating_system/ansios/_ansios.h
      #operating_system/ansios/_c.h
      #operating_system/ansios/ansios_file.h
      #operating_system/ansios/base.cpp
      #operating_system/ansios/callstack.h
      #operating_system/ansios/datetime.cpp
      #operating_system/ansios/datetime_c.h
      #operating_system/ansios/exception_engine.cpp
      #operating_system/ansios/exception_engine.h
      #operating_system/ansios/file.cpp
      #operating_system/ansios/file.h
      #operating_system/ansios/file_c.h
      #operating_system/ansios/file_raw.cpp
      #operating_system/ansios/file_raw.h
      #operating_system/ansios/file_std.cpp
      #operating_system/ansios/language.cpp
      #operating_system/ansios/memory.cpp
      #operating_system/ansios/multithreading.h
      #operating_system/ansios/process.cpp
      #operating_system/ansios/user.cpp
      #operating_system/ansios/win.cpp
      #operating_system/posix/base_file.cpp
      #operating_system/posix/local_memory_map.cpp
      #operating_system/posix/pthread.cpp
      #operating_system/posix/thread.cpp
      #operating_system/posix/time.cpp
      #operating_system/posix/timer.cpp
   )
endif ()

if (SOLARIS)
   list(APPEND core_source

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
      #      operating_system/solaris/solaris_process.cpp
      #      operating_system/solaris/solaris_process.h
      #      operating_system/solaris/solaris_process_pid.cpp
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


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   base
   bred
)


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
   target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)





   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_link_libraries(core PRIVATE ${library_references} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)




