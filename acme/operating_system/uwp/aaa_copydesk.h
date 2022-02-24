#pragma once


namespace universal_windows
{


   class CLASS_DECL_ACME copydesk :
      virtual public ::user::copydesk
   {
   public:


      copydesk();
      virtual ~copydesk();


      virtual void initialize(::matter * pobject) override;
      virtual void destroy() override;

      virtual bool _set_filea(const ::file::path_array & stra, e_op eop) override;
      virtual bool _get_filea(::file::path_array & stra, e_op & eop) override;
      virtual bool _has_filea() override;

      virtual bool _set_plain_text(const ::string & str) override;
      virtual bool _get_plain_text(string & str) override;
      virtual bool _has_plain_text() override;

      virtual bool _desk_to_image(::image * pimage) override;
      virtual bool _image_to_desk(const ::image * pimage) override;
      virtual bool _has_image() override;

   };


} // namespace universal_windows



