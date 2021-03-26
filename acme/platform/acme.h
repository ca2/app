// Created by camilo on 2021-03-21 18:11 <3ThomasBS_!!
#pragma once


namespace acme
{


   class CLASS_DECL_ACME acme :
      virtual public matter
   {
   public:


      acme();
      virtual ~acme();


      virtual ::e_status initialize_matter(::matter * pmatter) override;


      virtual void initialize_memory_counter();


      virtual void install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension);


      //virtual bool memory_counter_on();

      //virtual ::file::path memory_counter_base_path();

      virtual ::e_status datetime_to_filetime(::filetime_t* pfiletime, const ::datetime::time& time);


   };


} // namespace acme



