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


} // namespace simple_shader















