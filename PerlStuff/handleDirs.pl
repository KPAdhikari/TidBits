#!/usr/bin/perl
###!/usr/local/bin/perl

#Ref: https://www.guru99.com/perl-tutorials.html

use strict;

#opendir(DIR,"C:\\Program Files\\"); #DIR is the directory handler.
opendir(DIR,"."); #DIR is the directory handler. #worked in linux terminal

while(readdir(DIR)) # loop through the output of readdir to print the directory contents.
{
    print "$_\n";
}
closedir(DIR); #used to close the directory handler.

#or
print "##################\n From Alternative block of code. ##################\n";
#opendir(DIR,"C:\\Program Files\\");
#opendir(DIR,"."); #DIR is the directory handler.
opendir(DIR,"/Users/kpadhikari/GitProj/KPAdhikari/");

my @content=readdir(DIR);
foreach(@content)
{
    print "$_\n";
}
closedir(DIR);
