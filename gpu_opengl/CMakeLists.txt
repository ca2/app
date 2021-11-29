cmake_minimum_required(VERSION 3.17)
project(gpu_opengl CXX)


list(APPEND library_source
        _.cpp
        _.h
        buffer.cpp
        buffer.h
        context.cpp
        context.h
        _factory.cpp

        framework.cpp
        framework.h
        image_opengl.cpp
        opengl.cpp
        opengl.h
        program.cpp
        program.h
        shader.cpp
        shader.h)

if(WIN32)
    list(APPEND library_source
            context_win32.cpp
            context_win32.h
            )

endif()


if(LINUX)
    list(APPEND library_source
            context_egl.cpp
            context_egl.h
            context_glx.cpp
            context_glx.h
            )

    endif()


if(APPLE)
    list(APPEND library_source
            context_cgl.cpp
            context_cgl.h
            context_fbo.cpp
            context_fbo.h
            )

endif()


list(APPEND library_references
        acme
        apex
        aqua
        aura
        )


if(LINUX)

    list(APPEND library_references
       aura_posix
       )

endif()

add_library(gpu_opengl SHARED ${library_source})

target_precompile_headers(gpu_opengl PRIVATE framework.h)

set_target_properties(gpu_opengl PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)


    target_compile_options(gpu_opengl PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(gpu_opengl PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(gpu_opengl PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/gpu_opengl.lib")
    target_link_options(gpu_opengl PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/gpu_opengl.def")
    target_link_libraries(gpu_opengl PRIVATE glu32 glew32 opengl32)
    target_link_libraries(gpu_opengl PRIVATE ${library_references})


elseif(LINUX OR FREEBSD)


    pkg_check_modules(PKGCONFIG glew)
    target_compile_options(gpu_opengl PRIVATE -fpermissive)
    target_compile_options(gpu_opengl PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(gpu_opengl PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(gpu_opengl PRIVATE GL GLEW EGL GLU)
    target_link_libraries(gpu_opengl PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(gpu_opengl PRIVATE acme apex aqua aura)
    target_link_libraries(gpu_opengl PRIVATE ${library_references})
    target_link_libraries(gpu_opengl PRIVATE ${default_windowing})
    target_link_options(gpu_opengl PRIVATE -Wl,-z,defs)


endif()





target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(gpu_opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(gpu_opengl PRIVATE _GPU_OPENGL_LIBRARY)



