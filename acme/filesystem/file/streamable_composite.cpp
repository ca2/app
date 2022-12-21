// Created by camilo on 2021-09-09 22:59 Thomas Month!! <3ThomasBS__!!
#include "framework.h"
#include "streamable_composite.h"


namespace file
{


   streamable_composite::streamable_composite() 
   {
      
   }


   streamable_composite::streamable_composite(streamable * pstreamble)
   {
      
      m_pstreamable = pstreamble; 
      
   }
   
   
   streamable_composite::~streamable_composite()
   {
      
   }


   enum_status streamable_composite::_open(const ::scoped_string & scopedstrFilePath, const ::file::enum_open & eopen) 
   { 
      
      return m_pstreamable->_open(scopedstrFilePath, eopen);
   
   }


   filesize streamable_composite::translate(filesize offset, ::enum_seek eseek)
   { 
      
      return m_pstreamable->translate(offset, eseek); 
   
   }

   
   memsize streamable_composite::read(void * pdata, memsize nCount) 
   { 
      
      return m_pstreamable->read(pdata, nCount); 
   
   }

   
   void streamable_composite::write(const void * pdata, memsize nCount) 
   { 
      
      return m_pstreamable->write(pdata, nCount); 
   
   }

   
   void streamable_composite::close() 
   { 
      
      return m_pstreamable->close(); 
   
   }


   void streamable_composite::flush() 
   { 
      
      return m_pstreamable->flush(); 
   
   }

   
   void streamable_composite::set_size(filesize dwNewLen) 
   {
      
      return m_pstreamable->set_size(dwNewLen);
   
   }
      
   
   filesize streamable_composite::size() const 
   { 
      
      return m_pstreamable->size();
   
   }


} // namespace file



