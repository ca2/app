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


      virtual ::e_status initialize_copydesk(::windowing::window * pwindow);
      virtual ::e_status destroy() override;

      /// pass nullptr to ppatha to probe if there is at least one existing
      /// directory or file in str parsed as multiline.
      /// Pass a valid pointer at ppatha, to retrive all existing
      ///
      virtual ::e_status string_to_filea(::file::patha * ppatha, const ::string & str);

      virtual ::e_status set_filea(const ::file::patha & stra, e_op eop);
      virtual ::e_status get_filea(::file::patha & stra, e_op & eop);
      virtual bool has_filea();

      virtual ::e_status set_plain_text(const ::string & str, bool bForceSetIfEmpty = false);
      virtual ::e_status get_plain_text(string & str, enum_flag eflag = e_flag_none);
      virtual bool has_plain_text();

      virtual ::e_status desk_to_image(::image_pointer & pimage);
      virtual ::e_status image_to_desk(const ::image * pimage);
      virtual bool has_image();


      virtual ::e_status _set_filea(const ::file::patha & stra, e_op eop);
      virtual ::e_status _get_filea(::file::patha & stra, e_op & eop);
      virtual bool _has_filea();

      virtual ::e_status _set_plain_text(const ::string & str);
      virtual ::e_status _get_plain_text(string & str);
      virtual bool _has_plain_text();

      virtual ::e_status _desk_to_image(::image * pimage);
      virtual ::e_status _image_to_desk(const ::image * pimage);
      virtual bool _has_image();

   };


   typedef ___pointer < copydesk > copydesk_pointer;


} // namespace user



