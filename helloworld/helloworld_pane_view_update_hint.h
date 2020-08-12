#pragma once


namespace helloworld
{


   enum EPaneView
   {
      impact_none,
      impact_menu,
      PaneViewHelloWorld,
      PaneViewHelloWorldSwitcher
      
   };


   class CLASS_DECL_APP_HELLOWORLD ::update :
      public object
   {
   public:


      enum e_type
      {

         TypeNone,
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,

      };

      EPaneView m_eview;
      e_type m_etype;


      ::update();
      virtual ~::update();


      void set_type(e_type e_type);

      bool is_type_of(e_type e_type);


   };


} // namespace helloworld















