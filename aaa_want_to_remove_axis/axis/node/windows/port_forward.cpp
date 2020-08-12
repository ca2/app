#include "framework.h"
#include "_windows.h"


//const UINT UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION = ::RegisterWindowMessageA("UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION-{7C29C80A_5712_40e8_A124_A82E4B2795A7}");
#define UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION (WM_APP + 123)

namespace windows
{

   // forward declaration of global function which is included at the end of this file

   void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName);


   //////////////////////////////////////////////////////////////////////
   // Construction/Destruction
   //////////////////////////////////////////////////////////////////////

   port_forward::port_forward()
   {

      InitializeMembersToNull();

      ::InitializeCriticalSection( &m_cs );

   }


   port_forward::~port_forward()
   {

      StopListeningForUpnpChanges( );

      ::DeleteCriticalSection( &m_cs );

   }


   void port_forward::InitializeMembersToNull()
   {
      m_piNAT			= nullptr;
      m_piEventManager	= nullptr;
      m_piExternalIPAddressCallback= nullptr;
      m_piNumberOfEntriesCallback	= nullptr;

      m_pChangeCallbackFunctions	= nullptr;

   /*   m_ptaskPortRetrieval = nullptr;
      m_ptaskDeviceInformationRetrieval = nullptr;
      m_ptaskAddMapping = nullptr;
      m_ptaskEditMapping = nullptr;
      m_ptaskDeleteMapping = nullptr;*/

      m_oswindowForPortMapping = nullptr;
      m_oswindowForDeviceInfo = nullptr;
      m_oswindowForAddMapping = nullptr;
      m_oswindowForEditMapping = nullptr;
      m_oswindowForDeleteMapping = nullptr;

      m_bListeningForUpnpChanges = FALSE;
   }


   void port_forward::DeinitializeCom()
   {

      if ( m_piExternalIPAddressCallback != nullptr )
      {
         m_piExternalIPAddressCallback->Release();
         m_piExternalIPAddressCallback = nullptr;
      }


      if ( m_piNumberOfEntriesCallback != nullptr )
      {
         m_piNumberOfEntriesCallback->Release();
         m_piNumberOfEntriesCallback = nullptr;
      }

      if ( m_piEventManager != nullptr )
      {
         m_piEventManager->Release();
         m_piEventManager = nullptr;
      }

      if ( m_piNAT != nullptr )
      {
         m_piNAT->Release();
         m_piNAT = nullptr;
      }

      CoUninitialize();  // balancing call for CoInitialize
   }

   HRESULT port_forward::ListenForUpnpChanges(::net::port_forward_change_callbacks *pCallbacks /* =nullptr */ )
   {
      // check if we are already listening

      if ( m_bListeningForUpnpChanges == TRUE )
         return E_FAIL;

      m_bListeningForUpnpChanges = TRUE;


      if ( pCallbacks==nullptr )
      {
         SetChangeEventCallbackPointer(	new ::net::port_forward_change_callbacks );
      }
      else
      {
         SetChangeEventCallbackPointer( pCallbacks );
      }

      // initialize COM for this thread

      HRESULT result = ::CoInitializeEx(nullptr,COINIT_MULTITHREADED);
      if ( !SUCCEEDED(result) )
      {
         return E_FAIL;
      }

      // create COM instance of IUPnPNAT

      result = CoCreateInstance(__uuidof(UPnPNAT), nullptr, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&m_piNAT);
      if ( !SUCCEEDED(result) || ( m_piNAT==nullptr ) )
      {
         CoUninitialize();
         return E_FAIL;
      }


      // Get the INATEventManager interface

      result = m_piNAT->get_NATEventManager(&m_piEventManager);
      if ( !SUCCEEDED(result) || (m_piEventManager==nullptr ) )
      {
         m_piNAT->Release();
         m_piNAT = nullptr;
         CoUninitialize();
         return E_FAIL;
      }

      result = m_piEventManager->put_ExternalIPAddressCallback(
               m_piExternalIPAddressCallback = new IDerivedNATExternalIPAddressCallback( m_pChangeCallbackFunctions ) );

      if ( !SUCCEEDED(result) )
      {
         m_piEventManager->Release();
         m_piEventManager = nullptr;
         m_piNAT->Release();
         m_piNAT = nullptr;
         CoUninitialize();
         return E_FAIL;
      }

      result = m_piEventManager->put_NumberOfEntriesCallback(
               m_piNumberOfEntriesCallback = new IDerivedNATNumberOfEntriesCallback( m_pChangeCallbackFunctions ) );

      if ( !SUCCEEDED(result) )
      {
         m_piEventManager->Release();
         m_piEventManager = nullptr;
         m_piNAT->Release();
         m_piNAT = nullptr;
         CoUninitialize();
         return E_FAIL;
      }

      return S_OK;
   }



   HRESULT port_forward::StopListeningForUpnpChanges( )
   {
      // Stops listenting for UPnP change events on the router and deletes any
      // port_forward_change_callbacks-derived objects that are currently being held

      // check if we are already listening

      if ( m_bListeningForUpnpChanges == FALSE )
         return E_FAIL;

      m_bListeningForUpnpChanges = FALSE;


      DeinitializeCom( );

      if ( m_pChangeCallbackFunctions != nullptr )
      {
         delete m_pChangeCallbackFunctions;
         m_pChangeCallbackFunctions = nullptr;
      }

      return S_OK;
   }



   HRESULT port_forward::SetChangeEventCallbackPointer(::net::port_forward_change_callbacks *pCallbacks)
   {
      ASSERT( pCallbacks!=nullptr );

      if ( m_pChangeCallbackFunctions != nullptr )
      {
         delete m_pChangeCallbackFunctions;
         m_pChangeCallbackFunctions = nullptr;
      }

      m_pChangeCallbackFunctions = pCallbacks;

      return S_OK;
   }


   bool port_forward::IsAnyThreadRunning() const
   {
      
      bool bRet = FALSE;

      bRet |= (::is_active(m_ptaskPortRetrieval));
      bRet |= (::is_active(m_ptaskDeviceInformationRetrieval));
      bRet |= (::is_active(m_ptaskAddMapping));
      bRet |= (::is_active(m_ptaskEditMapping));
      bRet |= (::is_active(m_ptaskDeleteMapping));

      return bRet;

   }


   pointer_array < port_forward::port_map > port_forward::get_port_map() const
   {
      // returns a copy of the current mappings (note: thread-awareness is needed)

      // cast away const-ness of the critical department (since this is a const function)
      port_forward* pThis = const_cast< port_forward* >( this );

      ::EnterCriticalSection(&pThis->m_cs);

      pointer_array < port_forward::port_map > retVector;
      retVector = m_MappingContainer;

      ::LeaveCriticalSection(&pThis->m_cs);

      return retVector;
   }

   pointer_array < port_forward::device > port_forward::get_igd() const
   {
      // returns a copy of the current device information (note: thread-awareness is needed)

      // cast away const-ness of the critical department (since this is a const function)
      port_forward* pThis = const_cast< port_forward* >( this );

      ::EnterCriticalSection(&pThis->m_cs);

      pointer_array < device > retDeviceInfo;
      retDeviceInfo = m_DeviceInfo;

      ::LeaveCriticalSection(&pThis->m_cs);

      return retDeviceInfo;
   }


   ///////////////////////////////////////////////
   //
   // Get Mappings and Device Information UsingThreadThread Threads
   //
   ///////////////////////////////////////////////
   //
   // These comments explain the how to receive notifications from the threads that the
   // Port Forward Engine creates when running COM requests for device information or for
   // retreival/change of port mappings.
   //
   // There are five functions that create threads, and each function takes a oswindow as a
   // parameter.  During execution of the thread, each thread will post messages to this oswindow,
   // so as to notify the HWMND of the thread's progress through the needed COM tasks.  The
   // message is always the same: a UINT named UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION.
   // Encodings of the WPARAM and LPARAM within the message will enable the oswindow to determine
   // what's going on inside the thread.  The five functions are:
   //
   //   GetMappingsUsingThreadThread()
   //   EditMappingUsingThread()
   //   AddMappingUsingThread()
   //   DeleteMappingUsingThread()
   //   GetDeviceInformationUsingThread()
   //
   // The comments below explain each how to modify your class to receive the thread's notification
   // message, and also explain how to decode the WPARAM and LPARAM values



   // define the value of the registered Window message.  An arbitrary GUID is included, to ensure uniqueness





   ///////////////////////////////////////////////
   //
   //  GetMappingsUsingThread()
   //
   //////////////////////////////////////////////
   //
   // The GetMappingsUsingThread() function populates a std::vector of port_map's with port
   // mappings that it finds using a thread.  The reason for the thread is that COM retrieval of
   // port mappings is SLOW.  Moreover, retrieval of the port mappings also BLOCKS the message
   // pump, so without a separate thread the application would otherwise appear to be hung/frozen.
   //
   // The thread frees the user interface of your program to do other things.  The price you
   // pay for this convenience is that communication to your application is via Windows messages,
   // which the thread sends to your application and which your application must interpret and process.
   //
   // To use this function, your program must be able to receive (and process)
   // a registered interaction_impl message posted from the thread when the thread is finished.
   // Thus, you must pass in a oswindow of one of your windows that will receive the message.  Typically,
   // you would choose your CMainFrame interaction_impl (use the ::__get_main_window() function).  However, you might
   // choose a different interaction_impl, such as your CView-derived interaction_impl for SDI applications
   //
   // The interaction_impl that you choose must be able to process the message, which is a UINT named
   // UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION.  For an MFC application, here are the changes
   // you must make to your ::user::interaction class:
   //
   // 1. Declare a handler in your .h file using the following signature, in which
   //    the name "OnMappingNotificationMeesage" is arbitrary (ie, you can use
   //    any name that you want, but you must be consistent):
   //
   //		LRESULT OnMappingNotificationMeesage(WPARAM wParam, LPARAM lParam);
   //
   // 2. In your *.cpp file include the following "extern" statement somewhere at the beginning of
   //    the file.  This statement tells the linker that the value of the message is defined elsewhere:
   //
   //		extern const UINT UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION;  // defined in PortForwadEngine.cpp
   //
   // 3. In your .cpp implementation file, add an entry to the message map as follows:
   //
   //		ON_REGISTERED_MESSAGE( UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, OnMappingNotificationMeesage )
   //
   // 4. Again in your .cpp file, write the body of the OnMappingNotificationMeesage() function.
   //    Typically, you would check the WPARAM parameter to determine the nature of the notification.
   //      WPARAM == port_forward::EnumPortRetrieveInterval is sent at intervals, where
   //        LPARAM goes from 0 to 10.  You can use this to update a progress control (if you want)
   //      WPARAM == port_forward::EnumPortRetrieveDone is sent when the thread is done, where
   //        LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL).  Call the
   //        GetPortMappingVector() function to get a copy of the current contents of
   //        std::vector< port_forward::port_map > m_MappingContainer

   bool port_forward::async_port_retrieval( oswindow oswindow )
   {

      // returns TRUE if thread was started successfully

      if ( (m_ptaskPortRetrieval!=nullptr) || (oswindow==nullptr) || (!IsWindow(oswindow)) )
         return FALSE;

      m_oswindowForPortMapping = oswindow;

      __construct_below_normal(m_ptaskPortRetrieval, &port_forward::task_port_retrieval);

      if(m_ptaskPortRetrieval != nullptr )
      {
         return TRUE;
      }
      else
      {
         return FALSE;
      }
   }



   ///////////////////////////////////////////////
   //
   //  EditMappingUsingThreadThread()
   //
   //////////////////////////////////////////////
   //
   // The thread created by the EditMappingUsingThreadThread() function uses the same architecture for
   // message notification as above (ie, it posts a UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION
   // message), but with the following WPARAM and LPARAM encodings:
   //  WPARAM == port_forward::EnumEditMappingInterval at intervals, where
   //      LPARAM varies from 0 to 10.  You can use this to update of a progress control (if you want).
   //  WPARAM == port_forward::EnumEditMappingDone when the thread is finished, where
   //      LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL).


   bool port_forward::async_edit_mapping( port_forward::port_map& oldMapping, port_forward::port_map& newMapping, oswindow oswindow )
   {
      // returns TRUE if thread was started successfully

      if ( (m_ptaskEditMapping!=nullptr) || (oswindow==nullptr) || (!IsWindow(oswindow)) )
         return FALSE;

      m_scratchpadOldMapping = oldMapping;
      m_scratchpadNewMapping = newMapping;

      m_oswindowForEditMapping = oswindow;

      __construct_below_normal(m_ptaskEditMapping, &port_forward::task_edit_mapping);

      if(m_ptaskEditMapping != nullptr)
      {
         return TRUE;
      }
      else
      {
         return FALSE;
      }

   }



   ///////////////////////////////////////////////
   //
   //  AddMappingUsingThreadThread()
   //
   //////////////////////////////////////////////
   //
   // The thread created by the AddMappingUsingThreadThread() function uses the same architecture for
   // message notification as above (ie, it posts a UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION
   // message), but with the following WPARAM and LPARAM encodings:
   //  WPARAM == port_forward::EnumAddMappingInterval at intervals, where
   //      LPARAM varies from 0 to 10.  You can use this to update of a progress control (if you want).
   //  WPARAM == port_forward::EnumAddMappingDone when the thread is finished, where
   //      LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL).

   bool port_forward::async_add_mapping( port_forward::port_map& newMapping, oswindow oswindow )
   {
      // returns TRUE if thread was started successfully

      if ( (m_ptaskAddMapping!=nullptr) || (oswindow==nullptr) || (!IsWindow(oswindow)) )
         return FALSE;

      m_scratchpadAddedMapping = newMapping;

      m_oswindowForAddMapping = oswindow;

      __construct_below_normal(m_ptaskAddMapping, &port_forward::task_add_mapping);

      if(m_ptaskAddMapping != nullptr)
      {
         return TRUE;
      }
      else
      {
         return FALSE;
      }

   }



   ///////////////////////////////////////////////
   //
   //  DeleteMappingUsingThreadThread()
   //
   //////////////////////////////////////////////
   //
   // The thread created by the DeleteMappingUsingThreadThread() function uses the same architecture for
   // message notification as above (ie, it posts a UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION
   // message), but with the following WPARAM and LPARAM encodings:
   //  WPARAM == port_forward::EnumDeleteMappingInterval at intervals, where
   //      LPARAM varies from 0 to 10.  You can use this to update of a progress control (if you want).
   //  WPARAM == port_forward::EnumDeleteMappingDone when the thread is finished, where
   //      LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL).

   bool port_forward::async_delete_mapping( port_forward::port_map& oldMapping, oswindow oswindow )
   {
      // returns TRUE if thread was started successfully

      if ( (m_ptaskDeleteMapping!=nullptr) || (oswindow==nullptr) || (!IsWindow(oswindow)) )
         return FALSE;

      m_scratchpadDeletedMapping = oldMapping;

      m_oswindowForDeleteMapping = oswindow;

      __construct_below_normal(m_ptaskDeleteMapping, &port_forward::task_delete_mapping);

      if(m_ptaskDeleteMapping != nullptr)
      {
         return TRUE;
      }
      else
      {
         return FALSE;
      }

   }


   ///////////////////////////////////////////////
   //
   //  GetDeviceInformationUsingThreadThread()
   //
   //////////////////////////////////////////////
   //
   // The thread created by the GetDeviceInformationUsingThreadThread() function uses the same architecture for
   // message notification as above (ie, it posts a UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION
   // message), but with the following WPARAM and LPARAM encodings:
   //  WPARAM == port_forward::EnumDeviceInfoInterval at intervals, where
   //      LPARAM varies from 0 to 10.  You can use this to update of a progress control (if you want).
   //  WPARAM == port_forward::EnumDeviceInfoDone when thread is finished, where
   //      LPARAM signifies if the thread was or was not successful (S_OK or E_FAIL).  Call the
   //      GetDeviceInformationContainer() function to retrieve a copy of the current contents of
   //      port_forward::DeviceInformationContainer m_DeviceInfo

   bool port_forward::async_device_information_retrieval( oswindow oswindow )
   {
      // returns TRUE if thread was started successfully

      if ( (m_ptaskDeviceInformationRetrieval!=nullptr) || (oswindow==nullptr) || (!IsWindow(oswindow)) )
         return FALSE;

      m_oswindowForDeviceInfo = oswindow;

      __construct_below_normal(m_ptaskDeviceInformationRetrieval, &port_forward::task_device_information_retrieval);

      if(m_ptaskDeviceInformationRetrieval != nullptr)
      {
         return TRUE;
      }
      else
      {
         return FALSE;
      }

   }


   /*   static   */
   void port_forward::task_port_retrieval()
   {

      SetThreadName(::GetCurrentThreadId(), "PortRtrv" );  // helps in debugging to see a thread's name

      bool bContinue = TRUE;

      // local copies of shared variables

      oswindow oswindow_ForPosting = m_oswindowForPortMapping;

      WPARAM wp = EnumPortRetrieveInterval;
      LPARAM point = 0;


      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      // initialize COM

      if ( !SUCCEEDED( ::CoInitializeEx(nullptr,COINIT_MULTITHREADED) ) )  // STA model
         bContinue = FALSE;


      // create COM instance of IUPnPNAT

      IUPnPNAT* piNAT = nullptr;
      IStaticPortMappingCollection* piPortMappingCollection = nullptr;


      HRESULT hr;

      if ( !bContinue || !SUCCEEDED(hr= CoCreateInstance(__uuidof(UPnPNAT), nullptr, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&piNAT) ) || ( piNAT==nullptr ) )
         bContinue = FALSE;

      // Get the collection of forwarded ports

      if ( !bContinue || !SUCCEEDED(hr= piNAT->get_StaticPortMappingCollection(&piPortMappingCollection) ) || (piPortMappingCollection==nullptr ) )
         bContinue = FALSE;


      point = 1;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      // Get mapping enumerator and reset the list of mappings

      IUnknown* piUnk = nullptr;
      IEnumVARIANT* piEnumerator = nullptr;

      if ( !bContinue || !SUCCEEDED( piPortMappingCollection->get__NewEnum( &piUnk ) ) || piUnk==nullptr )
         bContinue = FALSE;

      if ( !bContinue || !SUCCEEDED( piUnk->QueryInterface(IID_IEnumVARIANT, (void **)&piEnumerator) ) || piEnumerator==nullptr )
         bContinue = FALSE;

      if ( !bContinue || !SUCCEEDED( piEnumerator->Reset() ) )
         bContinue = FALSE;

      point = 2;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      // get ::count of __static mappings

      long cMappings = 0;

      if ( !bContinue || !SUCCEEDED( piPortMappingCollection->get_Count( &cMappings ) ) )
         bContinue = FALSE;

      if ( cMappings <= 0 ) cMappings = 4;  // arbitrary non-zero value, so we can divide by non-zero value

      point = 3;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      HRESULT result = S_OK;
      i32 iii = 0;

      // clear all current mappings (note: thread-awareness is needed)

      ::EnterCriticalSection( &(m_cs) );
      m_MappingContainer.remove_all();
      ::LeaveCriticalSection( &(m_cs) );

      port_forward::port_map mapCont;

      while ( bContinue && SUCCEEDED(result) )
      {
         result = GetNextMapping( piEnumerator, mapCont );
         if ( SUCCEEDED(result) )
         {
            ::EnterCriticalSection( &(m_cs) );
            m_MappingContainer.add(new port_forward::port_map(mapCont));
            ::LeaveCriticalSection( &(m_cs) );
         }

         point = 3 + (10-3)*(++iii)/cMappings;

         ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );

      }

      // release COM objects and de-initialize COM

      if ( piEnumerator != nullptr )
      {
         piEnumerator->Release();
         piEnumerator = nullptr;
      }

      if ( piPortMappingCollection != nullptr )
      {
         piPortMappingCollection->Release();
         piPortMappingCollection = nullptr;
      }

      if ( piNAT != nullptr )
      {
         piNAT->Release();
         piNAT = nullptr;
      }


      CoUninitialize();

      // post completion message

      point = (bContinue ? S_OK : E_FAIL);

      wp = EnumPortRetrieveDone;
      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      m_ptaskPortRetrieval = nullptr;
      m_oswindowForPortMapping = nullptr;

   }


   /*   static   */
   void port_forward::task_device_information_retrieval()
   {
      SetThreadName(::GetCurrentThreadId(), "DevInfo" );  // helps in debugging to see a thread's name

      bool bContinue = TRUE;

      oswindow oswindow_ForPosting = m_oswindowForDeviceInfo;

      WPARAM wp = EnumDeviceInfoInterval;
      LPARAM point = 0;


      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      // initialize COM

      if ( !SUCCEEDED( ::CoInitializeEx(nullptr,COINIT_MULTITHREADED) ) )  // STA model
         bContinue = FALSE;

      // create COM instance of IUPnPDeviceFinder

      IUPnPDeviceFinder* piDeviceFinder = nullptr;

      if ( !bContinue || !SUCCEEDED( CoCreateInstance( CLSID_UPnPDeviceFinder, nullptr, CLSCTX_ALL,
                                     IID_IUPnPDeviceFinder, (void**) &piDeviceFinder ) ) || ( piDeviceFinder==nullptr ) )
         bContinue = FALSE;

      point = 1;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      // get devices of the desired type, using the PnP schema
      // < deviceType>urn:schemas-upnp-org:device:InternetGatewayDevice:1< /deviceType>

      BSTR bStrDev = SysAllocString( L"urn:schemas-upnp-org:device:InternetGatewayDevice:1" );
      IUPnPDevices* piFoundDevices = nullptr;

      if ( !bContinue || !SUCCEEDED( piDeviceFinder->FindByType( bStrDev, 0, &piFoundDevices ) )
            || ( piFoundDevices==nullptr ) )
         bContinue = FALSE;

      SysFreeString( bStrDev );


      point = 5;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      // now traverse the collection of piFoundDevices

      // the following code is axisd on code provided by MSDN in its Control Point API:
      // "Device Collections Returned By Synchronous Searches" at
      // http://msdn.microsoft.com/library/en-us/upnp/upnp/device_collections_returned_by_synchronous_searches.asp


      HRESULT result = S_OK;
      IUnknown * pUnk = nullptr;

      // remove all local devInfo from class member

      ::EnterCriticalSection( &(m_cs) );
      m_DeviceInfo.remove_all();
      ::LeaveCriticalSection( &(m_cs) );


      if ( bContinue && SUCCEEDED( piFoundDevices->get__NewEnum(&pUnk) ) && ( pUnk!=nullptr ) )
      {
         IEnumVARIANT * pEnumVar = nullptr;
         result = pUnk->QueryInterface(IID_IEnumVARIANT, (void **) &pEnumVar);
         if (SUCCEEDED(result))
         {
            VARIANT varCurDevice;
            VariantInit(&varCurDevice);
            pEnumVar->Reset();
            // Loop through each device in the collection
            while (S_OK == pEnumVar->Next(1, &varCurDevice, nullptr))
            {
               IUPnPDevice * pDevice = nullptr;
               IDispatch * pdispDevice = V_DISPATCH(&varCurDevice);
               if (SUCCEEDED(pdispDevice->QueryInterface(IID_IUPnPDevice, (void **) &pDevice)))
               {
                  // finally, post interval notification message and get all the needed information

                  point = 6;

                  ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


                  // allocate and fill local devInfo into class member
                  ::EnterCriticalSection( &(m_cs) );
                  device * pdevice = m_DeviceInfo.add_new(this);
                  result = PopulateDeviceInfoContainer( pDevice, *pdevice, oswindow_ForPosting );
                  ::LeaveCriticalSection( &(m_cs) );

               }
               VariantClear(&varCurDevice);
            }
            pEnumVar->Release();
         }
         pUnk->Release();
      }


      // release COM objects and de-initialize COM

      if ( piDeviceFinder!=nullptr )
      {
         piDeviceFinder->Release();
         piDeviceFinder = nullptr;
      }

      CoUninitialize();

      bContinue = SUCCEEDED( result );



      // post completion message

      point = (bContinue ? S_OK : E_FAIL);

      wp = EnumDeviceInfoDone;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      m_ptaskDeviceInformationRetrieval = nullptr;
      m_oswindowForDeviceInfo = nullptr;

   }


   /*   static   */
   void port_forward::task_edit_mapping()
   {
      SetThreadName(::GetCurrentThreadId(), "EditMap" );  // helps in debugging to see a thread's name

      bool bContinue = TRUE;

      port_map oldMapping = m_scratchpadOldMapping;
      port_map newMapping = m_scratchpadNewMapping;
      oswindow oswindow_ForPosting = m_oswindowForEditMapping;

      WPARAM wp = EnumEditMappingInterval;
      LPARAM point = 0;


      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      // initialize COM

      if ( !SUCCEEDED( ::CoInitializeEx(nullptr,COINIT_MULTITHREADED) ) )  // STA model
         bContinue = FALSE;


      // create COM instance of IUPnPNAT

      IUPnPNAT* piNAT = nullptr;
      IStaticPortMappingCollection* piPortMappingCollection = nullptr;

      if ( !bContinue || !SUCCEEDED( CoCreateInstance(__uuidof(UPnPNAT), nullptr, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&piNAT) ) || ( piNAT==nullptr ) )
         bContinue = FALSE;

      // Get the collection of forwarded ports

      if ( !bContinue || !SUCCEEDED( piNAT->get_StaticPortMappingCollection(&piPortMappingCollection) ) || (piPortMappingCollection==nullptr ) )
         bContinue = FALSE;


      point = 1;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      // get the target old mapping from the collection of mappings

      IStaticPortMapping* piStaticPortMapping = nullptr;

      if ( !bContinue || !SUCCEEDED( piPortMappingCollection->get_Item( atol(oldMapping.ExternalPort), oldMapping.Protocol.AllocSysString(), &piStaticPortMapping ) ) || (piStaticPortMapping==nullptr) )
         bContinue = FALSE;

      oldMapping.Protocol.release_string_buffer();


      point = 2;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      // update the mapping

      if ( bContinue )
      {
         HRESULT hr = S_OK;
         VARIANT_BOOL vb = ( ( newMapping.Enabled == "Yes" ) ? VARIANT_TRUE : VARIANT_FALSE );

         hr |= piStaticPortMapping->Enable( vb );
         point = 4;

         ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


         hr |= piStaticPortMapping->EditDescription( newMapping.Description.AllocSysString() );
         point = 6;

         ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


         hr |= piStaticPortMapping->EditInternalPort( atol(newMapping.InternalPort) );
         point = 8;

         ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


         hr |= piStaticPortMapping->EditInternalClient( newMapping.InternalClient.AllocSysString() );
         point = 10;

         ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


         if ( !SUCCEEDED(hr) )
            bContinue = FALSE;
      }


      // clean up and de-initialize COM

      if ( piStaticPortMapping != nullptr )
      {
         piStaticPortMapping->Release();
         piStaticPortMapping = nullptr;
      }


      if ( piPortMappingCollection != nullptr )
      {
         piPortMappingCollection->Release();
         piPortMappingCollection = nullptr;
      }

      if ( piNAT != nullptr )
      {
         piNAT->Release();
         piNAT = nullptr;
      }


      CoUninitialize();

      // post completion message

      point = (bContinue ? S_OK : E_FAIL);

      wp = EnumEditMappingDone;
      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      m_ptaskEditMapping = nullptr;
      m_oswindowForEditMapping = nullptr;

   }


   /*   static   */
   void port_forward::task_delete_mapping()
   {
      SetThreadName(::GetCurrentThreadId(), "DelMap" );  // helps in debugging to see a thread's name

      bool bContinue = TRUE;

      //port_forward * pThis = (port_forward *) p;

      // local copies of shared variables

      port_map oldMapping = m_scratchpadDeletedMapping;
      oswindow oswindow_ForPosting = m_oswindowForDeleteMapping;

      WPARAM wp = EnumDeleteMappingInterval;
      LPARAM point = 0;


      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      // initialize COM

      if ( !SUCCEEDED( ::CoInitializeEx(nullptr,COINIT_MULTITHREADED) ) )  // STA model
         bContinue = FALSE;


      // create COM instance of IUPnPNAT

      IUPnPNAT* piNAT = nullptr;
      IStaticPortMappingCollection* piPortMappingCollection = nullptr;

      if ( !bContinue || !SUCCEEDED( CoCreateInstance(__uuidof(UPnPNAT), nullptr, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&piNAT) ) || ( piNAT==nullptr ) )
         bContinue = FALSE;

      // Get the collection of forwarded ports

      if ( !bContinue || !SUCCEEDED( piNAT->get_StaticPortMappingCollection(&piPortMappingCollection) ) || (piPortMappingCollection==nullptr ) )
         bContinue = FALSE;


      point = 1;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      // get the target old mapping from the collection of mappings

      if ( !bContinue ||
            !SUCCEEDED( piPortMappingCollection->Remove( atol(oldMapping.ExternalPort), oldMapping.Protocol.AllocSysString() ) ) )
         bContinue = FALSE;

      oldMapping.Protocol.release_string_buffer();
      point = 2;

      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );




      // clean up and de-initialize COM


      if ( piPortMappingCollection != nullptr )
      {
         piPortMappingCollection->Release();
         piPortMappingCollection = nullptr;
      }

      if ( piNAT != nullptr )
      {
         piNAT->Release();
         piNAT = nullptr;
      }


      CoUninitialize();

      // post completion message

      point = (bContinue ? S_OK : E_FAIL);

      wp = EnumDeleteMappingDone;
      ::PostMessage( oswindow_ForPosting, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      m_ptaskDeleteMapping = nullptr;
      m_oswindowForDeleteMapping = nullptr;

      //return 0;
   }


   /*   static   */
   void port_forward::task_add_mapping()
   {
      SetThreadName(::GetCurrentThreadId(), "AddMap" );  // helps in debugging to see a thread's name

      ///port_forward * pThis = (port_forward *) p;

      port_map& newMapping = m_scratchpadAddedMapping;


      bool bContinue = TRUE;
      WPARAM wp = EnumAddMappingInterval;
      LPARAM point = 0;


      ::PostMessage( m_oswindowForAddMapping, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      // initialize COM

      if ( !SUCCEEDED( ::CoInitializeEx(nullptr,COINIT_MULTITHREADED) ) )  // STA model
         bContinue = FALSE;


      // create COM instance of IUPnPNAT

      IUPnPNAT* piNAT = nullptr;
      IStaticPortMappingCollection* piPortMappingCollection = nullptr;

      if ( !bContinue || !SUCCEEDED( CoCreateInstance(__uuidof(UPnPNAT), nullptr, CLSCTX_ALL, __uuidof(IUPnPNAT), (void **)&piNAT) ) || ( piNAT==nullptr ) )
         bContinue = FALSE;

      // Get the collection of forwarded ports

      if ( !bContinue || !SUCCEEDED( piNAT->get_StaticPortMappingCollection(&piPortMappingCollection) ) || (piPortMappingCollection==nullptr ) )
         bContinue = FALSE;


      point = 1;

      ::PostMessage( m_oswindowForAddMapping, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );



      // add the new mapping

      IStaticPortMapping* piStaticPortMapping = nullptr;

      VARIANT_BOOL vb = ( ( newMapping.Enabled == ("Yes") ) ? VARIANT_TRUE : VARIANT_FALSE );

      if ( !bContinue ||
            !SUCCEEDED(
            piPortMappingCollection->Add(
            atol(newMapping.ExternalPort),
            newMapping.Protocol.AllocSysString(),
            atol(newMapping.InternalPort),
            newMapping.InternalClient.AllocSysString(),
            vb,
            newMapping.Description.AllocSysString(),
            &piStaticPortMapping ) ) || (piStaticPortMapping==nullptr) )

         bContinue = FALSE;

      newMapping.Protocol.release_string_buffer();
      newMapping.InternalClient.release_string_buffer();
      newMapping.Description.release_string_buffer();

      point = 2;

      ::PostMessage( m_oswindowForAddMapping, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );




      // clean up and de-initialize COM

      if ( piStaticPortMapping != nullptr )
      {
         piStaticPortMapping->Release();
         piStaticPortMapping = nullptr;
      }


      if ( piPortMappingCollection != nullptr )
      {
         piPortMappingCollection->Release();
         piPortMappingCollection = nullptr;
      }

      if ( piNAT != nullptr )
      {
         piNAT->Release();
         piNAT = nullptr;
      }


      CoUninitialize();

      // post completion message

      point = (bContinue ? S_OK : E_FAIL);

      wp = EnumAddMappingDone;
      ::PostMessage( m_oswindowForAddMapping, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, point );


      m_ptaskAddMapping = nullptr;
      m_oswindowForAddMapping = nullptr;

      //return 0;
   }



   HRESULT port_forward::GetNextMapping( IEnumVARIANT* piEnumerator, port_forward::port_map& mappingContainer )
   {
      // uses the enumerator to get the next mapping and fill in a mapping container structure

      if ( piEnumerator == nullptr )
      {
         return E_FAIL;
      }

      VARIANT varCurMapping;
      VariantInit(&varCurMapping);

      HRESULT result = piEnumerator->Next( 1, &varCurMapping, nullptr);
      if( !SUCCEEDED(result) )
      {
         return E_FAIL;
      }

      if ( varCurMapping.vt == VT_EMPTY )
      {
         return E_FAIL;
      }

      IStaticPortMapping* piMapping = nullptr;
      IDispatch* piDispMap = V_DISPATCH(&varCurMapping);
      result = piDispMap->QueryInterface(IID_IStaticPortMapping, (void **)&piMapping);
      if( !SUCCEEDED(result) )
      {
         return E_FAIL;
      }


      // get external address

      BSTR bStr = nullptr;

      result = piMapping->get_ExternalIPAddress( &bStr );
      if( !SUCCEEDED(result) )
      {
         piMapping->Release();
         piMapping = nullptr;
         return E_FAIL;
      }

      if( bStr != nullptr )
         mappingContainer.ExternalIPAddress = string( ::str::international::unicode_to_utf8(bStr) );

      SysFreeString(bStr);
      bStr = nullptr;


      // get external port

      long lValue = 0;

      result = piMapping->get_ExternalPort( &lValue );
      if( !SUCCEEDED(result) )
      {
         piMapping->Release();
         piMapping = nullptr;
         return E_FAIL;
      }

      mappingContainer.ExternalPort.Format( "%d", lValue );


      // get internal port

      result = piMapping->get_InternalPort( &lValue );
      if( !SUCCEEDED(result) )
      {
         piMapping->Release();
         piMapping = nullptr;
         return E_FAIL;
      }

      mappingContainer.InternalPort.Format( ("%d"), lValue );


      // get protocol

      result = piMapping->get_Protocol( &bStr );
      if( !SUCCEEDED(result) )
      {
         piMapping->Release();
         piMapping = nullptr;
         return E_FAIL;
      }

      if( bStr != nullptr )
         mappingContainer.Protocol = ::str::international::unicode_to_utf8(bStr);

      SysFreeString(bStr);
      bStr = nullptr;


      // get internal client

      result = piMapping->get_InternalClient( &bStr );
      if( !SUCCEEDED(result) )
      {
         piMapping->Release();
         piMapping = nullptr;
         return E_FAIL;
      }

      if( bStr != nullptr )
         mappingContainer.InternalClient = ::str::international::unicode_to_utf8(bStr);

      SysFreeString(bStr);
      bStr = nullptr;


      // determine whether it's enabled

      VARIANT_BOOL bValue = VARIANT_FALSE;

      result = piMapping->get_Enabled( &bValue );
      if( !SUCCEEDED(result) )
      {
         piMapping->Release();
         piMapping = nullptr;
         return E_FAIL;
      }

      mappingContainer.Enabled = bValue==VARIANT_FALSE ? "No" : "Yes" ;


      // get description

      result = piMapping->get_Description( &bStr );
      if( !SUCCEEDED(result) )
      {
         piMapping->Release();
         piMapping = nullptr;
         return E_FAIL;
      }

      if( bStr != nullptr )
         mappingContainer.Description = ::str::international::unicode_to_utf8( bStr );

      SysFreeString(bStr);
      bStr = nullptr;

      // clean up

      piMapping->Release();
      piMapping = nullptr;


      VariantClear( &varCurMapping );

      return S_OK;

   }



   HRESULT port_forward::PopulateDeviceInfoContainer( IUPnPDevice* piDevice,
         port_forward::device & deviceInfo, oswindow oswindow /* =nullptr */ )
   {

      HRESULT result=S_OK, hrReturn=S_OK;
      long lValue = 0;
      BSTR bStr = nullptr;
      VARIANT_BOOL bValue = VARIANT_FALSE;
      IUPnPDevices* piDevices = nullptr;

      // parameters for interval notification messages

      double point = 6.0;

      double addend = (10.0 - 6.0)/19.0;  // there are 19 parameters that are retrieved, and we already sent 6 notifications
      WPARAM wp = EnumDeviceInfoInterval;


      // get children: We will NOT enumerate through the devices that might be returned.
      // Rather, we will only indicate how many there are.  So, in this sense, the information
      // is somewhat redundant to HasChildren

      result = piDevice->get_Children( &piDevices );
      hrReturn |= result;
      if ( SUCCEEDED(result) && (piDevices!=nullptr) )
      {
         piDevices->get_Count( &lValue );
         if ( lValue==0 )
         {
            deviceInfo.Children.Format( ("No: Zero children") );
         }
         else if ( lValue==1 )
         {
            deviceInfo.Children.Format( ("Yes: One child") );
         }
         else if ( lValue>=1 )
         {
            deviceInfo.Children.Format( ("Yes: %d children"), lValue );
         }
         piDevices->Release();
         piDevices = nullptr;
         lValue = 0;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get Description

      result = piDevice->get_Description( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.Description = ::str::international::unicode_to_utf8( bStr );
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
      {
         bool b = ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) ) != FALSE;

         if(!b)
         {
            DWORD dw = ::get_last_error();
            ::MessageBoxA(nullptr, __str((u32) dw), __str((u32) dw), 0);
         }
      }


      // Get FriendlyName

      result = piDevice->get_FriendlyName( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.FriendlyName = ::str::international::unicode_to_utf8(bStr );
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get HasChildren

      result = piDevice->get_HasChildren( &bValue );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.HasChildren = bValue==VARIANT_FALSE  ? "No" : "Yes";
         bValue = VARIANT_FALSE;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get IconURL

      BSTR bStrMime = SysAllocString(L"image/png");

      //result = piDevice->IconURL( bStrMime, 32, 32, 8, &bStr );
      result = piDevice->IconURL( bStrMime, 48, 48, 24, &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.IconURL = ::str::international::unicode_to_utf8( bStr );
         SysFreeString(bStr);
         bStr = nullptr;
      }

      SysFreeString(bStrMime);
      bStrMime = nullptr;

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get IsRootDevice

      result = piDevice->get_IsRootDevice( &bValue );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.IsRootDevice = bValue==VARIANT_FALSE ? "No" : "Yes";
         bValue = VARIANT_FALSE;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get ManufacturerName

      result = piDevice->get_ManufacturerName( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.ManufacturerName = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get ManufacturerURL

      result = piDevice->get_ManufacturerURL( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.ManufacturerURL = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get ModelName

      result = piDevice->get_ModelName( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.ModelName = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get ModelNumber

      result = piDevice->get_ModelNumber( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.ModelNumber = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get ModelURL

      result = piDevice->get_ModelURL( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.ModelURL = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get ParentDevice.  Actually, we will only get the FriendlyName of the parent device,
      // if there is one

      IUPnPDevice* piDev = nullptr;

      result = piDevice->get_ParentDevice( &piDev );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         if ( piDev==nullptr )
         {
            deviceInfo.ParentDevice.Format( ("This is a topmost device") );
         }
         else
         {
            if ( SUCCEEDED( piDev->get_FriendlyName( &bStr ) ) )
            {
               deviceInfo.ParentDevice = ::str::international::unicode_to_utf8(bStr);
               SysFreeString(bStr);
               bStr = nullptr;
            }
            piDev->Release();
            piDev = nullptr;
         }
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get PresentationURL

      result = piDevice->get_PresentationURL( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.PresentationURL = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get RootDevice.  Actually, we will only get the FriendlyName of the root device,
      // if there is one

      result = piDevice->get_RootDevice( &piDev );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         if ( piDev==nullptr )
         {
            deviceInfo.RootDevice.Format( ("This is a topmost device") );
         }
         else
         {
            if ( SUCCEEDED( piDev->get_FriendlyName( &bStr ) ) )
            {
               deviceInfo.RootDevice = ::str::international::unicode_to_utf8(bStr );
               SysFreeString(bStr);
               bStr = nullptr;
            }
            piDev->Release();
            piDev = nullptr;
         }
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );




      // Get SerialNumber

      result = piDevice->get_SerialNumber( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.SerialNumber = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get Services.  Actually, we will NOT enumerate through all the services that are contained
      // in the IUPnPServices collection.  Rather, we will only get a ::count of services

      IUPnPServices* piServices = nullptr;

      result = piDevice->get_Services( &piServices );
      hrReturn |= result;
      if ( SUCCEEDED(result) && (piServices!=nullptr) )
      {
         piServices->get_Count( &lValue );
         if ( lValue==0 )
         {
            deviceInfo.Services.Format( ("No: Zero services") );
         }
         else if ( lValue==1 )
         {
            deviceInfo.Services.Format( ("Yes: One service") );
         }
         else if ( lValue>=1 )
         {
            deviceInfo.Services.Format( ("Yes: %d services"), lValue );
         }
         piServices->Release();
         piServices = nullptr;
         lValue = 0;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get Type

      result = piDevice->get_Type( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.Type = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get UniqueDeviceName

      result = piDevice->get_UniqueDeviceName( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.UniqueDeviceName = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );



      // Get UPC

      result = piDevice->get_UPC( &bStr );
      hrReturn |= result;
      if ( SUCCEEDED(result) )
      {
         deviceInfo.UPC = ::str::international::unicode_to_utf8(bStr);
         SysFreeString(bStr);
         bStr = nullptr;
      }

      if ( oswindow!=nullptr )
         ::PostMessage( oswindow, UWM_PORT_FORWARD_ENGINEHREAD_NOTIFICATION, wp, (LPARAM)(point += addend) );


      return hrReturn;
   }











   HRESULT STDMETHODCALLTYPE port_forward::IDerivedNATNumberOfEntriesCallback::QueryInterface(REFIID iid, void ** ppvObject)
   {
      HRESULT hr = S_OK;
      *ppvObject = nullptr;

      if ( iid == IID_IUnknown ||	iid == IID_INATNumberOfEntriesCallback )
      {
         *ppvObject = this;
         AddRef();
         hr = NOERROR;
      }
      else
      {
         hr = E_NOINTERFACE;
      }

      return hr;
   }


   HRESULT STDMETHODCALLTYPE port_forward::IDerivedNATExternalIPAddressCallback::QueryInterface(REFIID iid, void ** ppvObject)
   {
      HRESULT hr = S_OK;
      *ppvObject = nullptr;

      if ( iid == IID_IUnknown ||	iid == IID_INATExternalIPAddressCallback )
      {
         *ppvObject = this;
         AddRef();
         hr = NOERROR;
      }
      else
      {
         hr = E_NOINTERFACE;
      }

      return hr;
   }

   /////////////////////////////////////////////////////////////////////
   //
   // SetThreadName -- a function to set the current thread's 8-character name
   // so as to be able to distinguish between the threads during debug operations
   //
   // Usage: SetThreadName (-1, "MainThread");
   // Must be called from the thread you're trying to name
   // For example SetThreadName(-1, "1st Thread");
   // Will truncate name to 8 characters
   //
   // code obtained from
   // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vsdebug/html/vxtsksettingthreadname.asp
   //


   void SetThreadName( DWORD dwThreadID, LPCSTR szThreadName)
   {

      struct THREADNAME_INFO
      {
         DWORD dwType; // must be 0x1000
         LPCSTR szName; // pointer to name (in user addr space)
         DWORD dwThreadID; // thread ID (-1=caller thread)
         DWORD dwFlags; // reserved for future use, must be zero
      } ;

      THREADNAME_INFO info;
      info.dwType = 0x1000;
      info.szName = szThreadName;
      info.dwThreadID = dwThreadID;
      info.dwFlags = 0;

      __try
      {
         RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD), (ULONG_PTR *) &info );
      }
      __except(EXCEPTION_CONTINUE_EXECUTION)
      {
      }
   }


} // namespace windows

