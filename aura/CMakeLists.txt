cmake_minimum_required(VERSION 3.17)
project(aura CXX)


list(APPEND library_source
   asset/cube_new.inl
   asset/new.inl
   axispolicy/_.h
   axispolicy/_c.h
   axispolicy/policy_objc.h
   axispolicy/policy_objcpp.h
   axispolicy/policy_winrt.h
   #const/_const.h
   #const/charset.h
   const/idpool.cpp
   const/idpool.h
   filesystem/filemanager/callback.cpp
   filesystem/filemanager/callback.h
   filesystem/filemanager/item_action.cpp
   filesystem/filemanager/item_action.h
   filesystem/_impl.h
   filesystem/filesystem.h
   game/_.h
   game/_game.h
   game/estamira.cpp
   game/estamira.h
   game/game.cpp
   game/game.h
   gpu/gpu/_.h
   gpu/gpu/approach.cpp
   gpu/gpu/approach.h
   gpu/gpu/buffer.cpp
   gpu/gpu/buffer.h
   gpu/gpu/context.cpp
   gpu/gpu/context.h
   gpu/gpu/program.cpp
   gpu/gpu/program.h
   gpu/gpu/shader.cpp
   gpu/gpu/shader.h
   graphics/draw2d/winrt/image_gif.cpp
   graphics/draw2d/_.cpp
   graphics/draw2d/_.h
   graphics/draw2d/_draw2d.h
   graphics/draw2d/_image.h
   graphics/draw2d/_image_impl.h
   graphics/draw2d/_impl.h
   graphics/draw2d/_visual_impl.h
   graphics/draw2d/alpha.cpp
   graphics/draw2d/api.cpp
   graphics/draw2d/api.h
   graphics/draw2d/bitmap.cpp
   graphics/draw2d/bitmap.h
   graphics/draw2d/brush.cpp
   graphics/draw2d/brush.h
   graphics/draw2d/buffered_graphics.cpp
   graphics/draw2d/buffered_graphics.h
   #graphics/draw2d/color.h
   graphics/draw2d/color_matrix.cpp
   graphics/draw2d/color_matrix.h
   graphics/draw2d/common.h
   graphics/draw2d/context_image.cpp
   graphics/draw2d/context_image.h
   graphics/draw2d/cursor.cpp
   graphics/draw2d/cursor.h
   graphics/draw2d/debug.cpp
   graphics/draw2d/device_lock.cpp
   graphics/draw2d/device_lock.h
   graphics/draw2d/draw2d.cpp
   graphics/draw2d/draw2d.h
   graphics/draw2d/fastblur.cpp
   graphics/draw2d/fastblur.h
   graphics/draw2d/fwd.h
   graphics/draw2d/glyph.cpp
   graphics/draw2d/glyph.h
   graphics/draw2d/glyph_set.cpp
   graphics/draw2d/glyph_set.h
   graphics/draw2d/graphics.cpp
   graphics/draw2d/graphics.h
   graphics/draw2d/graphics_extension.cpp
   graphics/draw2d/graphics_extension.h
   graphics/draw2d/icon.cpp
   graphics/draw2d/icon.h
   graphics/draw2d/igui.h
   graphics/draw2d/image.cpp
   graphics/draw2d/image.h
   graphics/draw2d/image_array.cpp
   graphics/draw2d/image_array.h
   graphics/draw2d/image_drawer.cpp
   graphics/draw2d/image_drawer.h
   graphics/draw2d/image_drawing.cpp
   graphics/draw2d/image_drawing.h
   graphics/draw2d/image_dynamic.cpp
   graphics/draw2d/image_dynamic.h
   graphics/draw2d/image_extension.cpp
   graphics/draw2d/image_extension.h
   graphics/draw2d/image_frame.cpp
   graphics/draw2d/image_frame.h
   graphics/draw2d/image_frame_array.h
   graphics/draw2d/image_gif_antialias_8bit.cpp
   graphics/draw2d/image_gif_detect_8bit_borders.cpp
   graphics/draw2d/image_header.h
   graphics/draw2d/image_list.cpp
   graphics/draw2d/image_list.h
   graphics/draw2d/image_map.cpp
   graphics/draw2d/image_map.h
   graphics/draw2d/image_map_ex1.h
   graphics/draw2d/image_meta.h
   graphics/draw2d/image_nanosvg.cpp
   graphics/draw2d/image_object.cpp
   graphics/draw2d/image_palette.h
   graphics/draw2d/image_pointer_array.cpp
   graphics/draw2d/imaging.cpp
   graphics/draw2d/imaging.h
   graphics/draw2d/keep.cpp
   graphics/draw2d/keep.h
   graphics/draw2d/load_gif_frame.cpp
   graphics/draw2d/lock.cpp
   graphics/draw2d/lock.h
   graphics/draw2d/matrix.cpp
   graphics/draw2d/matrix.h
   graphics/draw2d/nano_svg.cpp
   graphics/draw2d/nano_svg_rasterization.cpp
   graphics/draw2d/object.cpp
   graphics/draw2d/object.h
   graphics/draw2d/palette.cpp
   graphics/draw2d/palette.h
   graphics/draw2d/path.cpp
   graphics/draw2d/path.h
   graphics/draw2d/pen.cpp
   graphics/draw2d/pen.h
   graphics/draw2d/pixmap.h
   graphics/draw2d/printer.cpp
   graphics/draw2d/printer.h
   graphics/draw2d/region.cpp
   graphics/draw2d/region.h
   graphics/draw2d/task_tool.cpp
   graphics/draw2d/task_tool.h
   #graphics/draw2d/ttf_util.cpp
   #graphics/draw2d/ttf_util.h
   graphics/draw2d/water_routine.h
   graphics/draw3d/_.h
   graphics/draw3d/ortho.cpp
   graphics/draw3d/ortho.h
   graphics/graphics/asset/close_button.h
   graphics/graphics/asset/close_icon.h
   graphics/graphics/graphics/_.h
   graphics/graphics/_.h
   graphics/graphics/_graphics.h
   graphics/graphics/_impl.h
   graphics/graphics/bitmap_source_buffer.cpp
   graphics/graphics/bitmap_source_buffer.h
   graphics/graphics/buffer.cpp
   graphics/graphics/buffer.h
   graphics/graphics/console.cpp
   graphics/graphics/console.h
   graphics/graphics/device_context.cpp
   graphics/graphics/device_context.h
   graphics/graphics/double_buffer.cpp
   graphics/graphics/double_buffer.h
   graphics/graphics/double_pass_scale.h
   graphics/graphics/filters.h
   graphics/graphics/graphics.cpp
   graphics/graphics/graphics.h
   graphics/graphics/image_console.h
   graphics/graphics/monitor.cpp
   graphics/graphics/multiple_buffer.cpp
   graphics/graphics/multiple_buffer.h
   graphics/graphics/window.h
   graphics/graphics/window_buffer.h
   graphics/graphics/window_dc.h
   graphics/user/close_button.cpp
   graphics/user/close_button.h
   graphics/user/close_icon.cpp
   graphics/user/close_icon.h
   graphics/write_text/_.h
   graphics/write_text/bounding_rect.h
   graphics/write_text/contains.h
   graphics/write_text/drawer.cpp
   graphics/write_text/drawer.h
   graphics/write_text/draw_text.h
   graphics/write_text/font.cpp
   graphics/write_text/font.h
   graphics/write_text/fonts.cpp
   graphics/write_text/fonts.h
   graphics/write_text/font_enumeration.cpp
   graphics/write_text/font_enumeration.h
   graphics/write_text/font_list.cpp
   graphics/write_text/font_list.h
   graphics/write_text/text.h
   graphics/write_text/text_box.cpp
   graphics/write_text/text_box.h
   graphics/write_text/text_out.cpp
   graphics/write_text/text_out.h
   graphics/write_text/text_out_array.cpp
   graphics/write_text/text_out_array.h
   graphics/write_text/write_text.cpp
   graphics/write_text/write_text.h
   graphics/_.h
   graphics/_impl.h
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
   message/_.cpp
   message/_.h
   message/_impl.h
   message/_message.h
   message/timer.cpp
   message/timer.h
   message/user.cpp
   message/user.h
   node/_.h
   node/_node.h
   node/serial.h
   node/operating_system/ansi/_.h
   node/operating_system/ansi/_ansi.h
   node/operating_system/ansi/_c.h
   node/operating_system/ansi/ansi_file.h
   #os/ansios/callstack.h
   node/operating_system/ansi/datetime_c.h
   node/operating_system/ansi/exception_engine.h
   node/operating_system/ansi/file.h
   node/operating_system/ansi/file_c.h
   node/operating_system/ansi/file_raw.h
   node/operating_system/ansi/parallelization.h
   node/operating_system/cairo/_.h
   node/operating_system/cairo/_impl.h
   node/operating_system/_.h
   node/operating_system/_application.cpp
   node/operating_system/_application.h
   #node/operating_system/_c.h
   node/operating_system/_impl.h
   node/operating_system/_operating_system.h
   node/operating_system/_user.h
   #os/argcargv.cpp
   #os/binreloc.cpp
   #os/binreloc.h
   node/operating_system/chronometer.h
   node/operating_system/cross.h
   node/operating_system/file.h
   node/operating_system/graphics.h
   node/operating_system/http.cpp
   node/operating_system/operating_system.h
   #node/operating_system/os_windowing2.h
   #os/process.h
   node/operating_system/text.h
   node/operating_system/thread.cpp
   node/operating_system/time.h
   node/operating_system/windowing.cpp
   node/operating_system/windowing.h
   platform/_features.h
   platform/_impl.h
   platform/_platform.h
   platform/application.cpp
   platform/application.h
   platform/aura_mq.cpp
   platform/context.cpp
   platform/context.h
   platform/draw_context.cpp
   platform/draw_context2.h
   platform/drawable.cpp
   platform/drawable.h
   platform/message_queue.h
   platform/node.cpp
   platform/node.h
   platform/session.cpp
   platform/session.h
   platform/shell_open.cpp
   platform/shell_open.h
   platform/static_start.cpp
   platform/static_start.h
   platform/static_start_aura.cpp
   platform/system.cpp
   platform/system.h
   platform/theme.cpp
   platform/theme.h
   platform/timeout.h
   platform/title.h
   platform/user_parent.h
   template/list.h
   user/_.cpp
   user/_.h
   #user/_const-.h
   user/_const.h
   user/_data.h
   user/_experience_const.h
   user/_impl.h
   user/_interaction_impl.h
   user/_menu.h
   user/_prelude.h
   user/_user.h
   user/box.cpp
   user/box.h
   user/button.cpp
   user/button.h
   user/call_message_handler_task.cpp
   user/call_message_handler_task.h
   user/check_box.cpp
   user/check_box.h
   user/control_descriptor.cpp
   user/control_descriptor.h
   user/copydesk.cpp
   user/copydesk.h
   user/system.cpp
   user/system.h
   user/form.cpp
   user/form.h
   user/form_callback.cpp
   user/form_callback.h
   user/frame.cpp
   user/frame.h
   user/interaction.cpp
   user/interaction.h
   user/interaction_child.cpp
   user/interaction_child.h
   user/interaction_impl.cpp
   user/interaction_impl.h
   user/interaction_layout.cpp
   user/interaction_layout.h
   user/interaction_prodevian.cpp
   user/interaction_prodevian.h
   user/interaction_thread.cpp
   user/interaction_thread.h
   user/interaction_scaler.cpp
   user/interaction_scaler.h
   user/key.cpp
   user/key.h
   user/keyboard.cpp
   user/keyboard.h
   user/main_window.cpp
   user/main_window.h
   user/menu_command.cpp
   user/menu_command.h
   user/message.cpp
   user/message.h
   user/message_box.cpp
   user/message_box.h
   user/message_window.cpp
   user/message_window.h
   user/message_window_listener.h
   user/mouse.cpp
   user/mouse.h
   user/notify_icon.cpp
   user/notify_icon.h
   user/notify_icon_listener.cpp
   user/notify_icon_listener.h
   user/plain_edit.cpp
   user/plain_edit.h
   user/plain_text_data.cpp
   user/plain_text_data.h
   user/primitive_impl.cpp
   user/primitive_impl.h
   user/prodevian.h
   user/progress.cpp
   user/progress.h
   user/range.cpp
   user/range.h
   user/scroll.cpp
   user/scroll.h
   user/scroll_bar.cpp
   user/scroll_bar.h
   user/scroll_info.h
   user/shell.cpp
   user/shell.h
   user/still.cpp
   user/still.h
   user/style.cpp
   user/style.h
   user/style_base.cpp
   user/style_base.h
   user/style_control.cpp
   user/style_control.h
   user/text_composition.cpp
   user/text_composition.h
   user/tool_window.cpp
   user/tool_window.h
   user/user.cpp
   user/user.h
   user/wait_cursor.cpp
   user/wait_cursor.h
   user/window_map.cpp
   user/window_map.h
   user/window_state.cpp
   user/window_state.h
   user/window_util.cpp
   user/window_util.h
   user/windowing.cpp
   user/windowing.h
   windowing/buffer.cpp
   windowing/buffer.h
   windowing/cursor.cpp
   windowing/cursor.h
   windowing/cursor_manager.cpp
   windowing/cursor_manager.h
   windowing/display.cpp
   windowing/display.h
   windowing/icon.cpp
   windowing/icon.h
   windowing/keyboard.cpp
   windowing/keyboard.h
   windowing/menu.cpp
   windowing/menu.h
   windowing/menu_command.cpp
   windowing/menu_command.h
   windowing/menu_item.cpp
   windowing/menu_item.h
   windowing/monitor.cpp
   windowing/monitor.h
   windowing/window.cpp
   windowing/window.h
   windowing/windowing.cpp
   windowing/windowing.h
   version/version.config.h
   version/version.h
   _.cpp
   _.h
   __matter_ca2.cpp
   _defer.h
   _h.h
   application.h
   astr.h
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

if (WIN32)

   list(APPEND library_source
      #node/windows/base/_windows.h
      #node/windows/base/_factory.cpp
      #node/windows/base/
      #node/windows/base/implementation.h
      #node/windows/base/print_job.cpp
      #node/windows/base/print_job.h
      #node/windows/_.h
      #node/windows/_node_windows.h
      #node/windows/_node_windows_private.h
      #node/windows/_windows.h
      #node/windows/application.cpp
      #node/windows/buffer.h
      #node/windows/copydesk.cpp
      #node/windows/copydesk.h
      #node/windows/_factory.cpp
      #node/windows/
      #node/windows/graphics_buffer.cpp
      #node/windows/interaction_impl.cpp
      #node/windows/interaction_impl.h
      #node/windows/interaction_impl_message_bypass.cpp
      #node/windows/shell_open.cpp
      #node/windows/shell_open.h
      #node/windows/system_interaction.cpp
      #node/windows/system_interaction.h
      #node/windows/thread.cpp
      #node/windows/timer.cpp
      #node/windows/trace.cpp
      #node/windows/user.h
      #node/windows/user_frame.cpp
      #node/windows/windows_desktop.cpp
      #node/windows_common/application.cpp
      #os/windows/-ehrror.cpp
      os/windows/_.h
      os/windows/_c.h
      os/windows/_user.h
      os/windows/_windows.h
      os/windows/_windows_impl.h
      #os/windows/application.cpp
      os/windows/aura.cpp
      #os/windows/d2d1_1.h
      os/windows/dpi.cpp
      os/windows/gdi.cpp
      #os/windows/gdi_icon.cpp
      os/windows/gdiplus.h
      os/windows/graphics.cpp
      os/windows/graphics.h
      #os/windows/imm_client.cpp
      #os/windows/imm_client.h
      #os/windows/imm_context.cpp
      #os/windows/imm_context.h
      os/windows/implementation.h
      #os/windows/interaction_debug.cpp
      #os/windows/internal.cpp
      #os/windows/internal.h
      #os/windows/ipc.cpp
      #os/windows/itemidlist.cpp
      #os/windows/itemidlist.h
      #os/windows/language.cpp
      #os/windows/launcher.cpp
      #os/windows/library.cpp
      #os/windows/lock.cpp
      os/windows/main.cpp
      #os/windows/message_loop.cpp
      os/windows/monitor.cpp
      #os/windows/opengl_buffer.h
      #os/windows/port_forward.h
      #os/windows/print_job.h
      #os/windows/printer.cpp
      #os/windows/printer.h
      #os/windows/top_level_enum.h
      #os/windows/window_opengl.cpp
      #os/windows/window_opengl.h
      os/windows/windowing.cpp
      os/windows/windowing.h
      os/windows_common/_.h
      os/windows_common/_c.h
      os/windows_common/_default_dll_impl.h
      os/windows_common/_file_c.h
      os/windows_common/_unicode_c.h
      os/windows_common/bstring.h
      os/windows_common/cotaskptr.h
      #os/windows_common/draw2d_direct2d_global.cpp
      #os/windows_common/draw2d_direct2d_global.h
      os/windows_common/file.h
      os/windows_common/graphics.h
      os/windows_common/multithreading.h
      os/windows_common/new_api.h
      os/windows_common/variant.h
      )

else ()

   list(APPEND library_source
      node/operating_system/cross/windows/windowing.h
      node/operating_system/cross/_.h
      node/operating_system/cross/cross.h
      )

endif ()

if (WINDOWS_TSF)
   list(APPEND library_source
      user/windows_tsf/afxres.h
      user/windows_tsf/context_owner_composition_sink.cpp
      user/windows_tsf/dataobj.cpp
      user/windows_tsf/dataobj.h
      user/windows_tsf/edit_window.cpp
      user/windows_tsf/edit_window.h
      user/windows_tsf/function_provider.cpp
      user/windows_tsf/globals.h
      user/windows_tsf/persist.cpp
      user/windows_tsf/propldr.cpp
      user/windows_tsf/propldr.h
      user/windows_tsf/resource.h
      user/windows_tsf/test.cpp
      user/windows_tsf/text_store_acp.cpp
      user/windows_tsf/tsfapp.cpp
      user/windows_tsf/tsfedit.cpp
      user/windows_tsf/tsfwnd.cpp
      user/windows_tsf/tsfwnd.h
      user/windows_tsf/ui_element_sink.cpp
      user/windows_tsf/winres.h
      )

endif ()


if (UWP)
   list(APPEND library_source
      node/universal_windows/net/net_address.h
      node/universal_windows/_.h
      node/universal_windows/_uwp.h
      node/universal_windows/application.cpp
      node/universal_windows/buffer.h
      node/universal_windows/copydesk.cpp
      node/universal_windows/copydesk.h
      node/universal_windows/directx.cpp
      node/universal_windows/directx.h
      node/universal_windows/directx_impact.cpp
      node/universal_windows/directx_impact.h
      node/universal_windows/directx_interaction.cpp
      node/universal_windows/directx_interaction.h
      node/universal_windows/error.cpp
      node/universal_windows/_factory.cpp
      node/universal_windows/
      node/universal_windows/graphics_buffer.cpp
      node/universal_windows/interaction_impl.cpp
      node/universal_windows/interaction_impl.h
      node/universal_windows/timer.cpp
      node/universal_windows/trace.cpp
      node/universal_windows/util.cpp
      os/universal_windows/_.h
      os/universal_windows/_os_metrowin.cpp
      os/universal_windows/_uwp.h
      os/universal_windows/_winrt.h
      os/universal_windows/application_system_run.cpp
      os/universal_windows/aura.cpp
      os/universal_windows/base_file.h
      os/universal_windows/direct2d_tls.cpp
      #os/universal_windows/dummy_ipc.cpp
      os/universal_windows/file_winrt.h
      os/universal_windows/gdi_winrt.h
      os/universal_windows/graphics.cpp
      os/universal_windows/host_interaction.h
      os/universal_windows/lock.cpp
      os/universal_windows/main.cpp
      os/universal_windows/metrowin_metrowin.h
      os/universal_windows/multithreading.h
      os/universal_windows/multithreading_winrt.h
      os/universal_windows/oswindow.h
      #os/universal_windows/process.h
      os/universal_windows/simple_hold_handle.h
      os/universal_windows/simple_ui.h
      os/universal_windows/sockets.h
      os/universal_windows/user.cpp
      os/universal_windows/windowing.cpp


      )

else ()

   list(APPEND library_source
      #node/operating_system/cross/universal_windows/cross_metrowin_user.cpp
      #node/operating_system/cross/universal_windows/metrowin_user.cpp
      )

endif ()

if (UWP OR WIN32)

endif ()

list(APPEND windowing_source
   windowing/_.h
   windowing/_windowing.h
   windowing/buffer.cpp
   windowing/buffer.h
   #windowing/button.cpp
   #windowing/button.h
   windowing/debug.cpp
   windowing/display.cpp
   windowing/display.h
   windowing/exception.h
   #windowing/hook.cpp
   #windowing/hook.h
   windowing/keyboard.cpp
   windowing/keyboard.h
   #windowing/message_box.cpp
   #windowing/message_box.h
   #windowing/simple_ui_display.cpp
   #windowing/simple_ui_display.h
   windowing/windowing.cpp
   windowing/windowing.h
   #windowing/windowing___.cpp
   windowing/window.cpp
   windowing/window.h
   #windowing/xrender.cpp
   )

if (LINUX)

   list(APPEND library_source
      node/linux/_.h
      node/linux/_linux.h
      node/linux/application.cpp
      node/linux/application.h
      #node/linux/console.cpp
      #node/linux/console.h
      #node/linux/copydesk.cpp
      #node/linux/copydesk.h
      node/linux/_factory.cpp
      node/linux/
      #node/linux/interaction_impl.cpp
      #node/linux/interaction_impl.h
      node/linux/system.cpp
      #os/gdk/aura_gdk.cpp
      #os/gdk/aura_gdk.h
      node/operating_system/linux/_.h
      node/operating_system/linux/_c.h
      node/operating_system/linux/_glib.h
      node/operating_system/linux/_linux.h
      node/operating_system/linux/_user.h
      node/operating_system/linux/appindicator.cpp
      node/operating_system/linux/appindicator.h
      node/operating_system/linux/application_system_run.cpp
      node/operating_system/linux/aura.cpp
      node/operating_system/linux/bloat_pad.h
      node/operating_system/linux/cross_win_file.cpp
      node/operating_system/linux/cross_win_file.h
      node/operating_system/linux/cross_win_gdi.cpp
      node/operating_system/linux/cross_win_gdi.h
      node/operating_system/linux/cross_win_gdi_internal.h
      node/operating_system/linux/debug.cpp
      node/operating_system/linux/debug.h
      node/operating_system/linux/desktop_file.cpp
      node/operating_system/linux/desktop_file.h
      #os/linux/exception_engine.cpp
      #os/linux/exception_engine.h
      node/operating_system/linux/file.cpp
      node/operating_system/linux/file.h
      node/operating_system/linux/graphics.cpp
      node/operating_system/linux/graphics.h
      node/operating_system/linux/graphics2.h
      node/operating_system/linux/language.cpp
      #os/linux/launcher.cpp
      node/operating_system/linux/library.cpp
      node/operating_system/linux/linux.inl
      node/operating_system/linux/linux_linux.h
      #os/linux/list_serial_ports.cpp
      #node/operating_system/linux/lock.cpp
      node/operating_system/linux/message_loop.cpp
      #os/linux/monitor.cpp
      node/operating_system/linux/os.cpp
      #os/linux/osdisplay.cpp
      #os/linux/osdisplay.h
      #os/linux/oswindow.cpp
      #os/linux/oswindow.h
      node/operating_system/linux/parallelization.cpp
      #os/linux/process.cpp
      #os/linux/process.h
      #os/linux/process_pid.cpp
      node/operating_system/linux/simple_app.cpp
      node/operating_system/linux/time.cpp
      node/operating_system/linux/user.cpp
      node/operating_system/linux/user.h
      node/operating_system/linux/user_private.h
      node/operating_system/linux/win_base.cpp
      node/operating_system/linux/window_cairo.h
      #os/linux/window_xlib.cpp
      #os/linux/window_xlib.h
      node/operating_system/linux/windowing.cpp
      #os/linux/windowing_x11.cpp
      #os/linux/windowing_xcb.cpp
      node/operating_system/linux/windowing.h
      node/operating_system/linux/x11.h
      #os/linux/xdisplay.cpp
      #os/linux/xdisplay.h
      #os/linux/xinerama.cpp
      #os/x11/_x11.h
      #os/x11/debug.cpp
      #os/x11/x11_exception.h
      #os/x11/x11_keyboard.cpp
      #os/x11/x11_keyboard.h
      #os/x11/x11_windowing.cpp
      #os/x11/x11_xrender.cpp
      ${windowing_source}
      )
endif ()


if (FREEBSD)

   list(APPEND library_source
      node/freebsd/_.h
      node/freebsd/_freebsd.h
      node/freebsd/application.cpp
      node/freebsd/application.h
      #node/freebsd/console.cpp
      #node/freebsd/console.h
      #node/freebsd/copydesk.cpp
      #node/freebsd/copydesk.h
      node/freebsd/_factory.cpp
      node/freebsd/
      #node/freebsd/interaction_impl.cpp
      #node/freebsd/interaction_impl.h
      node/freebsd/system.cpp
      #os/gdk/aura_gdk.cpp
      #os/gdk/aura_gdk.h
      node/operating_system/freebsd/_.h
      node/operating_system/freebsd/_c.h
      node/operating_system/freebsd/_glib.h
      node/operating_system/freebsd/_freebsd.h
      node/operating_system/freebsd/_user.h
      node/operating_system/freebsd/appindicator.cpp
      node/operating_system/freebsd/appindicator.h
      node/operating_system/freebsd/application_system_run.cpp
      node/operating_system/freebsd/aura.cpp
      node/operating_system/freebsd/bloat_pad.h
      node/operating_system/freebsd/cross_win_file.cpp
      node/operating_system/freebsd/cross_win_file.h
      node/operating_system/freebsd/cross_win_gdi.cpp
      node/operating_system/freebsd/cross_win_gdi.h
      node/operating_system/freebsd/cross_win_gdi_internal.h
      node/operating_system/freebsd/debug.cpp
      node/operating_system/freebsd/debug.h
      node/operating_system/freebsd/desktop_file.cpp
      node/operating_system/freebsd/desktop_file.h
      #os/freebsd/exception_engine.cpp
      #os/freebsd/exception_engine.h
      node/operating_system/freebsd/file.cpp
      node/operating_system/freebsd/file.h
      node/operating_system/freebsd/graphics.cpp
      node/operating_system/freebsd/graphics.h
      node/operating_system/freebsd/graphics2.h
      node/operating_system/freebsd/language.cpp
      #os/freebsd/launcher.cpp
      node/operating_system/freebsd/library.cpp
      #node/operating_system/freebsd/freebsd.inl
      #node/operating_system/freebsd/freebsd_freebsd.h
      #os/freebsd/list_serial_ports.cpp
      #node/operating_system/freebsd/lock.cpp
      node/operating_system/freebsd/message_loop.cpp
      #os/freebsd/monitor.cpp
      node/operating_system/freebsd/os.cpp
      #os/freebsd/osdisplay.cpp
      #os/freebsd/osdisplay.h
      #os/freebsd/oswindow.cpp
      #os/freebsd/oswindow.h
      node/operating_system/freebsd/parallelization.cpp
      #os/freebsd/process.cpp
      #os/freebsd/process.h
      #os/freebsd/process_pid.cpp
      node/operating_system/freebsd/simple_app.cpp
      node/operating_system/freebsd/time.cpp
      node/operating_system/freebsd/user.cpp
      node/operating_system/freebsd/user.h
      node/operating_system/freebsd/user_private.h
      node/operating_system/freebsd/win_base.cpp
      node/operating_system/freebsd/window_cairo.h
      #os/freebsd/window_xlib.cpp
      #os/freebsd/window_xlib.h
      node/operating_system/freebsd/windowing.cpp
      #os/freebsd/windowing_x11.cpp
      #os/freebsd/windowing_xcb.cpp
      node/operating_system/freebsd/windowing.h
      node/operating_system/freebsd/x11.h
      #os/freebsd/xdisplay.cpp
      #os/freebsd/xdisplay.h
      #os/freebsd/xinerama.cpp
      #os/x11/_x11.h
      #os/x11/debug.cpp
      #os/x11/x11_exception.h
      #os/x11/x11_keyboard.cpp
      #os/x11/x11_keyboard.h
      #os/x11/x11_windowing.cpp
      #os/x11/x11_xrender.cpp
      ${windowing_source}
      )
endif ()


if (LINUX OR APPLE OR SOLARIS)
   list(APPEND library_source
      node/posix/_posix.h
      node/posix/application.cpp
      )

endif ()


if (MACOS)
   list(APPEND library_source
      node/macos/_.h
      node/macos/_macos.h
      node/macos/_mm.h
      node/macos/application.cpp
      node/macos/application.h
      #node/macos/copydesk.cpp
      #node/macos/copydesk.h
      node/macos/_factory.cpp
      node/macos/
      node/macos/frame_window.cpp
      #node/macos/interaction_impl.cpp
      #node/macos/interaction_impl.h
      #node/macos/keyboard.cpp
      #node/macos/keyboard.h
      #node/macos/main.cpp
      #node/macos/mm.mm
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
      #os/macos/graphics.cpp
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
      #os/macos/message_loop.cpp
      #os/macos/MessageBoxA.cpp
      #os/macos/mm.mm
      #os/macos/mm_base_user.mm
      #os/macos/mm_graphics.mm
      #os/macos/mm_oswindow.h
      #os/macos/mm_user.mm
      #os/macos/multithreading.cpp
      #os/macos/multithreading.h
      #os/macos/NSPasteboard++.mm
      #os/macos/os.cpp
      #os/macos/os.h
      #os/macos/oswindow_data.cpp
      #os/macos/oswindow_data.h
#      os/macos/process.cpp
#      os/macos/process_c.h
#      os/macos/process_pid.cpp
      #os/macos/simple_app.cpp
      #os/macos/time.cpp
      #os/macos/user.cpp
      #os/macos/user.h
      #os/macos/win_base.cpp
      #os/macos/window_impl.h
      #os/macos/windowing.cpp
      #os/macos/windowing.h
      #os/macos/windowing_c.h
      #os/macos/winpr_keycode.cpp
      )
endif ()


if (IOS)
   list(APPEND library_source
      ios_aura/ios_aura.h
      ios_aura/ios_aura.m
      node/ios/_.h
      node/ios/_ios.h
      node/ios/_m.h
      node/ios/_mm.h
      node/ios/application.cpp
      node/ios/application.h
      node/ios/aura_window.h
      node/ios/aura_window.mm
      node/ios/AuraViewController.h
      node/ios/AuraViewController.mm
      node/ios/AuraWindow.h
      node/ios/AuraWindow.mm
      node/ios/AuraWindowApp.h
      node/ios/AuraWindowApp.mm
      node/ios/AuraWindowFrameView.h
      node/ios/AuraWindowFrameView.mm
      node/ios/exception.cpp
      node/ios/_factory.cpp
      node/ios/
      node/ios/host_interaction.cpp
      node/ios/host_interaction.h
      node/ios/implementation.h
      node/ios/interaction_impl.cpp
      node/ios/interaction_impl.h
      node/ios/internal.h
      node/ios/ios.cpp
      node/ios/main.cpp
      node/ios/plane_system.cpp
      node/ios/plane_system.h
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
      os/ios/mm_graphics.mm
      os/ios/mm_oswindow.h
      os/ios/mm_thread.mm
      os/ios/mm_user.mm
      os/ios/multithreading.cpp
      os/ios/multithreading.h
      os/ios/oswindow_data.cpp
      os/ios/oswindow_data.h
#      os/ios/process.cpp
#      os/ios/process.h
#      os/ios/process_pid.cpp
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
endif ()

if (SOLARIS)
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
#      os/solaris/solaris_process.cpp
#      os/solaris/solaris_process.h
#      os/solaris/solaris_process_pid.cpp
      os/solaris/solaris_simple_ui.cpp
      os/solaris/solaris_simple_ui.h
      os/solaris/solaris_solaris.h
      os/solaris/solaris_thread.cpp
      os/solaris/solaris_user_impl.h
      os/solaris/solaris_win_base.cpp
      os/solaris/solaris_window.cpp
      os/solaris/solaris_window_xlib.cpp
      os/solaris/solaris_window_xlib.h
      )

endif ()

if (ANDROID)
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
      node/android/interaction_impl.cpp
      node/android/interaction_impl.h
      node/android/internal.h
      node/android/main.cpp
      node/android/os_context.cpp
      node/android/os_context.h
#      node/android/process.cpp
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
#      os/android/process.cpp
#      os/android/process.h
#      os/android/process_pid.cpp
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

   list(APPEND library_source
      timer.mm
      node/apple/apple_timer.cpp
#      node/apple/process.cpp
#      node/apple/process.h
      os/apple/_.cpp
      os/apple/_.h
      os/apple/_apple.h
      os/apple/_apple.mm
      os/apple/_c_mm.h
      os/apple/_mm.h
      os/apple/_mm_common.h
      os/apple/debug.cpp
      os/apple/debug.h
      os/apple/exe_path.cpp
      os/apple/graphics.cpp
      os/apple/graphics.h
      os/apple/image_gif.cpp
      os/apple/main.cpp
      os/apple/main.h
      os/apple/multihreading.cpp
      os/apple/ns_exception.cpp
      os/apple/ns_exception.h
#      os/apple/process.cpp
      os/apple/time.h
      os/apple/windowing.cpp
      os/apple/windowing.h
      )

endif ()


if (MACOS)

   list(APPEND library_source
      ios_aura/ios_aura.h
      ios_aura/ios_aura.m
      )

endif ()


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


add_library(aura SHARED ${library_source})


target_precompile_headers(aura PRIVATE framework.h)


set_target_properties(aura PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
   target_compile_options(aura PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(aura PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(aura PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/aura.lib")
   target_link_options(aura PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/aura.def")
   target_link_libraries(aura PRIVATE acme apex aqua zlib libcrypto libssl dwrite d2d1 d3d11 dxgi Dxva2 dbghelp imagehlp dwmapi Setupapi Windowscodecs Winmm ws2_32 Crypt32 Normaliz version Secur32 gdiplus Shlwapi Imm32)
elseif(LINUX OR FREEBSD)
   target_compile_options(aura PRIVATE -fpermissive)
      target_compile_options(aura PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(aura PRIVATE ${PKGCONFIG_LDFLAGS})
   #target_link_options(aura PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(aura PRIVATE dl pthread)
   target_link_libraries(aura PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(aura PRIVATE acme apex aqua)
   target_link_options(aura PRIVATE -Wl,-z,defs)
   message("PKGCONFIG_CFLAGS is " ${PKGCONFIG_CFLAGS})
   message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif ()


target_include_directories(aura PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(aura PRIVATE _AURA_LIBRARY)



