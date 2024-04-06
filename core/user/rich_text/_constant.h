#pragma once


namespace user
{


   namespace rich_text
   {


      enum enum_script
      {

         e_script_normal,
         e_script_subscript,
         e_script_superscript,

      };

      
      enum enum_line_height
      {

         e_line_height_single,
         e_line_height_one_and_a_half,
         e_line_height_double

      };


      enum enum_attribute
      {

         e_attribute_bold,
         e_attribute_italic,
         e_attribute_underline,
         e_attribute_family,
         e_attribute_size,
         e_attribute_foreground,
         e_attribute_background,
         e_attribute_script,
         e_attribute_line_height,
         e_attribute_align

      };


      using e_attribute = flags < enum_attribute >;


   } // namespace rich_text


} // namespace user



