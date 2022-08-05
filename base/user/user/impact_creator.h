#pragma once


namespace user
{


   class CLASS_DECL_BASE impact_creator :
      virtual public ::matter
   {
   public:


      virtual void on_create_impact(::user::impact_data * pimpactdata);


      virtual bool impact_creator_create_impact(::user::impact_data * pimpactdata);


   };


} // namespace user



