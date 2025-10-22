// Created by camilo on 2025-10-19 17:00 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:27 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 19:04 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


class CLASS_DECL_ACME file_system_item :
   virtual public ::subparticle
{
protected:


   friend class file_system;


   ::file::path                  m_pathReal2;


public:


   ::file_system_interface *     m_pfilesysteminterface;
   class ::time                  m_timeLastCheck2;
   ::logic::boolean              m_bFileExists2;
   ::logic::boolean              m_bIsDir2;
   ::logic::boolean              m_bHasScript2;
   ::string                      m_strExpandMd5;

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

      return m_pathReal2.has_character() && m_pathReal2.is_existent_file_or_folder();

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

      return m_pathReal2;

   }

};



