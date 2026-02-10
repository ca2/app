cmake_minimum_required(VERSION 3.16)
project(gpu_opengl CXX)



message(STATUS "PROJECT_NAME is ${PROJECT_NAME}")



# Collect all files in shaders/ directory
file(GLOB SHADER_FILES
   "${CMAKE_CURRENT_SOURCE_DIR}/ibl/shader/*"
)

message(STATUS "SHADER_FILES: ${SHADER_FILES}")

# Keep only .vert and .frag files
set(FILTERED_SHADERS "")
foreach(SHADER ${SHADER_FILES})
   get_filename_component(EXT ${SHADER} EXT)
   if(EXT STREQUAL ".vert" OR EXT STREQUAL ".frag")
      list(APPEND FILTERED_SHADERS ${SHADER})
   endif()
endforeach()


message(STATUS "FILTERED_SHADERS: ${FILTERED_SHADERS}")

set(GENERATED_HEADERS "")

foreach(SHADER ${FILTERED_SHADERS})
   get_filename_component(DIR ${SHADER} DIRECTORY)
   get_filename_component(NAME ${SHADER} NAME)
   set(OUTPUT_FILE ${DIR}/${NAME}.h)

   add_custom_command(
      OUTPUT ${OUTPUT_FILE}
      COMMAND ${APPLICATION_BUILD_HELPER_BINARY} --inline-text ${SHADER}
      DEPENDS ${SHADER}
      COMMENT "Generating header from ${SHADER}"
      VERBATIM
   )

   list(APPEND IBL_SHADERS_HEADERS ${OUTPUT_FILE})
endforeach()


message(STATUS "IBL_SHADERS_HEADERS: ${IBL_SHADERS_HEADERS}")

# A target that generates all headers
add_custom_target(${PROJECT_NAME}_generate_ibl_shader_headers ALL DEPENDS ${IBL_SHADERS_HEADERS})

list(APPEND library_source
   gltf/_constant.h
   gltf/material.h
   gltf/mesh.cpp
   gltf/mesh.h
   gltf/model.cpp
   gltf/model.h
   gltf/vertex.h
   ${IBL_SHADERS_HEADERS}
   #ibl/brdf_convolution_framebuffer.cpp
   #ibl/brdf_convolution_framebuffer.h
   #ibl/cubemap_framebuffer.cpp
   #ibl/cubemap_framebuffer.h
   ibl/diffuse_irradiance_map.cpp
   ibl/diffuse_irradiance_map.h
   ibl/equirectangular_cubemap.cpp
   ibl/equirectangular_cubemap.h
   #ibl/hdri_cube.cpp
   #ibl/hdri_cube.h
   #ibl/aaa_mipmap_cubemap_framebuffer.cpp
   #ibl/aaa_mipmap_cubemap_framebuffer.h
   ibl/specular_map.cpp
   ibl/specular_map.h
        _.cpp
        _.h
        _factory.cpp
   _glad.cpp
        _gpu_opengl.cpp
        _gpu_opengl.h
        approach.cpp
        approach.h
        assimp.cpp
        assimp.h
   block.cpp
   block.h
        command_buffer.cpp
   command_buffer.h
        cpu_buffer.cpp
        cpu_buffer.h
        context.cpp
        context.h
   context_egl.cpp
   context_egl.h
   context_ktx.cpp
   #cube.cpp
   #cube.h
        device.cpp
        device.h
        frame.h
        frame_buffer.cpp
        frame_buffer.h
   full_screen_quad.cpp
   full_screen_quad.h
   #gltf_mesh.cpp
   #gltf_mesh.h

      #gltf_model.cpp
   #gltf_model.h
        framework.cpp
        framework.h
   hdr_texture.cpp
   hdr_texture.h
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
       approach_egl.cpp
       context_egl.cpp
       context_egl.h
       device_egl.cpp
       #device_egl.h
       swap_chain_egl.cpp

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
       ktx
       #windowing_system_x11
            )

else()

   #list(APPEND library_references
    #  glad
   #)


endif ()

add_compile_definitions(GLAD_GLAPI_EXPORT)


add_library(${PROJECT_NAME} SHARED ${library_source}
   rotating_cube.cpp
   device_egl_x11.cpp
   context_win32.h)
add_library(static_${PROJECT_NAME} STATIC ${library_source})


add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_generate_ibl_shader_headers)
add_dependencies(static_${PROJECT_NAME} ${PROJECT_NAME}_generate_ibl_shader_headers)

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(${WIN32})


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE assimp glu32 opengl32 glad ktx)
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
        #pkg_check_modules(${PROJECT_NAME}_PKGCONFIG glew egl assimp ${extra_pkg_modules})
   pkg_check_modules(${PROJECT_NAME}_PKGCONFIG REQUIRED x11 egl assimp ${extra_pkg_modules})

    #endif ()
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

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



