//
// Created by camilo on 2022-10-25 21:27 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "acid/filesystem/filesystem/path.h"


namespace file
{


   // by CAMILO <3tbs
   class CLASS_DECL_ACID action
   {
   public:


      watch *                          m_pwatch;
      watch_id                         m_watchid;
      ::file::path                     m_pathFolder;
      ::file::path                     m_pathFile;
      enumeration < enum_action >      m_eaction;


      action();
      ~action();


   };


} // namespace file



