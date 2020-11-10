#pragma once


#include <gtk/gtk.h>




typedef struct
{

  GtkApplication parent_instance;

  //g::u32 quit_inhibit;
  //GMenu *time;
  //g::u32 timeout;

} BloatPad; // you can search for BloatPad in 2017 and so Internet

typedef GtkApplicationClass BloatPadClass;



extern BloatPad * g_pappBloatPad;


void bloat_pad_run(const char * pszAppName, const char * pszProgName);




