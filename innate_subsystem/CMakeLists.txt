cmake_minimum_required(VERSION 3.16)
project(innate_subsystem CXX)


list(APPEND library_source
   drawing/_.h
   drawing/Bitmap.cpp
   drawing/Bitmap.h
   drawing/BitmapGraphics.cpp
   drawing/BitmapGraphics.h
   drawing/Brush.cpp
   drawing/Brush.h
   drawing/Cursor.cpp
   drawing/Cursor.h
   drawing/DeviceContext.cpp
   drawing/DeviceContext.h
   drawing/Graphics.cpp
   drawing/Graphics.h
   drawing/GraphicsObject.h
   drawing/GraphicsObject.cpp
   drawing/Icon.cpp
   drawing/Icon.h
   drawing/Pen.cpp
   drawing/Pen.h
   drawing/SolidBrush.cpp
   drawing/SolidBrush.h
   framebuffer/DibFrameBuffer.cpp
   framebuffer/DibFrameBuffer.h
   framebuffer/DibSection.cpp
   framebuffer/DibSection.h
   framebuffer/FrameBuffer.cpp
   framebuffer/FrameBuffer.h
   
   #gui.vcproj
   #gui.vcxproj.user   gui/BalloonTip.cpp
   gui/BalloonTip.h
   gui/CheckBox.cpp
   gui/CheckBox.h
   gui/ComboBox.cpp
   gui/ComboBox.h
   gui/CommonControlsEx.cpp
   gui/CommonControlsEx.h
   gui/Control.cpp
   gui/Control.h
   #gui/Cursor.cpp
   #gui/Cursor.h
   gui/Dialog.cpp
   gui/Dialog.h
   gui/FilteredTextBox.cpp
   gui/FilteredTextBox.h
   gui/ImagedButton.cpp
   gui/ImagedButton.h
   gui/ImageList.cpp
   gui/ImageList.h
   gui/KeyboardLayout.cpp
   gui/KeyboardLayout.h
   gui/ListBox.cpp
   gui/ListBox.h
   gui/ListView.cpp
   gui/ListView.h
   gui/Menu.cpp
   gui/Menu.h
   gui/MessageWindow.cpp
   gui/MessageWindow.h
   gui/notification_handler.cpp
   gui/notification_handler.h
   gui/NotifyIcon.cpp
   gui/NotifyIcon.h
   gui/NotifyIconWindow.cpp
   gui/NotifyIconWindow.h
   #gui/PaintWindow.cpp
   #gui/PaintWindow.h
   gui/ProgressBar.cpp
   gui/ProgressBar.h
   #gui/resource_loader.cpp
   #gui/resource_loader.h
   gui/ScrollBar.cpp
   gui/ScrollBar.h
   gui/SpinControl.cpp
   gui/SpinControl.h
   gui/StringFilter.cpp
   gui/StringFilter.h
   #gui/subsystem.cpp
   #gui/subsystem.h
   gui/SystemMetrics.cpp
   gui/SystemMetrics.h
   gui/Tab.cpp
   gui/Tab.h
   gui/TabContainer.cpp
   gui/TabContainer.h
   gui/TabControl.cpp
   gui/TabControl.h
   gui/TextBox.cpp
   gui/TextBox.h
   gui/Toolbar.cpp
   gui/Toolbar.h
   gui/Tooltip.cpp
   gui/Tooltip.h
   gui/Trackbar.cpp
   gui/Trackbar.h
   gui/Window.cpp
   gui/Window.h
   gui/WindowFinder.cpp
   gui/WindowFinder.h
   #gui/WindowMessageHandler.h
   gui/WindowProcHolder.cpp
   gui/WindowProcHolder.h
   _.cpp
   _.h
   ##_library.h
   #_factory.h
   #application.cpp
   #application.h
   framework.cpp
   framework.h
   ResourceLoader.cpp
   ResourceLoader.h
   subsystem.cpp
   subsystem.h)


list(APPEND library_references
   acme
   subsystem
   apex
)


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})




#if(${LINUX} OR ${__BSD__})


   #add_custom_command(
      #OUTPUT ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
      #COMMAND ${APPLICATION_BUILD_HELPER_BINARY} --prepare-application ${PROJECT_SOURCE_DIR}
      #COMMENT "Generating ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o"
   #)

   #target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

#endif()




if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if(${WIN32})


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})


elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})


   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

   message(STATUS "(5) PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})


endif ()


add_dependencies(${PROJECT_NAME} apex_${OPERATING_SYSTEM_NAME})
add_dependencies(${PROJECT_NAME} ${default_node})
add_dependencies(${PROJECT_NAME} ${default_draw2d})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)


#add_subdirectory(__implement)



