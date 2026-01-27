#include "framework.h"
#include "application.h"
#include "system.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "aura/graphics/write_text/font.h"
#include "bred/gpu/bred_approach.h"
#include "acme/platform/node.h"


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

      if (!m_bGpu)
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


   ::string application::draw2d_get_default_implementation_name()
   {
      
      auto strName = ::berg::application::draw2d_get_default_implementation_name();

      return strName;

   }


   void application::set_gpu_api(const ::scoped_string &scopedstrGpuApi) 
   {

      try
      {

         set_application_file_setting_by_operating_system("graphics3d.txt", scopedstrGpuApi);

      }
      catch (...)
      {

         warning() << "Failed to set_gpu_api";

      }

      update_gpu_api_checkboxes();

      on_change_gpu_api();

   }


   void application::update_gpu_api_checkboxes()
   {

      auto strGpuApi = get_gpu_api();

      for (auto &poption: m_optionaGpuApi)
      {
         if (poption->m_strId != strGpuApi)
         {
            if (poption->checkbox()->is_checked())
            {
               poption->checkbox()->set_check(::e_check_unchecked, ::e_source_sync);
            }
         }
      }
      auto poption = gpu_api(strGpuApi);
      if (poption->checkbox())
      {
         if (!poption->checkbox()->is_checked())
         {
            poption->checkbox()->set_check(::e_check_checked, ::e_source_sync);
         }
      }

   }


   void application::on_change_gpu_api()
   {

      auto strGpuApi = get_gpu_api();
      auto strDraw2dApi = get_draw2d_api();
      auto strOutput = get_graphics3d_output();

      ::string_array straOkDraw2dApi = get_ok_draw2d_api();

      //::string_array straOkGpuApi = get_ok_gpu_api();

      if (!straOkDraw2dApi.contains(strDraw2dApi))
      {

         if (!m_optionaDraw2dApi.find(strDraw2dApi))
         {

            if (strDraw2dApi != strGpuApi)
            {

               set_gpu_api(strDraw2dApi);

            }

         }

      }

      enable_draw2d_api_checkboxes(straOkDraw2dApi);

   }


   void application::on_change_draw2d_api()
   {

      auto strDraw2dApi = get_draw2d_api();

      for (auto &poption: m_optionaDraw2dApi)
      {
         if (poption->m_strId == strDraw2dApi)
         {
            if (!poption->checkbox()->is_checked())
            {
               poption->checkbox()->set_check(::e_check_checked, ::e_source_sync);
            }
         }
         else
         {
            if (poption->checkbox()->is_checked())
            {
               poption->checkbox()->set_check(::e_check_unchecked, ::e_source_sync);
            }


         }
      }

      on_change_gpu_api();

   }


   ::string application::get_gpu_api()
   { 
      
      ::string strGpuApi = application_file_setting_by_operating_system("graphics3d.txt");

      //::string_array straOk;

      //straOk.add("opengl");
      //straOk.add("vulkan");
      //straOk.add("directx11");
      //straOk.add("directx12");

      if (!m_optionaGpuApi.find(strGpuApi))
      {
         
         //strGpuApi = "opengl";
         strGpuApi = m_optionaGpuApi.first()->m_strId;

      }

      return strGpuApi;

   }


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

      ::string strGpuApi = get_gpu_api();

      ::string strOutput = get_graphics3d_output();

      ::string_array straOk;

      if (strGpuApi == "opengl")
      {

         if (strOutput == "on_screen")
         {

            straOk.add("opengl");
            straOk.add("nanovg");

         }
         else if (strOutput == "off_screen")
         {
            
#ifdef WINDOWS_DESKTOP
            straOk.add("gdiplus");
#elif defined(__APPLE__)
            straOk.add("quartz2d");
#else
            straOk.add("cairo");
#endif
            
         }

      }
      else if (strGpuApi == "vulkan")
      {

         if (strOutput == "on_screen")
         {

            straOk.add("vulkan");
            straOk.add("vkvg");

         }
         else if (strOutput == "off_screen")
         {

#ifdef WINDOWS_DESKTOP
            straOk.add("gdiplus");
#elif defined(__APPLE__)
            straOk.add("quartz2d");
#else
            straOk.add("cairo");
#endif

         }

      }
#ifdef WINDOWS_DESKTOP
      else if (strGpuApi == "directx11")
      {
         
         if (strOutput == "on_screen")
         {

            straOk.add("directx11");
            straOk.add("direct2d");

         }
         else if (strOutput == "off_screen")
         {

            straOk.add("gdiplus");
            straOk.add("direct2d");

         }

      }
      else if (strGpuApi == "directx12")
      {

         if (strOutput == "on_screen")
         {

            straOk.add("directx12");
            straOk.add("direct2d");

         }
         else if (strOutput == "off_screen")
         {

            straOk.add("gdiplus");
            straOk.add("direct2d");

         }

      }

#endif

      return ::transfer(straOk);

   }


   ::string application::get_draw2d_api()
   {

      ::string strDraw2dApi = application_file_setting_by_operating_system("draw2d.txt");

      auto straOk = get_ok_draw2d_api();

      if (!straOk.contains(strDraw2dApi))
      {

         strDraw2dApi = straOk.first();

      }

      return strDraw2dApi;

   }


   ::string application::get_graphics3d_output()
   {

      ::string strOutput = application_file_setting("graphics3d_output.txt");

      if (!m_optionaGraphics3dOutput.find(strOutput))
      {

         strOutput = m_optionaGraphics3dOutput.first()->m_strId;

      }

      return strOutput;

   }


   void application::set_draw2d_api(const ::scoped_string &scopedstrDraw2dApi)
   {

      try
      {

         set_application_file_setting_by_operating_system("draw2d.txt", scopedstrDraw2dApi);

      }
      catch (...)
      {

         warning() << "Failed to set_get";

      }

      on_change_draw2d_api();

   }


   void application::set_graphics3d_output(const ::scoped_string &scopedstrOutput)
   {

      try
      {

         set_application_file_setting("graphics3d_output.txt", scopedstrOutput);

      }
      catch (...)
      {

         warning() << "Failed to set_graphics3d_output";

      }

      on_change_graphics3d_output();

   }


   void application::on_change_graphics3d_output()
   {

      auto strOutput = get_graphics3d_output();

      for (auto &poption: m_optionaGraphics3dOutput)
      {
         if (poption->m_strId != strOutput)
         {
            if (poption->checkbox()->is_checked())
            {
               poption->checkbox()->set_check(::e_check_unchecked, ::e_source_sync);
            }
         }
      }
      auto poption = graphics3d_output(strOutput);
      if (poption->checkbox())
      {
         if (!poption->checkbox()->is_checked())
         {
            poption->checkbox()->set_check(::e_check_checked, ::e_source_sync);
         }
      }

      on_change_gpu_api();

   }


   void application::enable_draw2d_api_checkboxes(const ::string_array &stra)
   {

      auto strCurrentDraw2dApi = get_draw2d_api();

      for (auto& poption : m_optionaDraw2dApi)
      {

         if (!stra.contains(poption->m_strId))
         {

            if (poption->checkbox()->is_this_screen_visible(::user::e_layout_sketch))
            {

               poption->hide();

            }

         }

         if (poption->m_strId == strCurrentDraw2dApi)
         {

            if (!poption->checkbox()->is_checked())
            {

               poption->checkbox()->set_check(::e_check_checked, ::e_source_sync);

            }

         }
         else
         {

            if (poption->checkbox()->is_checked())
            {

               poption->checkbox()->set_check(::e_check_unchecked, ::e_source_sync);

            }

         }

      }

      for (auto& strDraw2dApi : stra)
      {

         auto poptionDraw2dApi = draw2d_api(strDraw2dApi);

         auto pcheckbox = poptionDraw2dApi->checkbox();

         if (pcheckbox)
         {

            if (!pcheckbox->is_this_screen_visible(::user::e_layout_sketch))
            {

               poptionDraw2dApi->show();

            }

         }

      }

      m_plinelayoutDraw2dApiSelection->set_need_layout();

      m_plinelayoutDraw2dApiSelection->set_need_perform_layout();

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

         ødefer_construct(pstillTitle->m_pfont);

         pstillTitle->m_pfont->create_font(e_font_sans_ui, 24_pt);

         auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

         playoutLine->m_atomMatterId = "::user::line_layout(1)";

         ::string strGpuApi = get_gpu_api();

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
            poption->checkbox()->check_changed(this) += [this, poption](auto &check)
            {
               auto bSet = check.payload().as_bool();
               if (bSet)
               {
                  set_gpu_api(poption->m_strId);
               }
            };
            poption->m_puserinteractionLabel = create_label<::user::still>(playoutLine, poption->m_strName);
            poption->m_puserinteractionLabel->m_rectangleMargin1.right = 16;
         }
      }

      {

         auto pstillTitle = create_label<::user::still>(pparent, "draw2d API");

         ødefer_construct(pstillTitle->m_pfont);

         pstillTitle->m_pfont->create_font(e_font_sans_ui, 24_pt);

         auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

         m_plinelayoutDraw2dApiSelection = playoutLine;

         playoutLine->m_atomMatterId = "::user::line_layout(1)";

         ::string strDraw2dApi = get_draw2d_api();

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

         //for (int i = 0; i < straDraw2dApiItem.size(); i++)
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
               if (bSet)
               {
                  set_draw2d_api(poption->m_strId);
               }
            };
            poption->m_puserinteractionLabel=create_label<::user::still>(playoutLine, poption->m_strName);
            poption->m_puserinteractionLabel->m_rectangleMargin1.right = 16;
         }
      }


      {

         auto pstillTitle = create_label<::user::still>(pparent, "graphics3d Output");

         ødefer_construct(pstillTitle->m_pfont);

         pstillTitle->m_pfont->create_font(e_font_sans_ui, 24_pt);

         auto playoutLine = create_line_layout(pparent, e_orientation_horizontal);

         playoutLine->m_atomMatterId = "::user::line_layout(1)";

         ::string strOutput = get_graphics3d_output();

         //::string_array straOutput;
         //::string_array straOutputName;


         //straOutput.add("off_screen");
         //straOutputName.add("Off-Screen");
         //straOutput.add("on_screen");
         //straOutputName.add("On-Screen (Swap Chain)");

         //for (int i = 0; i < straOutput.size(); i++)
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
            poption->checkbox()->check_changed(this) += [this, poption](auto &check)
            {
               auto bSet = check.payload().as_bool();
               if (bSet)
               {
                  set_graphics3d_output(poption->m_strId);
               }
            };
            poption->m_puserinteractionLabel=create_label<::user::still>(playoutLine, poption->m_strName);
            poption->m_puserinteractionLabel->m_rectangleMargin1.right = 16;

         }
      }
      auto pbuttonRestartApp = create_button<::user::button>(pparent, "Restart App");

      pbuttonRestartApp->m_callbackOnClick =
         [this](::user::interaction *puserinteraction, ::item *pitem, ::user::activation_token *puseractivationtoken)
      {


            node()->restart_application();

            //set_finish();
            
            return true;
            };

      //on_change_graphics3d_output();

   }


   //#ifdef _OPENGL
   void application::create_gpu_approach()
   {

      if (m_pgpuapproach)
      {

         return;

      }

      //load_library("gpu_opengl");

      auto pfactoryGpu = component_factory("gpu");

      if (!pfactoryGpu)
      {

         ::string strGpuImplementation;

         ::string strDraw2dImplementation = m_papplication->draw2d_get_default_implementation_name();

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

            strGpuImplementation = graphics3d_get_implementation_name();

         }
         else if (strDraw2dImplementation == "cairo")
         {

            strGpuImplementation = graphics3d_get_implementation_name();

         }
         else if (strDraw2dImplementation == "quartz2d")
         {

            strGpuImplementation = graphics3d_get_implementation_name();

         }
         else if (strDraw2dImplementation.begins_eat("direct2d"))
         {

            strGpuImplementation = graphics3d_get_implementation_name();

            if(!strGpuImplementation.case_insensitive_begins("directx"))
            {
               
               strGpuImplementation = "directx12";

            }

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

      pfactoryGpu->øconstruct(this, m_pgpuapproach);


      m_pgpuapproach->initialize_gpu_approach();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


} // namespace bred



