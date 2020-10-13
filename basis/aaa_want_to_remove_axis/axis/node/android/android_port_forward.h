#pragma once



//#include <Natupnp.h>
//#include <UPnP.h>


namespace android
{


   class port_forward :
      virtual public ::net::port_forward
   {
   public:


      port_forward(::layered * pobjectContext);
      virtual ~port_forward();


      // forward declarations

      /* xxx	   interface IDerivedNATExternalIPAddresscallback;
      	   interface IDerivedNATNumberOfEntriescallback;


      	   // protected interfaces, which were forward-declared above, and which are used for event notifications from COM
      	   // most of the code is here in this .h file, except for the QueryInterface method which is in the .cpp file

      	   interface IDerivedNATExternalIPAddresscallback : public INATExternalIPAddresscallback
      	   {
      		   IDerivedNATExternalIPAddresscallback( ::ca2::port_forward_change_callbacks* p ) : m_pointer( p ), m_dwRef( 0 ) { };

      		   HRESULT STDMETHODcaLLTYPE NewExternalIPAddress( BSTR bstrNewExternalIPAddress )
      		   {
      			   ASSERT( m_pointer != nullptr );
                  string strNewExternalIPAddress(bstrNewExternalIPAddress);
      			   return m_pointer.OnNewExternalIPAddress(strNewExternalIPAddress );
      		   }

      		   HRESULT STDMETHODcaLLTYPE QueryInterface(REFIID iid, void ** ppvObject);

      		   ULONG STDMETHODcaLLTYPE AddRef()  {	return ++m_dwRef; }

      		   ULONG STDMETHODcaLLTYPE Release()
      		   {
      			   if ( --m_dwRef == 0 )
      				   delete this;

      			   return m_dwRef;
      		   }

      		   DWORD		m_dwRef;
      		   ::ca2::port_forward_change_callbacks*	m_pointer;
      	   };

      	   interface IDerivedNATNumberOfEntriescallback : public INATNumberOfEntriescallback
      	   {
      		   IDerivedNATNumberOfEntriescallback( ::ca2::port_forward_change_callbacks* p ) : m_pointer( p ), m_dwRef( 0 ) { };

      		   HRESULT STDMETHODcaLLTYPE NewNumberOfEntries( long lNewNumberOfEntries )
      		   {
      			   ASSERT( m_pointer != nullptr );
      			   return m_pointer.OnNewNumberOfEntries( lNewNumberOfEntries );
      		   }

      		   HRESULT STDMETHODcaLLTYPE QueryInterface(REFIID iid, void ** ppvObject);

      		   ULONG STDMETHODcaLLTYPE AddRef()  { return ++m_dwRef; }

      		   ULONG STDMETHODcaLLTYPE Release()
      		   {
      			   if ( --m_dwRef == 0 )
      				   delete this;

      			   return m_dwRef;
      		   }

      		   DWORD		m_dwRef;
      		   ::ca2::port_forward_change_callbacks*	m_pointer;
      	   };

      	   // public functions -- there are only a few


      	   virtual HRESULT ListenForUpnpChanges(::ca2::port_forward_change_callbacks *pcallbacks = nullptr);  // nullptr==default object; if you provide your own pointer to a port_forward_change_callbacks-derived object it is deleted for you automatically
      	   virtual HRESULT StopListeningForUpnpChanges( );  // Stops listenting for UPnP change events on the router and deletes any port_forward_change_callbacks-derived objects

      	   virtual int_bool GetDeviceInformationUsingThread( oswindow hWnd );  // starts a thread that will get IGD (router) device information; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFIcaTION message to hWnd when it's done
      	   virtual int_bool GetMappingsUsingThread( oswindow hWnd );  // starts a thread that will get all mappings; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFIcaTION message to hWnd when it's done
      	   virtual int_bool EditMappingUsingThread( port_map& oldMapping, port_map& newMapping, oswindow hWnd );  // starts a thread that will edit one specific mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFIcaTION message to hWnd when it's done
      	   virtual int_bool AddMappingUsingThread( port_map& newMapping, oswindow hWnd );  // starts a thread that will add one new mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFIcaTION message to hWnd when it's done
      	   virtual int_bool DeleteMappingUsingThread( port_map& oldMapping, oswindow hWnd );  // starts a thread that will delete one specific mapping; the thread posts a UWM_PORT_FORWARD_ENGINE_THREAD_NOTIFIcaTION message to hWnd when it's done

      	   virtual array_ptr_alloc < port_map > get_port_map() const;  // gets a copy of currently-known port mappings
      	   virtual array_ptr_alloc < device >  get_igd() const;  // gets a copy of currently-know device information

      	   virtual int_bool IsAnyThreadRunning() const;  // returns TRUE if there is any thread currently running


         protected:

      	   // protected functions used internally by PortMappingEngine

      	   void InitializeMembersToNull();
      	   void DeinitializeCom();
      	   HRESULT PopulateDeviceInfoContainer( IUPnPDevice* piDevice, device & deviceInfo, oswindow hWnd=nullptr );
      	   HRESULT GetNextMapping( IEnumVARIANT* piEnumerator, port_map & mappingContainer );
      	   HRESULT SetChangeEventcallbackPointer(::ca2::port_forward_change_callbacks *pcallbacks);

      	   static UINT ThreadForPortRetrieval( LPVOID pVoid );
      	   static UINT ThreadForDeviceInformationRetrieval( LPVOID pVoid );
      	   static UINT ThreadToEditMapping( LPVOID pVoid );
      	   static UINT ThreadToAddMapping( LPVOID pVoid );
      	   static UINT ThreadToDeleteMapping( LPVOID pVoid );



         protected:

      	   // protected members

      	   IUPnPNAT*								m_piNAT;
      	   IDerivedNATExternalIPAddresscallback*	m_piExternalIPAddresscallback;
      	   IDerivedNATNumberOfEntriescallback*		m_piNumberOfEntriescallback;

      	   INATEventManager*						m_piEventManager;
      	   ::ca2::port_forward_change_callbacks*			m_pChangecallbackFunctions;

      	   int_bool m_bListeningForUpnpChanges;

      	   ::ca2::thread_pointer m_pPortMappingThread;
      	   ::ca2::thread_pointer m_pDeviceInfoThread;
      	   ::ca2::thread_pointer m_pAddMappingThread;
      	   ::ca2::thread_pointer m_pEditMappingThread;
      	   ::ca2::thread_pointer m_pDeleteMappingThread;

      	   array_ptr_alloc<port_map> m_MappingContainer;

      	   CRITICAL_SECTION m_cs;


      	   // some more protected members, most of which could not be declared until after full-declaration
      	   // of the device_information_container and port_map nested classes

      	   array_ptr_alloc<device> m_DeviceInfo;

      	   // good-enough method for inter-thread transfer of information, since only
      	   // one thread of each type is ever permitted at one time

      	   port_map m_scratchpadOldMapping;
      	   port_map m_scratchpadNewMapping;
      	   port_map m_scratchpadAddedMapping;
      	   port_map m_scratchpadDeletedMapping;

      	   oswindow m_hWndForPortMappingThread;
      	   oswindow m_hWndForDeviceInfoThread;
      	   oswindow m_hWndForAddMappingThread;
      	   oswindow m_hWndForEditMappingThread;
      	   oswindow m_hWndForDeleteMappingThread;*/


   };


} // namespace android

