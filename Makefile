clean:
	rm *.o

all:
	gcc -c src/playlist.c
	gcc -c src/splice.c `perl includes.pl` -DKR_LINUX
	gcc -c src/main.c `perl includes.pl` -DKR_LINUX

	gcc -o kr_ezstream *.o -lkrad_mkv -lrt
