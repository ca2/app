cmake_minimum_required(VERSION 3.16)
project(_app)


add_subdirectory(acme)
add_subdirectory(apex)
add_subdirectory(aqua)
add_subdirectory(aura)
add_subdirectory(nano2d)
add_subdirectory(axis)
add_subdirectory(base)
add_subdirectory(bred)
add_subdirectory(core)

add_subdirectory(nanoui)

add_subdirectory(experience_anthill)
add_subdirectory(experience_core)
#add_subdirectory(experience_lite)
add_subdirectory(experience_nanoui)
add_subdirectory(experience_tranquillum)

if(${LINUX} OR ${__BSD__})
add_subdirectory(nano_idn_libidn)
endif()
add_subdirectory(networking_bsd)
add_subdirectory(crypto_openssl)
#add_subdirectory(compress_bzip2)
add_subdirectory(compress_zlib)
add_subdirectory(folder_zip)
add_subdirectory(database_sqlite3)
add_subdirectory(nano_archive_libarchive)
if(${LINUX})
    add_subdirectory(fs_folder_sync_dropbox)
endif()

add_dependencies(axis fs_raw_folder_protocol_dropbox)

add_subdirectory(fs_raw_folder_protocol_dropbox)
add_subdirectory(regular_expression_pcre2)


if(INCLUDE_DRAW2D_CAIRO)

    add_subdirectory(draw2d_cairo)

endif()


if(INCLUDE_IMAGING_FREEIMAGE)

    add_subdirectory(imaging_freeimage)

endif()

if(${INCLUDE_OPENGL} OR ${INCLUDE_DIRECTX11} OR ${INCLUDE_DIRECT2D} OR ${INCLUDE_VULKAN})
    add_subdirectory(typeface_freetype)
endif()
#if(INCLUDE_GPU_OPENGL)
#
#    add_subdirectory(gpu_opengl)
#
#endif()



