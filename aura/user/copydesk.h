#pragma once


namespace user
{


   class CLASS_DECL_AURA copydesk :
      virtual public ::object
   {
   public:


      enum e_op
      {

         op_copy,
         op_cut,

      };


      enum enum_flag
      {

         e_flag_none = 0,
         flag_prevent_data_blob = 1,

      };


      ::write_text::font_pointer          m_pfont;
      ::windowing::window *               m_pwindow;


      copydesk();
      ~copydesk() override;


      virtual void initialize_copydesk(::windowing::window * pwindow);
      virtual void destroy() override;

      /// pass nullptr to ppatha to probe if there is at least one existing
      /// directory or file in str parsed as multiline.
      /// Pass a valid pointer at ppatha, to retrive all existing
      ///
      virtual void string_to_filea(::file::patha * ppatha, const ::string & str);

      virtual void set_filea(const ::file::patha & stra, e_op eop);
      virtual void get_filea(::file::patha & stra, e_op & eop);
      virtual bool has_filea();

      virtual void set_plain_text(const ::string & str, bool bForceSetIfEmpty = false);
      virtual void get_plain_text(string & str, enum_flag eflag = e_flag_none);
      virtual bool has_plain_text();

      virtual void desk_to_image(::image_pointer & pimage);
      virtual void image_to_desk(const ::image * pimage);
      virtual bool has_image();


      virtual void _set_filea(const ::file::patha & stra, e_op eop);
      virtual void _get_filea(::file::patha & stra, e_op & eop);
      virtual bool _has_filea();

      virtual void _set_plain_text(const ::string & str);
      virtual void _get_plain_text(string & str);
      virtual bool _has_plain_text();

      virtual void _desk_to_image(::image * pimage);
      virtual void _image_to_desk(const ::image * pimage);
      virtual bool _has_image();

   };


   typedef ___pointer < copydesk > copydesk_pointer;


} // namespace user



