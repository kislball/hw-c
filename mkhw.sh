#!/bin/sh

if [[ -n $1 ]]; then
	mkdir -p hws/$1
	cp ./Makefile.tmpl ./hws/$1/Makefile
	cp ./template.c ./hws/$1/main.c
else
	echo "Укажите название ДЗ"
fi
