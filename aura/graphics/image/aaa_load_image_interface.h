// Created by camilo on 2026-07-21 00:30 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


class CLASS_DECL_ACME load_image_interface : virtual public ::particle
{
public:


   virtual void on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan);

   virtual void create_nanosvg(char_pointer pszXml, ::f64 dDpi);


};
