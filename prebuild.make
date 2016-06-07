.DEFAULT_GOAL=PrePost

PODIR = po
POTFILE = $(PODIR)/$(PROJECT_NAME).pot

.INTERMEDIAT: $(POTFILE)

PrePost: Release postbuild

lang: lang-ext lang-conv

prebuild: lang-ext
	@tput bold; echo PREBUILD phase DONE; tput sgr0

postbuild: lang-conv
	@tput bold; echo POSTBUILD phase DONE; tput sgr0

$(POTFILE): src/*.cpp src/*.h prebuild.make config.make
	@tput setaf 2; echo gettext extraction to POT file; tput sgr0
	xgettext --output=- --default-domain=$(PROJECT_NAME) --c++ --keyword=_ \
	--keyword=_N --sort-by-file --add-comments --package-name=$(PROJECT_NAME) \
	--package-version=$(PROJECT_VERSION) --msgid-bugs-address=$(GETTEXT_MAINTAINER_EMAIL) \
	--copyright-holder="$(GETTEXT_COPYRIGHT_HOLDER)" src/* | \
	sed -e "s/SOME DESCRIPTIVE TITLE/RealTime Visual projector management/" \
	-e "s/YEAR/2014/g" -e "s/FIRST AUTHOR/$(GETTEXT_COPYRIGHT_HOLDER)/" \
	-e "s/<EMAIL@ADDRESS>,/<$(GETTEXT_MAINTAINER_EMAIL)>,/" \
	-- > $(POTFILE)

lang-ext: $(POTFILE)

lang-push: lang-ext
	@tput setaf 2; echo Transifex push; tput sgr0
	tx push -s

lang-pull:
	@tput setaf 2; echo Transifex pull; tput sgr0
	tx pull -a

lang-conv: $(PODIR)/*.po
	@tput setaf 2; echo Converting language text file to binary MO; tput sgr0
	for lang in $(subst .po,,$(subst $(PODIR)/,,$?)); do \
		mkdir -p  bin/$$lang/LC_MESSAGES/; \
		msgfmt -o bin/$$lang/LC_MESSAGES/vilain.mo $(PODIR)/$$lang.po; \
	done
