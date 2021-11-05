#pragma once


#include <gtk/gtk.h>




typedef struct
{

  GtkApplication parent_instance;

  //g::u32 quit_inhibit;
  //GMenu *time;
  //g::u32 timeout;

} ApexApplication; // you can search for ApexApplication in 2017 and so Internet

typedef GtkApplicationClass BloatPadClass;



extern ApexApplication * g_papexapplication;


void apex_application_run(const ::string & pszAppName, const ::string & pszProgName);




