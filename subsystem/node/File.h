// Created by camilo on 2026-04-05 18:22 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem/_common_header.h"


namespace subsystem
{

   class CLASS_DECL_SUBSYSTEM FileInterface :
      virtual public ::Particle
   {
   public:



      //File();
      //virtual ~FileInterface() =0 ;

      virtual void * _HANDLE() = 0;

   };

    //using FileInterface = particle_interface<FileInterface>;


   class CLASS_DECL_SUBSYSTEM FileComposite :
   virtual public Composite<FileInterface >
   {
   public:

        ImplementCompositeø(File, file)
      //File();
      //~File() override;

      void * _HANDLE() override {return m_pfile->_HANDLE();}

   };


    class CLASS_DECL_SUBSYSTEM FileAggregate :
    virtual public Aggregate< FileComposite >
    {
    public:

        ImplementBaseø(File);

    };


   class CLASS_DECL_SUBSYSTEM File :
 virtual public Object < FileAggregate >
   {
   public:

   };



} // namespace subsystem



