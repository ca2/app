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
        graphics/draw2d/color_filter.cpp
        graphics/draw2d/color_filter.h
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
        #graphics/draw2d/matrix.cpp
        #graphics/draw2d/matrix.h
        graphics/draw2d/nano_svg.cpp
        graphics/draw2d/nano_svg_rasterization.cpp
        graphics/draw2d/object.cpp
        graphics/draw2d/object.h
        graphics/draw2d/palette.cpp
        graphics/draw2d/palette.h
        graphics/draw2d/path.cpp
        graphics/draw2d/path.h
        graphics/draw2d/path_optimization.cpp
        graphics/draw2d/path_optimization.h
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
        #   graphics/gpu/_.h
        #   graphics/gpu/approach.cpp
        #   graphics/gpu/approach.h
        #   graphics/gpu/cpu_buffer.cpp
        #   graphics/gpu/cpu_buffer.h
        #   graphics/gpu/context.cpp
        #   graphics/gpu/context.h
        #   graphics/gpu/object.cpp
        #   graphics/gpu/object.h
        #   graphics/gpu/program.cpp
        #   graphics/gpu/program.h
        #   graphics/gpu/render.cpp
        #   graphics/gpu/render.h
        #   graphics/gpu/shader.cpp
        #   graphics/gpu/shader.h
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
        #graphics/graphics/output_purpose.cpp
        #graphics/graphics/output_purpose.h
        graphics/graphics/target.cpp
        graphics/graphics/target.h
        graphics/graphics/window.h
        graphics/graphics/window_buffer.h
        graphics/graphics/window_dc.h
        #graphics/image/_image.h
        graphics/image/_.cpp
        graphics/image/_image_impl.h
        graphics/image/context.cpp
        graphics/image/context.h
        graphics/image/cursor.cpp
        graphics/image/cursor.h
        graphics/image/icon.cpp
        graphics/image/icon.h
        graphics/image/image.cpp
        graphics/image/image.h
        graphics/image/array.cpp
        graphics/image/array.h
        graphics/image/buffer.cpp
        graphics/image/buffer.h
        graphics/image/drawer.cpp
        graphics/image/drawer.h
        graphics/image/drawing.cpp
        graphics/image/drawing.h
        graphics/image/dynamic.cpp
        graphics/image/dynamic.h
        graphics/image/encoding_options.cpp
        graphics/image/encoding_options.h
        graphics/image/load_gif_frame.cpp
        graphics/image/load_image.cpp
        graphics/image/load_image.h
        graphics/image/load_options.h
        graphics/image/_constant.h
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
        #graphics/image/header.h
        graphics/image/list.cpp
        graphics/image/list.h
        graphics/image/load_gif_frame.cpp
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
        graphics/image/target.cpp
        graphics/image/target.h
        graphics/image/imaging.cpp
        graphics/image/imaging.h
        #graphics/image/pixmap.h
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
        graphics/write_text/font_family.cpp
        graphics/write_text/font_family.h
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
        graphics/write_text/internal_font.cpp
        graphics/write_text/internal_font.h
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
        hardware/device_group.cpp
        hardware/device_group.h
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
        platform/component.cpp
        platform/component.h
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
        user/menu/track_popup.cpp
        user/menu/track_popup.h
        #user/menu/shared.cpp
        #user/menu/shared.h
        #user/menu/shared_commnand.cpp
        #user/menu/shared_command.h
        #user/micro/message_box.cpp
        #user/micro/message_box.h
        user/user/_.cpp
        user/user/_.h
        user/user/_string.h
        user/user/_text_stream.h
        user/user/_string.cpp
        #user/_const-.h
        user/user/_constant.h
        user/user/_data.h
        user/user/_experience_const.h
        user/user/_impl.h
        user/user/_interaction_impl.h
        user/user/_prelude.h
        user/user/_string.cpp
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
        user/user/form_handler.cpp
        user/user/form_handler.h
        user/user/frame_interaction.cpp
        user/user/frame_interaction.h
        user/user/interaction.cpp
        user/user/interaction.h
        user/user/interaction_array.cpp
        user/user/interaction_array.h
        #user/user/window_util.h
        #user/user/interaction_child.cpp
        #user/user/interaction_child.h
        #use/user//interaction_draw2d.h
        #user/user/interaction_impl.cpp
        #user/user/interaction_impl.h
        user/user/interaction_layout.cpp
        user/user/interaction_layout.h
        user/user/interaction_listener.cpp
        user/user/interaction_listener.h
        user/user/interaction_graphics_thread.cpp
        user/user/interaction_graphics_thread.h
        user/user/interaction_thread.cpp
        user/user/interaction_thread.h
        user/user/interaction_scaler.cpp
        user/user/interaction_scaler.h
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
        #user/user/primitive_impl.cpp
        #user/user/primitive_impl.h
        user/user/progress.cpp
        user/user/progress.h
        user/user/range.cpp
        user/user/range.h
        user/user/redraw.cpp
        user/user/redraw.h
        user/user/scroll.cpp
        user/user/scroll.h
        user/user/scroll_bar.cpp
        user/user/scroll_bar.h
        user/user/scroll_base.cpp
        user/user/scroll_state.h
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
        user/user/user_aura.cpp
        user/user/user_aura.h
        user/user/user_axis.cpp
        user/user/user_axis.h
        user/user/user_base.cpp
        user/user/user_base.h
        user/user/user_bred.cpp
        user/user/user_bred.h
        user/user/user_core.cpp
        user/user/user_core.h
        user/user/wait_cursor.cpp
        user/user/wait_cursor.h
        #user/user/window_map.cpp
        #user/user/window_map.h
        user/user/windowing.cpp
        user/user/windowing.h
        user/user/zorder.cpp
        user/user/zorder.h
        user/user/scroll_base_x.cpp
        user/user/scroll_base_x.h
        user/user/scroll_base_y.cpp
        user/user/scroll_base_y.h
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
        windowing/placement_log.cpp
        windowing/placement_log.h
        windowing/text_editor_interface.cpp
        windowing/text_editor_interface.h
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
if (${ANDROID})
    list(APPEND library_source
            windowing/sandbox/host_interaction.cpp
            windowing/sandbox/host_interaction.h
            windowing/sandbox/window.h
            windowing/sandbox/window.cpp
            windowing/sandbox/windowing.h
            windowing/sandbox/windowing.cpp
    )
endif()
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


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(aura PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(aura PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(aura PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(aura PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/aura.lib")
    target_link_options(aura PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/aura.def")
    target_link_libraries(aura PRIVATE acme apex aqua zlib libcrypto libssl dwrite d2d1 d3d11 dxgi Dxva2 dbghelp imagehlp dwmapi Setupapi Windowscodecs Winmm ws2_32 Crypt32 Normaliz version Secur32 gdiplus Shlwapi Imm32)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
    #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})

    if(${ANDROID})
        target_link_libraries(aura PRIVATE ${system_dl_references})
    else()
        target_link_libraries(aura PRIVATE ${system_dl_references} pthread)
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message("PKGCONFIG_CFLAGS is " ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    message(STATUS "(7) PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



