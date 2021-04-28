#pragma once


namespace linux
{


   class CLASS_DECL_APEX copydesk :
      virtual public ::user::copydesk
   {
   public:




      copydesk();
      virtual ~copydesk();


      virtual ::e_status initialize(::object * pobject) override;
      virtual ::e_status finalize() override;

      virtual bool _set_filea(const ::file::patha & patha, e_op eop) override;
      virtual bool _get_filea(::file::patha & patha, e_op & eop) override;
      virtual bool _has_filea() override;


      //virtual bool set_plain_text(const string & str) override;
      virtual bool _set_plain_text(const string & str) override;
      virtual bool _get_plain_text(string & str) override;
      virtual bool _has_plain_text() override;

      virtual bool _desk_to_image(::image * pimage) override;
      virtual bool _image_to_desk(const ::image * pimage) override;
      virtual bool _has_image() override;

   };


} // namespace linux



