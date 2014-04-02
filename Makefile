ifneq ($(wildcard config.make),)
	include config.make
endif

ifndef OF_ROOT
	OF_ROOT=$(HOME)/openframeworks
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk

ifneq ($(wildcard prebuild.make),)
	include prebuild.make
endif
