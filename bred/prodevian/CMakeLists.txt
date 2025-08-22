# sandbox_game/CMakeLists.txt
project(sandbox_game LANGUAGES CXX)



list(APPEND library_source
        #main.cpp
        game_layer.h
        game_layer.cpp
        player_input.cpp
        player_input.h
   actor.h
        player.cpp
        game_object.cpp
        game_object.cpp
        #scene.h
        #scene.cpp
        #skybox.cpp
        #skybox.h
        camera.cpp
        camera.h
)


add_library(${PROJECT_NAME} SHARED ${library_source}
        )
add_library(static_${PROJECT_NAME} SHARED ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sandbox_engine

)
#target_link_libraries(${PROJECT_NAME}
#     PUBLIC
#     core_interfaces
#     glm
#     json
#
#)

#target_link_libraries(${PROJECT_NAME}
#        PUBLIC
#        core_interfaces
#        glm
#        json
#
#)

#add_dependencies(${PROJECT_NAME} CompileShaders)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)




