//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSørensen
// Generalized by camilo on 31/01/2022 14:28 <3ThomasBorregaardSørensen!!
//
#pragma once


class nano_details_window :
   virtual public nano_message_box
{
public:



   nano_details_window();
   ~nano_details_window() override;


   void calculate_size() override;



   void on_click(const ::atom& atom, int x, int y) override;


};
