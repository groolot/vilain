.DEFAULT_GOAL=PrePost

PrePost: prebuild  Release postbuild

prebuild:
	@tput bold; echo PREBUILD phase; tput sgr0
	@tput setaf 2; echo gettext extraction; tput sgr0
	xgettext --output=- --default-domain=$(PROJECT_NAME) --c++ --keyword=_ --keyword=_N --sort-by-file --package-name=$(PROJECT_NAME) --package-version=$(PROJECT_VERSION) --msgid-bugs-address=$(GETTEXT_MAINTAINER_EMAIL) --copyright-holder="$(GETTEXT_COPYRIGHT_HOLDER)" src/* | sed -e "s/SOME DESCRIPTIVE TITLE/RealTime Visual projector management/" -e "s/YEAR/2014/g" -e "s/FIRST AUTHOR/Grégory DAVID/" -e "s/<EMAIL@ADDRESS>,/<groolot@groolot\.net>,/" -- > po/vilain.po

postbuild:
	@tput bold; echo POSTBUILD phase; tput sgr0
