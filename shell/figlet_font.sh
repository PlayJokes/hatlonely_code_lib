#!/usr/bin/env bash

for font in `figlet -l`; do
    echo ${font}
    figlet -f ${font} $1
done
