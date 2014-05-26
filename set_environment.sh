#!/bin/bash
OF_VERSION=0.8.1
OF_FLAVOUR=linux64_release
OF_FILE=of_v${OF_VERSION}_${OF_FLAVOUR}.tar.gz

# Compile toolchain
tput setaf 2; echo Install compilation toolchain + Git; tput sgr0
sudo apt-get update -qq || exit 1
#sudo apt-get install -qq libboost1.48-dev libyajl-dev libxml2-dev libxqilla-dev
sudo apt-get install -qq g++-4.8 git || exit 1

# Get openFrameworks
tput setaf 2; echo Install openFrameworks; tput sgr0
pushd ${HOME}
wget http://www.openframeworks.cc/versions/v${OF_VERSION}/${OF_FILE} -O /tmp/${OF_FILE} || exit 1
tar xvfz /tmp/${OF_FILE} || exit 1
mv of_v${OF_VERSION}_${OF_FLAVOUR} openframeworks || exit 1
popd

# Install library dependencies
tput setaf 2; echo "Install needed libraries (OF)"; tput sgr0
sudo ${HOME}/openframeworks/scripts/linux/debian/install_dependencies.sh || exit 1

# Install codecs
tput setaf 2; echo "Install several codecs (OF)"; tput sgr0
sudo ${HOME}/openframeworks/scripts/linux/debian/install_codecs.sh || exit 1

# Install required AddOns
tput setaf 2; echo Install required ofxAddons; tput sgr0
./download_addons.sh || exit 1
