#pragma once


namespace draw2d
{


   class draw2d;
   class graphics;


   class CLASS_DECL_AURA graphics_lease
   {
   public:


      ::pointer<::draw2d::draw2d> m_pdraw2d;
      ::draw2d::graphics_pointer m_pgraphics;
      ::image::image_pointer m_pimage;
      bool m_bDamaged = false;


      graphics_lease();
      graphics_lease(
         ::draw2d::draw2d * pdraw2d,
         ::draw2d::graphics * pgraphics,
         ::image::image * pimage);
      graphics_lease(const graphics_lease &) = delete;
      graphics_lease & operator=(const graphics_lease &) = delete;
      graphics_lease(graphics_lease && lease) noexcept;
      graphics_lease & operator=(graphics_lease && lease) noexcept;
      ~graphics_lease() noexcept;


      explicit operator bool() const;
      ::draw2d::graphics * get() const;
      ::draw2d::graphics * operator->() const;
      void mark_damaged();
      void close();
      void close_noexcept() noexcept;


   };


} // namespace draw2d
