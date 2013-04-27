clean:
	rm *.o

all:
	gcc -c playlist.c
	gcc -c splice.c `perl includes.pl` -DKR_LINUX
	gcc -c main.c `perl includes.pl` -DKR_LINUX

	gcc -o kr_ezstream *.o -lkrad_mkv
