// Greatly changed by camilo on 2025 <3ThomasBorregaardSørensen!!
#pragma once


#include "berg/platform/application.h"
#include "acme/prototype/collection/array_map.h"


namespace bred
{


   class CLASS_DECL_BRED application :
      virtual public ::berg::application
   {
   public:


      class _001Option : virtual public ::particle
      {
      public:
         
         ::string                            m_strId;
         ::string                            m_strName;
         ::pointer<::user::interaction>      m_puserinteractionControl;
         ::pointer<::user::interaction>      m_puserinteractionLabel;

         _001Option() {}
         _001Option(const ::scoped_string &scopedstrId) : m_strId(scopedstrId) {}
         _001Option(const ::scoped_string &scopedstrId, const ::scoped_string &scopedstrName) :
             m_strId(scopedstrId), m_strName(scopedstrName)
         {
         }
         ~_001Option() override {}

         ::string key() const { return m_strId; }
         ::user::check_box *checkbox()
         {
            return m_puserinteractionControl.is_null() ? nullptr : m_puserinteractionControl.raw_cast<::user::check_box>();
         }
         void hide()
         {
            if (m_puserinteractionControl)
            {
               m_puserinteractionControl->hide();
            }
            if (m_puserinteractionLabel)
            {
               m_puserinteractionLabel->hide();
            }
         }
         void show()
         {
            if (m_puserinteractionControl)
            {
               m_puserinteractionControl->show();
            }
            if (m_puserinteractionLabel)
            {
               m_puserinteractionLabel->show();
            }
         }
      };


      //class draw2d_api : virtual public ::particle
      //{
      //public:

      //   ::string                         m_strDraw2dApi;
      //   ::string                         m_strDraw2ApiName;
      //   ::pointer<::user::check_box>     m_pcheckbox;


      //   draw2d_api() {}
      //   draw2d_api(const ::scoped_string & scopedstr):m_strDraw2dApi(scopedstr) {}
      //   ~draw2d_api() override {}

      //   ::string key() const { return m_strDraw2dApi; }

      //};


      //class graphics3d_output : virtual public ::particle
      //{
      //public:

      //   ::string                         m_strOutput;
      //   ::string                         m_strOutputName;
      //   ::pointer<::user::check_box>     m_pcheckbox;


      //   graphics3d_output() {}
      //   graphics3d_output(const ::scoped_string &scopedstr) : m_strOutput(scopedstr) {}
      //   ~graphics3d_output() override {}

      //   ::string key() const { return m_strOutput; }

      //};


      ::pointer_map< _001Option >            m_optionaGpuApi;
      ::pointer_map< _001Option >            m_optionaDraw2dApi;
      ::pointer_map< _001Option >            m_optionaGraphics3dOutput;

      ::pointer<::user::line_layout>         m_plinelayoutDraw2dApiSelection;


      application();
      ~application() override;


      void on_set_platform() override;
      

      void common_construct();


      //virtual ::pointer < ::graphics3d::application > start_graphics3d_aplication();


      void initialize(::particle * pparticle) override;
      //virtual ::pointer<progress_control>show_progress(::user::interaction* puiParent, const ::scoped_string & scopedstrTitle, ::collection::count iProgressCount);

      ::file::path get_main_weather_file_path(const ::scoped_string & scopedstringAspect) override;


      ::gpu::approach* get_gpu_approach() override;
      ::gpu::approach* gpu_approach() override;
      void create_gpu_approach() override;

      ::string draw2d_get_default_implementation_name() override;


      virtual void enable_draw2d_api_checkboxes(const ::string_array &stra);
      void create_options_impact(const ::atom &atom, ::user::interaction *pparent) override;
      void on_after_create_form(const ::atom &atom, ::user::interaction *pparent) override;
      virtual void create_gpu_api_selection_options_body(::user::interaction *pparent);
      virtual void set_gpu_api(const ::scoped_string &scopedstrGpuApi);
      virtual void set_draw2d_api(const ::scoped_string &scopedstrGpuApi);
      virtual void set_graphics3d_output(const ::scoped_string &scopedstrOutput);
      virtual ::string get_gpu_api();
      virtual ::string get_draw2d_api();
      //virtual ::string_array get_ok_gpu_api();
      virtual ::string_array get_ok_draw2d_api();
      virtual _001Option * gpu_api(const ::scoped_string &scopedstrGpuApi);
      virtual _001Option * draw2d_api(const ::scoped_string &scopedstrDraw2dApi);
      virtual _001Option * graphics3d_output(const ::scoped_string &scopedstrOuput);
      virtual ::string get_graphics3d_output();
      virtual void update_gpu_api_checkboxes();
      virtual void on_change_gpu_api();
      virtual void on_change_draw2d_api();
      virtual void on_change_graphics3d_output();

      
   };


} // namespace bred




