// From impact.h on 2023-01-15 09:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "base/user/user/impact.h"
#include "apex/platform/app_consumer.h"


namespace app_integration
{


   class CLASS_DECL_APP_INTEGRATION impact :
      virtual public app_consumer < application, ::user::impact >
   {
   public:

      string_array                              m_straName;
      ::pointer_array < ::string_array >        m_str2aOutput;

      ::string          m_strName;
      //::string          m_strRelease;
      //::string          m_strPlatform;
      //::string          m_strConfiguration;

      ::file::path      m_pathDownloadURL;


      int               m_iExitCode;
      ::string_array    m_straOutput;
      ::file::path      m_pathIntegration;


      impact();
      ~impact() override;

      
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


#ifdef _DEBUG
      int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


      //::file::path get_path();

      void fill();
      void add_platform(const ::scoped_string & scopedstrPlatform);
      void add_configuration(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
      void prepare();
      void start();


      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

   };


} // namespace simple_drawing


