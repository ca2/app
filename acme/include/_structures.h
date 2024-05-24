// Created by camilo on 2022-11-02 05:06 <3ThomasBorregaardSorensen!!
#pragma once


union message_union
{

   void* m_p;
   ::message::particle* m_pparticle;
   ::message::key* m_pkey;
   ::message::mouse* m_pmouse;
   ::message::context_menu* m_pcontextmenu;

};




