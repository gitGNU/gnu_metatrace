#!/bin/bash
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Copyright (C) 2009  Sebastian Mach (*1983)
# * mail: phresnel/at/gmail/dot/com
# * http:#phresnel.org
# * http:#picogen.org
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http:#www.gnu.org/licenses/>.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

mkdir -p supertrace

TOTAL_WIDTH=128
TOTAL_HEIGHT=128

TILE_WIDTH=5
TILE_HEIGHT=1

if [ ${1} = "join" ] ; then
        do_join="yes"
        render="no"
elif [ $1 = "multi" ] ; then 
        do_join="no"
        render="yes"
        y_start=$2
        n_th=$3
else
        do_join="yes"
        render="yes"
        y_start=0
        n_th=1
fi;



if [ $render = "yes" ] ; then
        for ((y=$y_start; y<TOTAL_HEIGHT; y+=((TILE_HEIGHT*$n_th)) )); do
                for ((x=0; x<TOTAL_WIDTH; x+=TILE_WIDTH)); do
                        mkdir -p supertrace/$y/
                        binname=$x.$y.out
                        g++-4.4 -o $binname -std=c++0x -ftemplate-depth-10000  \
                            -DTOTAL_WIDTH=$TOTAL_WIDTH   \
                            -DTOTAL_HEIGHT=$TOTAL_HEIGHT \
                            -DTILE_WIDTH=$TILE_WIDTH     \
                            -DTILE_HEIGHT=$TILE_HEIGHT   \
                            -DTOTAL_X=$x -DTOTAL_Y=$y    \
                        src/main.cc && ./$binname > supertrace/$y/$x.ppm
                        rm $binname
                done;
                pushd supertrace/$y/
                convert +append $(ls *.ppm | sort -n) ../$y.ppm
                popd
        done;
fi;
if [ $do_join = "yes" ] ; then
        echo "joining..."
        pushd supertrace
        convert -append $(ls *.ppm | sort -n) final.ppm
        popd
fi;
