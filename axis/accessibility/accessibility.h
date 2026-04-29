//
// Created by camilo on 2026-04-27 19:00 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#pragma once


namespace accessibility
{

   class CLASS_DECL_AXIS accessibility :
   virtual public ::particle
   {
   public:


      accessibility();
      ~accessibility() override;


      virtual ::pointer < ::accessibility::application > process_identifier_application(::process_identifier processidentifier);


      virtual ::pointer<::operating_system::application> module_path_application(const ::scoped_string& scopestr);


      //virtual ::pointer<::operating_system::application> process_identifier_application(::process_identifier processidentifier);


      virtual ::pointer<::operating_system::application> application_predicate(const ::function<bool(::operating_system::application* papplication)>& function);


   };

} // namespace accessibility

