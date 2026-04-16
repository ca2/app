// Created by camilo on 2026-04-05 18:22 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem/_common_header.h"


namespace subsystem
{

   class CLASS_DECL_SUBSYSTEM FileInterface :
      virtual public ::particle_base
   {
   public:



      //File();
      //virtual ~FileInterface() =0 ;

      virtual void * _HANDLE() = 0;

   };

    //using FileInterface = particle_interface<FileInterface>;


   class CLASS_DECL_SUBSYSTEM FileComposite :
   virtual public composite<FileInterface >
   {
   public:

        implement_compositeø(File, file)
      //File();
      //~File() override;

      void * _HANDLE() override {return m_pfile->_HANDLE();}

   };


    class CLASS_DECL_SUBSYSTEM File :
    virtual public aggregate< FileComposite >
    {
    public:

        implement_baseø(File);

    };


} // namespace subsystem



