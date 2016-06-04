ifneq ($(wildcard config.make),)
	include config.make
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk

ifneq ($(wildcard prebuild.make),)
	include prebuild.make
endif
