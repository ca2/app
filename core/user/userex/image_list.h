#pragma once


#include "acme/filesystem/filesystem/file_dialog.h"
#include "berg/user/user/image_list.h"


namespace userex
{


   class CLASS_DECL_CORE image_list_impact :
      virtual public ::user::image_list_impact
   {
   public:


      ::file::path                     m_pathFolder;
      ::pointer < ::file::listing >    m_plisting;
      //string_array                   m_straPattern;
      //string_array                   m_straPatternNames;
      ::file::file_dialog_filter       m_filedialogfilter;
      string                           m_strLinkPrefix;
      int                              m_iForkAddDib;

      image_list_impact();
      ~image_list_impact() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual string_array get_ls_pattern_stra() const;

      void update_data(bool bSaveAndValidate) override;

      bool _001GetItemText(string & str, ::collection::index iItem) override;
#ifdef _DEBUG
      long long increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      long long decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }
#endif
      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      virtual void load_images();

      virtual string get_link_prefix();

      virtual ::file::path get_link_path(const ::scoped_string & scopedstrLink);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);



   };


} // namespace tranquillum


