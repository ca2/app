//
// Created by camilo on 2022-10-25 21:27 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "acme/filesystem/filesystem/path.h"


namespace file
{


   // by CAMILO <3tbs
   class CLASS_DECL_ACME action
   {
   public:


      watch *                          m_pfilewatch;
      //watch_id                         m_pfilewatch;
      ::file::path                     m_pathFolder;
      ::file::path                     m_pathFile;
      enumeration < enum_action >      m_eaction;


      action();
      ~action();


   };


} // namespace file



