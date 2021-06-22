cmake_minimum_required(VERSION 3.17)
project(imaging_freeimage CXX)


list(APPEND library_source
        _.cpp
        _.h
        context_image.cpp
        context_image.h
        factory_exchange.cpp
        factory_exchange.h
        file_procedure.cpp
        file_procedure_ex1.cpp
        fimemory.h
        framework.cpp
        framework.h
        loading.cpp
        loading_gif.cpp
        saving.cpp)


add_library(imaging_freeimage SHARED ${library_source})


target_precompile_headers(imaging_freeimage PRIVATE framework.h)


set_target_properties(imaging_freeimage PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(imaging_freeimage PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_freeimage PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(imaging_freeimage PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/imaging_freeimage.lib")
    target_link_options(imaging_freeimage PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/imaging_freeimage.def")
    target_link_libraries(imaging_freeimage PRIVATE acme apex aqua aura freeimage)


elseif(LINUX)


    target_compile_options(imaging_freeimage PRIVATE -fpermissive)
    target_link_options(imaging_freeimage PRIVATE -Wl,-rpath=\$ORIGIN)
    target_link_libraries(imaging_freeimage PRIVATE freeimage)
    target_link_libraries(imaging_freeimage PRIVATE acme apex aqua aura)
    target_link_options(imaging_freeimage PRIVATE -Wl,-z,defs)


endif()


target_include_directories(imaging_freeimage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(imaging_freeimage PRIVATE _IMAGING_FREEIMAGE_LIBRARY)



