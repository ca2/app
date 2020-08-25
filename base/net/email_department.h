#pragma once


namespace net
{


   class CLASS_DECL_BASE email_department :
      virtual public ::aura::department
   {
   public:


      email_department();


      bool utf8_mail(class ::net::email * pemail);


      virtual bool syntax_is_valid(const string & strEmailAddress);

      virtual bool is_valid_public_address(const string& strEmailAddress);



      


   };


} // namespace net





