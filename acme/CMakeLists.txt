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
   compress/_.h
   compress/compress.cpp
   compress/compress.h
   compress/uncompress.cpp
   compress/uncompress.h
   constant/_.h
   constant/code_page.h
   constant/idpool.cpp
   #exception/overflow.cpp
   #exception/range.cpp
   #exception/runtime.cpp
   #exception/archive.cpp
   #exception/archive_exception.cpp
   #exception/base.cpp
   exception/callstack.cpp
   exception/cancel.cpp
   exception/const.cpp
   exception/debug.cpp
   exception/dump.cpp
   exception/dump_context.cpp
   exception/dump_floating_point.cpp
   exception/dump_output.cpp
   exception/exception.cpp
   exception/engine.cpp
   #exception/exit.cpp
   exception/extended_status.cpp
   exception/extended_status.h
   exception/extended_transport.h
   exception/file.cpp
   exception/file.h
   exception/file_open.cpp
   exception/file_open.h
   #exception/hresult.cpp
   #exception/index_out_of_bounds.cpp
   #exception/installing.cpp
   exception/interface_only.cpp
   #exception/invalid_argument.cpp
   #exception/invalid_character.cpp
   #exception/invalid_handle.cpp
   #exception/invalid_index.cpp
   exception/io.cpp
   #exception/memory.cpp
   exception/not_implemented.cpp
   #exception/not_installed.cpp
   #exception/not_licensed.cpp
   #exception/not_supported.cpp
   #exception/operation_canceled.cpp
   #exception/os.cpp
   exception/parsing.cpp
   exception/resource.cpp
   #exception/result.cpp
   exception/serialization.cpp
   exception/serialization.h
   #exception/simple.cpp
   #exception/standard_translator.cpp
   #exception/temporary.cpp
   exception/throw.cpp
   #exception/todo.cpp
   exception/translator.cpp
   exception/translator.h
   #exception/user.cpp
   #exception/void_implementation.cpp
   #exception/wtf.cpp
   #filesystem/file/_.cpp
   filesystem/file/binary_stream.cpp
   filesystem/file/buffered_buffer.cpp
   filesystem/file/c.cpp
   filesystem/file/circular_buffer.cpp
   filesystem/file/composite.cpp
   filesystem/file/cpp.cpp
   #filesystem/file/dir.cpp
   filesystem/file/dir2.cpp
   filesystem/file/exception.cpp
   filesystem/file/file.cpp
   filesystem/file/folder.cpp
   filesystem/file/folder.h
   filesystem/file/item.cpp
   filesystem/file/item_array.cpp
   filesystem/file/memory_file.cpp
   filesystem/file/memory_map.cpp
   filesystem/file/path.cpp
   filesystem/file/seekable.cpp
   filesystem/file/serializable.cpp
   filesystem/file/serialize.cpp
   #filesystem/file/stdio_file.cpp
   filesystem/file/stream.cpp
   filesystem/file/streamable.cpp
   filesystem/file/streamable.h
   filesystem/file/streamable_composite.cpp
   filesystem/file/streamable_composite.h
   filesystem/file/string_file.cpp
   filesystem/file/text_file.cpp
   filesystem/file/text_stream.cpp
   filesystem/file/transfer.cpp
   filesystem/file/transfer.h
   filesystem/file/payload_stream.cpp
   filesystem/filesystem/acme_dir.cpp
   filesystem/filesystem/acme_dir.h
   filesystem/filesystem/acme_file.cpp
   filesystem/filesystem/acme_file.h
   filesystem/filesystem/acme_path.cpp
   filesystem/filesystem/acme_path.h
   filesystem/filesystem/file_path.cpp
   filesystem/filesystem/file_path.h
   filesystem/filesystem/listing.cpp
   filesystem/filesystem/path.cpp
   filesystem/filesystem/path_object.cpp
   graphics/draw2d/_.cpp
   graphics/draw2d/_system_color.h
   graphics/draw2d/color.cpp
   graphics/draw2d/color32.h
   graphics/draw2d/colorref_array.cpp
   graphics/draw2d/os_font_name.cpp
   include/_.cpp
   memory/alloc.cpp
   memory/allocate_mid_big.cpp
   memory/allocate_processor_cache_oriented.cpp
   memory/allocate_system_heap.cpp
   memory/allocate_x86_cache_oriented.cpp
   memory/allocation.cpp
   memory/array_memory_allocate.cpp
   memory/array_memory_allocate.h
   memory/counter.cpp
   #memory/heap.cpp
   memory/memory_allocate.cpp
   memory/memory_allocate.h
   memory/memory_management.cpp
   memory/memory_management.h
   memory/new.cpp
   #memory/plex.cpp
   #memory/plex_heap.cpp
   memory/property_memory_allocate.cpp
   memory/property_memory_allocate.h
   memory/secondary_memory_allocate.cpp
   memory/secondary_memory_allocate.h
   memory/string_memory_allocate.cpp
   memory/string_memory_allocate.h
   memory/string_memory_allocator.h
   networking/top_level_domain_list.cpp
   networking/url.cpp
   networking/url.h
   networking/url_department.cpp
   networking/url_department.h
   networking/url_domain.cpp
   networking/url_domain.h
   node/operating_system/ansi/_pthread.h
   node/operating_system/ansi/base.cpp
   node/operating_system/ansi/datetime.cpp
   node/operating_system/ansi/exception_engine.cpp
   node/operating_system/ansi/file.cpp
   node/operating_system/ansi/file_raw.cpp
   node/operating_system/ansi/file_std.cpp
   node/operating_system/ansi/language.cpp
   node/operating_system/ansi/memory.cpp
   node/operating_system/ansi/process.cpp
   node/operating_system/ansi/user.cpp
   node/operating_system/ansi/win.cpp
   node/operating_system/_const_console.h
   node/operating_system/_.cpp
   node/operating_system/argcargv.cpp
   node/operating_system/chronometer.cpp
   node/operating_system/console.cpp
   node/operating_system/debug.cpp
   node/operating_system/file.cpp
   node/operating_system/http.cpp
   node/operating_system/parallelization.cpp
   node/operating_system/process.h
   node/operating_system/time.cpp
   node/operating_system/windowing.cpp
   parallelization/_.cpp
   parallelization/condition.cpp
   parallelization/condition.h
   parallelization/condition_variable.cpp
   parallelization/condition_variable.h
   parallelization/critical_section.cpp
   parallelization/event.cpp
   #parallelization/file_change_event.cpp
   parallelization/install_mutex.cpp
   parallelization/manual_reset_event.cpp
   parallelization/multiple_lock.cpp
   parallelization/multiple_lock.h
   parallelization/mutex.cpp
   parallelization/pool.cpp
   #primitive/promise/handler1.cpp
   #primitive/promise/manager.cpp
   #primitive/promise/routine_array.cpp
   #primitive/promise/_.h
   parallelization/semaphore.cpp
   parallelization/single_lock.cpp
   parallelization/socket_event.cpp
   parallelization/task.cpp
   parallelization/thread.cpp
   parallelization/thread_os.cpp
   parallelization/waitable.cpp
   platform/_.cpp
   platform/acme_main_data.cpp
   platform/acme_main_data.h
   platform/assert.cpp
   platform/aura_str_pool.cpp
   platform/build_debug.cpp
   platform/checked.cpp
   platform/context.cpp
   platform/context.h
   platform/debug.cpp
   platform/department.cpp
   platform/department.h
   platform/display.cpp
   platform/exclusive.cpp
   platform/factory.cpp
   platform/fixed_alloc.cpp
   platform/flags.cpp
   platform/hyperlink.cpp
   platform/implementable.cpp
   platform/implementable.h
   platform/library.cpp
   platform/library.h
   platform/log.cpp
   platform/log.h
   platform/logic.cpp
   platform/lparam.cpp
   platform/main.cpp
   platform/main.h
   platform/math.cpp
   platform/message_box.cpp
   platform/message.h
   platform/muldiv64.cpp
   platform/nanosecond_timer.cpp
   platform/nanosecond_timer.h
   platform/net.cpp
   platform/node.cpp
   platform/node.h
   platform/printf.cpp
   platform/predicate_holder.cpp
   platform/predicate_holder.h
   platform/profiler.cpp
   platform/routine.cpp
   platform/routine.h
   #platform/regex.cpp
   platform/serial.cpp
   #platform/simple_trace.cpp
   #platform/sprintf.cpp
   platform/static_setup.cpp
   platform/static_setup.h
   platform/static_start.cpp
   platform/static_start_aura.cpp
   platform/system.cpp
   platform/text.cpp
   platform/timer.cpp
   platform/timer_array.cpp
   platform/timer_callback.cpp
   platform/timer_event.cpp
   platform/timer_item.cpp
   platform/timer_task.cpp
   platform/trace.cpp
   platform/trace.h
   platform/trace_category.cpp
   #platform/update.cpp
   platform/version.cpp
   #process/_.cpp
   process/_.h
   process/bidirectional_pipe.cpp
   process/bidirectional_pipe.h
   process/exit_status.cpp
   process/exit_status.h
   process/pipe.cpp
   process/pipe.h
   primitive/collection/2d_array.cpp
   primitive/collection/array.cpp
   primitive/collection/bit_array.cpp
   primitive/collection/class_sort_array.cpp
   primitive/collection/comparable_array.cpp
   primitive/collection/event_map.cpp
   primitive/collection/id_array.cpp
   primitive/collection/key_sort_array.cpp
   primitive/collection/map_misc.cpp
   primitive/collection/map_test_51778915.cpp
   primitive/collection/numeric_array.cpp
   primitive/collection/point_array.cpp
   primitive/collection/rectangle_array.cpp
   primitive/collection/sort.cpp
   primitive/collection/string_array_base.cpp
   primitive/collection/string_list.cpp
   primitive/collection/string_to_string_map.cpp
   primitive/collection/string_array.cpp
   primitive/collection/stringl.cpp
   primitive/collection/payload_array.cpp
   primitive/comparison/var_strict.cpp
   primitive/data/_.h
   primitive/data/_data.h
   primitive/data/_impl.h
   primitive/data/_tree.h
   primitive/data/container.cpp
   primitive/data/container.h
   primitive/data/data.cpp
   primitive/data/data.h
   primitive/data/item.cpp
   primitive/data/item.h
   primitive/data/listener.cpp
   primitive/data/listener.h
   primitive/data/node.cpp
   primitive/data/node.h
   primitive/data/simple_item.cpp
   primitive/data/simple_item.h
   primitive/data/tree.cpp
   primitive/data/tree.h
   primitive/data/tree_item.cpp
   primitive/data/tree_item.h
   primitive/datetime/_.cpp
   primitive/datetime/_c.cpp
   primitive/datetime/date_span.cpp
   primitive/datetime/datetime.cpp
   primitive/datetime/department.cpp
   primitive/datetime/department.h
   primitive/datetime/filetime.cpp
   primitive/datetime/filetime_span.cpp
   primitive/datetime/microsecond_sleep.cpp
   primitive/datetime/microsecond_sleep.h
   primitive/datetime/mktime.cpp
   primitive/datetime/time.cpp
   primitive/datetime/time_span.cpp
   primitive/datetime/result.cpp
   primitive/datetime/result.h
   primitive/datetime/zonetime.cpp
   primitive/duration/duration/duration.cpp
   primitive/duration/duration/duration.h
   primitive/duration/duration/_.h
   primitive/duration/integral/_.h
   primitive/duration/floating/_.h
   primitive/geometry2d/_.cpp
   primitive/geometry2d/_shape.cpp
   primitive/geometry2d/_shape.h
   primitive/geometry2d/geometry.cpp
   primitive/geometry2d/point.cpp
   primitive/geometry2d/rectangle.cpp
   primitive/geometry2d/shape.cpp
   primitive/geometry2d/size.cpp
   primitive/geometry2d/types.cpp
   primitive/geometry3d/box.cpp
   primitive/geometry3d/location.cpp
   primitive/mathematics/_.cpp
   primitive/mathematics/binary_operation.cpp
   primitive/mathematics/cast.inl
   primitive/mathematics/cvt.cpp
   primitive/mathematics/cvt_g.cpp
   primitive/mathematics/int_biunique.cpp
   primitive/mathematics/mathematics.cpp
   primitive/mathematics/mathematics.h
   primitive/mathematics/mkint_c.cpp
   primitive/mathematics/natural.cpp
   primitive/mathematics/number.cpp
   primitive/mathematics/number_double.cpp
   primitive/mathematics/number_float.cpp
   primitive/mathematics/number_integer.cpp
   primitive/mathematics/random_number_generator.cpp
   primitive/mathematics/scalar.cpp
   primitive/mathematics/value.cpp
   primitive/primitive/_.cpp
   #primitive/promise/subject.cpp
   primitive/primitive/application_bias.cpp
   primitive/primitive/bit.cpp
   primitive/primitive/block.cpp
   #primitive/primitive/block.inl
   #primitive/promise/context.cpp
   primitive/primitive/command.cpp
   primitive/primitive/context_object_traits.cpp
   primitive/primitive/edit.cpp
   primitive/primitive/element.cpp
   primitive/primitive/element.h
   primitive/primitive/estatus.cpp
   primitive/primitive/element_array.cpp
   primitive/primitive/element_array.h
   primitive/primitive/enum_bitset.h
   primitive/primitive/enumeration.h
   primitive/primitive/factory.cpp
   #primitive/promise_predicate/predicate_function.cpp
   #primitive/promise/process.cpp
   primitive/primitive/handler.cpp
   primitive/primitive/id.cpp
   primitive/primitive/id_array.cpp
   primitive/primitive/material_object.cpp
   primitive/primitive/material_object.h
   primitive/primitive/id_space.cpp
   primitive/primitive/interlocked.h
   primitive/primitive/interlocked_count.h
   primitive/primitive/interlocked_long_pulse.cpp
   primitive/primitive/object.cpp
   primitive/primitive/object.h
   primitive/primitive/property_object.cpp
   primitive/primitive/property_object.h
   primitive/primitive/linked_property.cpp
   primitive/primitive/linked_property.h
   primitive/primitive/match.cpp
   primitive/primitive/material_object.cpp
   primitive/primitive/material_object.h
   primitive/primitive/matter.cpp
   primitive/primitive/memory.cpp
   primitive/primitive/memory_base.cpp
   primitive/primitive/memory_c.cpp
   primitive/primitive/memory_container.cpp
   primitive/primitive/object.cpp
   primitive/primitive/object.h
   #primitive/promise/routine.cpp
   #primitive/promise/promise.cpp
   primitive/primitive/property.cpp
   primitive/primitive/property_object.cpp
   primitive/primitive/property_object.h
   primitive/primitive/property_set.cpp
   primitive/primitive/property_set_composite.cpp
   primitive/primitive/property_set_papaya.cpp
   primitive/primitive/element.cpp
   primitive/primitive/element.h
   primitive/primitive/runnable.cpp
   primitive/primitive/shared_memory.cpp
   primitive/primitive/traits.cpp
   primitive/primitive/type.cpp
   primitive/primitive/payload.cpp
   primitive/primitive/tracer.cpp
   primitive/primitive/tracer.h
   primitive/primitive/var_element.cpp
   primitive/primitive/virtual_memory.cpp
   primitive/primitive/work.cpp
   primitive/promise/signalization.cpp
   primitive/promise/signalization.h
   primitive/string/_.h
   primitive/string/_base.h
   primitive/string/_base_impl.h
   primitive/string/_.cpp
   primitive/string/_c.cpp
   primitive/string/_c_trait_ansi.cpp
   primitive/string/_c_trait_wide.cpp
   primitive/string/_conv_ansi.cpp
   primitive/string/_unicode.cpp
   primitive/string/_unicode16.cpp
   primitive/string/_unicode16_32.cpp
   primitive/string/_unicode32.cpp
   primitive/string/base64.cpp
   primitive/string/bstring.cpp
   primitive/string/ch.cpp
   primitive/string/ch_class.cpp
   primitive/string/dup.cpp
   primitive/string/from_integer.cpp
   primitive/string/hex.cpp
   primitive/string/international.cpp
   primitive/string/manager.cpp
   primitive/string/parse.cpp
   primitive/string/simple.cpp
   primitive/string/str.cpp
   primitive/string/string_ansi.cpp
   primitive/string/string_wide.cpp
   primitive/string/string_wide_conversion.cpp
   primitive/string/stringtow.cpp
   primitive/string/strw.cpp
   primitive/string/strx.cpp
   primitive/string/sz.cpp
   primitive/string/to_integer.cpp
   primitive/string/tokenizer.cpp
   primitive/string/x.cpp
   primitive/text/context.cpp
   primitive/text/context.h
   primitive/text/data.h
   primitive/text/data.cpp
   primitive/text/international.cpp
   primitive/text/international.h
   primitive/text/international_locale_schema.cpp
   primitive/text/international_locale_schema.h
   primitive/text/text.cpp
   primitive/text/text.h
   primitive/text/translator.cpp
   primitive/text/translator.h
   regular_expression/_regular_expression.h
   regular_expression/context.cpp
   regular_expression/context.h
   regular_expression/regular_expression.cpp
   regular_expression/regular_expression.h
   regular_expression/topic.cpp
   regular_expression/topic.h
   subject/handler.cpp
   subject/handler.h
   subject/item.cpp
   subject/item.h
   subject/subject.cpp
   subject/subject.h
   user/check.cpp
   user/check.h
   user/element.cpp
   user/element.h
   user/ewindowflag.h
   user/os_colors.cpp
   user/os_theme_colors.cpp
   user/os_theme_colors.h
   user/text.cpp
   user/text.h
   user/theme_colors.h
   _.cpp
   __matter_ca2.cpp
   context_glx.cpp
   framework.cpp
   promise.cpp
   update.h)


list(APPEND library_source
   #"os/ios/window_boot 2.h"
   #exception/debug.h
   #node/android/buffer.h
   #os/ansios/parallelization.h
   #os/x11/_.h
   #os/x11/x11_button.h
   #os/x11/x11_exception.h
   #os/x11/x11_hook.h
   #os/x11/x11_keyboard.h
   #os/x11/x11_message_box.h
   #os/x11/x11_simple_ui_display.h
   #os/xcb/_xcb.h
   #os/xcb/xcb_hook.h
   #parallelization/file_change_event.h
   _.h
   _defer.h
   _start.h
   application.h
   astr.h
   axispolicy/_.h
   axispolicy/_c.h
   axispolicy/policy_objc.h
   axispolicy/policy_objcpp.h
   axispolicy/policy_winrt.h
   callback.h
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
   console.h
   constant/GLOBAL_ID.h
   constant/_constant.h
   constant/character_set.h
   constant/check.h
   constant/context.h
   constant/future.h
   constant/id.h
   constant/idpool.h
   constant/impact.h
   constant/message.h
   constant/routine.h
   constant/simple_command.h
   constant/source.h
   constant/status.h
   constant/status_range_authentication.h
   constant/thread.h
   constant/timer.h
   exception/_.h
   exception/_c.h
   #exception/_const.h
   exception/_dump_context.h
   #exception/assert.h
   #exception/base.h
   exception/call_stack.h
   exception/callstack.h
   exception/cancel.h
   #exception/debug_stream.h
   exception/dump_context.h
   exception/engine.h
   exception/exception.h
   exception/exception2.h
   exception/exit.cpp
   exception/exit.h
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
   exception/standard.h
   #exception/system.h
   #exception/temporary.h
   exception/throw.h
   #exception/todo.h
   #exception/translator.cpp
   exception/translator.h
   exception/trap.h
   #exception/unhandled_report.h
   #exception/user.h
   #exception/void_implementation.h
   filesystem/_impl.h
   filesystem/file/_.h
   filesystem/file/___serialization_draft.h
   filesystem/file/___serialization_draft001.h
   filesystem/file/_c.h
   filesystem/file/_const.h
   filesystem/file/_defer.h
   filesystem/file/_defer_payload_stream.h
   filesystem/file/_file.h
   filesystem/file/_impl.h
   filesystem/file/_papaya.h
   filesystem/file/_papaya_impl.h
   filesystem/file/_serializable_impl.h
   filesystem/file/_stream_process_impl.h
   filesystem/file/_text_stream_impl.h
   filesystem/file/_payload_stream_impl.h
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
   filesystem/file/primitive.h
   filesystem/file/serializable.h
   filesystem/file/serialize.h
   filesystem/file/status.h
   filesystem/file/stdio_file.cpp
   filesystem/file/stdio_file.h
   filesystem/file/stream.h
   filesystem/file/streamable.h
   filesystem/file/string_file.h
   filesystem/file/text_file.h
   filesystem/file/text_stream.h
   filesystem/file/transfer_file.h
   filesystem/file/payload_stream.h
   #filesystem/filesystem.h
   #filesystem/filesystem/_.h
   filesystem/filesystem/_impl.h
   filesystem/filesystem/listing.h
   filesystem/filesystem/path.h
   filesystem/filesystem/path_object.h
   framework.h
   framework_c.h
   graphics/draw2d/_.h
   graphics/draw2d/_const.h
   graphics/draw2d/color.h
   graphics/draw2d/colorref_array.h
   id.h
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
   inline/application/linux.h
   inline/application.h
   inline/application_common.h
   inline/console.h
   inline/console_common.h
   inline/library.h
   ios_aura/ios_aura.h
   library.h
   memory/_heap.h
   memory/align_byte_count.h
   memory/allocate.h
   memory/allocate_processor_cache_oriented.h
   memory/allocation.h
   memory/heap_.h
   memory/heap_c.h
   memory/heap_item.h
   memory/heap_item_array.h
   memory/heap_memory.h
   memory/malloc.h
   memory/memory.h
   memory/memory_allocator.h
   memory/new.h
   memory/os_alloc.h
   #memory/plex.h
   #memory/plex_heap1.h
   #memory/plex_heap_impl1.h
   #node/_.h
   #node/_node2.h
   node/android/Kerr/LocalMemory.h
   node/android/Kerr/kerr.h
   node/android/_.h
   node/android/_android.h
   node/android/android1.h
   node/android/application.h
   node/android/
   node/android/file.h
   node/android/implementation.h
   node/android/internal.h
   node/android/thread.h
   node/serial.h
   node/operating_system/_.h
   node/operating_system/_application.h
   node/operating_system/_impl.h
   node/operating_system/_operating_system.h
   node/operating_system/_user.h
   node/operating_system/android/_.h
   node/operating_system/android/_android.h
   node/operating_system/android/_c.h
   node/operating_system/android/_os_impl.h
   node/operating_system/android/_os_local.h
   node/operating_system/android/_os_object.h
   node/operating_system/android/_os_remote.h
   node/operating_system/android/cross_win_file.h
   node/operating_system/android/cross_win_gdi.h
   node/operating_system/android/cross_win_gdi_internal.h
   node/operating_system/android/exception_engine.h
   node/operating_system/android/file.h
   node/operating_system/android/graphics.h
   node/operating_system/android/internal.h
   node/operating_system/android/process.h
   node/operating_system/ansi/_.h
   node/operating_system/ansi/_ansi.h
   node/operating_system/ansi/_c.h
   node/operating_system/ansi/ansios_file.h
   node/operating_system/ansi/binreloc.h
   node/operating_system/ansi/callstack.h
   node/operating_system/ansi/datetime_c.h
   node/operating_system/ansi/exception_engine.h
   node/operating_system/ansi/file.h
   node/operating_system/ansi/file_c.h
   node/operating_system/ansi/file_raw.h
   node/operating_system/ansi/pmutex_lock.h
   node/operating_system/ansi/pthread.cpp
   node/operating_system/ansi/semun.h
   node/operating_system/file.h
   node/operating_system/graphics.h
   node/operating_system/ios/_.h
   node/operating_system/ios/_c.h
   node/operating_system/ios/_ios.h
   node/operating_system/ios/_m.h
   node/operating_system/ios/_mm.h
   node/operating_system/ios/base_internal.h
   node/operating_system/ios/cross_win_gdi.h
   node/operating_system/ios/engine.h
   node/operating_system/ios/gen_1.h
   node/operating_system/ios/implementation.h
   node/operating_system/ios/internal.h
   node/operating_system/ios/mm_graphics.h
   node/operating_system/ios/mm_oswindow.h
   node/operating_system/ios/oswindow_data.h
   node/operating_system/ios/parallelization.h
   node/operating_system/ios/process.h
   node/operating_system/ios/window.h
   node/operating_system/ios/window_boot.h
   node/operating_system/ios/window_impl.h
   node/operating_system/ios/windowing.h
   node/operating_system/os_windowing2.h
   node/operating_system/parallelization.h
   node/operating_system/posix/mq_base.h
   node/operating_system/posix/time.h
   node/operating_system/solaris/linux_internal.h
   node/operating_system/solaris/solaris.h
   node/operating_system/solaris/solaris_cairo_keep.h
   node/operating_system/solaris/solaris_cross_win_file.h
   node/operating_system/solaris/solaris_cross_win_gdi.h
   node/operating_system/solaris/solaris_cross_win_gdi_internal.h
   node/operating_system/solaris/solaris_debug.h
   node/operating_system/solaris/solaris_file.h
   node/operating_system/solaris/solaris_file_watcher.h
   node/operating_system/solaris/solaris_graphics.h
   node/operating_system/solaris/solaris_http.h
   node/operating_system/solaris/solaris_http_lib.h
   node/operating_system/solaris/solaris_internal.h
   node/operating_system/solaris/solaris_process.h
   node/operating_system/solaris/solaris_simple_ui.h
   node/operating_system/solaris/solaris_solaris.h
   node/operating_system/solaris/solaris_user_impl.h
   node/operating_system/solaris/solaris_window_xlib.h
   node/operating_system/text.h
   node/operating_system/time.h
   node/operating_system/user.h
   node/operating_system/universal_windows/_.h
   #node/operating_system/universal_windows/_uwp.h
   #node/operating_system/universal_windows/_winrt.h
   node/operating_system/universal_windows/base_file.h
   node/operating_system/universal_windows/exception_engine.h
   #ode/operating_system/universal_windows/file_winrt.h
   #node/operating_system/universal_windows/gdi_winrt.h
   node/operating_system/universal_windows/host_interaction.h
   node/operating_system/universal_windows/metrowin_metrowin.h
   node/operating_system/universal_windows/parallelization.h
   node/operating_system/universal_windows/parallelization_winrt.h
   node/operating_system/universal_windows/process.h
   node/operating_system/universal_windows/simple_hold_handle.h
   node/operating_system/universal_windows/simple_ui.h
   node/operating_system/universal_windows/sockets.h
   node/operating_system/windows/_.h
   #node/operating_system/windows/_c.h
   node/operating_system/windows/_windows.h
   #node/operating_system/windows/_windows_impl.h
   #node/operating_system/windows/api.h
   #os/windows/callstack.h
 # node/operating_system/windows/d2d1_1.h
 # node/operating_system/windows/dir.h
 # node/operating_system/windows/environment_variable.h
 # node/operating_system/windows/exception_engine.h
 # node/operating_system/windows/extract_icon.h
 # node/operating_system/windows/file.h
 # node/operating_system/windows/handle.h
 # node/operating_system/windows/implementation.h
 # node/operating_system/windows/internal.h
 # node/operating_system/windows/itemidlist.h
 # node/operating_system/windows/parallelization.h
 # node/operating_system/windows/port_forward.h
 # node/operating_system/windows/print_job.h
 # node/operating_system/windows/printer.h
 # node/operating_system/windows/process.h
 # node/operating_system/windows/process_data.h
 # node/operating_system/windows/registry.h
 # node/operating_system/windows/shell1.h
 # node/operating_system/windows/simple_hold_handle.h
 # node/operating_system/windows/utils.h
 # node/operating_system/windows/windowing.h
 # node/operating_system/windows_common/_.h
 # node/operating_system/windows_common/_c.h
 # node/operating_system/windows_common/_default_dll_impl.h
 # node/operating_system/windows_common/_file_c.h
 # node/operating_system/windows_common/_unicode_c.h
 # node/operating_system/windows_common/bstring.h
 # node/operating_system/windows_common/comptr.h
 # node/operating_system/windows_common/cotaskptr.h
 # node/operating_system/windows_common/file.h
 # #os/windows_common/graphics.h
 # node/operating_system/windows_common/new_api.h
 # node/operating_system/windows_common/parallelization.h
 # node/operating_system/windows_common/variant.h
 # node/operating_system/winpr_input.h
   parallelization/_.h
   parallelization/_impl.h
   parallelization/_thread_os_create_impl.h
   parallelization/_types.h
   parallelization/common.h
   parallelization/condition.h
   parallelization/create_thread.h
   parallelization/critical_section.h
   #parallelization/data.h
   parallelization/event.h
   parallelization/initial_single_lock.h
   parallelization/manual_reset_event.h
   parallelization/message_queue.cpp
   parallelization/message_queue.h
   parallelization/message_queue_global.cpp
   parallelization/mutex.h
   parallelization/pool.h
   parallelization/semaphore.h
   parallelization/set_event_on_exit.h
   parallelization/single_lock.h
   parallelization/socket_event.h
   parallelization/synchronization_array.cpp
   parallelization/synchronization_array.h
   parallelization/synchronous_lock.h
   parallelization/synchronization_object.cpp
   parallelization/synchronization_object.h
   parallelization/synchronization_result.cpp
   parallelization/synchronization_result.h
   parallelization/synchronized_process.cpp
   parallelization/synchronized_process.h
   parallelization/synchronized_routine.cpp
   parallelization/synchronized_routine.h
   parallelization/synchronized_task.cpp
   parallelization/synchronized_task.h
   parallelization/task.h
   parallelization/thread_impl.h
   parallelization/thread_os.h
   parallelization/thread_parameter.h
   parallelization/tools.cpp
   parallelization/tools.h
   parallelization/zaa_update_task.h
   parallelization/zaa_update_task_item.h
   parallelization/zaa_update_task_item_array.h
   platform/_features.h
   platform/_generic_object_constructor_impl.h
   platform/_global.h
   platform/_impl.h
   platform/_platform.h
   platform/acme_str_pool.h
   #platform/all.h
   #platform/acme.h
   #platform/aura_regex.h
   platform/auto.h
   platform/auto_pointer.h
   platform/class.h
   platform/cmp.h
   platform/cmp2.h
   platform/common.h
   platform/const.h
   platform/constraint.h
   platform/debug.h
   platform/definition.h
   platform/display.h
   platform/enum.h
   platform/error.h
   platform/exclusive.h
   platform/factory.h
   platform/filestream.h
   platform/fixed_alloc.h
   platform/fixed_alloc_impl.h
   platform/flags.h
   platform/hyperlink.h
   platform/keep.h
   platform/keep_true.h
   platform/less.h
   platform/logic.h
   platform/lparam.h
   platform/main.h
   #platform/message_box.h
   platform/muldiv32.h
   platform/muldiv64.h
   platform/nanosecond_timer.h
   platform/net.h
   platform/number.h
   platform/object_reference_count_debug.cpp
   platform/object_reference_count_debug.h
   platform/object_reference_count_debug_impl.h
   platform/object_type_counter.cpp
   platform/object_type_counter.h
   platform/printf.h
   platform/profiler.h
   #platform/regex.h
   platform/restore.h
   platform/sequence.cpp
   platform/sequence.h
   platform/serial.h
   #platform/serial_impl.h
   #platform/simple_app.h
   platform/simple_log.cpp
   platform/simple_log.h
   #platform/sprintf.h
   platform/static_start.h
   platform/static_start_internal.h
   platform/status.h
   platform/string_exchange.h
   platform/system.h
   #platform/system_impl.h
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
   platform/user_parent.h
   platform/version.h
   primitive/api/api.h
   primitive/api/api_rotate.h
   primitive/collection/_.h
   primitive/collection/_array_base_impl.h
   primitive/collection/_array_impl.h
   primitive/collection/_array_impl2.h
   primitive/collection/_collection_impl1.h
   primitive/collection/_collection_impl2.h
   primitive/collection/_fifo_map_impl.h
   primitive/collection/_list_impl.h
   primitive/collection/_map_impl.h
   primitive/collection/_papaya.h
   primitive/collection/_papaya_array.h
   primitive/collection/_papaya_array2d_impl.h
   primitive/collection/_papaya_array_impl.h
   primitive/collection/_papaya_heap.h
   primitive/collection/_papaya_impl.h
   primitive/collection/_papaya_map.h
   primitive/collection/_papaya_map_impl.h
   primitive/collection/_papaya_weak.h
   primitive/collection/_point_array.h
   primitive/collection/_raw_array_impl.h
   primitive/collection/_raw_array_impl2.h
   primitive/collection/_sort_array_impl.h
   primitive/collection/_sort_map_impl.h
   primitive/collection/_string_array_impl.h
   primitive/collection/address_array.h
   primitive/collection/array.h
   primitive/collection/array_base.h
   primitive/collection/attrib_map.h
   primitive/collection/back_insert_iterator.h
   primitive/collection/base_2array.h
   primitive/collection/base_enum.h
   primitive/collection/bit_array.h
   primitive/collection/bitset.h
   primitive/collection/common.h
   primitive/collection/comparable_array.h
   primitive/collection/comparable_eq_array.h
   primitive/collection/comparable_eq_list.h
   primitive/collection/comparable_list.h
   primitive/collection/comparable_primitive_array.h
   primitive/collection/comparable_raw_array.h
   primitive/collection/composite_array.h
   primitive/collection/decl.h
   primitive/collection/deque.h
   primitive/collection/fifo_map.h
   primitive/collection/file_path_map.h
   primitive/collection/forward.h
   primitive/collection/insert_iterator.h
   primitive/collection/int_map.h
   primitive/collection/iterable.h
   primitive/collection/iterator.h
   primitive/collection/list.h
   primitive/collection/logic_array.h
   primitive/collection/map.h
   primitive/collection/map_association.h
   primitive/collection/map_to_smart_pointer.h
   primitive/collection/numeric_array.h
   primitive/collection/numeric_array_range.h
   primitive/collection/packset.h
   primitive/collection/pair.h
   primitive/collection/pointer_array.h
   primitive/collection/pointer_array_process.h
   primitive/collection/priority_queue.h
   primitive/collection/ptr_array.h
   primitive/collection/queue.h
   primitive/collection/raw_array_decl.h
   primitive/collection/runnable_array.h
   primitive/collection/set.h
   primitive/collection/sort.h
   primitive/collection/sort_array.h
   primitive/collection/sort_list.h
   primitive/collection/sort_map.h
   primitive/collection/spreadset.h
   primitive/collection/stack.h
   primitive/collection/std_iterator.h
   primitive/collection/std_pair.h
   primitive/collection/strid_map.h
   primitive/collection/string_array_base.h
   primitive/collection/string_iterable.h
   primitive/collection/string_list.h
   primitive/collection/string_map.h
   primitive/collection/string_to_string_map.h
   primitive/collection/stringl.h
   #primitive/collection/template.h
   primitive/collection/unique_array.h
   primitive/collection/payload_array.h
   primitive/comparison/_.h
   primitive/comparison/_c.h
   primitive/comparison/binary.h
   primitive/comparison/compare.h
   primitive/comparison/equals.h
   primitive/comparison/hash.h
   primitive/comparison/less.h
   primitive/comparison/md5.h
   primitive/comparison/sign.h
   primitive/comparison/var_strict.h
   primitive/datetime/_.h
   primitive/datetime/_c.h
   primitive/datetime/_impl.h
   primitive/datetime/date_span.h
   primitive/datetime/filetime.h
   primitive/datetime/filetime_span.h
   primitive/datetime/system_time.cpp
   primitive/datetime/time.h
   primitive/datetime/time_span.h
   primitive/datetime/zonetime.h
   primitive/geometry2d/_.h
   primitive/geometry2d/_collection.h
   primitive/geometry2d/_collection_bounding_rect.h
   primitive/geometry2d/_collection_contains.h
   primitive/geometry2d/_defer.h
   primitive/geometry2d/_impl.h
   primitive/geometry2d/_rect_impl.h
   primitive/geometry2d/_size_impl.h
   primitive/geometry2d/_struct.h
   primitive/geometry2d/align.h
   primitive/geometry2d/angle.h
   primitive/geometry2d/arc.h
   primitive/geometry2d/bounding_rect.h
   primitive/geometry2d/collection.h
   primitive/geometry2d/contains.h
   primitive/geometry2d/geometry.h
   primitive/geometry2d/line.h
   primitive/geometry2d/lines.h
   primitive/geometry2d/ellipse.h
   primitive/geometry2d/point.h
   primitive/geometry2d/point_array.h
   primitive/geometry2d/polygon.h
   primitive/geometry2d/rectangle.h
   primitive/geometry2d/rectangle_array.h
   primitive/geometry2d/shape.h
   primitive/geometry2d/shape_array.h
   primitive/geometry2d/size.h
   primitive/geometry2d/size_array.h
   primitive/geometry2d/types.h
   primitive/geometry3d/_.h
   primitive/geometry3d/box.h
   primitive/geometry3d/dimension.h
   primitive/geometry3d/location.h
   primitive/geometry3d/quaternions.h
   primitive/mathematics/_.h
   primitive/mathematics/_impl.h
   primitive/mathematics/binary_operation.h
   primitive/mathematics/c_number.h
   primitive/mathematics/cast.h
   primitive/mathematics/classes.h
   primitive/mathematics/complex.h
   primitive/mathematics/count.h
   primitive/mathematics/filestream.h
   primitive/mathematics/index.h
   primitive/mathematics/math_clip.h
   primitive/mathematics/math_int_biunique.h
   primitive/mathematics/mkint_c.h
   primitive/mathematics/natural.h
   primitive/mathematics/number.h
   primitive/mathematics/number_double.h
   primitive/mathematics/number_float.h
   primitive/mathematics/number_integer.h
   primitive/mathematics/numeric_info.h
   primitive/mathematics/objects.h
   primitive/mathematics/random_number_generator.h
   primitive/mathematics/scalar.h
   primitive/mathematics/scalar_enum.h
   primitive/mathematics/static_numeric_info.h
   primitive/mathematics/std_template.h
   primitive/mathematics/value.h
   primitive/primitive/_.h
   primitive/primitive/_c_memory.h
   primitive/primitive/_property_object_impl.h
   primitive/primitive/_defer.h
   primitive/primitive/_factory_impl.h
   primitive/primitive/_factory_prefix.h
   primitive/primitive/_id_impl.h
   primitive/primitive/_impl.h
   primitive/primitive/_memory.h
   primitive/primitive/_papaya.h
   primitive/primitive/_papaya_impl.h
   primitive/primitive/_payload_impl.h
   primitive/primitive/action_context.h
   #primitive/primitive/application_bias.h
   primitive/primitive/atomic.h
   primitive/primitive/bit.h
   primitive/primitive/block.h
   #primitive/primitive/collection.h
   primitive/primitive/collection_file.h
   #primitive/primitive/command.h
   primitive/primitive/compare_predicate.h
   #primitive/primitive/edit.h
   primitive/primitive/element_array.h
   primitive/primitive/enumeration.h
   primitive/primitive/enumeration.h
   primitive/primitive/eobject.h
   primitive/primitive/estatus.h
   primitive/primitive/factory.h
   primitive/primitive/id.h
   primitive/primitive/id_array.h
   primitive/primitive/id_space.h
   primitive/primitive/interlocked_long_pulse.h
   #primitive/primitive/layered.h
   primitive/primitive/logic.h
   primitive/primitive/malloc.h
   primitive/primitive/map.h
   primitive/primitive/match.h
   primitive/primitive/matter.h
   primitive/primitive/member.h
   primitive/primitive/memory.h
   primitive/primitive/memory_base.h
   primitive/primitive/memory_container.h
   primitive/primitive/natural.h
   primitive/primitive/number.h
   primitive/primitive/papaya.h
   primitive/primitive/payload.h
   primitive/primitive/pointer.h
   primitive/primitive/pointer2.h
   #primitive/primitive/primitive_update.h
   primitive/primitive/property.h
   primitive/primitive/property_set.h
   primitive/primitive/property_set_papaya.h
   primitive/primitive/request_interface.h
   #primitive/primitive/request_signal.h
   primitive/primitive/runnable.h
   primitive/primitive/shared_memory.h
   primitive/primitive/simple_object.h
   primitive/primitive/stick.h
   primitive/primitive/str.h
   primitive/primitive/trait.h
   primitive/primitive/trait_predicate.h
   primitive/primitive/traits.h
   primitive/primitive/type.h
   primitive/primitive/uid.h
   primitive/primitive/util.h
   primitive/primitive/value.h
   primitive/primitive/var2.h
   primitive/primitive/virtual_memory.h
   primitive/primitive/work.h
   #primitive/promise/context.h
   #primitive/promise/handler1.h
   #primitive/promise/manager.h
   #primitive/promise/promise.h
   #primitive/promise/promise1.h
   #primitive/promise/routine.h
   #primitive/promise/routine_array.h
   #primitive/promise/subject.h
   #primitive/promise_predicate/predicate_function_pointer.h
   #primitive/promise_predicate/predicate_process.h
   #primitive/promise_predicate/predicate_function.cpp
   #primitive/promise_predicate/predicate_holder.cpp
   #primitive/promise_predicate/predicate_holder.h
   #primitive/promise_predicate/synchronized_predicate_routine.h
   primitive/string/_.h
   primitive/string/___ch_impl.h
   primitive/string/__c_ansi.h
   primitive/string/__c_ansi_impl.h
   primitive/string/__c_wd16.h
   primitive/string/__c_wd16_impl.h
   primitive/string/__c_wd32.h
   primitive/string/__c_wd32_impl.h
   primitive/string/__c_wide.h
   primitive/string/__c_wide_impl.h
   primitive/string/_base.h
   primitive/string/_base_impl.h
   primitive/string/_c.h
   primitive/string/_c_impl.h
   primitive/string/_c_inline.h
   primitive/string/_c_str.h
   primitive/string/_c_str_impl.h
   primitive/string/_c_trait.h
   primitive/string/_c_trait_ansi.h
   primitive/string/_c_trait_ansi_impl.h
   primitive/string/_c_trait_impl.h
   primitive/string/_c_trait_wd16.h
   primitive/string/_c_trait_wd16_impl.h
   primitive/string/_c_trait_wd32.h
   primitive/string/_c_trait_wd32_impl.h
   primitive/string/_c_trait_wide.h
   primitive/string/_c_trait_wide_impl.h
   primitive/string/_c_unicode.h
   primitive/string/_compare.h
   primitive/string/_compare_impl.h
   primitive/string/_conv.h
   primitive/string/_conv_ansi.h
   primitive/string/_conv_ansi_impl.h
   primitive/string/_defer.h
   primitive/string/_impl.h
   primitive/string/_impl_prio.h
   primitive/string/_international.h
   primitive/string/_natural.h
   primitive/string/_str.h
   primitive/string/_str_impl.h
   primitive/string/_string_wide.h
   primitive/string/_trait.h
   primitive/string/_trait_ansi.h
   primitive/string/_trait_ansi_impl.h
   primitive/string/_trait_impl.h
   primitive/string/_trait_wd16.h
   primitive/string/_trait_wd16_impl.h
   primitive/string/_trait_wd32.h
   primitive/string/_trait_wd32_impl.h
   primitive/string/_uhash.h
   primitive/string/_unicode.h
   primitive/string/_unicode_impl.h
   primitive/string/base64.h
   primitive/string/bstr.h
   primitive/string/bstring.h
   primitive/string/ch.h
   primitive/string/ch_class.h
   primitive/string/composite.h
   primitive/string/from_integer.h
   primitive/string/hex.h
   primitive/string/international.h
   primitive/string/international2.h
   primitive/string/parse.h
   primitive/string/static_string.h
   primitive/string/stdstring.h
   primitive/string/string_file.h
   primitive/string/string_inst.h
   primitive/string/string_wide_conversion.h
   primitive/string/stringtow.h
   primitive/string/sz.h
   primitive/string/to_integer.h
   primitive/string/tokenizer.h
   primitive/string/x.h
   primitive/string/x/x_charcategory.h
   primitive/string/x/x_charcategory2.h
   primitive/string/x/x_charcategory_names.h
   primitive/string/x/x_defines.h
   primitive/string/x/x_encodings.h
   primitive/string/x/x_tables.h
   procedure.h
   process/main.cpp
   template/list.h
   update.h
   user/_.h
   user/_const.h
   user/_const_key.h
   user/os_colors.h
   version/version.config.h
   version/version.h
   )


if (UWP)
   list(APPEND library_source
      exception/winrt/engine_winrt.cpp
      node/universal_windows/error.cpp
      node/universal_windows/_factory.cpp
      node/universal_windows/file.cpp
      node/universal_windows/file_find.cpp
      node/universal_windows/native_buffer.cpp
      node/universal_windows/timer.cpp
      node/universal_windows/util.cpp
      os/universal_windows/_.cpp
      os/universal_windows/_os_metrowin.cpp
      os/universal_windows/application_system_run.cpp
      os/universal_windows/aura.cpp
      os/universal_windows/debug.cpp
      os/universal_windows/direct2d_tls.cpp
      os/universal_windows/dpi.cpp
      os/universal_windows/dummy_ipc.cpp
      os/universal_windows/exception_engine.cpp
      os/universal_windows/file.cpp
      os/universal_windows/file_memory_map.cpp
      os/universal_windows/graphics.cpp
      os/universal_windows/language.cpp
      os/universal_windows/lock.cpp
      os/universal_windows/main.cpp
      os/universal_windows/parallelization.cpp
      os/universal_windows/os_message_box.cpp
      os/universal_windows/process.cpp
      os/universal_windows/sockets.cpp
      os/universal_windows/time.cpp
      os/universal_windows/user.cpp)

   list(APPEND library_source
      node/universal_windows/exception.h
      node/universal_windows/
      node/universal_windows/file.h
      node/universal_windows/file_find.h
      node/universal_windows/native_buffer.h
      node/universal_windows/net/net_address.h
      node/universal_windows/_.h
      node/universal_windows/_uwp.h
      )

endif ()


if (WIN32)

   list(APPEND library_source
#      node/windows/console.cpp
#      node/windows/_factory.cpp
#      node/windows/file.cpp
#      node/windows/file_find.cpp
#      node/windows/pipe.cpp
#      node/windows/registry.cpp
#      node/windows/serial.cpp
#      node/windows/timer.cpp
#      node/windows/trace.cpp
#      node/windows/uac_tools.cpp
#      node/windows/windows.cpp
#      node/windows/windows_desktop.cpp
#      os/windows/_.cpp
#      os/windows/_ansi.cpp
#      os/windows/_wd16.cpp
#      os/windows/_wd32.cpp
#      os/windows/ansi_file.cpp
#      os/windows/api.cpp
#      os/windows/application.cpp
      #os/windows/application_system_run.cpp
      #os/windows/callstack.cpp
#      os/windows/debug.cpp
#      os/windows/dir.cpp
#      os/windows/environment_variable.cpp
#      os/windows/exception_engine.cpp
#      os/windows/extract_icon.cpp
#      os/windows/file.cpp
      #os/windows/gdiplus.cpp
#      os/windows/internal.cpp
#      os/windows/itemidlist.cpp
#      os/windows/language.cpp
#      os/windows/library.cpp
      #os/windows/list_serial_ports.cpp
      #os/windows/local_memory_map.cpp
#      os/windows/lock.cpp
#      os/windows/main.cpp
#      os/windows/message_loop.cpp
#      os/windows/printer.cpp
#      os/windows/process.cpp
#      os/windows/registry.cpp
#      os/windows/simple_app.cpp
#      os/windows/parallelization.cpp
#      os/windows/time.cpp
#      os/windows/user.cpp
#      os/windows/util.cpp
#      os/windows/windowing.cpp
      #node/windows/base/
      #node/windows/base/implementation.h
      #node/windows/base/print_job.h
      #node/windows/base/_windows.h
      #node/windows/console.h
      #node/windows/exception.h
      #node/windows/
      #node/windows/file.h
      #node/windows/file_find.h
      #node/windows/pipe.h
      #node/windows/registry.h
      #node/windows/serial.h
      #node/windows/uac_tools.h
      #node/windows/user.h
      #node/windows/_.h
      #node/windows/_node_windows.h
      #node/windows/_node_windows_private.h
      #node/windows/_windows.h
      )
else ()

   list(APPEND library_source
      #node/posix/file_memory_map.cpp
      #node/posix/file_memory_map.h
      node/operating_system/ansi/dir.cpp
      node/operating_system/ansi/parallelization.cpp
      node/operating_system/cross/windows/user.cpp
      node/operating_system/cross/windows/file.cpp
      node/operating_system/cross/windows/dir.cpp
      node/operating_system/cross/windows/time.cpp
      #os/cross/windows/crt.cpp
      #os/cross/windows/crt_debug.cpp
      #os/cross/windows/datetime.cpp
      #os/cross/windows/error.cpp
      #os/cross/windows/locale.cpp
      #os/cross/windows/shared_memory.cpp
      #os/cross/windows/thread_local_storage.cpp
      #os/cross/windows/ansios_message_loop.cpp
      #os/cross/windows/user.cpp
      #os/cross/windows/windows.cpp
      #os/cross/windows/e.h
      #os/cross/windows/message_box.h
      #os/cross/windows/windows.h
      #os/cross/windows/windows_base.h
      #os/cross/windows/windows_base_tsd.h
      #os/cross/windows/windows_common_controls.h
      #os/cross/windows/windows_crt.h
      #os/cross/windows/windows_crtdefs.h
      #os/cross/windows/windows_defs.h
      #os/cross/windows/windows_errno.h
      #os/cross/windows/windows_error.h
      #os/cross/windows/windows_file.h
      #os/cross/windows/windows_gdi.h
      #os/cross/windows/windows_guid_def.h
      #os/cross/windows/windows_internals.h
      #os/cross/windows/windows_mmeapi.h
      #os/cross/windows/windows_mmsystem.h
      #os/cross/windows/windows_nls.h
      #os/cross/windows/windows_nt.h
      #os/cross/windows/windows_ntstatus.h
      #os/cross/windows/windows_ole_automation.h
      #os/cross/windows/windows_shared_memory.h
      #os/cross/windows/windows_thread.h
      #os/cross/windows/windows_thread_impl.h
      #os/cross/windows/windows_time.h
      #os/cross/windows/windows_types.h
      #os/cross/windows/windows_user.h
      #os/cross/windows/windows_wincon.h
      #os/cross/windows/windows_winnt.h
      #os/cross/windows/_.h
      #os/cross/_.h
      #os/cross.h
      #os/cross/_cross.h
      )

endif ()


if (WIN32 OR UWP)

   list(APPEND library_source
#      os/windows_common/_dll.cpp
#      os/windows_common/aura.cpp
#      os/windows_common/base.cpp
#      os/windows_common/bstring.cpp
#      os/windows_common/com.cpp
#      os/windows_common/debug.cpp
#      os/windows_common/file.cpp
      #os/windows_common/file_c.cpp
      #os/windows_common/graphics.cpp
      #os/windows_common/net.cpp
#      os/windows_common/parallelization.cpp
#      os/windows_common/time.cpp
#      os/windows_common/unicode.cpp
      )

endif ()


if (LINUX)
   list(APPEND library_source
      #node/linux/console.cpp
      node/linux/dumpinit.cpp
      node/linux/error.cpp
      node/linux/exception.cpp
      node/linux/_factory.cpp
      #node/linux/file.cpp
      node/linux/linux.cpp
      #node/linux/node.cpp
      #node/linux/node.h
      node/linux/root_tools.cpp
      #node/linux/shell.cpp
      #node/linux/shell_linux.cpp
      node/linux/system.cpp
      #node/linux/stdio_file.cpp
      node/linux/thread.cpp
      node/linux/trace.cpp
      node/linux/util.cpp
      #os/linux/application_system_run.cpp
      node/operating_system/linux/_.cpp
      node/operating_system/linux/callstack.cpp
      node/operating_system/linux/cross_win_file.cpp
      node/operating_system/linux/cross_win_gdi.cpp
      node/operating_system/linux/debug.cpp
      node/operating_system/linux/exception_engine.cpp
      node/operating_system/linux/file.cpp
      node/operating_system/linux/file_lock.cpp
      #os/linux/gdk.cpp
      node/operating_system/linux/graphics.cpp
      node/operating_system/linux/library.cpp
      node/operating_system/linux/linux.cpp
      node/operating_system/linux/linux.inl
      #node/operating_system/linux/list_serial_ports.cpp
      node/operating_system/linux/parallelization.cpp
      node/operating_system/linux/node.cpp
      node/operating_system/linux/os.cpp
      node/operating_system/linux/process.cpp
      node/operating_system/linux/process_pid.cpp
      node/operating_system/linux/simple_app.cpp
      node/operating_system/linux/time.cpp
      node/operating_system/linux/user.cpp
      node/operating_system/linux/win_base.cpp
      )


   list(APPEND library_source
      node/linux/application.h
      #node/linux/console.h
      node/linux/
      #node/linux/file.h
      node/linux/internal.h
      node/linux/root_tools.h
      #node/linux/stdio_file.h
      node/linux/thread.h
      node/linux/_.h
      node/linux/_linux.h
      node/operating_system/linux/cross_win_file.h
      node/operating_system/linux/cross_win_gdi.h
      node/operating_system/linux/cross_win_gdi_internal.h
      node/operating_system/linux/debug.h
      node/operating_system/linux/exception_engine.h
      node/operating_system/linux/file.h
      #os/linux/gdk.h
      node/operating_system/linux/linux_linux.h
      node/operating_system/linux/process.h
      node/operating_system/linux/user.h
      node/operating_system/linux/user_private.h
      node/operating_system/linux/_.h
      node/operating_system/linux/_c.h
      node/operating_system/linux/_linux.h
      node/operating_system/linux/_user.h
      )
endif ()


if (MACOS)
   list(APPEND library_source
      os/cross/universal_windows/cross_metrowin_user.cpp
      os/cross/universal_windows/metrowin_user.cpp
      #node/macos/application.cpp
      #node/macos/_factory.cpp
      #node/macos/file.cpp
      #node/macos/main.cpp
      #node/macos/stdio_file.cpp
      #node/macos/thread.cpp
      #node/macos/trace.cpp
      #node/macos/util.cpp
      os/macos/_.cpp
      #os/macos/application_system_run.cpp
      #os/macos/clipboard.cpp
      #os/macos/cross_win.cpp
      #os/macos/cross_win_file.cpp
      os/macos/debug.cpp
      os/macos/exception_engine.cpp
      #os/macos/file.cpp
      #os/macos/file.mm
      #os/macos/graphics.cpp
      os/macos/library.cpp
      #os/macos/list_serial_ports.cpp
      #os/macos/lock.cpp
      #os/macos/MessageBoxA.cpp
      #os/macos/mm.mm
      #os/macos/mm_graphics.mm
      #os/macos/mm_user.mm
      #os/macos/mmos.mm
      #os/macos/NSPasteboard++.mm
      #os/macos/os.cpp
           os/macos/parallelization.cpp
      #os/macos/process.cpp
      #os/macos/process_pid.cpp
      #os/macos/time.cpp
      #os/macos/user.cpp
      #os/macos/win_base.cpp
      #os/macos/windowing.cpp
      #os/macos/winpr_keycode.cpp
           )


   list(APPEND library_source
      #node/macos/application.h
           #node/macos/
           #node/macos/file.h
           #node/macos/stdio_file.h
           #node/macos/thread.h
           #node/macos/user.h
           #node/macos/_.h
           #node/macos/_macos.h
           #node/macos/_mm.h
           #os/macos/cross_win_gdi.h
           #os/macos/exception_engine.h
           #os/macos/file.h
           #os/macos/graphics_mm.h
           #os/macos/internal.h
           #os/macos/macos.h
           #os/macos/main.h
           #os/macos/mmos.h
           #os/macos/mm_oswindow.h
           #os/macos/os.h
           #os/macos/process_c.h
           #os/macos/user.h
           #os/macos/windowing.h
           #os/macos/windowing_c.h
           #os/macos/window_impl.h
           #os/macos/_.h
           #os/macos/_c.h
           #os/macos/_macos.h
           #os/macos/_mm.h
      )

endif ()


if (IOS)
   list(APPEND library_source
      os/cross/universal_windows/cross_metrowin_user.cpp
      os/cross/universal_windows/metrowin_user.cpp
      node/ios/exception.cpp
      node/ios/_factory.cpp
      node/ios/file.cpp
      node/ios/ios.cpp
      node/ios/ip_enum.cpp
      node/ios/main.cpp
      node/ios/os_context.cpp
      node/ios/plane_system.cpp
      node/ios/shell.cpp
      node/ios/thread.cpp
      node/ios/trace.cpp
      node/ios/util.cpp
      os/ios/application_system_run.cpp
      os/ios/aura.cpp
      os/ios/base_user.cpp
      os/ios/cross_win.cpp
      os/ios/cross_win_file.cpp
      os/ios/crypt.cpp
      os/ios/debug.cpp
      os/ios/error.cpp
      os/ios/exception_engine.cpp
      os/ios/file.cpp
      os/ios/fontopus.cpp
      os/ios/graphics.cpp
      os/ios/language.cpp
      os/ios/launcher.cpp
      os/ios/library.cpp
      os/ios/lock.cpp
      os/ios/MessageBoxA_W.mm
      os/ios/mm.mm
      os/ios/mm_cross_gdi.mm
      os/ios/mm_graphics.mm
      os/ios/mm_thread.mm
      os/ios/mm_user.mm
      os/ios/parallelization.cpp
      os/ios/oswindow_data.cpp
      os/ios/process.cpp
      os/ios/process_pid.cpp
      os/ios/simple_shell_launcher.cpp
      os/ios/small_ipca_channel.cpp
      os/ios/time.cpp
      os/ios/user.cpp
      os/ios/win_base.cpp
      os/ios/window.cpp
      #"os/ios/window_boot 2.h"
      os/ios/windowing.cpp
      )


   list(APPEND library_source
      node/ios/
      node/ios/file.h
      node/ios/implementation.h
      node/ios/internal.h
      node/ios/ip_enum.h
      node/ios/os_context.h
      node/ios/plane_system.h
      node/ios/shell.h
      node/ios/state.h
      node/ios/thread.h
      node/ios/_.h
      node/ios/_ios.h
      node/ios/_m.h
      node/ios/_mm.h
      )


endif ()


if (APPLE)


   list(APPEND library_source
           asset/new.cpp
           os/apple/_.cpp
           #os/apple/DDInvocationGrabber.h
           #os/apple/NSObject+DDExtensions.h
           #os/apple/NSString+SymlinksAndAliases.h
           #os/apple/UncaughtExceptionHandler.h
           #os/apple/_.h
           #os/apple/_apple.h
           #os/apple/_c_mm.h
           #os/apple/_mm.h
           #os/apple/_mm_common.h
           #os/apple/debug.h
           os/apple/exe_path.cpp
           #os/apple/graphics.h
           #os/apple/main.h
           #os/apple/ns_exception.h
           os/apple/time.cpp
           #os/apple/time.h
           #os/chronometer.h
           #timer.mm
           #exception/mm.mm
           #os/cross/universal_windows/cross_metrowin_user.cpp
           #os/cross/universal_windows/metrowin_user.cpp
           #node/apple/apple_timer.cpp
           #os/apple/_.cpp
           #os/apple/_apple.mm
           #os/apple/DDInvocationGrabber.mm
           #os/apple/debug.cpp
           #os/apple/exe_path.cpp
           #os/apple/graphics.cpp
           #os/apple/image_gif.cpp
           #os/apple/main.cpp
           #os/apple/parallelization.cpp
           #os/apple/ns_exception.cpp
           #os/apple/NSObject+DDExtensions.mm
           #os/apple/NSString+SymlinksAndAliases.mm
           #os/apple/process.cpp
           #os/apple/time.cpp
           #os/apple/UncaughtExceptionHandler.mm
           )
endif ()


if (ANDROID)


   list(APPEND library_source
      os/cross/universal_windows/cross_metrowin_user.cpp
      os/cross/universal_windows/metrowin_user.cpp
      node/android/android.cpp
      node/android/android1.cpp
      node/android/error.cpp
      node/android/exception.cpp
      node/android/_factory.cpp
      node/android/file.cpp
      node/android/main.cpp
      node/android/process.cpp
      node/android/thread.cpp
      node/android/trace.cpp
      node/android/util.cpp
      os/android/_bind_app.cpp
      os/android/_bind_impact.cpp
      os/android/_os_android.cpp
      os/android/_os_impl.cpp
      os/android/_os_object.cpp
      os/android/application_system_run.cpp
      os/android/aura.cpp
      os/android/c.cpp
      os/android/debug.cpp
      os/android/dir.cpp
      os/android/exception_engine.cpp
      os/android/file.cpp
      os/android/graphics.cpp
      os/android/jni_launcher.cpp
      os/android/language.cpp
      os/android/launcher.cpp
      os/android/library.cpp
      os/android/locale.cpp
      os/android/lock.cpp
      os/android/main_android.cpp
      os/android/process.cpp
      os/android/process_pid.cpp
      os/android/win_base.cpp
      )


endif ()


if (SOLARIS)


   list(APPEND library_source
      os/solaris/solaris.cpp
      os/solaris/solaris_cairo_keep.cpp
      os/solaris/solaris_cross_win_file.cpp
      os/solaris/solaris_cross_win_gdi.cpp
      os/solaris/solaris_display.cpp
      os/solaris/solaris_file.cpp
      os/solaris/solaris_file_watcher.cpp
      os/solaris/solaris_http.cpp
      os/solaris/solaris_http_lib.cpp
      os/solaris/solaris_launcher.cpp
      os/solaris/solaris_library.cpp
      os/solaris/solaris_lock.cpp
      os/solaris/solaris_message_loop.cpp
      os/solaris/solaris_process.cpp
      os/solaris/solaris_process_pid.cpp
      os/solaris/solaris_simple_shell_launcher.cpp
      os/solaris/solaris_simple_ui.cpp
      os/solaris/solaris_small_ipca_channel.cpp
      os/solaris/solaris_thread.cpp
      os/solaris/solaris_win_base.cpp
      os/solaris/solaris_window.cpp
      os/solaris/solaris_window_xlib.cpp)


endif ()



if (FREEBSD)
   list(APPEND library_source
      #node/freebsd/console.cpp
      node/freebsd/dumpinit.cpp
      node/freebsd/error.cpp
      node/freebsd/exception.cpp
      node/freebsd/_factory.cpp
      #node/freebsd/file.cpp
      node/freebsd/freebsd.cpp
      #node/freebsd/node.cpp
      #node/freebsd/node.h
      node/freebsd/root_tools.cpp
      #node/freebsd/shell.cpp
      #node/freebsd/shell_freebsd.cpp
      node/freebsd/system.cpp
      #node/freebsd/stdio_file.cpp
      node/freebsd/thread.cpp
      node/freebsd/trace.cpp
      node/freebsd/util.cpp
      #os/freebsd/application_system_run.cpp
      node/operating_system/freebsd/_.cpp
      node/operating_system/freebsd/callstack.cpp
      node/operating_system/freebsd/cross_win_file.cpp
      node/operating_system/freebsd/cross_win_gdi.cpp
      node/operating_system/freebsd/debug.cpp
      node/operating_system/freebsd/exception_engine.cpp
      node/operating_system/freebsd/file.cpp
      node/operating_system/freebsd/file_lock.cpp
      #os/freebsd/gdk.cpp
      node/operating_system/freebsd/graphics.cpp
      node/operating_system/freebsd/library.cpp
      node/operating_system/freebsd/freebsd.cpp
      node/operating_system/freebsd/freebsd.inl
      #node/operating_system/freebsd/list_serial_ports.cpp
      node/operating_system/freebsd/parallelization.cpp
      node/operating_system/freebsd/node.cpp
      node/operating_system/freebsd/os.cpp
      node/operating_system/freebsd/process.cpp
      node/operating_system/freebsd/process_pid.cpp
      node/operating_system/freebsd/simple_app.cpp
      node/operating_system/freebsd/time.cpp
      node/operating_system/freebsd/user.cpp
      node/operating_system/freebsd/win_base.cpp
      )


   list(APPEND library_source
      node/freebsd/application.h
      #node/freebsd/console.h
      node/freebsd/
      #node/freebsd/file.h
      node/freebsd/internal.h
      node/freebsd/root_tools.h
      #node/freebsd/stdio_file.h
      node/freebsd/thread.h
      node/freebsd/_.h
      node/freebsd/_freebsd.h
      node/operating_system/freebsd/cross_win_file.h
      node/operating_system/freebsd/cross_win_gdi.h
      node/operating_system/freebsd/cross_win_gdi_internal.h
      node/operating_system/freebsd/debug.h
      node/operating_system/freebsd/exception_engine.h
      node/operating_system/freebsd/file.h
      #os/freebsd/gdk.h
      node/operating_system/freebsd/freebsd_freebsd.h
      node/operating_system/freebsd/process.h
      node/operating_system/freebsd/user.h
      node/operating_system/freebsd/user_private.h
      node/operating_system/freebsd/_.h
      node/operating_system/freebsd/_c.h
      node/operating_system/freebsd/_freebsd.h
      node/operating_system/freebsd/_user.h
      )
endif ()



if (LINUX OR APPLE OR SOLARIS OR FREEBSD)


   list(APPEND library_source
      node/operating_system/posix/_.h
      node/operating_system/posix/_posix.h
      node/operating_system/posix/base_file.cpp
      node/operating_system/posix/file_lock.cpp
      node/operating_system/posix/file_lock.h
      node/operating_system/posix/local_memory_map.cpp
      node/operating_system/posix/process.cpp
      node/operating_system/posix/pthread.cpp
      node/operating_system/posix/parallelization.cpp
      node/operating_system/posix/time.cpp
      node/operating_system/posix/timer.cpp
      node/operating_system/winpr_keycode.cpp
      node/operating_system/winpr_scancode.cpp
      node/posix/_posix.h
      )

   #set_source_files_properties(node/operating_system/posix/process.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
endif ()


if (LINUX)


   list(APPEND library_source
      node/operating_system/ansi/binreloc.cpp
           )


endif ()


add_library(acme SHARED ${library_source})


target_precompile_headers(acme PRIVATE framework.h)


set_target_properties(acme PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(acme PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(acme PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(acme PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/acme.lib")
   target_link_options(acme PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/acme.def")
   target_link_libraries(acme PRIVATE zlib dbghelp imagehlp dwmapi Setupapi Windowscodecs Winmm ws2_32 Crypt32 Normaliz version Secur32 gdiplus Shlwapi Imm32.lib)


elseif(LINUX OR FREEBSD)

#//target_compile_options\([A-Za-z0-9_)]+\s+PRIVATE\s+\$\{PKGCONFIG_CFLAGS\}\)
   pkg_check_modules(PKGCONFIG freetype2 libidn)
   target_compile_options(acme PRIVATE -fpermissive)
      target_compile_options(acme PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(acme PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(acme PRIVATE z dl idn pthread)
if(FREEBSD)
   target_link_libraries(acme PRIVATE iconv)
endif()
   target_link_libraries(acme PRIVATE  ${PKGCONFIG_LIBRARIES})
   target_link_options(acme PRIVATE -Wl,-z,defs)
   message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


elseif (MACOS)


    target_link_libraries(acme PRIVATE z iconv idn ${COCOA} ${IOKIT})


endif ()


target_link_directories(acme PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(acme PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)
target_link_directories(acme PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/storage-${OPERATING_SYSTEM_NAME}/third/library/x64/basis)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(acme PRIVATE _ACME_LIBRARY)

#if(LINUX)
#set(third_binaries "${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/storage-${OPERATING_SYSTEM_NAME}/third/binary/x64/basis/")
#add_custom_command(TARGET acme POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${third_binaries} ${EXECUTABLE_OUTPUT_PATH})
#set(storage_binaries "${CMAKE_CURRENT_SOURCE_DIR}/../../../operating-system/storage-${OPERATING_SYSTEM_NAME}/binary/x64/basis/")
#add_custom_command(TARGET acme POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${storage_binaries} ${EXECUTABLE_OUTPUT_PATH})
#endif()


