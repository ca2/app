#pragma once


namespace turboc
{


   enum EPaneView
   {
      impact_none,
      MAIN_IMPACT,
      PaneViewHelloMultiverseSwitcher,
      
   };


   class CLASS_DECL_TURBOC ::impact_update :
      public object  
   {
   public:


      enum enum_type
      {

         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,

      };

      EPaneView m_eview;
      enum_type m_etype;


      ::impact_update();
      virtual ~::impact_update();
      
      
      void set_type(enum_type enum_type);

      bool is_type_of(enum_type enum_type);


   };


} // namespace turboc















