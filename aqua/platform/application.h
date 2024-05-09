#pragma once


#include "apex/platform/application.h"
#include "aqua/multimedia/media_item_picker_callback.h"


namespace aqua
{


   class CLASS_DECL_AQUA application :
      virtual public ::apex::application,
      virtual public ::aqua::media_item_picker_callback
   {
   public:


      ::pointer<::aqua::game>                      m_paquagame;
      ::pointer<::networking::application>         m_pnetworkingapplication;
     

      application();
      ~application() override;
      

      void common_construct();


      //inline ::aqua::system* system();


      void initialize(::particle * pparticle) override;


      void on_set_platform() override;

      //void on_initialize_application(::main* pmain) override;

      //virtual ::pointer<progress_control>show_progress(::user::interaction* puiParent, const ::scoped_string & scopedstrTitle, ::collection::count iProgressCount);

      void init2() override;


      void exit_application() override;

      virtual void game_on_create(::aqua::game * pgame);

      bool load_cached_string(string& str, const ::atom& atom, bool bLoadStringTable) override;

      void did_pick_media_item(::aqua::media_item * pmediaitem) override;

      virtual ::aqua::media_player * assign_media_player_to_media_item(::aqua::media_item * pmediaitem);
      
   };


} // namespace aqua




