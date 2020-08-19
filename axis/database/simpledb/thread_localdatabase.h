#pragma once


namespace simpledb
{


   class CLASS_DECL_AURA thread_localdatabase :
      virtual public ::thread
   {
   public:


      __reference(storage)                   m_pstorage;

      pointer_array < queue_item >           m_itema;


      thread_localdatabase();
      virtual ~thread_localdatabase();


      virtual ::estatus     run() override;

      void queue(const char * pszKey, block block);

   };


} // namespace simpledb



