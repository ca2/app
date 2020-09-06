#pragma once


namespace user
{


   class CLASS_DECL_AXIS validate :
      virtual public ::object
   {
   public:


      validate();
      virtual ~validate();


      virtual ::estatus Validate(string& strParam, ::user::control_descriptor* pdescriptor);



   };




}