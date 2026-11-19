#include "platform.h"
#include "core/user/userex/dialog.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"
#include "berg/user/form/document.h"
#include "berg/user/form/impact.h"
#include "berg/user/simple/frame_window.h"
#include "berg/user/experience/frame.h"
#include "acme/filesystem/file/folder_importer.h"
#include "acme/filesystem/file/file.h"
#include "acme/user/interface/message_box.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/filesystem/fs/set.h"
#include "impact_base.h"
#include "document.h"
#include "tab_impact.h"
#include "data.h"
#include "operation/document.h"
#include "operation/thread.h"
#include "operation/operation.h"
#include "acme/constant/id.h"
#include "acme/filesystem/file/item.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"
#include "aura/user/user/copydesk.h"
#include "aura/message/user.h"
#include "aura/user/user/frame_interaction.h"
#include "core/platform/application.h"


namespace
{
   class paste_progress_bar : public ::user::interaction
   {
   public:
      ::f64 m_rate = 0.0;
      ::f64_size get_preferred_size(::draw2d::graphics_pointer &) override { return {420, 18}; }
      void resize_to_fit(::draw2d::graphics_pointer &) override { set_size({420, 18}); }
      void _001OnDraw(::draw2d::graphics_pointer & graphics) override
      {
         auto bounds = rectangle();
         graphics->fill_rectangle(bounds, argb(255, 220, 220, 220));
         bounds.right = bounds.left + bounds.width() * m_rate;
         graphics->fill_rectangle(bounds, argb(255, 40, 130, 220));
      }
   };
   class paste_progress_dialog : public ::userex::dialog
   {
   public:
      ::pointer<::user::still> m_status;
      ::pointer<::user::button> m_cancel;
      ::pointer<paste_progress_bar> m_progress;
      bool m_bCancelled = false;
      bool m_bFinished = false;
      paste_progress_dialog() { m_bResizable = false; defer_create_synchronization(); }
      ::i32_bool on_init_dialog() override
      {
         if (!::userex::dialog::on_init_dialog()) return false;
         m_pformdocument->set_title("Paste files");
         // Keep the active transfer visible; cancellation goes through the Cancel button.
         m_pframe->m_ebuttonaHide.add_unique(::experience::e_button_close);
         auto column = create_line_layout(m_pform, ::e_orientation_vertical);
         column->set_position({16, 16});
         m_status = create_label<::user::still>(column, "Preparing to paste files into the selected folder...");
         m_progress = create_newø<paste_progress_bar>();
         m_progress->create_child(column);
         m_progress->display();
         m_cancel = create_button(column, "Cancel");
         m_cancel->m_callbackOnAction = [this](::user::interaction *, ::item *, ::user::activation_token *)
         {
            ::pointer<paste_progress_dialog> keepAlive = this;
            bool finished;
            {
               _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
               finished = m_bFinished;
               if (!finished) m_bCancelled = true;
            }
            if (finished) EndModalLoop("close");
            else
            {
               m_status->set_window_text("Cancelling the transfer...");
               m_cancel->enable_window(false);
               m_status->set_need_redraw();
               m_status->post_redraw();
            }
            return true;
         };
         return true;
      }
      bool cancelled()
      {
         _synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         return m_bCancelled;
      }
      void update(const ::string & text, ::f64 rate)
      {
         ::pointer<paste_progress_dialog> dialog = this;
         m_pform->user_post([dialog, text, rate]()
         {
            if (dialog->cancelled()) return;
            dialog->m_progress->m_rate = rate;
            dialog->m_progress->set_need_redraw();
            dialog->m_progress->post_redraw();
            dialog->m_status->set_window_text(text);
            dialog->m_status->set_need_redraw();
            dialog->m_status->post_redraw();
         });
      }
      void finish(const ::string & text)
      {
         ::pointer<paste_progress_dialog> dialog = this;
         m_pform->user_post([dialog, text]()
         {
            {
               _synchronous_lock lock(dialog->synchronization());
               dialog->m_bFinished = true;
            }
            dialog->m_status->set_window_text(text);
            dialog->m_status->set_need_redraw();
            dialog->m_status->post_redraw();
            dialog->m_cancel->set_window_text("Close");
            dialog->m_cancel->enable_window(true);
         });
      }
   };
}

filemanager_impact_base::filemanager_impact_base()
{

   m_bEditConnectInit = false;
   //m_pfsdata = nullptr;
   //m_pfilemanagerdocument = nullptr;

}


filemanager_impact_base::~filemanager_impact_base()
{

}


// ::core::application* filemanager_impact_base::get_app()
// {
//
//    auto papplication = application();
//
//    return ::is_set(papplication) ? papplication : nullptr;
//
// }
//
//
// ::core::session* filemanager_impact_base::get_session()
// {
//
//    auto pacmesession = session();
//
//    return ::is_set(pacmesession) ? pacmesession : nullptr;
//
// }
//
//
// ::core::system* filemanager_impact_base::get_system()
// {
//
//    auto pacmesystem = system();
//
//    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
//
// }


::filemanager::document * filemanager_impact_base::get_document()
{

   return filemanager_document();

}


::filemanager::data * filemanager_impact_base::filemanager_data()
{

   return filemanager_document()->filemanager_data();

}


//void filemanager_impact_base::initialize_impact(::user::document * pdocument)
//{
//
//   ::user::impact::initialize_impact(pdocument);
//
//   //m_pfilemanagerdocument = pdocument;
//
//   //m_pfsdata = filemanager_data()->fs_data();
//
//}


void filemanager_impact_base::install_message_routing(::channel * pchannel)
{

   ::user::impact::install_message_routing(pchannel);

   add_command_prober("edit_paste", { this,  &filemanager_impact_base::_001OnUpdateEditPaste });

   add_command_handler("edit_paste", { this,  &filemanager_impact_base::_001OnEditPaste });

   USER_MESSAGE_LINK(WM_APP + 1024,pchannel,this,&filemanager_impact_base::_001OnOperationDocMessage);

}


::file::item * filemanager_impact_base::filemanager_item()
{

   auto pdocument = filemanager_document();

   if (!pdocument)
   {

      return nullptr;

   }

   return pdocument->filemanager_item();

}


//::pointer<::fs::data>filemanager_impact_base::fs_data()
//{
//
//   return filemanager_document()->fs_data();
//
//}


::file::path filemanager_impact_base::filemanager_path()
{

   return filemanager_item()->user_path();

}


::filemanager::document * filemanager_impact_base::filemanager_document()
{
   
   return dynamic_cast < ::filemanager::document *>(::user::impact::get_document()); 

}


//virtual ::filemanager::data *                   filemanager_data();
::fs::set * filemanager_impact_base::fs_data() 
{
   
   return filemanager_data()->fs_data(); 

}


::filemanager::filemanager * filemanager_impact_base::filemanager()
{
   return get_app()->filemanager(); 
}
//
//::filemanager::document * filemanager_impact_base::filemanager_document()
//{
//
//   return dynamic_cast <::filemanager::document * > (get_document());
//
//}


//::filemanager::data * filemanager_impact_base::get_document()
//{
//
//   return  filemanager_document()->get_document();
//
//}


void filemanager_impact_base::_001Refresh()
{

   filemanager_document()->_001Refresh();

}


void filemanager_impact_base::browse_sync(const ::action_context & context)
{

   __UNREFERENCED_PARAMETER(context);

}


void filemanager_impact_base::knowledge(const ::file::path & pathUser, const ::action_context & context)
{

   __UNREFERENCED_PARAMETER(pathUser);
   __UNREFERENCED_PARAMETER(context);

}


void filemanager_impact_base::_001OnUpdateEditPaste(::message::message * pmessage)
{

   ::pointer<::message::command>pcommand(pmessage);

   auto pcopydesk = copydesk();
   
   bool bHasFile = pcopydesk->has_filea();
         
   pcommand->enable(bHasFile);

   pmessage->m_bRet = true;

}


void filemanager_impact_base::_001OnEditPaste(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   ::file::listing_base listing;

   ::user::copydesk::enum_op eop = ::user::copydesk::e_op_copy;

   auto pcopydesk = copydesk();
   
   bool bOk = pcopydesk->get_filea(listing, eop);
   information() << "File Manager Paste: clipboard read " << bOk << ", files " << listing.size();

   if(!bOk || listing.is_empty())
   {

      auto message = create_newø<::user_interface::message_box>();
      message->initialize_message_box("The clipboard contains no files to paste. Select files and use Copy first.", "Paste files");
      message->display(e_display_normal, {});
      pmessage->m_bRet = true;

      return;

   }

   string strDir;

   strDir = filemanager_item()->user_path();

   auto provider = fs_data()->path_data(strDir);
   ::cast<::file::folder_importer> importer = provider;
   {
      pmessage->m_bRet = true;
      auto dialog = create_newø<paste_progress_dialog>();
      dialog->m_pdialogOwner = parent_frame();
      if (!dialog->show()) throw ::exception(error_failed, "Could not display paste progress");
      ::pointer<filemanager_impact_base> impact = this;
      get_document()->fork([impact, dialog, importer, listing, strDir, eop]()
      {
         ::collection::count completed = 0;
         try
         {
            for (const auto & source : listing)
            {
               if (dialog->cancelled()) throw ::exception(error_cancelled, "Paste cancelled");
               int lastPercent = -1;
               auto progress = [&](::f64 rate)
               {
                  if (dialog->cancelled()) return false;
                  int percent = (int)(rate * 100.0);
                  if (percent != lastPercent)
                  {
                     lastPercent = percent;
                     dialog->update("File " + ::as_string(completed + 1) + " of " + ::as_string(listing.size())
                        + ": " + source.name() + " (" + ::as_string(percent) + "%)",
                        (completed + rate) / (::f64)listing.size());
                  }
                  return true;
               };
               if (importer)
               {
                  importer->import_file(strDir, source, progress);
               }
               else
               {
                  auto filesystem = impact->fs_data();
                  ::file::image_info info;
                  auto name = source.name();
                  if (filesystem->get_file_image_info(source, info) && info.m_strName.has_character())
                     name = info.m_strName;
                  // Provider display names must remain a single destination filename.
                  if (name.is_empty() || name == "." || name == ".."
                     || name.contains("/") || name.contains("\\") || name.contains(":"))
                     throw ::exception(error_bad_argument, "Invalid source filename");
                  auto destination = impact->application()->defer_process_path(::file::path(strDir) / name);
                  if (destination.contains("://"))
                     throw ::exception(error_not_supported, "This destination does not support pasting files.");
                  if (impact->file()->exists(destination) || impact->directory()->is(destination))
                     throw ::exception(error_failed, "Destination already exists: " + name);
                  progress(0.0);
                  if (filesystem->is_dir(source) > 0)
                  {
                     auto localSource = impact->application()->defer_process_path(source);
                     if (localSource.contains("://"))
                        throw ::exception(error_not_supported, "Copying virtual folders is not supported; select files instead.");
                     impact->file()->copy(destination, localSource, true);
                  }
                  else
                  {
                     // Open through the owning provider so virtual URIs download correctly.
                     auto input = filesystem->get_file(source, ::file::e_open_read | ::file::e_open_binary);
                     if (!input) throw ::exception(error_failed, "Could not open source file");
                     if (dialog->cancelled()) throw ::exception(error_cancelled, "Paste cancelled");
                     impact->file()->copy(destination, input, true);
                  }
                  progress(1.0);
               }
               ++completed;
               // Never delete a cut source until the destination copy succeeds.
               if (eop == ::user::copydesk::e_op_cut) impact->file()->erase(source);
            }
            dialog->finish("Pasted " + ::as_string(completed) + " file(s).");
         }
         catch (const ::exception & exception)
         {
            dialog->finish(exception.get_message() + " (" + ::as_string(completed) + " file(s) completed)");
         }
         catch (...)
         {
            dialog->finish("Paste failed. " + ::as_string(completed) + " file(s) completed.");
         }
         impact->user_post([impact]() { impact->_001Refresh(); });
      });
      return;
   }


}


void filemanager_impact_base::_001OnOperationDocMessage(::message::message * pmessage)
{

   ::pointer<::user::message>pusermessage(pmessage);

   if(pusermessage->m_wparam == 4096)
   {

      if(pusermessage->m_lparam == 0)
      {

         _001Refresh();

      }

   }

}



void filemanager_impact_base::handle(::topic * ptopic, ::handler_context * phandlercontext)
{

   ::user::impact::handle(ptopic, phandlercontext);

   if (ptopic->id() == id_initialize)
   {

      //if (filemanager_document() == ptopic->cast < ::user::document >(id_document))
      //{

      //   //::pointer<::database::client>pclient = parent_frame();

      //   //if (pclient != nullptr && !::string(pclient->id()).contains("::frame"))
      //   //{

      //   //   string str;

      //   //   str.formatf("frame(%s)", ::string(get_document()->id()).c_str());

      //   //   pclient->set_data_key_modifier(str);

      //   //}

      //}

   }
   else if (ptopic->id() == id_synchronize_path)
   {

      ::pointer<::core::application>papp = get_app();

      auto pfileitemTopic = ptopic->_extended_topic()->m_pfileitem;

      if (pfileitemTopic)
      {

         bool bSameFilePath = false;

         if (::is_set(filemanager_item()))
         {

            ::file::path pathTopicFinal = ptopic->_extended_topic()->m_pfileitem->final_path();

            ::file::path pathItemFinal = filemanager_item()->final_path();

            bSameFilePath = papp->is_equal_file_path(pathTopicFinal, pathItemFinal);

         }

         if (bSameFilePath)
         {

#define DBG_LOOP  1
            for (::collection::index i = 0; i < DBG_LOOP; i++)
            {

               browse_sync(ptopic->m_actioncontext + ::e_source_sync);

            }

         }
         else
         {

            ::file::path pathUser;

            pathUser = pfileitemTopic->user_path();

            knowledge(pathUser, ptopic->m_actioncontext + ::e_source_sync);

         }

         set_need_redraw();

      }

   }

}




