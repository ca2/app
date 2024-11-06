// From _container.h by camilo on 2024-03-10 22:58 <3ThomasBorregaardSorensen!!
#pragma once


inline ::string quoted_string(const ::scoped_string& scopedstr)
{

   ::string str;

   str = scopedstr;

   str.find_replace("\\", "\\\\");

   str.find_replace("\"", "\\\"");

   return "\"" + str + "\"";

}


inline ::string as_string(const string_array & container, const ::scoped_string& scopedstrSeparator = " ")
{

   ::string str;

   for (const auto& item : container)
   {

      if (str.has_character())
      {

         str += scopedstrSeparator;

      }

      str += quoted_string(item);

   }

   return str;

}

bool character_is_the_space(::ansi_character ansich) noexcept
{
   return ansich == ' ';

}


inline void from_string(string_array& container, const ::scoped_string& scopedstr)
{

   auto range = scopedstr();

   ::string str;

   try
   {

      while (true)
      {

         range.consume(&character_is_the_space, 0);

         if (!range.defer_consume_quoted_value(str))
         {

            break;

         }

         container.add_item(str);

      }

   }
   catch (...)
   {


   }

}