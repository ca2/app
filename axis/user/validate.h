#pragma once


namespace user
{


   class CLASS_DECL_AXIS validate :
      virtual public ::object
   {
   public:


      validate();
      virtual ~validate();


      virtual ::e_status Validate(string& strParam, ::user::control_descriptor* pdescriptor);



   };




}