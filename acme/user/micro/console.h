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
    ::array < char >              m_cha1;
    ::string_array                m_stra;
::pointer < ::micro::interchange > m_pinterchange;

   console();
   ~console() override;

   virtual void create_console(::micro::interchange * pinterchange);
   virtual void _stdout_console();


};



} // namespace micro



