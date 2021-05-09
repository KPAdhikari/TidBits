#!/bin/tcsh -f



set i=5
set si=`printf "%02s\n" "$i"`
echo "${si}"

echo "Setting name servers...."
foreach j ( ns1.cyberciti.biz ns2.cyberciti.biz  )
echo $j
end


#foreach i (`seq -w 0 10`) #works
foreach k (`seq -w 0 "$i"`)
	set si=`printf "%02s\n" "$k"`
	echo "$k"_"$si".txt;
end

#################################
#	KPAd's FunPrompt $ which seq
#	/usr/bin/seq
#	KPAd's FunPrompt $ whatis seq
#	seq(1)                   - print sequences of numbers
#	KPAd's FunPrompt $ seq -w 0 3
#	0
#	1
#	2
#	3
#	KPAd's FunPrompt $
#################################


	set i=5
	set evtsperfile=3000
	set thou=`expr $evtsperfile / 1000`
	set sthou=`printf "%02s\n" "$thou"`

	#foreach i (`seq -w 0 10`) #works
	foreach k (`seq -w 0 "$i"`)
		set si=`printf "%02s\n" "$k"`
		set fname=rgf_spring2020_lund_${sthou}kEvs_Fl$si.gcard
		#echo "$k"_"$si".txt;
		echo "$fname";
	end
