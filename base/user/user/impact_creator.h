#pragma once


namespace user
{


   class CLASS_DECL_BASE impact_creator :
      virtual public ::matter
   {
   public:


      //__pointer(impact_creator)  m_pimpactcreator;


      //impact_creator();
      //virtual ~impact_creator();

      
      //void set_impact_creator(impact_creator* pimpactcreator);


      virtual void on_create_impact(::user::impact_data * pimpactdata);


      virtual bool create_impact(::user::impact_data * pimpactdata);


      


   };


} // namespace user



