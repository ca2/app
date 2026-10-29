//
// Created by camilo on 2026-04-27 19:00 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#pragma once
#include "selection.h"
#include "window_geometry.h"


namespace accessibility
{

   class CLASS_DECL_ACME accessibility :
   virtual public ::particle
   {
   public:


      accessibility();
      ~accessibility() override;


      virtual ::pointer < ::accessibility::application > process_identifier_application(::process_identifier processidentifier);


      virtual ::pointer<::accessibility::application> module_path_application(const ::scoped_string &scopestr);


      //virtual ::pointer<::operating_system::application> process_identifier_application(::process_identifier processidentifier);


      virtual ::pointer<::accessibility::application>
      application_predicate(const ::function<bool(::accessibility::application *papplication)> &function);


      virtual ::pointer_array < main_window > system_get_main_windows();

      // Nonblocking cache lookup. False means unavailable, not found, or ambiguous.
      // Empty window ID selects by PID and optional exact title; use the returned ID thereafter.
      // With no title, the process must have exactly one normal window.
      // Failure leaves geometry unchanged. No Qt or compositor types cross this API.
      virtual bool get_window_geometry(::process_identifier processidentifier,
         const ::scoped_string & title, window_geometry & geometry,
         const ::scoped_string & windowId = {});

      virtual automation::element_pointer automation_desktop();

      // Synchronous automation: invoke from a worker, outside the GUI thread.
      virtual ::pointer<automation::menu_selection_result> select_application_menu(
         const automation::menu_selection_request &request);

   };

} // namespace accessibility

