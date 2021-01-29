// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA display :
      virtual public ::matter
   {
   public:



      display();
      virtual ~display();

      virtual iptr get_os_data() const;

      virtual window * default_root_window();

   };


   using display_map = iptr_map < __pointer(display) >;


} // namespace windowing



