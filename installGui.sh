#!/bin/sh -e
##
## EPITECH PROJECT, 2018
## cpp_plazza
## File description:
## install
##

INSTALL_DIR="Gui/"

cd $INSTALL_DIR
pwd
qmake
make -j 4

mv PlazzaGui ../
