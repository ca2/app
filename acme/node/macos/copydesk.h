#pragma once


namespace macos
{


   class CLASS_DECL_ACME copydesk :
      virtual public ::user::copydesk
   {
   public:

      long        m_lTicket;
      bool        m_bHasFile;
      bool        m_bHasText;
      bool        m_bHasDib;

      dispatch_source_t m_ds;

      copydesk();
      virtual ~copydesk();


      virtual ::estatus initialize(::generic * pobjectContext) override;
      virtual void finalize() override;

      virtual bool _set_filea(const ::file::patha & stra, e_op eop) override;
      virtual bool _get_filea(::file::patha & stra, e_op & eop) override;
      virtual bool _has_filea() override;

      virtual bool _os_has_filea();
      
      virtual bool _os_clipboard_has_changed();

      virtual bool _set_plain_text(const string & str) override;
      virtual bool _get_plain_text(string & str) override;
      virtual bool _has_plain_text() override;

      virtual bool _os_has_plain_text();


      virtual bool _desk_to_image(::image * pimage) override;
      virtual bool _image_to_desk(const ::image * pimage) override;
      virtual bool _has_image() override;

      virtual bool _os_has_image();


      virtual void _os_step();
      virtual void _on_os_clipboard_changed();


   };


} // namespace macos



