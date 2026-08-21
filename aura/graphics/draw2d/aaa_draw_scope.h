// Created by camilo on 2026-07-22 15:37 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


namespace draw2d
{


   class graphics_lease;


   class CLASS_DECL_AURA draw_scope
   {
   public:


      bool m_bOpen;

      ::draw2d::graphics_lease *m_pgraphicslease = nullptr;


      draw_scope();
      explicit draw_scope(::draw2d::graphics_lease &graphicslease);
      draw_scope(const draw_scope &) = delete;
      draw_scope &operator=(const draw_scope &) = delete;
      //draw_scope(draw_scope &&scope) noexcept;
      //draw_scope &operator=(draw_scope &&scope) noexcept;
      ~draw_scope() noexcept;


      explicit operator bool() const;
      void close();
      void close_noexcept() noexcept;


   };


} // namespace draw2d
