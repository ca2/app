﻿//
//  status_range_authentication.h
//  (account_e_success.h)
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//


error_authentication = INT_FAILURE_STATUS(STATUS_RANGE_AUTHENTICATION),
error_credentials,
error_pre_authentication,
error_pre_authentication_missing_sessid,
error_pre_authentication_missing_account_server,
error_pre_authentication_invalid,
error_authentication_missing_sessid,
error_authentication_missing_host,
error_authentication_none,
error_authentication_in_progress,
error_authentication_no_connection,
error_credentials_non_interactive,
error_credentials_user_cancelled,
error_credentials_no_valid_cached_credentials,
error_credentials_no_login,
error_credentials_no_password,
error_credentials_invalid,
error_credentials_invalid_login,
error_credentials_invalid_password,
error_authentication_wrong_password_or_login,
error_authentication_time_out,
error_authentication_invalid_sessid,
error_authentication_session_expired,
error_authorization,
error_licensing,
error_licensing_no_user,
error_registration_deferred,
error_please_finish_registration,


success_authenticated = INT_SUCCESS_STATUS(STATUS_RANGE_AUTHENTICATION),
success_credentials,
success_pre_authenticated,
success_licensed,
success_authorized,
success_optional_not_authenticated,


