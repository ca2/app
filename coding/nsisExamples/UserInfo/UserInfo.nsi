Name "UserInfo.dll test"
OutFile UserInfo.exe

!define REALMSG "$\nOriginal non-restricted account type: $2"

Section
	ClearErrors
	UserInfo::GetName
	IfErrors Win9x
	Pop $0
	UserInfo::GetAccountType
	Pop $1
	# GetOriginalAccountType will check the tokens of the original user of the
	# current thread/process. If the user tokens were elevated or limited for
	# this process, GetOriginalAccountType will return the non-restricted
	# account type.
	# On Vista with UAC, for example, this is not the same value when running
	# with `RequestExecutionLevel user`. GetOriginalAccountType will return
	# "admin" while GetAccountType will return "user".
	UserInfo::GetOriginalAccountType
	Pop $2
	StrCmp $1 "Admin" 0 +3
		MessageBox e_message_box_ok 'User "$0" is in the Administrators group${REALMSG}'
		Goto done
	StrCmp $1 "Power" 0 +3
		MessageBox e_message_box_ok 'User "$0" is in the Power Users group${REALMSG}'
		Goto done
	StrCmp $1 "User" 0 +3
		MessageBox e_message_box_ok 'User "$0" is just a regular user${REALMSG}'
		Goto done
	StrCmp $1 "Guest" 0 +3
		MessageBox e_message_box_ok 'User "$0" is a guest${REALMSG}'
		Goto done
	MessageBox e_message_box_ok "Unknown error"
	Goto done

	Win9x:
		# This one means you don't need to care about admin or
		# not admin because Windows 9x doesn't either
		MessageBox e_message_box_ok "Error! This DLL can't run under Windows 9x!"

	done:
SectionEnd

