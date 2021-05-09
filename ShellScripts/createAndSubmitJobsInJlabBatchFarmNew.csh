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
	set fname=jpt.gcard

	#foreach i (`seq -w 0 10`) #works
	foreach k (`seq -w 0 "$i"`)
		set si=`printf "%02s\n" "$k"`
		set fname=rgf_spring2020_lund_${sthou}kEvs_Fl$si.gcard
		#echo "$k"_"$si".txt;
		echo "$fname";
		cat <<EOF > kpFiles"$k"_"$si".txt;
			kp bp cp
		EOF
   end


	#Make a script that runs 5 executables in chain: read_map_Linux, steg_Linux, gsim, gpp and user_ana.
	#cat <<END > rgf_spring2020_lund_09kEvs_Fl$jobNum.gcard
	cat <<EOF > $fname

	<gcard>
	<!-- target. Notice variation give the target type. Can be: lH2, lD2, ND3 -->
	<detector name="detectors/clas12/targets/target" factory="TEXT" variation="bonus"/>111

	<!-- central detectors 	-->
	<detector name="detectors/clas12/rtpc/rtpc"             factory="TEXT" variation="original"/>
	<detector name="detectors/clas12/micromegas/micromegas" factory="TEXT" variation="rgf_spring2020"/>

	<option name="INTEGRATEDRAW" value="rtpc"/>

	<!--ctof, cad  -->
	<detector name="detectors/clas12/ctof/ctof"                   factory="TEXT" variation="rga_fall2018"/>
	<detector name="detectors/clas12/ctof/javacad_rga_fall2018/"  factory="CAD"/>
	<detector name="detectors/clas12/cnd/cnd"                     factory="TEXT" variation="original"/>

	<!--high threshold cherenkov -->
	<detector name="detectors/clas12/htcc/htcc"      factory="TEXT" variation="original"/>

	<!-- magnets -->
	<detector name="detectors/clas12/magnets/solenoid" factory="TEXT" variation="original"/>
	<detector name="detectors/clas12/magnets/cad/"     factory="CAD" />


	<!-- Beamline configuration: FT is used -->
	<detector name="detectors/clas12/ft/ft"                 factory="TEXT" variation="FTOff"/>
    	<detector name="detectors/clas12/beamline/cadBeamlineFTOFF/" factory="CAD"/>
    	<detector name="detectors/clas12/beamline/vacuumLine/"  factory="CAD"/>
    	<detector name="detectors/clas12/beamline/beamline"     factory="TEXT" variation="FTOff"/>

	<!-- forward carriage -->
	<detector name="detectors/clas12/fc/forwardCarriage" factory="TEXT" variation="TorusSymmetric"/>

	<detector name="detectors/clas12/dc/dc"              factory="TEXT" variation="default"/>
	<detector name="detectors/clas12/ftof/ftof"          factory="TEXT" variation="rga_fall2018"/>
	<detector name="detectors/clas12/ec/ec"              factory="TEXT" variation="rga_fall2018"/>
	<detector name="detectors/clas12/pcal/pcal"          factory="TEXT" variation="rga_fall2018"/>
	<detector name="detectors/clas12/ltcc/ltcc"          factory="TEXT" variation="rgb_spring2019"/>
	<detector name="detectors/clas12/ltcc/cad_cone/"     factory="CAD"/>
	<detector name="detectors/clas12/ltcc/cad/"          factory="CAD"/>


	<!-- you can scale the fields here. Remember torus -1 means e- INBENDING  -->
	<option name="SCALE_FIELD" value="TorusSymmetric, -1"/>
	<option name="SCALE_FIELD" value="clas12-newSolenoid, -0.756"/>

	<!-- hall field  -->
	<option name="HALL_FIELD"  value="clas12-newSolenoid"/>

	<!-- fields, precise mode -->
	<option name="FIELD_PROPERTIES" value="TorusSymmetric,     2*mm, G4ClassicalRK4, linear"/>
	<option name="FIELD_PROPERTIES" value="clas12-newSolenoid, 1*mm, G4ClassicalRK4, linear"/>


	<option name="SAVE_ALL_MOTHERS" value="1"/>
	<option name="RECORD_OPTICALPHOTONS"   value="1"/>

	<option name="PHYSICS" value="FTFP_BERT + STD + Optical"/>

	<option name="OUTPUT"   value="evio, out_ep_34118_20_9kEvs_Fl01.evio"/>

	<option name="INPUT_GEN_FILE" value="LUND, lund/ep_34118_20_ev09k_file01.lund"/>

	<!--  Will print message every 10 events -->
	<option name="PRINT_EVENT"    value="100" />


	<!--  Run Number 11, picked up by digitization routines -->
	<!-- Bradley Y. Email 1/28/21:  The v59.2 parameters have been set for run 10. -->
 	<!--              Previously, we thought that simulated runs were tagged '11'. -->
	<!-- <option name="RUNNO"    value="11" /> -->
        <option name="RUNNO"    value="10" />
	<!-- <option name="DIGITIZATION_VARIATION"  value="rgf_spring2020" /> -->
	<option name="DIGITIZATION_VARIATION"  value="default" />

	<!--  Do not track staff after the apex -->
	<option name="MAX_Z_POS" value="8000"/>

	<!--  RF Signal needs event time window defined by LUMI_EVENT -->
	<option name="LUMI_EVENT"  value="0, 248.5*ns, 4*ns" />
	<option name="RFSETUP"     value="0.499, 40, 20" />

	<!--  Reference position set as target shift below -->
	<option name="RFSTART"     value="eventVertex, 0, 0, -30.0" />

	<!-- production threshold for passive volumes -->
	<!-- beamline shielding: 2cm-->
	<option name="PRODUCTIONCUTFORVOLUMES" value="innerShieldAndFlange, outerFlange, outerMount, nut1, nut2, nut3, nut4, nut5, nut6, nut7, nut8, nut9, taggerInnerShield,
 main-cone, main-cone, adjuster1, adjuster2, adjuster3, DSShieldFrontLead, DSShieldBackLead, DSShieldInnerAss, DSShieldBackAss, DSShieldFrontAss, DSShieldBackCover, DSShieldF
	rontCover, DSShieldFlangeAttachment, DSShieldFlange,  20" />

	<!-- vacuum line: 2cm-->
	<option name="PRODUCTIONCUTFORVOLUMES" value="connectUpstreamToTorusPipe, connectTorusToDownstreamPipe, downstreamPipeFlange,  20" />

	<!-- torus magnet: 2cm-->
	<option name="PRODUCTIONCUTFORVOLUMES" value="BoreShield, CenterTube, DownstreamShieldingPlate, DownstreamVacuumJacket, WarmBoreTube, apex, Shield1, Shield2, Shield3,
 Shield4, Shield5, Shield6, Shield7, shell1a, shell1b, shell2a, shell2b, shell3a, shell3b, shell4a, shell4b, shell5a, shell5b, shell6a, shell6b, 20" />

	<!--  Target and central detectors are all shifted upstream by 30 mm -->
	<detector name="target">    <position x="0.12*cm"  y="0.11*cm"  z="-3.00*cm"  />  </detector>
	<detector name="svt">       <position x="0*cm"     y="0*cm"     z="-3.00*cm"  />  </detector>
	<detector name="bstShield"> <position x="0*cm"     y="0*cm"     z="-3.00*cm"  />  </detector>
	<detector name="BMT">       <position x="0*cm"     y="0*cm"     z="-3.00*cm"  />  </detector>
	<!--  notice no shift of MM as its geometry its already centered at -3 cm -->
	<detector name="FMT">       <position x="0*cm"     y="0*cm"     z="0.00*cm"  />  </detector>
	<detector name="ctof">      <position x="0*cm"     y="0*cm"     z="-3.00*cm"  />  </detector>
	<detector name="cnd">       <position x="0*cm"     y="0*cm"     z="-3.00*cm"  />  </detector>

	<!-- solenoid volume and field map shifted upstream by 20 mm -->
	<detector name="solenoid">  <position x="0*cm"  y="0*cm"  z="-3.00*cm"  />  </detector>
	<option name="DISPLACE_FIELDMAP"     value="clas12-newSolenoid, 0*cm, 0*cm, -3.00*cm" />

	<!--  HTCC shifted upstream by 20 mm -->
	<detector name="htccBigGasVolume">     <position x="0*cm"  y="0*cm"  z="-1.94*cm"  />  </detector>
	<detector name="htccEntryDishVolume">  <position x="0*cm"  y="0*cm"  z="-1.94*cm"  />  </detector>
	<detector name="htccEntryConeVolume">  <position x="0*cm"  y="0*cm"  z="-1.94*cm"  />  </detector>
	<detector name="htccEntryDishCone">    <position x="0*cm"  y="0*cm"  z="-1.94*cm"  />  </detector>
	<detector name="htcc">                 <position x="0*cm"  y="0*cm"  z="-1.94*cm"  />  </detector>

	<!--kp <option name="USE_GUI" value="1"/> -->
	<option name="USE_GUI" value="0"/>

	<!-- MAX is 34118 -->
	<option name="N" value="${evtsperfile}"/>



	</gcard>

	EOF

	#Above end pairs with the one after 'cat <<END' above, thus, it doesn't show up in the output file.

	#end
	#This 'end' pairs with the one for the 'foreach' loop.



	#chmod u+x job_launchGSIMgppRecsis_.csh
	#jsub job_sub_batch
