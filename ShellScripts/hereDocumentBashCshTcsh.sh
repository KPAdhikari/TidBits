#!/bin/csh
##!/bin/bash
# Works with bash and csh & tcsh

cat > fileFromHereDocumentTest.txt <<EOF
data to be put in 'here-document' testtestfile
EOF

	set i=5
	set evtsperfile=3000
	set thou=`expr $evtsperfile / 1000`
	set sthou=`printf "%02s\n" "$thou"`

foreach k (`seq -w 0 "$i"`)
		set si=`printf "%02s\n" "$k"`
		set fname=rgf_spring2020_lund_${sthou}kEvs_Fl$si.gcard
		#echo "$k"_"$si".txt;
		echo "$fname";

		cat > fileFromHereDocumentTest"$si".txt <<EOF
			data to be put in 'here-document' testtestfile
		EOF
end
