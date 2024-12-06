cmake_minimum_required(VERSION 3.16)
project(acme CXX)


list(APPEND library_source
   #compress/zip/api.cpp
   #compress/zip/file.cpp
   #compress/zip/in_file.cpp
   #compress/zip/ioapi.cpp
   #compress/zip/memory_buffer.cpp
   #compress/zip/unzip.cpp
   #compress/zip/zip.cpp
   #exception/archive.cpp
   #exception/archive_exception.cpp
   #exception/base.cpp
   #exception/engine.cpp
   #exception/exit.cpp
   #exception/hresult.cpp
   #exception/index_out_of_bounds.cpp
   #exception/installing.cpp
   #exception/invalid_argument.cpp
   #exception/invalid_character.cpp
   #exception/invalid_handle.cpp
   #exception/invalid_index.cpp
   #exception/not_installed.cpp
   #exception/not_licensed.cpp
   #exception/not_supported.cpp
   #exception/operation_canceled.cpp
   #exception/os.cpp
   #exception/overflow.cpp
   #exception/range.cpp
   #exception/result.cpp
   #exception/runtime.cpp
   #exception/simple.cpp
   #exception/standard_translator.cpp
   #exception/temporary.cpp
   #exception/todo.cpp
   #exception/user.cpp
   #exception/void_implementation.cpp
   #exception/wtf.cpp
   #filesystem/file/_.cpp
   #filesystem/file/dir.cpp
   #filesystem/file/stdio_file.cpp
   #memory/heap.cpp
   #memory/plex.cpp
   #memory/plex_heap.cpp
   #operating_system/ansi/win.cpp
   #parallelization/file_change_event.cpp
   #platform/regex.cpp
   #platform/simple_trace.cpp
   #platform/sprintf.cpp
   #platform/update.cpp
   #prototype/prototype/application_bias.h
   #prototype/prototype/block.inl
   #prototype/prototype/collection.h
   #prototype/prototype/command.h
   #prototype/prototype/edit.h
   #prototype/prototype/layered.h
   #prototype/prototype/prototype_update.h
   #prototype/prototype/request_signal.h
   #prototype/promise/_.h
   #prototype/promise/context.cpp
   #prototype/promise/context.h
   #prototype/promise/handler1.cpp
   #prototype/promise/handler1.h
   #prototype/promise/manager.cpp
   #prototype/promise/manager.h
   #prototype/promise/process.cpp
   #prototype/promise/promise.cpp
   #prototype/promise/promise.h
   #prototype/promise/promise1.h
   #prototype/promise/routine.cpp
   #prototype/promise/routine.h
   #prototype/promise/routine_array.cpp
   #prototype/promise/routine_array.h
   #prototype/promise/subject.cpp
   #prototype/promise/subject.h
   #prototype/promise_predicate/predicate_function.cpp
   #prototype/promise_predicate/predicate_function.cpp
   #prototype/promise_predicate/predicate_function_pointer.h
   #prototype/promise_predicate/predicate_holdercpp.cpp
   #prototype/promise_predicate/predicate_holder.h
   #prototype/promise_predicate/predicate_process.h
   #prototype/promise_predicate/synchronized_predicate_routine.h
   #process/_.cpp
   _.cpp
   #__matter_ca2.cpp
   compress/_.h
   compress/compress.cpp
   compress/compress.h
   compress/uncompress.cpp
   compress/uncompress.h
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
   constant/_.h
   constant/code_page.h
   constant/earth.h
   constant/element.h
   #constant/idpool.cpp
   constant/library.h
   constant/message_box.h
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
   #context_glx.cpp
   #exception/callstack.cpp
   exception/assert.cpp
   exception/cancel.cpp
   #exception/const.cpp
   exception/debug.cpp
   #exception/dump.cpp
   exception/dump_context.cpp
   exception/dump_floating_point.cpp
   #exception/dump_output.cpp
   exception/exception.cpp
   exception/extended_status.cpp
   exception/extended_status.h
   exception/extended_transport.h
   #exception/file.cpp
   #exception/file.h
   #exception/file_open.cpp
   #exception/file_open.h
   exception/interface_only.cpp
   exception/io.cpp
   exception/library_not_loaded.cpp
   exception/library_not_loaded.h
   exception/no_memory.cpp
   exception/no_memory.h
   exception/not_implemented.cpp
   exception/parsing.cpp
   exception/resource.cpp
   exception/serialization.cpp
   exception/serialization.h
   #exception/throw.cpp
   exception/translator.cpp
   exception/translator.h
   filesystem/file/binary_stream.cpp
   filesystem/file/buffered_buffer.cpp
   #filesystem/file/c.cpp
   filesystem/file/circular_buffer.cpp
   filesystem/file/composite.cpp
   filesystem/file/cpp.cpp
   #filesystem/file/dir2.cpp
   filesystem/file/exception.cpp
   filesystem/file/exception.h
   filesystem/file/file.cpp
   filesystem/file/folder.cpp
   filesystem/file/folder.h
   filesystem/file/item.cpp
   filesystem/file/item_array.cpp
   filesystem/file/memory_file.cpp
   filesystem/file/memory_map.cpp
   #filesystem/file/path.cpp
   filesystem/file/payload_stream.cpp
   filesystem/file/print_formatting.cpp
   filesystem/file/print_formatting.h
   #filesystem/file/seekable.cpp
   #filesystem/file/serializable.cpp
   #filesystem/file/serialize.cpp
   filesystem/file/stream.cpp
   filesystem/file/streamable.cpp
   filesystem/file/streamable.h
   filesystem/file/streamable_composite.cpp
   filesystem/file/streamable_composite.h
   filesystem/file/string_buffer.cpp
   filesystem/file/string_buffer.h #3 ***----
   filesystem/file/string_stream.cpp
   filesystem/file/string_stream.h
   filesystem/file/text_file.cpp
   filesystem/file/text_stream.cpp
   filesystem/file/transfer.cpp
   filesystem/file/transfer.h
   filesystem/file/translatable.cpp
   filesystem/file/translatable.h
   filesystem/file/write_text_stream.cpp
   filesystem/file/write_text_stream.h
   filesystem/filesystem/_.h
   filesystem/filesystem/_2.h
   filesystem/filesystem/_impl.h
   filesystem/filesystem/_impl2.h
   filesystem/filesystem/directory_context.cpp
   filesystem/filesystem/directory_context.h
   filesystem/filesystem/directory_system.cpp
   filesystem/filesystem/directory_system.h
   filesystem/filesystem/dir_system_heap.h
   filesystem/filesystem/file_context.cpp
   filesystem/filesystem/file_context.h
   filesystem/filesystem/file_context_interface.cpp
   filesystem/filesystem/file_context_interface.h
   filesystem/filesystem/file_system_options.cpp
   filesystem/filesystem/file_system_options.h
   filesystem/filesystem/file_system.cpp
   filesystem/filesystem/file_system.h
   filesystem/filesystem/link.cpp
   filesystem/filesystem/link.h
   filesystem/filesystem/file_dialog.cpp
   filesystem/filesystem/file_dialog.h
   filesystem/filesystem/file_path.cpp
   filesystem/filesystem/file_path.h
   filesystem/filesystem/folder_dialog.cpp
   filesystem/filesystem/folder_dialog.h
   filesystem/filesystem/link.cpp
   filesystem/filesystem/link.h
   filesystem/filesystem/listing.cpp
   filesystem/filesystem/path.cpp
   filesystem/filesystem/path_object.cpp
   filesystem/filesystem/path_system.cpp
   filesystem/filesystem/path_system.h
   filesystem/watcher/action.cpp
   filesystem/watcher/action.h
   filesystem/watcher/listener.h
   filesystem/watcher/watch.cpp
   filesystem/watcher/watch.h
   filesystem/watcher/watcher.cpp
   filesystem/watcher/watcher.h
   framework.cpp
   graphics/draw2d/_.cpp
   graphics/draw2d/_system_color.h
   graphics/draw2d/color.cpp
   graphics/draw2d/color32.h
   graphics/draw2d/color_array.cpp
   graphics/draw2d/color_array.h
   graphics/draw2d/os_font_name.cpp
   graphics/graphics/_.h
   graphics/graphics/output_purpose.cpp
   graphics/graphics/output_purpose.h
   graphics/image/image32.cpp
   graphics/image/image32.h
   graphics/image/image32_array.cpp
   graphics/image/image32_array.h
   graphics/image/pixmap.cpp
   handler/extended_topic.cpp
   handler/extended_topic.h
   handler/handler.cpp
   handler/handler.h
   handler/item.cpp
   handler/item.h
   handler/item_container.cpp
   handler/item_container.h
   handler/item_container_map.cpp
   handler/item_container_map.cpp
   handler/topic.cpp
   handler/topic.h
   handler/request.cpp
   handler/request.h
   handler/sequence.cpp
   handler/sequence.h
   handler/source.cpp
   handler/source.h
   #include/_.cpp
   #include/path.h        #prototype/collection/comparable_array.cpp
   #memory/alloc.cpp
   memory/_.cpp
   memory/allocate_processor_cache_oriented.cpp
   #memory/allocate_system_heap.cpp
   memory/allocate_x86_cache_oriented.cpp
   memory/allocation.cpp
   #memory/array_memory_allocate.cpp
   #memory/array_memory_allocate.h
   memory/counter.cpp
   #memory/memory_allocate.cpp
   #memory/memory_allocate.h
   memory/management.cpp
   memory/management.h
   memory/memory.cpp
   memory/memory.h
   memory/memory_allocate.cpp
   memory/memory_allocate.h
   memory/memory_management.cpp
   memory/memory_management.h
   #memory/new.cpp
   memory/operation.cpp
   memory/operation.h
   memory/os_alloc.cpp
   #memory/os_alloc.h
   #memory/os_impl/malloc.cpp
   memory/heap/std.cpp
   memory/allocator/default.cpp
   memory/allocator/malloc.cpp
   memory/paged.h
   memory/paged_large.cpp
   #   memory/property_memory_allocate.cpp
   #   memory/property_memory_allocate.h
   #   memory/secondary_memory_allocate.cpp
   #   memory/secondary_memory_allocate.h
   memory/simple_memory_allocate.cpp
   memory/simple_memory_allocate.h
   #   memory/string_memory_allocate.cpp
   #   memory/string_memory_allocate.h
   #   memory/string_memory_allocator.h
   nano/account/_.h
   nano/account/account.cpp
   nano/account/account.h
   nano/account/id.cpp
   nano/account/id.h
   nano/account/user.cpp
   nano/account/user.h
   nano/archive/_.h
   nano/archive/archive.cpp
   nano/archive/archive.h
   nano/compress/_.h
   nano/compress/compress.cpp
   nano/compress/compress.h
   #nano/dynamic_library/_.h
   #nano/dynamic_library/dynamic_library.cpp
   #nano/dynamic_library/dynamic_library.h
   nano/graphics/brush.cpp
   nano/graphics/brush.h
   nano/graphics/device.cpp
   nano/graphics/device.h
   nano/graphics/device.h
   nano/graphics/font.cpp
   nano/graphics/font.h
   nano/graphics/graphics.cpp
   nano/graphics/graphics.h
   nano/graphics/object.cpp
   nano/graphics/object.h
   nano/graphics/pen.cpp
   nano/graphics/pen.h
   nano/graphics/icon.cpp
   nano/graphics/icon.h

   nano/http/_.h
   nano/http/http.cpp
   nano/http/http.h
   _static_factory.h
   windowing/_.h
   user/micro/
   user/user/element.cpp
   user/user/element.h
   #nano/user/console.cpp
   #nano/user/console.h

   nano/idn/_.h
   nano/idn/idn.cpp
   nano/idn/idn.h
   nano/http/get.cpp
   nano/http/get.h
   nano/shell/_.h
   nano/shell/shell.cpp
   nano/shell/shell.h
   nano/speech/_.h
   nano/speech/speech.cpp
   nano/speech/speech.h
   #        nano/user/_user.cpp
   #        nano/user/_.h
   #        nano/user/button.cpp
   #        nano/user/button.h
   #        nano/user/child.cpp
   #        nano/user/child.h
   #        nano/user/details_window.cpp
   #        nano/user/details_window.h
   #        nano/user/display.cpp
   #        nano/user/display.h
   #        nano/user/message_box.cpp
   #        nano/user/message_box.h
   #        nano/user/user.cpp
   #        nano/user/user.h
   #        nano/user/popup_button.cpp
   #        nano/user/popup_button.h
   #        nano/user/still.cpp
   #        nano/user/still.h
   #        nano/user/interchange.cpp
   #        nano/user/interchange.h
   #        #nano/user/window_implementation.cpp
   #        #nano/user/window_implementation.h
   #        #nano/user/window_interface.cpp
   #        #nano/user/window_interface.h
   nano/nano.cpp
   nano/nano.h
   nano/_.h
   #networking/top_level_domain_list.cpp
   #networking/net.cpp
   #networking/net.h
   #networking/url.cpp
   #networking/url.h
   #networking/url_department.cpp
   #networking/url_department.h
   #networking/url_domain.cpp
   #networking/url_domain.h
   operating_system/_.cpp
   operating_system/_const_console.h
   operating_system/__eoperating_ambient.cpp
   operating_system/__operating_system.cpp
   operating_system/ansi/_pthread.h
   #operating_system/ansi/base.cpp
   operating_system/ansi/call_stack.cpp
   operating_system/ansi/call_stack.h
   operating_system/ansi/datetime.cpp
   operating_system/ansi/file.cpp
   operating_system/ansi/file_raw.cpp
   operating_system/ansi/file_std.cpp
   #operating_system/ansi/language.cpp
   #operating_system/ansi/memory.cpp
   operating_system/ansi/process.cpp
   #operating_system/ansi/user.cpp
   operating_system/application.cpp
   operating_system/application.h

   operating_system/argcargv.cpp
   operating_system/a_system_menu.cpp
   operating_system/a_system_menu.h
   operating_system/chronometer.cpp
   operating_system/console.cpp
   operating_system/console_client.cpp
   operating_system/console_client.h
   operating_system/debug.cpp
   operating_system/dynamic_library.cpp
   operating_system/dynamic_library.h
   operating_system/file.cpp
   #operating_system/http.cpp
   operating_system/main_window.cpp
   operating_system/main_window.h
   operating_system/message.cpp
   operating_system/message.h
   operating_system/message_box.cpp
   operating_system/message_box.h
   operating_system/parallelization.cpp
   operating_system/path.cpp
   operating_system/path.h
   operating_system/process.h
   operating_system/string.cpp
   operating_system/summary.cpp
   operating_system/summary.h
   operating_system/time.cpp
   operating_system/windowing.cpp
   parallelization/_.cpp
   parallelization/condition.cpp
   parallelization/condition.h
   parallelization/condition_variable.cpp
   parallelization/condition_variable.h
   parallelization/create_task_attributes.cpp
   parallelization/create_task_attributes.h
   parallelization/critical_section.cpp
   parallelization/fork.cpp
   parallelization/fork.h
   parallelization/happening.cpp
   parallelization/happening.h
   parallelization/install_mutex.cpp
   parallelization/manual_reset_happening.cpp
   parallelization/manual_reset_happening.h
   parallelization/multiple_lock.cpp
   parallelization/multiple_lock.h
   parallelization/mutex.cpp
   parallelization/pool.cpp
   parallelization/retry.h
   parallelization/semaphore.cpp
   parallelization/signalization.cpp
   parallelization/signalization.h
   parallelization/single_lock.cpp
   parallelization/socket_event.cpp
   parallelization/synchronizer.cpp
   parallelization/synchronizer.h
   parallelization/task.cpp
   parallelization/task_flag.h
   parallelization/task_keep.h
   parallelization/task_message_queue.cpp
   parallelization/task_message_queue.h
   parallelization/task_payload.h
   #parallelization/thread.cpp
   #parallelization/thread_os.cpp
   #parallelization/waitable.cpp
   platform/_.cpp
   platform/_main_hold_base.cpp
   platform/_synchronization.cpp
   platform/_synchronization.h
   platform/acme.cpp
   platform/acme.h
   platform/allocator.cpp
   platform/allocator.h
   #platform/acme_main_struct.cpp
   #platform/acme_main_struct.h
   #platform/apex_main_data.cpp
   #platform/apex_main_data.h
   #platform/apex_main_struct.cpp
   #platform/apex_main_struct.h
   integrate/qt/_.h
   integrate/qt.h
   integrate/qt/geometry2d.h
   integrate/qt/image.h
   operating_system/x11/_x11.h
   operating_system/x11/_x11.h
   platform/system_acme.h
   platform/system_apex.h
   platform/system_aqua.h
   platform/system_aura.h
   platform/application_acme.h
   platform/application_acme.cpp
   platform/application_apex.h
   platform/application_apex.cpp
   platform/application_aqua.h
   platform/application_aqua.cpp
   platform/application_aura.h
   platform/application_aura.cpp
   platform/application_axis.h
   platform/application_axis.cpp
   platform/application_axis.h
   platform/application_axis.cpp
   platform/http.cpp
   platform/http.h
   platform/http_acme.cpp
   platform/http_acme.h
   platform/http_apex.cpp
   platform/http_apex.h
   prototype/prototype/cast.h
   prototype/data/client.h
   prototype/data/client.cpp
   user/menu/_.h
   user/menu/menu.cpp
   user/menu/menu.h
   platform/application_menu.cpp
   platform/application_menu.h
   platform/application_menu_command.cpp
   platform/application_menu_command.h
   platform/application.cpp
   platform/application.h
   platform/application_acme.cpp
   platform/application_acme.h
   platform/application_apex.cpp
   platform/application_apex.h
   platform/application_aqua.cpp
   platform/application_aqua.h
   platform/application_aura.cpp
   platform/application_aura.h
   platform/application_array.cpp
   platform/application_array.h
   platform/application_base.cpp
   platform/application_base.h
   platform/application_bred.cpp
   platform/application_bred.h
   platform/application_core.cpp
   platform/application_core.h
   platform/application_container.cpp
   platform/application_container.h
   platform/application_exit.cpp
   platform/application_exit.h
   #platform/application_flags.cpp
   platform/application_flags.h
   #platform/app_core.cpp
   #platform/app_core.h
   platform/assert.cpp
   #platform/aura_str_pool.cpp
   platform/build_debug.cpp
   platform/checked.cpp
   platform/context.cpp
   platform/context.h
   platform/context_acme.cpp
   platform/context_acme.h
   platform/context_apex.cpp
   platform/context_apex.h
   platform/context_aqua.cpp
   platform/context_aqua.h
   platform/context_aura.cpp
   platform/context_aura.h
   platform/debug.cpp
   platform/department.cpp
   platform/department.h
   platform/display.cpp
   platform/exclusive.cpp
   #platform/factory.cpp
   platform/factory_function.cpp
   platform/factory_function.h
   platform/fixed_alloc.cpp
   platform/flags.cpp
   platform/hyperlink.cpp
   platform/implementable.cpp
   platform/implementable.h
   platform/ini.cpp
   platform/integration_context.cpp
   platform/integration_context.h
   platform/library.cpp
   platform/library.h
   platform/log.cpp
   platform/log.h
   platform/logger.cpp
   platform/logger.h
   #platform/logic.cpp
   platform/lparam.cpp
   platform/application_flags.cpp
   #platform/main.cpp
   #platform/main.h
   platform/math.cpp
   platform/message.h
   platform/message_box.cpp
   platform/message_box.h
   #platform/muldiv64.cpp
   #   platform/nano_http.cpp
   #   platform/nano_http.h
   #   platform/nano_http_response.cpp
   #   platform/nano_http_response.h
   platform/nanosecond_timer.cpp
   platform/nanosecond_timer.h
   platform/node.cpp
   platform/node.h
   platform/node_acme.cpp
   platform/node_acme.h
   platform/node_apex.cpp
   platform/node_apex.h
   platform/node_aqua.cpp
   platform/node_aqua.h
   platform/node_aura.cpp
   platform/node_aura.h
   platform/predicate_holder.cpp
   platform/predicate_holder.h
   platform/printf.cpp
   platform/profiler.cpp
   platform/procedure.cpp
   platform/procedure.h
   platform/serial.cpp
   platform/session.cpp
   platform/session.h
   platform/session_acme.cpp
   platform/session_acme.h
   platform/session_apex.cpp
   platform/session_apex.h
   platform/session_aqua.cpp
   platform/session_aqua.h
   platform/session_aura.cpp
   platform/session_aura.h
   platform/session_axis.cpp
   platform/session_axis.h
   platform/platform.cpp
   platform/platform.h
   platform/shell.cpp
   platform/shell.h
   platform/reference_item.cpp
   platform/reference_item.h
   platform/reference_item_array.cpp
   platform/reference_item_array.h
   platform/reference_referer.cpp
   platform/reference_referer.h
   platform/referencing_debugging.cpp
   platform/referencing_debugging.h
   platform/system.cpp
   platform/system_acme.cpp
   platform/system_acme.h
   platform/system_apex.cpp
   platform/system_apex.h
   platform/system_aqua.cpp
   platform/system_aqua.h
   platform/system_aura.cpp
   platform/system_aura.h
   platform/system_axis.cpp
   platform/system_axis.h
   platform/system_core.cpp
   platform/system_core.h
   platform/system_factory.cpp
   platform/system_factory.h
   platform/system_setup.cpp
   platform/system_setup.h
   platform/text.cpp
   platform/timer.cpp
   platform/timer_array.cpp
   platform/timer_callback.cpp
   platform/timer_event.cpp
   #platform/timer_item.cpp
   platform/timer_task.cpp
   platform/trace.cpp
   platform/trace.h
   platform/tracer.cpp
   platform/tracer.h
   platform/trace_category.cpp
   platform/url_context.cpp
   platform/url_context.h
   platform/version.cpp
   prototype/collection/__payload_array.cpp
   prototype/collection/_generic_array.h

   #prototype/collection/2d_array.cpp
   prototype/collection/array.cpp
   prototype/collection/atom_array.h
   prototype/collection/atom_map.h
   prototype/collection/bit_array.cpp
   #prototype/collection/class_sort_array.cpp
   prototype/collection/collection.h
   #prototype/collection/event_map.cpp
   #prototype/collection/id_array.cpp
   #prototype/collection/key_sort_array.cpp
   #prototype/collection/map_misc.cpp
   prototype/collection/map_test_51778915.cpp
   #prototype/collection/numeric_array.cpp
   #prototype/collection/point_array.cpp
   prototype/collection/procedure_array.cpp
   prototype/collection/procedure_array.h
   prototype/collection/property_set.h
   #prototype/collection/rectangle_array.cpp
   prototype/collection/sort.cpp
   prototype/collection/str_array.cpp
   prototype/collection/string_array.cpp
   #prototype/collection/string_array_base.cpp
   #prototype/collection/string_list.cpp
   #prototype/collection/string_list.cpp
   #prototype/collection/string_to_string_map.cpp
   prototype/collection/string_list.cpp
   prototype/collection/string_list.h
   prototype/comparison/array.h
   prototype/comparison/var_strict.cpp
   prototype/data/_.h
   #prototype/data/_data.h
   prototype/data/_impl.h
   prototype/data/_tree.h
   prototype/data/check_property.cpp
   prototype/data/check_property.h
   prototype/data/container.cpp
   prototype/data/container.h
   prototype/data/data.cpp
   prototype/data/data.h
   prototype/data/item.cpp
   prototype/data/item.h
   prototype/data/listener.cpp
   prototype/data/listener.h
   prototype/data/node.cpp
   prototype/data/node.h
   prototype/data/property.cpp
   prototype/data/property.h
   prototype/data/property_container.cpp
   prototype/data/property_container.h
   prototype/data/property_listener.cpp
   prototype/data/property_listener.h
   prototype/data/simple_item.cpp
   prototype/data/simple_item.h
   prototype/data/tree.cpp
   prototype/data/text_property.cpp
   prototype/data/text_property.h
   prototype/data/tree.h
   prototype/data/tree_item.cpp
   prototype/data/tree_item.h
   #prototype/datetime/_.cpp
   prototype/datetime/_.h
   #prototype/datetime/_c.cpp
   prototype/datetime/_c.h
   prototype/datetime/_impl.h
   prototype/datetime/date_span.cpp
   prototype/datetime/date_span.h
   prototype/datetime/datetime.cpp
   prototype/datetime/datetime.h
   prototype/datetime/earth_gregorian_time.cpp
   prototype/datetime/earth_gregorian_time.h
   prototype/datetime/earth_time_shift.h
   prototype/datetime/earth_time.cpp
   prototype/datetime/earth_time.h
   prototype/datetime/earth_time_span.cpp
   prototype/datetime/earth_time_span.h
   prototype/datetime/earth_zone_time.cpp
   prototype/datetime/earth_zone_time.h
   prototype/datetime/file_time.cpp
   prototype/datetime/file_time.h
   prototype/datetime/file_time_span.cpp
   prototype/datetime/file_time_span.h
   prototype/datetime/microsecond_sleep.cpp
   prototype/datetime/microsecond_sleep.h
   prototype/datetime/mktime.cpp
   prototype/datetime/result.cpp
   prototype/datetime/result.h
   prototype/datetime/system_time.cpp
   prototype/geometry/sequence.h
   prototype/geometry2d/_.cpp
   prototype/geometry2d/_.h
   prototype/geometry2d/_collection.h
   #prototype/geometry2d/_collection_bounding_rect.h
   #prototype/geometry2d/_collection_contains.h
   #prototype/geometry2d/_collection_enhanced.h
   #prototype/geometry2d/_concept.h
   #prototype/geometry2d/_enhanced.h
   prototype/geometry2d/_defer.h
   #prototype/geometry2d/_geometry2d.h
   #prototype/geometry2d/_impl.h
   #prototype/geometry2d/_rect_impl.h
   #prototype/geometry2d/_shape.cpp
   #prototype/geometry2d/_shape.h
   #prototype/geometry2d/_size_impl.h
   prototype/geometry2d/_struct.h
   prototype/geometry2d/_text_stream.h
   #prototype/geometry2d/align.h
   prototype/geometry2d/angle.h
   prototype/geometry2d/arc.h
   #prototype/geometry2d/bounding_rect.h
   prototype/geometry2d/collection.h
   prototype/geometry2d/contains.h
   prototype/geometry2d/ellipse.h
   prototype/geometry2d/geometry.cpp
   prototype/geometry2d/geometry.h
   prototype/geometry2d/item.cpp
   prototype/geometry2d/item.h
   prototype/geometry2d/line.h
   prototype/geometry2d/lines.h
   #prototype/geometry2d/point.cpp
   prototype/geometry2d/matrix.cpp
   prototype/geometry2d/matrix.h
   prototype/geometry2d/point.h
   prototype/geometry2d/point_array.h
   prototype/geometry2d/polygon.h
   prototype/geometry2d/rectangle.cpp
   prototype/geometry2d/rectangle.h
   prototype/geometry2d/rectangle_array.cpp
   prototype/geometry2d/rectangle_array.h
   prototype/geometry2d/region.cpp
   prototype/geometry2d/region.h
   #prototype/geometry2d/shape.cpp
   #prototype/geometry2d/shape.h
   #prototype/geometry2d/shape_array.h
   #prototype/geometry2d/size.cpp
   prototype/geometry2d/size.h
   prototype/geometry2d/size_array.h
   #prototype/geometry2d/types.cpp
   prototype/geometry2d/types.h
   prototype/geometry3d/_.h
   prototype/geometry3d/box.cpp
   prototype/geometry3d/box.h
   prototype/geometry3d/dimension.h
   prototype/geometry3d/location.cpp
   prototype/geometry3d/location.h
   prototype/geometry3d/quaternions.h
   prototype/geometry4d/color.h
   prototype/geometry4d/quadruple.h
   prototype/mathematics/_.cpp
   prototype/mathematics/_.h
   prototype/mathematics/_impl.h
   #prototype/mathematics/_types.h
   prototype/mathematics/binary_operation.cpp
   prototype/mathematics/binary_operation.h
   prototype/mathematics/c_number.h
   prototype/mathematics/cast.h
   prototype/mathematics/cast.inl
   prototype/mathematics/classes.h
   prototype/mathematics/clip.h
   prototype/mathematics/complex.h
   prototype/mathematics/cvt.cpp
   prototype/mathematics/cvt_g.cpp
   prototype/mathematics/filestream.h
   #prototype/mathematics/index.h
   prototype/mathematics/int_biunique.cpp
   prototype/mathematics/int_biunique.h
   prototype/mathematics/mathematics.cpp
   prototype/mathematics/mathematics.h
   prototype/mathematics/mkint_c.cpp
   prototype/mathematics/mkint_c.h
   prototype/mathematics/natural.cpp
   prototype/mathematics/natural.h
   prototype/mathematics/number.cpp
   prototype/mathematics/number.h
   prototype/mathematics/number_double.cpp
   prototype/mathematics/number_double.h
   prototype/mathematics/number_float.cpp
   prototype/mathematics/number_float.h
   prototype/mathematics/number_integer.cpp
   prototype/mathematics/number_integer.h
   prototype/mathematics/numeric_info.h
   prototype/mathematics/numeric.h
   prototype/mathematics/objects.h
   prototype/mathematics/random_number_generator.cpp
   prototype/mathematics/random_number_generator.h
   prototype/mathematics/scalar.cpp
   prototype/mathematics/scalar.h
   #prototype/mathematics/scalar_enum.h
   prototype/mathematics/static_numeric_info.h
   prototype/mathematics/std_template.h
   prototype/mathematics/value.cpp
   prototype/mathematics/value.h
   prototype/media_library/item.cpp
   prototype/media_library/item.h
   #prototype/prototype/__particle_factory.h
   prototype/prototype/_.cpp
   prototype/prototype/_.h
   #prototype/prototype/_atom_impl.h
   #prototype/prototype/_c_memory.h
   prototype/prototype/_defer.h
   #prototype/prototype/_factory_impl.h
   #prototype/prototype/_factory_prefix.h
   prototype/prototype/_impl.h
   prototype/prototype/_impl_atom.h
   #prototype/prototype/_memory.h
   prototype/prototype/_papaya.h
   prototype/prototype/_papaya_impl.h
   #prototype/prototype/_payload_impl.h
   prototype/prototype/_property_object_impl.h
   prototype/prototype/action_context.cpp
   prototype/prototype/action_context.h
   #prototype/prototype/application_bias.cpp
   prototype/prototype/atom.cpp
   prototype/prototype/atom.h
   #prototype/prototype/atom_space.cpp
   #prototype/prototype/atom_space.h
   prototype/prototype/atomic.h
   prototype/prototype/bit.cpp
   prototype/prototype/bit.h
   prototype/prototype/block.cpp
   prototype/prototype/block.h
   prototype/prototype/collection_file.h
   #prototype/prototype/command.cpp
   prototype/prototype/compare_predicate.h
   #prototype/prototype/context_object_traits.cpp
   prototype/prototype/domain_enumeration.h
   #prototype/prototype/edit.cpp
   #prototype/prototype/element.cpp
   #prototype/prototype/element.cpp
   #prototype/prototype/element.h
   #prototype/prototype/element.h
   #prototype/prototype/element_array.cpp
   #prototype/prototype/element_array.h
   #prototype/prototype/element_array.h
   prototype/prototype/enum_bitset.h
   prototype/prototype/enumeration.h
   prototype/prototype/enumeration.h
   prototype/prototype/enumeration.h
   #prototype/prototype/eobject.h
   prototype/prototype/e_status.cpp
   prototype/prototype/e_status.h
   prototype/prototype/factory.cpp
   prototype/prototype/factory.h
   prototype/prototype/get_memory.cpp
   prototype/prototype/get_memory.h
   #prototype/prototype/handler.cpp
   #prototype/prototype/id_array.cpp
   prototype/prototype/integral_byte.cpp
   #prototype/prototype/interlocked.h
   prototype/prototype/interlocked_count.h
   #prototype/prototype/interlocked_long_pulse.cpp
   #prototype/prototype/interlocked_long_pulse.h
   #prototype/prototype/linked_property.cpp
   #prototype/prototype/linked_property.h
   prototype/prototype/logic.h
   prototype/prototype/malloc.h
   prototype/prototype/map.h
   prototype/prototype/match.cpp
   prototype/prototype/match.h
   #prototype/prototype/material_object.cpp
   #prototype/prototype/material_object.cpp
   #prototype/prototype/material_object.h
   #prototype/prototype/material_object.h
   prototype/prototype/matter.cpp
   prototype/prototype/matter.h
   #prototype/prototype/member.h
   prototype/prototype/memory.cpp
   prototype/prototype/memory.h
   prototype/prototype/memory_base.cpp
   prototype/prototype/memory_base.h
   #prototype/prototype/memory_c.cpp
   prototype/prototype/memory_container.cpp
   prototype/prototype/memory_container.h
   #prototype/prototype/natural.h
   prototype/prototype/number.h
   prototype/prototype/object.cpp
   prototype/prototype/object.h
   prototype/prototype/object_meta.cpp
   prototype/prototype/object_meta.h
   #prototype/prototype/papaya.h
   prototype/prototype/particle.cpp
   prototype/prototype/particle.h
   #prototype/prototype/particle_flags.h
   prototype/prototype/payload.cpp
   prototype/prototype/payload.h
   prototype/prototype/payload2.h
   prototype/prototype/pointer.h
   prototype/prototype/pointer2.h
   prototype/prototype/prototype.cpp
   prototype/prototype/prototype.h
   prototype/prototype/property.cpp
   prototype/prototype/property.h
   prototype/prototype/property_object.cpp
   prototype/prototype/property_object.cpp
   prototype/prototype/property_object.h
   prototype/prototype/property_object.h
   prototype/prototype/property_set.cpp
   #prototype/prototype/property_set_composite.cpp
   #prototype/prototype/property_set_papaya.cpp
   prototype/prototype/property_set_papaya.h
   prototype/prototype/quantum.cpp
   prototype/prototype/quantum.h
   prototype/prototype/read_only_memory.cpp
   prototype/prototype/read_only_memory.h
   prototype/prototype/request_interface.h
   #prototype/prototype/runnable.cpp
   #prototype/prototype/runnable.h
   prototype/prototype/scope_stack.h
   prototype/prototype/sequence_continuation.cpp
   #prototype/prototype/shared_memory.cpp
   #prototype/prototype/shared_memory.h
   #prototype/prototype/simple_object.h
   prototype/prototype/stick.h
   #prototype/prototype/str.h
   prototype/prototype/subparticle.cpp
   prototype/prototype/subparticle.h
   prototype/prototype/subparticle_flags.cpp
   prototype/prototype/subparticle_flags.h
   #prototype/prototype/top_level_domain_list.cpp
   #prototype/prototype/tracer.cpp
   #prototype/prototype/tracer.h
   #prototype/prototype/trait.h
   #prototype/prototype/trait_predicate.h
   #prototype/prototype/traits.cpp
   #prototype/prototype/traits.h
   prototype/prototype/type.cpp
   prototype/prototype/type.h
   prototype/prototype/uid.h
   prototype/prototype/url.cpp
   prototype/prototype/url.h
   prototype/prototype/url_domain.cpp
   prototype/prototype/url_domain.h
   prototype/prototype/util.h
   prototype/prototype/value.h
   prototype/prototype/var_element.cpp
   #prototype/prototype/virtual_memory.cpp
   #prototype/prototype/virtual_memory.h
   prototype/prototype/work.cpp
   prototype/prototype/work.h
   #prototype/promise/signalization.cpp
   #prototype/promise/signalization.h
   prototype/string/_.cpp
   #prototype/string/_.h
   #prototype/string/_.h
   prototype/string/_impl_string_base.h
   prototype/string/_impl_string_meta_data.h
   #prototype/string/c/extension/_impl.h
   prototype/string/c/encoding.h
   prototype/string/c/ancient/ansi.h
   prototype/string/c/coupling.h
   prototype/string/c/extension/wd32.h
   #prototype/string/c/ancient/_impl.h
   prototype/string/c/extension/_.h
   prototype/string/c/_.h
   prototype/string/c/strdup.cpp
   prototype/string/c/strdup.h
   prototype/string/c/extension/ansi_impl.cpp
   prototype/string/c/extension/ansi.h
   prototype/string/c/extension/wd32_impl.cpp
   prototype/string/c/extension/wd16_impl.cpp
   prototype/string/c/ancient/wd32.h
   prototype/string/c/unicode.h
   prototype/string/c/encoding_impl.h
   prototype/string/c/_impl.h
   prototype/string/c/ancient/_.h
   prototype/string/c/ancient/_c.cpp
   prototype/string/c/coupling_impl.cpp
   prototype/string/c/extension/wd16.h
   prototype/string/c/ancient/wd16.h
   prototype/string/c/unicode_impl.cpp
   prototype/string/c/ancient/ansi_impl.cpp
   prototype/string/c/ancient/wd16_impl.cpp
   prototype/string/c/ancient/wd32_impl.cpp
   prototype/string/sz/_.h
   prototype/string/sz/wd32.cpp
   prototype/string/sz/ansi.cpp
   prototype/string/sz/wd32_impl.cpp
   prototype/string/sz/ansi.h
   prototype/string/sz/wd32.h
   prototype/string/sz/wd16_impl.cpp
   prototype/string/sz/wd16.cpp
   prototype/string/sz/wd16.h
   prototype/string/sz/ansi_impl.cpp
   #prototype/string/sz/_impl.h
   #prototype/string/__c_wd32_impl.h
   #prototype/string/__c_wide.h
   #prototype/string/__c_wide_impl.h
   #prototype/string/_base.h
   #prototype/string/_base.h
   #prototype/string/_base_impl.h
   #prototype/string/_base_impl.h
   #prototype/string/_c.cpp
   #prototype/string/_c.h
   #prototype/string/_c_impl.h
   #prototype/string/_c_inline.h
   #prototype/string/_c_str.h
   #prototype/string/_c_str_impl.h
   #prototype/string/_c_trait.h
   prototype/string/_c_trait_ansi.cpp
   #prototype/string/_c_trait_ansi.h
   #prototype/string/_c_trait_ansi_impl.h
   #prototype/string/_c_trait_impl.h
   #prototype/string/_c_trait_wd16.h
   #prototype/string/_c_trait_wd16_impl.h
   #prototype/string/_c_trait_wd32.h
   #prototype/string/_c_trait_wd32_impl.h
   prototype/string/_c_trait_wide.cpp
   #prototype/string/_c_trait_wide.h
   #prototype/string/_c_trait_wide_impl.h
   #prototype/string/_c_unicode.h
   #prototype/string/__str_compare.h
   #prototype/string/_str_compare_impl.h
   prototype/string/_conv.h
   #prototype/string/_conv_ansi.cpp
   #prototype/string/_conv_ansi.h
   #prototype/string/_conv_ansi_impl.h
   prototype/string/__wide.cpp
   prototype/string/__wide.h
   prototype/string/_defer.h
   prototype/string/_impl.h
   prototype/string/_impl_prio.h
   prototype/string/_international.h
   #prototype/string/_natural.h
   #prototype/string/_str.h
   prototype/string/_str.cpp
   prototype/string/_string.cpp
   prototype/string/_str_impl.cpp
   #prototype/string/_str_impl.h
   #prototype/string/_string_wide.h
   #prototype/string/_sz_ansi.cpp
   #prototype/string/_sz_wd16.cpp
   #prototype/string/_sz_wd32.cpp
   #prototype/string/__string.h
   #prototype/string/_trait.h
   #prototype/string/_trait_ansi.h
   #prototype/string/_trait_ansi_impl.h
   #prototype/string/_trait_impl.h
   #prototype/string/_trait_wd16.h
   #prototype/string/_trait_wd16_impl.h
   #prototype/string/_trait_wd32.h
   #prototype/string/_trait_wd32_impl.h
   prototype/string/_u32hash.h
   #prototype/string/_unicode.h
   #prototype/string/_unicode_impl.h
   prototype/string/as_string.cpp
   prototype/string/base64.cpp
   prototype/string/base64.h
   prototype/string/bstr.h
   #prototype/string/bstring.cpp
   prototype/string/bstring.h
   prototype/string/ch.cpp
   #prototype/string/ch.h
   prototype/string/ch_class.cpp
   prototype/string/ch_class.h
   prototype/string/command_line.cpp
   prototype/string/command_line.h
   prototype/string/composite.h
   prototype/string/c_string.h
   #prototype/string/dup.cpp
   prototype/string/encoding_exception.cpp
   prototype/string/encoding_exception.h
   prototype/string/from_integer.cpp
   prototype/string/from_integer.h
   prototype/string/hex.cpp
   prototype/string/hex.h
   prototype/string/international.cpp
   prototype/string/international.h
   #prototype/string/international2.cpp
   #prototype/string/international2.h
   #prototype/string/manager.cpp
   prototype/string/network_payload.cpp
   prototype/string/network_payload.h
   prototype/string/parse.cpp
   prototype/string/parse.h
   #prototype/string/simple.cpp
   prototype/string/static_string.h
   #prototype/string/stdstring.h
   prototype/string/string.cpp
   prototype/string/string.h
   prototype/string/string_ansi.cpp
   #prototype/string/string_buffer.h
   prototype/string/string_inst.h
   prototype/string/string_wide.cpp
   #prototype/string/string_wide_conversion.cpp
   prototype/string/stringtow.cpp
   prototype/string/stringtow.h
   prototype/string/strw.cpp
   prototype/string/strx.cpp
   prototype/string/sz.cpp
   prototype/string/sz.h
   prototype/string/to_integer.cpp
   prototype/string/to_integer.h
   #prototype/string/to_string.cpp
   prototype/string/tokenizer.cpp
   prototype/string/tokenizer.h
   prototype/string/unicode.cpp
   prototype/string/unicode16.cpp
   prototype/string/unicode16_32.cpp
   prototype/string/unicode32.cpp
   prototype/string/character.cpp
   prototype/string/utf8_character.h
   prototype/string/wildcard.cpp
   #prototype/string/wstring_adaptor.h
   #prototype/string/x.cpp
   #prototype/string/x.h
   prototype/string/x/x_charcategory.h
   prototype/string/x/x_charcategory2.h
   prototype/string/x/x_charcategory_names.h
   prototype/string/x/x_defines.h
   prototype/string/x/x_encodings.h
   prototype/string/x/x_tables.h
   prototype/text/context.cpp
   prototype/text/context.h
   prototype/text/data.cpp
   prototype/text/data.h
   prototype/text/international.cpp
   prototype/text/international.h
   prototype/text/international_locale_schema.cpp
   prototype/text/international_locale_schema.h
   prototype/text/text.cpp
   prototype/text/text.h
   prototype/text/translator.cpp
   prototype/text/translator.h
   #prototype/time/duration/_.h
   #prototype/time/duration/duration.cpp
   #prototype/time/duration/duration.h
   prototype/time/floating/_.h
   prototype/time/integral/_.h
   prototype/time/time/posix_time.cpp
   prototype/time/time/posix_time.h
   prototype/time/time/time.cpp
   prototype/time/time/time.h
   prototype/time/_.h
   prototype/time/__string.cpp
   prototype/time/__string.h
   prototype/time/_binary_stream.h
   prototype/time/_impl.h
   prototype/time/_string.h
   #prototype/time/_time.h
   prototype/time/_impl.h
   prototype/time/_string.h
   prototype/time/_structures.h
   prototype/time/_text_stream.h
   #prototype/time/_unit.h
   prototype/time/_unit_operator.h
   prototype/time/time.cpp
   #prototype/time/
   #prototype/time/time_operator.h
   promise.cpp
   regular_expression/_regular_expression.h
   regular_expression/context.cpp
   regular_expression/context.h
   regular_expression/regular_expression.cpp
   regular_expression/regular_expression.h
   regular_expression/result.cpp
   regular_expression/result.h
   user/micro/_.h
   user/micro/button.cpp
   user/micro/button.h
   user/micro/console.cpp
   user/micro/console.h
   user/micro/details_window.cpp
   user/micro/details_window.h
   user/micro/dialog.cpp
   user/micro/dialog.h
   user/micro/elemental.cpp
   user/micro/elemental.h
   user/micro/main_window.cpp
   user/micro/main_window.h
   user/micro/message_box.cpp
   user/micro/message_box.h
   user/micro/popup_button.cpp
   user/micro/popup_button.h
   user/micro/still.cpp
   user/micro/still.h
   user/micro/theme.cpp
   user/micro/theme.h
   user/micro/user.cpp
   user/micro/user.h
   #   user/nano/_nano.cpp
   #   user/nano/_.h
   #   user/nano/brush.cpp
   #   user/nano/brush.h
   #   user/nano/button.cpp
   #   user/nano/button.h
   #   user/nano/child.cpp
   #   user/nano/child.h
   #   user/nano/details_window.cpp
   #   user/nano/details_window.h
   #   user/nano/device.cpp
   #   user/nano/device.h
   #   user/nano/device.h
   #   user/nano/display.cpp
   #   user/nano/display.h
   #   user/nano/font.cpp
   #   user/nano/font.h
   #   user/nano/message_box.cpp
   #   user/nano/message_box.h
   #   user/nano/nano.cpp
   #   user/nano/nano.h
   #   user/nano/object.cpp
   #   user/nano/object.h
   #   user/nano/pen.cpp
   #   user/nano/pen.h
   #   user/nano/popup_button.cpp
   #   user/nano/popup_button.h
   #   user/nano/still.cpp
   #   user/nano/still.h
   #   user/nano/window.cpp
   #   user/nano/window.h
   #   user/nano/window_implementation.cpp
   #   user/nano/window_implementation.h
   #   user/nano/window_interface.cpp
   #   user/nano/window_interface.h
   user/user/_string.cpp
   user/user/_string.h
   user/user/_text_stream.h
   #user/user/check.cpp
   #user/user/check.h
   user/user/check.cpp
   user/user/check.h
   user/user/check_property.cpp
   user/user/check_property.h
   user/user/container.cpp
   user/user/container.h
   user/user/content.h
   user/user/control.cpp
   user/user/control.h
   user/user/controller.cpp
   user/user/controller.h
   #user/user/conversation.cpp
   #user/user/conversation.h
   user/user/drag.cpp
   user/user/drag.h
   user/user/drag_client.cpp
   user/user/drag_client.h
   user/user/element.cpp
   user/user/element.h
   user/user/e_window_flag.h
   user/user/frame_interaction.cpp
   user/user/frame_interaction.h
   user/user/interaction.cpp
   user/user/interaction.h
   user/user/item.h
   user/user/key_state.cpp
   user/user/key_state.h
   user/user/message_box.cpp
   user/user/message_box.h
   user/user/mouse.cpp
   user/user/mouse.h
   user/user/os_colors.cpp
   user/user/os_theme_colors.cpp
   user/user/os_theme_colors.h
   user/user/property.cpp
   user/user/property.h
   #user/user/text.cpp
   #user/user/text.h
   user/user/text.cpp
   user/user/text.h
   user/user/text_property.cpp
   user/user/text_property.h
   user/user/theme_colors.h
   user/user/tool.h
   user/user/tool_item.cpp
   user/user/tool_item.h
   user/_.h
   windowing/sandbox/_sandbox.h
   windowing/sandbox/host_interaction.cpp
   windowing/sandbox/host_interaction.h
   windowing/sandbox/window.cpp
   windowing/sandbox/window.h
   windowing/sandbox/windowing.cpp
   windowing/sandbox/windowing.h
   windowing/_.h
   windowing/_windowing.cpp
   windowing/display.cpp
   windowing/display.h
   windowing/window.h
   windowing/window.cpp
   windowing/windowing.cpp
   windowing/windowing.h
   #windowing_system/_.h
   #windowing_system/windowing_system.cpp
   #windowing_system/windowing_system.h
   #update.h
)


list(APPEND library_source

   #   operating_system/android/
   #   operating_system/android/Kerr/LocalMemory.h
   #   operating_system/android/Kerr/kerr.h
   #   operating_system/android/_.h
   #   operating_system/android/_android.h
   #   operating_system/android/android1.h
   #   operating_system/android/application.h
   #   operating_system/android/file.h
   #   operating_system/android/implementation.h
   #   operating_system/android/internal.h
   #   operating_system/android/thread.h
   #   operating_system/serial.h
   # #operating_system/windows_common/graphics.h
   # operating_system/windows/d2d1_1.h
   # operating_system/windows/dir.h
   # operating_system/windows/environment_variable.h
   # operating_system/windows/exception_engine.h
   # operating_system/windows/extract_icon.h
   # operating_system/windows/file.h
   # operating_system/windows/handle.h
   # operating_system/windows/implementation.h
   # operating_system/windows/internal.h
   # operating_system/windows/itemidlist.h
   # operating_system/windows/parallelization.h
   # operating_system/windows/port_forward.h
   # operating_system/windows/print_job.h
   # operating_system/windows/printer.h
   # operating_system/windows/process.h
   # operating_system/windows/process_data.h
   # operating_system/windows/registry.h
   # operating_system/windows/shell1.h
   # operating_system/windows/simple_hold_handle.h
   # operating_system/windows/utils.h
   # operating_system/windows/windowing.h
   # operating_system/windows_common/_.h
   # operating_system/windows_common/_c.h
   # operating_system/windows_common/_default_dll_impl.h
   # operating_system/windows_common/_file_c.h
   # operating_system/windows_common/_unicode_c.h
   # operating_system/windows_common/bstring.h
   # operating_system/windows_common/comptr.h
   # operating_system/windows_common/cotaskptr.h
   # operating_system/windows_common/file.h
   # operating_system/windows_common/new_api.h
   # operating_system/windows_common/parallelization.h
   # operating_system/windows_common/variant.h
   # operating_system/winpr_input.h
   #_defer.h
   #allback.h
   #amework_c.h
   #application.h
   #array.h
   #astr.h
   #axispolicy/_.h
   #axispolicy/_c.h
   #compress/_.h
   #compress/gz.h
   #compress/zip/_.h
   #compress/zip/_internal.h
   #compress/zip/api.h
   #compress/zip/crypt.h
   #compress/zip/file.h
   #compress/zip/impl.h
   #compress/zip/in_file.h
   #compress/zip/ioapi.h
   #compress/zip/iowin32.h
   #compress/zip/memory_buffer.h
   #compress/zip/unzip.h
   #constant/thread.h
   #exception/_const.h
   #exception/assert.h
   #exception/base.h
   #exception/debug_stream.h
   #exception/engine.h
   #exception/hresult.h
   #exception/installing.h
   #exception/interface_only.h
   #exception/invalid_argument.h
   #exception/invalid_character.h
   #exception/invalid_handle.h
   #exception/invalid_index.h
   #exception/invalid_type.h
   #exception/io.h
   #exception/memory.h
   #exception/misc.h
   #exception/not_implemented.h
   #exception/not_installed.h
   #exception/not_licensed.h
   #exception/not_supported.h
   #exception/operation_canceled.h
   #exception/os.h
   #exception/overflow.h
   #exception/parsing.h
   #exception/range.h
   #exception/resource.h
   #exception/result.h
   #exception/runtime.h
   #exception/simple.h
   #exception/system.h
   #exception/temporary.h
   #exception/throw.h
   #exception/todo.h
   #exception/translator.cpp
   #exception/unhandled_report.h
   #exception/user.h
   #exception/void_implementation.h
   #filesystem/file/serializable.h
   #filesystem/filesystem.h
   #filesystem/filesystem/_.h
   #id.h
   #inline/${PROJECT_NAME}.h
   #inline/_acid.h
   #inline/application.h
   #inline/library.h
   #ispolicy/policy_objc.h
   #library.h
   #memory/plex.h
   #memory/plex_heap1.h
   #memory/plex_heap_impl1.h
   #ode/operating_system/universal_windows/file_winrt.h
   #operating_system/_.h
   #operating_system/_operating_system.h
   #operating_system/_operating_system2.h
   #operating_system/_user.h
   #operating_system/ansi/exception_engine.h
   #operating_system/ansi/pthread.cpp
   #operating_system/main.cpp
   #operating_system/universal_windows/_uwp.h
   #operating_system/universal_windows/_winrt.h
   #operating_system/universal_windows/gdi_winrt.h
   #operating_system/universal_windows/metrowin_metrowin.h
   #operating_system/universal_windows/simple_hold_handle.h
   #operating_system/universal_windows/simple_ui.h
   #operating_system/windows/_c.h
   #operating_system/windows/_windows.h
   #operating_system/windows/_windows_impl.h
   #operating_system/windows/api.h
   #operating_system/windows/callstack.h
   #parallelization/_.h
   #parallelization/create_thread.h
   #parallelization/data.h
   #parallelization/synchronization_object.cpp
   #parallelization/synchronization_object.h
   #parallelization/synchronization_result.cpp
   #parallelization/synchronized_process.cpp
   #parallelization/synchronized_task.cpp
   #parallelization/synchronized_task.h
   #parallelization/thread_impl.h
   #parallelization/thread_os.h
   #parallelization/thread_parameter.h
   #parallelization/zaa_update_task.h
   #parallelization/zaa_update_task_item.h
   #parallelization/zaa_update_task_item_array.h
   #platform/_generic_object_constructor_impl.h
   #platform/acme.h
   #platform/acme_str_pool.h
   #platform/all.h
   #platform/aura_regex.h
   #platform/keep_true.h
   #platform/main.h
   #platform/message_box.h
   #platform/net.h
   #platform/regex.h
   #platform/restore.h
   #platform/serial_impl.h
   #platform/simple_app.h
   #platform/sprintf.h
   #platform/static_start.h
   #platform/static_start_internal.h
   #platform/system_impl.h
   #prototype/collection/_.h
   #prototype/collection/_array_base_impl.h
   #prototype/collection/_array_impl.h
   #prototype/collection/_array_impl2.h
   #prototype/collection/_collection_impl1.h
   #prototype/collection/_collection_impl2.h
   #prototype/collection/_fifo_map_impl.h
   #prototype/collection/_list_impl.h
   #prototype/collection/_map_impl.h
   #prototype/collection/_papaya.h
   #prototype/collection/_papaya_array.h
   #prototype/collection/_papaya_array2d_impl.h
   #prototype/collection/_papaya_array_impl.h
   #prototype/collection/_papaya_impl.h
   #prototype/collection/_papaya_map.h
   #prototype/collection/_papaya_map_impl.h
   #prototype/collection/_point_array.h
   #prototype/collection/_raw_array_impl.h
   #prototype/collection/_raw_array_impl2.h
   #prototype/collection/_sort_array_impl.h
   #prototype/collection/_sort_map_impl.h
   #prototype/collection/_string_array_impl.h
   #prototype/collection/base_2array.h
   #prototype/collection/decl.h
   #prototype/collection/runnable_array.h
   #prototype/collection/string_to_string_map.h
   #prototype/collection/stringl.h
   #prototype/collection/template.h
   #prototype/comparison/var_strict.h
   #update.h
   #user/user/_constant.h
   #user/user/mouse.cpp
   #xispolicy/policy_objcpp.h
   #xispolicy/policy_winrt.h
   _.h
   _start.h
   acme.h
   array2d.h
   console.h
   constant/_constant.h
   constant/_id.h
   constant/character_set.h
   constant/check.h
   constant/context.h
   constant/future.h
   constant/id.h
   #constant/idpool.h
   constant/impact.h
   constant/message.h
   constant/routine.h
   constant/simple_command.h
   constant/source.h
   constant/status.h
   constant/status_range_authentication.h
   constant/timer.h
   constant/user_key.cpp
   constant/user_key.h
   constant/_user_key_text.h
   #constant/user/_.h
   #constant/user/tool_item.h
   exception/_.h
   exception/_c.h
   exception/_dump_context.h
   exception/call_stack.cpp
   exception/call_stack.h
   #exception/callstack.h
   exception/cancel.h
   exception/dump_context.h
   exception/exception.cpp
   exception/exception.h
   exception/exception2.h
   exception/exit.cpp
   exception/exit.h
   exception/runtime_check.cpp
   exception/runtime_check.h
   #exception/standard.cpp
   #exception/standard.h
   exception/translator.h
   exception/trap.h
   filesystem/_impl.h
   filesystem/file/_.h
   filesystem/file/___serialization_draft.h
   filesystem/file/___serialization_draft001.h
   filesystem/file/_c.h
   filesystem/file/_constant.h
   filesystem/file/_defer.h
   filesystem/file/_defer_payload_stream.h
   filesystem/file/_file.h
   filesystem/file/_impl.h
   filesystem/file/_impl_text_stream.h
   filesystem/file/_impl_write_text_stream.h
   filesystem/file/_papaya.h
   filesystem/file/_papaya_impl.h
   filesystem/file/_payload_stream_impl.h
   filesystem/file/_serializable_impl.h
   filesystem/file/_stream_process_impl.h
   filesystem/file/_text_stream_impl.h
   filesystem/file/binary_stream.h
   filesystem/file/buffer.h
   filesystem/file/buffered_file.h
   filesystem/file/byte_stream.h
   filesystem/file/byte_stream_memory_file.h
   filesystem/file/circular_file.h
   filesystem/file/composite.h
   filesystem/file/cpp.h
   filesystem/file/dir.h
   filesystem/file/exception.h
   filesystem/file/file.h
   filesystem/file/file_stream1.h
   filesystem/file/item.h
   filesystem/file/item_array.h
   filesystem/file/listing_provider.h
   filesystem/file/memory_file.h
   filesystem/file/memory_map.h
   filesystem/file/opened.h
   filesystem/file/ostream_flush.h
   filesystem/file/path.h
   filesystem/file/payload_stream.h
   filesystem/file/prototype.h
   filesystem/file/read_sz_stream.h
   filesystem/file/serialize.h
   filesystem/file/status.h
   filesystem/file/stream.h
   filesystem/file/streamable.h
   filesystem/file/string_buffer.h
   filesystem/file/text_file.h
   filesystem/file/text_stream.h
   filesystem/file/transfer_file.h
   filesystem/file/write_text_stream.h
   filesystem/filesystem/_impl.h
   filesystem/filesystem/enumerator.cpp
   filesystem/filesystem/enumerator.h
   filesystem/filesystem/listing.h
   filesystem/filesystem/path.h
   filesystem/filesystem/path_array.cpp
   filesystem/filesystem/path_array.h
   filesystem/filesystem/path_object.h
   framework.h
   graphics/draw2d/_.h
   graphics/draw2d/_constant.h
   graphics/draw2d/color.h
   #graphics/draw2d/colorref_array.h
   include/_.h
   #include/_c.h
   include/_c_bridge.h
   include/_include.h
   include/_setup.h
   include/_simple_templates.h
   include/objc.h
   include/objcpp.h
   include/winrt.h
   inline/__debug_box_clear_impl.h
   inline/__debug_box_set_impl.h
   inline/_application.h
   inline/_console_old.h
   inline/_draw2d_impl.h
   inline/_new_impl.h
   inline/application/linux.h
   inline/application_common.h
   inline/console.h
   inline/console_common.h
   ios_aura/ios_aura.h
   #memory/_heap.h
   memory/_new.h
   memory/align_byte_count.h
   memory/allocate.h
   memory/allocate_processor_cache_oriented.h
   #memory/allocate_system_heap.cpp
   memory/allocator.cpp
   memory/allocator.h
   memory/allocation.h
   #memory/heap_.h
   #memory/heap_c.h
   memory/heap_item.h
   memory/heap_item_array.h
   memory/heap_memory.h
   memory/heap.cpp
   memory/heap.h
   memory/malloc.h
   memory/memory.cpp
   memory/memory.h
   #memory/memory_allocator.h
   #memory/os_alloc.h
   memory/operation.cpp
   memory/operation.h
   memory/plex.cpp
   memory/plex.h
   memory/plex_heap.cpp
   memory/plex_heap.h
   memory/plex_heap_alloc.cpp
   memory/plex_heap_alloc.h
   memory/plex_heap_alloc_array.cpp
   memory/plex_heap_alloc_array.h
   memory/plex_heap_alloc_sync.cpp
   memory/plex_heap_alloc_sync.h
   operating_system/_.h
   operating_system/_api.cpp
   operating_system/_application.h
   operating_system/_impl.h
   operating_system/ansi/_.h
   operating_system/ansi/_ansi.h
   operating_system/ansi/_c.h
   operating_system/ansi/ansios_file.h
   operating_system/ansi/binreloc.h
   operating_system/ansi/call_stack.h
   operating_system/ansi/datetime_c.h
   operating_system/ansi/file.h
   operating_system/ansi/file_c.h
   operating_system/ansi/file_raw.h
   operating_system/ansi/pmutex_lock.h
   operating_system/ansi/semun.h
   operating_system/bidirectional_pipe.cpp
   operating_system/bidirectional_pipe.h
   operating_system/environment.cpp
   operating_system/environment.h
   operating_system/error_code.cpp
   operating_system/error_code.h
   operating_system/exit_status.cpp
   operating_system/exit_status.h
   operating_system/file.h
   operating_system/graphics.h
   operating_system/memory.cpp
   operating_system/os_windowing2.h
   operating_system/parallelization.h
   operating_system/pipe.cpp
   operating_system/pipe.h
   #operating_system/posix/_null_nano_dynamic_library_dl.cpp
   operating_system/posix/_stdio_file.h
   operating_system/posix/call_stack.cpp
   operating_system/posix/mq_base.h
   operating_system/posix/file.h
   operating_system/pthread/pthread_np.cpp
   operating_system/process.cpp
   operating_system/security_attributes.cpp
   operating_system/security_attributes.h
   operating_system/shared_posix/c_error_number.cpp
   operating_system/shared_posix/c_error_number.h
   operating_system/shared_posix/debug.cpp
   operating_system/shared_posix/earth_time_shift.cpp
   operating_system/shared_posix/errno.cpp
   operating_system/shared_posix/stdio_file.cpp
   operating_system/shared_posix/stdio_file.h
   operating_system/shared_posix/windows_time.cpp
   operating_system/shared_posix/time.cpp
   operating_system/shared_posix/time.h
   operating_system/solaris/linux_internal.h
   operating_system/solaris/solaris.h
   operating_system/solaris/solaris_cairo_keep.h
   operating_system/solaris/solaris_cross_win_file.h
   operating_system/solaris/solaris_cross_win_gdi.h
   operating_system/solaris/solaris_cross_win_gdi_internal.h
   operating_system/solaris/solaris_debug.h
   operating_system/solaris/solaris_file.h
   operating_system/solaris/solaris_file_watcher.h
   operating_system/solaris/solaris_graphics.h
   operating_system/solaris/solaris_http.h
   operating_system/solaris/solaris_http_lib.h
   operating_system/solaris/solaris_internal.h
   operating_system/solaris/solaris_process.h
   operating_system/solaris/solaris_simple_ui.h
   operating_system/solaris/solaris_solaris.h
   operating_system/solaris/solaris_user_impl.h
   operating_system/solaris/solaris_window_xlib.h
   operating_system/string.cpp
   operating_system/text.h
   operating_system/time.h
   operating_system/universal_windows/_.h
   operating_system/universal_windows/base_file.h
   operating_system/universal_windows/exception_engine.h
   operating_system/universal_windows/host_interaction.h
   operating_system/universal_windows/parallelization.h
   operating_system/universal_windows/parallelization_winrt.h
   operating_system/universal_windows/process.h
   operating_system/universal_windows/sockets.h
   operating_system/user.h
   operating_system/windows/_.h
   parallelization/_impl.h
   parallelization/_thread_os_create_impl.h
   parallelization/_types.h
   parallelization/common.h
   parallelization/condition.h
   parallelization/critical_section.h
   parallelization/initial_single_lock.h
   #parallelization/manual_reset_event.h
   parallelization/message_queue.cpp
   parallelization/message_queue.h
   parallelization/message_queue_global.cpp
   parallelization/mutex.h
   parallelization/pool.h
   parallelization/queue.cpp
   parallelization/queue.h
   parallelization/semaphore.h
   parallelization/set_event_on_exit.h
   parallelization/single_lock.h
   parallelization/socket_event.h
   parallelization/synchronization_array.cpp
   parallelization/synchronization_array.h
   #parallelization/synchronization_result.h
   parallelization/synchronized_process.h
   parallelization/synchronous_lock.h
   parallelization/task.h
   parallelization/tools.cpp
   parallelization/tools.h
   parallelization/wait_for_end_of_sequence.cpp
   parallelization/wait_for_end_of_sequence.h
   platform/_features.h
   platform/_global.h
   platform/_impl.h
   platform/_platform.h
   platform/auto.h
   platform/auto_pointer.h
   platform/c.cpp
   platform/c.h
   platform/class.h
   platform/cmp.h
   platform/cmp2.h
   #platform/common.h
   platform/const.h
   platform/constraint.h
   #platform/conversation_message.cpp
   #platform/conversation_message.h
   platform/debug.h
   platform/definition.h
   platform/display.h
   platform/enum.h
   #platform/error.h
   platform/exclusive.h
   platform/factory.h
   platform/filestream.h
   platform/fixed_alloc.h
   platform/fixed_alloc_impl.h
   platform/flags.h
   platform/hyperlink.h
   platform/keep.h
   platform/less.h
   platform/logic.h
   platform/lparam.h
   platform/muldiv64.cpp
   platform/nanosecond_timer.h
   platform/number.h
   platform/_referencing_debugging.h
   platform/reference_item.cpp
   platform/reference_item.h
   platform/referencing_debugging.cpp
   platform/referencing_debugging.h
   platform/reference_item_array.cpp
   platform/reference_item_array.h
   platform/object_type_counter.cpp
   platform/object_type_counter.h
   platform/printf.h
   platform/profiler.h
   platform/release_time.h
   #platform/sequence.cpp
   #platform/sequencer.h
   platform/serial.h
   platform/simple_log.cpp
   platform/simple_log.h
   platform/status.h
   platform/string_exchange.cpp
   platform/string_exchange.h
   platform/system.h
   platform/text.h
   platform/timeout.h
   platform/timer.h
   platform/timer_array.h
   platform/timer_callback.h
   platform/timer_event.h
   platform/timer_item.h
   platform/timer_task.h
   platform/title.h
   platform/trace_category.h
   platform/trace_statement.cpp
   platform/trace_statement.h
   platform/uint32_muldiv.h
   platform/uint64_muldiv.h
   platform/user_parent.h
   prototype/api/api.h
   prototype/api/api_rotate.h
   prototype/collection/__payload_array.h
   prototype/collection/_function.h
   prototype/collection/_loosely.h
   prototype/collection/_loosely_map.h
   prototype/collection/_papaya_heap.h
   prototype/collection/_sort.h
   prototype/collection/address_array.h
   prototype/collection/array.h
   prototype/collection/array_base.h
   prototype/collection/attrib_map.h
   prototype/collection/back_insert_iterator.h
   prototype/collection/base_enum.h
   prototype/collection/bit_array.h
   prototype/collection/bitset.h
   prototype/collection/bool_array.h
   prototype/collection/comparable_array.h
   prototype/collection/comparable_eq_array.h
   prototype/collection/comparable_eq_list.h
   prototype/collection/comparable_list.h
   prototype/collection/comparable_prototype_array.h
   prototype/collection/comparable_raw_array.h
   prototype/collection/composite_array.h
   prototype/collection/deque.h
   prototype/collection/fifo_map.h
   prototype/collection/file_path_map.h
   prototype/collection/forward.h
   prototype/collection/insert_iterator.h
   prototype/collection/int_map.h
   prototype/collection/iterable.h
   prototype/collection/iterator.h
   prototype/collection/list.h
   prototype/collection/map.h
   prototype/collection/set_node.h
   prototype/collection/map_to_smart_pointer.h
   prototype/collection/numeric_array.h
   prototype/collection/numeric_array_range.h
   prototype/collection/packset.h
   prototype/collection/pair.h
   prototype/collection/pointer_array.h
   prototype/collection/pointer_array_process.h
   prototype/collection/priority_queue.h
   prototype/collection/ptr_array.h
   prototype/collection/queue.h
   prototype/collection/range.h
   prototype/collection/raw_array.h
   prototype/collection/set.h
   prototype/collection/sort_array.h
   prototype/collection/sort_list.h
   prototype/collection/sort_map.h
   prototype/collection/spreadset.h
   prototype/collection/stack.h
   prototype/collection/std_iterator.h
   prototype/collection/std_pair.h
   prototype/collection/strid_map.h
   prototype/collection/string_array.h
   prototype/collection/string_iterable.h
   prototype/collection/string_list.h
   prototype/collection/string_map.h
   prototype/collection/unique_array.h
   prototype/comparison/_.h
   prototype/comparison/_c.h
   prototype/comparison/binary.h
   prototype/comparison/compare.h
   prototype/comparison/equals.h
   prototype/comparison/hash.h
   prototype/comparison/less.h
   prototype/comparison/md5.h
   prototype/comparison/sign.h
   prototype/prototype/_impl_pointer.h
   prototype/prototype/_impl_prototype.h
   procedure.h
   template/list.h
   user/user/_.h
   user/user/_constant.h
   user/user/mouse.h
   user/user/os_colors.h
   release/release.config.h
   release/release.h
   release/release.cpp
   include/_impl.h
)

if (ANDROID)
   list(APPEND library_source

      operating_system/android/_.h
      operating_system/android/_android.h
      operating_system/android/_c.h
      operating_system/android/_os_impl.h
      operating_system/android/_os_local.h
      operating_system/android/_os_object.h
      operating_system/android/_os_remote.h
      operating_system/android/cross_win_file.h
      operating_system/android/cross_win_gdi.h
      operating_system/android/cross_win_gdi_internal.h
      operating_system/android/exception_engine.h
      operating_system/android/file.h
      operating_system/android/graphics.h
      operating_system/android/internal.h
      operating_system/android/process.h

   )

endif ()

if (APPLE_IOS)
   list(APPEND library_source


      operating_system/ios/_.h
      operating_system/ios/_c.h
      operating_system/ios/_ios.h
      operating_system/ios/_m.h
      operating_system/ios/_mm.h
      operating_system/ios/base_internal.h
      operating_system/ios/cross_win_gdi.h
      operating_system/ios/engine.h
      operating_system/ios/gen_1.h
      operating_system/ios/implementation.h
      operating_system/ios/internal.h
      operating_system/ios/mm_graphics.h
      operating_system/ios/mm_oswindow.h
      operating_system/ios/oswindow_data.h
      operating_system/ios/parallelization.h
      operating_system/ios/process.h
      operating_system/ios/window.h
      operating_system/ios/window_boot.h
      operating_system/ios/window_impl.h
      operating_system/ios/windowing.h

   )

endif ()


if (UWP)
   list(APPEND library_source
      exception/winrt/engine_winrt.cpp
      operating_system/universal_windows/error.cpp
      operating_system/universal_windows/_factory.cpp
      operating_system/universal_windows/file.cpp
      operating_system/universal_windows/file_find.cpp
      operating_system/universal_windows/native_buffer.cpp
      operating_system/universal_windows/timer.cpp
      operating_system/universal_windows/util.cpp
      operating_system/universal_windows/_.cpp
      operating_system/universal_windows/_os_metrowin.cpp
      operating_system/universal_windows/application_system_run.cpp
      operating_system/universal_windows/aura.cpp
      operating_system/universal_windows/debug.cpp
      operating_system/universal_windows/direct2d_tls.cpp
      operating_system/universal_windows/dpi.cpp
      operating_system/universal_windows/dummy_ipc.cpp
      #operating_system/universal_windows/exception_engine.cpp
      operating_system/universal_windows/file.cpp
      operating_system/universal_windows/file_memory_map.cpp
      operating_system/universal_windows/graphics.cpp
      operating_system/universal_windows/language.cpp
      operating_system/universal_windows/lock.cpp
      operating_system/universal_windows/main.cpp
      operating_system/universal_windows/parallelization.cpp
      operating_system/universal_windows/os_message_box.cpp
      operating_system/universal_windows/process.cpp
      operating_system/universal_windows/sockets.cpp
      operating_system/universal_windows/time.cpp
      operating_system/universal_windows/user.cpp)

   list(APPEND library_source
      operating_system/universal_windows/exception.h
      operating_system/universal_windows/
      operating_system/universal_windows/file.h
      operating_system/universal_windows/file_find.h
      operating_system/universal_windows/native_buffer.h
      operating_system/universal_windows/net/net_address.h
      operating_system/universal_windows/_.h
      operating_system/universal_windows/_uwp.h
   )

endif ()


if (WIN32)

   list(APPEND library_source
      #      operating_system/windows/console.cpp
      #      operating_system/windows/_factory.cpp
      #      operating_system/windows/file.cpp
      #      operating_system/windows/file_find.cpp
      #      operating_system/windows/pipe.cpp
      #      operating_system/windows/registry.cpp
      #      operating_system/windows/serial.cpp
      #      operating_system/windows/timer.cpp
      #      operating_system/windows/trace.cpp
      #      operating_system/windows/uac_tools.cpp
      #      operating_system/windows/windows.cpp
      #      operating_system/windows/windows_desktop.cpp
      #      operating_system/windows/_.cpp
      #      operating_system/windows/_ansi.cpp
      #      operating_system/windows/_wd16.cpp
      #      operating_system/windows/_wd32.cpp
      #      operating_system/windows/ansi_file.cpp
      #      operating_system/windows/api.cpp
      #      operating_system/windows/application.cpp
      #operating_system/windows/application_system_run.cpp
      #operating_system/windows/callstack.cpp
      #      operating_system/windows/debug.cpp
      #      operating_system/windows/dir.cpp
      #      operating_system/windows/environment_variable.cpp
      #      operating_system/windows/exception_engine.cpp
      #      operating_system/windows/extract_icon.cpp
      #      operating_system/windows/file.cpp
      #operating_system/windows/gdiplus.cpp
      #      operating_system/windows/internal.cpp
      #      operating_system/windows/itemidlist.cpp
      #      operating_system/windows/language.cpp
      #      operating_system/windows/library.cpp
      #operating_system/windows/list_serial_ports.cpp
      #operating_system/windows/local_memory_map.cpp
      #      operating_system/windows/lock.cpp
      #      operating_system/windows/main.cpp
      #      operating_system/windows/message_loop.cpp
      #      operating_system/windows/printer.cpp
      #      operating_system/windows/process.cpp
      #      operating_system/windows/registry.cpp
      #      operating_system/windows/simple_app.cpp
      #      operating_system/windows/parallelization.cpp
      #      operating_system/windows/time.cpp
      #      operating_system/windows/user.cpp
      #      operating_system/windows/util.cpp
      #      operating_system/windows/windowing.cpp
      #operating_system/windows/base/
      #operating_system/windows/base/implementation.h
      #operating_system/windows/base/print_job.h
      #operating_system/windows/base/_windows.h
      #operating_system/windows/console.h
      operating_system/windows/calculate_edesktop.cpp
      operating_system/windows/calculate_etoolkit.cpp
      operating_system/windows/calculate_ewindowing.cpp
      operating_system/windows/callstack.cpp
      operating_system/windows/file1.cpp
      #operating_system/windows/heap_allocator.cpp
      #operating_system/windows/heap_allocator.h
      operating_system/windows/dynamic_library.cpp
      operating_system/windows/dynamic_library.h
      #operating_system/windows/memory.cpp
      operating_system/windows/message_box.cpp
      operating_system/windows/message_loop.cpp
      operating_system/windows/parallelization.cpp
      operating_system/windows/process.cpp
      operating_system/windows/thread.cpp
      operating_system/windows/user.cpp
      operating_system/windows/window.cpp
      operating_system/windows/windows.cpp
      #operating_system/windows/exception.h
      #operating_system/windows/
      #operating_system/windows/file.h
      #operating_system/windows/file_find.h
      #operating_system/windows/pipe.h
      #operating_system/windows/registry.h
      #operating_system/windows/serial.h
      #operating_system/windows/uac_tools.h
      #operating_system/windows/user.h
      #operating_system/windows/_.h
      #operating_system/windows/_operating_system_windows.h
      #operating_system/windows/_operating_system_windows_private.h
      #operating_system/windows/_windows.h
#      operating_system/windows/nano/user/_user.cpp
#      operating_system/windows/nano/user/brush.cpp
#      operating_system/windows/nano/user/brush.h
#      operating_system/windows/nano/user/device.cpp
#      operating_system/windows/nano/user/device.h
#      operating_system/windows/nano/user/font.cpp
#      operating_system/windows/nano/user/font.h
#      operating_system/windows/nano/user/object.h
#      operating_system/windows/nano/user/object.cpp
#      operating_system/windows/nano/user/pen.cpp
#      operating_system/windows/nano/user/pen.h
#      operating_system/windows/nano/user/window.cpp
#      operating_system/windows/nano/user/window.h
#      operating_system/windows/nano/user/http/_nano_http.cpp
      operating_system/windows/nano/http/_http.h
      operating_system/windows/nano/http/hinternet.cpp
      operating_system/windows/nano/http/hinternet.h
      operating_system/windows/nano/http/http.cpp
      operating_system/windows/nano/http/http.h
      operating_system/windows/nano/http/connect.cpp
      operating_system/windows/nano/http/connect.h
      operating_system/windows/nano/http/get.cpp
      operating_system/windows/nano/http/get.h
      operating_system/windows/nano/http/request.cpp
      operating_system/windows/nano/http/request.h
      operating_system/windows/nano/http/session.cpp
      operating_system/windows/nano/http/session.h
   )
else ()

   list(APPEND library_source
      #operating_system/posix/file_memory_map.cpp
      #operating_system/posix/file_memory_map.h
      operating_system/ansi/time.cpp
      operating_system/ansi/dir.cpp
      operating_system/ansi/int_handle.cpp
      operating_system/ansi/int_handle.h
      #operating_system/ansi/parallelization.cpp
      operating_system/ansi/windows_time.cpp
      operating_system/ansi/windows_time.h
      operating_system/ansi/windows_unicode.cpp
      operating_system/ansi/windows_unicode.h
      #operating_system/cross/windows/user.cpp
      #operating_system/cross/windows/file.cpp
      #operating_system/cross/windows/dir.cpp
      #operating_system/cross/windows/time.cpp
      #operating_system/cross/windows/crt.cpp
      #operating_system/cross/windows/crt_debug.cpp
      #operating_system/cross/windows/datetime.cpp
      #operating_system/cross/windows/error.cpp
      #operating_system/cross/windows/locale.cpp
      #operating_system/cross/windows/shared_memory.cpp
      #operating_system/cross/windows/thread_local_storage.cpp
      #operating_system/cross/windows/ansios_message_loop.cpp
      #operating_system/cross/windows/user.cpp
      #operating_system/cross/windows/windows.cpp
      #operating_system/cross/windows/e.h
      #operating_system/cross/windows/message_box.h
      #operating_system/cross/windows/windows.h
      #operating_system/cross/windows/windows_base.h
      #operating_system/cross/windows/windows_base_tsd.h
      #operating_system/cross/windows/windows_common_controls.h
      #operating_system/cross/windows/windows_crt.h
      #operating_system/cross/windows/windows_crtdefs.h
      #operating_system/cross/windows/windows_defs.h
      #operating_system/cross/windows/windows_errno.h
      #operating_system/cross/windows/windows_error.h
      #operating_system/cross/windows/windows_file.h
      #operating_system/cross/windows/windows_gdi.h
      #operating_system/cross/windows/windows_guid_def.h
      #operating_system/cross/windows/windows_internals.h
      #operating_system/cross/windows/windows_mmeapi.h
      #operating_system/cross/windows/windows_mmsystem.h
      #operating_system/cross/windows/windows_nls.h
      #operating_system/cross/windows/windows_nt.h
      #operating_system/cross/windows/windows_ntstatus.h
      #operating_system/cross/windows/windows_ole_automation.h
      #operating_system/cross/windows/windows_shared_memory.h
      #operating_system/cross/windows/windows_thread.h
      #operating_system/cross/windows/windows_thread_impl.h
      #operating_system/cross/windows/windows_time.h
      #operating_system/cross/windows/windows_types.h
      #operating_system/cross/windows/windows_user.h
      #operating_system/cross/windows/windows_wincon.h
      #operating_system/cross/windows/windows_winnt.h
      #operating_system/cross/windows/_.h
      #operating_system/cross/_.h
      #operating_system/cross.h
      #operating_system/cross/_cross.h
   )

endif ()


if (${WIN32} OR ${UWP})

   list(APPEND library_source
      operating_system/windows_common/nano/idn/_.h
      operating_system/windows_common/nano/idn/_idn.cpp
      operating_system/windows_common/nano/idn/idn.cpp
      operating_system/windows_common/nano/idn/idn.h
      #      operating_system/windows_common/_dll.cpp
      #      operating_system/windows_common/aura.cpp
      #      operating_system/windows_common/base.cpp
      #      operating_system/windows_common/bstring.cpp
      #      operating_system/windows_common/com.cpp
      operating_system/windows_common/debug.cpp
      #operating_system/windows_common/desktop.cpp
      operating_system/windows_common/dll.cpp
      operating_system/windows_common/file.cpp
      operating_system/windows_common/file.h
      operating_system/windows_common/file1.cpp
      operating_system/windows_common/find_file.cpp
      operating_system/windows_common/find_file.h
      operating_system/windows_common/handle.cpp
      operating_system/windows_common/handle.h
      #operating_system/windows_common/idn.cpp
      operating_system/windows_common/heap_allocator.cpp
      operating_system/windows_common/heap_allocator.h
      operating_system/windows_common/last_error.h
      operating_system/windows_common/last_error_exception.cpp
      operating_system/windows_common/last_error_exception.h
      operating_system/windows_common/library.cpp
      operating_system/windows_common/memory.cpp
      operating_system/windows_common/parallelization.cpp
      operating_system/windows_common/process.cpp
      operating_system/windows_common/time.cpp
      operating_system/windows_common/unicode.cpp
      #operating_system/windows_common/user.cpp
      operating_system/windows_common/windows_common.cpp
      #      operating_system/windows_common/file.cpp
      #operating_system/windows_common/file_c.cpp
      #operating_system/windows_common/graphics.cpp
      #operating_system/windows_common/net.cpp
      #      operating_system/windows_common/parallelization.cpp
      #      operating_system/windows_common/time.cpp
      #      operating_system/windows_common/unicode.cpp
   )

endif ()


if (${LINUX})
   list(APPEND library_source
      operating_system/linux/
      operating_system/linux/_.cpp
      operating_system/linux/_.h
      operating_system/linux/_.h
      operating_system/linux/_c.h
      operating_system/linux/_factory.cpp
      #operating_system/linux/_linux.h
      #operating_system/linux/_linux.h
      #operating_system/linux/_user.h
      operating_system/linux/application.h
      operating_system/linux/callstack.cpp
      #operating_system/linux/cross_win_file.cpp
      #operating_system/linux/cross_win_file.h
      #operating_system/linux/cross_win_gdi.cpp
      #operating_system/linux/cross_win_gdi.h
      #operating_system/linux/cross_win_gdi_internal.h
      operating_system/linux/debug.cpp
      operating_system/linux/debug.h
      operating_system/linux/dumpinit.cpp
      operating_system/linux/error.cpp
      operating_system/linux/file.cpp
      #operating_system/linux/file.h
      operating_system/linux/file_lock.cpp
      operating_system/linux/graphics.cpp
      #operating_system/linux/internal.h
      #operating_system/linux/library.cpp
      operating_system/linux/linux.cpp
      operating_system/linux/linux.cpp
      operating_system/linux/linux.inl
      operating_system/linux/linux2.cpp
      operating_system/linux/linux_linux.h
      operating_system/linux/node.cpp
      operating_system/linux/os.cpp
      operating_system/linux/parallelization.cpp
      operating_system/linux/process.cpp
      operating_system/linux/process.h
      operating_system/linux/process_pid.cpp
      operating_system/linux/root_tools.cpp
      operating_system/linux/root_tools.h
      operating_system/linux/simple_app.cpp
      operating_system/linux/standard_exception.cpp
      operating_system/linux/standard_exception.h
      operating_system/linux/system.cpp
      operating_system/linux/thread.cpp
      #operating_system/linux/thread.h
      operating_system/linux/time.cpp
      operating_system/linux/trace.cpp
      operating_system/linux/user.cpp
      operating_system/linux/user.h
      operating_system/linux/user_private.h
      operating_system/linux/util.cpp
      operating_system/linux/win_base.cpp
   )


endif ()


#if(${LINUX} OR ${FREEBSD} OR ${OPENBSD})
#
#
#   list(APPEND library_source
#      operating_system/motif/message_box.cpp
#      operating_system/motif/message_box.h
#      operating_system/motif/application.cpp
#      operating_system/motif/application.h
#   )
#
#   list(APPEND this_system_libraries Xm)
#
#   list(APPEND extra_pkg_modules xt)
#
#endif()

if (MACOS)
   list(APPEND library_source
      operating_system/cross/universal_windows/cross_metrowin_user.cpp
      operating_system/cross/universal_windows/metrowin_user.cpp
      #operating_system/macos/application.cpp
      #operating_system/macos/_factory.cpp
      #operating_system/macos/file.cpp
      #operating_system/macos/main.cpp
      #operating_system/macos/stdio_file.cpp
      #operating_system/macos/thread.cpp
      #operating_system/macos/trace.cpp
      #operating_system/macos/util.cpp
      operating_system/macos/_.cpp
      #operating_system/macos/application_system_run.cpp
      #operating_system/macos/clipboard.cpp
      #operating_system/macos/cross_win.cpp
      #operating_system/macos/cross_win_file.cpp
      operating_system/macos/debug.cpp
      operating_system/macos/exception_engine.cpp
      #operating_system/macos/file.cpp
      #operating_system/macos/file.mm
      #operating_system/macos/graphics.cpp
      operating_system/macos/library.cpp
      #operating_system/macos/list_serial_ports.cpp
      #operating_system/macos/lock.cpp
      #operating_system/macos/MessageBoxA.cpp
      operating_system/macos/message_box.cpp
      operating_system/macos/message_box.h
      #operating_system/macos/mm.mm
      #operating_system/macos/mm_graphics.mm
      #operating_system/macos/mm_user.mm
      #operating_system/macos/mmos.mm
      #operating_system/macos/NSPasteboard++.mm
      #operating_system/macos/os.cpp
      operating_system/macos/parallelization.cpp
      #operating_system/macos/process.cpp
      #operating_system/macos/process_pid.cpp
      #operating_system/macos/time.cpp
      #operating_system/macos/user.cpp
      #operating_system/macos/win_base.cpp
      #operating_system/macos/windowing.cpp
      #operating_system/macos/winpr_keycode.cpp
   )


   list(APPEND library_source
      #operating_system/macos/application.h
      #operating_system/macos/
      #operating_system/macos/file.h
      #operating_system/macos/stdio_file.h
      #operating_system/macos/thread.h
      #operating_system/macos/user.h
      #operating_system/macos/_.h
      #operating_system/macos/_macos.h
      #operating_system/macos/_mm.h
      #operating_system/macos/cross_win_gdi.h
      #operating_system/macos/exception_engine.h
      #operating_system/macos/file.h
      #operating_system/macos/graphics_mm.h
      #operating_system/macos/internal.h
      #operating_system/macos/macos.h
      #operating_system/macos/main.h
      #operating_system/macos/mmos.h
      #operating_system/macos/mm_oswindow.h
      #operating_system/macos/os.h
      #operating_system/macos/process_c.h
      #operating_system/macos/user.h
      #operating_system/macos/windowing.h
      #operating_system/macos/windowing_c.h
      #operating_system/macos/window_impl.h
      #operating_system/macos/_.h
      #operating_system/macos/_c.h
      #operating_system/macos/_macos.h
      #operating_system/macos/_mm.h
   )

endif ()


if (IOS)
   list(APPEND library_source
      operating_system/cross/universal_windows/cross_metrowin_user.cpp
      operating_system/cross/universal_windows/metrowin_user.cpp
      operating_system/ios/exception.cpp
      operating_system/ios/_factory.cpp
      operating_system/ios/file.cpp
      operating_system/ios/ios.cpp
      operating_system/ios/ip_enum.cpp
      operating_system/ios/main.cpp
      operating_system/ios/os_context.cpp
      operating_system/ios/plane_system.cpp
      operating_system/ios/shell.cpp
      operating_system/ios/thread.cpp
      operating_system/ios/trace.cpp
      operating_system/ios/util.cpp
      operating_system/ios/application_system_run.cpp
      operating_system/ios/aura.cpp
      operating_system/ios/base_user.cpp
      operating_system/ios/cross_win.cpp
      operating_system/ios/cross_win_file.cpp
      operating_system/ios/crypt.cpp
      operating_system/ios/debug.cpp
      operating_system/ios/error.cpp
      operating_system/ios/exception_engine.cpp
      operating_system/ios/file.cpp
      operating_system/ios/fontopus.cpp
      operating_system/ios/graphics.cpp
      operating_system/ios/language.cpp
      operating_system/ios/launcher.cpp
      operating_system/ios/library.cpp
      operating_system/ios/lock.cpp
      operating_system/ios/MessageBoxA_W.mm
      operating_system/ios/mm.mm
      operating_system/ios/mm_cross_gdi.mm
      operating_system/ios/mm_graphics.mm
      operating_system/ios/mm_thread.mm
      operating_system/ios/mm_user.mm
      operating_system/ios/parallelization.cpp
      operating_system/ios/oswindow_data.cpp
      operating_system/ios/process.cpp
      operating_system/ios/process_pid.cpp
      operating_system/ios/simple_shell_launcher.cpp
      operating_system/ios/small_ipca_channel.cpp
      operating_system/ios/time.cpp
      operating_system/ios/user.cpp
      operating_system/ios/win_base.cpp
      operating_system/ios/window.cpp
      #"operating_system/ios/window_boot 2.h"
      operating_system/ios/windowing.cpp
   )


   list(APPEND library_source
      operating_system/ios/
      operating_system/ios/file.h
      operating_system/ios/implementation.h
      operating_system/ios/internal.h
      operating_system/ios/ip_enum.h
      operating_system/ios/os_context.h
      operating_system/ios/plane_system.h
      operating_system/ios/shell.h
      operating_system/ios/state.h
      operating_system/ios/thread.h
      operating_system/ios/_.h
      operating_system/ios/_ios.h
      operating_system/ios/_m.h
      operating_system/ios/_mm.h
   )


endif ()


if (APPLE)


   list(APPEND library_source
      asset/new.cpp
      operating_system/apple/_.cpp
      #operating_system/apple/DDInvocationGrabber.h
      #operating_system/apple/NSObject+DDExtensions.h
      #operating_system/apple/NSString+SymlinksAndAliases.h
      #operating_system/apple/UncaughtExceptionHandler.h
      #operating_system/apple/_.h
      #operating_system/apple/_apple.h
      #operating_system/apple/_c_mm.h
      #operating_system/apple/_mm.h
      #operating_system/apple/_mm_common.h
      #operating_system/apple/debug.h
      operating_system/apple/exe_path.cpp
      #operating_system/apple/graphics.h
      #operating_system/apple/main.h
      #operating_system/apple/ns_exception.h
      operating_system/apple/time.cpp
      #operating_system/apple/time.h
      #operating_system/chronometer.h
      #timer.mm
      #exception/mm.mm
      #operating_system/cross/universal_windows/cross_metrowin_user.cpp
      #operating_system/cross/universal_windows/metrowin_user.cpp
      #operating_system/apple/apple_timer.cpp
      #operating_system/apple/_.cpp
      #operating_system/apple/_apple.mm
      #operating_system/apple/DDInvocationGrabber.mm
      #operating_system/apple/debug.cpp
      #operating_system/apple/exe_path.cpp
      #operating_system/apple/graphics.cpp
      #operating_system/apple/image_gif.cpp
      #operating_system/apple/main.cpp
      #operating_system/apple/parallelization.cpp
      #operating_system/apple/ns_exception.cpp
      #operating_system/apple/NSObject+DDExtensions.mm
      #operating_system/apple/NSString+SymlinksAndAliases.mm
      #operating_system/apple/process.cpp
      #operating_system/apple/time.cpp
      #operating_system/apple/UncaughtExceptionHandler.mm
   )
endif ()


if (ANDROID)


   list(APPEND library_source
      operating_system/cross/universal_windows/cross_metrowin_user.cpp
      operating_system/cross/universal_windows/metrowin_user.cpp
      operating_system/android/android.cpp
      operating_system/android/android1.cpp
      operating_system/android/error.cpp
      operating_system/android/exception.cpp
      operating_system/android/_factory.cpp
      operating_system/android/file.cpp
      operating_system/android/main.cpp
      operating_system/android/process.cpp
      operating_system/android/thread.cpp
      operating_system/android/trace.cpp
      operating_system/android/util.cpp
      operating_system/android/_bind_app.cpp
      operating_system/android/_bind_impact.cpp
      operating_system/android/_os_android.cpp
      operating_system/android/_os_impl.cpp
      operating_system/android/_os_object.cpp
      operating_system/android/application_system_run.cpp
      operating_system/android/aura.cpp
      operating_system/android/c.cpp
      operating_system/android/debug.cpp
      operating_system/android/dir.cpp
      operating_system/android/exception_engine.cpp
      operating_system/android/file.cpp
      operating_system/android/graphics.cpp
      operating_system/android/jni_launcher.cpp
      operating_system/android/language.cpp
      operating_system/android/launcher.cpp
      operating_system/android/library.cpp
      operating_system/android/locale.cpp
      operating_system/android/lock.cpp
      operating_system/android/main_android.cpp
      operating_system/android/process.cpp
      operating_system/android/process_pid.cpp
      operating_system/android/win_base.cpp
   )


endif ()


if (SOLARIS)


   list(APPEND library_source
      operating_system/solaris/solaris.cpp
      operating_system/solaris/solaris_cairo_keep.cpp
      operating_system/solaris/solaris_cross_win_file.cpp
      operating_system/solaris/solaris_cross_win_gdi.cpp
      operating_system/solaris/solaris_display.cpp
      operating_system/solaris/solaris_file.cpp
      operating_system/solaris/solaris_file_watcher.cpp
      operating_system/solaris/solaris_http.cpp
      operating_system/solaris/solaris_http_lib.cpp
      operating_system/solaris/solaris_launcher.cpp
      operating_system/solaris/solaris_library.cpp
      operating_system/solaris/solaris_lock.cpp
      operating_system/solaris/solaris_message_loop.cpp
      operating_system/solaris/solaris_process.cpp
      operating_system/solaris/solaris_process_pid.cpp
      operating_system/solaris/solaris_simple_shell_launcher.cpp
      operating_system/solaris/solaris_simple_ui.cpp
      operating_system/solaris/solaris_small_ipca_channel.cpp
      operating_system/solaris/solaris_thread.cpp
      operating_system/solaris/solaris_win_base.cpp
      operating_system/solaris/solaris_window.cpp
      operating_system/solaris/solaris_window_xlib.cpp)


endif ()

if (${DARWIN})
   list(APPEND library_source
      #operating_system/darwin/callstack.cpp
   )
endif ()


if (${FREEBSD})
   list(APPEND library_source

      #operating_system/freebsd/application_system_run.cpp
      #operating_system/freebsd/console.cpp
      #operating_system/freebsd/console.h
      #operating_system/freebsd/file.cpp
      #operating_system/freebsd/file.h
      #operating_system/freebsd/gdk.cpp
      #operating_system/freebsd/gdk.h
      #operating_system/freebsd/list_serial_ports.cpp
      #operating_system/freebsd/operating_system.cpp
      #operating_system/freebsd/operating_system.h
      #operating_system/freebsd/shell.cpp
      #operating_system/freebsd/shell_freebsd.cpp
      #operating_system/freebsd/stdio_file.cpp
      #operating_system/freebsd/stdio_file.h
      #operating_system/freebsd/user.cpp
      operating_system/freebsd/
      operating_system/freebsd/_.cpp
      operating_system/freebsd/_.cpp
      operating_system/freebsd/_.h
      operating_system/freebsd/_.h
      operating_system/freebsd/_c.h
      operating_system/freebsd/_factory.cpp
      operating_system/freebsd/_freebsd.h
      operating_system/freebsd/_freebsd2.h
      #operating_system/freebsd/_user.h
      operating_system/freebsd/application.h
      operating_system/freebsd/call_stack.cpp
      #      operating_system/freebsd/cross_win_file.cpp
      #      operating_system/freebsd/cross_win_file.h
      #      operating_system/freebsd/cross_win_gdi.cpp
      #      operating_system/freebsd/cross_win_gdi.h
      #      operating_system/freebsd/cross_win_gdi_internal.h
      operating_system/freebsd/debug.cpp
      operating_system/freebsd/debug.h
      operating_system/freebsd/dumpinit.cpp
      operating_system/freebsd/error.cpp
      operating_system/freebsd/exception.cpp
      operating_system/freebsd/exception_engine.cpp
      operating_system/freebsd/exception_engine.h
      operating_system/freebsd/file.cpp
      operating_system/freebsd/file.h
      operating_system/freebsd/file_lock.cpp
      operating_system/freebsd/freebsd.cpp
      operating_system/freebsd/freebsd.inl
      operating_system/freebsd/freebsd2.cpp
      operating_system/freebsd/freebsd_freebsd.h
      #operating_system/freebsd/get_module_path_openbsd.cpp
      operating_system/freebsd/graphics.cpp
      operating_system/freebsd/internal.h
      #operating_system/freebsd/library.cpp
      operating_system/freebsd/os.cpp
      operating_system/freebsd/parallelization.cpp
      operating_system/freebsd/process.cpp
      operating_system/freebsd/process.h
      operating_system/freebsd/process_pid.cpp
      operating_system/freebsd/root_tools.cpp
      operating_system/freebsd/root_tools.h
      operating_system/freebsd/simple_app.cpp
      operating_system/freebsd/standard_exception.cpp
      operating_system/freebsd/standard_exception.h
      operating_system/freebsd/system.cpp
      operating_system/freebsd/thread.cpp
      operating_system/freebsd/thread.h
      #            operating_system/freebsd/time.cpp
      operating_system/freebsd/trace.cpp
      operating_system/freebsd/user.h
      operating_system/freebsd/user_private.h
      operating_system/freebsd/util.cpp
      operating_system/freebsd/win_base.cpp
   )

endif ()


if (${OPENBSD})
   list(APPEND library_source

      #operating_system/openbsd/application_system_run.cpp
      #operating_system/openbsd/console.cpp
      #operating_system/openbsd/console.h
      #operating_system/openbsd/file.cpp
      #operating_system/openbsd/file.h
      #operating_system/openbsd/gdk.cpp
      #operating_system/openbsd/gdk.h
      #operating_system/openbsd/list_serial_ports.cpp
      #operating_system/openbsd/operating_system.cpp
      #operating_system/openbsd/operating_system.h
      #operating_system/openbsd/shell.cpp
      #operating_system/openbsd/shell_openbsd.cpp
      #operating_system/openbsd/stdio_file.cpp
      #operating_system/openbsd/stdio_file.h
      #operating_system/openbsd/user.cpp
      operating_system/openbsd/
      operating_system/openbsd/_.cpp
      operating_system/openbsd/_.cpp
      operating_system/openbsd/_.h
      operating_system/openbsd/_.h
      operating_system/openbsd/_c.h
      operating_system/openbsd/_factory.cpp
      operating_system/openbsd/_openbsd.h
      operating_system/openbsd/_openbsd2.h
      #operating_system/openbsd/_user.h
      operating_system/openbsd/application.h
      operating_system/openbsd/call_stack.cpp
      #      operating_system/openbsd/cross_win_file.cpp
      #      operating_system/openbsd/cross_win_file.h
      #      operating_system/openbsd/cross_win_gdi.cpp
      #      operating_system/openbsd/cross_win_gdi.h
      #      operating_system/openbsd/cross_win_gdi_internal.h
      operating_system/openbsd/debug.cpp
      operating_system/openbsd/debug.h
      operating_system/openbsd/dumpinit.cpp
      operating_system/openbsd/error.cpp
      operating_system/openbsd/exception.cpp
      operating_system/openbsd/exception_engine.cpp
      operating_system/openbsd/exception_engine.h
      operating_system/openbsd/get_module_path.cpp
      operating_system/openbsd/file.cpp
      operating_system/openbsd/file.h
      operating_system/openbsd/file_lock.cpp
      operating_system/openbsd/openbsd.cpp
      operating_system/openbsd/openbsd.inl
      operating_system/openbsd/openbsd2.cpp
      operating_system/openbsd/openbsd_openbsd.h
      operating_system/openbsd/graphics.cpp
      operating_system/openbsd/internal.h
      #            operating_system/openbsd/library.cpp
      operating_system/openbsd/os.cpp
      operating_system/openbsd/parallelization.cpp
      operating_system/openbsd/process.cpp
      operating_system/openbsd/process.h
      operating_system/openbsd/process_pid.cpp
      operating_system/openbsd/root_tools.cpp
      operating_system/openbsd/root_tools.h
      operating_system/openbsd/simple_app.cpp
      operating_system/openbsd/standard_exception.cpp
      operating_system/openbsd/standard_exception.h
      operating_system/openbsd/system.cpp
      operating_system/openbsd/thread.cpp
      operating_system/openbsd/thread.h
      #            operating_system/openbsd/time.cpp
      operating_system/openbsd/trace.cpp
      operating_system/openbsd/user.h
      operating_system/openbsd/user_private.h
      operating_system/openbsd/util.cpp
      operating_system/openbsd/win_base.cpp
   )

endif ()


if (${NETBSD})
   list(APPEND library_source

      operating_system/netbsd/
      operating_system/netbsd/_.cpp
      operating_system/netbsd/_.cpp
      operating_system/netbsd/_.h
      operating_system/netbsd/_.h
      operating_system/netbsd/_c.h
      operating_system/netbsd/_factory.cpp
      operating_system/netbsd/_netbsd.h
      operating_system/netbsd/_netbsd2.h
      operating_system/netbsd/application.h
      operating_system/netbsd/call_stack.cpp
      operating_system/netbsd/debug.cpp
      operating_system/netbsd/debug.h
      operating_system/netbsd/dumpinit.cpp
      operating_system/netbsd/error.cpp
      operating_system/netbsd/exception.cpp
      operating_system/netbsd/exception_engine.cpp
      operating_system/netbsd/exception_engine.h
      #            operating_system/netbsd/get_module_path.cpp
      operating_system/netbsd/file.cpp
      operating_system/netbsd/file.h
      operating_system/netbsd/file_lock.cpp
      operating_system/netbsd/netbsd.cpp
      operating_system/netbsd/netbsd.inl
      operating_system/netbsd/netbsd2.cpp
      operating_system/netbsd/netbsd_netbsd.h
      operating_system/netbsd/graphics.cpp
      operating_system/netbsd/internal.h
      operating_system/netbsd/os.cpp
      operating_system/netbsd/parallelization.cpp
      operating_system/netbsd/process.cpp
      operating_system/netbsd/process.h
      operating_system/netbsd/process_pid.cpp
      operating_system/netbsd/root_tools.cpp
      operating_system/netbsd/root_tools.h
      operating_system/netbsd/simple_app.cpp
      operating_system/netbsd/standard_exception.cpp
      operating_system/netbsd/standard_exception.h
      operating_system/netbsd/system.cpp
      operating_system/netbsd/thread.cpp
      operating_system/netbsd/thread.h
      #            operating_system/netbsd/time.cpp
      operating_system/netbsd/trace.cpp
      operating_system/netbsd/user.h
      operating_system/netbsd/user_private.h
      operating_system/netbsd/util.cpp
      operating_system/netbsd/win_base.cpp
   )

endif ()

if (${__BSD__})

   list(APPEND library_source
      operating_system/bsd/time.cpp
      operating_system/bsd/sysctl.cpp
   )

endif ()

# if (${LINUX})

#    list(APPEND library_source
#       operating_system/posix/dynamic_library_dl.cpp
#       operating_system/posix/dynamic_library_dl.h
#    )

# endif ()


if (${LINUX} OR ${__BSD__} OR ${NETBSD} OR ${OPENBSD})


list(APPEND library_source
      operating_system/posix/__edesktop_calculate.cpp
      operating_system/posix/__edisplaytype_initialize.cpp
      operating_system/posix/__etoolkit_calculate.cpp
   )

endif ()


if (${LINUX} OR ${LINUX} OR ${__BSD__} OR ${APPLE} OR ${SOLARIS})


   list(APPEND library_source
      operating_system/posix/_.cpp
      operating_system/posix/_.h
      operating_system/posix/_posix.h
      operating_system/posix/file.cpp
      operating_system/posix/chldstatus.cpp
      operating_system/posix/environment.cpp
      operating_system/posix/environment.h
      operating_system/posix/file_lock.cpp
      operating_system/posix/file_lock.h
      #operating_system/posix/idn.cpp
      #operating_system/posix/local_memory_map.cpp
      operating_system/posix/memory.cpp
      operating_system/posix/process.cpp
      operating_system/posix/parallelization.cpp
      operating_system/posix/parallelization_pthread.cpp
      operating_system/posix/parallelization_pthread.h
      #operating_system/posix/time.cpp
      #operating_system/posix/timer.cpp
      operating_system/winpr_keycode.cpp
      operating_system/winpr_scancode.cpp
      operating_system/strict_posix/debug.cpp
   )

   #set_source_files_properties(operating_system/posix/process.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
endif ()


if (${LINUX} OR ${__BSD__})


   list(APPEND library_source
      operating_system/ansi/binreloc.cpp
      operating_system/ansi/acme.cpp
   )


endif ()


if (${LINUX} OR ${__BSD__})


   list(APPEND library_source
      operating_system/posix/call_stack.cpp
   )


endif ()




add_library(${PROJECT_NAME} SHARED ${library_source}
   operating_system/posix/dynamic_library_dl.cpp
   operating_system/posix/dynamic_library_dl.h
)


add_library(static_${PROJECT_NAME} STATIC ${library_source}
   operating_system/posix/_null_nano_dynamic_library_dl.cpp)


if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(static_${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

   message(STATUS "acme LIBRARY_OUTPUT_PATH is ${LIBRARY_OUTPUT_PATH}")
   message(STATUS "some target link options ${PROJECT_NAME} PRIVATE \"/IMPLIB:${LIBRARY_OUTPUT_PATH}/acme.lib\"")

   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/acme.lib")
   #target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/acme.def")
   target_link_libraries(${PROJECT_NAME} PRIVATE archive zlib dbghelp imagehlp dwmapi Setupapi Windowscodecs Winmm ws2_32 Crypt32 Normaliz version Secur32 gdiplus Shlwapi Imm32.lib)


elseif (${LINUX} OR ${__BSD__})

   if (NOT ${SUSE})

      target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
      #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
      target_compile_features(static_${PROJECT_NAME} PRIVATE cxx_std_20)

   endif ()


   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS} ${GLOBAL_EXTRA_COMPILER_FLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS} ${GLOBAL_EXTRA_COMPILER_FLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})

   if (${OPENBSD})
      #list(APPEND this_system_libraries z pthread iconv execinfo kvm c)
      list(APPEND this_system_libraries z pthread iconv kvm c)
      list(APPEND static_this_system_libraries z pthread iconv kvm c)
      message(STATUS "OPENBSD acme this_system_libraries ${this_system_libraries}")
   elseif (${FREEBSD})
      list(APPEND this_system_libraries z dl pthread iconv execinfo)
      list(APPEND static_this_system_libraries z dl pthread iconv execinfo elf)
      message(STATUS "FREEBSD acme this_system_libraries ${this_system_libraries}")
   elseif (${NETBSD})
      list(APPEND this_system_libraries z pthread iconv execinfo c)
      list(APPEND static_this_system_libraries z pthread iconv execinfo elf)
      message(STATUS "NETBSD acme this_system_libraries ${this_system_libraries}")
   else ()
      list(APPEND this_system_libraries z pthread idn)
      list(APPEND static_this_system_libraries pthread)
      message(STATUS "ELSE acme this_system_libraries ${this_system_libraries}")
   endif ()

   #add_dependencies(${PROJECT_NAME} static_nano_dynamic_library_dl)


   #target_link_libraries(${PROJECT_NAME} PRIVATE
   #       ${this_system_libraries} ${global_library_references}
   #      -lstatic_nano_dynamic_library_dl
   #)
   target_link_libraries(${PROJECT_NAME} PRIVATE
      ${this_system_libraries}
   )
   target_link_libraries(static_${PROJECT_NAME} PRIVATE
      ${static_this_system_libraries}
   )

   target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)


   message(STATUS "(3) pkg_config_modules_here is " ${pkg_config_modules_here})

   message(STATUS "(3) global_library_references is " ${global_library_references})

   message(STATUS "(3) ${PROJECT_NAME}_PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})

elseif (MACOS)


   target_link_libraries(acme PRIVATE z iconv idn ${COCOA} ${IOKIT})


endif ()


message(STATUS "Library Output Path at acme is : \"${LIBRARY_OUTPUT_PATH}\".")

target_link_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


# defining C Macro _acme_project
target_compile_definitions(${PROJECT_NAME} PRIVATE "_${PROJECT_NAME}_project")
target_compile_definitions(static_${PROJECT_NAME} PRIVATE "_${PROJECT_NAME}_project")



