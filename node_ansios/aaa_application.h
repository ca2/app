#pragma once


//#include <gtk/gtk.h>




typedef struct
{

  GtkApplication parent_instance;

  //g::u32 quit_inhibit;
  //GMenu *time;
  //g::u32 timeout;

} ApexApplication; // you can search for ApexApplication in 2017 and so Internet

typedef GtkApplicationClass ApexApplicationClass;



extern ApexApplication * g_papexapplication;


void apex_application_run(const char * pszAppName, const char * pszProgName);






void apex_application_set_application_menu(::apex::application_menu * papplicationmenu, ::apex::application * papp);


