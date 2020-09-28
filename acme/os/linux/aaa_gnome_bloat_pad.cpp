#include "framework.h"
#include "bloat_pad.h"



void sn_start_context();

GtkWindow * g_pmainwindow = nullptr;

G_DEFINE_TYPE (BloatPad, bloat_pad, GTK_TYPE_APPLICATION)

BloatPad * g_pappBloatPad = nullptr;

BloatPad * bloat_pad_new (const char * pszAppName, const char * pszProgName)
{

   BloatPad * bloat_pad;

   //g_set_application_name (pszAppName);

   bloat_pad = (BloatPad *) g_object_new (bloat_pad_get_type (),
                                          "application-id", pszProgName,
                                          "flags", G_APPLICATION_FLAGS_NONE,
                                          "inactivity-timeout", 30000,
                                          "register-session", TRUE,
                                          nullptr);

   return bloat_pad;

}


gboolean linux_start_system(gpointer data)
{

   GApplication * papp = g_application_get_default ();

   ::acme::system * psystem = (::acme::system *) data;

   //psystem->m_strAppId = psystem->m_pmaindata->m_strAppId;

   //psystem->startup_command(psystem->m_pmaindata);

   //psystem->request(psystem->m_pcommand);

   return FALSE;

}


void bloat_pad_activate(GApplication * application)
{

   //GCancellable * pc = g_cancellable_new();

   //GError * perror = nullptr;

   //g_application_register(application, pc, &perror);
   //new_window(application, nullptr);

   #ifndef RASPBIAN

   sn_start_context();

   #endif

}


void bloat_pad_run_mainloop(GApplication * application)
{

   BloatPad * bloatpad = (BloatPad *) application;

   GtkApplication * app = GTK_APPLICATION (application);

   G_APPLICATION_CLASS (bloat_pad_parent_class)->run_mainloop(application);

}


void bloat_pad_init (BloatPad *app)
{

}


void bloat_pad_startup (GApplication *application)
{

   BloatPad * bloatpad = (BloatPad *) application;

   GtkApplication * app = GTK_APPLICATION (application);

   G_APPLICATION_CLASS (bloat_pad_parent_class)->startup (application);

   g_pmainwindow = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));

   gtk_application_add_window(app, g_pmainwindow);

   ::acme::system * psystem = (::acme::system *) ::get_context_system();

   //psystem->m_strAppId = psystem->m_pmaindata->m_strAppId;

   //psystem->startup_command(psystem->m_pmaindata);

   //psystem->request(psystem->m_pcommand);

   g_application_hold(application);

}


void bloat_pad_open(GApplication * application, GFile ** files, gint n_files, const gchar * hint)
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


void bloat_pad_finalize (GObject *elemental)
{

   G_OBJECT_CLASS (bloat_pad_parent_class)->finalize (elemental);

}


void bloat_pad_shutdown(GApplication *application)
{

   BloatPad * bloatpad = (BloatPad *) application;

   /*

   if (bloatpad->timeout)
   {

      g_source_remove (bloatpad->timeout);

      bloatpad->timeout = 0;

   }

   */

   G_APPLICATION_CLASS (bloat_pad_parent_class)->shutdown (application);

}


void bloat_pad_class_init (BloatPadClass * pclass)
{

   GApplicationClass *application_class    = G_APPLICATION_CLASS (pclass);

   GObjectClass *object_class              = G_OBJECT_CLASS (pclass);

   application_class->startup              = bloat_pad_startup;
   application_class->shutdown             = bloat_pad_shutdown;
   application_class->activate             = bloat_pad_activate;
   application_class->open                 = bloat_pad_open;

   application_class->run_mainloop         = bloat_pad_run_mainloop;

   object_class->finalize                  = bloat_pad_finalize;

}


void bloat_pad_run(const char * pszAppName, const char * pszProgName)
{

   g_pappBloatPad = bloat_pad_new(pszAppName, pszProgName);

   if(g_pappBloatPad == nullptr)
   {

      output_debug_string("Failed to initialize GtkApplication (gtk_application_new return nullptr)");

      return;

   }

   int status = g_application_run (G_APPLICATION (g_pappBloatPad), 0, nullptr);

   g_object_unref(g_pappBloatPad);

   g_pappBloatPad = nullptr;

}




