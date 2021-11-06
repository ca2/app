#pragma once


namespace simpledb
{


   class CLASS_DECL_AXIS thread_localdatabase :
      virtual public ::task
   {
   public:


      __reference(storage)                   m_pstorage;

      __pointer_array(queue_item)            m_itema;


      thread_localdatabase();
      ~thread_localdatabase() override;


      virtual ::e_status     run() override;

      void queue(const ::string & pszKey, block block);


   };


} // namespace simpledb



