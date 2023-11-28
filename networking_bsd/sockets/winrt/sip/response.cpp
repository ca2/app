#include "framework.h"


namespace sip
{


   response::response(::particle * pparticle, const string & version) :
   ::object(pparticle),
   transaction(pparticle),
   m_memfileBody(papp )
   {
      UNREFERENCED_PARAMETER(version);
   }


   // --------------------------------------------------------------------------------------
   response::response(const response& src) :
   ::object(((response &)src).get_app()),
   transaction(src)
   , m_memfileBody(((response &)src).get_app() )
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
      m_file = std::auto_ptr<IFile>(aaa_memory_new File);
      m_file -> fopen( path, "rb" );
   }*/

   // --------------------------------------------------------------------------------------
   void response::clear()
   {
      transaction::clear();
      file()->Truncate(0);
   //   m_file = std::auto_ptr<IFile>(aaa_memory_new MemFile);
   }

} // namespace sip


