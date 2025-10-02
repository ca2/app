cmake_minimum_required(VERSION 3.16)
project(gpu CXX)


list(APPEND library_source
   gltf/material.h
   gltf/mesh.cpp
   gltf/mesh.h
   gltf/model.cpp
   gltf/model.h
   gltf/vertex.h
   ibl/brdf_convolution_framebuffer.cpp
   ibl/brdf_convolution_framebuffer.h
   ibl/cubemap_framebuffer.cpp
   ibl/cubemap_framebuffer.h
   ibl/diffuse_irradiance_map.cpp
   ibl/diffuse_irradiance_map.h
   ibl/equirectangular_cubemap.cpp
   ibl/equirectangular_cubemap.h
   ibl/hdri_cube.cpp
   ibl/hdri_cube.h
   ibl/mipmap_cubemap_framebuffer.cpp
   ibl/mipmap_cubemap_framebuffer.h
   ibl/specular_map.cpp
   ibl/specular_map.h

   ibl/_.h
   gltf/_.h
   _.cpp
   assimp_iosystem.h
   framework.cpp
   framework.h
   context.cpp
   context.h
   cube.cpp
   cube.h
   full_screen_quad.cpp
   full_screen_quad.h
   hdr_texture.cpp
   hdr_texture.h
)

if (MACOS)
#   list(APPEND ${PROJECT_NAME}_source
 #     operating_system/macos/graphics.cpp
  # )
endif ()


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


list(APPEND library_references
   acme
   apex
aqua
aura
axis
berg
bred
)


list(APPEND static_library_references ${library_references})
list(TRANSFORM static_library_references PREPEND static_)


add_library(${PROJECT_NAME} SHARED ${library_source}
   _ktx.cpp
   _ktx.h)
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
#   if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#      list(APPEND library_references assimp-vc143-mtd)
#   elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
#      list(APPEND library_references assimp-vc143-mt)
#   endif()

   #target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
   target_link_libraries(${PROJECT_NAME} PRIVATE assimp ktx ${library_references} )
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})
   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)

   target_link_libraries(${PROJECT_NAME} PRIVATE)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

   message(STATUS "(6) PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
endif ()




list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
target_compile_definitions(static_${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
