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
      virtual ~image_list_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual string_array get_ls_pattern_stra() const;

      virtual bool update_data(bool bSaveAndValidate) override;

      virtual bool _001GetItemText(string & str, index iItem) override;
#ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }
#endif
      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual void load_images();

      virtual string get_link_prefix();

      virtual ::file::path get_link_path(string strLink);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnDestroy);



   };


} // namespace tranquillum


