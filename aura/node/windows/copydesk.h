#pragma once


namespace windows
{


   class CLASS_DECL_AURA copydesk :
      virtual public ::user::copydesk,
      virtual public ::user::message_queue
   {
   public:


      //HWND m_hwnd;

      //__pointer(::user::interaction)      m_puserinteraction;

      /// negative value undefined
      ::count  m_cFileCount;
      /// -2 value undefined
      int   m_iPriorityTextFormat;
      /// negative value undefined
      int  m_iFilea;
      /// negative value undefined
      int  m_iText;
      /// negative value undefined
      int  m_iDib;


      copydesk();
      virtual ~copydesk();


      //static lresult WINAPI WindowProc(HWND hwnd, ::u32 message, wparam wparam, lparam lparam);


      DECL_GEN_SIGNAL(_001OnClipboardUpdate);
      DECL_GEN_SIGNAL(_001OnDestroy);

      virtual void install_message_routing(::channel * pchannel) override;



      virtual ::e_status initialize(::layered * pobjectContext) override;
      virtual void finalize() override;


      virtual void OnClipboardUpdate();

      virtual ::count _get_file_count();
      virtual int _get_priority_text_format();

      virtual HGLOBAL hglobal_get_filea(const ::file::patha & stra);
      virtual HGLOBAL hglobal_get_wide_text(const string & str);
      virtual HGLOBAL hglobal_get_utf8_text(const string & str);
      virtual HGLOBAL hglobal_get_image(const ::image * pimage);

      virtual bool _set_filea(const ::file::patha & stra, e_op eop) override;
      virtual bool _get_filea(::file::patha & stra, e_op & eop) override;
      virtual bool _has_filea() override;

      virtual bool _set_plain_text(const string & str) override;
      virtual bool _get_plain_text(string & str) override;
      virtual bool _has_plain_text() override;

      virtual bool _desk_to_image(::image * pimage) override;
      virtual bool _image_to_desk(const ::image * pimage) override;
      virtual bool _has_image() override;

   };


} // namespace windows



