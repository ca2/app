// _.h changed to _operating_system.h
// Created as regular general include _.h by camilo on 2023-04-15 20:32 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME void flush_stdin();


namespace operating_system
{


   class application;
   class main_window;

   class a_system_menu;
   class a_system_menu_item;


} // namespace operating_system




#ifdef UNIVERSAL_WINDOWS

consteval bool is_universal_windows() { return true; }

#else

consteval bool is_universal_windows() { return false; }

#endif



// Created by camilo on 2024-06-02 16:46 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
#pragma once


struct library_t;


namespace operating_system
{


   class dynamic_library;


} // namespace operating_system


#if defined(WIN32)


namespace windows
{

   CLASS_DECL_ACME unsigned int last_error();

} // namespace windows


#endif



