cc=gcc
CC=g++
obj=./obj/
src=./src/
OBJ=2220202929_mysh

all: clean create cat cp help ipconfig list mkdir more ps pstree pwd rm rmdir touch tty wc echo

shell:
	$(CC) -o $(OBJ) shell.cpp

cat:
	$(cc) -o $(obj)cat $(src)cat.c
cp:
	$(cc) -o $(obj)cp $(src)cp.c
help:
	$(CC) -o $(obj)man $(src)help.cpp
ipconfig:
	$(CC) -o $(obj)ipconfig $(src)ipconfig.cpp
list:
	$(CC) -o $(obj)ls $(src)list.cpp
mkdir:
	$(cc) -o $(obj)mkdir $(src)mkdir.c
more:
	$(CC) -o $(obj)more $(src)more.cpp
# ping:
# 	$(cc) -o $(obj)ping $(src)ping.cpp
ps:
	$(CC) -o $(obj)ps $(src)ps.cpp
pstree:
	$(CC) -o $(obj)pstree $(src)pstree.cpp
pwd:
	$(CC) -o $(obj)pwd $(src)pwd.cpp
rm:
	$(cc) -o $(obj)rm $(src)rm.c
rmdir:
	$(cc) -o $(obj)rmdir $(src)rmdir.c
touch:
	$(cc) -o $(obj)touch $(src)touch.c
tty:
	$(CC) -o $(obj)tty $(src)tty.cpp
wc:
	$(cc) -o $(obj)wc $(src)wc.c
echo:
	$(cc) -o $(obj)echo $(src)echo.c

clean:
	rm -rf obj 
	echo 'clean success!'

create:
	mkdir obj 

clean2:
	rm $(OBJ)