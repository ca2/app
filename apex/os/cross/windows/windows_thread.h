//
//  windows_thread.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 16/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


CLASS_DECL_ACME ::u32 WINAPI ResumeThread(htask_t hthread);
CLASS_DECL_ACME int_bool WINAPI SetThreadPriority(htask_t hthread, i32 nPriority);
CLASS_DECL_ACME i32 WINAPI GetThreadPriority(htask_t hthread);



