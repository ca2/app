//
// Created by camilo on 2025-08-31 23:54 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/filesystem/file/byte2_stream.h"

#include "acme/user/user/message_box.h"


namespace message
{

   struct set_editor_selection {

      ::i32 m_iSelectionStart;
      ::i32 m_iSelectionEnd;

      void byte2_exchange(byte2_stream & stream)
      {

         stream.exchange(m_iSelectionStart);
         stream.exchange(m_iSelectionEnd);

      }

   };

   struct editor_text_and_selection {

      ::string m_strEditorText;
      ::i32 m_iSelectionStart;
      ::i32 m_iSelectionEnd;

      void byte2_exchange(byte2_stream & stream)
      {

         stream.exchange(m_strEditorText);
         stream.exchange(m_iSelectionStart);
         stream.exchange(m_iSelectionEnd);

      }

   };

   struct editor_text_updated {

      ::string m_strEditorText;
      void byte2_exchange(byte2_stream & stream)
      {

         stream.exchange(m_strEditorText);

      }

   };


   struct text {

      ::string m_strText;
      void byte2_exchange(byte2_stream & stream)
      {

         stream.exchange(m_strText);

      }

   };


   struct open_url {

      ::string m_strUrl;
      void byte2_exchange(byte2_stream & stream)
      {

         stream.exchange(m_strUrl);

      }
   };


   struct message_box
      {
      ::i64 m_llMessageBoxSequence;
      ::string m_strMessage;
      ::string m_strTitle;
      ::i32 m_iButton;

      message_box()
      {
         m_llMessageBoxSequence = 0;
         m_iButton = 0;

      }

      message_box(::acme::user::message_box * pmessagebox)
      {
         pmessagebox->increment_reference_count();
         m_llMessageBoxSequence = (::i64)(::iptr)(void*)pmessagebox;
         m_strMessage = pmessagebox->m_strMessage;
         m_strTitle = pmessagebox->m_strTitle;
         m_iButton = 0;

      }

      void byte2_exchange(byte2_stream & stream)
      {

         stream.exchange(m_llMessageBoxSequence);
         stream.exchange(m_strMessage);
         stream.exchange(m_strTitle);
         stream.exchange(m_iButton);

      }

   };


}// namespace message

//
//void stream_exchange(byte2_stream & stream, ::message::set_editor_selection & selection)
//{
//
//   stream.exchange(selection.m_iSelectionStart);
//   stream.exchange(selection.m_iSelectionEnd);
//
//}
//
//
//
//void stream_exchange(byte2_stream & stream, ::message::editor_text_updated & updated)
//{
//
//   stream.exchange(updated.m_strEditorText);
//
//}
//
//
//
//void stream_exchange(byte2_stream & stream, ::message::text & text)
//{
//
//   stream.exchange(text.m_strText);
//
//}
//void stream_exchange(byte2_stream & stream, ::message::open_url & openurl)
//{
//
//   stream.exchange(openurl.m_strUrl);
//
//}

