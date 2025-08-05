cmake_minimum_required(VERSION 3.16)
project(bred CXX)


list(APPEND library_source
        const/idpool.cpp
        const/idpool.h
        gpu/_.cpp
        gpu/_.h
        gpu/_constant.h
        #gpu/aaa_end_draw.cpp
        #gpu/aaa_end_draw.h
        #gpu/aaaa_gpu.h
        gpu/bred_approach.cpp
        gpu/bred_approach.h
        gpu/command_buffer.cpp
        gpu/command_buffer.h
        gpu/compositor.cpp
        gpu/compositor.h
        gpu/context.cpp
        gpu/context.h
        gpu/context_lock.cpp
        gpu/context_lock.h
        gpu/context_object.cpp
        gpu/context_object.h
        gpu/cpu_buffer.cpp
        gpu/cpu_buffer.h
        gpu/device.cpp
        gpu/device.h
        gpu/draw2d.cpp
        gpu/draw2d.h
        gpu/frame.cpp
        gpu/frame.h
        gpu/graphics.cpp
        gpu/graphics.h
        gpu/guard.cpp
        gpu/guard.h
        gpu/input_layout.cpp
        gpu/input_layout.h
        gpu/layer.cpp
        gpu/layer.h
        gpu/memory_buffer.cpp
        gpu/memory_buffer.h
        gpu/model_buffer.cpp
        gpu/model_buffer.h
        gpu/object.cpp
        gpu/object.h
        gpu/pixmap.cpp
        gpu/pixmap.h
        gpu/program.cpp
        gpu/program.h
        gpu/properties.cpp
        gpu/properties.h
        gpu/render.cpp
        gpu/render.h
        gpu/render_state.cpp
        gpu/render_state.h
        gpu/render_target.cpp
        gpu/render_target.h
        gpu/renderer.cpp
        gpu/renderer.h
        gpu/shader.cpp
        gpu/shader.h
        gpu/swap_chain.cpp
        gpu/swap_chain.h
        gpu/texture.cpp
        gpu/texture.h
        gpu/types.h
        graphics3d/_.h
        #graphics3d/aaa_context.cpp
        #graphics3d/aaa_context.h
        #graphics3d/aaa_renderer.cpp
        #graphics3d/aaa_renderer.h
        graphics3d/camera.cpp
        graphics3d/camera.h
        graphics3d/cube_map.cpp
        graphics3d/cube_map.h
        graphics3d/engine.cpp
        graphics3d/engine.h
        graphics3d/frame.cpp
        graphics3d/frame.h
        graphics3d/input.cpp
        graphics3d/input.h
        graphics3d/key_map.cpp
        graphics3d/key_map.h
        graphics3d/model.cpp
        graphics3d/model.h
        graphics3d/scene.cpp
        graphics3d/scene.h
        graphics3d/scene_object.cpp
        graphics3d/scene_object.h
        graphics3d/scene_system.cpp
        graphics3d/scene_system.h
        graphics3d/types.h
        graphics3d/utilities.h
        include/_.h
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
        platform/_platform.h
        platform/application.cpp
        platform/application.h
        platform/session.cpp
        platform/session.h
        platform/system.cpp
        platform/system.h
        typeface/_.h
        typeface/character.h
        typeface/face.cpp
        typeface/face.h
        user/user/graphics3d.cpp
        user/user/graphics3d.h
        user/user/user.cpp
        user/user/user.h
        _.cpp
        _.h
        _defer.h
        console.h
        framework.cpp
        framework.h
        id.h
        library.h
)

if (${WIN32})
    list(APPEND library_source
            gpu/hlsl_context.cpp
            gpu/hlsl_context.h
    )

endif ()

list(APPEND library_references
        acme
        apex
        aqua
        aura
        axis
        berg)


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
    #target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE)
target_compile_definitions(${PROJECT_NAME} PRIVATE _UNICODE)



