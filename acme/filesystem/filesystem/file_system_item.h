// Created by camilo on 2025-10-19 17:00 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:27 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 19:04 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


class CLASS_DECL_ACME file_system_item :
   virtual public ::subparticle
{
public:


   ::file_system_interface *     m_pfilesysteminterface;
   class ::time                  m_timeLastCheck2;
   ::file::e_type                m_etype;
   //::logic::boolean              m_bFileExists2;
   //::logic::boolean              m_bIsDir2;
   ::logic::boolean              m_bHasScript2;
   ::string                      m_strExpandMd5;
   ::particle_pointer            m_particlea[MAX_FILE_SYSTEM_ITEM_SLOT_COUNT];
   ::file::path                  m_pathReal1;
   ::file::path                  m_pathLogical1;



   //bool           m_bHasScript = false;
   //bool           m_bHasScriptCalculated = false;

   file_system_item();
   ~file_system_item() override;


   bool is_ok() const
   {

      if (::is_null(this))
      {

         return false;

      }

      return m_pathReal1.has_character() && m_pathReal1.is_existent_file_or_folder();

   }


   bool ok() const
   {

      if (::is_null(this))
      {

         return false;

      }

      return this->is_ok();
      
   }


   const ::file::path & path() const
   {

      return m_pathLogical1;

   }

   bool is_folder() const
   {

      if (::is_null(this))
      {

         return false;

      }

      return (m_etype & ::file::e_type_existent_folder) == ::file::e_type_existent_folder;

   }

   bool is_file() const
   {

      if (::is_null(this))
      {

         return false;

      }

      return (m_etype & ::file::e_type_existent_file) == ::file::e_type_existent_file;

   }

};



