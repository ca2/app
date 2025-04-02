//
// Created by camilo on 2024-10-28 06:08 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


//   struct CLASS_DECL_ACME core_application_layer_t
//   {
//
//
//      ::pointer<::userex::pane_tab_impact>     m_ppaneimpactCore;
//      ::pointer < ::filemanager::filemanager> m_pfilemanager;
//
//
//   };


   class CLASS_DECL_ACME core_application_layer
   {
   public:


      virtual void initialize_rich_text_kit();

      virtual string prepare_impact_options();
      virtual string prepare_impact_options_header();
      virtual string prepare_impact_options_main_body();
      virtual string prepare_impact_options_footer();


      virtual ::filemanager::filemanager * filemanager();


   };


} // namespace platform




