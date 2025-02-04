cmake_minimum_required(VERSION 3.16)
project(imaging_freeimage CXX)


list(APPEND library_source
        _.cpp
        _.h
        _factory.cpp
        image_context.cpp
        image_context.h
        file_procedure.cpp
        file_procedure_ex1.cpp
        fimemory.h
        framework.cpp
        framework.h
        loading.cpp
        loading_multi_frame.cpp
        loading_svg.cpp
        saving.cpp)


list(APPEND library_references
   acme 
   apex 
   aqua 
   aura )


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})




list(APPEND static_library_references ${library_references})
list(TRANSFORM static_library_references PREPEND static_)




if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
#if (NOT ${NO_PRECOMPILED_HEADER})
#
#    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
#    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)
#
#endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (${MSVC})


    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura freeimage)


elseif (${FREEBSD})


    #pkg_check_modules(PKGCONFIG librsvg-2.0 freeimage)
    pkg_check_modules(PKGCONFIG_${PROJECT_NAME} freeimage)
    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive ${PKGCONFIG_${PROJECT_NAME}_CFLAGS})
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive ${PKGCONFIG_${PROJECT_NAME}_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE  ${PKGCONFIG_${PROJECT_NAME}_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${PKGCONFIG_${PROJECT_NAME}_LIBRARIES})
    target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${PKGCONFIG_${PROJECT_NAME}_LIBRARIES})


    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


    message(STATUS "(E) PKGCONFIG_CFLAGS is ${PKGCONFIG_CFLAGS}")
    message(STATUS "(E) PKGCONFIG_LDFLAGS is ${PKGCONFIG_LDFLAGS}")
    message(STATUS "(E) PKGCONFIG_LIBRARIES is ${PKGCONFIG_LIBRARIES}")


elseif (${LINUX} OR ${OPENBSD} OR ${NETBSD})


    #if(USE_PKGCONFIG)
    #    pkg_check_modules(PKGCONFIG_${PROJECT_NAME} librsvg-2.0)
    #endif()


    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)



    target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_${PROJECT_NAME}_CFLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_${PROJECT_NAME}_LDFLAGS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_${PROJECT_NAME}_LIBRARIES} freeimage ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)


endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



