#pragma once


#include <gtk/gtk.h>




typedef struct
{

  GtkApplication parent_instance;

  //guint quit_inhibit;
  //GMenu *time;
  //guint timeout;

} BloatPad; // you can search for BloatPad in 2017 and so Internet

typedef GtkApplicationClass BloatPadClass;



extern BloatPad * g_pappBloatPad;


void bloat_pad_run(const char * pszAppName, const char * pszProgName);




