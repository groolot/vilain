OF_ROOT = $(HOME)/openframeworks
PROJECT_NAME = vilain
# Version number comply with the Semantic Versioning http://semver.org
PROJECT_VERSION = 0.0.1
# PROJECT_ROOT = .
# PROJECT_EXTERNAL_SOURCE_PATHS =
# PROJECT_EXCLUSIONS =
PROJECT_EXCLUSIONS = $(PROJECT_ROOT)/addons/ofxOsc/libs/oscpack/src/ip/win32
PROJECT_EXCLUSIONS += $(PROJECT_ROOT)/addons/ofxOscRouter/example/src
PROJECT_EXCLUSIONS += $(PROJECT_ROOT)/addons/ofxAnimatable/example
# PROJECT_LDFLAGS=-Wl,-rpath=./libs
PROJECT_DEFINES += PROG_NAME="\"$(PROJECT_NAME)\""

# PLATFORM_LIBRARIES +=
# PLATFORM_LIBRARY_SEARCH_PATHS +=
# PLATFORM_STATIC_LIBRARIES +=
# PLATFORM_PKG_CONFIG_LIBRARIES +=

# PROJECT_CFLAGS = -std=c++14
# PROJECT_OPTIMIZATION_CFLAGS_RELEASE =
# PROJECT_OPTIMIZATION_CFLAGS_DEBUG =
# PROJECT_CXX =g++
# PROJECT_CC =gcc

GETTEXT_MAINTAINER_EMAIL=dev@groolot.net
GETTEXT_COPYRIGHT_HOLDER=Grégory DAVID

# MAKEFILE_DEBUG=true
