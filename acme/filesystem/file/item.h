#pragma once


#include "acme/filesystem/filesystem/path.h"
#include "acme/primitive/primitive/element.h"


namespace file
{


   class CLASS_DECL_ACME item :
      virtual public element
   {
   protected:


      ::file::path                  m_pathUser;
      ::file::path                  m_pathFinal;


   public:


      enumeration < enum_flag >     m_flags;
      string                        m_strName;


      item() {}


      item(const item & item) :
         m_pathUser(item.m_pathUser),
         m_pathFinal(item.m_pathFinal),
         m_flags(item.m_flags),
         m_strName(item.m_strName)
      {


      }


      item(const ::file::path & pathUser, const ::file::path & pathFinal) :
         m_pathUser(pathUser),
         m_pathFinal(pathFinal),
         m_strName(pathUser.name())
      {

         if (m_pathFinal.has_char())
         {

            if (m_pathFinal & e_flag_final_path)
            {

               m_flags += e_flag_final_path;

            }
            else
            {

               ASSERT(false);

            }

         }

      }
      

      item(const ::file::path & pathUser, const ::file::path & pathFinal, const enumeration < enum_flag > & flags) :
         m_pathUser(pathUser),
         m_pathFinal(pathFinal),
         m_flags(flags),
         m_strName(pathUser.name())
      {

         if (m_pathFinal.has_char())
         {

            if (m_pathFinal & e_flag_final_path)
            {

               m_flags += e_flag_final_path;

            }
            else
            {

               ASSERT(false);

            }

         }

      }
      ~item() override {}


      const ::file::path & user_path() const { return m_pathUser.has_char() ? m_pathUser : m_pathFinal; }
      const ::file::path & final_path() const { return m_pathFinal.has_char() ? m_pathFinal : m_pathUser; }

      ::file::path & user_path_reference() { return m_pathUser; }
      ::file::path & final_path_reference() { return m_pathFinal; }

      
      void set_user_path(const ::file::path & pathUser) { m_pathUser = pathUser; m_flags -= e_flag_final_path;}
      void set_final_path(const ::file::path & pathFinal) { ASSERT(pathFinal & e_flag_final_path); m_pathFinal = pathFinal; m_flags += e_flag_final_path; }


      int get_final_path_dir() const { return m_pathFinal.m_iDir; }
      void set_final_path_dir(int iDir) { m_pathFinal.m_iDir = iDir; }


      inline bool has_final_path() const { return m_flags.has(e_flag_final_path); }


      bool IsFolder() const;


   };


} // namespace file



