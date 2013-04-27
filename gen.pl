#!/usr/bin/perl -w 

my @files = <./*.webm>;

foreach(@files)
{
	print $_ . "\n";
}
