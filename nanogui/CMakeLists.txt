cmake_minimum_required(VERSION 3.16)
project(nanogui CXX)


list(APPEND library_source
   nano2d/_nano2d.h
   nano2d/context.cpp
   nano2d/context.h
   nano2d/draw2d_context.cpp
   nano2d/draw2d_context.h
   nano2d/nano2d.cpp
        _.cpp
        _.h
        _nanogui.h
        Button.cpp
        Button.h
        Canvas.cpp
        Canvas.h
   CheckBox.cpp
   CheckBox.h
   ColorPicker.cpp
   ColorPicker.h
   ColorWheel.cpp
   ColorWheel.h
   ComboBox.cpp
   ComboBox.h
   common.cpp
   common.h
   FormHelper.h
        framework.cpp
        framework.h
   Graph.cpp
   Graph.h
   Icons.h
   ImagePanel.cpp
   ImagePanel.h
   ImageView.cpp
   ImageView.h
   Label.cpp
   Label.h
   Layout.cpp
   Layout.h
   MessageDialog.cpp
   MessageDialog.h
   Object.h
   Popup.cpp
   Popup.h
   PopupButton.cpp
   PopupButton.h
   ProgressBar.cpp
   ProgressBar.h
   Screen.cpp
   Screen.h
   Slider.cpp
   Slider.h
   TabWidget.cpp
   TabWidget.h
   TextBox.cpp
   TextBox.h
   Theme.cpp
   Theme.h
   ToolButton.h
   traits.h
   vector.h
   VScrollPanel.cpp
   VScrollPanel.h
   Widget.cpp
   Widget.h
   Window.cpp
   Window.h


        )


list(APPEND library_references
   acme
   apex
   aqua
   aura
   )


add_library(nanogui SHARED ${library_source})


target_precompile_headers(nanogui PRIVATE framework.h)


set_target_properties(nanogui PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(nanogui PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(nanogui PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_libraries(nanogui PRIVATE ${library_references})
    target_link_options(nanogui PRIVATE "/SUBSYSTEM:WINDOWS")
elseif(LINUX OR FREEBSD)
    target_compile_options(nanogui PRIVATE -fpermissive)
    #target_link_options(nanogui PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(nanogui PRIVATE ${library_references})
    target_link_options(nanogui PRIVATE -Wl,-z,defs)
endif()


add_dependencies(nanogui experience_core)
add_dependencies(nanogui ${default_draw2d})
add_dependencies(nanogui ${default_write_text})
add_dependencies(nanogui ${app_common_dependencies})
add_dependencies(nanogui database_sqlite3)


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(nanogui PRIVATE _APP_SIMPLE_APPLICATION_LIBRARY)

