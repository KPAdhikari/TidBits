#!/usr/bin/perl
###!/usr/local/bin/perl

#Ref: https://www.guru99.com/perl-tutorials.html

use strict;

#Subroutines are similar to functions in other programming languages. We have already used some built-in functions like print, chomp, chop, etc. We can write our own subroutines in Perl. These subroutines can be written anywhere in the program; it is preferable to place the subroutines either at the beginning or at the end of the code.
#
#   Subroutines Example
#         sub subroutine_name
#     {
#          Statements…;    # this is how typical subroutines look like.
#     }
#

sub display
{
    my $var=@_; # @_ is a special array variable which stores the list of arguments passed.
    print "$var is the value passed\n"; #Prints the # of arguments passed
    #my @$arVar=@_;
    my $var1 = $_[2]; #3rd element of the argument array
    print "$var1 is the values passed\n";
    my $var2 = shift; #kp: this gives the 0th element of @_
    my $var3 = shift; #kp: this gives the 1st element of @_
    my $var4 = shift; #kp: this gives the 2nd element of @_
    print "$var2 is passed\n";
    print "$var2, $var3, and $var4 are passed\n";
}

#Now that, we know how to write a subroutine, how do we access it?
#We need to access or call a subroutine using the subroutine name prefixed with '&' symbol.
#kp: It seems, & is not essential.
#
&display(2,3,4);   #works
display(2,3,4);    #this is how we need to pass the arguments.
display(5);
display("kp","bp");

####
#### We can return a value from subroutine using the return keyword.
sub add
{
    my $a=shift;
    my $b=shift;
    return($a+$b);
}
my $result=add(5,6);
print "add(a,b) result: $result\n";

# $result will be holding the value of the $a and $b added.

####
####We can also pass hashes and array directly to the subroutine.
sub hash
{
    my %hash=@_;
    print %hash;
}
my %value= ( 1=>'a', 2=>'b');
&hash(%value);
print "\n";


######
## We can also return a hash or an array.
sub hashArray
{
    my %hash=@_;
    print "Inside Sub-routine\n";
    print %hash;
    return(%hash);
}
my %hash=(1=>'a', 2=>'b');
my(@ret)=hashArray(%hash);
print "After Sub-routine call\n";
print @ret;
print "\n";
