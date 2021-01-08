#!/usr/bin/perl
###!/usr/local/bin/perl
#Ref: https://www.guru99.com/perl-tutorials.html
######## Scope of a variable – Access Modifiers #######
# We can declare a scalar anywhere in the program. But you need to specify an access modifier
# There are 3 types of modifiers
#   1)  my
#   2)  local
#   3)  our

######### My: ############
# Using 'my' you can declare any variable which is specific within the block. i.e. within the curly braces.

my $var=5;
if(1)
{
    my $var_2 =$var;
}
print $var_2; #No output

#The variable, which is declared outside the block will be accessible to if-block but the variable which was declared inside if-block won't be accessible to the outer program.

############# Local: ############
#Using this we can actually mask the same variable values to different values without actually changing the original value of the variable.

#$var = 5; #kp: to avoid "Can't localize lexical variable" error, I renamed var as var3
$var3 = 5;
{
    local $var3 = 3; #kp: Initially, this line was at L27 and gave the following error
    ##kp: Can't localize lexical variable $var at ./modifiers_my_local_our.pl line 27.
    print "local,\$var3 = $var3 \n";
}
print "global,\$var3 = $var3 \n";

# The output of the above program will be in this manner.
#      local, $var = 3
#      global, $var = 5
# This way we can change the value of the variable without affecting the original value.

############# Our: ############
# Once a variable is declared with access modifier "our", it can be used across the entire package. Suppose, you have Perl module or a package ‘test.pm’ which has a variable declared with scope ‘our’. This variable can be accessed in any scripts which will use that package.


#============ Scope of Variables =======
#Refs: https://www.geeksforgeeks.org/perl-scope-of-variables/
# The scope of a variable is the part of the program where the variable is accessible. A scope is also termed as the visibility of the variables in a program. In Perl, we can declare either Global variables or Private variables. Private variables are also known as lexical variables.
