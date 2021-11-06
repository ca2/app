//
//  _impl_synchronization_result.h
//  acme
//
//  Created by Camilo Sasuke on 2021-05-11 23:45 BRT <3ThomasBS_!!.
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once




//inline bool synchronization_result::abandoned() const
//{
//   
//   return m_esynchronizationresult >= e_synchronization_result_abandoned_base
//      && m_esynchronizationresult < (e_synchronization_result_abandoned_base + MAXIMUM_SYNCHRONIZING_OBJECTS);
//
//}


//inline ::index synchronization_result::abandoned_index() const
//{
//   
//   if (!abandoned())
//   {
//
//      return -1;
//
//   }
//
//   return m_esynchronizationresult - e_synchronization_result_abandoned_base;
//
//}


//inline bool synchronization_result::error() const
//{
//   
//   return m_esynchronizationresult == e_synchronization_result_error;
//
//}


//inline bool synchronization_result::bad_thread() const
//{
//   
//   return m_esynchronizationresult == e_synchronization_result_bad_thread;
//
//}


//inline bool synchronization_result::timed_out() const
//{
//   
//   return m_esynchronizationresult == e_synchronization_result_timed_out;
//
//}


//inline bool synchronization_result::signaled() const
//{
//   
//   return m_esynchronizationresult >= e_synchronization_result_signaled_base &&
//      m_esynchronizationresult < (e_synchronization_result_signaled_base + MAXIMUM_SYNCHRONIZING_OBJECTS);
//
//}



//inline bool synchronization_result::succeeded() const
//{
//   
//   return signaled();
//
//}


//inline ::index synchronization_result::signaled_index() const
//{
//
//   if (!signaled())
//   {
//
//      return -1;
//
//   }
//
//   return m_esynchronizationresult - e_synchronization_result_signaled_base;
//
//}
//


