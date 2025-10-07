// Created by camilo on 2023-05-28 19:24 <3ThomasBorregaardSorensen!!
#pragma once


namespace microsoft
{


   class visual_studio :
      virtual public ::particle
   {
   public:

      
      visual_studio();
      ~visual_studio() override;


      ::string_array_base get_instances();


      ::string get_a_visual_studio_2022_instance();


      ::file::path get_an_existing_visual_studio_2022_install_location();



   };


} /// namespace microsoft






