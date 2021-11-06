//
//  ca_os_thread.h
//  ca
//
//  Created by Camilo Sasuke Tsumanuma on 6/26/13.
//
//

#pragma once


void * get_thread_ptr(const char * pszKey);
void set_thread_ptr(const char * pszKey, const void * p);


int get_thread_int(const char * pszKey);
void set_thread_int(const char * pszKey, int i);


i32 process_get_os_priority(i32 nCa2Priority);

i32 process_get_scheduling_priority(i32 iOsPriority);
