#pragma once


////#include "acme/primitive/primitive/matter.h"


namespace operating_system
{


   class CLASS_DECL_ACME pipe :
      virtual public ::matter
   {
   public:


      char *               m_pchBuf;
      string               m_strRead;

      bool                 m_bInherit;
      bool                 m_bBlock;


      pipe();
      virtual ~pipe();


      virtual bool create(bool bBlock = true, bool bInherit = false);


      virtual bool not_inherit_read();
      virtual bool not_inherit_write();

      virtual bool write(const scoped_string & str);
      virtual string read();
      virtual string one_pass_read();


#ifdef WINDOWS

      void readex();

#endif



   };


} // namespace operating_system



