cmake_minimum_required(VERSION 3.16)
project(aura CXX)


list(APPEND library_source
        asset/cube_new.inl
        asset/new.inl
        #axispolicy/_.h
        #axispolicy/_c.h
        #axispolicy/policy_objc.h
        #axispolicy/policy_objcpp.h
        #axispolicy/policy_winrt.h
        #const/_const.h
        #const/charset.h
        constant/idpool.cpp
        constant/idpool.h
        filesystem/filemanager/callback.cpp
        filesystem/filemanager/callback.h
        filesystem/filemanager/item_action.cpp
        filesystem/filemanager/item_action.h
        filesystem/_impl.h
        filesystem/filesystem.h
        game/_.h
        #game/_game.h
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
        gpu/gpu/object.cpp
        gpu/gpu/object.h
        gpu/gpu/program.cpp
        gpu/gpu/program.h
        gpu/gpu/shader.cpp
        gpu/gpu/shader.h
        graphics/draw2d/winrt/image_gif.cpp
        graphics/draw2d/_.cpp
        graphics/draw2d/_.h
        #graphics/draw2d/_component.h
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
        graphics/draw2d/debug.cpp
        graphics/draw2d/device_lock.cpp
        graphics/draw2d/device_lock.h
        graphics/draw2d/draw2d.cpp
        graphics/draw2d/draw2d.h
        graphics/draw2d/fwd.h
        graphics/draw2d/graphics.cpp
        graphics/draw2d/graphics.h
        graphics/draw2d/graphics_extension.cpp
        graphics/draw2d/graphics_extension.h
        graphics/draw2d/holdee.cpp
        graphics/draw2d/holdee.h
        graphics/draw2d/holder.cpp
        graphics/draw2d/holder.h
        graphics/draw2d/host.cpp
        graphics/draw2d/host.h
        graphics/draw2d/item.cpp
        graphics/draw2d/item.h
        #graphics/draw2d/keep.cpp
        #graphics/draw2d/keep.h
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
        graphics/draw2d/path_shape.h
        graphics/draw2d/path_simple_optimization.cpp
        graphics/draw2d/path_simple_optimization.h
        graphics/draw2d/pen.cpp
        graphics/draw2d/pen.h
        graphics/draw2d/printer.cpp
        graphics/draw2d/printer.h
        graphics/draw2d/region.cpp
        graphics/draw2d/region.h
        #graphics/draw2d/region_item.cpp
        #graphics/draw2d/region_shape.h
        graphics/draw2d/task_tool.cpp
        graphics/draw2d/task_tool.h
        #graphics/draw2d/ttf_util.cpp
        #graphics/draw2d/ttf_util.h
        #graphics/draw2d/water_routine.h
        graphics/draw3d/_.h
        graphics/draw3d/ortho.cpp
        graphics/draw3d/ortho.h
        #graphics/graphics/asset/control_box_button.cpp
        #graphics/graphics/asset/control_box_button.h
        #graphics/graphics/asset/control_box_icon.cpp
        #graphics/graphics/asset/control_box_icon.cpp
        graphics/graphics/graphics/_.h
        graphics/graphics/_.h
        #graphics/graphics/_graphics.h
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
        graphics/graphics/target.cpp
        graphics/graphics/target.h
        graphics/graphics/window.h
        graphics/graphics/window_buffer.h
        graphics/graphics/window_dc.h
        #graphics/image/_image.h
        graphics/image/_.cpp
        graphics/image/_image_impl.h
        graphics/image/context_image.cpp
        graphics/image/context_image.h
        graphics/image/cursor.cpp
        graphics/image/cursor.h
        graphics/image/icon.cpp
        graphics/image/icon.h
        graphics/image/image.cpp
        graphics/image/image.h
        graphics/image/array.cpp
        graphics/image/array.h
        graphics/image/drawer.cpp
        graphics/image/drawer.h
        graphics/image/drawing.cpp
        graphics/image/drawing.h
        graphics/image/dynamic.cpp
        graphics/image/dynamic.h
        graphics/image/extension.cpp
        graphics/image/extension.h
        graphics/image/fastblur.cpp
        graphics/image/fastblur.h
        graphics/image/frame.cpp
        graphics/image/frame.h
        graphics/image/frame_array.cpp
        graphics/image/frame_array.h
        graphics/image/gif_antialias_8bit.cpp
        #graphics/image/gif_detect_8bit_borders.cpp
        graphics/image/header.h
        graphics/image/list.cpp
        graphics/image/list.h
        graphics/image/map.cpp
        graphics/image/map.h
        graphics/image/map_ex1.h
        graphics/image/meta.cpp
        graphics/image/meta.h
        graphics/image/nanosvg.cpp
        #graphics/image/object.cpp
        graphics/image/palette.h
        graphics/image/source.cpp
        graphics/image/source.h
        graphics/image/imaging.cpp
        graphics/image/imaging.h
        graphics/image/pixmap.h
        graphics/user/control_box_button.cpp
        graphics/user/control_box_button.h
        graphics/user/control_box_icon.cpp
        graphics/user/control_box_icon.h
        graphics/write_text/_.h
        #graphics/write_text/_shape.h
        #graphics/write_text/_shape.cpp
        graphics/write_text/bounding_rect.h
        graphics/write_text/contains.h
        graphics/write_text/drawer.cpp
        graphics/write_text/drawer.h
        graphics/write_text/draw_text.h
        graphics/write_text/font.cpp
        graphics/write_text/font.h
        graphics/write_text/fonts.cpp
        graphics/write_text/fonts.h
        graphics/write_text/font_descriptor.h
        graphics/write_text/font_enumeration.cpp
        graphics/write_text/font_enumeration.h
        graphics/write_text/font_enumeration_item.cpp
        graphics/write_text/font_enumeration_item.h
        graphics/write_text/font_list.cpp
        graphics/write_text/font_list.h
        #graphics/write_text/font_utf8.cpp
        graphics/write_text/glyph.cpp
        graphics/write_text/glyph.h
        graphics/write_text/glyph_set.cpp
        graphics/write_text/glyph_set.h
        graphics/write_text/text.h
        graphics/write_text/text_box.cpp
        graphics/write_text/text_box.h
        graphics/write_text/text_metric.h
        graphics/write_text/text_out.cpp
        graphics/write_text/text_out.h
        graphics/write_text/text_out_array.cpp
        graphics/write_text/text_out_array.h
        graphics/write_text/true_type_font_utilities.cpp
        graphics/write_text/true_type_font_utilities.h
        graphics/write_text/write_text.cpp
        graphics/write_text/write_text.h
        graphics/_.h
        graphics/_impl.h
        hardware/device_listener.cpp
        hardware/device_listener.h
        hardware/devices.cpp
        hardware/devices.h
        #include/_.cpp
        include/_.h
        #include/_c.h
        #include/_c_bridge.h
        include/_include.h
        #include/_no_templates.h
        #include/_setup.h
        #include/objc.h
        #include/objcpp.h
        #include/winrt.h
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
        message/_.cpp
        message/_.h
        message/_impl.h
        message/_message.h
        message/timer.cpp
        message/timer.h
        message/user.cpp
        message/user.h
#        operating_system/_.h
#        #operating_system/_node.h
#        operating_system/serial.h
#        operating_system/ansi/_.h
#        operating_system/ansi/_ansi.h
#        operating_system/ansi/_c.h
#        operating_system/ansi/ansi_file.h
#        #operating_system/ansios/callstack.h
#        operating_system/ansi/datetime_c.h
#        operating_system/ansi/exception_engine.h
#        operating_system/ansi/file.h
#        operating_system/ansi/file_c.h
#        operating_system/ansi/file_raw.h
#        operating_system/ansi/parallelization.h
#        operating_system/cairo/_.h
#        operating_system/cairo/_impl.h
#        operating_system/_.h
#        #operating_system/_application.cpp
#        operating_system/_application.h
#        #operating_system/_c.h
#        operating_system/_impl.h
#        operating_system/_operating_system.h
#        operating_system/_user.h
#        #operating_system/argcargv.cpp
#        #operating_system/binreloc.cpp
#        #operating_system/binreloc.h
#        operating_system/chronometer.h
#        operating_system/cross.h
#        operating_system/file.h
#        operating_system/graphics.h
#        operating_system/http.cpp
#        #operating_system/operating_system.h
#        #operating_system/os_windowing2.h
#        #operating_system/process.h
#        #operating_system/text.h
#        operating_system/thread.cpp
#        operating_system/time.h
#        operating_system/windowing.cpp
#        operating_system/windowing.h
        platform/_features.h
        platform/_impl.h
        platform/_platform.h
        platform/application.cpp
        platform/application.h
        platform/aura.h
        #platform/aura.cpp
        platform/message_queue.cpp
        platform/context.cpp
        platform/context.h
        platform/draw_context.cpp
        platform/draw_context2.h
        platform/message_queue.h
        platform/node.cpp
        platform/node.h
        platform/session.cpp
        platform/session.h
        platform/shell_open.cpp
        platform/shell_open.h
        #platform/static_start.cpp
        #platform/static_start.h
        #platform/static_start_aura.cpp
        platform/system.cpp
        platform/system.h
        platform/theme.cpp
        platform/theme.h
        platform/timeout.h
        platform/title.h
        platform/user_parent.h
        template/list.h
        user/appearance/appearance.cpp
        user/appearance/appearance.h
        #user/appearance/_appearance.h
        #user/menu/_menu.h
        user/menu/command.cpp
        user/menu/command.h
        user/menu/shared.cpp
        user/menu/shared.h
        user/menu/shared_commnand.cpp
        user/menu/shared_command.h

        #user/micro/message_box.cpp
        #user/micro/message_box.h
        user/user/_.cpp
        user/user/_.h
        #user/_const-.h
        user/user/_constant.h
        user/user/_data.h
        user/user/_experience_const.h
        user/user/_impl.h
        user/user/_interaction_impl.h
        user/user/_prelude.h
        #user/user/_user.h
        user/user/alpha_source.cpp
        user/user/alpha_source.h
        user/user/box.cpp
        user/user/box.h
        user/user/button.cpp
        user/user/button.h
        user/user/call_message_handler_task.cpp
        user/user/call_message_handler_task.h
        user/user/check_box.cpp
        user/user/check_box.h
        #user/user/control_descriptor.cpp
        user/user/control_descriptor.h
        user/user/control_style.cpp
        user/user/copydesk.cpp
        user/user/copydesk.h
        user/user/drawable.cpp
        user/user/drawable.h
        user/user/form.cpp
        user/user/form.h
        user/user/form_callback.cpp
        user/user/form_callback.h
        user/user/frame.cpp
        user/user/frame.h
        user/user/interaction.cpp
        user/user/interaction.h
        user/user/interaction_child.cpp
        user/user/interaction_child.h
        #use/user//interaction_draw2d.h
        user/user/interaction_impl.cpp
        user/user/interaction_impl.h
        user/user/interaction_layout.cpp
        user/user/interaction_layout.h
        user/user/interaction_prodevian.cpp
        user/user/interaction_prodevian.h
        user/user/interaction_thread.cpp
        user/user/interaction_thread.h
        user/user/interaction_scaler.cpp
        user/user/interaction_scaler.h
        user/user/key.cpp
        user/user/key.h
        user/user/keyboard.cpp
        user/user/keyboard.h
        user/user/layout_state.cpp
        user/user/layout_state.h
        user/user/main_window.cpp
        user/user/main_window.h
        #user/user/message.cpp
        #user/user/message.h
        user/user/message_box.cpp
        user/user/message_box.h
        #user/user/message_window.cpp
        #user/user/message_window.h
        #user/user/message_window_listener.h
        #user/user/mouse.cpp
        #user/user/mouse.h
        user/user/notify_icon.cpp
        user/user/notify_icon.h
        user/user/notify_icon_listener.cpp
        user/user/notify_icon_listener.h
        user/user/plain_edit.cpp
        user/user/plain_edit.h
        user/user/plain_edit_style.h
        user/user/plain_text_data.cpp
        user/user/plain_text_data.h
        user/user/plain_text_tree.cpp
        user/user/plain_text_tree.h
        user/user/primitive_impl.cpp
        user/user/primitive_impl.h
        user/user/prodevian.cpp
        user/user/prodevian.h
        user/user/progress.cpp
        user/user/progress.h
        user/user/range.cpp
        user/user/range.h
        user/user/scroll.cpp
        user/user/scroll.h
        user/user/scroll_bar.cpp
        user/user/scroll_bar.h
        user/user/scroll_info.h
        user/user/shell.cpp
        user/user/shell.h
        user/user/still.cpp
        user/user/still.h
        user/user/style.cpp
        user/user/style.h
        user/user/style_base.cpp
        user/user/style_base.h
        #user/user/style_control.cpp
        #user/user/style_control.h
        user/user/system.cpp
        user/user/system.h
        user/user/text_composition_client.cpp
        user/user/text_composition_client.h
        user/user/text_composition_composite.cpp
        user/user/text_composition_composite.h
        user/user/tool_window.cpp
        user/user/tool_window.h
        user/user/user.cpp
        user/user/user.h
        user/user/wait_cursor.cpp
        user/user/wait_cursor.h
        #user/user/window_map.cpp
        #user/user/window_map.h
        user/user/window_util.cpp
        user/user/window_util.h
        user/user/windowing.cpp
        user/user/windowing.h
        user/user/zorder.cpp
        user/user/zorder.h
        user/user/horizontal_scroll_base.cpp
        user/user/horizontal_scroll_base.h
        user/user/vertical_scroll_base.cpp
        user/user/vertical_scroll_base.h
        user/user/visual_state.cpp
        user/user/visual_state.h
        #windowing/buffer.cpp
        #windowing/buffer.h
        windowing/cursor.cpp
        windowing/cursor.h
        windowing/cursor_manager.cpp
        windowing/cursor_manager.h
        windowing/desktop_environment.cpp
        windowing/desktop_environment.h
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
        #__matter_ca2.cpp
        #_defer.h
        #_h.h
        #application.h
        #astr.h
        #console.h
        #console_slim.h
        #context_glx.cpp
        framework.cpp
        framework.h
        #framework_c.h
        #id.h
        #library.h
        #message.h
        #procedure.h
        #update.h
        )

if (WIN32)

    list(APPEND library_source
            #operating_system/windows/base/_windows.h
            #operating_system/windows/base/_factory.cpp
            #operating_system/windows/base/
            #operating_system/windows/base/implementation.h
            #operating_system/windows/base/print_job.cpp
            #operating_system/windows/base/print_job.h
            #operating_system/windows/_.h
            #operating_system/windows/_node_windows.h
            #operating_system/windows/_node_windows_private.h
            #operating_system/windows/_windows.h
            #operating_system/windows/application.cpp
            #operating_system/windows/buffer.h
            #operating_system/windows/copydesk.cpp
            #operating_system/windows/copydesk.h
            #operating_system/windows/_factory.cpp
            #operating_system/windows/
            #operating_system/windows/graphics_buffer.cpp
            #operating_system/windows/interaction_impl.cpp
            #operating_system/windows/interaction_impl.h
            #operating_system/windows/interaction_impl_message_bypass.cpp
            #operating_system/windows/shell_open.cpp
            #operating_system/windows/shell_open.h
            #operating_system/windows/system_interaction.cpp
            #operating_system/windows/system_interaction.h
            #operating_system/windows/thread.cpp
            #operating_system/windows/timer.cpp
            #operating_system/windows/trace.cpp
            #operating_system/windows/user.h
            #operating_system/windows/user_frame.cpp
            #operating_system/windows/windows_desktop.cpp
            #operating_system/windows_common/application.cpp
            #operating_system/windows/-ehrror.cpp
            #      operating_system/windows/_.h
            #      operating_system/windows/_c.h
            #      operating_system/windows/_user.h
            #      operating_system/windows/_windows.h
            #      operating_system/windows/_windows_impl.h
            #operating_system/windows/application.cpp
            #      operating_system/windows/aura.cpp
            #operating_system/windows/d2d1_1.h
            #      operating_system/windows/dpi.cpp
            #      operating_system/windows/gdi.cpp
            #operating_system/windows/gdi_icon.cpp
            #      operating_system/windows/gdiplus.h
            #      operating_system/windows/graphics.cpp
            #      operating_system/windows/graphics.h
            #operating_system/windows/imm_client.cpp
            #operating_system/windows/imm_client.h
            #operating_system/windows/imm_context.cpp
            #operating_system/windows/imm_context.h
            #      operating_system/windows/implementation.h
            #operating_system/windows/interaction_debug.cpp
            #operating_system/windows/internal.cpp
            #operating_system/windows/internal.h
            #operating_system/windows/ipc.cpp
            #operating_system/windows/itemidlist.cpp
            #operating_system/windows/itemidlist.h
            #operating_system/windows/language.cpp
            #operating_system/windows/launcher.cpp
            #operating_system/windows/library.cpp
            #operating_system/windows/lock.cpp
            #      operating_system/windows/main.cpp
            #operating_system/windows/message_loop.cpp
            #      operating_system/windows/monitor.cpp
            #operating_system/windows/opengl_buffer.h
            #operating_system/windows/port_forward.h
            #operating_system/windows/print_job.h
            #operating_system/windows/printer.cpp
            #operating_system/windows/printer.h
            #operating_system/windows/top_level_enum.h
            #operating_system/windows/window_opengl.cpp
            #operating_system/windows/window_opengl.h
            #      operating_system/windows/windowing.cpp
            #      operating_system/windows/windowing.h
            #      operating_system/windows_common/_.h
            #      operating_system/windows_common/_c.h
            #      operating_system/windows_common/_default_dll_impl.h
            #      operating_system/windows_common/_file_c.h
            #      operating_system/windows_common/_unicode_c.h
            #      operating_system/windows_common/bstring.h
            #      operating_system/windows_common/cotaskptr.h
            #operating_system/windows_common/draw2d_direct2d_global.cpp
            #operating_system/windows_common/draw2d_direct2d_global.h
            #      operating_system/windows_common/file.h
            #      operating_system/windows_common/graphics.h
            #      operating_system/windows_common/multithreading.h
            #      operating_system/windows_common/new_api.h
            #      operating_system/windows_common/variant.h
            )

else ()

#    list(APPEND library_source
#            operating_system/cross/windows/windowing.h
#            operating_system/cross/_.h
#            operating_system/cross/cross.h
#            )

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


#if (UWP)
#    list(APPEND library_source
#            operating_system/universal_windows/net/net_address.h
#            operating_system/universal_windows/_.h
#            operating_system/universal_windows/_uwp.h
#            operating_system/universal_windows/application.cpp
#            operating_system/universal_windows/buffer.h
#            operating_system/universal_windows/copydesk.cpp
#            operating_system/universal_windows/copydesk.h
#            operating_system/universal_windows/directx.cpp
#            operating_system/universal_windows/directx.h
#            operating_system/universal_windows/directx_impact.cpp
#            operating_system/universal_windows/directx_impact.h
#            operating_system/universal_windows/directx_interaction.cpp
#            operating_system/universal_windows/directx_interaction.h
#            operating_system/universal_windows/error.cpp
#            operating_system/universal_windows/_factory.cpp
#            operating_system/universal_windows/
#            operating_system/universal_windows/graphics_buffer.cpp
#            operating_system/universal_windows/interaction_impl.cpp
#            operating_system/universal_windows/interaction_impl.h
#            operating_system/universal_windows/timer.cpp
#            operating_system/universal_windows/trace.cpp
#            operating_system/universal_windows/util.cpp
#            operating_system/universal_windows/_.h
#            operating_system/universal_windows/_os_metrowin.cpp
#            operating_system/universal_windows/_uwp.h
#            operating_system/universal_windows/_winrt.h
#            operating_system/universal_windows/application_system_run.cpp
#            operating_system/universal_windows/aura.cpp
#            operating_system/universal_windows/base_file.h
#            operating_system/universal_windows/direct2d_tls.cpp
#            #operating_system/universal_windows/dummy_ipc.cpp
#            operating_system/universal_windows/file_winrt.h
#            operating_system/universal_windows/gdi_winrt.h
#            operating_system/universal_windows/graphics.cpp
#            operating_system/universal_windows/host_interaction.h
#            operating_system/universal_windows/lock.cpp
#            operating_system/universal_windows/main.cpp
#            operating_system/universal_windows/metrowin_metrowin.h
#            operating_system/universal_windows/multithreading.h
#            operating_system/universal_windows/multithreading_winrt.h
#            operating_system/universal_windows/oswindow.h
#            #operating_system/universal_windows/process.h
#            operating_system/universal_windows/simple_hold_handle.h
#            operating_system/universal_windows/simple_ui.h
#            operating_system/universal_windows/sockets.h
#            operating_system/universal_windows/user.cpp
#            operating_system/universal_windows/windowing.cpp
#
#
#            )
#
#else ()
#
#    list(APPEND library_source
#            #operating_system/cross/universal_windows/cross_metrowin_user.cpp
#            #operating_system/cross/universal_windows/metrowin_user.cpp
#            )
#
#endif ()

if (UWP OR WIN32)

endif ()

list(APPEND windowing_source
        windowing/_.h
        #windowing/_component.h
        #windowing/buffer.cpp
        #windowing/buffer.h
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

#if (LINUX)
#
#    list(APPEND library_source
#            operating_system/linux/_.h
#            #operating_system/linux/_linux.h
#            operating_system/linux/application.cpp
#            operating_system/linux/application.h
#            #operating_system/linux/console.cpp
#            #operating_system/linux/console.h
#            #operating_system/linux/copydesk.cpp
#            #operating_system/linux/copydesk.h
#            operating_system/linux/_factory.cpp
#            operating_system/linux/
#            #operating_system/linux/interaction_impl.cpp
#            #operating_system/linux/interaction_impl.h
#            operating_system/linux/system.cpp
#            #operating_system/gdk/aura_gdk.cpp
#            #operating_system/gdk/aura_gdk.h
#            operating_system/linux/_.h
#            operating_system/linux/_c.h
#            operating_system/linux/_glib.h
#            #operating_system/linux/_linux.h
#            operating_system/linux/_user.h
#            operating_system/linux/appindicator.cpp
#            operating_system/linux/appindicator.h
#            operating_system/linux/application_system_run.cpp
#            operating_system/linux/aura.cpp
#            operating_system/linux/bloat_pad.h
#            operating_system/linux/cross_win_file.cpp
#            operating_system/linux/cross_win_file.h
#            operating_system/linux/cross_win_gdi.cpp
#            operating_system/linux/cross_win_gdi.h
#            operating_system/linux/cross_win_gdi_internal.h
#            operating_system/linux/debug.cpp
#            operating_system/linux/debug.h
#            #operating_system/linux/desktop_file.cpp
#            #operating_system/linux/desktop_file.h
#            #operating_system/linux/exception_engine.cpp
#            #operating_system/linux/exception_engine.h
#            operating_system/linux/file.cpp
#            operating_system/linux/file.h
#            operating_system/linux/graphics.cpp
#            operating_system/linux/graphics.h
#            operating_system/linux/graphics2.h
#            operating_system/linux/language.cpp
#            #operating_system/linux/launcher.cpp
#            operating_system/linux/library.cpp
#            operating_system/linux/linux.inl
#            operating_system/linux/linux_linux.h
#            #operating_system/linux/list_serial_ports.cpp
#            #operating_system/linux/lock.cpp
#            operating_system/linux/message_loop.cpp
#            #operating_system/linux/monitor.cpp
#            operating_system/linux/os.cpp
#            #operating_system/linux/osdisplay.cpp
#            #operating_system/linux/osdisplay.h
#            #operating_system/linux/oswindow.cpp
#            #operating_system/linux/oswindow.h
#            operating_system/linux/parallelization.cpp
#            #operating_system/linux/process.cpp
#            #operating_system/linux/process.h
#            #operating_system/linux/process_pid.cpp
#            operating_system/linux/simple_app.cpp
#            operating_system/linux/time.cpp
#            operating_system/linux/user.cpp
#            operating_system/linux/user.h
#            operating_system/linux/user_private.h
#            operating_system/linux/win_base.cpp
#            operating_system/linux/window_cairo.h
#            #operating_system/linux/window_xlib.cpp
#            #operating_system/linux/window_xlib.h
#            operating_system/linux/windowing.cpp
#            #operating_system/linux/windowing_x11.cpp
#            #operating_system/linux/windowing_xcb.cpp
#            operating_system/linux/windowing.h
#            operating_system/linux/x11.h
#            #operating_system/linux/xdisplay.cpp
#            #operating_system/linux/xdisplay.h
#            #operating_system/linux/xinerama.cpp
#            #operating_system/x11/_x11.h
#            #operating_system/x11/debug.cpp
#            #operating_system/x11/x11_exception.h
#            #operating_system/x11/x11_keyboard.cpp
#            #operating_system/x11/x11_keyboard.h
#            #operating_system/x11/x11_windowing.cpp
#            #operating_system/x11/x11_xrender.cpp
#            ${windowing_source}
#            )
#endif ()
#
#
#if (FREEBSD)
#
#    list(APPEND library_source
#            operating_system/freebsd/_.h
#            operating_system/freebsd/_freebsd.h
#            operating_system/freebsd/application.cpp
#            operating_system/freebsd/application.h
#            #operating_system/freebsd/console.cpp
#            #operating_system/freebsd/console.h
#            #operating_system/freebsd/copydesk.cpp
#            #operating_system/freebsd/copydesk.h
#            operating_system/freebsd/_factory.cpp
#            operating_system/freebsd/
#            #operating_system/freebsd/interaction_impl.cpp
#            #operating_system/freebsd/interaction_impl.h
#            operating_system/freebsd/system.cpp
#            #operating_system/gdk/aura_gdk.cpp
#            #operating_system/gdk/aura_gdk.h
#            operating_system/freebsd/_.h
#            operating_system/freebsd/_c.h
#            operating_system/freebsd/_glib.h
#            operating_system/freebsd/_freebsd.h
#            operating_system/freebsd/_user.h
#            operating_system/freebsd/appindicator.cpp
#            operating_system/freebsd/appindicator.h
#            operating_system/freebsd/application_system_run.cpp
#            operating_system/freebsd/aura.cpp
#            operating_system/freebsd/bloat_pad.h
#            operating_system/freebsd/cross_win_file.cpp
#            operating_system/freebsd/cross_win_file.h
#            operating_system/freebsd/cross_win_gdi.cpp
#            operating_system/freebsd/cross_win_gdi.h
#            operating_system/freebsd/cross_win_gdi_internal.h
#            operating_system/freebsd/debug.cpp
#            operating_system/freebsd/debug.h
#            #operating_system/freebsd/desktop_file.cpp
#            #operating_system/freebsd/desktop_file.h
#            #operating_system/freebsd/exception_engine.cpp
#            #operating_system/freebsd/exception_engine.h
#            operating_system/freebsd/file.cpp
#            operating_system/freebsd/file.h
#            operating_system/freebsd/graphics.cpp
#            operating_system/freebsd/graphics.h
#            operating_system/freebsd/graphics2.h
#            operating_system/freebsd/language.cpp
#            #operating_system/freebsd/launcher.cpp
#            operating_system/freebsd/library.cpp
#            #operating_system/freebsd/freebsd.inl
#            #operating_system/freebsd/freebsd_freebsd.h
#            #operating_system/freebsd/list_serial_ports.cpp
#            #operating_system/freebsd/lock.cpp
#            operating_system/freebsd/message_loop.cpp
#            #operating_system/freebsd/monitor.cpp
#            operating_system/freebsd/os.cpp
#            #operating_system/freebsd/osdisplay.cpp
#            #operating_system/freebsd/osdisplay.h
#            #operating_system/freebsd/oswindow.cpp
#            #operating_system/freebsd/oswindow.h
#            operating_system/freebsd/parallelization.cpp
#            #operating_system/freebsd/process.cpp
#            #operating_system/freebsd/process.h
#            #operating_system/freebsd/process_pid.cpp
#            operating_system/freebsd/simple_app.cpp
#            operating_system/freebsd/time.cpp
#            operating_system/freebsd/user.cpp
#            operating_system/freebsd/user.h
#            operating_system/freebsd/user_private.h
#            operating_system/freebsd/win_base.cpp
#            operating_system/freebsd/window_cairo.h
#            #operating_system/freebsd/window_xlib.cpp
#            #operating_system/freebsd/window_xlib.h
#            operating_system/freebsd/windowing.cpp
#            #operating_system/freebsd/windowing_x11.cpp
#            #operating_system/freebsd/windowing_xcb.cpp
#            operating_system/freebsd/windowing.h
#            operating_system/freebsd/x11.h
#            #operating_system/freebsd/xdisplay.cpp
#            #operating_system/freebsd/xdisplay.h
#            #operating_system/freebsd/xinerama.cpp
#            #operating_system/x11/_x11.h
#            #operating_system/x11/debug.cpp
#            #operating_system/x11/x11_exception.h
#            #operating_system/x11/x11_keyboard.cpp
#            #operating_system/x11/x11_keyboard.h
#            #operating_system/x11/x11_windowing.cpp
#            #operating_system/x11/x11_xrender.cpp
#            graphics/write_text/font_utf8.cpp
#            ${windowing_source}
#            )
#endif ()
#
#
#if (LINUX OR APPLE OR SOLARIS)
#    list(APPEND library_source
#            operating_system/posix/_posix.h
#            #  operating_system/posix/application.cpp
#            )
#
#endif ()


#if (MACOS)
#    list(APPEND library_source
#            operating_system/macos/_.h
#            operating_system/macos/_macos.h
#            operating_system/macos/_mm.h
#            operating_system/macos/application.cpp
#            operating_system/macos/application.h
#            #operating_system/macos/copydesk.cpp
#            #operating_system/macos/copydesk.h
#            operating_system/macos/_factory.cpp
#            operating_system/macos/
#            operating_system/macos/frame_window.cpp
#            #operating_system/macos/interaction_impl.cpp
#            #operating_system/macos/interaction_impl.h
#            #operating_system/macos/keyboard.cpp
#            #operating_system/macos/keyboard.h
#            #operating_system/macos/main.cpp
#            #operating_system/macos/mm.mm
#            #operating_system/macos/thread.cpp
#            #operating_system/macos/thread.h
#            #operating_system/macos/trace.cpp
#            #operating_system/macos/user.h
#            #operating_system/macos/util.cpp
#            #operating_system/macos/_.h
#            #operating_system/macos/_c.h
#            #operating_system/macos/_macos.h
#            #operating_system/macos/_mm.h
#            #operating_system/macos/application_system_run.cpp
#            #operating_system/macos/aura.cpp
#            #operating_system/macos/clipboard.cpp
#            #operating_system/macos/cross_win.cpp
#            #operating_system/macos/cross_win_file.cpp
#            #operating_system/macos/cross_win_gdi.h
#            #operating_system/macos/debug.cpp
#            #operating_system/macos/exception_engine.cpp
#            #operating_system/macos/exception_engine.h
#            #operating_system/macos/file.cpp
#            #operating_system/macos/file.h
#            #operating_system/macos/file.mm
#            #operating_system/macos/graphics.cpp
#            #operating_system/macos/graphics_mm.h
#            #operating_system/macos/internal.h
#            #operating_system/macos/keyboard.cpp
#            #operating_system/macos/language.cpp
#            #operating_system/macos/launcher.cpp
#            #operating_system/macos/library.cpp
#            #operating_system/macos/list_serial_ports.cpp
#            #operating_system/macos/lock.cpp
#            #operating_system/macos/macos.h
#            #operating_system/macos/main.h
#            #operating_system/macos/message_loop.cpp
#            #operating_system/macos/MessageBoxA.cpp
#            #operating_system/macos/mm.mm
#            #operating_system/macos/mm_base_user.mm
#            #operating_system/macos/mm_graphics.mm
#            #operating_system/macos/mm_oswindow.h
#            #operating_system/macos/mm_user.mm
#            #operating_system/macos/multithreading.cpp
#            #operating_system/macos/multithreading.h
#            #operating_system/macos/NSPasteboard++.mm
#            #operating_system/macos/os.cpp
#            #operating_system/macos/os.h
#            #operating_system/macos/oswindow_data.cpp
#            #operating_system/macos/oswindow_data.h
#            #      operating_system/macos/process.cpp
#            #      operating_system/macos/process_c.h
#            #      operating_system/macos/process_pid.cpp
#            #operating_system/macos/simple_app.cpp
#            #operating_system/macos/time.cpp
#            #operating_system/macos/user.cpp
#            #operating_system/macos/user.h
#            #operating_system/macos/win_base.cpp
#            #operating_system/macos/window_impl.h
#            #operating_system/macos/windowing.cpp
#            #operating_system/macos/windowing.h
#            #operating_system/macos/windowing_c.h
#            #operating_system/macos/winpr_keycode.cpp
#            )
#endif ()
#
#
#if (IOS)
#    list(APPEND library_source
#            ios_aura/ios_aura.h
#            ios_aura/ios_aura.m
#            operating_system/ios/_.h
#            operating_system/ios/_ios.h
#            operating_system/ios/_m.h
#            operating_system/ios/_mm.h
#            operating_system/ios/application.cpp
#            operating_system/ios/application.h
#            operating_system/ios/aura_window.h
#            operating_system/ios/aura_window.mm
#            operating_system/ios/AuraImpactController.h
#            operating_system/ios/AuraImpactController.mm
#            operating_system/ios/AuraWindow.h
#            operating_system/ios/AuraWindow.mm
#            operating_system/ios/AuraWindowApp.h
#            operating_system/ios/AuraWindowApp.mm
#            operating_system/ios/AuraWindowFrameImpact.h
#            operating_system/ios/AuraWindowFrameImpact.mm
#            operating_system/ios/exception.cpp
#            operating_system/ios/_factory.cpp
#            operating_system/ios/
#            operating_system/ios/host_interaction.cpp
#            operating_system/ios/host_interaction.h
#            operating_system/ios/implementation.h
#            operating_system/ios/interaction_impl.cpp
#            operating_system/ios/interaction_impl.h
#            operating_system/ios/internal.h
#            operating_system/ios/ios.cpp
#            operating_system/ios/main.cpp
#            operating_system/ios/plane_system.cpp
#            operating_system/ios/plane_system.h
#            operating_system/ios/RoundCaretImpact.h
#            operating_system/ios/RoundCaretImpact.mm
#            operating_system/ios/RoundEditImpact.h
#            operating_system/ios/RoundEditImpact.mm
#            operating_system/ios/RoundTextPosition.h
#            operating_system/ios/RoundTextPosition.mm
#            operating_system/ios/RoundTextRange.h
#            operating_system/ios/RoundTextRange.mm
#            operating_system/ios/RoundTextImpact.h
#            operating_system/ios/RoundTextImpact.mm
#            operating_system/ios/state.h
#            operating_system/ios/thread.cpp
#            operating_system/ios/thread.h
#            operating_system/ios/trace.cpp
#            operating_system/ios/util.cpp
#            operating_system/ios/_.h
#            operating_system/ios/_c.h
#            operating_system/ios/_ios.h
#            operating_system/ios/_m.h
#            operating_system/ios/_mm.h
#            operating_system/ios/application_system_run.cpp
#            operating_system/ios/aura.cpp
#            operating_system/ios/base_internal.h
#            operating_system/ios/base_user.cpp
#            operating_system/ios/cross_win.cpp
#            operating_system/ios/cross_win_file.cpp
#            operating_system/ios/cross_win_gdi.h
#            operating_system/ios/crypt.cpp
#            operating_system/ios/debug.cpp
#            operating_system/ios/error.cpp
#            operating_system/ios/exception_engine.cpp
#            operating_system/ios/exception_engine.h
#            operating_system/ios/file.cpp
#            operating_system/ios/fontopus.cpp
#            operating_system/ios/gen_1.h
#            operating_system/ios/graphics.cpp
#            operating_system/ios/implementation.h
#            operating_system/ios/internal.h
#            operating_system/ios/language.cpp
#            operating_system/ios/launcher.cpp
#            operating_system/ios/library.cpp
#            operating_system/ios/lock.cpp
#            operating_system/ios/MessageBoxA_W.mm
#            operating_system/ios/mm.mm
#            operating_system/ios/mm_cross_gdi.mm
#            operating_system/ios/mm_graphics.h
#            operating_system/ios/mm_graphics.mm
#            operating_system/ios/mm_oswindow.h
#            operating_system/ios/mm_thread.mm
#            operating_system/ios/mm_user.mm
#            operating_system/ios/multithreading.cpp
#            operating_system/ios/multithreading.h
#            operating_system/ios/oswindow_data.cpp
#            operating_system/ios/oswindow_data.h
#            #      operating_system/ios/process.cpp
#            #      operating_system/ios/process.h
#            #      operating_system/ios/process_pid.cpp
#            operating_system/ios/time.cpp
#            operating_system/ios/user.cpp
#            operating_system/ios/win_base.cpp
#            operating_system/ios/window.cpp
#            operating_system/ios/window.h
#            "operating_system/ios/window_boot 2.h"
#            operating_system/ios/window_boot.h
#            operating_system/ios/window_impl.h
#            operating_system/ios/windowing.cpp
#            operating_system/ios/windowing.h
#            )
#endif ()
#
#if (SOLARIS)
#    list(APPEND library_source
#            operating_system/solaris/linux_internal.h
#            operating_system/solaris/solaris.cpp
#            operating_system/solaris/solaris.h
#            operating_system/solaris/solaris_cairo_keep.cpp
#            operating_system/solaris/solaris_cairo_keep.h
#            operating_system/solaris/solaris_cross_win_file.cpp
#            operating_system/solaris/solaris_cross_win_file.h
#            operating_system/solaris/solaris_cross_win_gdi.cpp
#            operating_system/solaris/solaris_cross_win_gdi.h
#            operating_system/solaris/solaris_cross_win_gdi_internal.h
#            operating_system/solaris/solaris_debug.h
#            operating_system/solaris/solaris_display.cpp
#            operating_system/solaris/solaris_file.cpp
#            operating_system/solaris/solaris_file.h
#            operating_system/solaris/solaris_file_watcher.cpp
#            operating_system/solaris/solaris_file_watcher.h
#            operating_system/solaris/solaris_graphics.h
#            operating_system/solaris/solaris_http.cpp
#            operating_system/solaris/solaris_http.h
#            operating_system/solaris/solaris_http_lib.cpp
#            operating_system/solaris/solaris_http_lib.h
#            operating_system/solaris/solaris_internal.h
#            operating_system/solaris/solaris_launcher.cpp
#            operating_system/solaris/solaris_library.cpp
#            operating_system/solaris/solaris_lock.cpp
#            operating_system/solaris/solaris_message_loop.cpp
#            #      operating_system/solaris/solaris_process.cpp
#            #      operating_system/solaris/solaris_process.h
#            #      operating_system/solaris/solaris_process_pid.cpp
#            operating_system/solaris/solaris_simple_ui.cpp
#            operating_system/solaris/solaris_simple_ui.h
#            operating_system/solaris/solaris_solaris.h
#            operating_system/solaris/solaris_thread.cpp
#            operating_system/solaris/solaris_user_impl.h
#            operating_system/solaris/solaris_win_base.cpp
#            operating_system/solaris/solaris_window.cpp
#            operating_system/solaris/solaris_window_xlib.cpp
#            operating_system/solaris/solaris_window_xlib.h
#            )
#
#endif ()
#
#if (ANDROID)
#    list(APPEND library_source
#            operating_system/android/Kerr/kerr.h
#            operating_system/android/Kerr/LocalMemory.h
#            operating_system/android/_.h
#            operating_system/android/_android.h
#            operating_system/android/android.cpp
#            operating_system/android/android1.cpp
#            operating_system/android/android1.h
#            operating_system/android/application.cpp
#            operating_system/android/application.h
#            operating_system/android/buffer.cpp
#            operating_system/android/buffer.h
#            operating_system/android/dir_context.cpp
#            operating_system/android/dir_context.h
#            operating_system/android/dir_system.cpp
#            operating_system/android/dir_system.h
#            operating_system/android/error.cpp
#            operating_system/android/exception.cpp
#            operating_system/android/_factory.cpp
#            operating_system/android/
#            operating_system/android/file.cpp
#            operating_system/android/file.h
#            operating_system/android/file_context.cpp
#            operating_system/android/file_context.h
#            operating_system/android/file_system.cpp
#            operating_system/android/file_system.h
#            operating_system/android/host_interaction.cpp
#            operating_system/android/host_interaction.h
#            operating_system/android/implementation.h
#            operating_system/android/interaction_impl.cpp
#            operating_system/android/interaction_impl.h
#            operating_system/android/internal.h
#            operating_system/android/main.cpp
#            operating_system/android/os_context.cpp
#            operating_system/android/os_context.h
#            #      operating_system/android/process.cpp
#            operating_system/android/thread.cpp
#            operating_system/android/thread.h
#            operating_system/android/trace.cpp
#            operating_system/android/util.cpp
#            operating_system/android/_.h
#            operating_system/android/_android.h
#            operating_system/android/_bind_app.cpp
#            operating_system/android/_bind_impact.cpp
#            operating_system/android/_c.h
#            operating_system/android/_os_android.cpp
#            operating_system/android/_os_impl.cpp
#            operating_system/android/_os_impl.h
#            operating_system/android/_os_local.h
#            operating_system/android/_os_object.cpp
#            operating_system/android/_os_object.h
#            operating_system/android/_os_remote.h
#            operating_system/android/application_system_run.cpp
#            operating_system/android/aura.cpp
#            operating_system/android/c.cpp
#            operating_system/android/cairo_keep.h
#            operating_system/android/cross_win_file.h
#            operating_system/android/cross_win_gdi.h
#            operating_system/android/cross_win_gdi_internal.h
#            operating_system/android/debug.cpp
#            operating_system/android/dir.cpp
#            operating_system/android/exception_engine.cpp
#            operating_system/android/exception_engine.h
#            operating_system/android/file.cpp
#            operating_system/android/file.h
#            operating_system/android/graphics.cpp
#            operating_system/android/graphics.h
#            operating_system/android/internal.h
#            operating_system/android/jni_launcher.cpp
#            operating_system/android/language.cpp
#            operating_system/android/launcher.cpp
#            operating_system/android/library.cpp
#            operating_system/android/locale.cpp
#            operating_system/android/lock.cpp
#            operating_system/android/main_android.cpp
#            operating_system/android/message_loop.cpp
#            operating_system/android/multithreading.cpp
#            #      operating_system/android/process.cpp
#            #      operating_system/android/process.h
#            #      operating_system/android/process_pid.cpp
#            operating_system/android/impact_bitmap.h
#            operating_system/android/win_base.cpp
#            operating_system/android/window_android.cpp
#            operating_system/android/window_android.h
#            operating_system/android/window_impl.cpp
#            operating_system/android/windowing.cpp
#            operating_system/android/windowing.h
#            )
#
#endif ()
#
#if (APPLE)
#
#    list(APPEND library_source
#            timer.mm
#            operating_system/apple/apple_timer.cpp
#            #      operating_system/apple/process.cpp
#            #      operating_system/apple/process.h
#            operating_system/apple/_.cpp
#            operating_system/apple/_.h
#            operating_system/apple/_apple.h
#            operating_system/apple/_apple.mm
#            operating_system/apple/_c_mm.h
#            operating_system/apple/_mm.h
#            operating_system/apple/_mm_common.h
#            operating_system/apple/debug.cpp
#            operating_system/apple/debug.h
#            operating_system/apple/exe_path.cpp
#            operating_system/apple/graphics.cpp
#            operating_system/apple/graphics.h
#            operating_system/apple/image_gif.cpp
#            operating_system/apple/main.cpp
#            operating_system/apple/main.h
#            operating_system/apple/multihreading.cpp
#            operating_system/apple/ns_exception.cpp
#            operating_system/apple/ns_exception.h
#            #      operating_system/apple/process.cpp
#            operating_system/apple/time.h
#            operating_system/apple/windowing.cpp
#            operating_system/apple/windowing.h
#            )
#
#endif ()


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


list(APPEND library_references
        acme
        apex
        aqua)



list(APPEND static_library_references ${library_references})
list(TRANSFORM static_library_references PREPEND static_)





add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)


set_target_properties(aura PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(aura PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(aura PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(aura PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/aura.lib")
    target_link_options(aura PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/aura.def")
    target_link_libraries(aura PRIVATE acme apex aqua zlib libcrypto libssl dwrite d2d1 d3d11 dxgi Dxva2 dbghelp imagehlp dwmapi Setupapi Windowscodecs Winmm ws2_32 Crypt32 Normaliz version Secur32 gdiplus Shlwapi Imm32)
elseif (LINUX OR FREEBSD)


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(aura PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(aura PRIVATE dl pthread)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message("PKGCONFIG_CFLAGS is " ${PKGCONFIG_CFLAGS})
    message(STATUS "PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(aura PRIVATE _AURA_LIBRARY)



