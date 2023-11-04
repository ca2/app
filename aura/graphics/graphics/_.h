#pragma once


namespace windowing_universal_windows
{


   class buffer;


} // namespace windowing_universal_windows


namespace windowing_win32
{


   class buffer;


} // namespace windowing_win32


namespace OPERATING_SYSTEM_NAMESPACE
{


   class buffer;


} // namespace OPERATING_SYSTEM_NAMESPACE


namespace graphics
{


   class graphics;
   class buffer_item;


   class output_purpose;


} // namespace graphics

namespace graphics
{

   
   enum enum_output_purpose
   {

      e_output_purpose_none,
      e_output_purpose_fps = 1,
      //e_output_purpose_auto = 1,
      e_output_purpose_offscreen = 0x80,
      e_output_purpose_offscreen_fps = e_output_purpose_offscreen | e_output_purpose_fps,
      e_output_purpose_screen = 0x8000,
      e_output_purpose_screen_fps = e_output_purpose_screen | e_output_purpose_fps,
      //e_output_purpose_screen_auto = e_output_purpose_screen | e_output_purpose_auto,

   };


} // namespace graphics



