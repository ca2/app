//
// Created by camilo on 31/01/2022 05:00 PM <3ThomasBorregaardSorensen!! Thomas Likes Number 5!!
//
#pragma once


namespace nano{namespace graphics{


class CLASS_DECL_ACME object :
   virtual public ::particle
{
public:


   bool              m_bModified;
   void *            m_pthis;


   object();
   ~object();


   virtual void destroy();


   virtual void * operating_system_data();


   virtual void update(::nano::graphics::device * pnanodevice);


};





   } // namespace graphics


} // namespace nano



