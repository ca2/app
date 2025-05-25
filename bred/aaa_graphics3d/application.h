// Created by camilo on 2025-05-16 23:15 <3ThomasBorregaardSorensen!!
#pragma once


namespace graphics3d
{


   class CLASS_DECL_BRED application :
      virtual public ::object
   {
   public:


      int m_iWidth;
      int m_iHeight;

      ::pointer < ::graphics3d::container > m_pcontainer;


      ::function < void(void*, int, int, int)> m_callbackOffscreen;


      application();
      ~application();



      virtual ::file::path assets_folder();

      virtual ::file::path shaders_folder();


      virtual void initialize_application(::graphics3d::container* pcontainer);

      virtual void run_application();

      virtual void resize(int cx, int cy);

      virtual void load_game_objects();


      virtual void handle_mouse_move(int x, int y);


   };


} // namespace graphics3d



