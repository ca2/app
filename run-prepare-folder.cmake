# The helper may repair files elsewhere in the checkout. Serialize calls from
# parallel project builds in the same CMake build tree.
file(LOCK "${LOCK_FILE}")
execute_process(
    COMMAND "${HELPER}" --defer-prepare-folder "${PROJECT_DIRECTORY}/" "${PLATFORM}" "${CONFIGURATION}"
    RESULT_VARIABLE result)
if(NOT result STREQUAL "0")
    message(FATAL_ERROR "application_build_helper failed for ${PROJECT_DIRECTORY} (${result})")
endif()
