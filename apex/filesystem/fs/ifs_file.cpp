﻿#include "framework.h"
#include "apex/networking/sockets/_sockets.h"
#include "apex/filesystem/fs/_fs.h"
#include "ifs_file.h"
#include "acme/filesystem/file/memory_file.h"


ifs_file::ifs_file(::payload payloadFile) :
   m_payloadFile(payloadFile)
{

}


ifs_file::~ifs_file()
{

}


memsize ifs_file::read(void *pdata, memsize nCount)
{

   return m_phttpfile->read(pdata, nCount);

}


void ifs_file::write(const void * pdata, memsize nCount)
{

   m_pmemfile->write(pdata, nCount);

}


filesize ifs_file::get_size() const
{

   if((m_nOpenFlags & ::file::e_open_read) != 0)
   {

      return m_phttpfile->get_size();

   }
   else
   {

      return m_pmemfile->get_size();

   }

}


filesize ifs_file::translate(filesize offset, ::enum_seek eseek)
{

   if((m_nOpenFlags & ::file::e_open_read) != 0)
   {

      return m_phttpfile->translate(offset, eseek);

   }
   else
   {

      return m_pmemfile->translate(offset, eseek);

   }

}


void ifs_file::get_file_data()
{

   string strUrl;

   auto psystem = m_psystem;

   auto purl = psystem->url();

   strUrl = "http://file.ca2.software/ifs/get?path=" + purl->url_encode(m_strPath);

   ::file::e_open eopenAdd;

   if(m_nOpenFlags & ::file::e_open_update_unknown_length_supported)
   {

      eopenAdd |= ::file::e_open_update_unknown_length_supported;

   }

   m_phttpfile->open(strUrl, ::file::e_open_binary | ::file::e_open_read | eopenAdd);

}


void ifs_file::set_file_data()
{

   string strUrl;

   auto psystem = m_psystem;

   auto purl = psystem->url();

   if(m_payloadFile["xmledit"].cast < ::memory_file > () != nullptr)
   {

      strUrl = "http://file.ca2.software/ifs/xmledit?path=" + purl->url_encode(m_payloadFile["url"]);

      property_set setRequest;

      setRequest["get_response"] = "";  // touch/create property to get_response

      m_pcontext->m_papexcontext->http().put(strUrl, m_payloadFile["xmledit"].cast < ::memory_file >(), setRequest);

      string strResponse(setRequest["get_response"].get_string());

      property_set set;

      set.parse_network_arguments(strResponse);

      string strMd5Here;

      strMd5Here = m_pcontext->m_papexcontext->file().md5(m_payloadFile["xml"].cast < ::memory_file >());

      string strMd5There;
      
      strMd5There = set["md5"];

      if (strMd5Here == strMd5There)
      {

         return;

      }

      strUrl = "http://file.ca2.software/ifs/set?path=" + purl->url_encode(m_payloadFile["url"]);

      property_set setPut;

      m_pcontext->m_papexcontext->http().put(strUrl, m_payloadFile["xml"].cast < ::memory_file >(), setPut);

      return;

   }

   strUrl = "http://file.ca2.software/ifs/set?path=" + purl->url_encode(m_strPath);

   property_set setPut;

   m_pcontext->m_papexcontext->http().put(strUrl, m_pmemfile, setPut);

}



