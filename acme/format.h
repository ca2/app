// Created by speccylad(twitch)/turd(discord) trasncript by camilo on
// 2023-10-19 23:26 <3ThomasBorregaardSorensen!!
#pragma once


#include <format>
#include <stdio.h>


namespace std
{


   template <> 
   struct std::formatter<::string> :
      public std::formatter<std::string>
   {

      template<typename Context>
      auto format(const ::string& s, Context& ctx) const
      {

         return formatter<string>::format(std::format("{}", s.c_str()), ctx);
      }

   };


} // namespace std




template<typename ...Args>
[[nodiscard]] inline ::string
format(const std::format_string<Args...> fmt, Args&&... args) noexcept
{

   return ::string(std::format<Args...>(fmt, std::forward<Args>(args)...).c_str());

}


template<typename ...Args>
inline void print(
   std::format_string<Args...> format,
   Args&&... args) noexcept
{
   const auto _Fmtd = ::format(format, std::forward<Args>(args)...);
   printf("%s", _Fmtd.c_str());
}


