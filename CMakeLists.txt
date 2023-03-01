cmake_minimum_required(VERSION 3.16)
project(_app)


add_subdirectory(acme)
add_subdirectory(apex)
add_subdirectory(aqua)
add_subdirectory(aura)
add_subdirectory(axis)
add_subdirectory(base)
add_subdirectory(bred)
add_subdirectory(core)


add_subdirectory(experience_anthill)
add_subdirectory(experience_core)
#add_subdirectory(experience_lite)
add_subdirectory(experience_nanogui)
add_subdirectory(experience_tranquillum)


add_subdirectory(networking_bsd)
add_subdirectory(crypto_openssl)
add_subdirectory(compress_bzip2)
add_subdirectory(compress_zlib)
add_subdirectory(folder_zip)
add_subdirectory(database_sqlite3)
add_subdirectory(regular_expression_pcre2)



if(INCLUDE_DRAW2D_CAIRO)

    add_subdirectory(draw2d_cairo)

endif()


if(INCLUDE_IMAGING_FREEIMAGE)

    add_subdirectory(imaging_freeimage)

endif()



