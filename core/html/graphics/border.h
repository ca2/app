#pragma once


namespace html
{


   class CLASS_DECL_CORE border :
      public ::rectangle_f32
   {
   public:

      enum e_style
      {

         style_solid,

      };


      color32_t    crLeft;
      color32_t    crTop;
      color32_t    crRight;
      color32_t    crBottom;
      
      e_style     styleLeft;
      e_style     styleTop;
      e_style     styleRight;
      e_style     styleBottom;

      
   };


} // namespace html




