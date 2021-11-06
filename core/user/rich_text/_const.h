#pragma once




namespace user
{


   namespace rich_text
   {


      enum e_script
      {

         script_normal,
         script_subscript,
         script_superscript,

      };

      enum e_line_height
      {

         line_height_single,
         line_height_one_and_a_half,
         line_height_double

      };

      enum e_attribute
      {

         attribute_bold,
         attribute_italic,
         attribute_underline,
         attribute_family,
         attribute_size,
         attribute_foreground,
         attribute_background,
         attribute_script,
         attribute_line_height,
         attribute_align

      };

      using eattribute = flags < e_attribute >;


   } // namespace rich_text


} // namespace user
