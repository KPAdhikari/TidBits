#!/usr/bin/perl
###!/usr/local/bin/perl

#Ref: https://www.guru99.com/perl-tutorials.html

use strict;

#print "\$ENV{PATH} = $ENV{PATH}\n";

#my $narg = scalar @ARGV;
#print "N-args = scalar \@ARGV = $narg\n";
#print "Please remember that ARGV doesn't include the filename unlike in C/C++ etc.\n";


#https://github.com/KPAdhikari/Gemc/blob/main/develKA/detectors/clas12/rtpc/rtpc.pl
print " https://stackoverflow.com/questions/1161624/in-perl-what-is-the-difference-between-use-and-require-for-loading-a-module\n";
print "   'use ModuleName' is equivalent to 'BEGIN { require Module; Module->import( LIST ); }'\n";
print "  use runs at compile time, and require runs at run time. (Don't forget the calling of import.)\n";
print " I think, when we call require on a module, it loads all the functions in \n";
print "     it, to make it ready for calling later on. But, if there are lines \n";
print "     such as print lines or some calculations outside of the functions or \n";
print "     subroutines, then these lines will be executed right away too. That's why \n";
print "     all the print lines from someKpTests.pl are executed below right away.\n\n";


print "############ Now calling 'require' on './someKpTests.pl'. ############\n\n";

require "./someKpTests.pl";
