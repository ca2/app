// Created with speccylad (Twitch) by camilo on
// 2023-10-19 23:43 <3ThomasBorregaardSorensen!!
#pragma once


#ifdef __STD_FORMAT__


namespace std
{


   template <>
   struct std::formatter<::file::path> :
      public std::formatter<std::string>
   {

      template<typename Context>
      auto format(const ::file::path& path, Context& ctx) const
      {

         return formatter<string>::format(std::format("{}", path.c_str()), ctx);

      }

   };


} // namespace std



#endif // __STD_FORMAT__
