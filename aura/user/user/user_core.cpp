//
// Created by camilo on 2024-10-29 08:25 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "user_core.h"


namespace user
{


   void core_user_layer::on_file_manager_open(::filemanager::data* pdata, ::file::item_array& itema)
   {
   }


   bool core_user_layer::get_fs_size(string& strSize, const ::string& pszPath, bool& bPending)
   {

      return false;

   }


   bool core_user_layer::get_fs_size(i64& i64Size, const ::string& pszPath, bool& bPending)
   {

      return false;

   }


   void core_user_layer::data_on_after_change(::message::message* pmessage)
   {
   }


   class keyboard* core_user_layer::keyboard()
   {

      return {};

   }


   bool core_user_layer::modal_get_color(::user::interaction* puiOwner, ::color::hls& hls)
   {

      return false;

   }


   void core_user_layer::AddToRecentFileList(const ::string& pszPathName)
   {
   }


   void core_user_layer::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {
   }


   void core_user_layer::_001OnFileNew()
   {
   }


   ::pointer<::user::list_header> core_user_layer::default_create_list_header(::particle* pparticle)
   {

      return {};

   }


   ::pointer<::user::mesh_data> core_user_layer::default_create_mesh_data(::particle* pparticle)
   {

      return {};

   }


   ::pointer<::user::list_data> core_user_layer::default_create_list_data(::particle* pparticle)
   {

      return {};

   }


   ::type_atom core_user_layer::default_type_mesh_data()
   {

return {};

   }


   ::type_atom core_user_layer::default_type_list_header()
   {

      return {};

   }


   ::type_atom core_user_layer::default_type_list_data()
   {

      return {};

   }


   void core_user_layer::will_use_impact_hint(::atom idImpact)
   {
   }


   //void core_user_layer::term_instance() override{}


   void core_user_layer::LoadStdProfileSettings(unsigned int nMaxMRU)
   {
   }


   ::collection::count core_user_layer::get_template_count() const
   {

      return 0;
   }


   ::pointer<::user::impact_system> core_user_layer::get_template(::collection::index index) const
   {

      return {};
   }


   ::user::document* core_user_layer::hold(::pointer<::user::interaction> pinteraction)
   {

return nullptr;

   }


   //void core_user_layer::initialize(::particle * pparticle) override{}


   //bool core_user_layer::do_prompt_file_name(::payload& payloadFile, string strTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument, const atom & atomFileManager = "file_manager_save"){}


   void core_user_layer::initialize_userex()
   {
   }


   void core_user_layer::userfs_init1()
   {
   }


   void core_user_layer::userfs_process_init()
   {
   }


   //void core_user_layer::create_html(){}

   //::pointer<::userex::userex>create_userex(){}
   //::pointer<::userfs::userfs>create_userfs(){}


   ::type_atom core_user_layer::get_pane_tab_impact_type_info()
   {

      return {};

   }


   //::type_atom get_simple_frame_window_type_info() override{}
   //::type_atom get_simple_child_frame_type_info(){}


   //void core_user_layer::on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array& patha) override{}



} // namespace user
