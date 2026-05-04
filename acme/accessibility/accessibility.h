//
// Created by camilo on 2026-04-27 19:00 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#pragma once


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


   };

} // namespace accessibility

