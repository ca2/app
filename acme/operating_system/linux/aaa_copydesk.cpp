#include "framework.h"
#include "_.h"
#include "acme/operating_system/linux/_linux.h"
#include "acme/operating_system/linux/gnome_gnome.h"
#include "acme/node/linux/_linux.h"


#include <gtk/gtk.h>


//extern GMainContext * gtk_main_context;


enum e_clipboard
{

   clipboard_none,
   clipboard_error,
   clipboard_get_plain_text,
   clipboard_set_patha,
   clipboard_get_patha,
   clipboard_get_file_target_count,
   clipboard_get_image,

};


struct clipboard_data :
   virtual public ::matter
{
public:


   clipboard_data(::particle * pparticle, e_clipboard eclipboard) :
      matter(pparticle)
   {

      m_eclipboard = eclipboard;

      m_happening.reset_happening();

   }

   ::user::copydesk::e_op     m_eop;
   e_clipboard                m_eclipboard;
   manual_reset_happening         m_happening;
   string                     m_str;
   ::image::image_pointer            m_pimage;
   ::file::path_array              m_patha;
   int                        m_nTargets;
   GtkImage *                 m_pgtkimage;

};




void clipboard_targets_func(GtkClipboard *clipboard, GdkAtom *atoms, gint n_atoms, gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   GdkAtom target = gdk_atom_intern("x-special/gnome-copied-files", false);

   pdata->m_nTargets = 0;

   for(int i = 0; i < n_atoms; i++)
   {

      if(atoms[i] == target)
      {

         pdata->m_nTargets = 1;

         break;

      }

   }

   pdata->m_happening.set_happening();

}

void clipboard_image_received_func(GtkClipboard * clipboard, GdkPixbuf * pixbuf,	gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   int iBitsPerSample = gdk_pixbuf_get_bits_per_sample(pixbuf);

   int iChannels = gdk_pixbuf_get_n_channels (pixbuf);

   GdkColorspace space = gdk_pixbuf_get_colorspace (pixbuf);

   bool bHasAlpha = gdk_pixbuf_get_has_alpha (pixbuf);

   if(iBitsPerSample == 8
         && (iChannels == 4 || iChannels == 3)
         && (space == GDK_COLORSPACE_RGB)
         && (bHasAlpha || !bHasAlpha))
   {

      int w = gdk_pixbuf_get_width(pixbuf);

      int h = gdk_pixbuf_get_height(pixbuf);

      color32_t * pimage32Src = (color32_t *) gdk_pixbuf_read_pixels(pixbuf);

      int iSrcScan = gdk_pixbuf_get_rowstride(pixbuf);

      pdata->m_pimage->create({w, h});

      if(pdata->m_pimage)
      {

         pdata->m_pimage->map();

         ::copy_image32_swap_red_blue(
         pdata->m_pimage->image32(),
         pdata->m_pimage->width(),
         pdata->m_pimage->height(),
         pdata->m_pimage->scan_size(),
         pimage32Src,
         iSrcScan);

         if(!bHasAlpha)
         {

            pdata->m_pimage->fill_channel(255, ::color::e_channel_opacity);

         }

      }

   }

   pdata->m_happening.set_happening();

}



void clipboard_received_func(GtkClipboard * clipboard, GtkSelectionData * selection_data, gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   string str = (const char *)gtk_selection_data_get_data(selection_data);

   string_array stra;

   stra.add_lines(str);

   if(stra.is_empty())
   {

      pdata->m_eclipboard = clipboard_error;

      pdata->m_happening.set_happening();

      return;

   }

   string strOp = stra[0];

   if(strOp.case_insensitive_order("copy") == 0)
   {

      pdata->m_eop = ::user::copydesk::op_copy;

   }
   else if(strOp.case_insensitive_order("cut") == 0)
   {

      pdata->m_eop = ::user::copydesk::op_cut;

   }
   else
   {

      pdata->m_eclipboard = clipboard_error;

      pdata->m_happening.set_happening();

      return;

   }

   for(::collection::index i = 1; i < stra.get_size(); i++)
   {

      string strItem = stra[i];

      strItem.case_insensitive_begins_eat("file://");

      pdata->m_patha.add(::file::path(strItem));

   }

   pdata->m_happening.set_happening();

}


void clipboard_get_func(GtkClipboard * clipboard, GtkSelectionData * selection_data, gunsigned int info, gpointer user_data)
{

   clipboard_data * pdata = (clipboard_data *) user_data;

   //::payload temp = _action + "\n" + _source; _action "cut"/"copy"

   string strAction;

   if(pdata->m_eop == ::user::copydesk::op_copy)
   {

      strAction = "copy";

   }
   else if(pdata->m_eop == ::user::copydesk::op_cut)
   {

      strAction = "cut";

   }
   else
   {

      pdata->m_eclipboard = clipboard_error;

      return;

   }

   string str;

   if(info == 1)
   {

      str = "# ";

   }

   str += strAction;

   for(auto & path : pdata->m_patha)
   {

      str += "\n";

      str += "file://" + path;

   }

   GdkAtom target = gtk_selection_data_get_target(selection_data);

   gtk_selection_data_set(selection_data, target, 8, (const guchar *) (const char *) str);


}


void clipboard_clear_func(GtkClipboard * clipboard, gpointer user_data)
{

   clipboard_data * pdata = (clipboard_data *) user_data;

   ::release(pdata);

}

void clipboard_text_request_callback(GtkClipboard *clipboard, const gchar * text, gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   if(text != nullptr)
   {

      pdata->m_str = text;

   }

   pdata->m_happening.set_happening();

}


gboolean clipboard_callback(gpointer data)
{

   clipboard_data * pdata = (clipboard_data *) data;

   GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

   if(pdata->m_eclipboard == clipboard_get_plain_text)
   {


      gtk_clipboard_request_text(clipboard, &clipboard_text_request_callback, pdata);

   }
   else if(pdata->m_eclipboard == clipboard_set_patha)
   {

      //_source = _fileCopy.Uri;
      //     _action = _radioMove.Active ? "cut" : "copy";

      GtkTargetEntry entrya[2];

      entrya[0].target = (char *) "x-special/gnome-copied-files";
      entrya[0].flags = 0;
      entrya[0].info = 0;

      entrya[1].target = (char *) "text/uri-list";
      entrya[1].flags = 0;
      entrya[1].info = 1;

      gtk_clipboard_set_with_data(clipboard, entrya, 2, &clipboard_get_func, &clipboard_clear_func, pdata);

      pdata->m_happening.set_happening();

   }
   else if(pdata->m_eclipboard == clipboard_get_patha)
   {

      GdkAtom target = gdk_atom_intern("x-special/gnome-copied-files", false);

      gtk_clipboard_request_contents(clipboard, target, &clipboard_received_func, pdata);

   }
   else if(pdata->m_eclipboard == clipboard_get_file_target_count)
   {

      gtk_clipboard_request_targets(clipboard, &clipboard_targets_func, pdata);

   }
   else if(pdata->m_eclipboard == clipboard_get_image)
   {

      if(gtk_clipboard_wait_is_image_available(clipboard))
      {

         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);

         return false;

      }

      clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY);

      if(gtk_clipboard_wait_is_image_available(clipboard))
      {

         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);

         return false;

      }

      clipboard = gtk_clipboard_get(GDK_SELECTION_SECONDARY);

      if(gtk_clipboard_wait_is_image_available(clipboard))
      {

         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);

         return false;

      }

      pdata->m_happening.set_happening();

//      GdkPixbuf * pixbuf = gtk_clipboard_wait_for_image(clipboard);
//
//      if(pixbuf == nullptr)
//      {
//
//         clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY);
//
//         pixbuf = gtk_clipboard_wait_for_image(clipboard);
//
//      }
//
//      if(pixbuf != nullptr)
//      {
//
//         clipboard_data * pdata = (clipboard_data *) data;
//
//         int iBitsPerSample = gdk_pixbuf_get_bits_per_sample(pixbuf);
//
//         int iChannels = gdk_pixbuf_get_n_channels (pixbuf);
//
//         GdkColorspace space = gdk_pixbuf_get_colorspace (pixbuf);
//
//         bool bHasAlpha = gdk_pixbuf_get_has_alpha (pixbuf);
//
//         if(iBitsPerSample == 8
//            && (iChannels == 4 || iChannels == 3)
//            && (space == GDK_COLORSPACE_RGB)
//            && (bHasAlpha || !bHasAlpha))
//         {
//
//            int w = gdk_pixbuf_get_width(pixbuf);
//
//            int h = gdk_pixbuf_get_height(pixbuf);
//
//            color32_t * pimage32Src = (color32_t *) gdk_pixbuf_read_pixels(pixbuf);
//
//            int iSrcScan = gdk_pixbuf_get_rowstride(pixbuf);
//
//            if(pdata->m_pimage = create_image({w,  h)})
//            {
//
//               ::copy_image32(
//                  pdata->m_pimage->width(),
//                  pdata->m_pimage->height(),
//                  pdata->m_pimage->m_pcolorref,
//                  pdata->m_pimage->m_iScan,
//                  pimage32Src,
//                  iSrcScan);
//
//               if(!bHasAlpha)
//               {
//
//                  pdata->m_pimage->fill_channel(255, ::color::e_channel_opacity);
//
//               }
//
//            }
//
//         }
//
//      }
//
//      pdata->m_happening.set_happening();


   }
   else
   {

      throw ::exception(error_bad_argument);

   }

   return false;

}




namespace linux
{


   copydesk::copydesk()
   {


   }


   copydesk::~copydesk()
   {

   }


   void copydesk::initialize(::particle * pparticle)
   {

      auto estatus = ::user::copydesk::initialize(pparticle);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void copydesk::destroy()
   {

      ::user::copydesk::destroy();

   }


   //bool copydesk::set_plain_text(const ::scoped_string & scopedstrParam)
   //{

   //   string str(strParam);

   //      string strText(str);

   //      ::user::copydesk::set_plain_text(strText);

   //   });

   //   return true;

   //}


   bool copydesk::_set_plain_text(const ::scoped_string & scopedstr)
   {

      gdk_fork([this, str]
      {

         GtkClipboard * clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

         gtk_clipboard_set_text(clipboard, str.c_str(), str.length());

      });

      return true;

   }


   bool copydesk::_get_plain_text(string & str)
   {

      ::pointer<clipboard_data>pdata = __allocate clipboard_data(get_app(), clipboard_get_plain_text);

      pdata->increment_reference_count(REFERENCING_DEBUGGING_P_NOTE(this, "copydesk::_get_plain_text"));

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);

      g_source_attach(idle_source, g_main_context_default());

      if(!pdata->m_happening.wait(seconds(5)).succeeded())
      {

         return false;

      }

      g_source_destroy(idle_source);

      str = pdata->m_str;

      return true;

   }


   bool copydesk::_has_plain_text()
   {

      ::pointer<ovar>::payload(__allocate ovar());

      ::payload->m_var = false;

      gdk_sync(seconds(5), [=]()
      {

         GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

         ::payload->m_var = gtk_clipboard_wait_is_text_available (clipboard);

      });

      return ::payload->m_var.operator bool();

   }


   bool copydesk::_has_filea()
   {

      ::pointer<clipboard_data>pdata = __allocate clipboard_data(get_app(), clipboard_get_file_target_count);

      pdata->increment_reference_count(REFERENCING_DEBUGGING_P_NOTE(this, "copydesk::_has_filea"));

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);

      g_source_attach(idle_source, g_main_context_default());

      if(!pdata->m_happening.wait(seconds(5)).succeeded())
      {

         return false;

      }

      return pdata->m_nTargets > 0;

   }


   bool copydesk::_get_filea(::file::path_array & patha, e_op & eop)
   {

      ::pointer<clipboard_data>pdata = __allocate clipboard_data(get_app(), clipboard_get_patha);

      pdata->increment_reference_count(REFERENCING_DEBUGGING_P_NOTE(this, "copydesk::_get_filea"));

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);

      g_source_attach(idle_source, g_main_context_default());

      if(!pdata->m_happening.wait(seconds(5)).succeeded() || pdata->m_eclipboard == clipboard_error)
      {

         return false;

      }

      eop = pdata->m_eop;

      patha = pdata->m_patha;

      return true;

   }


   bool copydesk::_set_filea(const ::file::path_array & patha, e_op eop)
   {

      ::pointer<clipboard_data>pdata = __allocate clipboard_data(get_app(), clipboard_set_patha);

      pdata->increment_reference_count(REFERENCING_DEBUGGING_P_NOTE(this, "copydesk::_set_filea"));

      pdata->m_eop = eop;

      pdata->m_patha = patha;

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);

      g_source_attach(idle_source, g_main_context_default());

      if(!pdata->m_happening.wait(seconds(5)).succeeded())
      {

         return false;

      }

      g_source_destroy(idle_source);

      return true;

   }


   bool copydesk::_desk_to_image(::image::image *pimage)
   {

      ::pointer<clipboard_data>pdata = __allocate clipboard_data(get_app(), clipboard_get_image);

      pdata->increment_reference_count(REFERENCING_DEBUGGING_P_NOTE(this, "copydesk::_desk_to_image"));

      pdata->m_pimage = __create_image();

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &clipboard_callback, pdata, nullptr);

      g_source_attach(idle_source, g_main_context_default());

      if(!pdata->m_happening.wait(seconds(5)).succeeded() || pdata->m_eclipboard == clipboard_error)
      {

         return false;

      }

      pimage->from(pdata->m_pimage);

      return true;

   }


   bool copydesk::_image_to_desk(const ::image::image *pimage)
   {


      throw ::exception(todo);

      return false;


   }


   bool copydesk::_has_image()
   {

      bool b = false;

      main_sync([&]()
      {

         GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

         b = gtk_clipboard_wait_is_image_available (clipboard);


      });

      return b;

   }


} // namespace linux




