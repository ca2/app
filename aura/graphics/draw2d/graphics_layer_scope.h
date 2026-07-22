#pragma once


namespace draw2d
{


   class graphics_lease;


   class CLASS_DECL_AURA graphics_layer_scope
   {
   public:


      ::draw2d::graphics_lease * m_pgraphicslease = nullptr;
      ::draw2d::graphics_pointer m_pgraphics;
      bool m_bOpen = false;


      graphics_layer_scope();
      explicit graphics_layer_scope(::draw2d::graphics_lease & graphicslease);
      graphics_layer_scope(const graphics_layer_scope &) = delete;
      graphics_layer_scope & operator=(const graphics_layer_scope &) = delete;
      graphics_layer_scope(graphics_layer_scope && scope) noexcept;
      graphics_layer_scope & operator=(graphics_layer_scope && scope) noexcept;
      ~graphics_layer_scope() noexcept;


      explicit operator bool() const;
      void close();
      void close_noexcept() noexcept;


   };


} // namespace draw2d
