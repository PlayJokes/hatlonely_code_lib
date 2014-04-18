#!/usr/bin/bash

DIRECTORYS="/bin /usr/bin /usr/local/bin /sbin /usr/sbin /usr/local/sbin"

get_md5()
{
    cd $1
    for file in `ls`; do
        if [ -f $file ]; then
            echo "$1 `md5sum $file`"
        elif [ -d $file ]; then
            get_md5 $1/$file
        fi
    done
}

for directory in $DIRECTORYS; do
    get_md5 $directory
done
