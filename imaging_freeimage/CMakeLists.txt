cmake_minimum_required(VERSION 3.16)
project(imaging_freeimage CXX)


list(APPEND library_source
    _.cpp
    _.h
    _factory.cpp
    context_image.cpp
    context_image.h
    file_procedure.cpp
    file_procedure_ex1.cpp
    fimemory.h
    framework.cpp
    framework.h
    loading.cpp
    loading_gif.cpp
    saving.cpp)


add_library(imaging_freeimage SHARED ${library_source} loading_svg.cpp)


target_precompile_headers(imaging_freeimage PRIVATE framework.h)


set_target_properties(imaging_freeimage PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(imaging_freeimage PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_freeimage PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_freeimage PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/imaging_freeimage.lib")
    target_link_options(imaging_freeimage PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/imaging_freeimage.def")
    target_link_libraries(imaging_freeimage PRIVATE acme apex aqua aura freeimage)


elseif(FREEBSD)


    pkg_check_modules(PKGCONFIG librsvg-2.0 freeimage)
    target_compile_options(imaging_freeimage PRIVATE -fpermissive ${PKGCONFIG_CFLAGS})
    target_link_options(imaging_freeimage PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(imaging_freeimage PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(imaging_freeimage PRIVATE acme apex aqua aura)
    target_link_options(imaging_freeimage PRIVATE -Wl,-z,defs)

elseif(LINUX)


    pkg_check_modules(PKGCONFIG librsvg-2.0)
    target_compile_options(imaging_freeimage PRIVATE -fpermissive ${PKGCONFIG_CFLAGS})
    target_link_options(imaging_freeimage PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(imaging_freeimage PRIVATE freeimage acme apex aqua aura)
    target_link_options(imaging_freeimage PRIVATE -Wl,-z,defs)


endif()


target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(imaging_freeimage PRIVATE _IMAGING_FREEIMAGE_LIBRARY)



