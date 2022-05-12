if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject)
download_project(PROJ                cxxopts
                 GIT_REPOSITORY      https://github.com/jarro2783/cxxopts.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

add_subdirectory(${cxxopts_SOURCE_DIR} ${cxxopts_BINARY_DIR})
include_directories("${cxxopts_SOURCE_DIR}/include")