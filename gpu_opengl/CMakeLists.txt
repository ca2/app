cmake_minimum_required(VERSION 3.16)
project(gpu_opengl CXX)



message(STATUS "PROJECT_NAME is ${PROJECT_NAME}")

list(APPEND library_source
   gltf/_constant.h
   gltf/material.h
   gltf/mesh.cpp
   gltf/mesh.h
   gltf/model.cpp
   gltf/model.h
   gltf/vertex.h
   ibl/brdfconvolutionframebuffer.cpp
   ibl/brdfconvolutionframebuffer.h
   ibl/cubemapframebuffer.cpp
   ibl/cubemapframebuffer.h
   ibl/diffuseirradiancemap.cpp
   ibl/diffuseirradiancemap.h
   ibl/hdricube.cpp
   ibl/hdricube.h
   ibl/mipmapcubemapframebuffer.cpp
   ibl/mipmapcubemapframebuffer.h
   ibl/specularmap.cpp
   ibl/specularmap.h
        _.cpp
        _.h
        _factory.cpp
        _gpu_opengl.cpp
        _gpu_opengl.h
        approach.cpp
        approach.h
        assimp.cpp
        assimp.h
        command_buffer.cpp
        command_buffer.h
        cpu_buffer.cpp
        cpu_buffer.h
        context.cpp
        context.h
        device.cpp
        device.h
        frame.h
        frame_buffer.cpp
        frame_buffer.h
   gltf_mesh.cpp
   gltf_mesh.h

   gltf_model.cpp
   gltf_model.h
        framework.cpp
        framework.h
        image_opengl.cpp
        input_layout.cpp
        input_layout.h
        lock.cpp
        lock.h
        memory_buffer.cpp
        memory_buffer.h
        model_buffer.cpp
        model_buffer.h
        object.cpp
        object.h
        offscreen_render_target.cpp
        offscreen_render_target.h
        #opengl.cpp
        #opengl.h
        pixmap.cpp
        pixmap.h
        program.cpp
        program.h
        render_target.cpp
        render_target.h
        renderer.cpp
        renderer.h
        shader.cpp
        shader.h
        swap_chain.cpp
        swap_chain.h
        texture.cpp
        texture.h
)

if (WIN32)
    list(APPEND library_source
            approach_win32.cpp
            device_win32.cpp
            device_win32.h
            )

endif ()


if(${LINUX} OR ${__BSD__})
    list(APPEND library_source
#            context_egl.cpp
 #           context_egl.h
            #context_glx.cpp
            #context_glx.h
       #device_egl.cpp
       #device_egl.h
       approach_glx.cpp
            )

endif ()


if (APPLE)
    list(APPEND library_source
            context_cgl.cpp
            context_cgl.h
            context_fbo.cpp
            context_fbo.h
            )

endif ()


list(APPEND library_references
        acme
        apex
        aqua
        aura
        berg
        bred
   gpu
        )


if(${LINUX} OR ${__BSD__})

    list(APPEND library_references
            aura_posix
       glad
       #windowing_system_x11
            )

else()

   #list(APPEND library_references
    #  glad
   #)


endif ()


add_library(${PROJECT_NAME} SHARED ${library_source}
   gltf_model.cpp
   gltf_model.h)
add_library(static_${PROJECT_NAME} STATIC ${library_source})

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE assimp glu32 opengl32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)



   if(${OPENBSD})
      #list(APPEND extra_pkg_modules glm gl)
      list(APPEND extra_pkg_modules gl osmesa)
   elseif(${FREEBSD})
      list(APPEND extra_pkg_modules gl osmesa)
   endif()

    #if (${USE_PKGCONFIG})
        pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glew egl assimp ${extra_pkg_modules})

    #endif ()
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${default_windowing})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



