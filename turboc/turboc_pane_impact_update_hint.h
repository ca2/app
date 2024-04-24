#pragma once


namespace turboc
{


   enum EPaneImpact
   {
      impact_none,
      MAIN_IMPACT,
      PaneImpactHelloMultiverseSwitcher,
      
   };


   class CLASS_DECL_TURBOC ::impact_update :
      public object  
   {
   public:


      enum enum_type
      {

         TypeGetImpact,
         TypeSetImpact,
         TypeOnShowKaraoke,
         TypeOnShowImpact,

      };

      EPaneImpact m_eview;
      enum_type m_etype;


      ::impact_update();
      virtual ~::impact_update();
      
      
      void set_type(enum_type enum_type);

      bool is_type_of(enum_type enum_type);


   };


} // namespace turboc















