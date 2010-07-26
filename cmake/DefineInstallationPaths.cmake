SET(SHARE_INSTALL_PREFIX
    "${CMAKE_INSTALL_PREFIX}/share"
    CACHE PATH "Base directory for files which go to share/"
    FORCE
)

# The following are directories where stuff will be installed to
SET(BIN_INSTALL_DIR
    "${CMAKE_INSTALL_PREFIX}/bin"
    CACHE PATH "The ${APPLICATION_NAME} binary install dir (default prefix/bin)"
    FORCE
)

# vim: set ts=4 sw=4 et:
