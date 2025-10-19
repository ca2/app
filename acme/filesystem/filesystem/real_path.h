// Created by camilo on 2025-10-19 17:00 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


namespace programming
{


   class CLASS_DECL_APP_PROGRAMMING real_path
   {
   public:


      ::string       m_strName;
      ::file::path   m_pathReal;
      class ::time   m_timeLastCheck;
      //bool           m_bHasScript = false;
      //bool           m_bHasScriptCalculated = false;

      bool is_ok() const
      {

         return m_pathReal.has_character();

      }

   };


} // namespace programming




