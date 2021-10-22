set(LIBLIST
  FileSys
  Qsort
)

foreach(LIB ${LIBLIST})
  add_subdirectory(${LIB})
endforeach()

set(LIBLIST "${LIBLIST}" PARENT_SCOPE)
