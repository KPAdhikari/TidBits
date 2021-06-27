#!/bin/tcsh -f
#!/bin/csh -f
#
# Say hello
#


foreach name ( $argv )
   echo Saying hello to $name
   #echo "e2h out_ep_34118_20rot3_02kEvs_Fl00v2.evio"
   echo "e2h out_ep_34118_20rot${name}_02kEvs_Fl00v2.evio"
   echo "Hello from $user! " | write $name
end


echo The $0 command is called with $#argv parameters
echo   parameter 1 is $1
echo   parameter 2 is $2
echo   parameter 3 is $3
echo   parameter 4 is $4
echo 2nd and on parameters are \"$argv[2-]\" 

#!/bin/csh
# demoloop.csh - Sample loop script
set j = 1
while ( $j <= 5 )
   echo "Welcome $j times"
   @ j++
end
