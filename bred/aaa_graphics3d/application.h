// Created by camilo on 2025-05-16 23:15 <3ThomasBorregaardSorensen!!
#pragma once


namespace graphics3d
{


   class CLASS_DECL_BRED application :
      virtual public ::object
   {
   public:


      ::i32 m_iWidth;
      ::i32 m_iHeight;

      ::pointer < ::graphics3d::container > m_pcontainer;


      ::function < void(void*, ::i32, ::i32, ::i32)> m_callbackOffscreen;


      application();
      ~application();



      virtual ::file::path assets_folder();

      virtual ::file::path shaders_folder();


      virtual void initialize_application(::graphics3d::container* pcontainer);

      virtual void run_application();

      virtual void resize(::i32 cx, ::i32 cy);

      virtual void load_game_objects();


      virtual void handle_mouse_move(::i32 x, ::i32 y);


   };


} // namespace graphics3d



