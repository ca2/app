// Created by camilo on 2024-11-06 19:49 <3ThomasBorregaardSorensen!!
#pragma once


//#include "aura/windowing/::menu::item.h"
//#include "aura/windowing/menu.h"
#include "acme/user/user/interaction.h"


namespace acme
{


   namespace user
   {


      class CLASS_DECL_ACME frame_interaction :
         virtual public ::acme::user::interaction
      {
      public:


         union
         {
            
            
            struct
            {
               
               
               bool                                      m_bNcActive : 1;
               bool                                      m_bWindowVisible : 1;
               bool                                      m_bMinimizeBox : 1;
               bool                                      m_bMaximizeBox : 1;
               bool                                      m_bResizeable : 1;
               bool                                      m_bCapture : 1;
               bool                                      m_bStartCentered : 1;
               bool                                      m_bArbitraryPositioning : 1;
               bool                                      m_bTopMost : 1;


            };
            
            
            unsigned long long m_uAcmeUserFrameInteractionFlags;


         };


         frame_interaction();
         ~frame_interaction() override;

         
         ::pointer<::operating_system::a_system_menu> create_system_menu(bool bContextual) override;
        

      };


   } // namespace user


} // namespace acme



