#include "framework.h"
#include "apex_application.h"



void sn_start_context();

GtkWindow * g_pmainwindow = nullptr;

G_DEFINE_TYPE (ApexApplication, apex_application, GTK_TYPE_APPLICATION)

ApexApplication * g_papexapplication = nullptr;

ApexApplication * apex_application_new (const ::string & pszAppName, const ::string & pszProgName)
{

   ApexApplication * apex_application;

   g_set_application_name (pszAppName);

   apex_application = (ApexApplication *) g_object_new (apex_application_get_type (),
                                          "application-atom", pszProgName,
                                          "flags", G_APPLICATION_FLAGS_NONE,
                                          "inactivity-timeout", 30000,
                                          "register-session", true,
                                          nullptr);

   return apex_application;

}


gboolean linux_start_system(gpointer data)
{

   GApplication * papp = g_application_get_default ();

   ::aura::system * psystem = (::aura::system *) data;

   //psystem->m_strAppId = psystem->m_pmaindata->m_strAppId;

   //psystem->startup_command(psystem->m_pmaindata);

   //psystem->request(psystem->m_pcommand);

   return false;

}


void apex_application_activate(GApplication * application)
{

   //GCancellable * pc = g_cancellable_new();

   //GError * perror = nullptr;

   //g_application_register(application, pc, &perror);
   //new_window(application, nullptr);

   #ifndef RASPBERRYPIOS

   sn_start_context();

   #endif

}


void apex_application_run_mainloop(GApplication * application)
{

   ApexApplication * papexapplication = (ApexApplication *) application;

   GtkApplication * app = GTK_APPLICATION (application);

   G_APPLICATION_CLASS (apex_application_parent_class)->run_mainloop(application);

}


void apex_application_init (ApexApplication *app)
{

}


void apex_application_startup (GApplication *application)
{

   ApexApplication * papexapplication = (ApexApplication *) application;

   GtkApplication * app = GTK_APPLICATION (application);

   G_APPLICATION_CLASS (apex_application_parent_class)->startup (application);

   g_pmainwindow = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));

   gtk_application_add_window(app, g_pmainwindow);

   ::aura::system * psystem = (::aura::system *) ::get_context_system();

   //psystem->m_strAppId = psystem->m_pmaindata->m_strAppId;

   //psystem->startup_command(psystem->m_pmaindata);

   //psystem->request(psystem->m_pcommand);

   g_application_hold(application);

}


void apex_application_open(GApplication * application, GFile ** files, gint n_files, const gchar * hint)
{

//   gint i;
//
//   for (i = 0; i < n_files; i++)
//   {
//
//      new_window (application, files[i]);
//
//   }

}


void apex_application_finalize (GObject *object)
{

   G_OBJECT_CLASS (apex_application_parent_class)->destroy (object);

}


void apex_application_shutdown(GApplication *application)
{

   ApexApplication * papexapplication = (ApexApplication *) application;

   /*

   if (papexapplication->timeout)
   {

      g_source_erase (papexapplication->timeout);

      papexapplication->timeout = 0;

   }

   */

   G_APPLICATION_CLASS (apex_application_parent_class)->shutdown (application);

}


void apex_application_class_init (BloatPadClass * pclass)
{

   GApplicationClass *pappclass    = G_APPLICATION_CLASS (pclass);

   GObjectClass *pobjectclass              = G_OBJECT_CLASS (pclass);

   pappclass->startup              = apex_application_startup;
   pappclass->shutdown             = apex_application_shutdown;
   pappclass->activate             = apex_application_activate;
   pappclass->open                 = apex_application_open;

   pappclass->run_mainloop         = apex_application_run_mainloop;

   pobjectclass->destroy                  = apex_application_finalize;

}


void apex_application_run(const ::string & pszAppName, const ::string & pszProgName)
{

   g_papexapplication = apex_application_new(pszAppName, pszProgName);

   if(g_papexapplication == nullptr)
   {

      information("Failed to initialize GtkApplication (gtk_application_new return nullptr)");

      return;

   }

   int status = g_application_run (G_APPLICATION (g_papexapplication), 0, nullptr);

   g_object_unref(g_papexapplication);

   g_papexapplication = nullptr;

}




