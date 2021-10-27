if (BUILD_DOC)
  find_package(Doxygen REQUIRED doxygen)

  # Doxygen options
  set(DOXYGEN_ALPHABETICAL_INDEX NO)
  set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
  set(DOXYGEN_CASE_SENSE_NAMES NO)
  set(DOXYGEN_CLASS_DIAGRAMS NO)
  set(DOXYGEN_DISTRIBUTE_GROUP_DOC YES)
  set(DOXYGEN_EXCLUDE bin)
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_EXTRACT_LOCAL_CLASSES NO)
  set(DOXYGEN_FILE_PATTERNS "*.hh;*.cc")
  set(DOXYGEN_GENERATE_TREEVIEW YES)
  set(DOXYGEN_HIDE_FRIEND_COMPOUNDS YES)
  set(DOXYGEN_HIDE_IN_BODY_DOCS YES)
  set(DOXYGEN_HIDE_UNDOC_CLASSES YES)
  set(DOXYGEN_HIDE_UNDOC_MEMBERS YES)
  set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
  set(DOXYGEN_QT_AUTOBRIEF YES)
  set(DOXYGEN_QUIET YES)
  set(DOXYGEN_RECURSIVE YES)
  set(DOXYGEN_REFERENCED_BY_RELATION YES)
  set(DOXYGEN_REFERENCES_RELATION YES)
  set(DOXYGEN_SORT_BY_SCOPE_NAME YES)
  set(DOXYGEN_SORT_MEMBER_DOCS NO)
  set(DOXYGEN_SOURCE_BROWSER YES)
  set(DOXYGEN_STRIP_CODE_COMMENTS NO)

  set(DOXYGEN_GENERATE_LATEX YES)
  set(DOXYGEN_STRIP_FROM_PATH ./)
  set(DOXYGEN_FULL_PATH_NAMES NO)

  doxygen_add_docs(doc
    "${CMAKE_SOURCE_DIR}/lib"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}"
    ALL
    COMMENT "Generate documentation"
  )

endif()
