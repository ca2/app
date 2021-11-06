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


      enum enum_type
      {

         TypeNone,
         TypeGetView,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,

      };

      EPaneView m_eview;
      enum_type m_etype;


      ::update();
      virtual ~::update();


      void set_type(enum_type enum_type);

      bool is_type_of(enum_type enum_type);


   };


} // namespace helloworld















