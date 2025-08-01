cmake_minimum_required(VERSION 3.16)
project(networking_bsd CXX)


list(APPEND library_source
   #sockets.cpp
   sockets/_.h
   sockets/_1.h
   sockets/_sockets.h
   sockets/_strconv.h
   #sockets/_system_sockets.cpp
   #sockets/aaa__component.h
   #sockets/aaa_http_batch_buffer.cpp
   #sockets/aaa_link_in_socket.cpp
   #sockets/aaa_link_out_socket.cpp
   #sockets/aaa_sockets_base.cpp
   #sockets/aaa_transfer_socket.cpp
   #sockets/aaa_want_to_remove_sockets_sockets.h
   #sockets/aaa_websocket_client.cpp
   sockets/base/base_socket.cpp
   sockets/base/base_socket.h
   sockets/base/base_socket_handler.cpp
   sockets/base/base_socket_handler.h
   #sockets/base/socket_thread.cpp
   #sockets/base/socket_thread.h
   sockets/basic/_.h
   #        sockets/basic/aaa_basic_net.cpp
   #        sockets/basic/aaa_net.h
   #        sockets/basic/aaa_sync_socket_handler.cpp
   #        sockets/basic/aaa_sync_socket_handler.h
   sockets/basic/listen_socket_impl.cpp
   sockets/basic/listen_socket_impl.h
   sockets/basic/sctp_socket.cpp
   sockets/basic/sctp_socket.h
   sockets/basic/socket.cpp
   sockets/basic/socket.h
   sockets/basic/socket_handler.cpp
   sockets/basic/socket_handler.h
   sockets/basic/stream_socket.cpp
   sockets/basic/stream_socket.h
   sockets/basic/tcp_socket.cpp
   sockets/basic/tcp_socket.h
   sockets/basic/tls_socket.cpp
   sockets/basic/tls_socket.h
   sockets/basic/udp_socket.cpp
   sockets/basic/udp_socket.h
   sockets/config.h
   #        sockets/dns/resolv_server.cpp
   #        sockets/dns/resolv_server.h
   #        sockets/dns/resolv_socket.cpp
   #        sockets/dns/resolv_socket.h
   #        sockets/http/_.h
   #        sockets/http/client_socket.cpp
   #        sockets/http/client_socket.h
   #        sockets/http/debug_socket.cpp
   #        sockets/http/debug_socket.h
   #        sockets/http/get_socket.cpp
   #        sockets/http/get_socket.h
   #        sockets/http/http_base_socket.cpp
   #        sockets/http/http_base_socket.h
   #        sockets/http/listener.cpp
   #        sockets/http/listener.h
   #        sockets/http/post_socket.cpp
   #        sockets/http/post_socket.h
   #        sockets/http/put_socket.cpp
   #        sockets/http/put_socket.h
   #        sockets/http/session.cpp
   #        sockets/http/session.h
   #        sockets/http/socket.cpp
   #        sockets/http/socket.h
   #        sockets/http/tunnel.cpp
   #        sockets/http/tunnel.h
   #        sockets/http_batch_buffer.h
   #        sockets/http_buffer.h
   #        sockets/link_in_socket.h
   #        sockets/link_out_socket.h
   #        sockets/logger.h
   sockets/socket_id_list.h
   #sockets/sockets.cpp
   #sockets/sockets.h
   sockets/sockets_base.h
   sockets/ssl/_.h
   sockets/ssl/client_context.cpp
   sockets/ssl/client_context.h
   sockets/ssl/client_context_map.cpp
   sockets/ssl/client_context_map.h
   sockets/ssl/context.cpp
   sockets/ssl/context.h
   sockets/ssl/initializer.cpp
   sockets/ssl/initializer.h
   sockets/ssl/ticket_key.h
   sockets/transfer_socket.h
   sockets/_collection.h
   _binary_stream.h
   _constant.h
   address.cpp
   address.h
   framework.cpp
   framework.h
   ip_enum.cpp
   ip_enum.h
   networking.cpp
   networking.h
   networking_bsd.cpp
   port_forward.cpp
   port_forward.h
   resource.h
   #        sockets/webserver/httpd_socket.cpp
   #        sockets/webserver/httpd_socket.h
   #        sockets/websocket_client.h
   _.cpp
   _.h
   _byte_order.h
   _factory.cpp
   _impl.h
   #_net.h
   #_networking.h
   #_networking_impl.h
   _operating_system.h
)


if (WIN32 OR UWP)

   list(APPEND library_source
      winsock2/_.cpp
      winsock2/_.h
      winsock2/list_computers.cpp
      winsock2/list_network_interfaces.cpp
   )

endif ()


if (${LINUX} OR ${__BSD__} OR ${ANDROID})

   list(APPEND library_source
      bsd/_.cpp
      bsd/_.h
      bsd/list_computers.cpp
      bsd/list_network_interfaces.cpp
   )

endif()


if (${__BSD__})

   list(APPEND library_source
   bsd/bsd_list_computers.cpp

   )
endif()

list(APPEND library_references
   acme apex)


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
endif ()


add_library(${PROJECT_NAME} SHARED ${library_source})
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
   target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} Ws2_32)
elseif (${LINUX} OR ${__BSD__} OR ${ANDROID})

   target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
   #set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)




   if (${USE_PKGCONFIG})
      message(STATUS "networking_bsd USE_PKGCONFIG")
      pkg_check_modules(${PROJECT_NAME}_PKGCONFIG libcrypto libssl)
   else()
      list(APPEND library_references
      crypto ssl)
   endif ()


   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_options(static_${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   if (NOT ${FREEBSD})
      target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   endif ()
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)

   message(STATUS "(G) PKGCONFIG_CFLAGS ${${PROJECT_NAME}_PKGCONFIG_CFLAGS}")
   message(STATUS "(G) PKGCONFIG_LIBRARIES is ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES}")
   message(STATUS "(G) PKGCONFIG_LDFLAGS is ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS}")
endif ()

if(${LINUX} OR ${__BSD__})
add_dependencies(${PROJECT_NAME} nano_idn_libidn)
endif()

list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)



