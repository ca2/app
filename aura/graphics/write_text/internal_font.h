// Create by camilo on 2024-12-30 19:53 <3ThomasBorregaardSorensen!!
#pragma once


namespace write_text
{


   class CLASS_DECL_AURA internal_font :
      virtual public ::matter
   {
   public:


      internal_font();
      ~internal_font() override;


      virtual void load_from_memory(::memory_base * pmemory);
      virtual void on_create_font(::draw2d::graphics * pgraphics, ::write_text::font * pfont);

   };


} // namespace write_text


