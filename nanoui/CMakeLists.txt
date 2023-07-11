cmake_minimum_required(VERSION 3.16)
project(nanoui CXX)


list(APPEND library_source
        #nano2d/_component.h
        #nano2d/context.cpp
        #nano2d/context.h
        #nano2d/draw2d_context.cpp
        #nano2d/draw2d_context.h
        #nano2d/font_sink.cpp
        #nano2d/font_sink.h
        #nano2d/nano2d.cpp
        _.cpp
        _.h
        _constant.h
        _function.h
        ##_library.h
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
        #Icons.h
        ImagePanel.cpp
        ImagePanel.h
        ImageImpact.cpp
        ImageImpact.h
        Label.cpp
        Label.h
        Layout.cpp
        Layout.h
        MessageDialog.cpp
        MessageDialog.h
        Object.h
        platform.cpp
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
        #vector.h
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
        nano2d
        )


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()
if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
elseif (${LINUX} OR ${FREEBSD})


    target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
    target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


    #target_link_options(${PROJECT_NAME}  PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



