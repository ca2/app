// Created by Camilo on 2023-01-31 01:36 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "../networking.h"
#include "../address.h"
#include "acme/platform/node.h"


#if defined(BSD_UNIX)
//
//void arp_a(void *p, void(*callback)(void *p, void * addr, const char * ip_address, const char * host, const char * status));


namespace networking_bsd
{

   struct arp_a :
      virtual public ::particle
   {
   
      ::pointer < ::item_array > m_pitema;

      arp_a(::particle * p)
      {
         
         initialize(p);
         
         __defer_construct_new(m_pitema);
         
         node()->arp_a(this, &arp_a::callback);
         
      }

      static void callback(void *p, ::u32 uIp, const char * status)
      {
      
         auto parpa = (arp_a *) p;
      
         parpa->step(uIp, status);

      }
   
      
      void step(::u32 uIp, const char * status)
      {
         
         in_addr inaddr;
         
         inaddr.s_addr = uIp;

         information() << "arp_a status : " << status;

         auto paddress = __create_new<::networking_bsd::address>();
         
         paddress->set_address(inaddr);

         m_pitema->add(paddress);

      }
  
   };


   ::pointer < ::item_array > networking::list_computers()
   {

      arp_a arpa(this);
      
      //__defer_construct_new(callback.m_pitema);

//      auto callback = [this, pitema](void * addr, const char * ip_address, const char * host, const char * status)
//      {
//         
//         
//
//         
//      };
      
      //arp_a(callback);
       

      for (::index iItem = 0; iItem < arpa.m_pitema->size(); iItem++)
      {

         auto pitem = arpa.m_pitema->element_at(iItem);

         pitem->m_item.m_iItem = iItem;

      }

      return arpa.m_pitema;

   }


} // namespace networking_bsd



#endif



