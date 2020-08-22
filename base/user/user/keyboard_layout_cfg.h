#pragma once


namespace user
{


   class CLASS_DECL_AURA keyboard_layout_cfg :
      virtual public ::object
   {
   public:



      keyboard_layout_cfg();
      virtual ~keyboard_layout_cfg();

      bool CreateViews();

      void on_show();

   };


} // namespace user


