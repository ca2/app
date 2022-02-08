//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#include "framework.h"
#include "_.h"


namespace text
{

   translator::translator()
   {

      defer_create_mutex();

   }


   translator::~translator()
   {


   }


   void translator::translate_text_data(data* ptextdata)
   {

      m_pcontext->translate_text_data(ptextdata);

   }


   void translator::translate_text_data()
   {

      for (auto ptextdata : m_dataaddressa)
      {

         ptextdata->m_bPendingUpdate = true;

      }

   }


   data* translator::create_text_data(const ::atom& atom)
   {

      data* ptextdata = new data(this);

      ptextdata->m_atom = atom;

      return ptextdata;

   }


   data* translator::clone_text_data(const data* ptextdataParam)
   {

      data* ptextdata = new data(this);

      ptextdata->m_atom = ptextdataParam->m_atom;

      ptextdata->m_str = ptextdataParam->m_str;

      return ptextdata;

   }


   void translator::destroy_text_data(data* ptextdata)
   {

      delete ptextdata;

   }


} // namespace text



