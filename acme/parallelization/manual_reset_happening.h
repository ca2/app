//*****************************************************************************
//
//      Class:          manual_reset_happening
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an happening has
//                      occurred.
//
//*****************************************************************************


#pragma once


#include "happening.h"


// #define DECLARE_REUSABLE(TYPE) \
// TYPE * m_pnext; \
// ::factory_item::reusable_factory_item < TYPE, TYPE > * m_pfactory; \
// void delete_this() override { if(m_pfactory) m_pfactory->return_back(this); else delete this;}


class CLASS_DECL_ACME manual_reset_happening :
   public ::happening
{
public:


   //__creatable(manual_reset_happening);


   ::e_status m_estatus;
   // DECLARE_REUSABLE(manual_reset_happening);


   manual_reset_happening(char * sz = nullptr, bool bInitiallyOwn = false);
   ~manual_reset_happening() override;

   //void reuse() { reset_happening(); }

};

class manual_reset_happening;

class CLASS_DECL_ACME notify_lock :
   virtual public ::particle
{
public:


   manual_reset_happening  *               m_pmanualresethappening;


   ::pointer < ::pointer_array< ::subparticle > > m_psynca;
   
   
   notify_lock(manual_reset_happening * pmanualresethappening):
   m_pmanualresethappening(pmanualresethappening)
   {
      
   
   }
   void add(::subparticle *p)
   {
      
      if(!m_psynca)
      {
         
         __raw_construct_new(m_psynca);
         
      }
      
      m_psynca->add_unique(p);
      
//      for (int i = 0; i < m_iSyncCount; i++)
//      {
//         
//         auto & psync = m_synca[i];
//         
//         if(psync == p)
//         {
//            
//            return;
//            
//         }
//         
//      }
//
//      for (int i = 0; i < m_iSyncCount; i++)
//      {
//         
//         auto & psync = m_synca[i];
//         
//         if(!psync)
//         {
//            psync = p;
//            
//            return;
//            
//         }
//         
//      }
//         m_synca[m_iSyncCount] = p;
//         
//         m_iSyncCount++;
//         
      }

   void erase(::subparticle *p)
   {
      if(!m_psynca)
      {
         
         return;
      }
   
//      for (int i = 0; i < m_iSyncCount; i++)
//      {
//         
//         auto & psync = m_synca[i];
//if(psync == p)
//{
//   psync.release();
//   break;
//}
//
//      }

   }

   ~notify_lock() override
   {
      
      if(m_psynca)
      {

      for (auto & psync: *m_psynca)
      {
         
         //auto & psync = m_synca[i];
         if(psync)
         {
            psync->end_notify_lock(this);
            
         }
         
      }

      }

   }

};

