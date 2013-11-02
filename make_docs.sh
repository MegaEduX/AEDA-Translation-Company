#!/bin/bash

#####
#
#	translation_company
#	
#	This file creates the docs and moves them to the root of the project.
#
#####

rm -rf docs

cd translation_company

doxygen Doxyfile

mkdir docs

mv latex docs/
mv html docs/

mv docs ../docs

ln -s html/index.html ../docs/index.html
