//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#include "framework.h"
#include "_.h"


text_translator::text_translator()
{
   
   defer_create_mutex();

}


text_translator::~text_translator()
{


}


void text_translator::translate_text_data(text_data* ptextdata)
{

   m_pcontext->translate_text_data(ptextdata);

}


void text_translator::translate_text_data()
{

   for (auto ptextdata : m_textdataaddressa)
   {

      ptextdata->m_bPendingUpdate = true;

   }

}


text_data* text_translator::create_text_data(const ::id& id)
{

   text_data* ptextdata = new text_data(this);

   ptextdata->m_id = id;

   return ptextdata;

}

text_data* text_translator::clone_text_data(const text_data * ptextdataParam)
{

   text_data* ptextdata = new text_data(this);

   ptextdata->m_id = ptextdataParam->m_id;

   ptextdata->m_str = ptextdataParam->m_str;

   return ptextdata;

}

void text_translator::destroy_text_data(text_data* ptextdata)
{

   delete ptextdata;

}
