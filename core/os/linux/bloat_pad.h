#pragma once


#include <gtk/gtk.h>




typedef struct
{

  GtkApplication parent_instance;

  //guint quit_inhibit;
  //GMenu *time;
  //guint timeout;

} ApexApplication; // you can search for ApexApplication in 2017 and so Internet

typedef GtkApplicationClass BloatPadClass;



extern ApexApplication * g_papexapplication;


void apex_application_run(const char * pszAppName, const char * pszProgName);




