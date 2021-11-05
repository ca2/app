


namespace ios
{
   
   
   file_set::file_set(::object * pobject) :
   ::object(pobject),
   ::file::set(pobject),
   m_straFile(pobject)
   {
      
   }
   
   
   file_set::~file_set()
   {
      
   }
   
   
   void file_set::add_search(string_array & stra, bool_array & baRecursive)
   {
      
      m_straSearch.add(stra);
      
      m_baRecursive.add(baRecursive);
      
      refresh();
      
   }
   
   
   void file_set::add_filter(string_array & stra)
   {
      
      m_straFilter.add(stra);
      
      refresh();
      
   }
   
   
   ::count file_set::get_file_count()
   {
      
      return m_straFile.get_size();
      
   }
   
   
   void file_set::file_at(::index i, string & str)
   {
      
      str = m_straFile[i];
      
   }
   
   
   ::index file_set::find_first_file(const ::string & pcsz, ::index iStart)
   {
      
      return m_straFile.find_first_ci(pcsz, iStart);
      
   }
   
   
   void file_set::clear_search()
   {
      
      m_straSearch.erase_all();
      
   }
   
   
   void file_set::clear_filter()
   {
      
      m_straFilter.erase_all();
      
   }
   
   
   void file_set::clear_file()
   {
      
      m_straFile.erase_all();
      
   }
   
   
   void file_set::refresh()
   {
      
      clear_file();
      
      string strFilter;
      
      i32 i, j;
      
      string strFile;
      
      string str;
      
      for(i = 0; i < m_straSearch.get_size(); i++)
      {
         
         bool bRecursive = true;
         
         if(i < m_baRecursive.get_size())
         {
            
            bRecursive = m_baRecursive[i];
            
         }
         
         for(j = 0; j < m_straFilter.get_size(); j++)
         {
            
            string strFilter = m_straFilter.element_at(j);
            
            strFilter.trim("\\/");
            
            if(bRecursive)
            {
               
               m_straFile.rls_pattern(m_straSearch.element_at(i), strFilter);
               
            }
            else
            {
               
               m_straFile.ls_pattern(m_straSearch.element_at(i), strFilter);
               
            }
            
         }
         
      }
      
   }
   
   
} // namespace ios



