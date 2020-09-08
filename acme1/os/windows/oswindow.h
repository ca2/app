#pragma once


using oswindow = HWND;


class CLASS_DECL_ACME oswindow_array :
   public comparable_array < oswindow, oswindow >
{
public:


   void SortByZOrder();
   void SortSiblingsByZOrder();
   void top_windows_by_z_order();


};



