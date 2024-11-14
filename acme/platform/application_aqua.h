//
// Created by camilo on 2024-10-24 22:46 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


   struct CLASS_DECL_ACME aqua_application_layer_t
   {


      ::pointer<::aqua::game>                      m_paquagame;
      //::pointer<::networking::application>         m_p_networkingapplication;


   };


   class CLASS_DECL_ACME aqua_application_layer
   {
   public:


      virtual void game_on_create(::aqua::game * pgame);

//      bool load_cached_string(string & str, const ::atom & atom, bool bLoadStringTable) override;

//      void did_pick_media_item(::aqua::media_item * pmediaitem) override;

      virtual ::aqua::media_player * assign_media_player_to_media_item(::aqua::media_item * pmediaitem);


   };


} // namespace platform



