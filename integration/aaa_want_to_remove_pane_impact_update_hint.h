#pragma once


namespace simple_drawing
{


   enum EPaneImpact
   {
      impact_none,
      PaneImpactMenu,
      PaneImpactSimpleDrawing
   };


   class CLASS_DECL_APP_INTEGRATION ::update :
      public object
   {
   public:


      enum enum_type
      {

         TypeNone,
         TypeGetImpact,
         TypeSetImpact,
         TypeOnShowKaraoke,
         TypeOnShowImpact,

      };

      EPaneImpact m_eview;
      enum_type m_etype;


      ::update();
      virtual ~::update();


      void set_type(enum_type enum_type);

      bool is_type_of(enum_type enum_type);


   };


} // namespace simple_drawing















