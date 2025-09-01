//
// Created by camilo on 2025-08-31 23:54 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/filesystem/file/byte2_stream.h"




namespace message
{

   struct set_editor_selection {

      int m_iSelectionStart;
      int m_iSelectionEnd;


   };


   struct editor_text_updated {

      ::string m_strEditorText;

   };


   struct text {

      ::string m_strText;

   };


   struct open_url {

      ::string m_strUrl;

   };


}// namespace message


void stream_exchange(byte2_stream & stream, ::message::set_editor_selection & selection)
{

   stream.exchange(selection.m_iSelectionStart);
   stream.exchange(selection.m_iSelectionEnd);

}



void stream_exchange(byte2_stream & stream, ::message::editor_text_updated & updated)
{

   stream.exchange(updated.m_strEditorText);

}



void stream_exchange(byte2_stream & stream, ::message::text & text)
{

   stream.exchange(textmessage.m_strText);

}




void stream_exchange(byte2_stream & stream, ::message::open_url & openurl)
{

   stream.exchange(openurl.m_strUrl);

}

