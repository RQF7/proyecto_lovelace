#!/bin/sh

#
# Instalación de dependencias de distribución.
# LaTeX y doxygen
#
# Proyecto Lovelace.
#

# Desde repositorios de ubuntu:
sudo apt-get -qq install \
  texlive \
  texlive-latex-recommended \
  texlive-latex-extra \
  texlive-lang-spanish \
  texlive-bibtex-extra \
  texlive-generic-extra \
  graphviz

# glossaries
wget --quiet http://mirrors.ctan.org/install/macros/latex/contrib/glossaries.tds.zip
unzip --qq -d ~/texmf glossaries.tds.zip
rm glossaries.tds.zip

# tracklang
wget --quiet http://mirrors.ctan.org/install/macros/generic/tracklang.tds.zip
unzip -qq -d ~/texmf tracklang.tds.zip
rm tracklang.tds.zip

# bibtex
wget --quiet https://iweb.dl.sourceforge.net/project/biblatex/biblatex-3.9/biblatex-3.9.tds.tgz
tar -xf biblatex-3.9.tds.tgz -C ~/texmf
rm biblatex-3.9.tds.tgz

# babel
wget --quiet http://mirrors.ctan.org/install/macros/latex/required/babel-base.tds.zip
unzip -qq -d ~/texmf babel-base.tds.zip
rm babel-base.tds.zip

# biber
wget --quiet https://phoenixnap.dl.sourceforge.net/project/biblatex-biber/biblatex-biber/current/binaries/Linux/biber-linux_x86_64.tar.gz
mkdir ~/ejecutable_biber
tar -xf biber-linux_x86_64.tar.gz -C ~/ejecutable_biber
rm biber-linux_x86_64.tar.gz

# doxygen
# wget --quiet http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.14.linux.bin.tar.gz
# mkdir ~/ejecutable_doxygen
#tar -xf doxygen-1.8.14.linux.bin.tar.gz -C ~/ejecutable_doxygen
# rm doxygen-1.8.14.linux.bin.tar.gz

git clone https://github.com/doxygen/doxygen.git ~/doxygen
cd ~/doxygen
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
sudo make install
