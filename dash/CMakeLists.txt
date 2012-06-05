set(UNITY_SRC ../plugins/unityshell/src)

find_package (PkgConfig)

set (CFLAGS
     ${CACHED_UNITY_DEPS_CFLAGS}
     ${CACHED_UNITY_DEPS_CFLAGS_OTHER}
     ${MAINTAINER_CFLAGS}
     "-DGETTEXT_PACKAGE=\"unity\""
     "-I${CMAKE_CURRENT_BINARY_DIR}"
     )

if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
  set (CFLAGS ${CFLAGS} "-fPIC")
endif (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")

add_definitions (${CFLAGS})

set (LIBS ${CACHED_UNITY_DEPS_LIBRARIES} "-lunity-core-${UNITY_API_VERSION} -lm -lGL -lGLU")
link_libraries (${LIBS})

set (LIB_PATHS ${CACHED_UNITY_DEPS_LIBRARY_DIRS})
link_directories (${CMAKE_BINARY_DIR}/UnityCore ${LIB_PATHS})

include_directories (. .. ../services ../UnityCore ${UNITY_SRC} ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

#
# Headers & Sources
#
set (DASH_SOURCES
     AbstractPlacesGroup.cpp
     DashController.cpp
     DashView.cpp
     DashViewPrivate.cpp
     FilterAllButton.cpp
     FilterBar.cpp
     FilterBasicButton.cpp
     FilterExpanderLabel.cpp
     FilterFactory.cpp
     FilterGenreButton.cpp
     FilterGenreWidget.cpp
     FilterMultiRangeButton.cpp
     FilterMultiRangeWidget.cpp
     FilterRatingsButton.cpp
     FilterRatingsWidget.cpp
     LensBar.cpp
     LensBarIcon.cpp
     LensView.cpp
     LensViewPrivate.cpp
     PlacesGroup.cpp
     PlacesVScrollBar.cpp
     PreviewApplications.cpp
     PreviewBase.cpp
     PreviewBasicButton.cpp
     ResultRenderer.cpp
     ResultRendererHorizontalTile.cpp
     ResultRendererTile.cpp
     ResultView.cpp
     ResultViewGrid.cpp
     )

add_library (dash-lib STATIC ${DASH_SOURCES})
add_dependencies (dash-lib unity-core-${UNITY_API_VERSION} unity-shared)
# 
# Standalone variant
#
add_executable (dash StandaloneDash.cpp)
add_dependencies (dash dash-lib)
target_link_libraries (dash dash-lib unity-shared)