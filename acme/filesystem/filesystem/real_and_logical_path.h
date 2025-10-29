// Created by camilo on 2025-10-26 14:26 <3ThomasBorregaardSørensen!!
#pragma once


namespace file
{


   class real_and_logical_path
   {
   public:


      ::file::path   m_pathReal1;
      ::file::path   m_pathLogical1;


      bool is_ok() const
      {

         return m_pathReal1.has_character() && !m_pathReal1.is_unknown_type();

      }


   };


} // namespace file




