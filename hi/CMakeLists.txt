cmake_minimum_required(VERSION 3.16)
project(_console_hello CXX)


add_executable(${PROJECT_NAME}
   _.cpp
   application.cpp remove_utf8_bom.cpp search_special_characters.cpp)


if(${WIN32})






   if(MSVC)


      target_compile_options(${PROJECT_NAME} PRIVATE    "/MD$<$<CONFIG:Debug>:d>")
      target_link_options(${PROJECT_NAME} PRIVATE    "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
      target_link_options(${PROJECT_NAME} PRIVATE    "/SUBSYSTEM:WINDOWS")
      target_link_options(${PROJECT_NAME} PRIVATE    "/bigobj")
      target_link_options(${PROJECT_NAME} PRIVATE    "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
      target_link_options(${PROJECT_NAME} PRIVATE    "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")


   else()


      target_link_options(${PROJECT_NAME} PRIVATE "-mwindows")
      target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")


   endif()



else()
    target_compile_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_COMPILER_FLAGS})
    target_link_options(${PROJECT_NAME} PRIVATE ${GLOBAL_EXTRA_LINKER_FLAGS} -Wl${GLOBAL_EXTRA_LINK_FLAGS},-z,defs)
endif()


#target_link_options(${PROJECT_NAME} PRIVATE -L . -Wl,-rpath .)


add_dependencies(${PROJECT_NAME} acme_${OPERATING_SYSTEM_NAME})


target_link_libraries(${PROJECT_NAME} PRIVATE acme)






