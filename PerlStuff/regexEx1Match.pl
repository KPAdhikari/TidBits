#!/usr/bin/perl
###!/usr/local/bin/perl
#Ref: https://www.guru99.com/perl-tutorials.html

use strict;

my $userinput="Guru99 Rocks";
if($userinput=~m/.*(Guru99).*/)
{
    print "Found Pattern\n";
}
else
{
    print "unable to find the pattern\n";
}


my $var="Hello this is perl";
if($var=~m/perl/)
{
    print "true\n";
}
else
{
    print "False\n";
}

### We can try replacing =~ with !~ to see the difference between those two operators.

if($var !~m/perl/)
{
    print "true\n";
}
else
{
    print "False\n";
}
