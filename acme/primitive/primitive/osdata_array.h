#pragma once


class CLASS_DECL_ACME osdata_array
{
public:


   tiny_array < void* >   m_osdata;


   void set_os_data(::i32 i, void* p)
   {

      m_osdata.set_at_grow(i, p);

   }


   inline void* get_os_data(::i32 i = 0) const
   {
      
      if(i >= m_osdata.m_iCount)
      {
         
         if(i >= 8)
         {
            
            return nullptr;
            
         }
       
         ((osdata_array*)this)->m_osdata.element_at_grow(i) = 0;
         
      }

      return m_osdata.m_p[i];

   }


   inline void set_os_data(void* p)
   {

      set_os_data(0, p);

   }

   inline void clear_os_data() { m_osdata.zero(); }


};



