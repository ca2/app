//
// Created by camilo on 2024-09-26 17:48 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace micro
{



   class CLASS_DECL_ACME console :
      virtual public ::particle
   {
   public:

      map < char, ::collection::index >         m_mapCharIndex;
      ::array < char >                          m_cha1;
      ::string_array_base                            m_stra;
      ::pointer < ::micro::dialog >             m_pdialog;


      console();
      ~console() override;


      virtual void create_console(::micro::dialog * pdialog);
      virtual void _stdout_console();


   };



} // namespace micro



