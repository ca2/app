cmake_minimum_required(VERSION "3.13")
project(draw2d_opengl CXX)


set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")


list(APPEND library_source

        _.cpp
        _.h
        _factory.cpp
        bitmap.cpp
        bitmap.h
        brush.cpp
        brush.h
        character.h
        color.h
        draw2d.cpp
        draw2d.h
        face.cpp
        face.h
        font.cpp
        font.h
        platform.cpp
        platform.h
        graphics.cpp
        graphics.h
        image.cpp
        image.h
        initialize_opengl_version.cpp
        object.cpp
        object.h
        path.cpp
        path.h
        pen.cpp
        pen.h
        region.cpp
        region.h
)

# Link vendor libs
list(APPEND library_references
    acme
    apex
    aqua
    aura
        axis
        berg
    bred
    gpu_opengl
)


# Shader Compilation
file(GLOB SHADER_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../_matter/continuum/_std/_std/shaders/*.vert"
        "${CMAKE_CURRENT_SOURCE_DIR}/../_matter/continuum/_std/_std/shaders/*.frag")


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE platform.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE platform.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PRIVATE Opengl32 ${library_references})
elseif (${LINUX})

    #if(USE_PKGCONFIG)
    pkg_check_modules(PKGCONFIG x11 gl glx)
    #endif()


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)


    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})

    target_link_libraries(${PROJECT_NAME} PRIVATE glad ${library_references} ${global_library_references} ${PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


    message(STATUS "(C) PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})

endif ()


add_dependencies(${PROJECT_NAME} ${app_common_dependencies})
add_dependencies(${PROJECT_NAME} ${default_draw2d})
add_dependencies(${PROJECT_NAME} ${default_imaging})
add_dependencies(${PROJECT_NAME} ${default_networking})
add_dependencies(${PROJECT_NAME} ${default_write_text})
add_dependencies(${PROJECT_NAME} database_sqlite3)

#set(SPIRV_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}../_matter/continuum/_std/_std/shaders/spirV")
#file(MAKE_DIRECTORY ${SPIRV_OUTPUT_DIR})

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
    add_custom_command(
            OUTPUT ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv
            COMMAND ${CMAKE_COMMAND} -E echo "Compiling shader: ${FILE_NAME}"
            COMMAND glslangValidator -V ${SHADER_FILE} -o ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv
            DEPENDS ${SHADER_FILE}
            COMMENT "Compiling ${FILE_NAME} to SPIR-V"
    )
    list(APPEND SPIRV_BINARIES ${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv)
endforeach()

add_custom_target(_draw2d_opengl_shaders ALL DEPENDS ${SPIRV_BINARIES})

# Ensure shaders are compiled before the VKContinuum executable
add_dependencies(${PROJECT_NAME} _draw2d_opengl_shaders)
if(${WIN32})
add_dependencies(${PROJECT_NAME} typeface_gdiplus)
endif()

if(${WIN32})
    add_dependencies(${PROJECT_NAME} typeface_freetype)
endif()




list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)


