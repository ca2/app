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
    loading_multi_frame.cpp
    saving.cpp)


add_library(${PROJECT_NAME} SHARED ${library_source} loading_svg.cpp)


target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura freeimage)


elseif(FREEBSD)


    #pkg_check_modules(PKGCONFIG librsvg-2.0 freeimage)
    pkg_check_modules(PKGCONFIG freeimage)
    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura)
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)

elseif(LINUX)


    #if(NOT DONT_USE_PKG_CONFIG)
    #    pkg_check_modules(PKGCONFIG librsvg-2.0)
    #endif()
    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive ${PKGCONFIG_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES} freeimage acme apex aqua aura)
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)


endif()


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_LIBRARY)



