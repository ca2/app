#pragma once


namespace simple_shader
{


   enum EPaneView
   {
      impact_none,
      PaneViewMenu,
      PaneViewSimpleDrawing
   };


   class CLASS_DECL_APP_SIMPLE_SHADER ::update :
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


} // namespace simple_shader















