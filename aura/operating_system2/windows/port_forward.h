#pragma once



#include <Natupnp.h>
#include <UPnP.h>


namespace windows
{


   class port_forward :
      virtual public ::net::port_forward
   {
   public:
	
	   // forward declarations
	
	   interface IDerivedNATExternalIPAddressCallback;
	   interface IDerivedNATNumberOfEntriesCallback;
	
	
	   // protected interfaces, which were forward-declared above, and which are used for event notifications from COM
	   // most of the code is here in this .h file, except for the QueryInterface method which is in the .cpp file

	   interface IDerivedNATExternalIPAddressCallback : public INATExternalIPAddressCallback
	   {
		   IDerivedNATExternalIPAddressCallback( ::net::port_forward_change_callbacks * point_i32 ) : m_pointer( point_i32 ), m_dwRef( 0 ) { };
		
		   HRESULT STDMETHODCALLTYPE NewExternalIPAddress( BSTR bstrNewExternalIPAddress )
		   {
			   ASSERT( m_pointer != nullptr );			
            string strNewExternalIPAddress(bstrNewExternalIPAddress);
			   return m_pointer.OnNewExternalIPAddress(strNewExternalIPAddress );
		   }
		
		   HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);
		
		   ULONG STDMETHODCALLTYPE AddRef()  {	return ++m_dwRef; }
		
		   ULONG STDMETHODCALLTYPE Release()  
		   {
			   if ( --m_dwRef == 0 )
				   delete this;
			
			   return m_dwRef;
		   }
		
		   ::u32		m_dwRef;
		   ::net::port_forward_change_callbacks*	m_pointer;
	   };
	
	   interface IDerivedNATNumberOfEntriesCallback : public INATNumberOfEntriesCallback
	   {
		   IDerivedNATNumberOfEntriesCallback( ::net::port_forward_change_callbacks* point_i32 ) : m_pointer( point_i32 ), m_dwRef( 0 ) { };
		
		   HRESULT STDMETHODCALLTYPE NewNumberOfEntries( long lNewNumberOfEntries )
		   {
			   ASSERT( m_pointer != nullptr );			
			   return m_pointer.OnNewNumberOfEntries( lNewNumberOfEntries );
		   }
		
		   HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject); 
		
		   ULONG STDMETHODCALLTYPE AddRef()  { return ++m_dwRef; }
		
		   ULONG STDMETHODCALLTYPE Release()
		   {
			   if ( --m_dwRef == 0 )
				   delete this;
			
			   return m_dwRef;
		   }
		
		   ::u32		m_dwRef;
		   ::net::port_forward_change_callbacks*	m_pointer;
	   };
	
	   // public functions -- there are only a few
	
	   port_forward(::particle * pparticle);
	   virtual ~port_forward();
	
	   virtual HRESULT ListenForUpnpChanges(::net::port_forward_change_callbacks *pCallbacks = nullptr);  // nullptr==default object; if you provide your own pointer to a port_forward_change_callbacks-derived object it is deleted for you automatically
	   virtual HRESULT StopListeningForUpnpChanges( );  // Stops listenting for UPnP change events on the router and deletes any port_forward_change_callbacks-derived objects
	
	   virtual bool GetDeviceInformationUsingThread( oswindow oswindow );  // starts a thread that will get IGD (router) device information; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
	   virtual bool GetMappingsUsingThread( oswindow oswindow );  // starts a thread that will get all mappings; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
	   virtual bool EditMappingUsingThread( port_map& oldMapping, port_map& newMapping, oswindow oswindow );  // starts a thread that will edit one specific mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
	   virtual bool AddMappingUsingThread( port_map& newMapping, oswindow oswindow );  // starts a thread that will add one memory_new mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
	   virtual bool DeleteMappingUsingThread( port_map& oldMapping, oswindow oswindow );  // starts a thread that will delete one specific mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFICATION message to oswindow when it's done
	
	   virtual pointer_array < port_map > get_port_map() const;  // gets a copy of currently-known port mappings
	   virtual pointer_array < device >  get_igd() const;  // gets a copy of currently-know device information
	
	   virtual bool IsAnyThreadRunning() const;  // returns true if there is any thread currently running
	
	
   protected:
	
	   // protected functions used internally by PortMappingEngine
	
	   void InitializeMembersToNull();
	   void DeinitializeCom();
	   HRESULT PopulateDeviceInfoContainer( IUPnPDevice* piDevice, device & deviceInfo, oswindow oswindow=nullptr );
	   HRESULT GetNextMapping( IEnumVARIANT* piEnumerator, port_map & mappingContainer );
	   HRESULT SetChangeEventCallbackPointer(::net::port_forward_change_callbacks *pCallbacks);
	
	   static ::u32 ThreadForPortRetrieval( LPVOID pVoid );
	   static ::u32 ThreadForDeviceInformationRetrieval( LPVOID pVoid );
	   static ::u32 ThreadToEditMapping( LPVOID pVoid );
	   static ::u32 ThreadToAddMapping( LPVOID pVoid );
	   static ::u32 ThreadToDeleteMapping( LPVOID pVoid );
	
	
	
   protected:
		
	   // protected members
	
	   IUPnPNAT*								m_piNAT;					
	   IDerivedNATExternalIPAddressCallback*	m_piExternalIPAddressCallback;
	   IDerivedNATNumberOfEntriesCallback*		m_piNumberOfEntriesCallback;
	
	   INATEventManager*						m_piEventManager;
	   ::net::port_forward_change_callbacks*			m_pChangeCallbackFunctions;
	
	   bool m_bListeningForUpnpChanges;
	
	   thread_pointer m_pPortMappingThread;
	   thread_pointer m_pDeviceInfoThread;
	   thread_pointer m_pAddMappingThread;
	   thread_pointer m_pEditMappingThread;
	   thread_pointer m_pDeleteMappingThread;
	
	   pointer_array<port_map> m_MappingContainer;
	
	   CRITICAL_SECTION m_criticalsection;
	
	
	   // some more protected members, most of which could not be declared until after full-declaration
	   // of the device_information_container and port_map nested classes
	
	   pointer_array<device> m_DeviceInfo;
	
	   // good-enough method for inter-thread transfer of information, since only
	   // one thread of each type is ever permitted at one time
	
	   port_map m_scratchpadOldMapping;
	   port_map m_scratchpadNewMapping;
	   port_map m_scratchpadAddedMapping;
	   port_map m_scratchpadDeletedMapping;
	
	   oswindow m_oswindow_ForPortMappingThread;
	   oswindow m_oswindow_ForDeviceInfoThread;
	   oswindow m_oswindow_ForAddMappingThread;
	   oswindow m_oswindow_ForEditMappingThread;
	   oswindow m_oswindow_ForDeleteMappingThread;
	
	
   };


} // namespace aura

