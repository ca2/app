#include "framework.h"


namespace sip
{


   response::response(::object * pobject, const string & version) :
   ::object(pobject),
   transaction(pobject),
   m_memfileBody(papp )
   {
      __UNREFERENCED_PARAMETER(version);
   }


   // --------------------------------------------------------------------------------------
   response::response(const response& src) :
   ::object(((response &)src).get_application()),
   transaction(src)
   , m_memfileBody(((response &)src).get_application() )
   {
      m_memfileBody = src.m_memfileBody;
   }


   // --------------------------------------------------------------------------------------
   response::~response()
   {
   }


   // --------------------------------------------------------------------------------------
   response& response::operator=(const response& src)
   {
      m_memfileBody        = src.m_memfileBody;

      transaction::operator=(src);

      return *this;
   }

   // --------------------------------------------------------------------------------------
   /*void response::SetFile( const string & path )
   {
      m_file = std::auto_ptr<IFile>(new File);
      m_file -> fopen( path, "rb" );
   }*/

   // --------------------------------------------------------------------------------------
   void response::clear()
   {
      transaction::clear();
      file().Truncate(0);
   //   m_file = std::auto_ptr<IFile>(new MemFile);
   }

} // namespace sip


