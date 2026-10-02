# Runs TOOL with stdin from IN and stdout to OUT, in WORKDIR. ARGS is separated by |.
if(NOT DEFINED WORKDIR)
  set(WORKDIR ".")
endif()
string(REPLACE "|" ";" ARGS "${ARGS}")
set(_in)
if(DEFINED IN)
  set(_in INPUT_FILE "${IN}")
endif()
execute_process(COMMAND "${TOOL}" ${ARGS}
  WORKING_DIRECTORY "${WORKDIR}"
  ${_in}
  OUTPUT_FILE "${OUT}"
  RESULT_VARIABLE rc)
if(NOT rc EQUAL 0)
  file(REMOVE "${OUT}")
  message(FATAL_ERROR "${TOOL} failed with ${rc}")
endif()
