// Created by camilo on 2023-08-12 20:38 <3ThomasBorregaardSorensen!!
#pragma once


//#include "application.h"
//#include "user.h"
#include "aura/user/user/scroll_base.h"
//#include "apex/handler/manager.h"
//#include "apex/platform/api.h"
//#include "apex/platform/api_client.h"
//#include "apex/platform/app_consumer.h"



namespace user
{




   class CLASS_DECL_CORE list2 :
      virtual public ::user::scroll_base
   {
   public:


      //::pointer < user_list_main_impact >       m_pmainimpact;


      list2();
      ~list2() override;

      void install_message_routing(::channel * psender) override;
      DECLARE_MESSAGE_HANDLER(on_message_create);




      // void fill_task();



      //void parse(const ::string& pszSource);

      //void start_build(i32 iItem = -1);

      //void PostFillTask(string& strFile, uptr uiTimer);

      //void _001OnSort() override;
      /// bool GetSongPath(string& str, ::raw::index iItem);

      void handle(::topic * ptopic, ::context * pcontext) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      //virtual void update_data();
      //virtual void add_user(const ::scoped_string & scopedstrEmail);
      //virtual void erase_user(const ::scoped_string & scopedstrEmail);

      //bool on_click(::item * pitem) override;


   };


} // namespace RedDotLogicsInternal_license_manager


