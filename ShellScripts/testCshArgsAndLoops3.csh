#!/bin/tcsh -f
#!/bin/csh -f

echo The $0 command is called with $#argv parameters
set Nargs = $#argv


echo   parameter 1 is $1
echo   parameter 2 is $2
echo   parameter 3 is $3
echo   parameter 4 is $4
echo 1st and on parameters are \"$argv[1-]\" 
echo 2nd and on parameters are \"$argv[2-]\" 

#!/bin/csh
# demoloop.csh - Sample loop script
set j = 1
#while ( $j <= 5 )
while ( $j <= ${Nargs} )
   echo "Welcome $j times"
   echo "parameter $j is " \"$argv[$j]\" 
   @ j++
end

set k = 1
set value = ""
while ($k <= $argv[2])
    echo "this loop is on ${k}th iteration "
    #value=$(printf "%02d" $k) #works with bash?
    if ($argv[1] > 0) then
	echo "e2h out_ep_34118_20rot${argv[1]}_02kEvs_Fl00v2.evio"
    else
	echo "e2h out_ep_34118_20_02kEvs_Fl00v2.evio"
    endif
    @ k++
end


#for i in $(seq -w 0 20); do 
#    echo "$i".txt; 
#done

foreach x (`seq 1 5 20`)
     echo $x
end

foreach x (`seq -w 0 20`)
     echo $x
end
echo ""

#set k = 1
foreach x (`seq -w 0 $argv[2]`)
     echo $x
    if ($argv[1] > 0) then
	echo "e2h out_ep_34118_20rot${argv[1]}_02kEvs_Fl${x}v2.evio"
    else
	echo "e2h out_ep_34118_20_02kEvs_Fl${x}v2.evio"
    endif
end
