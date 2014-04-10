.DEFAULT_GOAL=PrePost

PrePost: prebuild Release postbuild

prebuild: lang-ext lang-push lang-pull lang-conv
	@tput bold; echo PREBUILD phase; tput sgr0

postbuild:
	@tput bold; echo POSTBUILD phase; tput sgr0


lang-ext:
	@tput setaf 2; echo gettext extraction to POT file; tput sgr0
	xgettext --output=- --default-domain=$(PROJECT_NAME) --c++ --keyword=_ --keyword=_N --sort-by-file --package-name=$(PROJECT_NAME) --package-version=$(PROJECT_VERSION) --msgid-bugs-address=$(GETTEXT_MAINTAINER_EMAIL) --copyright-holder="$(GETTEXT_COPYRIGHT_HOLDER)" src/* | sed -e "s/SOME DESCRIPTIVE TITLE/RealTime Visual projector management/" -e "s/YEAR/2014/g" -e "s/FIRST AUTHOR/Grégory DAVID/" -e "s/<EMAIL@ADDRESS>,/<groolot@groolot\.net>,/" -- > po/vilain.pot

lang-push: lang-ext
	@tput setaf 2; echo Transifex push; tput sgr0
	tx push -s

lang-pull: lang-ext lang-push
	@tput setaf 2; echo Transifex pull; tput sgr0
	tx pull -a

lang-conv: lang-pull
	@tput setaf 2; echo Converting language text file to binary MO; tput sgr0
	tx pull -a

