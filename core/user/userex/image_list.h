#pragma once


#include "base/user/user/image_list.h"


namespace userex
{


   class CLASS_DECL_CORE image_list_view :
      virtual public ::user::image_list_view
   {
   public:


      ::file::path                     m_pathFolder;
      __pointer(::file::listing)       m_plisting;
      string_array                     m_straPattern;
      string_array                     m_straPatternNames;
      string                           m_strLinkPrefix;
      int                              m_iForkAddDib;

      image_list_view();
      ~image_list_view() override;


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

      virtual string_array get_ls_pattern_stra() const;

      void update_data(bool bSaveAndValidate) override;

      bool _001GetItemText(string & str, index iItem) override;
#ifdef _DEBUG
      i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
#endif
      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual void load_images();

      virtual string get_link_prefix();

      virtual ::file::path get_link_path(string strLink);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);



   };


} // namespace tranquillum


