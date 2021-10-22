set(TOOLLIST
  onegin
)

foreach(TOOL ${TOOLLIST})
  add_subdirectory(${TOOL})
endforeach()

set(TOOLLIST "${TOOLLIST}" PARENT_SCOPE)
