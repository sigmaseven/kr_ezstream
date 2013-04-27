#!/usr/bin/perl -w 

my @dirs = </home/sigma/kradradio/lib/*>;

foreach(@dirs)
{
	print "-I$_ ";
}
