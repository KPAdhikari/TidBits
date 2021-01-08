#!/usr/bin/perl
###!/usr/local/bin/perl
#Ref: https://www.guru99.com/perl-tutorials.html

use strict;

#The substitution operator can be used for searching and replacing any character with either null or some other character.

my $a="Hello how are you";
$a=~s/hello/cello/gi;
print $a;
print "\n";

#The Translation operation is similar to Substitution, but it does not use any perl regular expressions, rather we can directly pass the value or a word which we want to replace.

my $b="Hello how are you\n";
$b=~tr/hello/cello/;
print $b;
