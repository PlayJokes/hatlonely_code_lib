#!/usr/bin/env bash

mkdir -p ~/.vim/autoload ~/.vim/bundle &&
cd ~/.vim &&
wget --no-check-certificate https://tpo.pe/pathogen.vim &&
cd ~/.vim/bundle &&
git clone git://github.com/godlygeek/tabular.git

