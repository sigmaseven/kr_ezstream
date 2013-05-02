#!/usr/bin/perl -w 

my @dirs = </home/sigma/krad_radio/lib/*>;

foreach(@dirs)
{
	print "-I$_ ";
}
