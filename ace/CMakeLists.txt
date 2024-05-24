# Created by camilo on 2024-05-22 03:03 <3ThomasBorregaardSorensen!!
cmake_minimum_required(VERSION 3.16)
project(ace CXX)


list(APPEND library_source
        filesystem/filesystem/filesystem.h
        networking/curl.cpp
        networking/http.cpp
        networking/http.h
        networking/wget.cpp
        primitive/primitive/e_status.cpp
        primitive/primitive/e_status.h
        primitive/primitive/interlocked_count.cpp
        primitive/primitive/interlocked_count.h
        primitive/primitive/quantum.cpp
        primitive/primitive/quantum.h
        primitive/string/string.cpp
        primitive/string/string.h
        primitive/string/string_pointer.h
        primitive/string/string_pointer.cpp
        platform/application.h
        platform/application.cpp
        process/process.h
        process/process.cpp

)


if(${LINUX})
   list(APPEND library_source
   filesystem/filesystem/posix/filesystem.cpp
   )
endif()


add_library(${PROJECT_NAME} STATIC ${library_source}
        networking/http.h
        networking/http.cpp
        platform/context.h
        platform/context.cpp
)


if (NOT ${NO_PRECOMPILED_HEADER})


   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)


endif ()


if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
target_compile_definitions(${PROJECT_NAME} PRIVATE CUBE)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}.)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE "_${PROJECT_NAME}_project")



