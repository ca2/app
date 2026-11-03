#include "platform.h"
#include "application.h"
#include "apex/graphics/early_configuration.h"
#include "system.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
//#include "aura/graphics/write_text/_constant.h"
#include "aura/graphics/write_text/font.h"
#include "bred/gpu/bred_approach.h"
#include "bred/graphics3d/graphics3d.h"
#include "bred/user/user/graphics3d_engine_host.h"
#include "acme/operating_system/operating_system.h"
#include "acme/platform/node.h"
#include "apex/graphics/early_configuration.h"


namespace bred
{


   application::application()
   {

      m_optionaGpuApi.main_add("opengl", "OpenGL");
      m_optionaGpuApi.main_add("vulkan", "Vulkan");   
#ifdef WINDOWS_DESKTOP
      m_optionaGpuApi.main_add("directx11", "DirectX 11");
      m_optionaGpuApi.main_add("directx12", "DirectX 12");
#endif
#if defined(__APPLE__)
      m_optionaGpuApi.main_add("metal", "Metal");
#endif

      
#ifdef WINDOWS_DESKTOP
      m_optionaDraw2dApi.main_add("gdiplus", "GDI+");
#endif
#if defined(__APPLE__)
      m_optionaDraw2dApi.main_add("quartz2d", "Quartz 2D");
      m_optionaDraw2dApi.main_add("metal", "Metal");
#endif
      m_optionaDraw2dApi.main_add("cairo", "cairo");
      m_optionaDraw2dApi.main_add("opengl", "OpenGL");
      m_optionaDraw2dApi.main_add("vulkan", "Vulkan");
#ifdef WINDOWS_DESKTOP
      m_optionaDraw2dApi.main_add("directx11", "DirectX 11");
      m_optionaDraw2dApi.main_add("directx12", "DirectX 12");
#endif
      m_optionaDraw2dApi.main_add("nanovg", "nanovg");
      m_optionaDraw2dApi.main_add("vkvg", "vkvg");
#ifdef WINDOWS_DESKTOP
      m_optionaDraw2dApi.main_add("direct2d", "Direct2D");
      m_optionaDraw2dApi.main_add("direct2d_for_directx11", "Direct2D for DirectX 11");
      m_optionaDraw2dApi.main_add("direct2d_for_directx12", "Direct2D for DirectX 12");
#endif

      m_optionaGraphics3dOutput.main_add("off_screen", "Off-Screen");
      m_optionaGraphics3dOutput.main_add("on_screen", "On-Screen (Swap Chain)");


   }


   application::~application()
   {

   }


   void application::on_set_platform()
   {

      ::berg::application::on_set_platform();

      factory()->add_factory_item < ::bred::system, ::platform::system >();

   }


   void application::common_construct()
   {


   }


   void application::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::axis::application::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   ::file::path application::get_main_weather_file_path(const ::scoped_string & scopedstringAspect)
   {

      return directory_system()->roaming() / "user/weather" / (scopedstringAspect + ".txt");

   }

   
   ::gpu::approach* application::get_gpu_approach()
   {

      if (!m_bGpu2)
      {

         throw ::exception(error_wrong_state, "Gpu application flag should be enabled to use gpu components.");

      }

      if (!m_pgpuapproach)
      {

         create_gpu_approach();

      }

      return m_pgpuapproach.get();

   }


   ::gpu::approach* application::gpu_approach()
   {

      return m_pgpuapproach.get();

   }


   //::string application::draw2d_get_default_implementation_name()
   //{
   //   
   //   auto strName = ::berg::application::draw2d_get_default_implementation_name();

   //   return strName;

   //}



   //void application::set_gpu_api(const ::scoped_string &scopedstrGpuApi) 
   //{

   //   if (m_strGpuImplementation.has_character()) return;

   //   try
   //   {

   //      set_application_file_setting_by_operating_system("graphics3d.txt", scopedstrGpuApi);

   //   }
   //   catch (...)
   //   {

   //      warning() << "Failed to set_gpu_api";

   //   }

   //   update_gpu_api_checkboxes();

   //   on_change_gpu_api();

   //}


   void application::update_gpu_api_checkboxes()
   {

      auto strGpuApi = _gpu_get_implementation_name_setting();

      if (strGpuApi.is_empty())
      {

         strGpuApi = gpu_get_implementation_name();

      }

      for (auto &poption: m_optionaGpuApi)
      {
         if (poption->m_strId != strGpuApi)
         {
            if (poption->checkbox() && poption->checkbox()->is_checked())
            {
               poption->checkbox()->set_check(::e_check_unchecked, ::e_source_sync);
            }
         }
      }
      auto poption = gpu_api(strGpuApi);
      if (poption->checkbox())
      {
         if (poption->checkbox() && !poption->checkbox()->is_checked())
         {
            poption->checkbox()->set_check(::e_check_checked, ::e_source_sync);
         }
      }

   }


   void application::on_change_gpu_api()
   {

      update_gpu_api_checkboxes();
      enable_draw2d_api_checkboxes(get_ok_draw2d_api());


   }


   void application::on_change_draw2d_api()
   {

      auto strDraw2dApi = _draw2d_get_implementation_name_setting();

      if (strDraw2dApi.is_empty())
      {

         strDraw2dApi = draw2d_get_implementation_name();

      }

      for (auto &poption: m_optionaDraw2dApi)
      {
         if (poption->m_strId == strDraw2dApi)
         {
            if (poption->checkbox() && !poption->checkbox()->is_checked())
            {
               poption->checkbox()->set_check(::e_check_checked, ::e_source_sync);
            }
         }
         else
         {
            if (poption->checkbox() && poption->checkbox()->is_checked())
            {
               poption->checkbox()->set_check(::e_check_unchecked, ::e_source_sync);
            }


         }
      }

      on_change_gpu_api();

   }


   //::string application::get_gpu_api()
   //{ 
   //   
   //   ::string strGpuApi = graphics3d_get_implementation_setting();
   //   strGpuApi.trim();
   //   strGpuApi.make_lower();

   //   //::string_array straOk;

   //   //straOk.add("opengl");
   //   //straOk.add("vulkan");
   //   //straOk.add("directx11");
   //   //straOk.add("directx12");

   //   if (!m_optionaGpuApi.find(strGpuApi))
   //      strGpuApi = m_optionaGpuApi.first()->m_strId;
   //   return strGpuApi;


   //}


//   ::string_array application::get_ok_gpu_api()
//   {
//
//      ::string_array straOk;
//
//      straOk.add("opengl");
//      straOk.add("vulkan");
//
//#if defined(WINDOWS_DESKTOP)
//
//      straOk.add("directx11");
//      straOk.add("directx12");
//
//#endif
//
//      return ::transfer(straOk);
//
//   }


   application::_001Option * application::gpu_api(const ::scoped_string &scopedstrGpuApi)
   {

      return m_optionaGpuApi[scopedstrGpuApi];

   }


   application::_001Option * application::draw2d_api(const ::scoped_string &scopedstrDraw2dApi)
   {

      return m_optionaDraw2dApi[scopedstrDraw2dApi];

   }



   application::_001Option *application::graphics3d_output(const ::scoped_string &scopedstrOutput)
   {

      return m_optionaGraphics3dOutput[scopedstrOutput];

   }


   ::string_array application::get_ok_draw2d_api()
   {

      auto strGpuApi = _gpu_get_implementation_name_setting();
      auto strOutput = get_graphics3d_output();
      auto eoperatingsystem = ::operating_system::get();
         //#ifdef WINDOWS_DESKTOP
//      constexpr bool windows = true;
//#else
//      constexpr bool windows = false;
//#endif
//#ifdef __APPLE__
//      constexpr bool apple = true;
//#else
//      constexpr bool apple = false;
//#endif

      ::graphics::early_configuration earlyconfiguration;
      auto available = earlyconfiguration.draw2d_apis(
         //strGpuApi.c_str(), strOutput == "off_screen", windows, apple);
         strGpuApi.c_str(), !use_gpu_swap_chain(), eoperatingsystem);
      ::string_array straOk;
      for (auto & value : available) straOk.add(value.c_str());
      return straOk;


   }


   //::string application::get_draw2d_api()
   //{

   //   auto strSetting = application_file_setting_by_operating_system("draw2d.txt");
   //   auto straOk = get_ok_draw2d_api();
   //   ::std::vector<::std::string> available;
   //   for (auto & value : straOk) available.emplace_back(value.c_str());
   //   return ::aura::graphics_configuration::draw2d_api(strSetting.c_str(), available).c_str();


   //}


   //::string application::get_graphics3d_output()
   //{

   //   ::string strOutput = graphics3d_get_output_setting();

   //   strOutput.trim();
   //   strOutput.make_lower();
   //   if (strOutput == "swap_chain") strOutput = "on_screen";

   //   if (!m_optionaGraphics3dOutput.find(strOutput))
   //   {

   //      strOutput = m_optionaGraphics3dOutput.first()->m_strId;

   //   }

   //   return strOutput;

   //}


   //void application::set_draw2d_api(const ::scoped_string &scopedstrDraw2dApi)
   //{

   //   try
   //   {

   //      set_application_file_setting_by_operating_system("draw2d.txt", scopedstrDraw2dApi);

   //   }
   //   catch (...)
   //   {

   //      warning() << "Failed to set_get";

   //   }

   //   on_change_draw2d_api();

   //}


   //void application::set_graphics3d_output(const ::scoped_string &scopedstrOutput)
   //{

   //   if (m_strGpuImplementation.has_character())
   //      return;

   //   try
   //   {

   //      set_application_file_setting("graphics3d_output.txt", scopedstrOutput);

   //   }
   //   catch (...)
   //   {

   //      warning() << "Failed to set_graphics3d_output";

   //   }

   //   on_change_graphics3d_output();

   //}


   void application::on_change_graphics3d_output()
   {

      auto strOutput = get_graphics3d_output();

      for (auto &poption: m_optionaGraphics3dOutput)
      {
         if (poption->m_strId != strOutput)
         {
            if (poption->checkbox() && poption->checkbox()->is_checked())
            {
               poption->checkbox()->set_check(::e_check_unchecked, ::e_source_sync);
            }
         }
      }
      auto poption = graphics3d_output(strOutput);
      if (poption->checkbox())
      {
         if (poption->checkbox() && !poption->checkbox()->is_checked())
         {
            poption->checkbox()->set_check(::e_check_checked, ::e_source_sync);
         }
      }

      on_change_gpu_api();

   }


   void application::enable_draw2d_api_checkboxes(const ::string_array & stra)
   {

      auto strCurrentDraw2dApi = _draw2d_get_implementation_name_setting();

      if (strCurrentDraw2dApi.is_empty())
      {

         strCurrentDraw2dApi = draw2d_get_implementation_name();

      }

      for (auto & poption : m_optionaDraw2dApi)
      {

         // Hide incompatible choices even while the parent form is not yet visible.
         if (stra.contains(poption->m_strId)) poption->show();
         else poption->hide();
         auto pcheckbox = poption->checkbox();
         if (pcheckbox)
         {
            auto echeck = poption->m_strId == strCurrentDraw2dApi ? e_check_checked : e_check_unchecked;
            if (pcheckbox->is_checked() != (echeck == e_check_checked))
               pcheckbox->set_check(echeck, ::e_source_sync);
         }

      }
      if (m_plinelayoutDraw2dApiSelection)
      {
         m_plinelayoutDraw2dApiSelection->set_need_layout();
         m_plinelayoutDraw2dApiSelection->set_need_perform_layout();
      }

   }



   void application::create_options_impact(const ::atom &atom, ::user::interaction *puserinteractionParent)
   {
      if (atom == "options_impact_handler://gpu")
      {
         auto playout = create_line_layout(puserinteractionParent, e_orientation_vertical);

         create_gpu_api_selection_options_body(playout);
      }
      else
      {
         ::berg::application::create_options_impact(atom, puserinteractionParent);
      }
   }

   void application::on_after_create_form(const ::atom & atom, ::user::interaction * puserinteractionParent)
   {

            if (atom == "options_impact_handler://gpu")
      {

               on_change_graphics3d_output();

      }
      else
      {
         ::berg::application::on_after_create_form(atom, puserinteractionParent);
      }

            

      }

   

   void application::create_gpu_api_selection_options_body(::user::interaction* pparent)
   {

      {

         auto pstillTitle = create_label<::user::still>(pparent, "GPU API");

         defer_constructø(pstillTitle->m_pwritetextfont);

         pstillTitle->m_pwritetextfont->create_font(e_font_sans_ui, 24_pt,::e_font_weight_bold);

         auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

         playoutLine->m_atomMatterId = "::user::line_layout(1)";

         ::string strGpuApi = _gpu_get_implementation_name_setting();

         //::string_array straGpuApiItem;
         //::string_array straGpuApiName;

         //straGpuApiItem.add("opengl");
         //straGpuApiName.add("OpenGL");
         //straGpuApiItem.add("vulkan");
         //straGpuApiName.add("Vulkan");
         //straGpuApiItem.add("directx11");
         //straGpuApiName.add("DirectX 11");
         //straGpuApiItem.add("directx12");
         //straGpuApiName.add("DirectX 12");

         for (auto & poption : m_optionaGpuApi)
         {
            //auto strGpuApiItem = straGpuApiItem[i];
            //auto strGpuApiName = straGpuApiName[i];
            poption->m_puserinteractionControl = create_check_box<::user::check_box>(playoutLine, ""); 
            poption->m_puserinteractionControl->m_rectangleMargin1.right = 1;
            //auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "");
            //m_mapGpuApiSelectionCheckBox[strGpuApiItem] = pcheckbox;
            if (poption->m_strId == strGpuApi)
            {
               poption->checkbox()->set_check(e_check_checked, ::e_source_initialize);
            }
            poption->checkbox()->enable_window(m_strGpuImplementation.is_empty());
            poption->checkbox()->check_changed(this) += [this, poption](auto &check)
            {
               auto bSet = check.payload().as_bool();
               if (bSet && poption->m_strId != _gpu_get_implementation_name_setting())
               {
                  _gpu_set_implementation_name_setting(poption->m_strId);
               }
            };
            poption->m_puserinteractionLabel = create_label<::user::still>(playoutLine, poption->m_strName);
            poption->m_puserinteractionLabel->m_rectangleMargin1.right = 16;
         }
      }

      {

         auto pstillTitle = create_label<::user::still>(pparent, "draw2d API");

         defer_constructø(pstillTitle->m_pwritetextfont);

         pstillTitle->m_pwritetextfont->create_font(e_font_sans_ui, 24_pt, ::e_font_weight_bold);

         auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

         m_plinelayoutDraw2dApiSelection = playoutLine;

         playoutLine->m_atomMatterId = "::user::line_layout(1)";

         ::string strDraw2dApi = _draw2d_get_implementation_name_setting();

//         ::string_array straDraw2dApiItem;
//         ::string_array straDraw2dApiName;
//
//#ifdef WINDOWS
//         straDraw2dApiItem.add("gdiplus");
//         straDraw2dApiName.add("GDI+");
//         straDraw2dApiItem.add("direct2d");
//         straDraw2dApiName.add("Direct2D");
//#else
//         straDraw2dApiItem.add("cairo");
//         straDraw2dApiName.add("cairo");
//#endif
//        
//         straDraw2dApiItem.add("opengl");
//         straDraw2dApiName.add("OpenGL");
//         straDraw2dApiItem.add("vulkan");
//         straDraw2dApiName.add("Vulkan");
//         straDraw2dApiItem.add("directx11");
//         straDraw2dApiName.add("DirectX 11");
//         straDraw2dApiItem.add("directx12");
//         straDraw2dApiName.add("DirectX 12");

         //straDraw2dApiItem.add("nanovg");
         //straDraw2dApiName.add("nanovg");
         //straDraw2dApiItem.add("vkvg");
         //straDraw2dApiName.add("vkvg");

         //for (::i32 i = 0; i < straDraw2dApiItem.size(); i++)
         for(auto &poption : m_optionaDraw2dApi)
         {
            //auto strDraw2dApiItem = straDraw2dApiItem[i];
            //auto strDraw2dApiName = straDraw2dApiName[i];
            auto pcheckbox = create_check_box<::user::check_box>(playoutLine, "");
            //m_mapDraw2dApiSelectionCheckBox[strDraw2dApiItem] = pcheckbox;
            poption->m_puserinteractionControl = pcheckbox;
            poption->m_puserinteractionControl->m_rectangleMargin1.right = 1;
            if (poption->m_strId == strDraw2dApi)
            {
               pcheckbox->set_check(e_check_checked, ::e_source_initialize);
            }
            pcheckbox->check_changed(this) += [this, poption](auto &check)
            {
               auto bSet = check.payload().as_bool();
               if (bSet && poption->m_strId != _draw2d_get_implementation_name_setting())
               {
                  _draw2d_set_implementation_name_setting(poption->m_strId);
               }
            };
            poption->m_puserinteractionLabel=create_label<::user::still>(playoutLine, poption->m_strName);
            poption->m_puserinteractionLabel->m_rectangleMargin1.right = 16;
         }
      }


      {

         auto pstillTitle = create_label<::user::still>(pparent, "graphics3d Output");

         defer_constructø(pstillTitle->m_pwritetextfont);

         pstillTitle->m_pwritetextfont->create_font(e_font_sans_ui, 24_pt, ::e_font_weight_bold);

         auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

         playoutLine->m_atomMatterId = "::user::line_layout(1)";

         ::string strOutput = get_graphics3d_output();

         //::string_array straOutput;
         //::string_array straOutputName;


         //straOutput.add("off_screen");
         //straOutputName.add("Off-Screen");
         //straOutput.add("on_screen");
         //straOutputName.add("On-Screen (Swap Chain)");

         //for (::i32 i = 0; i < straOutput.size(); i++)
         for (auto & poption : m_optionaGraphics3dOutput)
         {
            //auto strOutputItem = straOutput[i];
            //auto strOutputName = straOutputName[i];
            poption->m_puserinteractionControl = create_check_box<::user::check_box>(playoutLine, "");
            poption->m_puserinteractionControl->m_rectangleMargin1.right = 1;
            if (poption->m_strId == strOutput)
            {
               poption->checkbox()->set_check(e_check_checked, ::e_source_initialize);
            }
            poption->checkbox()->enable_window(m_strGpuImplementation.is_empty());
            poption->checkbox()->check_changed(this) += [this, poption](auto &check)
            {
               auto bSet = check.payload().as_bool();
               if (bSet && poption->m_strId != _get_graphics3d_output_setting())
               {
                  _set_graphics3d_output_setting(poption->m_strId);
               }
            };
            poption->m_puserinteractionLabel=create_label<::user::still>(playoutLine, poption->m_strName);
            poption->m_puserinteractionLabel->m_rectangleMargin1.right = 16;

         }
      }
      auto pbuttonRestartApp = create_button<::user::button>(pparent, "Restart App");

      pbuttonRestartApp->m_callbackOnClick =
         [this](::user::interaction *puserinteraction, ::item *pitem, ::user::activation_token *puseractivationtoken)->bool
      {


            node()->restart_application();

            //set_finish();
            
            return true;
            };

      on_change_graphics3d_output();

   }


   //#ifdef _OPENGL
   void application::create_gpu_approach()
   {

      if (m_pgpuapproach)
      {

         return;

      }

      //load_library("gpu_opengl");

      // A fixed application GPU must also win over a component factory that
      // another draw2d implementation may already have registered.
      auto strGpuOverride = m_strGpuImplementation;
      ::factory::factory_pointer pfactoryGpu;
      if (strGpuOverride.has_character())
      {
         pfactoryGpu = factory("gpu", gpu_get_implementation_name());
         pfactoryGpu->merge_to_global_factory();
      }
      else
      {
         pfactoryGpu = component_factory("gpu");
      }

      if (!pfactoryGpu)
      {

         ::string strGpuImplementation;

         ::string strDraw2dImplementation = m_papplication->draw2d_get_implementation_name();

         if (strDraw2dImplementation.is_empty())
         {

            strDraw2dImplementation = system()->component_factory_implementation_name("draw2d");

         }

         if (strDraw2dImplementation == "nanovg")
         {

            strGpuImplementation = "opengl";

         }
         else if (strDraw2dImplementation == "vkvg")
         {

            strGpuImplementation = "vulkan";

         }
         else if (strDraw2dImplementation == "vulkan")
         {

            strGpuImplementation = "vulkan";

         }
         else if (strDraw2dImplementation == "opengl")
         {

            strGpuImplementation = "opengl";

         }
         else if (strDraw2dImplementation == "directx11")
         {

            strGpuImplementation = "directx11";

         }
         else if (strDraw2dImplementation == "directx12")
         {

            strGpuImplementation = "directx12";

         }
         else if (strDraw2dImplementation == "gdiplus")
         {

            strGpuImplementation = gpu_get_implementation_name();

         }
         else if (strDraw2dImplementation == "cairo")
         {

            strGpuImplementation = gpu_get_implementation_name();

         }
         else if (strDraw2dImplementation == "quartz2d")
         {

            strGpuImplementation = gpu_get_implementation_name();

         }
         else if (strDraw2dImplementation.begins_eat("direct2d"))
         {

            strGpuImplementation = gpu_get_implementation_name();

            //if(!strGpuImplementation.case_insensitive_begins("directx"))
            //{
            //   
            //   strGpuImplementation = "directx12";

            //}

         }
         else
         {

            throw ::exception(error_not_implemented, "Unknown draw2d implementation: " + strDraw2dImplementation);

         }

         pfactoryGpu = factory("gpu", strGpuImplementation);

         pfactoryGpu->merge_to_global_factory();

      }

      //get_library("gpu_opengl");



      //if (!pfactoryGpu)
      //{

      //   error() <<"gpu_opengl ([a-z0-9_]+)_factory has failed";

      //   return pfactoryGpu;

      //}

      //auto estatus =

      pfactoryGpu->constructø(this, m_pgpuapproach);


      m_pgpuapproach->initialize_gpu_approach();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }

   
   ::graphics3d::graphics3d * application::graphics3d()
   {

      if (!m_pgraphics3d)
      {

         constructø(m_pgraphics3d);

         m_pgraphics3d->initialize_graphics3d();

      }

      return m_pgraphics3d;

   }


   void application::register_user_graphics3d(::collection::index i, ::user::graphics3d_engine_host * pusergraphics3denginehost)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_usergraphics3denginehosta.atø(i) = pusergraphics3denginehost;

   }


} // namespace bred



