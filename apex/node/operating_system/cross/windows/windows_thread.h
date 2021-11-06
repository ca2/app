//
//  windows_thread.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 16/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


CLASS_DECL_ACME ::u32 ResumeThread(htask_t htask);
CLASS_DECL_ACME int_bool SetThreadPriority(htask_t htask, i32 nPriority);
CLASS_DECL_ACME i32 GetThreadPriority(htask_t htask);



