#pragma once


namespace axis
{


   class CLASS_DECL_AXIS user :
      virtual public ::user::user
   {
   public:


      user();
      virtual ~user();


      virtual ::estatus init() override;
      virtual void term() override;


   };


} // namespace axis



