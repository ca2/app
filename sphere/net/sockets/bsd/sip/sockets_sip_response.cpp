#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "aura/net/net_sockets.h"


namespace sip
{


   response::response(::object * pobject, const string & version) :
   ::object(pobject),
   transaction(pobject),
   m_memfileBody(papp )
   {

      __UNREFERENCED_PARAMETER(version);

   }


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

      ::sip::transaction::operator=(src);

      return *this;
   }

   // --------------------------------------------------------------------------------------
   /*void response::SetFile( const string & path )
   {
      m_file = ::pointer<IFile>e>(memory_new File);
      m_file -> fopen( path, "rb" );
   }*/

   // --------------------------------------------------------------------------------------
   void response::clear()
   {
      transaction::clear();
      file().Truncate(0);
   //   m_file = ::pointer<IFile>e>(memory_new MemFile);
   }

} // namespace sip


