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
        #primitive/primitive/application_bias.h
        #primitive/primitive/block.inl
        #primitive/primitive/collection.h
        #primitive/primitive/command.h
        #primitive/primitive/edit.h
        #primitive/primitive/layered.h
        #primitive/primitive/primitive_update.h
        #primitive/primitive/request_signal.h
        #primitive/promise/_.h
        #primitive/promise/context.cpp
        #primitive/promise/context.h
        #primitive/promise/handler1.cpp
        #primitive/promise/handler1.h
        #primitive/promise/manager.cpp
        #primitive/promise/manager.h
        #primitive/promise/process.cpp
        #primitive/promise/promise.cpp
        #primitive/promise/promise.h
        #primitive/promise/promise1.h
        #primitive/promise/routine.cpp
        #primitive/promise/routine.h
        #primitive/promise/routine_array.cpp
        #primitive/promise/routine_array.h
        #primitive/promise/subject.cpp
        #primitive/promise/subject.h
        #primitive/promise_predicate/predicate_function.cpp
        #primitive/promise_predicate/predicate_function.cpp
        #primitive/promise_predicate/predicate_function_pointer.h
        #primitive/promise_predicate/predicate_holdercpp.cpp
        #primitive/promise_predicate/predicate_holder.h
        #primitive/promise_predicate/predicate_process.h
        #primitive/promise_predicate/synchronized_predicate_routine.h
        #process/_.cpp
        _.cpp
        #__matter_ca2.cpp
        compress/_.h
        compress/compress.cpp
        compress/compress.h
        compress/uncompress.cpp
        compress/uncompress.h
        constant/_.h
        constant/code_page.h
        constant/earth.h
        constant/element.h
        constant/idpool.cpp
        constant/library.h
        constant/message_box.h
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
        filesystem/file/text_file.cpp
        filesystem/file/text_stream.cpp
        filesystem/file/transfer.cpp
        filesystem/file/transfer.h
        filesystem/file/translatable.cpp
        filesystem/file/translatable.h
        filesystem/filesystem/acme_directory.cpp
        filesystem/filesystem/acme_directory.h
        filesystem/filesystem/acme_file.cpp
        filesystem/filesystem/acme_file.h
        filesystem/filesystem/acme_path.cpp
        filesystem/filesystem/acme_path.h
        filesystem/filesystem/file_dialog.cpp
        filesystem/filesystem/file_dialog.h
        filesystem/filesystem/file_path.cpp
        filesystem/filesystem/file_path.h
        filesystem/filesystem/folder_dialog.cpp
        filesystem/filesystem/folder_dialog.h
        filesystem/filesystem/listing.cpp
        filesystem/filesystem/path.cpp
        filesystem/filesystem/path_object.cpp
        framework.cpp
        graphics/draw2d/_.cpp
        graphics/draw2d/_system_color.h
        graphics/draw2d/color.cpp
        graphics/draw2d/color32.h
        graphics/draw2d/colorref_array.cpp
        graphics/draw2d/os_font_name.cpp
        handler/extended_topic.cpp
        handler/extended_topic.h
        handler/handler.cpp
        handler/handler.h
        handler/item.cpp
        handler/item.h
        handler/topic.cpp
        handler/topic.h
        handler/request.cpp
        handler/request.h
        #include/_.cpp
        #include/path.h        #primitive/collection/comparable_array.cpp
        #memory/alloc.cpp
        memory/allocate_processor_cache_oriented.cpp
        memory/allocate_system_heap.cpp
        memory/allocate_x86_cache_oriented.cpp
        memory/allocation.cpp
        memory/array_memory_allocate.cpp
        memory/array_memory_allocate.h
        memory/counter.cpp
        memory/memory.cpp
        memory/memory_allocate.cpp
        memory/memory_allocate.h
        memory/memory_management.cpp
        memory/memory_management.h
        #memory/new.cpp
        memory/os_alloc.cpp
        memory/os_alloc.h
        memory/os_impl/malloc.cpp
        memory/paged.h
        memory/paged_large.cpp
        memory/property_memory_allocate.cpp
        memory/property_memory_allocate.h
        memory/secondary_memory_allocate.cpp
        memory/secondary_memory_allocate.h
        memory/string_memory_allocate.cpp
        memory/string_memory_allocate.h
        memory/string_memory_allocator.h
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
        operating_system/ansi/_pthread.h
        #operating_system/ansi/base.cpp
        operating_system/ansi/callstack.cpp
        operating_system/ansi/callstack.h
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
        operating_system/chronometer.cpp
        operating_system/console.cpp
        operating_system/console_client.cpp
        operating_system/console_client.h
        operating_system/debug.cpp
        operating_system/file.cpp
        #operating_system/http.cpp
        operating_system/main_window.cpp
        operating_system/main_window.h
        operating_system/parallelization.cpp
        operating_system/process.h
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
        parallelization/event.cpp
        parallelization/fork.cpp
        parallelization/fork.h
        parallelization/install_mutex.cpp
        parallelization/manual_reset_event.cpp
        parallelization/multiple_lock.cpp
        parallelization/multiple_lock.h
        parallelization/mutex.cpp
        parallelization/pool.cpp
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
        #platform/acme_main_struct.cpp
        #platform/acme_main_struct.h
        #platform/apex_main_data.cpp
        #platform/apex_main_data.h
        #platform/apex_main_struct.cpp
        #platform/apex_main_struct.h
        platform/application.cpp
        platform/application.h
        platform/application_array.cpp
        platform/application_array.h
        platform/application_base.cpp
        platform/application_base.h
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
        platform/library.cpp
        platform/library.h
        platform/log.cpp
        platform/log.h
        #platform/logic.cpp
        platform/lparam.cpp
        platform/application_flags.cpp
        #platform/main.cpp
        #platform/main.h
        platform/math.cpp
        platform/message.h
        #platform/message_box.cpp
        #platform/muldiv64.cpp
        platform/nanosecond_timer.cpp
        platform/nanosecond_timer.h
        platform/node.cpp
        platform/node.h
        platform/predicate_holder.cpp
        platform/predicate_holder.h
        platform/printf.cpp
        platform/profiler.cpp
        platform/procedure.cpp
        platform/procedure.h
        platform/serial.cpp
        platform/session.cpp
        platform/session.h
        platform/sub_system.cpp
        platform/sub_system.h
        platform/system.cpp
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
        platform/version.cpp
        primitive/collection/__payload_array.cpp
        primitive/collection/__property_set.h
        #primitive/collection/2d_array.cpp
        primitive/collection/array.cpp
        primitive/collection/atom_array.h
        primitive/collection/atom_map.h
        primitive/collection/bit_array.cpp
        #primitive/collection/class_sort_array.cpp
        primitive/collection/collection.h
        #primitive/collection/event_map.cpp
        #primitive/collection/id_array.cpp
        #primitive/collection/key_sort_array.cpp
        #primitive/collection/map_misc.cpp
        primitive/collection/map_test_51778915.cpp
        #primitive/collection/numeric_array.cpp
        #primitive/collection/point_array.cpp
        #primitive/collection/rectangle_array.cpp
        primitive/collection/sort.cpp
        primitive/collection/str_array.cpp
        primitive/collection/string_array.cpp
        #primitive/collection/string_array_base.cpp
        #primitive/collection/string_list.cpp
        #primitive/collection/string_list.cpp
        #primitive/collection/string_to_string_map.cpp
        primitive/collection/string_list.cpp
        primitive/collection/string_list.h
        primitive/comparison/var_strict.cpp
        primitive/data/_.h
        #primitive/data/_data.h
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
        #primitive/datetime/_.cpp
        primitive/datetime/_.h
        #primitive/datetime/_c.cpp
        primitive/datetime/_c.h
        primitive/datetime/_impl.h
        primitive/datetime/date_span.cpp
        primitive/datetime/date_span.h
        primitive/datetime/datetime.cpp
        primitive/datetime/datetime.h
        primitive/datetime/earth_gregorian_time.cpp
        primitive/datetime/earth_gregorian_time.h
        primitive/datetime/earth_time_shift.h
        primitive/datetime/earth_time.cpp
        primitive/datetime/earth_time.h
        primitive/datetime/earth_time_span.cpp
        primitive/datetime/earth_time_span.h
        primitive/datetime/file_time.cpp
        primitive/datetime/file_time.h
        primitive/datetime/file_time_span.cpp
        primitive/datetime/file_time_span.h
        primitive/datetime/microsecond_sleep.cpp
        primitive/datetime/microsecond_sleep.h
        primitive/datetime/mktime.cpp
        primitive/datetime/result.cpp
        primitive/datetime/result.h
        primitive/datetime/system_time.cpp
        primitive/datetime/zonetime.cpp
        primitive/datetime/zonetime.h
        #primitive/time/duration/_.h
        #primitive/time/duration/duration.cpp
        #primitive/time/duration/duration.h
        primitive/time/floating/_.h
        primitive/time/integral/_.h
        primitive/time/_.h
        primitive/time/__string.cpp
        primitive/time/__string.h
        primitive/time/_binary_stream.h
        primitive/time/_impl.h
        primitive/time/_string.h
        #primitive/time/_time.h
        primitive/time/_impl.h
        primitive/time/_string.h
        primitive/time/_structures.h
        primitive/time/_text_stream.h
        #primitive/time/_unit.h
        primitive/time/_unit_operator.h
        primitive/time/time.cpp
        primitive/time/time.h
        #primitive/time/time_operator.h
        primitive/geometry2d/_.cpp
        primitive/geometry2d/_.h
        primitive/geometry2d/_collection.h
        primitive/geometry2d/_collection_bounding_rect.h
        primitive/geometry2d/_collection_contains.h
        primitive/geometry2d/_collection_enhanced.h
        #primitive/geometry2d/_concept.h
        primitive/geometry2d/_enhanced.h
        primitive/geometry2d/_defer.h
        primitive/geometry2d/_geometry2d.h
        #primitive/geometry2d/_impl.h
        #primitive/geometry2d/_rect_impl.h
        primitive/geometry2d/_shape.cpp
        primitive/geometry2d/_shape.h
        #primitive/geometry2d/_size_impl.h
        primitive/geometry2d/_struct.h
        #primitive/geometry2d/align.h
        primitive/geometry2d/_angle.h
        primitive/geometry2d/_arc.h
        primitive/geometry2d/bounding_rect.h
        primitive/geometry2d/collection.h
        primitive/geometry2d/contains.h
        primitive/geometry2d/_ellipse.h
        primitive/geometry2d/geometry.cpp
        primitive/geometry2d/geometry.h
        primitive/geometry2d/_line.h
        primitive/geometry2d/_lines.h
        #primitive/geometry2d/point.cpp
        primitive/geometry2d/_point.h
        primitive/geometry2d/point_array.h
        primitive/geometry2d/_polygon.h
        primitive/geometry2d/rectangle.cpp
        primitive/geometry2d/_rectangle.h
        primitive/geometry2d/rectangle_array.h
        primitive/geometry2d/shape.cpp
        primitive/geometry2d/shape.h
        primitive/geometry2d/shape_array.h
        #primitive/geometry2d/size.cpp
        primitive/geometry2d/_size.h
        primitive/geometry2d/size_array.h
        #primitive/geometry2d/types.cpp
        primitive/geometry2d/types.h
        primitive/geometry3d/_.h
        primitive/geometry3d/box.cpp
        primitive/geometry3d/box.h
        primitive/geometry3d/dimension.h
        primitive/geometry3d/location.cpp
        primitive/geometry3d/location.h
        primitive/geometry3d/quaternions.h
        primitive/mathematics/_.cpp
        primitive/mathematics/_.h
        primitive/mathematics/_impl.h
        #primitive/mathematics/_types.h
        primitive/mathematics/binary_operation.cpp
        primitive/mathematics/binary_operation.h
        primitive/mathematics/c_number.h
        primitive/mathematics/cast.h
        primitive/mathematics/cast.inl
        primitive/mathematics/classes.h
        primitive/mathematics/complex.h
        primitive/mathematics/cvt.cpp
        primitive/mathematics/cvt_g.cpp
        primitive/mathematics/filestream.h
        #primitive/mathematics/index.h
        primitive/mathematics/int_biunique.cpp
        primitive/mathematics/math_clip.h
        primitive/mathematics/int_biunique.h
        primitive/mathematics/mathematics.cpp
        primitive/mathematics/mathematics.h
        primitive/mathematics/mkint_c.cpp
        primitive/mathematics/mkint_c.h
        primitive/mathematics/natural.cpp
        primitive/mathematics/natural.h
        primitive/mathematics/number.cpp
        primitive/mathematics/number.h
        primitive/mathematics/number_double.cpp
        primitive/mathematics/number_double.h
        primitive/mathematics/number_float.cpp
        primitive/mathematics/number_float.h
        primitive/mathematics/number_integer.cpp
        primitive/mathematics/number_integer.h
        primitive/mathematics/numeric_info.h
        primitive/mathematics/numeric.h
        primitive/mathematics/objects.h
        primitive/mathematics/random_number_generator.cpp
        primitive/mathematics/random_number_generator.h
        primitive/mathematics/scalar.cpp
        primitive/mathematics/scalar.h
        #primitive/mathematics/scalar_enum.h
        primitive/mathematics/static_numeric_info.h
        primitive/mathematics/std_template.h
        primitive/mathematics/value.cpp
        primitive/mathematics/value.h
        primitive/media_library/item.cpp
        primitive/media_library/item.h
        #primitive/primitive/__particle_factory.h
        primitive/primitive/__property.h
        primitive/primitive/_.cpp
        primitive/primitive/_.h
        #primitive/primitive/_atom_impl.h
        primitive/primitive/_c_memory.h
        primitive/primitive/_defer.h
        #primitive/primitive/_factory_impl.h
        #primitive/primitive/_factory_prefix.h
        primitive/primitive/_impl.h
        primitive/primitive/_impl_atom.h
        #primitive/primitive/_memory.h
        primitive/primitive/_papaya.h
        primitive/primitive/_papaya_impl.h
        #primitive/primitive/_payload_impl.h
        primitive/primitive/_property_object_impl.h
        primitive/primitive/action_context.cpp
        primitive/primitive/action_context.h
        #primitive/primitive/application_bias.cpp
        primitive/primitive/atom.cpp
        primitive/primitive/atom.h
        #primitive/primitive/atom_space.cpp
        #primitive/primitive/atom_space.h
        primitive/primitive/atomic.h
        primitive/primitive/bit.cpp
        primitive/primitive/bit.h
        primitive/primitive/block.cpp
        primitive/primitive/block.h
        primitive/primitive/collection_file.h
        #primitive/primitive/command.cpp
        primitive/primitive/compare_predicate.h
        #primitive/primitive/context_object_traits.cpp
        #primitive/primitive/edit.cpp
        #primitive/primitive/element.cpp
        #primitive/primitive/element.cpp
        #primitive/primitive/element.h
        #primitive/primitive/element.h
        #primitive/primitive/element_array.cpp
        #primitive/primitive/element_array.h
        #primitive/primitive/element_array.h
        primitive/primitive/enum_bitset.h
        primitive/primitive/enumeration.h
        primitive/primitive/enumeration.h
        primitive/primitive/enumeration.h
        #primitive/primitive/eobject.h
        primitive/primitive/e_status.cpp
        primitive/primitive/e_status.h
        primitive/primitive/factory.cpp
        primitive/primitive/factory.h
        primitive/primitive/get_memory.cpp
        primitive/primitive/get_memory.h
        #primitive/primitive/handler.cpp
        #primitive/primitive/id_array.cpp
        primitive/primitive/integral_byte.cpp
        #primitive/primitive/interlocked.h
        primitive/primitive/interlocked_count.h
        #primitive/primitive/interlocked_long_pulse.cpp
        #primitive/primitive/interlocked_long_pulse.h
        primitive/primitive/linked_property.cpp
        primitive/primitive/linked_property.h
        primitive/primitive/logic.h
        primitive/primitive/malloc.h
        primitive/primitive/map.h
        primitive/primitive/match.cpp
        primitive/primitive/match.h
        #primitive/primitive/material_object.cpp
        #primitive/primitive/material_object.cpp
        #primitive/primitive/material_object.h
        #primitive/primitive/material_object.h
        primitive/primitive/matter.cpp
        primitive/primitive/matter.h
        #primitive/primitive/member.h
        primitive/primitive/memory.cpp
        primitive/primitive/memory.h
        primitive/primitive/memory_base.cpp
        primitive/primitive/memory_base.h
        primitive/primitive/memory_c.cpp
        primitive/primitive/memory_container.cpp
        primitive/primitive/memory_container.h
        #primitive/primitive/natural.h
        primitive/primitive/number.h
        primitive/primitive/object.cpp
        primitive/primitive/object.h
        primitive/primitive/object_meta.cpp
        primitive/primitive/object_meta.h
        #primitive/primitive/papaya.h
        primitive/primitive/particle.cpp
        primitive/primitive/particle.h
        primitive/primitive/payload.cpp
        primitive/primitive/payload.h
        primitive/primitive/payload2.h
        primitive/primitive/pointer.h
        primitive/primitive/pointer2.h
        primitive/primitive/property.cpp
        primitive/primitive/property_object.cpp
        primitive/primitive/property_object.cpp
        primitive/primitive/property_object.h
        primitive/primitive/property_object.h
        primitive/primitive/property_set.cpp
        #primitive/primitive/property_set_composite.cpp
        #primitive/primitive/property_set_papaya.cpp
        primitive/primitive/property_set_papaya.h
        primitive/primitive/read_only_memory.cpp
        primitive/primitive/read_only_memory.h
        primitive/primitive/request_interface.h
        #primitive/primitive/runnable.cpp
        #primitive/primitive/runnable.h
        primitive/primitive/scope_stack.h
        #primitive/primitive/shared_memory.cpp
        #primitive/primitive/shared_memory.h
        #primitive/primitive/simple_object.h
        primitive/primitive/stick.h
        #primitive/primitive/str.h
        primitive/primitive/top_level_domain_list.cpp
        #primitive/primitive/tracer.cpp
        #primitive/primitive/tracer.h
        #primitive/primitive/trait.h
        #primitive/primitive/trait_predicate.h
        #primitive/primitive/traits.cpp
        #primitive/primitive/traits.h
        primitive/primitive/type.cpp
        primitive/primitive/type.h
        primitive/primitive/uid.h
        primitive/primitive/url.cpp
        primitive/primitive/url.h
        primitive/primitive/url_domain.cpp
        primitive/primitive/url_domain.h
        primitive/primitive/util.h
        primitive/primitive/value.h
        primitive/primitive/var_element.cpp
        #primitive/primitive/virtual_memory.cpp
        #primitive/primitive/virtual_memory.h
        primitive/primitive/work.cpp
        primitive/primitive/work.h
        #primitive/promise/signalization.cpp
        #primitive/promise/signalization.h
        primitive/string/_.cpp
        #primitive/string/_.h
        #primitive/string/_.h
        primitive/string/_impl_string_base.h
        primitive/string/_impl_string_meta_data.h
        primitive/string/c/extension/_impl.h
        primitive/string/c/encoding.h
        primitive/string/c/ancient/ansi.h
        primitive/string/c/coupling.h
        primitive/string/c/extension/wd32.h
        primitive/string/c/ancient/_impl.h
        primitive/string/c/extension/_.h
        primitive/string/c/_.h
        primitive/string/c/extension/ansi_impl.h
        primitive/string/c/extension/ansi.h
        primitive/string/c/extension/wd32_impl.h
        primitive/string/c/extension/wd16_impl.h
        primitive/string/c/ancient/wd32.h
        primitive/string/c/unicode.h
        primitive/string/c/encoding_impl.h
        primitive/string/c/_impl.h
        primitive/string/c/ancient/_.h
        primitive/string/c/coupling_impl.h
        primitive/string/c/extension/wd16.h
        primitive/string/c/ancient/wd16.h
        primitive/string/c/unicode_impl.h
        primitive/string/c/ancient/ansi_impl.h
        primitive/string/c/ancient/wd16_impl.h
        primitive/string/c/ancient/wd32_impl.h
        primitive/string/sz/_.h
        primitive/string/sz/wd32.cpp
        primitive/string/sz/ansi.cpp
        primitive/string/sz/wd32_impl.h
        primitive/string/sz/ansi.h
        primitive/string/sz/wd32.h
        primitive/string/sz/wd16_impl.h
        primitive/string/sz/wd16.cpp
        primitive/string/sz/wd16.h
        primitive/string/sz/ansi_impl.h
        primitive/string/sz/_impl.h
        #primitive/string/__c_wd32_impl.h
        #primitive/string/__c_wide.h
        #primitive/string/__c_wide_impl.h
        #primitive/string/_base.h
        #primitive/string/_base.h
        #primitive/string/_base_impl.h
        #primitive/string/_base_impl.h
        #primitive/string/_c.cpp
        #primitive/string/_c.h
        #primitive/string/_c_impl.h
        #primitive/string/_c_inline.h
        #primitive/string/_c_str.h
        #primitive/string/_c_str_impl.h
        #primitive/string/_c_trait.h
        primitive/string/_c_trait_ansi.cpp
        #primitive/string/_c_trait_ansi.h
        #primitive/string/_c_trait_ansi_impl.h
        #primitive/string/_c_trait_impl.h
        #primitive/string/_c_trait_wd16.h
        #primitive/string/_c_trait_wd16_impl.h
        #primitive/string/_c_trait_wd32.h
        #primitive/string/_c_trait_wd32_impl.h
        #primitive/string/_c_trait_wide.cpp
        #primitive/string/_c_trait_wide.h
        #primitive/string/_c_trait_wide_impl.h
        #primitive/string/_c_unicode.h
        #primitive/string/__str_compare.h
        #primitive/string/_str_compare_impl.h
        primitive/string/_conv.h
        #primitive/string/_conv_ansi.cpp
        #primitive/string/_conv_ansi.h
        #primitive/string/_conv_ansi_impl.h
        primitive/string/_defer.h
        primitive/string/_impl.h
        primitive/string/_impl_prio.h
        primitive/string/_international.h
        #primitive/string/_natural.h
        #primitive/string/_str.h
        primitive/string/_string.cpp
        #primitive/string/_str_impl.h
        #primitive/string/_string_wide.h
        #primitive/string/_sz_ansi.cpp
        #primitive/string/_sz_wd16.cpp
        #primitive/string/_sz_wd32.cpp
        #primitive/string/__string.h
        #primitive/string/_trait.h
        #primitive/string/_trait_ansi.h
        #primitive/string/_trait_ansi_impl.h
        #primitive/string/_trait_impl.h
        #primitive/string/_trait_wd16.h
        #primitive/string/_trait_wd16_impl.h
        #primitive/string/_trait_wd32.h
        #primitive/string/_trait_wd32_impl.h
        primitive/string/_u32hash.h
        #primitive/string/_unicode.h
        #primitive/string/_unicode_impl.h
        primitive/string/as_string.cpp
        primitive/string/base64.cpp
        primitive/string/base64.h
        primitive/string/bstr.h
        #primitive/string/bstring.cpp
        primitive/string/bstring.h
        primitive/string/ch.cpp
        #primitive/string/ch.h
        primitive/string/ch_class.cpp
        primitive/string/ch_class.h
        primitive/string/command_line.cpp
        primitive/string/command_line.h
        primitive/string/composite.h
        #primitive/string/dup.cpp
        primitive/string/encoding_exception.cpp
        primitive/string/encoding_exception.h
        primitive/string/from_integer.cpp
        primitive/string/from_integer.h
        primitive/string/hex.cpp
        primitive/string/hex.h
        primitive/string/international.cpp
        primitive/string/international.h
        #primitive/string/international2.cpp
        #primitive/string/international2.h
        #primitive/string/manager.cpp
        primitive/string/network_payload.cpp
        primitive/string/network_payload.h
        primitive/string/parse.cpp
        primitive/string/parse.h
        #primitive/string/simple.cpp
        primitive/string/static_string.h
        #primitive/string/stdstring.h
        primitive/string/str.cpp
        primitive/string/string.cpp
        primitive/string/string.h
        primitive/string/string_ansi.cpp
        #primitive/string/string_buffer.h
        primitive/string/string_inst.h
        primitive/string/string_wide.cpp
        #primitive/string/string_wide_conversion.cpp
        primitive/string/stringtow.cpp
        primitive/string/stringtow.h
        primitive/string/strw.cpp
        primitive/string/strx.cpp
        primitive/string/sz.cpp
        primitive/string/sz.h
        primitive/string/to_integer.cpp
        primitive/string/to_integer.h
        #primitive/string/to_string.cpp
        primitive/string/tokenizer.cpp
        primitive/string/tokenizer.h
        primitive/string/unicode.cpp
        primitive/string/unicode16.cpp
        primitive/string/unicode16_32.cpp
        primitive/string/unicode32.cpp
        primitive/string/character.cpp
        primitive/string/utf8_character.h
        primitive/string/wildcard.cpp
        #primitive/string/wstring_adaptor.h
        #primitive/string/x.cpp
        #primitive/string/x.h
        primitive/string/x/x_charcategory.h
        primitive/string/x/x_charcategory2.h
        primitive/string/x/x_charcategory_names.h
        primitive/string/x/x_defines.h
        primitive/string/x/x_encodings.h
        primitive/string/x/x_tables.h
        primitive/text/context.cpp
        primitive/text/context.h
        primitive/text/data.cpp
        primitive/text/data.h
        primitive/text/international.cpp
        primitive/text/international.h
        primitive/text/international_locale_schema.cpp
        primitive/text/international_locale_schema.h
        primitive/text/text.cpp
        primitive/text/text.h
        primitive/text/translator.cpp
        primitive/text/translator.h
        promise.cpp
        regular_expression/_regular_expression.h
        regular_expression/context.cpp
        regular_expression/context.h
        regular_expression/regular_expression.cpp
        regular_expression/regular_expression.h
        regular_expression/result.cpp
        regular_expression/result.h
        user/nano/_nano.cpp
        user/nano/_.h
        user/nano/brush.cpp
        user/nano/brush.h
        user/nano/button.cpp
        user/nano/button.h
        user/nano/child.cpp
        user/nano/child.h
        user/nano/details_window.cpp
        user/nano/details_window.h
        user/nano/device.cpp
        user/nano/device.h
        user/nano/device.h
        user/nano/display.cpp
        user/nano/display.h
        user/nano/font.cpp
        user/nano/font.h
        user/nano/message_box.cpp
        user/nano/message_box.h
        user/nano/nano.cpp
        user/nano/nano.h
        user/nano/object.cpp
        user/nano/object.h
        user/nano/pen.cpp
        user/nano/pen.h
        user/nano/popup_button.cpp
        user/nano/popup_button.h
        user/nano/still.cpp
        user/nano/still.h
        user/nano/window.cpp
        user/nano/window.h
        user/nano/window_implementation.cpp
        user/nano/window_implementation.h
        user/nano/window_interface.cpp
        user/nano/window_interface.h
        user/user/check.cpp
        user/user/check.h
        user/user/conversation.cpp
        user/user/conversation.h
        user/user/drag.cpp
        user/user/drag.h
        user/user/drag_client.cpp
        user/user/drag_client.h
        user/user/element.cpp
        user/user/element.h
        user/user/e_window_flag.h
        user/user/mouse.h
        user/user/os_colors.cpp
        user/user/os_theme_colors.cpp
        user/user/os_theme_colors.h
        user/user/text.cpp
        user/user/text.h
        user/user/theme_colors.h
        user/user/tool_item.cpp
        user/user/tool_item.h
        user/_.h
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
        #primitive/collection/_.h
        #primitive/collection/_array_base_impl.h
        #primitive/collection/_array_impl.h
        #primitive/collection/_array_impl2.h
        #primitive/collection/_collection_impl1.h
        #primitive/collection/_collection_impl2.h
        #primitive/collection/_fifo_map_impl.h
        #primitive/collection/_list_impl.h
        #primitive/collection/_map_impl.h
        #primitive/collection/_papaya.h
        #primitive/collection/_papaya_array.h
        #primitive/collection/_papaya_array2d_impl.h
        #primitive/collection/_papaya_array_impl.h
        #primitive/collection/_papaya_impl.h
        #primitive/collection/_papaya_map.h
        #primitive/collection/_papaya_map_impl.h
        #primitive/collection/_point_array.h
        #primitive/collection/_raw_array_impl.h
        #primitive/collection/_raw_array_impl2.h
        #primitive/collection/_sort_array_impl.h
        #primitive/collection/_sort_map_impl.h
        #primitive/collection/_string_array_impl.h
        #primitive/collection/base_2array.h
        #primitive/collection/decl.h
        #primitive/collection/runnable_array.h
        #primitive/collection/string_to_string_map.h
        #primitive/collection/stringl.h
        #primitive/collection/template.h
        #primitive/comparison/var_strict.h
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
        constant/idpool.h
        constant/impact.h
        constant/message.h
        constant/routine.h
        constant/simple_command.h
        constant/source.h
        constant/status.h
        constant/status_range_authentication.h
        constant/timer.h
        #constant/user/_.h
        #constant/user/tool_item.h
        exception/_.h
        exception/_c.h
        exception/_dump_context.h
        exception/call_stack.h
        exception/callstack.h
        exception/cancel.h
        exception/dump_context.h
        exception/exception.cpp
        exception/exception.h
        exception/exception2.h
        exception/exit.cpp
        exception/exit.h
        exception/standard.cpp
        exception/standard.h
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
        filesystem/file/primitive.h
        filesystem/file/read_sz_stream.h
        filesystem/file/serialize.h
        filesystem/file/status.h
        filesystem/file/stdio_file.cpp
        filesystem/file/stdio_file.h
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
        graphics/draw2d/colorref_array.h
        include/_.h
        include/_c.h
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
        memory/_heap.h
        memory/_new.h
        memory/align_byte_count.h
        memory/allocate.h
        memory/allocate_processor_cache_oriented.h
        memory/allocate_system_heap.cpp
        memory/allocation.h
        memory/heap_.h
        memory/heap_c.h
        memory/heap_item.h
        memory/heap_item_array.h
        memory/heap_memory.h
        memory/malloc.h
        memory/memory.cpp
        memory/memory.h
        memory/memory_allocator.h
        memory/os_alloc.h
        operating_system/_.h
        operating_system/_api.cpp
        operating_system/_application.h
        operating_system/_impl.h
        operating_system/ansi/_.h
        operating_system/ansi/_ansi.h
        operating_system/ansi/_c.h
        operating_system/ansi/ansios_file.h
        operating_system/ansi/binreloc.h
        operating_system/ansi/callstack.h
        operating_system/ansi/datetime_c.h
        operating_system/ansi/file.h
        operating_system/ansi/file_c.h
        operating_system/ansi/file_raw.h
        operating_system/ansi/pmutex_lock.h
        operating_system/ansi/semun.h
        operating_system/bidirectional_pipe.cpp
        operating_system/bidirectional_pipe.h
        operating_system/error_code.cpp
        operating_system/error_code.h
        operating_system/exit_status.cpp
        operating_system/exit_status.h
        operating_system/file.h
        operating_system/graphics.h
        operating_system/os_windowing2.h
        operating_system/parallelization.h
        operating_system/pipe.cpp
        operating_system/pipe.h
        operating_system/posix/callstack.cpp
        operating_system/posix/mq_base.h
        operating_system/posix/time.h
        operating_system/process.cpp
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
        #parallelization/synchronization_result.h
        parallelization/synchronized_process.h
        parallelization/synchronous_lock.h
        parallelization/task.h
        parallelization/tools.cpp
        parallelization/tools.h
        platform/_features.h
        platform/_global.h
        platform/_impl.h
        platform/_platform.h
        platform/auto.h
        platform/auto_pointer.h
        platform/class.h
        platform/cmp.h
        platform/cmp2.h
        platform/common.h
        platform/const.h
        platform/constraint.h
        platform/conversation_message.cpp
        platform/conversation_message.h
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
        platform/less.h
        platform/logic.h
        platform/lparam.h
        platform/nanosecond_timer.h
        platform/number.h
        platform/object_reference_count_debug.cpp
        platform/object_reference_count_debug.h
        platform/object_reference_count_debug_impl.h
        platform/object_type_counter.cpp
        platform/object_type_counter.h
        platform/printf.h
        platform/profiler.h
        platform/sequence.cpp
        platform/sequencer.h
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
        platform/uint32_muldiv.h
        platform/uint64_muldiv.h
        platform/user_parent.h
        platform/version.h
        primitive/api/api.h
        primitive/api/api_rotate.h
        primitive/collection/__payload_array.h
        primitive/collection/_loosely.h
        primitive/collection/_loosely_map.h
        primitive/collection/_papaya_heap.h
        primitive/collection/address_array.h
        primitive/collection/array.h
        primitive/collection/array_base.h
        primitive/collection/attrib_map.h
        primitive/collection/back_insert_iterator.h
        primitive/collection/base_enum.h
        primitive/collection/bit_array.h
        primitive/collection/bitset.h
        primitive/collection/bool_array.h
        primitive/collection/comparable_array.h
        primitive/collection/comparable_eq_array.h
        primitive/collection/comparable_eq_list.h
        primitive/collection/comparable_list.h
        primitive/collection/comparable_primitive_array.h
        primitive/collection/comparable_raw_array.h
        primitive/collection/composite_array.h
        primitive/collection/deque.h
        primitive/collection/fifo_map.h
        primitive/collection/file_path_map.h
        primitive/collection/forward.h
        primitive/collection/insert_iterator.h
        primitive/collection/int_map.h
        primitive/collection/iterable.h
        primitive/collection/iterator.h
        primitive/collection/list.h
        primitive/collection/map.h
        primitive/collection/set_node.h
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
        primitive/collection/range.h
        primitive/collection/raw_array.h
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
        primitive/collection/string_array.h
        primitive/collection/string_iterable.h
        primitive/collection/string_list.h
        primitive/collection/string_map.h
        primitive/collection/unique_array.h
        primitive/comparison/_.h
        primitive/comparison/_c.h
        primitive/comparison/binary.h
        primitive/comparison/compare.h
        primitive/comparison/equals.h
        primitive/comparison/hash.h
        primitive/comparison/less.h
        primitive/comparison/md5.h
        primitive/comparison/sign.h
        primitive/primitive/_impl_pointer.h
        primitive/primitive/_impl_primitive.h
        procedure.h
        template/list.h
        user/user/_.h
        user/user/_constant.h
        user/user/mouse.h
        user/user/os_colors.h
        version/version.config.h
        version/version.h
        include/_impl.h
        primitive/geometry2d/_text_stream.h
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
            operating_system/windows/nano_user/nano_brush.cpp
            operating_system/windows/nano_user/nano_brush.h
            operating_system/windows/nano_user/nano_device.cpp
            operating_system/windows/nano_user/nano_device.h
            operating_system/windows/nano_user/nano_font.cpp
            operating_system/windows/nano_user/nano_font.h
            operating_system/windows/nano_user/nano_object.h
            operating_system/windows/nano_user/nano_object.cpp
            operating_system/windows/nano_user/nano_pen.cpp
            operating_system/windows/nano_user/nano_pen.h
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


if (WIN32 OR UWP)

    list(APPEND library_source
            #      operating_system/windows_common/_dll.cpp
            #      operating_system/windows_common/aura.cpp
            #      operating_system/windows_common/base.cpp
            #      operating_system/windows_common/bstring.cpp
            #      operating_system/windows_common/com.cpp
            #      operating_system/windows_common/debug.cpp
            #      operating_system/windows_common/file.cpp
            #operating_system/windows_common/file_c.cpp
            #operating_system/windows_common/graphics.cpp
            #operating_system/windows_common/net.cpp
            #      operating_system/windows_common/parallelization.cpp
            #      operating_system/windows_common/time.cpp
            #      operating_system/windows_common/unicode.cpp
            )

endif ()

if (LINUX OR FREEBSD)

    list(APPEND library_source
            operating_system/cairo/nano/_nano.cpp
            operating_system/cairo/nano/device.cpp
            operating_system/cairo/nano/device.h
            operating_system/x11/nano/_.h
            operating_system/x11/nano/_nano.cpp
            operating_system/x11/nano/_.h
            operating_system/x11/nano/display.cpp
            operating_system/x11/nano/display.h
            operating_system/x11/nano/event_listener.h
            operating_system/x11/nano/window.h
            operating_system/x11/nano/window.cpp
            operating_system/x11/_.cpp
            operating_system/x11/_atom.cpp
            operating_system/x11/_atom.h
            operating_system/x11/keyboard.cpp
            operating_system/x11/keyboard.h
            operating_system/xcb/nano/_nano.cpp
            operating_system/xcb/nano/_.h
            operating_system/xcb/nano/display.cpp
            operating_system/xcb/nano/display.h
            operating_system/xcb/nano/event_listener.h
            operating_system/xcb/nano/window.h
            operating_system/xcb/nano/window.cpp
            operating_system/xcb/_.h
            operating_system/xcb/_.cpp
            )

    list(APPEND extra_pkg_modules cairo xcb x11 xkbcommon xcb-render xcb-aux x11-xcb)


endif ()


if (LINUX)
    list(APPEND library_source
            operating_system/linux/
            operating_system/linux/_.cpp
            operating_system/linux/_.h
            operating_system/linux/_.h
            operating_system/linux/_c.h
            operating_system/linux/_factory.cpp
            operating_system/linux/_linux.h
            operating_system/linux/_linux.h
            operating_system/linux/_user.h
            operating_system/linux/application.h
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
            operating_system/linux/file_lock.cpp
            operating_system/linux/graphics.cpp
            #operating_system/linux/internal.h
            operating_system/linux/library.cpp
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


if (FREEBSD)
    list(APPEND library_source
            #operating_system/freebsd/console.cpp
            operating_system/freebsd/dumpinit.cpp
            operating_system/freebsd/error.cpp
            operating_system/freebsd/exception.cpp
            operating_system/freebsd/_factory.cpp
            #operating_system/freebsd/file.cpp
            operating_system/freebsd/freebsd.cpp
            operating_system/freebsd/freebsd2.cpp
            #operating_system/freebsd/operating_system.cpp
            #operating_system/freebsd/operating_system.h
            operating_system/freebsd/root_tools.cpp
            #operating_system/freebsd/shell.cpp
            #operating_system/freebsd/shell_freebsd.cpp
            operating_system/freebsd/system.cpp
            #operating_system/freebsd/stdio_file.cpp
            operating_system/freebsd/thread.cpp
            operating_system/freebsd/trace.cpp
            operating_system/freebsd/util.cpp
            #operating_system/freebsd/application_system_run.cpp
            operating_system/freebsd/_.cpp
            operating_system/freebsd/callstack.cpp
            operating_system/freebsd/cross_win_file.cpp
            operating_system/freebsd/cross_win_gdi.cpp
            operating_system/freebsd/debug.cpp
            operating_system/freebsd/exception_engine.cpp
            operating_system/freebsd/file.cpp
            operating_system/freebsd/file_lock.cpp
            #operating_system/freebsd/gdk.cpp
            operating_system/freebsd/graphics.cpp
            operating_system/freebsd/library.cpp
            operating_system/freebsd/freebsd.cpp
            operating_system/freebsd/freebsd.inl
            #operating_system/freebsd/list_serial_ports.cpp
            operating_system/freebsd/parallelization.cpp
            operating_system/freebsd/_.cpp
            operating_system/freebsd/os.cpp
            operating_system/freebsd/process.cpp
            operating_system/freebsd/process_pid.cpp
            operating_system/freebsd/simple_app.cpp
            operating_system/freebsd/time.cpp
            #operating_system/freebsd/user.cpp
            operating_system/freebsd/win_base.cpp
            )


    list(APPEND library_source
            operating_system/freebsd/application.h
            #operating_system/freebsd/console.h
            operating_system/freebsd/
            #operating_system/freebsd/file.h
            operating_system/freebsd/internal.h
            operating_system/freebsd/root_tools.h
            #operating_system/freebsd/stdio_file.h
            operating_system/freebsd/thread.h
            operating_system/freebsd/_.h
            operating_system/freebsd/_freebsd.h
            operating_system/freebsd/cross_win_file.h
            operating_system/freebsd/cross_win_gdi.h
            operating_system/freebsd/cross_win_gdi_internal.h
            operating_system/freebsd/debug.h
            operating_system/freebsd/exception_engine.h
            operating_system/freebsd/file.h
            #operating_system/freebsd/gdk.h
            operating_system/freebsd/freebsd_freebsd.h
            operating_system/freebsd/process.h
            operating_system/freebsd/user.h
            operating_system/freebsd/user_private.h
            operating_system/freebsd/_.h
            operating_system/freebsd/_c.h
            operating_system/freebsd/_freebsd.h
            operating_system/freebsd/_user.h
            )
endif ()


if (LINUX OR APPLE OR SOLARIS OR FREEBSD)


    list(APPEND library_source
            operating_system/posix/_.h
            operating_system/posix/_posix.h
            operating_system/posix/file.cpp
            operating_system/posix/chldstatus.cpp
            operating_system/posix/desktop.cpp
            operating_system/posix/file_lock.cpp
            operating_system/posix/file_lock.h
            operating_system/posix/idn.cpp
            #operating_system/posix/local_memory_map.cpp
            operating_system/posix/process.cpp
            operating_system/posix/parallelization.cpp
            operating_system/posix/parallelization_pthread.cpp
            operating_system/posix/parallelization_pthread.h
            operating_system/posix/time.cpp
            #operating_system/posix/timer.cpp
            operating_system/winpr_keycode.cpp
            operating_system/winpr_scancode.cpp
            )

    #set_source_files_properties(operating_system/posix/process.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
endif ()


if (LINUX OR FREEBSD)


    list(APPEND library_source
            operating_system/ansi/binreloc.cpp
            )


endif ()


if (LINUX OR FREEBSD)


    list(APPEND library_source
            operating_system/posix/callstack.cpp
            )


endif ()


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT DEFINED NO_PRECOMPILED_HEADER)

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(acme PROPERTIES LINKER_LANGUAGE CXX)





if (MSVC)


    target_compile_options(acme PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(acme PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(acme PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/acme.lib")
    target_link_options(acme PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/acme.def")
    target_link_libraries(acme PRIVATE zlib dbghelp imagehlp dwmapi Setupapi Windowscodecs Winmm ws2_32 Crypt32 Normaliz version Secur32 gdiplus Shlwapi Imm32.lib)


elseif (LINUX OR FREEBSD)

    #//target_compile_options\([A-Za-z0-9_)]+\s+PRIVATE\s+\$\{PKGCONFIG_CFLAGS\}\)

    #if(NOT DONT_USE_PKG_CONFIG)
    pkg_check_modules(PKGCONFIG cairo freetype2 libidn ${extra_pkg_modules})
    #endif()
    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})

    if (FREEBSD)
        list(APPEND system_libraries z dl pthread iconv execinfo)
    else ()
        list(APPEND system_libraries z dl pthread idn)
    endif ()

    target_link_libraries(${PROJECT_NAME} PRIVATE ${system_libraries} ${PKGCONFIG_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${system_libraries} ${PKGCONFIG_LIBRARIES})

    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

    message(STATUS "PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})


elseif (MACOS)


    target_link_libraries(acme PRIVATE z iconv idn ${COCOA} ${IOKIT})


endif ()


target_link_directories(acme PRIVATE ${LIBRARY_OUTPUT_PATH})
target_link_directories(acme PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/library/x64/basis)
target_link_directories(acme PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/third/library/x64/basis)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(acme PRIVATE _ACME_LIBRARY)

#if(LINUX)
#set(third_binaries "${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/third/binary/x64/basis/")
#add_custom_command(TARGET acme POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${third_binaries} ${EXECUTABLE_OUTPUT_PATH})
#set(storage_binaries "${CMAKE_CURRENT_SOURCE_DIR}/../../../operating_system/storage-${OPERATING_SYSTEM_NAME}/binary/x64/basis/")
#add_custom_command(TARGET acme POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${storage_binaries} ${EXECUTABLE_OUTPUT_PATH})
#endif()


