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


      enum e_type
      {

         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,

      };

      EPaneView m_eview;
      e_type m_etype;


      ::impact_update();
      virtual ~::impact_update();
      
      
      void set_type(e_type e_type);

      bool is_type_of(e_type e_type);


   };


} // namespace turboc















