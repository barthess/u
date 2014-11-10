<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="5" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="6" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="3" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="tplace-old" color="10" fill="1" visible="yes" active="yes"/>
<layer number="109" name="ref-old" color="11" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="no" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="no" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="no" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="barthess">
<packages>
<package name="PLD_2X10_PSEUDOSMD">
<wire x1="11.26" y1="16.5" x2="2.26" y2="16.5" width="0.127" layer="51"/>
<wire x1="2.26" y1="16.5" x2="2.26" y2="-16.5" width="0.127" layer="51"/>
<wire x1="2.26" y1="-16.5" x2="11.26" y2="-16.5" width="0.127" layer="51"/>
<wire x1="11.26" y1="-16.5" x2="11.26" y2="-2.365" width="0.127" layer="51"/>
<wire x1="11.26" y1="-2.365" x2="11.26" y2="16.5" width="0.127" layer="51"/>
<wire x1="11.16" y1="2.365" x2="3.76" y2="2.365" width="0.127" layer="51"/>
<wire x1="3.76" y1="2.365" x2="3.76" y2="-2.365" width="0.127" layer="51"/>
<wire x1="3.76" y1="-2.365" x2="11.26" y2="-2.365" width="0.127" layer="51"/>
<circle x="-2.885" y="11.585" radius="0.449" width="0.254" layer="21"/>
<smd name="1" x="0" y="11.43" dx="4" dy="2" layer="1"/>
<smd name="2" x="0" y="11.43" dx="4" dy="2" layer="16"/>
<smd name="3" x="0" y="8.89" dx="4" dy="2" layer="1"/>
<smd name="4" x="0" y="8.89" dx="4" dy="2" layer="16"/>
<smd name="5" x="0" y="6.35" dx="4" dy="2" layer="1"/>
<smd name="6" x="0" y="6.35" dx="4" dy="2" layer="16"/>
<smd name="7" x="0" y="3.81" dx="4" dy="2" layer="1"/>
<smd name="8" x="0" y="3.81" dx="4" dy="2" layer="16"/>
<smd name="9" x="0" y="1.27" dx="4" dy="2" layer="1"/>
<smd name="10" x="0" y="1.27" dx="4" dy="2" layer="16"/>
<smd name="11" x="0" y="-1.27" dx="4" dy="2" layer="1"/>
<smd name="12" x="0" y="-1.27" dx="4" dy="2" layer="16"/>
<smd name="13" x="0" y="-3.81" dx="4" dy="2" layer="1"/>
<smd name="14" x="0" y="-3.81" dx="4" dy="2" layer="16"/>
<smd name="15" x="0" y="-6.35" dx="4" dy="2" layer="1"/>
<smd name="16" x="0" y="-6.35" dx="4" dy="2" layer="16"/>
<smd name="17" x="0" y="-8.89" dx="4" dy="2" layer="1"/>
<smd name="18" x="0" y="-8.89" dx="4" dy="2" layer="16"/>
<smd name="19" x="0" y="-11.43" dx="4" dy="2" layer="1"/>
<smd name="20" x="0" y="-11.43" dx="4" dy="2" layer="16"/>
<text x="-1.451" y="16.194" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<text x="-1.451" y="-15.302" size="0.4064" layer="104">&gt;NAME</text>
<rectangle x1="-1.27" y1="11.1125" x2="8.255" y2="11.7475" layer="51"/>
<rectangle x1="-1.27" y1="8.5725" x2="8.255" y2="9.2075" layer="51"/>
<rectangle x1="-1.27" y1="6.0325" x2="8.255" y2="6.6675" layer="51"/>
<rectangle x1="-1.27" y1="3.4925" x2="8.255" y2="4.1275" layer="51"/>
<rectangle x1="-1.27" y1="0.9525" x2="8.255" y2="1.5875" layer="51"/>
<rectangle x1="-1.27" y1="-1.5875" x2="8.255" y2="-0.9525" layer="51"/>
<rectangle x1="-1.27" y1="-4.1275" x2="8.255" y2="-3.4925" layer="51"/>
<rectangle x1="-1.27" y1="-6.6675" x2="8.255" y2="-6.0325" layer="51"/>
<rectangle x1="-1.27" y1="-9.2075" x2="8.255" y2="-8.5725" layer="51"/>
<rectangle x1="-1.27" y1="-11.7475" x2="8.255" y2="-11.1125" layer="51"/>
</package>
<package name="PLD_2X05_PSEUDOSMD">
<wire x1="11.26" y1="10.15" x2="2.26" y2="10.15" width="0.127" layer="51"/>
<wire x1="2.26" y1="10.15" x2="2.26" y2="-10.15" width="0.127" layer="51"/>
<wire x1="2.26" y1="-10.15" x2="11.26" y2="-10.15" width="0.127" layer="51"/>
<wire x1="11.26" y1="-10.15" x2="11.26" y2="-1.984" width="0.127" layer="51"/>
<wire x1="11.26" y1="-1.984" x2="11.26" y2="10.15" width="0.127" layer="51"/>
<wire x1="11.16" y1="1.984" x2="3.76" y2="1.984" width="0.127" layer="51"/>
<wire x1="3.76" y1="1.984" x2="3.76" y2="-1.984" width="0.127" layer="51"/>
<wire x1="3.76" y1="-1.984" x2="11.26" y2="-1.984" width="0.127" layer="51"/>
<circle x="-3.175" y="5.08" radius="0.449" width="0.254" layer="21"/>
<smd name="1" x="0" y="5.08" dx="4" dy="2" layer="1"/>
<smd name="2" x="0" y="5.08" dx="4" dy="2" layer="16"/>
<smd name="3" x="0" y="2.54" dx="4" dy="2" layer="1"/>
<smd name="4" x="0" y="2.54" dx="4" dy="2" layer="16"/>
<smd name="5" x="0" y="0" dx="4" dy="2" layer="1"/>
<smd name="6" x="0" y="0" dx="4" dy="2" layer="16"/>
<smd name="7" x="0" y="-2.54" dx="4" dy="2" layer="1"/>
<smd name="8" x="0" y="-2.54" dx="4" dy="2" layer="16"/>
<smd name="9" x="0" y="-5.08" dx="4" dy="2" layer="1"/>
<smd name="10" x="0" y="-5.08" dx="4" dy="2" layer="16"/>
<text x="-1.451" y="8.574" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<text x="-1.451" y="-7.682" size="0.4064" layer="25">&gt;NAME</text>
<rectangle x1="-1.27" y1="4.7625" x2="8.255" y2="5.3975" layer="51"/>
<rectangle x1="-1.27" y1="2.2225" x2="8.255" y2="2.8575" layer="51"/>
<rectangle x1="-1.27" y1="-0.3175" x2="8.255" y2="0.3175" layer="51"/>
<rectangle x1="-1.27" y1="-2.8575" x2="8.255" y2="-2.2225" layer="51"/>
<rectangle x1="-1.27" y1="-5.3975" x2="8.255" y2="-4.7625" layer="51"/>
</package>
<package name="BUTTON_6X3.5">
<wire x1="0" y1="0" x2="6" y2="0" width="0.2032" layer="21"/>
<wire x1="6" y1="-3.5" x2="0" y2="-3.5" width="0.2032" layer="21"/>
<wire x1="1" y1="-2" x2="2" y2="-2" width="0.127" layer="51"/>
<wire x1="2" y1="-2" x2="3" y2="-1" width="0.127" layer="51"/>
<wire x1="3" y1="-2" x2="4.75" y2="-2" width="0.127" layer="51"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.005" y1="-2.85" x2="-0.005" y2="-3.485" width="0.2032" layer="21"/>
<wire x1="6.01" y1="-2.85" x2="6.01" y2="-3.485" width="0.2032" layer="21"/>
<wire x1="6.01" y1="0" x2="6.01" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-3.5" width="0.127" layer="51"/>
<wire x1="0" y1="-3.5" x2="6.025" y2="-3.5" width="0.127" layer="51"/>
<wire x1="6.025" y1="-3.5" x2="6.025" y2="0" width="0.127" layer="51"/>
<wire x1="6.025" y1="0" x2="0" y2="0" width="0.127" layer="51"/>
<smd name="P" x="0" y="-1.75" dx="1.5" dy="1.5" layer="1"/>
<smd name="S" x="6" y="-1.75" dx="1.5" dy="1.5" layer="1"/>
<text x="0" y="0.5" size="1.27" layer="25">&gt;NAME</text>
<text x="0" y="-5.25" size="1.27" layer="25">&gt;VALUE</text>
<rectangle x1="-0.325" y1="-2.5" x2="0.625" y2="-1" layer="51"/>
<rectangle x1="5.375" y1="-2.5" x2="6.375" y2="-1" layer="51"/>
</package>
<package name="PLD_2X10_SHROUDED">
<wire x1="4.5" y1="16.45" x2="4.5" y2="-16.45" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="-16.45" x2="-4.5" y2="-3.47" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="-3.47" x2="-4.5" y2="3.47" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="3.47" x2="-4.5" y2="16.45" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="16.45" x2="4.4" y2="16.45" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-16.45" x2="-4.5" y2="-16.45" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="3.47" x2="-3" y2="3.47" width="0.2032" layer="21"/>
<wire x1="-3" y1="3.47" x2="-3" y2="-3.47" width="0.2032" layer="21"/>
<wire x1="-3" y1="-3.47" x2="-4.5" y2="-3.47" width="0.2032" layer="21"/>
<pad name="1" x="-1.27" y="11.43" drill="1.016" diameter="1.8796" shape="square" rot="R270"/>
<pad name="2" x="1.27" y="11.43" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="3" x="-1.27" y="8.89" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="4" x="1.27" y="8.89" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="5" x="-1.27" y="6.35" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="6" x="1.27" y="6.35" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="7" x="-1.27" y="3.81" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="8" x="1.27" y="3.81" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="9" x="-1.27" y="1.27" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="10" x="1.27" y="1.27" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="11" x="-1.27" y="-1.27" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="12" x="1.27" y="-1.27" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="13" x="-1.27" y="-3.81" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="14" x="1.27" y="-3.81" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="15" x="-1.27" y="-6.35" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="16" x="1.27" y="-6.35" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="17" x="-1.27" y="-8.89" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="18" x="1.27" y="-8.89" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="19" x="-1.27" y="-11.43" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="20" x="1.27" y="-11.43" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<text x="-2.921" y="16.764" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<text x="-2.921" y="-17.272" size="0.4064" layer="104">&gt;NAME</text>
<rectangle x1="-1.524" y1="11.176" x2="-1.016" y2="11.684" layer="51"/>
<rectangle x1="1.016" y1="11.176" x2="1.524" y2="11.684" layer="51"/>
<rectangle x1="1.016" y1="8.636" x2="1.524" y2="9.144" layer="51"/>
<rectangle x1="-1.524" y1="8.636" x2="-1.016" y2="9.144" layer="51"/>
<rectangle x1="1.016" y1="6.096" x2="1.524" y2="6.604" layer="51"/>
<rectangle x1="-1.524" y1="6.096" x2="-1.016" y2="6.604" layer="51"/>
<rectangle x1="1.016" y1="3.556" x2="1.524" y2="4.064" layer="51"/>
<rectangle x1="-1.524" y1="3.556" x2="-1.016" y2="4.064" layer="51"/>
<rectangle x1="1.016" y1="1.016" x2="1.524" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="1.016" x2="-1.016" y2="1.524" layer="51"/>
<rectangle x1="-1.524" y1="3.556" x2="-1.016" y2="4.064" layer="51"/>
<rectangle x1="1.016" y1="3.556" x2="1.524" y2="4.064" layer="51"/>
<rectangle x1="-1.524" y1="-1.524" x2="-1.016" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-1.524" x2="1.524" y2="-1.016" layer="51"/>
<rectangle x1="1.016" y1="-4.064" x2="1.524" y2="-3.556" layer="51"/>
<rectangle x1="-1.524" y1="-4.064" x2="-1.016" y2="-3.556" layer="51"/>
<rectangle x1="1.016" y1="-6.604" x2="1.524" y2="-6.096" layer="51"/>
<rectangle x1="-1.524" y1="-6.604" x2="-1.016" y2="-6.096" layer="51"/>
<rectangle x1="1.016" y1="-9.144" x2="1.524" y2="-8.636" layer="51"/>
<rectangle x1="-1.524" y1="-9.144" x2="-1.016" y2="-8.636" layer="51"/>
<rectangle x1="1.016" y1="-11.684" x2="1.524" y2="-11.176" layer="51"/>
<rectangle x1="-1.524" y1="-11.684" x2="-1.016" y2="-11.176" layer="51"/>
<rectangle x1="-1.524" y1="-9.144" x2="-1.016" y2="-8.636" layer="51"/>
<rectangle x1="1.016" y1="-9.144" x2="1.524" y2="-8.636" layer="51"/>
</package>
<package name="STAND-OFF">
<description>&lt;b&gt;Stand Off&lt;/b&gt;&lt;p&gt;
This is the mechanical footprint for a #4 phillips button head screw. Use the keepout ring to avoid running the screw head into surrounding components. SKU : PRT-00447</description>
<wire x1="0" y1="1.8542" x2="0" y2="-1.8542" width="0.2032" layer="41" curve="-180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="41" curve="-180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="42" curve="180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="42" curve="-180"/>
<circle x="0" y="0" radius="2.794" width="0.127" layer="39"/>
<hole x="0" y="0" drill="3.3"/>
</package>
<package name="STAND-OFF-TIGHT">
<description>&lt;b&gt;Stand Off&lt;/b&gt;&lt;p&gt;
This is the mechanical footprint for a #4 phillips button head screw. Use the keepout ring to avoid running the screw head into surrounding components. SKU : PRT-00447</description>
<wire x1="0" y1="1.8542" x2="0" y2="-1.8542" width="0.2032" layer="41" curve="-180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="41" curve="-180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="42" curve="180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="42" curve="-180"/>
<circle x="0" y="0" radius="2.794" width="0.127" layer="39"/>
<hole x="0" y="0" drill="3.05"/>
</package>
<package name="PLS_2X32_PSEUDOSMD">
<wire x1="3.64" y1="40.63" x2="-1.55" y2="40.63" width="0.127" layer="51"/>
<wire x1="-1.55" y1="40.63" x2="-1.55" y2="-40.63" width="0.127" layer="51"/>
<wire x1="-1.55" y1="-40.63" x2="3.64" y2="-40.63" width="0.127" layer="51"/>
<wire x1="3.64" y1="-40.63" x2="3.64" y2="-2.365" width="0.127" layer="51"/>
<wire x1="3.64" y1="-2.365" x2="3.64" y2="40.63" width="0.127" layer="51"/>
<wire x1="3.54" y1="2.365" x2="-1.32" y2="2.365" width="0.127" layer="51"/>
<wire x1="-1.32" y1="2.365" x2="-1.32" y2="-2.365" width="0.127" layer="51"/>
<wire x1="-1.32" y1="-2.365" x2="3.64" y2="-2.365" width="0.127" layer="51"/>
<circle x="-6.695" y="-40.485" radius="0.449" width="0.254" layer="21"/>
<smd name="1" x="-3.81" y="-39.37" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="2" x="-3.81" y="-39.37" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="3" x="-3.81" y="-36.83" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="4" x="-3.81" y="-36.83" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="5" x="-3.81" y="-34.29" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="6" x="-3.81" y="-34.29" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="7" x="-3.81" y="-31.75" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="8" x="-3.81" y="-31.75" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="9" x="-3.81" y="-29.21" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="10" x="-3.81" y="-29.21" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="11" x="-3.81" y="-26.67" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="12" x="-3.81" y="-26.67" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="13" x="-3.81" y="-24.13" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="14" x="-3.81" y="-24.13" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="15" x="-3.81" y="-21.59" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="16" x="-3.81" y="-21.59" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="17" x="-3.81" y="-19.05" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="18" x="-3.81" y="-19.05" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="19" x="-3.81" y="-16.51" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="20" x="-3.81" y="-16.51" dx="4" dy="2" layer="16" rot="R180"/>
<text x="-5.261" y="41.594" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<text x="-3.991" y="-41.972" size="0.4064" layer="104">&gt;NAME</text>
<rectangle x1="-5.08" y1="-26.9875" x2="1.27" y2="-26.3525" layer="51"/>
<rectangle x1="-5.08" y1="-24.4475" x2="1.27" y2="-23.8125" layer="51"/>
<rectangle x1="-5.08" y1="-21.9075" x2="1.27" y2="-21.2725" layer="51"/>
<rectangle x1="-5.08" y1="-19.3675" x2="1.27" y2="-18.7325" layer="51"/>
<rectangle x1="-5.08" y1="-16.8275" x2="1.27" y2="-16.1925" layer="51"/>
<rectangle x1="-5.08" y1="-29.5275" x2="1.27" y2="-28.8925" layer="51"/>
<rectangle x1="-5.08" y1="-32.0675" x2="1.27" y2="-31.4325" layer="51"/>
<rectangle x1="-5.08" y1="-34.6075" x2="1.27" y2="-33.9725" layer="51"/>
<rectangle x1="-5.08" y1="-37.1475" x2="1.27" y2="-36.5125" layer="51"/>
<rectangle x1="-5.08" y1="-39.6875" x2="1.27" y2="-39.0525" layer="51"/>
<smd name="21" x="-3.81" y="-13.97" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="22" x="-3.81" y="-13.97" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="23" x="-3.81" y="-11.43" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="24" x="-3.81" y="-11.43" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="25" x="-3.81" y="-8.89" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="26" x="-3.81" y="-8.89" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="27" x="-3.81" y="-6.35" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="28" x="-3.81" y="-6.35" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="29" x="-3.81" y="-3.81" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="30" x="-3.81" y="-3.81" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="31" x="-3.81" y="-1.27" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="32" x="-3.81" y="-1.27" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="33" x="-3.81" y="1.27" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="34" x="-3.81" y="1.27" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="35" x="-3.81" y="3.81" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="36" x="-3.81" y="3.81" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="37" x="-3.81" y="6.35" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="38" x="-3.81" y="6.35" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="39" x="-3.81" y="8.89" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="40" x="-3.81" y="8.89" dx="4" dy="2" layer="16" rot="R180"/>
<rectangle x1="-5.08" y1="-1.5875" x2="1.27" y2="-0.9525" layer="51"/>
<rectangle x1="-5.08" y1="0.9525" x2="1.27" y2="1.5875" layer="51"/>
<rectangle x1="-5.08" y1="3.4925" x2="1.27" y2="4.1275" layer="51"/>
<rectangle x1="-5.08" y1="6.0325" x2="1.27" y2="6.6675" layer="51"/>
<rectangle x1="-5.08" y1="8.5725" x2="1.27" y2="9.2075" layer="51"/>
<rectangle x1="-5.08" y1="-4.1275" x2="1.27" y2="-3.4925" layer="51"/>
<rectangle x1="-5.08" y1="-6.6675" x2="1.27" y2="-6.0325" layer="51"/>
<rectangle x1="-5.08" y1="-9.2075" x2="1.27" y2="-8.5725" layer="51"/>
<rectangle x1="-5.08" y1="-11.7475" x2="1.27" y2="-11.1125" layer="51"/>
<rectangle x1="-5.08" y1="-14.2875" x2="1.27" y2="-13.6525" layer="51"/>
<smd name="41" x="-3.81" y="11.43" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="42" x="-3.81" y="11.43" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="43" x="-3.81" y="13.97" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="44" x="-3.81" y="13.97" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="45" x="-3.81" y="16.51" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="46" x="-3.81" y="16.51" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="47" x="-3.81" y="19.05" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="48" x="-3.81" y="19.05" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="49" x="-3.81" y="21.59" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="50" x="-3.81" y="21.59" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="51" x="-3.81" y="24.13" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="52" x="-3.81" y="24.13" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="53" x="-3.81" y="26.67" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="54" x="-3.81" y="26.67" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="55" x="-3.81" y="29.21" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="56" x="-3.81" y="29.21" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="57" x="-3.81" y="31.75" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="58" x="-3.81" y="31.75" dx="4" dy="2" layer="16" rot="R180"/>
<smd name="59" x="-3.81" y="34.29" dx="4" dy="2" layer="1" rot="R180"/>
<smd name="60" x="-3.81" y="34.29" dx="4" dy="2" layer="16" rot="R180"/>
<rectangle x1="-5.08" y1="23.8125" x2="1.27" y2="24.4475" layer="51"/>
<rectangle x1="-5.08" y1="26.3525" x2="1.27" y2="26.9875" layer="51"/>
<rectangle x1="-5.08" y1="28.8925" x2="1.27" y2="29.5275" layer="51"/>
<rectangle x1="-5.08" y1="31.4325" x2="1.27" y2="32.0675" layer="51"/>
<rectangle x1="-5.08" y1="33.9725" x2="1.27" y2="34.6075" layer="51"/>
<rectangle x1="-5.08" y1="21.2725" x2="1.27" y2="21.9075" layer="51"/>
<rectangle x1="-5.08" y1="18.7325" x2="1.27" y2="19.3675" layer="51"/>
<rectangle x1="-5.08" y1="16.1925" x2="1.27" y2="16.8275" layer="51"/>
<rectangle x1="-5.08" y1="13.6525" x2="1.27" y2="14.2875" layer="51"/>
<rectangle x1="-5.08" y1="11.1125" x2="1.27" y2="11.7475" layer="51"/>
<smd name="61" x="-3.81" y="36.83" dx="4" dy="2" layer="1"/>
<smd name="62" x="-3.81" y="36.83" dx="4" dy="2" layer="16"/>
<smd name="63" x="-3.81" y="39.37" dx="4" dy="2" layer="1"/>
<smd name="64" x="-3.81" y="39.37" dx="4" dy="2" layer="16"/>
<rectangle x1="-5.08" y1="36.5125" x2="1.27" y2="37.1475" layer="51"/>
<rectangle x1="-5.08" y1="39.0525" x2="1.27" y2="39.6875" layer="51"/>
</package>
<package name="TQFP176">
<description>&lt;b&gt;Thin Quad Flat Pack&lt;/b&gt;</description>
<wire x1="-9.873" y1="9.873" x2="9.873" y2="9.873" width="0.1524" layer="21"/>
<wire x1="9.873" y1="9.873" x2="9.873" y2="-9.873" width="0.1524" layer="21"/>
<wire x1="9.873" y1="-9.873" x2="-8.873" y2="-9.873" width="0.1524" layer="21"/>
<wire x1="-8.873" y1="-9.873" x2="-9.873" y2="-8.873" width="0.1524" layer="21"/>
<wire x1="-9.873" y1="-8.873" x2="-9.873" y2="9.873" width="0.1524" layer="21"/>
<circle x="-7.5" y="-7.5" radius="1" width="0.1524" layer="21"/>
<smd name="132" x="-8.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="131" x="-8.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="130" x="-7.8" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="129" x="-7.4" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="128" x="-7" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="127" x="-6.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="126" x="-6.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="125" x="-5.8" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="124" x="-5.4" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="123" x="-5" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="122" x="-4.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="121" x="-4.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="120" x="-3.8" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="119" x="-3.4" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="118" x="-3" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="117" x="-2.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="116" x="-2.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="115" x="-1.8" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="114" x="-1.4" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="113" x="-1" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="112" x="-0.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="111" x="-0.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="110" x="0.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="109" x="0.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="108" x="1" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="107" x="1.4" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="105" x="2.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="106" x="1.8" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="104" x="2.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="103" x="3" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="102" x="3.4" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="101" x="3.8" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="100" x="4.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="99" x="4.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="98" x="5" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="97" x="5.4" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="96" x="5.8" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="95" x="6.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="94" x="6.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="93" x="7" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="92" x="7.4" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="91" x="7.8" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="90" x="8.2" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="89" x="8.6" y="10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="45" x="10.75" y="-8.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="46" x="10.75" y="-8.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="47" x="10.75" y="-7.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="48" x="10.75" y="-7.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="49" x="10.75" y="-7" dx="1.5" dy="0.23" layer="1"/>
<smd name="50" x="10.75" y="-6.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="51" x="10.75" y="-6.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="52" x="10.75" y="-5.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="53" x="10.75" y="-5.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="54" x="10.75" y="-5" dx="1.5" dy="0.23" layer="1"/>
<smd name="55" x="10.75" y="-4.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="56" x="10.75" y="-4.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="57" x="10.75" y="-3.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="58" x="10.75" y="-3.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="59" x="10.75" y="-3" dx="1.5" dy="0.23" layer="1"/>
<smd name="60" x="10.75" y="-2.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="61" x="10.75" y="-2.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="62" x="10.75" y="-1.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="63" x="10.75" y="-1.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="64" x="10.75" y="-1" dx="1.5" dy="0.23" layer="1"/>
<smd name="65" x="10.75" y="-0.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="66" x="10.75" y="-0.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="67" x="10.75" y="0.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="68" x="10.75" y="0.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="69" x="10.75" y="1" dx="1.5" dy="0.23" layer="1"/>
<smd name="70" x="10.75" y="1.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="72" x="10.75" y="2.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="71" x="10.75" y="1.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="73" x="10.75" y="2.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="74" x="10.75" y="3" dx="1.5" dy="0.23" layer="1"/>
<smd name="75" x="10.75" y="3.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="76" x="10.75" y="3.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="77" x="10.75" y="4.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="78" x="10.75" y="4.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="79" x="10.75" y="5" dx="1.5" dy="0.23" layer="1"/>
<smd name="80" x="10.75" y="5.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="81" x="10.75" y="5.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="82" x="10.75" y="6.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="83" x="10.75" y="6.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="84" x="10.75" y="7" dx="1.5" dy="0.23" layer="1"/>
<smd name="85" x="10.75" y="7.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="86" x="10.75" y="7.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="87" x="10.75" y="8.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="88" x="10.75" y="8.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="176" x="-10.75" y="-8.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="175" x="-10.75" y="-8.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="174" x="-10.75" y="-7.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="173" x="-10.75" y="-7.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="172" x="-10.75" y="-7" dx="1.5" dy="0.23" layer="1"/>
<smd name="171" x="-10.75" y="-6.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="170" x="-10.75" y="-6.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="169" x="-10.75" y="-5.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="168" x="-10.75" y="-5.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="167" x="-10.75" y="-5" dx="1.5" dy="0.23" layer="1"/>
<smd name="166" x="-10.75" y="-4.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="165" x="-10.75" y="-4.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="164" x="-10.75" y="-3.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="163" x="-10.75" y="-3.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="162" x="-10.75" y="-3" dx="1.5" dy="0.23" layer="1"/>
<smd name="161" x="-10.75" y="-2.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="160" x="-10.75" y="-2.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="159" x="-10.75" y="-1.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="158" x="-10.75" y="-1.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="157" x="-10.75" y="-1" dx="1.5" dy="0.23" layer="1"/>
<smd name="156" x="-10.75" y="-0.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="155" x="-10.75" y="-0.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="154" x="-10.75" y="0.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="153" x="-10.75" y="0.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="152" x="-10.75" y="1" dx="1.5" dy="0.23" layer="1"/>
<smd name="151" x="-10.75" y="1.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="149" x="-10.75" y="2.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="150" x="-10.75" y="1.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="148" x="-10.75" y="2.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="147" x="-10.75" y="3" dx="1.5" dy="0.23" layer="1"/>
<smd name="146" x="-10.75" y="3.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="145" x="-10.75" y="3.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="144" x="-10.75" y="4.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="143" x="-10.75" y="4.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="142" x="-10.75" y="5" dx="1.5" dy="0.23" layer="1"/>
<smd name="141" x="-10.75" y="5.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="140" x="-10.75" y="5.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="139" x="-10.75" y="6.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="138" x="-10.75" y="6.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="137" x="-10.75" y="7" dx="1.5" dy="0.23" layer="1"/>
<smd name="136" x="-10.75" y="7.4" dx="1.5" dy="0.23" layer="1"/>
<smd name="135" x="-10.75" y="7.8" dx="1.5" dy="0.23" layer="1"/>
<smd name="134" x="-10.75" y="8.2" dx="1.5" dy="0.23" layer="1"/>
<smd name="133" x="-10.75" y="8.6" dx="1.5" dy="0.23" layer="1"/>
<smd name="1" x="-8.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="2" x="-8.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="3" x="-7.8" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="4" x="-7.4" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="5" x="-7" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="6" x="-6.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="7" x="-6.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="8" x="-5.8" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="9" x="-5.4" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="10" x="-5" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="11" x="-4.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="12" x="-4.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="13" x="-3.8" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="14" x="-3.4" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="15" x="-3" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="16" x="-2.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="17" x="-2.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="18" x="-1.8" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="19" x="-1.4" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="20" x="-1" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="21" x="-0.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="22" x="-0.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="23" x="0.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="24" x="0.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="25" x="1" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="26" x="1.4" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="28" x="2.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="27" x="1.8" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="29" x="2.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="30" x="3" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="31" x="3.4" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="32" x="3.8" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="33" x="4.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="34" x="4.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="35" x="5" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="36" x="5.4" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="37" x="5.8" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="38" x="6.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="39" x="6.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="40" x="7" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="41" x="7.4" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="42" x="7.8" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="43" x="8.2" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<smd name="44" x="8.6" y="-10.75" dx="0.23" dy="1.5" layer="1"/>
<text x="-8.636" y="11.811" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-2.54" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.715" y1="9.873" x2="-8.485" y2="10.872" layer="51"/>
<rectangle x1="-8.315" y1="9.873" x2="-8.085" y2="10.872" layer="51"/>
<rectangle x1="-7.915" y1="9.873" x2="-7.685" y2="10.872" layer="51"/>
<rectangle x1="-7.515" y1="9.873" x2="-7.285" y2="10.872" layer="51"/>
<rectangle x1="-7.115" y1="9.873" x2="-6.885" y2="10.872" layer="51"/>
<rectangle x1="-6.715" y1="9.873" x2="-6.485" y2="10.872" layer="51"/>
<rectangle x1="-6.315" y1="9.873" x2="-6.085" y2="10.872" layer="51"/>
<rectangle x1="-5.915" y1="9.873" x2="-5.685" y2="10.872" layer="51"/>
<rectangle x1="-5.515" y1="9.873" x2="-5.285" y2="10.872" layer="51"/>
<rectangle x1="-5.115" y1="9.873" x2="-4.885" y2="10.872" layer="51"/>
<rectangle x1="-4.715" y1="9.873" x2="-4.485" y2="10.872" layer="51"/>
<rectangle x1="-4.315" y1="9.873" x2="-4.085" y2="10.872" layer="51"/>
<rectangle x1="-3.915" y1="9.873" x2="-3.685" y2="10.872" layer="51"/>
<rectangle x1="-3.515" y1="9.873" x2="-3.285" y2="10.872" layer="51"/>
<rectangle x1="-3.115" y1="9.873" x2="-2.885" y2="10.872" layer="51"/>
<rectangle x1="-2.715" y1="9.873" x2="-2.485" y2="10.872" layer="51"/>
<rectangle x1="-2.315" y1="9.873" x2="-2.085" y2="10.872" layer="51"/>
<rectangle x1="-1.915" y1="9.873" x2="-1.685" y2="10.872" layer="51"/>
<rectangle x1="-1.515" y1="9.873" x2="-1.285" y2="10.872" layer="51"/>
<rectangle x1="-1.115" y1="9.873" x2="-0.885" y2="10.872" layer="51"/>
<rectangle x1="-0.715" y1="9.873" x2="-0.485" y2="10.872" layer="51"/>
<rectangle x1="-0.315" y1="9.873" x2="-0.085" y2="10.872" layer="51"/>
<rectangle x1="0.085" y1="9.873" x2="0.315" y2="10.872" layer="51"/>
<rectangle x1="0.485" y1="9.873" x2="0.715" y2="10.872" layer="51"/>
<rectangle x1="0.885" y1="9.873" x2="1.115" y2="10.872" layer="51"/>
<rectangle x1="1.285" y1="9.873" x2="1.515" y2="10.872" layer="51"/>
<rectangle x1="1.685" y1="9.873" x2="1.915" y2="10.872" layer="51"/>
<rectangle x1="2.085" y1="9.873" x2="2.315" y2="10.872" layer="51"/>
<rectangle x1="2.485" y1="9.873" x2="2.715" y2="10.872" layer="51"/>
<rectangle x1="2.885" y1="9.873" x2="3.115" y2="10.872" layer="51"/>
<rectangle x1="3.285" y1="9.873" x2="3.515" y2="10.872" layer="51"/>
<rectangle x1="3.685" y1="9.873" x2="3.915" y2="10.872" layer="51"/>
<rectangle x1="4.085" y1="9.873" x2="4.315" y2="10.872" layer="51"/>
<rectangle x1="4.485" y1="9.873" x2="4.715" y2="10.872" layer="51"/>
<rectangle x1="4.885" y1="9.873" x2="5.115" y2="10.872" layer="51"/>
<rectangle x1="5.285" y1="9.873" x2="5.515" y2="10.872" layer="51"/>
<rectangle x1="5.685" y1="9.873" x2="5.915" y2="10.872" layer="51"/>
<rectangle x1="6.085" y1="9.873" x2="6.315" y2="10.872" layer="51"/>
<rectangle x1="6.485" y1="9.873" x2="6.715" y2="10.872" layer="51"/>
<rectangle x1="6.885" y1="9.873" x2="7.115" y2="10.872" layer="51"/>
<rectangle x1="7.285" y1="9.873" x2="7.515" y2="10.872" layer="51"/>
<rectangle x1="7.685" y1="9.873" x2="7.915" y2="10.872" layer="51"/>
<rectangle x1="8.085" y1="9.873" x2="8.315" y2="10.872" layer="51"/>
<rectangle x1="8.485" y1="9.873" x2="8.715" y2="10.872" layer="51"/>
<rectangle x1="8.485" y1="-10.872" x2="8.715" y2="-9.873" layer="51"/>
<rectangle x1="8.085" y1="-10.872" x2="8.315" y2="-9.873" layer="51"/>
<rectangle x1="7.685" y1="-10.872" x2="7.915" y2="-9.873" layer="51"/>
<rectangle x1="7.285" y1="-10.872" x2="7.515" y2="-9.873" layer="51"/>
<rectangle x1="6.885" y1="-10.872" x2="7.115" y2="-9.873" layer="51"/>
<rectangle x1="6.485" y1="-10.872" x2="6.715" y2="-9.873" layer="51"/>
<rectangle x1="6.085" y1="-10.872" x2="6.315" y2="-9.873" layer="51"/>
<rectangle x1="5.685" y1="-10.872" x2="5.915" y2="-9.873" layer="51"/>
<rectangle x1="5.285" y1="-10.872" x2="5.515" y2="-9.873" layer="51"/>
<rectangle x1="4.885" y1="-10.872" x2="5.115" y2="-9.873" layer="51"/>
<rectangle x1="4.485" y1="-10.872" x2="4.715" y2="-9.873" layer="51"/>
<rectangle x1="4.085" y1="-10.872" x2="4.315" y2="-9.873" layer="51"/>
<rectangle x1="3.685" y1="-10.872" x2="3.915" y2="-9.873" layer="51"/>
<rectangle x1="3.285" y1="-10.872" x2="3.515" y2="-9.873" layer="51"/>
<rectangle x1="2.885" y1="-10.872" x2="3.115" y2="-9.873" layer="51"/>
<rectangle x1="2.485" y1="-10.872" x2="2.715" y2="-9.873" layer="51"/>
<rectangle x1="2.085" y1="-10.872" x2="2.315" y2="-9.873" layer="51"/>
<rectangle x1="1.685" y1="-10.872" x2="1.915" y2="-9.873" layer="51"/>
<rectangle x1="1.285" y1="-10.872" x2="1.515" y2="-9.873" layer="51"/>
<rectangle x1="0.885" y1="-10.872" x2="1.115" y2="-9.873" layer="51"/>
<rectangle x1="0.485" y1="-10.872" x2="0.715" y2="-9.873" layer="51"/>
<rectangle x1="0.085" y1="-10.872" x2="0.315" y2="-9.873" layer="51"/>
<rectangle x1="-0.315" y1="-10.872" x2="-0.085" y2="-9.873" layer="51"/>
<rectangle x1="-0.715" y1="-10.872" x2="-0.485" y2="-9.873" layer="51"/>
<rectangle x1="-1.115" y1="-10.872" x2="-0.885" y2="-9.873" layer="51"/>
<rectangle x1="-1.515" y1="-10.872" x2="-1.285" y2="-9.873" layer="51"/>
<rectangle x1="-1.915" y1="-10.872" x2="-1.685" y2="-9.873" layer="51"/>
<rectangle x1="-2.315" y1="-10.872" x2="-2.085" y2="-9.873" layer="51"/>
<rectangle x1="-2.715" y1="-10.872" x2="-2.485" y2="-9.873" layer="51"/>
<rectangle x1="-3.115" y1="-10.872" x2="-2.885" y2="-9.873" layer="51"/>
<rectangle x1="-3.515" y1="-10.872" x2="-3.285" y2="-9.873" layer="51"/>
<rectangle x1="-3.915" y1="-10.872" x2="-3.685" y2="-9.873" layer="51"/>
<rectangle x1="-4.315" y1="-10.872" x2="-4.085" y2="-9.873" layer="51"/>
<rectangle x1="-4.715" y1="-10.872" x2="-4.485" y2="-9.873" layer="51"/>
<rectangle x1="-5.115" y1="-10.872" x2="-4.885" y2="-9.873" layer="51"/>
<rectangle x1="-5.515" y1="-10.872" x2="-5.285" y2="-9.873" layer="51"/>
<rectangle x1="-5.915" y1="-10.872" x2="-5.685" y2="-9.873" layer="51"/>
<rectangle x1="-6.315" y1="-10.872" x2="-6.085" y2="-9.873" layer="51"/>
<rectangle x1="-6.715" y1="-10.872" x2="-6.485" y2="-9.873" layer="51"/>
<rectangle x1="-7.115" y1="-10.872" x2="-6.885" y2="-9.873" layer="51"/>
<rectangle x1="-7.515" y1="-10.872" x2="-7.285" y2="-9.873" layer="51"/>
<rectangle x1="-7.915" y1="-10.872" x2="-7.685" y2="-9.873" layer="51"/>
<rectangle x1="-8.315" y1="-10.872" x2="-8.085" y2="-9.873" layer="51"/>
<rectangle x1="-8.715" y1="-10.872" x2="-8.485" y2="-9.873" layer="51"/>
<rectangle x1="-10.872" y1="-8.715" x2="-9.873" y2="-8.485" layer="51"/>
<rectangle x1="-10.872" y1="-8.315" x2="-9.873" y2="-8.085" layer="51"/>
<rectangle x1="-10.872" y1="-7.915" x2="-9.873" y2="-7.685" layer="51"/>
<rectangle x1="-10.872" y1="-7.515" x2="-9.873" y2="-7.285" layer="51"/>
<rectangle x1="-10.872" y1="-7.115" x2="-9.873" y2="-6.885" layer="51"/>
<rectangle x1="-10.872" y1="-6.715" x2="-9.873" y2="-6.485" layer="51"/>
<rectangle x1="-10.872" y1="-6.315" x2="-9.873" y2="-6.085" layer="51"/>
<rectangle x1="-10.872" y1="-5.915" x2="-9.873" y2="-5.685" layer="51"/>
<rectangle x1="-10.872" y1="-5.515" x2="-9.873" y2="-5.285" layer="51"/>
<rectangle x1="-10.872" y1="-5.115" x2="-9.873" y2="-4.885" layer="51"/>
<rectangle x1="-10.872" y1="-4.715" x2="-9.873" y2="-4.485" layer="51"/>
<rectangle x1="-10.872" y1="-4.315" x2="-9.873" y2="-4.085" layer="51"/>
<rectangle x1="-10.872" y1="-3.915" x2="-9.873" y2="-3.685" layer="51"/>
<rectangle x1="-10.872" y1="-3.515" x2="-9.873" y2="-3.285" layer="51"/>
<rectangle x1="-10.872" y1="-3.115" x2="-9.873" y2="-2.885" layer="51"/>
<rectangle x1="-10.872" y1="-2.715" x2="-9.873" y2="-2.485" layer="51"/>
<rectangle x1="-10.872" y1="-2.315" x2="-9.873" y2="-2.085" layer="51"/>
<rectangle x1="-10.872" y1="-1.915" x2="-9.873" y2="-1.685" layer="51"/>
<rectangle x1="-10.872" y1="-1.515" x2="-9.873" y2="-1.285" layer="51"/>
<rectangle x1="-10.872" y1="-1.115" x2="-9.873" y2="-0.885" layer="51"/>
<rectangle x1="-10.872" y1="-0.715" x2="-9.873" y2="-0.485" layer="51"/>
<rectangle x1="-10.872" y1="-0.315" x2="-9.873" y2="-0.085" layer="51"/>
<rectangle x1="-10.872" y1="0.085" x2="-9.873" y2="0.315" layer="51"/>
<rectangle x1="-10.872" y1="0.485" x2="-9.873" y2="0.715" layer="51"/>
<rectangle x1="-10.872" y1="0.885" x2="-9.873" y2="1.115" layer="51"/>
<rectangle x1="-10.872" y1="1.285" x2="-9.873" y2="1.515" layer="51"/>
<rectangle x1="-10.872" y1="1.685" x2="-9.873" y2="1.915" layer="51"/>
<rectangle x1="-10.872" y1="2.085" x2="-9.873" y2="2.315" layer="51"/>
<rectangle x1="-10.872" y1="2.485" x2="-9.873" y2="2.715" layer="51"/>
<rectangle x1="-10.872" y1="2.885" x2="-9.873" y2="3.115" layer="51"/>
<rectangle x1="-10.872" y1="3.285" x2="-9.873" y2="3.515" layer="51"/>
<rectangle x1="-10.872" y1="3.685" x2="-9.873" y2="3.915" layer="51"/>
<rectangle x1="-10.872" y1="4.085" x2="-9.873" y2="4.315" layer="51"/>
<rectangle x1="-10.872" y1="4.485" x2="-9.873" y2="4.715" layer="51"/>
<rectangle x1="-10.872" y1="4.885" x2="-9.873" y2="5.115" layer="51"/>
<rectangle x1="-10.872" y1="5.285" x2="-9.873" y2="5.515" layer="51"/>
<rectangle x1="-10.872" y1="5.685" x2="-9.873" y2="5.915" layer="51"/>
<rectangle x1="-10.872" y1="6.085" x2="-9.873" y2="6.315" layer="51"/>
<rectangle x1="-10.872" y1="6.485" x2="-9.873" y2="6.715" layer="51"/>
<rectangle x1="-10.872" y1="6.885" x2="-9.873" y2="7.115" layer="51"/>
<rectangle x1="-10.872" y1="7.285" x2="-9.873" y2="7.515" layer="51"/>
<rectangle x1="-10.872" y1="7.685" x2="-9.873" y2="7.915" layer="51"/>
<rectangle x1="-10.872" y1="8.085" x2="-9.873" y2="8.315" layer="51"/>
<rectangle x1="-10.872" y1="8.485" x2="-9.873" y2="8.715" layer="51"/>
<rectangle x1="9.873" y1="8.485" x2="10.872" y2="8.715" layer="51"/>
<rectangle x1="9.873" y1="8.085" x2="10.872" y2="8.315" layer="51"/>
<rectangle x1="9.873" y1="7.685" x2="10.872" y2="7.915" layer="51"/>
<rectangle x1="9.873" y1="7.285" x2="10.872" y2="7.515" layer="51"/>
<rectangle x1="9.873" y1="6.885" x2="10.872" y2="7.115" layer="51"/>
<rectangle x1="9.873" y1="6.485" x2="10.872" y2="6.715" layer="51"/>
<rectangle x1="9.873" y1="6.085" x2="10.872" y2="6.315" layer="51"/>
<rectangle x1="9.873" y1="5.685" x2="10.872" y2="5.915" layer="51"/>
<rectangle x1="9.873" y1="5.285" x2="10.872" y2="5.515" layer="51"/>
<rectangle x1="9.873" y1="4.885" x2="10.872" y2="5.115" layer="51"/>
<rectangle x1="9.873" y1="4.485" x2="10.872" y2="4.715" layer="51"/>
<rectangle x1="9.873" y1="4.085" x2="10.872" y2="4.315" layer="51"/>
<rectangle x1="9.873" y1="3.685" x2="10.872" y2="3.915" layer="51"/>
<rectangle x1="9.873" y1="3.285" x2="10.872" y2="3.515" layer="51"/>
<rectangle x1="9.873" y1="2.885" x2="10.872" y2="3.115" layer="51"/>
<rectangle x1="9.873" y1="2.485" x2="10.872" y2="2.715" layer="51"/>
<rectangle x1="9.873" y1="2.085" x2="10.872" y2="2.315" layer="51"/>
<rectangle x1="9.873" y1="1.685" x2="10.872" y2="1.915" layer="51"/>
<rectangle x1="9.873" y1="1.285" x2="10.872" y2="1.515" layer="51"/>
<rectangle x1="9.873" y1="0.885" x2="10.872" y2="1.115" layer="51"/>
<rectangle x1="9.873" y1="0.485" x2="10.872" y2="0.715" layer="51"/>
<rectangle x1="9.873" y1="0.085" x2="10.872" y2="0.315" layer="51"/>
<rectangle x1="9.873" y1="-0.315" x2="10.872" y2="-0.085" layer="51"/>
<rectangle x1="9.873" y1="-0.715" x2="10.872" y2="-0.485" layer="51"/>
<rectangle x1="9.873" y1="-1.115" x2="10.872" y2="-0.885" layer="51"/>
<rectangle x1="9.873" y1="-1.515" x2="10.872" y2="-1.285" layer="51"/>
<rectangle x1="9.873" y1="-1.915" x2="10.872" y2="-1.685" layer="51"/>
<rectangle x1="9.873" y1="-2.315" x2="10.872" y2="-2.085" layer="51"/>
<rectangle x1="9.873" y1="-2.715" x2="10.872" y2="-2.485" layer="51"/>
<rectangle x1="9.873" y1="-3.115" x2="10.872" y2="-2.885" layer="51"/>
<rectangle x1="9.873" y1="-3.515" x2="10.872" y2="-3.285" layer="51"/>
<rectangle x1="9.873" y1="-3.915" x2="10.872" y2="-3.685" layer="51"/>
<rectangle x1="9.873" y1="-4.315" x2="10.872" y2="-4.085" layer="51"/>
<rectangle x1="9.873" y1="-4.715" x2="10.872" y2="-4.485" layer="51"/>
<rectangle x1="9.873" y1="-5.115" x2="10.872" y2="-4.885" layer="51"/>
<rectangle x1="9.873" y1="-5.515" x2="10.872" y2="-5.285" layer="51"/>
<rectangle x1="9.873" y1="-5.915" x2="10.872" y2="-5.685" layer="51"/>
<rectangle x1="9.873" y1="-6.315" x2="10.872" y2="-6.085" layer="51"/>
<rectangle x1="9.873" y1="-6.715" x2="10.872" y2="-6.485" layer="51"/>
<rectangle x1="9.873" y1="-7.115" x2="10.872" y2="-6.885" layer="51"/>
<rectangle x1="9.873" y1="-7.515" x2="10.872" y2="-7.285" layer="51"/>
<rectangle x1="9.873" y1="-7.915" x2="10.872" y2="-7.685" layer="51"/>
<rectangle x1="9.873" y1="-8.315" x2="10.872" y2="-8.085" layer="51"/>
<rectangle x1="9.873" y1="-8.715" x2="10.872" y2="-8.485" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="M10X2">
<wire x1="-1.27" y1="5.08" x2="-2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="7.62" x2="-2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="10.16" x2="-2.54" y2="10.16" width="0.6096" layer="94"/>
<wire x1="-3.81" y1="12.7" x2="-3.81" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="-1.27" y1="0" x2="-2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="2.54" x2="-2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="-2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-5.08" x2="-2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-7.62" x2="-2.54" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-10.16" x2="-2.54" y2="-10.16" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-12.7" x2="-2.54" y2="-12.7" width="0.6096" layer="94"/>
<wire x1="3.81" y1="-15.24" x2="-3.81" y2="-15.24" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-7.62" x2="2.54" y2="-7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-10.16" x2="2.54" y2="-10.16" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-12.7" x2="2.54" y2="-12.7" width="0.6096" layer="94"/>
<wire x1="3.81" y1="-15.24" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="12.7" x2="3.81" y2="12.7" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="7.62" x2="2.54" y2="7.62" width="0.6096" layer="94"/>
<wire x1="1.27" y1="10.16" x2="2.54" y2="10.16" width="0.6096" layer="94"/>
<text x="-2.54" y="-17.78" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="13.97" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="-7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="2" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="-7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="4" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="-7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="6" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="7" x="-7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="8" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="9" x="-7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="10" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="11" x="-7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="12" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="13" x="-7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="14" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="15" x="-7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="16" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="17" x="-7.62" y="-10.16" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="18" x="7.62" y="-10.16" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="19" x="-7.62" y="-12.7" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="20" x="7.62" y="-12.7" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
<symbol name="M05X2">
<wire x1="3.81" y1="-7.62" x2="-3.81" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="-3.81" y1="7.62" x2="-3.81" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-7.62" x2="3.81" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="7.62" x2="3.81" y2="7.62" width="0.4064" layer="94"/>
<wire x1="1.27" y1="5.08" x2="2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="0" x2="-2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="-2.54" y2="-2.54" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="-5.08" x2="-2.54" y2="-5.08" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="5.08" x2="-2.54" y2="5.08" width="0.6096" layer="94"/>
<wire x1="-1.27" y1="2.54" x2="-2.54" y2="2.54" width="0.6096" layer="94"/>
<text x="-2.54" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="8.382" size="1.778" layer="95">&gt;NAME</text>
<pin name="10" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="6" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="9" x="-7.62" y="-5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="7" x="-7.62" y="-2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="5" x="-7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="3" x="-7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1"/>
<pin name="1" x="-7.62" y="5.08" visible="pad" length="middle" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="TS">
<wire x1="0" y1="-3.175" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="3.175" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-0.635" y2="0" width="0.254" layer="94"/>
<wire x1="-4.445" y1="1.905" x2="-3.175" y2="1.905" width="0.254" layer="94"/>
<wire x1="-4.445" y1="-1.905" x2="-3.175" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-4.445" y1="1.905" x2="-4.445" y2="0" width="0.254" layer="94"/>
<wire x1="-4.445" y1="0" x2="-4.445" y2="-1.905" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.905" y2="0" width="0.1524" layer="94"/>
<wire x1="-1.27" y1="0" x2="-0.635" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.635" y1="0" x2="-1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="-4.445" y1="0" x2="-3.175" y2="0" width="0.1524" layer="94"/>
<text x="-6.35" y="-1.905" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="-3.81" y="3.175" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="P" x="0" y="-5.08" visible="pad" length="short" direction="pas" rot="R90"/>
<pin name="S" x="0" y="5.08" visible="pad" length="short" direction="pas" rot="R270"/>
</symbol>
<symbol name="STAND-OFF">
<circle x="0" y="0" radius="1.27" width="0.254" layer="94"/>
</symbol>
<symbol name="PLS_2X32">
<wire x1="-1.778" y1="-161.036" x2="-1.778" y2="1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="-161.036" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-4.064" y2="-1.016" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-4.064" y2="1.016" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-4.064" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-2.54" x2="-4.064" y2="-3.556" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-4.064" y2="-6.096" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-4.064" y2="-4.064" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="-4.064" y2="-6.604" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="-4.064" y2="-8.636" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-10.16" x2="-4.064" y2="-11.176" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-10.16" x2="-4.064" y2="-9.144" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-12.7" x2="-4.064" y2="-11.684" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-12.7" x2="-4.064" y2="-13.716" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-15.24" x2="-4.064" y2="-16.256" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-15.24" x2="-4.064" y2="-14.224" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-17.78" x2="-4.064" y2="-16.764" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-17.78" x2="-4.064" y2="-18.796" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-20.32" x2="-4.064" y2="-21.336" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-20.32" x2="-4.064" y2="-19.304" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-22.86" x2="-4.064" y2="-21.844" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-22.86" x2="-4.064" y2="-23.876" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-25.4" x2="-4.064" y2="-26.416" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-25.4" x2="-4.064" y2="-24.384" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-27.94" x2="-4.064" y2="-26.924" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-27.94" x2="-4.064" y2="-28.956" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-30.48" x2="-4.064" y2="-31.496" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-30.48" x2="-4.064" y2="-29.464" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-33.02" x2="-4.064" y2="-32.004" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-33.02" x2="-4.064" y2="-34.036" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-35.56" x2="-4.064" y2="-36.576" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-35.56" x2="-4.064" y2="-34.544" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-38.1" x2="-4.064" y2="-37.084" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-38.1" x2="-4.064" y2="-39.116" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-40.64" x2="-4.064" y2="-41.656" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-40.64" x2="-4.064" y2="-39.624" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-43.18" x2="-4.064" y2="-42.164" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-43.18" x2="-4.064" y2="-44.196" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-45.72" x2="-4.064" y2="-46.736" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-45.72" x2="-4.064" y2="-44.704" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-48.26" x2="-4.064" y2="-47.244" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-48.26" x2="-4.064" y2="-49.276" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-50.8" x2="-4.064" y2="-51.816" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-50.8" x2="-4.064" y2="-49.784" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-53.34" x2="-4.064" y2="-52.324" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-53.34" x2="-4.064" y2="-54.356" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-55.88" x2="-4.064" y2="-56.896" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-55.88" x2="-4.064" y2="-54.864" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-58.42" x2="-4.064" y2="-57.404" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-58.42" x2="-4.064" y2="-59.436" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-60.96" x2="-4.064" y2="-61.976" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-60.96" x2="-4.064" y2="-59.944" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-63.5" x2="-4.064" y2="-62.484" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-63.5" x2="-4.064" y2="-64.516" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-66.04" x2="-4.064" y2="-67.056" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-66.04" x2="-4.064" y2="-65.024" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-68.58" x2="-4.064" y2="-67.564" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-68.58" x2="-4.064" y2="-69.596" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-71.12" x2="-4.064" y2="-72.136" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-71.12" x2="-4.064" y2="-70.104" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-73.66" x2="-4.064" y2="-72.644" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-73.66" x2="-4.064" y2="-74.676" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-76.2" x2="-4.064" y2="-77.216" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-76.2" x2="-4.064" y2="-75.184" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-78.74" x2="-4.064" y2="-77.724" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-78.74" x2="-4.064" y2="-79.756" width="0.254" layer="94"/>
<text x="-4.826" y="2.286" size="1.778" layer="95">&gt;NAME</text>
<text x="-4.572" y="6.477" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="0" y="0" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="0" y="-2.54" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="3" x="0" y="-5.08" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="4" x="0" y="-7.62" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="5" x="0" y="-10.16" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="6" x="0" y="-12.7" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="7" x="0" y="-15.24" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="8" x="0" y="-17.78" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="9" x="0" y="-20.32" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="10" x="0" y="-22.86" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="11" x="0" y="-25.4" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="12" x="0" y="-27.94" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="13" x="0" y="-30.48" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="14" x="0" y="-33.02" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="15" x="0" y="-35.56" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="16" x="0" y="-38.1" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="17" x="0" y="-40.64" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="18" x="0" y="-43.18" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="19" x="0" y="-45.72" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="20" x="0" y="-48.26" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="21" x="0" y="-50.8" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="22" x="0" y="-53.34" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="23" x="0" y="-55.88" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="24" x="0" y="-58.42" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="25" x="0" y="-60.96" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="26" x="0" y="-63.5" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="27" x="0" y="-66.04" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="28" x="0" y="-68.58" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="29" x="0" y="-71.12" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="30" x="0" y="-73.66" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="31" x="0" y="-76.2" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="32" x="0" y="-78.74" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<wire x1="-5.08" y1="-81.28" x2="-4.064" y2="-82.296" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-81.28" x2="-4.064" y2="-80.264" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-83.82" x2="-4.064" y2="-82.804" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-83.82" x2="-4.064" y2="-84.836" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-86.36" x2="-4.064" y2="-87.376" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-86.36" x2="-4.064" y2="-85.344" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-88.9" x2="-4.064" y2="-87.884" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-88.9" x2="-4.064" y2="-89.916" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-91.44" x2="-4.064" y2="-92.456" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-91.44" x2="-4.064" y2="-90.424" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-93.98" x2="-4.064" y2="-92.964" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-93.98" x2="-4.064" y2="-94.996" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-96.52" x2="-4.064" y2="-97.536" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-96.52" x2="-4.064" y2="-95.504" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-99.06" x2="-4.064" y2="-98.044" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-99.06" x2="-4.064" y2="-100.076" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-101.6" x2="-4.064" y2="-102.616" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-101.6" x2="-4.064" y2="-100.584" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-104.14" x2="-4.064" y2="-103.124" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-104.14" x2="-4.064" y2="-105.156" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-106.68" x2="-4.064" y2="-107.696" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-106.68" x2="-4.064" y2="-105.664" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-109.22" x2="-4.064" y2="-108.204" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-109.22" x2="-4.064" y2="-110.236" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-111.76" x2="-4.064" y2="-112.776" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-111.76" x2="-4.064" y2="-110.744" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-114.3" x2="-4.064" y2="-113.284" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-114.3" x2="-4.064" y2="-115.316" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-116.84" x2="-4.064" y2="-117.856" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-116.84" x2="-4.064" y2="-115.824" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-119.38" x2="-4.064" y2="-118.364" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-119.38" x2="-4.064" y2="-120.396" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-121.92" x2="-4.064" y2="-122.936" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-121.92" x2="-4.064" y2="-120.904" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-124.46" x2="-4.064" y2="-123.444" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-124.46" x2="-4.064" y2="-125.476" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-127" x2="-4.064" y2="-128.016" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-127" x2="-4.064" y2="-125.984" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-129.54" x2="-4.064" y2="-128.524" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-129.54" x2="-4.064" y2="-130.556" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-132.08" x2="-4.064" y2="-133.096" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-132.08" x2="-4.064" y2="-131.064" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-134.62" x2="-4.064" y2="-133.604" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-134.62" x2="-4.064" y2="-135.636" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-137.16" x2="-4.064" y2="-138.176" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-137.16" x2="-4.064" y2="-136.144" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-139.7" x2="-4.064" y2="-138.684" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-139.7" x2="-4.064" y2="-140.716" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-142.24" x2="-4.064" y2="-143.256" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-142.24" x2="-4.064" y2="-141.224" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-144.78" x2="-4.064" y2="-143.764" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-144.78" x2="-4.064" y2="-145.796" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-147.32" x2="-4.064" y2="-148.336" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-147.32" x2="-4.064" y2="-146.304" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-149.86" x2="-4.064" y2="-148.844" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-149.86" x2="-4.064" y2="-150.876" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-152.4" x2="-4.064" y2="-153.416" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-152.4" x2="-4.064" y2="-151.384" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-154.94" x2="-4.064" y2="-153.924" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-154.94" x2="-4.064" y2="-155.956" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-157.48" x2="-4.064" y2="-158.496" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-157.48" x2="-4.064" y2="-156.464" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-160.02" x2="-4.064" y2="-159.004" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-160.02" x2="-4.064" y2="-161.036" width="0.254" layer="94"/>
<pin name="33" x="0" y="-81.28" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="34" x="0" y="-83.82" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="35" x="0" y="-86.36" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="36" x="0" y="-88.9" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="37" x="0" y="-91.44" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="38" x="0" y="-93.98" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="39" x="0" y="-96.52" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="40" x="0" y="-99.06" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="41" x="0" y="-101.6" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="42" x="0" y="-104.14" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="43" x="0" y="-106.68" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="44" x="0" y="-109.22" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="45" x="0" y="-111.76" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="46" x="0" y="-114.3" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="47" x="0" y="-116.84" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="48" x="0" y="-119.38" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="49" x="0" y="-121.92" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="50" x="0" y="-124.46" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="51" x="0" y="-127" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="52" x="0" y="-129.54" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="53" x="0" y="-132.08" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="54" x="0" y="-134.62" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="55" x="0" y="-137.16" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="56" x="0" y="-139.7" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="57" x="0" y="-142.24" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="58" x="0" y="-144.78" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="59" x="0" y="-147.32" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="60" x="0" y="-149.86" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="61" x="0" y="-152.4" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="62" x="0" y="-154.94" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="63" x="0" y="-157.48" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="64" x="0" y="-160.02" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
<symbol name="STM32F407I">
<wire x1="-35.56" y1="116.84" x2="-7.62" y2="116.84" width="0.1524" layer="94"/>
<wire x1="-7.62" y1="116.84" x2="5.08" y2="116.84" width="0.1524" layer="94"/>
<wire x1="5.08" y1="116.84" x2="27.94" y2="116.84" width="0.1524" layer="94"/>
<wire x1="27.94" y1="116.84" x2="27.94" y2="-129.54" width="0.1524" layer="94"/>
<wire x1="27.94" y1="-129.54" x2="5.08" y2="-129.54" width="0.1524" layer="94"/>
<wire x1="5.08" y1="-129.54" x2="-7.62" y2="-129.54" width="0.1524" layer="94"/>
<wire x1="-7.62" y1="-129.54" x2="-35.56" y2="-129.54" width="0.1524" layer="94"/>
<wire x1="-35.56" y1="-129.54" x2="-35.56" y2="116.84" width="0.1524" layer="94"/>
<text x="-7.62" y="117.856" size="1.524" layer="95">&gt;NAME</text>
<text x="-5.334" y="-132.842" size="1.524" layer="95">&gt;VALUE</text>
<pin name="PE2" x="33.02" y="66.04" length="middle" rot="R180"/>
<pin name="PE3" x="33.02" y="63.5" length="middle" rot="R180"/>
<pin name="PE4" x="33.02" y="60.96" length="middle" rot="R180"/>
<pin name="PE5" x="33.02" y="58.42" length="middle" rot="R180"/>
<pin name="PE6" x="33.02" y="55.88" length="middle" rot="R180"/>
<pin name="V_BAT" x="-40.64" y="104.14" length="middle" direction="pwr"/>
<pin name="PC13(TAMPER-RTC)" x="-40.64" y="-121.92" length="middle"/>
<pin name="PC14(OSC32_IN)" x="-40.64" y="-124.46" length="middle"/>
<pin name="PC15(OSC32_OUT)" x="-40.64" y="-127" length="middle"/>
<pin name="GND@4" x="-40.64" y="38.1" length="middle" direction="pwr"/>
<pin name="VDD@6" x="-40.64" y="73.66" length="middle" direction="pwr"/>
<pin name="NRST" x="-40.64" y="-12.7" length="middle"/>
<pin name="PC0" x="-40.64" y="-88.9" length="middle"/>
<pin name="PC1" x="-40.64" y="-91.44" length="middle"/>
<pin name="PC2" x="-40.64" y="-93.98" length="middle"/>
<pin name="PC3" x="-40.64" y="-96.52" length="middle"/>
<pin name="VDD@1" x="-40.64" y="86.36" length="middle" direction="pwr"/>
<pin name="GND_A" x="-40.64" y="93.98" length="middle" direction="pwr"/>
<pin name="VREF+" x="-40.64" y="99.06" length="middle" direction="pwr"/>
<pin name="VDD_A" x="-40.64" y="96.52" length="middle" direction="pwr"/>
<pin name="PA0" x="-40.64" y="-17.78" length="middle"/>
<pin name="PA1" x="-40.64" y="-20.32" length="middle"/>
<pin name="PA2" x="-40.64" y="-22.86" length="middle"/>
<pin name="PA3" x="-40.64" y="-25.4" length="middle"/>
<pin name="GND@3" x="-40.64" y="40.64" length="middle" direction="pwr"/>
<pin name="VDD@5" x="-40.64" y="76.2" length="middle" direction="pwr"/>
<pin name="PA4" x="-40.64" y="-27.94" length="middle"/>
<pin name="PA5" x="-40.64" y="-30.48" length="middle"/>
<pin name="PA6" x="-40.64" y="-33.02" length="middle"/>
<pin name="PA7" x="-40.64" y="-35.56" length="middle"/>
<pin name="PC4" x="-40.64" y="-99.06" length="middle"/>
<pin name="PC5" x="-40.64" y="-101.6" length="middle"/>
<pin name="PB0" x="-40.64" y="-53.34" length="middle"/>
<pin name="PB1" x="-40.64" y="-55.88" length="middle"/>
<pin name="BOOT_1(PB2)" x="-40.64" y="5.08" length="middle"/>
<pin name="PE7" x="33.02" y="53.34" length="middle" rot="R180"/>
<pin name="PE8" x="33.02" y="50.8" length="middle" rot="R180"/>
<pin name="PE9" x="33.02" y="48.26" length="middle" rot="R180"/>
<pin name="PE10" x="33.02" y="45.72" length="middle" rot="R180"/>
<pin name="PE11" x="33.02" y="43.18" length="middle" rot="R180"/>
<pin name="PE12" x="33.02" y="40.64" length="middle" rot="R180"/>
<pin name="PE13" x="33.02" y="38.1" length="middle" rot="R180"/>
<pin name="PE14" x="33.02" y="35.56" length="middle" rot="R180"/>
<pin name="PE15" x="33.02" y="33.02" length="middle" rot="R180"/>
<pin name="PB10" x="-40.64" y="-71.12" length="middle"/>
<pin name="PB11" x="-40.64" y="-73.66" length="middle"/>
<pin name="VCAP_1" x="-40.64" y="111.76" length="middle" direction="pwr"/>
<pin name="VDD@2" x="-40.64" y="83.82" length="middle" direction="pwr"/>
<pin name="PB12" x="-40.64" y="-76.2" length="middle"/>
<pin name="PB13" x="-40.64" y="-78.74" length="middle"/>
<pin name="PB14" x="-40.64" y="-81.28" length="middle"/>
<pin name="PB15" x="-40.64" y="-83.82" length="middle"/>
<pin name="PD8" x="33.02" y="93.98" length="middle" rot="R180"/>
<pin name="PD9" x="33.02" y="91.44" length="middle" rot="R180"/>
<pin name="PD10" x="33.02" y="88.9" length="middle" rot="R180"/>
<pin name="PD11" x="33.02" y="86.36" length="middle" rot="R180"/>
<pin name="PD12" x="33.02" y="83.82" length="middle" rot="R180"/>
<pin name="PD13" x="33.02" y="81.28" length="middle" rot="R180"/>
<pin name="PD14" x="33.02" y="78.74" length="middle" rot="R180"/>
<pin name="PD15" x="33.02" y="76.2" length="middle" rot="R180"/>
<pin name="PC6" x="-40.64" y="-104.14" length="middle"/>
<pin name="PC7" x="-40.64" y="-106.68" length="middle"/>
<pin name="PC8" x="-40.64" y="-109.22" length="middle"/>
<pin name="PC9" x="-40.64" y="-111.76" length="middle"/>
<pin name="PA8" x="-40.64" y="-38.1" length="middle"/>
<pin name="PA9" x="-40.64" y="-40.64" length="middle"/>
<pin name="PA10" x="-40.64" y="-43.18" length="middle"/>
<pin name="PA11" x="-40.64" y="-45.72" length="middle"/>
<pin name="PA12" x="-40.64" y="-48.26" length="middle"/>
<pin name="JTMS(PA13)" x="-40.64" y="0" length="middle"/>
<pin name="GND@1" x="-40.64" y="45.72" length="middle" direction="pwr"/>
<pin name="VDD@3" x="-40.64" y="81.28" length="middle" direction="pwr"/>
<pin name="JTCK(PA14)" x="-40.64" y="-2.54" length="middle"/>
<pin name="JTDI(PA15)" x="-40.64" y="-5.08" length="middle"/>
<pin name="PC10" x="-40.64" y="-114.3" length="middle"/>
<pin name="PC11" x="-40.64" y="-116.84" length="middle"/>
<pin name="PC12" x="-40.64" y="-119.38" length="middle"/>
<pin name="PD0" x="33.02" y="114.3" length="middle" rot="R180"/>
<pin name="PD1" x="33.02" y="111.76" length="middle" rot="R180"/>
<pin name="PD2" x="33.02" y="109.22" length="middle" rot="R180"/>
<pin name="PD3" x="33.02" y="106.68" length="middle" rot="R180"/>
<pin name="PD4" x="33.02" y="104.14" length="middle" rot="R180"/>
<pin name="PD5" x="33.02" y="101.6" length="middle" rot="R180"/>
<pin name="PD6" x="33.02" y="99.06" length="middle" rot="R180"/>
<pin name="PD7" x="33.02" y="96.52" length="middle" rot="R180"/>
<pin name="JTDO(PB3)" x="-40.64" y="-10.16" length="middle"/>
<pin name="NJTRST(PB4)" x="-40.64" y="-7.62" length="middle"/>
<pin name="PB5" x="-40.64" y="-58.42" length="middle"/>
<pin name="PB6" x="-40.64" y="-60.96" length="middle"/>
<pin name="PB7" x="-40.64" y="-63.5" length="middle"/>
<pin name="BOOT_0" x="-40.64" y="7.62" length="middle" direction="in"/>
<pin name="PB8" x="-40.64" y="-66.04" length="middle"/>
<pin name="PB9" x="-40.64" y="-68.58" length="middle"/>
<pin name="PE0" x="33.02" y="71.12" length="middle" rot="R180"/>
<pin name="PE1" x="33.02" y="68.58" length="middle" rot="R180"/>
<pin name="GND@2" x="-40.64" y="43.18" length="middle" direction="pwr"/>
<pin name="VDD@4" x="-40.64" y="78.74" length="middle" direction="pwr"/>
<pin name="VCAP_2" x="-40.64" y="114.3" length="middle" direction="pwr"/>
<wire x1="-7.62" y1="-129.54" x2="-7.62" y2="116.84" width="0.1524" layer="94"/>
<wire x1="5.08" y1="116.84" x2="5.08" y2="-129.54" width="0.1524" layer="94"/>
<pin name="VDD@0" x="-40.64" y="88.9" length="middle" direction="pwr"/>
<pin name="VDD@7" x="-40.64" y="71.12" length="middle" direction="pwr"/>
<pin name="VDD@8" x="-40.64" y="68.58" length="middle" direction="pwr"/>
<pin name="VDD@9" x="-40.64" y="66.04" length="middle" direction="pwr"/>
<pin name="VDD@10" x="-40.64" y="63.5" length="middle" direction="pwr"/>
<pin name="VDD@11" x="-40.64" y="60.96" length="middle" direction="pwr"/>
<pin name="VDD@12" x="-40.64" y="58.42" length="middle" direction="pwr"/>
<pin name="VDD@13" x="-40.64" y="55.88" length="middle" direction="pwr"/>
<pin name="VDD@14" x="-40.64" y="53.34" length="middle" direction="pwr"/>
<pin name="GND@0" x="-40.64" y="48.26" length="middle" direction="pwr"/>
<pin name="GND@5" x="-40.64" y="35.56" length="middle" direction="pwr"/>
<pin name="GND@6" x="-40.64" y="33.02" length="middle" direction="pwr"/>
<pin name="GND@7" x="-40.64" y="30.48" length="middle" direction="pwr"/>
<pin name="GND@8" x="-40.64" y="27.94" length="middle" direction="pwr"/>
<pin name="GND@9" x="-40.64" y="25.4" length="middle" direction="pwr"/>
<pin name="GND@10" x="-40.64" y="22.86" length="middle" direction="pwr"/>
<pin name="GND@11" x="-40.64" y="20.32" length="middle" direction="pwr"/>
<pin name="PF0" x="33.02" y="27.94" length="middle" rot="R180"/>
<pin name="PF1" x="33.02" y="25.4" length="middle" rot="R180"/>
<pin name="PF2" x="33.02" y="22.86" length="middle" rot="R180"/>
<pin name="PF3" x="33.02" y="20.32" length="middle" rot="R180"/>
<pin name="PF4" x="33.02" y="17.78" length="middle" rot="R180"/>
<pin name="PF5" x="33.02" y="15.24" length="middle" rot="R180"/>
<pin name="PF6" x="33.02" y="12.7" length="middle" rot="R180"/>
<pin name="PF7" x="33.02" y="10.16" length="middle" rot="R180"/>
<pin name="PF8" x="33.02" y="7.62" length="middle" rot="R180"/>
<pin name="PF9" x="33.02" y="5.08" length="middle" rot="R180"/>
<pin name="PF10" x="33.02" y="2.54" length="middle" rot="R180"/>
<pin name="PF11" x="33.02" y="0" length="middle" rot="R180"/>
<pin name="PF12" x="33.02" y="-2.54" length="middle" rot="R180"/>
<pin name="PF13" x="33.02" y="-5.08" length="middle" rot="R180"/>
<pin name="PF14" x="33.02" y="-7.62" length="middle" rot="R180"/>
<pin name="PF15" x="33.02" y="-10.16" length="middle" rot="R180"/>
<pin name="PH0(OSC_IN)" x="-40.64" y="12.7" length="middle"/>
<pin name="PH1(OSC_OUT)" x="-40.64" y="15.24" length="middle"/>
<pin name="PH2" x="33.02" y="-58.42" length="middle" rot="R180"/>
<pin name="PH3" x="33.02" y="-60.96" length="middle" rot="R180"/>
<pin name="PH4" x="33.02" y="-63.5" length="middle" rot="R180"/>
<pin name="PH5" x="33.02" y="-66.04" length="middle" rot="R180"/>
<pin name="PH6" x="33.02" y="-68.58" length="middle" rot="R180"/>
<pin name="PH7" x="33.02" y="-71.12" length="middle" rot="R180"/>
<pin name="PH8" x="33.02" y="-73.66" length="middle" rot="R180"/>
<pin name="PH9" x="33.02" y="-76.2" length="middle" rot="R180"/>
<pin name="PH10" x="33.02" y="-78.74" length="middle" rot="R180"/>
<pin name="PH11" x="33.02" y="-81.28" length="middle" rot="R180"/>
<pin name="PH12" x="33.02" y="-83.82" length="middle" rot="R180"/>
<pin name="PH13" x="33.02" y="-86.36" length="middle" rot="R180"/>
<pin name="PH14" x="33.02" y="-88.9" length="middle" rot="R180"/>
<pin name="PH15" x="33.02" y="-91.44" length="middle" rot="R180"/>
<pin name="PI0" x="33.02" y="-96.52" length="middle" rot="R180"/>
<pin name="PI1" x="33.02" y="-99.06" length="middle" rot="R180"/>
<pin name="PI2" x="33.02" y="-101.6" length="middle" rot="R180"/>
<pin name="PI3" x="33.02" y="-104.14" length="middle" rot="R180"/>
<pin name="PI4" x="33.02" y="-106.68" length="middle" rot="R180"/>
<pin name="PI5" x="33.02" y="-109.22" length="middle" rot="R180"/>
<pin name="PI6" x="33.02" y="-111.76" length="middle" rot="R180"/>
<pin name="PI7" x="33.02" y="-114.3" length="middle" rot="R180"/>
<pin name="PI8" x="33.02" y="-116.84" length="middle" rot="R180"/>
<pin name="PI9" x="33.02" y="-119.38" length="middle" rot="R180"/>
<pin name="PI10" x="33.02" y="-121.92" length="middle" rot="R180"/>
<pin name="PI11" x="33.02" y="-124.46" length="middle" rot="R180"/>
<pin name="PG0" x="33.02" y="-15.24" length="middle" rot="R180"/>
<pin name="PG1" x="33.02" y="-17.78" length="middle" rot="R180"/>
<pin name="PG2" x="33.02" y="-20.32" length="middle" rot="R180"/>
<pin name="PG3" x="33.02" y="-22.86" length="middle" rot="R180"/>
<pin name="PG4" x="33.02" y="-25.4" length="middle" rot="R180"/>
<pin name="PG5" x="33.02" y="-27.94" length="middle" rot="R180"/>
<pin name="PG6" x="33.02" y="-30.48" length="middle" rot="R180"/>
<pin name="PG7" x="33.02" y="-33.02" length="middle" rot="R180"/>
<pin name="PG8" x="33.02" y="-35.56" length="middle" rot="R180"/>
<pin name="PG9" x="33.02" y="-38.1" length="middle" rot="R180"/>
<pin name="PG10" x="33.02" y="-40.64" length="middle" rot="R180"/>
<pin name="PG11" x="33.02" y="-43.18" length="middle" rot="R180"/>
<pin name="PG12" x="33.02" y="-45.72" length="middle" rot="R180"/>
<pin name="PG13" x="33.02" y="-48.26" length="middle" rot="R180"/>
<pin name="PG14" x="33.02" y="-50.8" length="middle" rot="R180"/>
<pin name="PG15" x="33.02" y="-53.34" length="middle" rot="R180"/>
<pin name="PDR_ON" x="-40.64" y="109.22" length="middle" direction="pwr"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="2X10" prefix="XP">
<description>Standard 10x2 JTAG header for ARM.</description>
<gates>
<gate name="G$1" symbol="M10X2" x="0" y="0"/>
</gates>
<devices>
<device name="-SHROUDED" package="PLD_2X10_SHROUDED">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-PSEUDO_SMD" package="PLD_2X10_PSEUDOSMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="2X5" prefix="XP">
<description>Standard 2x5 header.</description>
<gates>
<gate name="G$1" symbol="M05X2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="PLD_2X05_PSEUDOSMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BUTTON_6X3.5" prefix="S" uservalue="yes">
<description>&lt;b&gt;OMRON SWITCH&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="TS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BUTTON_6X3.5">
<connects>
<connect gate="1" pin="P" pad="P"/>
<connect gate="1" pin="S" pad="S"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="STAND-OFF" prefix="JP">
<description>&lt;b&gt;Stand Off&lt;/b&gt;&lt;p&gt;
This is the mechanical footprint for a #4 phillips button head screw. Use the keepout ring to avoid running the screw head into surrounding components. SKU : PRT-00447</description>
<gates>
<gate name="G$1" symbol="STAND-OFF" x="0" y="0"/>
</gates>
<devices>
<device name="" package="STAND-OFF">
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TIGHT" package="STAND-OFF-TIGHT">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PLS_2X32">
<gates>
<gate name="G$1" symbol="PLS_2X32" x="0" y="-10.16"/>
</gates>
<devices>
<device name="" package="PLS_2X32_PSEUDOSMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="21" pad="21"/>
<connect gate="G$1" pin="22" pad="22"/>
<connect gate="G$1" pin="23" pad="23"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="25" pad="25"/>
<connect gate="G$1" pin="26" pad="26"/>
<connect gate="G$1" pin="27" pad="27"/>
<connect gate="G$1" pin="28" pad="28"/>
<connect gate="G$1" pin="29" pad="29"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="30" pad="30"/>
<connect gate="G$1" pin="31" pad="31"/>
<connect gate="G$1" pin="32" pad="32"/>
<connect gate="G$1" pin="33" pad="33"/>
<connect gate="G$1" pin="34" pad="34"/>
<connect gate="G$1" pin="35" pad="35"/>
<connect gate="G$1" pin="36" pad="36"/>
<connect gate="G$1" pin="37" pad="37"/>
<connect gate="G$1" pin="38" pad="38"/>
<connect gate="G$1" pin="39" pad="39"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="40" pad="40"/>
<connect gate="G$1" pin="41" pad="41"/>
<connect gate="G$1" pin="42" pad="42"/>
<connect gate="G$1" pin="43" pad="43"/>
<connect gate="G$1" pin="44" pad="44"/>
<connect gate="G$1" pin="45" pad="45"/>
<connect gate="G$1" pin="46" pad="46"/>
<connect gate="G$1" pin="47" pad="47"/>
<connect gate="G$1" pin="48" pad="48"/>
<connect gate="G$1" pin="49" pad="49"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="50" pad="50"/>
<connect gate="G$1" pin="51" pad="51"/>
<connect gate="G$1" pin="52" pad="52"/>
<connect gate="G$1" pin="53" pad="53"/>
<connect gate="G$1" pin="54" pad="54"/>
<connect gate="G$1" pin="55" pad="55"/>
<connect gate="G$1" pin="56" pad="56"/>
<connect gate="G$1" pin="57" pad="57"/>
<connect gate="G$1" pin="58" pad="58"/>
<connect gate="G$1" pin="59" pad="59"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="60" pad="60"/>
<connect gate="G$1" pin="61" pad="61"/>
<connect gate="G$1" pin="62" pad="62"/>
<connect gate="G$1" pin="63" pad="63"/>
<connect gate="G$1" pin="64" pad="64"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="STM32F407I">
<gates>
<gate name="G$1" symbol="STM32F407I" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TQFP176">
<connects>
<connect gate="G$1" pin="BOOT_0" pad="166"/>
<connect gate="G$1" pin="BOOT_1(PB2)" pad="58"/>
<connect gate="G$1" pin="GND@0" pad="14"/>
<connect gate="G$1" pin="GND@1" pad="22"/>
<connect gate="G$1" pin="GND@10" pad="148"/>
<connect gate="G$1" pin="GND@11" pad="158"/>
<connect gate="G$1" pin="GND@2" pad="48"/>
<connect gate="G$1" pin="GND@3" pad="61"/>
<connect gate="G$1" pin="GND@4" pad="71"/>
<connect gate="G$1" pin="GND@5" pad="90"/>
<connect gate="G$1" pin="GND@6" pad="102"/>
<connect gate="G$1" pin="GND@7" pad="113"/>
<connect gate="G$1" pin="GND@8" pad="126"/>
<connect gate="G$1" pin="GND@9" pad="135"/>
<connect gate="G$1" pin="GND_A" pad="37"/>
<connect gate="G$1" pin="JTCK(PA14)" pad="137"/>
<connect gate="G$1" pin="JTDI(PA15)" pad="138"/>
<connect gate="G$1" pin="JTDO(PB3)" pad="161"/>
<connect gate="G$1" pin="JTMS(PA13)" pad="124"/>
<connect gate="G$1" pin="NJTRST(PB4)" pad="162"/>
<connect gate="G$1" pin="NRST" pad="31"/>
<connect gate="G$1" pin="PA0" pad="40"/>
<connect gate="G$1" pin="PA1" pad="41"/>
<connect gate="G$1" pin="PA10" pad="121"/>
<connect gate="G$1" pin="PA11" pad="122"/>
<connect gate="G$1" pin="PA12" pad="123"/>
<connect gate="G$1" pin="PA2" pad="42"/>
<connect gate="G$1" pin="PA3" pad="47"/>
<connect gate="G$1" pin="PA4" pad="50"/>
<connect gate="G$1" pin="PA5" pad="51"/>
<connect gate="G$1" pin="PA6" pad="52"/>
<connect gate="G$1" pin="PA7" pad="53"/>
<connect gate="G$1" pin="PA8" pad="119"/>
<connect gate="G$1" pin="PA9" pad="120"/>
<connect gate="G$1" pin="PB0" pad="56"/>
<connect gate="G$1" pin="PB1" pad="57"/>
<connect gate="G$1" pin="PB10" pad="79"/>
<connect gate="G$1" pin="PB11" pad="80"/>
<connect gate="G$1" pin="PB12" pad="92"/>
<connect gate="G$1" pin="PB13" pad="93"/>
<connect gate="G$1" pin="PB14" pad="94"/>
<connect gate="G$1" pin="PB15" pad="95"/>
<connect gate="G$1" pin="PB5" pad="163"/>
<connect gate="G$1" pin="PB6" pad="164"/>
<connect gate="G$1" pin="PB7" pad="165"/>
<connect gate="G$1" pin="PB8" pad="167"/>
<connect gate="G$1" pin="PB9" pad="168"/>
<connect gate="G$1" pin="PC0" pad="32"/>
<connect gate="G$1" pin="PC1" pad="33"/>
<connect gate="G$1" pin="PC10" pad="139"/>
<connect gate="G$1" pin="PC11" pad="140"/>
<connect gate="G$1" pin="PC12" pad="141"/>
<connect gate="G$1" pin="PC13(TAMPER-RTC)" pad="8"/>
<connect gate="G$1" pin="PC14(OSC32_IN)" pad="9"/>
<connect gate="G$1" pin="PC15(OSC32_OUT)" pad="10"/>
<connect gate="G$1" pin="PC2" pad="34"/>
<connect gate="G$1" pin="PC3" pad="35"/>
<connect gate="G$1" pin="PC4" pad="54"/>
<connect gate="G$1" pin="PC5" pad="55"/>
<connect gate="G$1" pin="PC6" pad="115"/>
<connect gate="G$1" pin="PC7" pad="116"/>
<connect gate="G$1" pin="PC8" pad="117"/>
<connect gate="G$1" pin="PC9" pad="118"/>
<connect gate="G$1" pin="PD0" pad="142"/>
<connect gate="G$1" pin="PD1" pad="143"/>
<connect gate="G$1" pin="PD10" pad="98"/>
<connect gate="G$1" pin="PD11" pad="99"/>
<connect gate="G$1" pin="PD12" pad="100"/>
<connect gate="G$1" pin="PD13" pad="101"/>
<connect gate="G$1" pin="PD14" pad="104"/>
<connect gate="G$1" pin="PD15" pad="105"/>
<connect gate="G$1" pin="PD2" pad="144"/>
<connect gate="G$1" pin="PD3" pad="145"/>
<connect gate="G$1" pin="PD4" pad="146"/>
<connect gate="G$1" pin="PD5" pad="147"/>
<connect gate="G$1" pin="PD6" pad="150"/>
<connect gate="G$1" pin="PD7" pad="151"/>
<connect gate="G$1" pin="PD8" pad="96"/>
<connect gate="G$1" pin="PD9" pad="97"/>
<connect gate="G$1" pin="PDR_ON" pad="171"/>
<connect gate="G$1" pin="PE0" pad="169"/>
<connect gate="G$1" pin="PE1" pad="170"/>
<connect gate="G$1" pin="PE10" pad="73"/>
<connect gate="G$1" pin="PE11" pad="74"/>
<connect gate="G$1" pin="PE12" pad="75"/>
<connect gate="G$1" pin="PE13" pad="76"/>
<connect gate="G$1" pin="PE14" pad="77"/>
<connect gate="G$1" pin="PE15" pad="78"/>
<connect gate="G$1" pin="PE2" pad="1"/>
<connect gate="G$1" pin="PE3" pad="2"/>
<connect gate="G$1" pin="PE4" pad="3"/>
<connect gate="G$1" pin="PE5" pad="4"/>
<connect gate="G$1" pin="PE6" pad="5"/>
<connect gate="G$1" pin="PE7" pad="68"/>
<connect gate="G$1" pin="PE8" pad="69"/>
<connect gate="G$1" pin="PE9" pad="70"/>
<connect gate="G$1" pin="PF0" pad="16"/>
<connect gate="G$1" pin="PF1" pad="17"/>
<connect gate="G$1" pin="PF10" pad="28"/>
<connect gate="G$1" pin="PF11" pad="59"/>
<connect gate="G$1" pin="PF12" pad="60"/>
<connect gate="G$1" pin="PF13" pad="63"/>
<connect gate="G$1" pin="PF14" pad="64"/>
<connect gate="G$1" pin="PF15" pad="65"/>
<connect gate="G$1" pin="PF2" pad="18"/>
<connect gate="G$1" pin="PF3" pad="19"/>
<connect gate="G$1" pin="PF4" pad="20"/>
<connect gate="G$1" pin="PF5" pad="21"/>
<connect gate="G$1" pin="PF6" pad="24"/>
<connect gate="G$1" pin="PF7" pad="25"/>
<connect gate="G$1" pin="PF8" pad="26"/>
<connect gate="G$1" pin="PF9" pad="27"/>
<connect gate="G$1" pin="PG0" pad="66"/>
<connect gate="G$1" pin="PG1" pad="67"/>
<connect gate="G$1" pin="PG10" pad="153"/>
<connect gate="G$1" pin="PG11" pad="154"/>
<connect gate="G$1" pin="PG12" pad="155"/>
<connect gate="G$1" pin="PG13" pad="156"/>
<connect gate="G$1" pin="PG14" pad="157"/>
<connect gate="G$1" pin="PG15" pad="160"/>
<connect gate="G$1" pin="PG2" pad="106"/>
<connect gate="G$1" pin="PG3" pad="107"/>
<connect gate="G$1" pin="PG4" pad="108"/>
<connect gate="G$1" pin="PG5" pad="109"/>
<connect gate="G$1" pin="PG6" pad="110"/>
<connect gate="G$1" pin="PG7" pad="111"/>
<connect gate="G$1" pin="PG8" pad="112"/>
<connect gate="G$1" pin="PG9" pad="152"/>
<connect gate="G$1" pin="PH0(OSC_IN)" pad="29"/>
<connect gate="G$1" pin="PH1(OSC_OUT)" pad="30"/>
<connect gate="G$1" pin="PH10" pad="87"/>
<connect gate="G$1" pin="PH11" pad="88"/>
<connect gate="G$1" pin="PH12" pad="89"/>
<connect gate="G$1" pin="PH13" pad="128"/>
<connect gate="G$1" pin="PH14" pad="129"/>
<connect gate="G$1" pin="PH15" pad="130"/>
<connect gate="G$1" pin="PH2" pad="43"/>
<connect gate="G$1" pin="PH3" pad="44"/>
<connect gate="G$1" pin="PH4" pad="45"/>
<connect gate="G$1" pin="PH5" pad="46"/>
<connect gate="G$1" pin="PH6" pad="83"/>
<connect gate="G$1" pin="PH7" pad="84"/>
<connect gate="G$1" pin="PH8" pad="85"/>
<connect gate="G$1" pin="PH9" pad="86"/>
<connect gate="G$1" pin="PI0" pad="131"/>
<connect gate="G$1" pin="PI1" pad="132"/>
<connect gate="G$1" pin="PI10" pad="12"/>
<connect gate="G$1" pin="PI11" pad="13"/>
<connect gate="G$1" pin="PI2" pad="133"/>
<connect gate="G$1" pin="PI3" pad="134"/>
<connect gate="G$1" pin="PI4" pad="173"/>
<connect gate="G$1" pin="PI5" pad="174"/>
<connect gate="G$1" pin="PI6" pad="175"/>
<connect gate="G$1" pin="PI7" pad="176"/>
<connect gate="G$1" pin="PI8" pad="7"/>
<connect gate="G$1" pin="PI9" pad="11"/>
<connect gate="G$1" pin="VCAP_1" pad="81"/>
<connect gate="G$1" pin="VCAP_2" pad="125"/>
<connect gate="G$1" pin="VDD@0" pad="15"/>
<connect gate="G$1" pin="VDD@1" pad="23"/>
<connect gate="G$1" pin="VDD@10" pad="127"/>
<connect gate="G$1" pin="VDD@11" pad="136"/>
<connect gate="G$1" pin="VDD@12" pad="149"/>
<connect gate="G$1" pin="VDD@13" pad="159"/>
<connect gate="G$1" pin="VDD@14" pad="172"/>
<connect gate="G$1" pin="VDD@2" pad="36"/>
<connect gate="G$1" pin="VDD@3" pad="49"/>
<connect gate="G$1" pin="VDD@4" pad="62"/>
<connect gate="G$1" pin="VDD@5" pad="72"/>
<connect gate="G$1" pin="VDD@6" pad="82"/>
<connect gate="G$1" pin="VDD@7" pad="91"/>
<connect gate="G$1" pin="VDD@8" pad="103"/>
<connect gate="G$1" pin="VDD@9" pad="114"/>
<connect gate="G$1" pin="VDD_A" pad="39"/>
<connect gate="G$1" pin="VREF+" pad="38"/>
<connect gate="G$1" pin="V_BAT" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun">
<packages>
<package name="EIA3216">
<wire x1="-1" y1="-1.2" x2="-2.5" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-1.2" x2="-2.5" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="-1.2" x2="2.5" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-0.8" x2="2.5" y2="0.8" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.8" x2="2.1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.1" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="0.381" y1="1.016" x2="0.381" y2="-1.016" width="0.127" layer="21"/>
<smd name="C" x="-1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<smd name="A" x="1.4" y="0" dx="1.6" dy="1.4" layer="1" rot="R90"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3528">
<wire x1="-0.9" y1="-1.6" x2="-2.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-1.6" x2="-2.6" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.2" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="-1.55" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="2.6" y2="1.25" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.25" x2="2.2" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="0.609" y1="1.311" x2="0.609" y2="-1.286" width="0.2032" layer="21" style="longdash"/>
<smd name="C" x="-1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<smd name="A" x="1.65" y="0" dx="2.5" dy="1.2" layer="1" rot="R90"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="CPOL-RADIAL-100UF-25V">
<wire x1="-0.635" y1="1.27" x2="-1.905" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="3.25" width="0.2032" layer="21"/>
<pad name="2" x="-1.27" y="0" drill="0.7" diameter="1.651"/>
<pad name="1" x="1.27" y="0" drill="0.7" diameter="1.651" shape="square"/>
<text x="-1.905" y="-4.318" size="0.8128" layer="27">&gt;Value</text>
<text x="-0.762" y="1.651" size="0.4064" layer="25">&gt;Name</text>
</package>
<package name="CPOL-RADIAL-10UF-25V">
<wire x1="-0.762" y1="1.397" x2="-1.778" y2="1.397" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="2.5" width="0.2032" layer="21"/>
<pad name="1" x="1.27" y="0" drill="0.7" diameter="1.651" shape="square"/>
<pad name="2" x="-1.27" y="0" drill="0.7" diameter="1.651"/>
<text x="-0.889" y="1.524" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.905" y="-3.683" size="0.8128" layer="27">&gt;Value</text>
</package>
<package name="EIA7343">
<wire x1="-5" y1="2.5" x2="-2" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="2.5" x2="-5" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="-5" y1="-2.5" x2="-2" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="2" y1="2.5" x2="4" y2="2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="2.5" x2="5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="1.5" x2="5" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="5" y1="-1.5" x2="4" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="-2.5" x2="2" y2="-2.5" width="0.2032" layer="21"/>
<smd name="C" x="-3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<smd name="A" x="3.17" y="0" dx="2.55" dy="2.7" layer="1" rot="R180"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="-1.27" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="PANASONIC_G">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package G&lt;/b&gt;</description>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="-2.8" width="0.1016" layer="51"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="5.1" width="0.1016" layer="51"/>
<wire x1="-5.1" y1="1" x2="-5.1" y2="5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="5.1" x2="2.8" y2="5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="5.1" x2="5.1" y2="2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="2.8" x2="5.1" y2="1" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-1" x2="5.1" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="5.1" y1="-2.8" x2="2.8" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="2.8" y1="-5.1" x2="-5.1" y2="-5.1" width="0.2032" layer="21"/>
<wire x1="-5.1" y1="-5.1" x2="-5.1" y2="-1" width="0.2032" layer="21"/>
<wire x1="-4.85" y1="-1" x2="4.85" y2="-1" width="0.2032" layer="21" curve="156.699401" cap="flat"/>
<wire x1="-4.85" y1="1" x2="4.85" y2="1" width="0.2032" layer="21" curve="-156.699401" cap="flat"/>
<wire x1="-3.25" y1="3.7" x2="-3.25" y2="-3.65" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="4.95" width="0.1016" layer="51"/>
<smd name="-" x="-4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<smd name="+" x="4.25" y="0" dx="3.9" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-5.85" y1="-0.45" x2="-4.9" y2="0.45" layer="51"/>
<rectangle x1="4.9" y1="-0.45" x2="5.85" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-3.3" y="3.6"/>
<vertex x="-4.05" y="2.75"/>
<vertex x="-4.65" y="1.55"/>
<vertex x="-4.85" y="0.45"/>
<vertex x="-4.85" y="-0.45"/>
<vertex x="-4.65" y="-1.55"/>
<vertex x="-4.05" y="-2.75"/>
<vertex x="-3.3" y="-3.6"/>
<vertex x="-3.3" y="3.55"/>
</polygon>
</package>
<package name="PANASONIC_E">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="-1.8" width="0.1016" layer="51"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="4.1" width="0.1016" layer="51"/>
<wire x1="-4.1" y1="0.9" x2="-4.1" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="4.1" x2="1.8" y2="4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="4.1" x2="4.1" y2="1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="1.8" x2="4.1" y2="0.9" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-0.9" x2="4.1" y2="-1.8" width="0.2032" layer="21"/>
<wire x1="4.1" y1="-1.8" x2="1.8" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="1.8" y1="-4.1" x2="-4.1" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="-4.1" x2="-4.1" y2="-0.9" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="3.25" x2="-2.2" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.85" y1="0.9" x2="3.85" y2="0.9" width="0.2032" layer="21" curve="-153.684915" cap="flat"/>
<wire x1="-3.85" y1="-0.9" x2="3.85" y2="-0.9" width="0.2032" layer="21" curve="153.684915" cap="flat"/>
<circle x="0" y="0" radius="3.95" width="0.1016" layer="51"/>
<smd name="-" x="-3" y="0" dx="3.8" dy="1.4" layer="1"/>
<smd name="+" x="3" y="0" dx="3.8" dy="1.4" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-4.5" y1="-0.35" x2="-3.8" y2="0.35" layer="51"/>
<rectangle x1="3.8" y1="-0.35" x2="4.5" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.25" y="3.2"/>
<vertex x="-3" y="2.5"/>
<vertex x="-3.6" y="1.5"/>
<vertex x="-3.85" y="0.65"/>
<vertex x="-3.85" y="-0.65"/>
<vertex x="-3.55" y="-1.6"/>
<vertex x="-2.95" y="-2.55"/>
<vertex x="-2.25" y="-3.2"/>
<vertex x="-2.25" y="3.15"/>
</polygon>
</package>
<package name="PANASONIC_C">
<description>&lt;b&gt;Panasonic Aluminium Electrolytic Capacitor VS-Serie Package E&lt;/b&gt;</description>
<wire x1="-2.6" y1="2.45" x2="1.6" y2="2.45" width="0.2032" layer="21"/>
<wire x1="1.6" y1="2.45" x2="2.7" y2="1.35" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.75" x2="1.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="1.6" y1="-2.85" x2="-2.6" y2="-2.85" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2.45" x2="1.6" y2="2.45" width="0.1016" layer="51"/>
<wire x1="1.6" y1="2.45" x2="2.7" y2="1.35" width="0.1016" layer="51"/>
<wire x1="2.7" y1="-1.75" x2="1.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="1.6" y1="-2.85" x2="-2.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="-2.6" y1="2.45" x2="-2.6" y2="0.35" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="-2.85" x2="-2.6" y2="-0.75" width="0.2032" layer="21"/>
<wire x1="2.7" y1="1.35" x2="2.7" y2="0.35" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.75" x2="2.7" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="-2.6" y1="2.45" x2="-2.6" y2="-2.85" width="0.1016" layer="51"/>
<wire x1="2.7" y1="1.35" x2="2.7" y2="-1.75" width="0.1016" layer="51"/>
<wire x1="-2.4" y1="0.35" x2="2.45" y2="0.3" width="0.2032" layer="21" curve="-156.699401"/>
<wire x1="2.5" y1="-0.7" x2="-2.4" y2="-0.75" width="0.2032" layer="21" curve="-154.694887"/>
<circle x="0.05" y="-0.2" radius="2.5004" width="0.1016" layer="51"/>
<smd name="-" x="-1.8" y="-0.2" dx="2.2" dy="0.65" layer="1"/>
<smd name="+" x="1.9" y="-0.2" dx="2.2" dy="0.65" layer="1"/>
<text x="-2.6" y="2.7" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.6" y="-3.45" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="NIPPON_F80">
<wire x1="-3.3" y1="3.3" x2="1.7" y2="3.3" width="0.2032" layer="21"/>
<wire x1="1.7" y1="3.3" x2="3.3" y2="2" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2" x2="1.7" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="1.7" y1="-3.3" x2="-3.3" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3.3" x2="1.7" y2="3.3" width="0.1016" layer="51"/>
<wire x1="1.7" y1="3.3" x2="3.3" y2="2" width="0.1016" layer="51"/>
<wire x1="3.3" y1="-2" x2="1.7" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="1.7" y1="-3.3" x2="-3.3" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="-3.3" y1="3.3" x2="-3.3" y2="0.685" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="-3.3" x2="-3.3" y2="-0.685" width="0.2032" layer="21"/>
<wire x1="3.3" y1="2" x2="3.3" y2="0.685" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2" x2="3.3" y2="-0.685" width="0.2032" layer="21"/>
<wire x1="-3.3" y1="3.3" x2="-3.3" y2="-3.3" width="0.1016" layer="51"/>
<wire x1="3.3" y1="2" x2="3.3" y2="-2" width="0.1016" layer="51"/>
<wire x1="-3.1" y1="0.685" x2="3.1" y2="0.685" width="0.2032" layer="21" curve="-156.500033"/>
<wire x1="3.1" y1="-0.685" x2="-3.1" y2="-0.685" width="0.2032" layer="21" curve="-154.748326"/>
<circle x="0" y="0" radius="3.15" width="0.1016" layer="51"/>
<smd name="-" x="-2.4" y="0" dx="2.95" dy="1" layer="1"/>
<smd name="+" x="2.4" y="0" dx="2.95" dy="1" layer="1"/>
<text x="-3.2" y="3.5" size="0.4064" layer="25">&gt;NAME</text>
<text x="-3.2" y="-3.85" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="PANASONIC_D">
<wire x1="-3.25" y1="3.25" x2="1.55" y2="3.25" width="0.1016" layer="51"/>
<wire x1="1.55" y1="3.25" x2="3.25" y2="1.55" width="0.1016" layer="51"/>
<wire x1="3.25" y1="1.55" x2="3.25" y2="-1.55" width="0.1016" layer="51"/>
<wire x1="3.25" y1="-1.55" x2="1.55" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="1.55" y1="-3.25" x2="-3.25" y2="-3.25" width="0.1016" layer="51"/>
<wire x1="-3.25" y1="-3.25" x2="-3.25" y2="3.25" width="0.1016" layer="51"/>
<wire x1="-3.25" y1="0.95" x2="-3.25" y2="3.25" width="0.1016" layer="21"/>
<wire x1="-3.25" y1="3.25" x2="1.55" y2="3.25" width="0.1016" layer="21"/>
<wire x1="1.55" y1="3.25" x2="3.25" y2="1.55" width="0.1016" layer="21"/>
<wire x1="3.25" y1="1.55" x2="3.25" y2="0.95" width="0.1016" layer="21"/>
<wire x1="3.25" y1="-0.95" x2="3.25" y2="-1.55" width="0.1016" layer="21"/>
<wire x1="3.25" y1="-1.55" x2="1.55" y2="-3.25" width="0.1016" layer="21"/>
<wire x1="1.55" y1="-3.25" x2="-3.25" y2="-3.25" width="0.1016" layer="21"/>
<wire x1="-3.25" y1="-3.25" x2="-3.25" y2="-0.95" width="0.1016" layer="21"/>
<wire x1="2.95" y1="0.95" x2="-2.95" y2="0.95" width="0.1016" layer="21" curve="144.299363"/>
<wire x1="-2.95" y1="-0.95" x2="2.95" y2="-0.95" width="0.1016" layer="21" curve="144.299363"/>
<wire x1="-2.1" y1="2.25" x2="-2.1" y2="-2.2" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="3.1" width="0.1016" layer="51"/>
<smd name="+" x="2.4" y="0" dx="3" dy="1.4" layer="1"/>
<smd name="-" x="-2.4" y="0" dx="3" dy="1.4" layer="1"/>
<text x="-1.75" y="1" size="1.016" layer="25">&gt;NAME</text>
<text x="-1.75" y="-1.975" size="1.016" layer="27">&gt;VALUE</text>
<rectangle x1="-3.65" y1="-0.35" x2="-3.05" y2="0.35" layer="51"/>
<rectangle x1="3.05" y1="-0.35" x2="3.65" y2="0.35" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-2.15" y="2.15"/>
<vertex x="-2.6" y="1.6"/>
<vertex x="-2.9" y="0.9"/>
<vertex x="-3.05" y="0"/>
<vertex x="-2.9" y="-0.95"/>
<vertex x="-2.55" y="-1.65"/>
<vertex x="-2.15" y="-2.15"/>
<vertex x="-2.15" y="2.1"/>
</polygon>
</package>
<package name="CPOL-RADIAL-1000UF-63V">
<wire x1="-3.175" y1="1.905" x2="-4.445" y2="1.905" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="8.001" width="0.2032" layer="21"/>
<pad name="2" x="-3.81" y="0" drill="1.016" diameter="1.6764"/>
<pad name="1" x="3.81" y="0" drill="1.016" diameter="1.651" shape="square"/>
<text x="-2.54" y="8.89" size="0.8128" layer="27">&gt;Value</text>
<text x="-2.54" y="10.16" size="0.8128" layer="25">&gt;Name</text>
</package>
<package name="CPOL-RADIAL-1000UF-25V">
<wire x1="-1.905" y1="1.27" x2="-3.175" y2="1.27" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="5.461" width="0.2032" layer="21"/>
<pad name="2" x="-2.54" y="0" drill="0.7" diameter="1.651"/>
<pad name="1" x="2.54" y="0" drill="0.7" diameter="1.651" shape="square"/>
<text x="-1.905" y="-4.318" size="0.8128" layer="27">&gt;Value</text>
<text x="-0.762" y="2.921" size="0.4064" layer="25">&gt;Name</text>
</package>
<package name="VISHAY_C">
<wire x1="0" y1="1.27" x2="0" y2="1.905" width="0.254" layer="21"/>
<wire x1="-2.0574" y1="4.2926" x2="-2.0574" y2="-4.2926" width="0.127" layer="21"/>
<wire x1="-2.0574" y1="-4.2926" x2="2.0574" y2="-4.2926" width="0.127" layer="21"/>
<wire x1="2.0574" y1="-4.2926" x2="2.0574" y2="4.2926" width="0.127" layer="21"/>
<wire x1="2.0574" y1="4.2926" x2="-2.0574" y2="4.2926" width="0.127" layer="21"/>
<smd name="+" x="0" y="3.048" dx="3.556" dy="1.778" layer="1"/>
<smd name="-" x="0" y="-3.048" dx="3.556" dy="1.778" layer="1"/>
<text x="-1.905" y="4.445" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.905" y="-5.08" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="PANASONIC_H13">
<wire x1="-6.75" y1="6.75" x2="4" y2="6.75" width="0.1016" layer="51"/>
<wire x1="4" y1="6.75" x2="6.75" y2="4" width="0.1016" layer="51"/>
<wire x1="6.75" y1="4" x2="6.75" y2="-4" width="0.1016" layer="51"/>
<wire x1="6.75" y1="-4" x2="4" y2="-6.75" width="0.1016" layer="51"/>
<wire x1="4" y1="-6.75" x2="-6.75" y2="-6.75" width="0.1016" layer="51"/>
<wire x1="-6.75" y1="-6.75" x2="-6.75" y2="6.75" width="0.1016" layer="51"/>
<wire x1="-6.75" y1="1" x2="-6.75" y2="6.75" width="0.2032" layer="21"/>
<wire x1="-6.75" y1="6.75" x2="4" y2="6.75" width="0.2032" layer="21"/>
<wire x1="4" y1="6.75" x2="6.75" y2="4" width="0.2032" layer="21"/>
<wire x1="6.75" y1="4" x2="6.75" y2="1" width="0.2032" layer="21"/>
<wire x1="6.75" y1="-1" x2="6.75" y2="-4" width="0.2032" layer="21"/>
<wire x1="6.75" y1="-4" x2="4" y2="-6.75" width="0.2032" layer="21"/>
<wire x1="4" y1="-6.75" x2="-6.75" y2="-6.75" width="0.2032" layer="21"/>
<wire x1="-6.75" y1="-6.75" x2="-6.75" y2="-1" width="0.2032" layer="21"/>
<wire x1="-6.55" y1="-1.2" x2="6.45" y2="-1.2" width="0.2032" layer="21" curve="156.692742" cap="flat"/>
<wire x1="-6.55" y1="1.2" x2="6.55" y2="1.2" width="0.2032" layer="21" curve="-156.697982" cap="flat"/>
<wire x1="-5" y1="4.25" x2="-4.95" y2="-4.35" width="0.1016" layer="51"/>
<circle x="0" y="0" radius="6.6" width="0.1016" layer="51"/>
<smd name="-" x="-4.7" y="0" dx="5" dy="1.6" layer="1"/>
<smd name="+" x="4.7" y="0" dx="5" dy="1.6" layer="1"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-7.55" y1="-0.45" x2="-6.6" y2="0.45" layer="51"/>
<rectangle x1="6.6" y1="-0.45" x2="7.55" y2="0.45" layer="51"/>
<polygon width="0.1016" layer="51">
<vertex x="-5" y="4.2"/>
<vertex x="-5.75" y="3.15"/>
<vertex x="-6.25" y="2.05"/>
<vertex x="-6.55" y="0.45"/>
<vertex x="-6.55" y="-0.45"/>
<vertex x="-6.35" y="-1.65"/>
<vertex x="-5.75" y="-3.25"/>
<vertex x="-5" y="-4.2"/>
</polygon>
</package>
<package name="EIA6032">
<wire x1="3.2" y1="-1.6" x2="3.2" y2="1.6" width="0.127" layer="21"/>
<wire x1="-2.8" y1="-1.6" x2="3.2" y2="-1.6" width="0.127" layer="21"/>
<wire x1="3.2" y1="1.6" x2="-2.8" y2="1.6" width="0.127" layer="21"/>
<wire x1="-2.8" y1="1.6" x2="-3.4" y2="1" width="0.127" layer="21"/>
<wire x1="-3.4" y1="1" x2="-3.4" y2="-1" width="0.127" layer="21"/>
<wire x1="-2.8" y1="-1.6" x2="-3.4" y2="-1" width="0.127" layer="21"/>
<smd name="P$1" x="-2.3" y="0" dx="1.5" dy="2.4" layer="1"/>
<smd name="P$2" x="2.3" y="0" dx="1.5" dy="2.4" layer="1"/>
</package>
<package name="EN_J2">
<description>Type J2 package for SMD supercap PRT-10317 (p# EEC-EN0F204J2)</description>
<wire x1="-2.5" y1="-3.5" x2="2.5" y2="-3.5" width="0.127" layer="51"/>
<wire x1="-2.1" y1="3.5" x2="2.1" y2="3.5" width="0.127" layer="51"/>
<wire x1="-2.1" y1="3.5" x2="-2.5" y2="3.1" width="0.127" layer="51"/>
<wire x1="-2.5" y1="3.1" x2="-2.5" y2="2.3" width="0.127" layer="51"/>
<wire x1="2.1" y1="3.5" x2="2.5" y2="3.1" width="0.127" layer="51"/>
<wire x1="2.5" y1="3.1" x2="2.5" y2="2.3" width="0.127" layer="51"/>
<wire x1="-2.5" y1="-3.5" x2="-2.5" y2="-2.3" width="0.127" layer="51"/>
<wire x1="2.5" y1="-3.5" x2="2.5" y2="-2.3" width="0.127" layer="51"/>
<wire x1="-2.5908" y1="-2.413" x2="-2.5654" y2="2.4384" width="0.127" layer="21" curve="-91.212564"/>
<wire x1="2.5908" y1="-2.413" x2="2.5654" y2="2.4384" width="0.127" layer="21" curve="86.79344"/>
<wire x1="1.7272" y1="-1.27" x2="1.7272" y2="-2.0828" width="0.127" layer="21"/>
<wire x1="1.3462" y1="-1.6764" x2="2.159" y2="-1.6764" width="0.127" layer="21"/>
<circle x="0" y="0" radius="3.4" width="0.127" layer="51"/>
<smd name="-" x="0" y="2.8" dx="5" dy="2.4" layer="1"/>
<smd name="+" x="0" y="-3.2" dx="5" dy="1.6" layer="1"/>
<text x="-2.28" y="0.66" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.31" y="-1.21" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="EIA3216-KIT">
<description>&lt;h3&gt;EIA3216-KIT&lt;/h3&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has longer pads to make hand soldering easier.&lt;br&gt;</description>
<wire x1="-1" y1="-1.2" x2="-3" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="-1.2" x2="-3" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="1.2" x2="-1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.2" x2="2.6" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="-1.2" x2="3" y2="-0.8" width="0.2032" layer="21"/>
<wire x1="3" y1="-0.8" x2="3" y2="0.8" width="0.2032" layer="21"/>
<wire x1="3" y1="0.8" x2="2.6" y2="1.2" width="0.2032" layer="21"/>
<wire x1="2.6" y1="1.2" x2="1" y2="1.2" width="0.2032" layer="21"/>
<wire x1="0.381" y1="1.016" x2="0.381" y2="-1.016" width="0.127" layer="21"/>
<smd name="C" x="-1.65" y="0" dx="1.9" dy="1.6" layer="1"/>
<smd name="A" x="1.65" y="0" dx="1.9" dy="1.6" layer="1"/>
<text x="-2.54" y="1.381" size="0.4064" layer="25">&gt;NAME</text>
<text x="0.408" y="1.332" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1210">
<wire x1="-1.6" y1="1.3" x2="1.6" y2="1.3" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.3" x2="1.6" y2="-1.3" width="0.127" layer="51"/>
<wire x1="1.6" y1="-1.3" x2="-1.6" y2="-1.3" width="0.127" layer="51"/>
<wire x1="-1.6" y1="-1.3" x2="-1.6" y2="1.3" width="0.127" layer="51"/>
<wire x1="-1.6" y1="1.3" x2="1.6" y2="1.3" width="0.2032" layer="21"/>
<wire x1="-1.6" y1="-1.3" x2="1.6" y2="-1.3" width="0.2032" layer="21"/>
<smd name="1" x="-1.6" y="0" dx="1.2" dy="2" layer="1"/>
<smd name="2" x="1.6" y="0" dx="1.2" dy="2" layer="1"/>
<text x="-0.8" y="0.5" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.9" y="-0.7" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="0805">
<wire x1="-0.3" y1="0.6" x2="0.3" y2="0.6" width="0.1524" layer="21"/>
<wire x1="-0.3" y1="-0.6" x2="0.3" y2="-0.6" width="0.1524" layer="21"/>
<smd name="1" x="-0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<smd name="2" x="0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<text x="-0.762" y="0.8255" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="USB-A-H">
<description>&lt;b&gt;USB Series A Hole Mounted&lt;/b&gt;</description>
<wire x1="-17.8" y1="6" x2="-17.8" y2="-6" width="0.2032" layer="51"/>
<wire x1="-3" y1="6" x2="-3" y2="-6" width="0.2032" layer="21"/>
<wire x1="-3" y1="6" x2="-17.8" y2="6" width="0.2032" layer="51"/>
<wire x1="-3" y1="-6" x2="-17.8" y2="-6" width="0.2032" layer="51"/>
<wire x1="-3" y1="6" x2="-2" y2="6" width="0.2032" layer="21"/>
<wire x1="-3" y1="-6" x2="-2" y2="-6" width="0.2032" layer="21"/>
<wire x1="1" y1="-4" x2="1" y2="4" width="0.2032" layer="21"/>
<wire x1="-13.5" y1="4.3" x2="-13.5" y2="1.9" width="0.2032" layer="51"/>
<wire x1="-13.5" y1="1.9" x2="-11.2" y2="1.9" width="0.2032" layer="51"/>
<wire x1="-11.2" y1="1.9" x2="-11.2" y2="4.3" width="0.2032" layer="51"/>
<wire x1="-11.2" y1="4.3" x2="-13.5" y2="4.3" width="0.2032" layer="51"/>
<wire x1="-13.5" y1="-1.9" x2="-13.5" y2="-4.3" width="0.2032" layer="51"/>
<wire x1="-13.5" y1="-4.3" x2="-11.2" y2="-4.3" width="0.2032" layer="51"/>
<wire x1="-11.2" y1="-4.3" x2="-11.2" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-11.2" y1="-1.9" x2="-13.5" y2="-1.9" width="0.2032" layer="51"/>
<pad name="GND" x="2.4" y="3.5" drill="0.9144" diameter="1.8796" rot="R270"/>
<pad name="D+" x="2.4" y="1.127" drill="0.9144" diameter="1.8796" rot="R270"/>
<pad name="D-" x="2.4" y="-1.127" drill="0.9144" diameter="1.8796" rot="R270"/>
<pad name="VBUS" x="2.4" y="-3.5" drill="0.9144" diameter="1.8796" rot="R270"/>
<pad name="GND2" x="0" y="-5.8" drill="2.2" rot="R270"/>
<pad name="GND3" x="0" y="5.8" drill="2.2" rot="R270"/>
<text x="5.85" y="-2.7" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="-3.9" y="-4.4" size="1.27" layer="51" rot="R90">PCB Edge</text>
<hole x="-0.1" y="2.25" drill="1.1"/>
<hole x="-0.1" y="-2.25" drill="1.1"/>
</package>
<package name="USB-A-S">
<description>&lt;b&gt;USB Series A Surface Mounted&lt;/b&gt;</description>
<wire x1="3.6957" y1="6.5659" x2="-10.287" y2="6.5659" width="0.127" layer="21"/>
<wire x1="3.6957" y1="-6.5659" x2="-10.287" y2="-6.5659" width="0.127" layer="21"/>
<wire x1="-10.287" y1="6.477" x2="-10.287" y2="-6.477" width="0.127" layer="21"/>
<wire x1="3.7084" y1="6.5024" x2="3.7084" y2="-6.5024" width="0.127" layer="21"/>
<wire x1="-2.54" y1="-5.08" x2="-8.89" y2="-4.445" width="0.127" layer="21"/>
<wire x1="-8.89" y1="-4.445" x2="-8.89" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-8.89" y1="-1.27" x2="-2.54" y2="-0.635" width="0.127" layer="21"/>
<wire x1="-2.54" y1="5.08" x2="-8.89" y2="4.445" width="0.127" layer="21"/>
<wire x1="-8.89" y1="4.445" x2="-8.89" y2="1.27" width="0.127" layer="21"/>
<wire x1="-8.89" y1="1.27" x2="-2.54" y2="0.635" width="0.127" layer="21"/>
<pad name="P$5" x="0" y="-6.5659" drill="2.3114" rot="R270"/>
<pad name="P$6" x="0" y="6.5659" drill="2.3114" rot="R270"/>
<smd name="D-" x="3.45" y="1" dx="3" dy="0.9" layer="1"/>
<smd name="VBUS" x="3.45" y="3" dx="3" dy="0.9" layer="1"/>
<smd name="D+" x="3.45" y="-1" dx="3" dy="0.9" layer="1"/>
<smd name="GND" x="3.45" y="-3" dx="3" dy="0.9" layer="1"/>
<text x="5.715" y="3.81" size="1.27" layer="25" rot="R90">&gt;NAME</text>
</package>
<package name="USB-MB-H">
<description>&lt;b&gt;USB Series Mini-B Hole Mounted&lt;/b&gt;</description>
<wire x1="-3.75" y1="3.9" x2="-3.75" y2="-3.9" width="0.127" layer="22"/>
<wire x1="5.25" y1="3.9" x2="5.25" y2="-3.9" width="0.127" layer="22"/>
<wire x1="-3.75" y1="3.9" x2="5.25" y2="3.9" width="0.127" layer="22"/>
<wire x1="-3.75" y1="-3.9" x2="5.25" y2="-3.9" width="0.127" layer="22"/>
<wire x1="0.75" y1="3.5" x2="-3.25" y2="3" width="0.127" layer="22"/>
<wire x1="-3.25" y1="3" x2="-3.25" y2="2" width="0.127" layer="22"/>
<wire x1="-3.25" y1="2" x2="0.75" y2="1.5" width="0.127" layer="22"/>
<wire x1="1.25" y1="-3.5" x2="-3.25" y2="-3" width="0.127" layer="22"/>
<wire x1="-3.25" y1="-3" x2="-3.25" y2="-2" width="0.127" layer="22"/>
<wire x1="-3.25" y1="-2" x2="1.25" y2="-1.5" width="0.127" layer="22"/>
<wire x1="-3.25" y1="1.25" x2="1.75" y2="0.75" width="0.127" layer="22"/>
<wire x1="1.75" y1="0.75" x2="1.75" y2="-0.75" width="0.127" layer="22"/>
<wire x1="1.75" y1="-0.75" x2="-3.25" y2="-1.25" width="0.127" layer="22"/>
<pad name="VBUS" x="5.1" y="1.6" drill="0.8"/>
<pad name="D+" x="5.1" y="0" drill="0.8"/>
<pad name="GND" x="5.1" y="-1.6" drill="0.8"/>
<pad name="D-" x="3.9" y="0.8" drill="0.8"/>
<pad name="ID" x="3.9" y="-0.8" drill="0.8"/>
<pad name="P$6" x="0" y="-3.65" drill="1.9"/>
<pad name="P$7" x="0" y="3.65" drill="1.9"/>
<text x="7.25" y="1.5" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<rectangle x1="3.25" y1="3" x2="5.75" y2="4.4" layer="43"/>
<rectangle x1="3.25" y1="-4.4" x2="5.75" y2="-3" layer="43"/>
<rectangle x1="-3.75" y1="-3.1" x2="-1.425" y2="3.1" layer="43"/>
<rectangle x1="-1.425" y1="-2.325" x2="-0.65" y2="2.325" layer="43"/>
</package>
<package name="USB-B-SMT">
<description>USB Series B Surface Mounted</description>
<wire x1="-1" y1="-6" x2="2.4" y2="-6" width="0.2032" layer="51"/>
<wire x1="2.4" y1="6" x2="-1" y2="6" width="0.2032" layer="51"/>
<wire x1="2.4" y1="6" x2="2.4" y2="7.3" width="0.2032" layer="51"/>
<wire x1="2.4" y1="7.3" x2="2.2" y2="7.5" width="0.2032" layer="51"/>
<wire x1="2.2" y1="7.5" x2="1.9" y2="7.5" width="0.2032" layer="51"/>
<wire x1="1.9" y1="7.5" x2="1.4" y2="7" width="0.2032" layer="51"/>
<wire x1="-1" y1="6" x2="-1" y2="7.3" width="0.2032" layer="51"/>
<wire x1="-0.8" y1="7.5" x2="-0.5" y2="7.5" width="0.2032" layer="51"/>
<wire x1="-0.5" y1="7.5" x2="0" y2="7" width="0.2032" layer="51"/>
<wire x1="0" y1="7" x2="1.4" y2="7" width="0.2032" layer="51"/>
<wire x1="-1" y1="-6" x2="-1" y2="-7.3" width="0.2032" layer="51"/>
<wire x1="-1" y1="-7.3" x2="-0.8" y2="-7.5" width="0.2032" layer="51"/>
<wire x1="-0.8" y1="-7.5" x2="-0.5" y2="-7.5" width="0.2032" layer="51"/>
<wire x1="-0.5" y1="-7.5" x2="0" y2="-7" width="0.2032" layer="51"/>
<wire x1="1.9" y1="-7.5" x2="1.4" y2="-7" width="0.2032" layer="51"/>
<wire x1="1.4" y1="-7" x2="0" y2="-7" width="0.2032" layer="51"/>
<wire x1="-1" y1="7.3" x2="-0.8" y2="7.5" width="0.2032" layer="51"/>
<wire x1="2.2" y1="-7.5" x2="1.9" y2="-7.5" width="0.2032" layer="51"/>
<wire x1="2.2" y1="-7.5" x2="2.4" y2="-7.3" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-6" x2="2.4" y2="-7.3" width="0.2032" layer="51"/>
<wire x1="-5" y1="6" x2="-5" y2="-6" width="0.2032" layer="51"/>
<wire x1="-5" y1="6" x2="-9" y2="6" width="0.2032" layer="51"/>
<wire x1="-9" y1="6" x2="-9" y2="-6" width="0.2032" layer="51"/>
<wire x1="-9" y1="-6" x2="-5" y2="-6" width="0.2032" layer="51"/>
<wire x1="-5" y1="6" x2="-3" y2="6" width="0.2032" layer="21"/>
<wire x1="-5" y1="-6" x2="-3" y2="-6" width="0.2032" layer="21"/>
<wire x1="4" y1="-6" x2="7" y2="-6" width="0.2032" layer="21"/>
<wire x1="7" y1="-6" x2="7" y2="-3" width="0.2032" layer="21"/>
<wire x1="7" y1="3" x2="7" y2="6" width="0.2032" layer="21"/>
<wire x1="7" y1="6" x2="4" y2="6" width="0.2032" layer="21"/>
<smd name="5" x="0.58" y="6.8" dx="6.04" dy="3.4" layer="1"/>
<smd name="6" x="0.58" y="-6.8" dx="6.04" dy="3.4" layer="1"/>
<smd name="D+" x="7" y="1.875" dx="3" dy="0.7" layer="1"/>
<smd name="D-" x="7" y="0.625" dx="3" dy="0.7" layer="1"/>
<smd name="GND" x="7" y="-0.625" dx="3" dy="0.7" layer="1"/>
<smd name="VUSB" x="7" y="-1.875" dx="3" dy="0.7" layer="1"/>
<text x="4.3" y="-7.795" size="1.27" layer="25">&gt;NAME</text>
<hole x="0" y="2.25" drill="1.4"/>
<hole x="0" y="-2.25" drill="1.4"/>
</package>
<package name="USB-MINIB-OLD">
<description>&lt;b&gt;USB Series Mini-B Surface Mounted&lt;/b&gt;</description>
<wire x1="-1.5" y1="3.8" x2="0.9" y2="3.8" width="0.127" layer="21"/>
<wire x1="3.3" y1="3.1" x2="3.3" y2="2.1" width="0.127" layer="21"/>
<wire x1="3.3" y1="-2.1" x2="3.3" y2="-3.1" width="0.127" layer="21"/>
<wire x1="1" y1="-3.8" x2="-1.5" y2="-3.8" width="0.127" layer="21"/>
<wire x1="-5.9" y1="3.8" x2="-5.9" y2="-3.8" width="0.127" layer="51"/>
<wire x1="-5.9" y1="-3.8" x2="-4.5" y2="-3.8" width="0.127" layer="51"/>
<wire x1="-5.9" y1="3.8" x2="-4.5" y2="3.8" width="0.127" layer="51"/>
<smd name="1" x="-3" y="-4.5" dx="2.5" dy="2" layer="1"/>
<smd name="2" x="-3" y="4.5" dx="2.5" dy="2" layer="1"/>
<smd name="3" x="3" y="-4.5" dx="3.5" dy="2" layer="1"/>
<smd name="4" x="3" y="4.5" dx="3.5" dy="2" layer="1"/>
<smd name="D+" x="3" y="0" dx="3.5" dy="0.5" layer="1"/>
<smd name="D-" x="3" y="0.8" dx="3.5" dy="0.5" layer="1"/>
<smd name="VBUS" x="3.01" y="1.61" dx="3.5" dy="0.5" layer="1"/>
<smd name="ID" x="3" y="-0.8" dx="3.5" dy="0.5" layer="1"/>
<smd name="GND" x="3" y="-1.6" dx="3.5" dy="0.5" layer="1"/>
<text x="-3.81" y="-1.27" size="0.4064" layer="27">&gt;VALUE</text>
<text x="-3.81" y="0" size="0.4064" layer="25">&gt;NAME</text>
<hole x="0" y="2.2" drill="0.9"/>
<hole x="0" y="-2.2" drill="0.9"/>
</package>
<package name="USB-B-PTH">
<description>&lt;b&gt;USB Series B Hole Mounted&lt;/b&gt;</description>
<wire x1="-12.5" y1="6" x2="-8.6" y2="6" width="0.2032" layer="51"/>
<wire x1="-8.6" y1="6" x2="-8.6" y2="-6" width="0.2032" layer="51"/>
<wire x1="-8.6" y1="-6" x2="-12.5" y2="-6" width="0.2032" layer="51"/>
<wire x1="-12.5" y1="-6" x2="-12.5" y2="6" width="0.2032" layer="51"/>
<wire x1="-8.6" y1="6" x2="-4.8" y2="6" width="0.2032" layer="21"/>
<wire x1="-8.6" y1="-6" x2="-4.8" y2="-6" width="0.2032" layer="21"/>
<wire x1="-0.6" y1="-6" x2="3.3" y2="-6" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-6" x2="3.3" y2="6" width="0.2032" layer="21"/>
<wire x1="3.3" y1="6" x2="-0.6" y2="6" width="0.2032" layer="21"/>
<pad name="VBUS" x="1.9812" y="-1.25" drill="0.9144" diameter="1.6764" rot="R90"/>
<pad name="D-" x="1.9812" y="1.25" drill="0.9144" diameter="1.6764" rot="R90"/>
<pad name="D+" x="0" y="1.25" drill="0.9144" diameter="1.6764" rot="R270"/>
<pad name="GND" x="0" y="-1.25" drill="0.9144" diameter="1.6764" rot="R270"/>
<pad name="S1" x="-2.7178" y="-6.0198" drill="2.286"/>
<pad name="S2" x="-2.7178" y="6.0198" drill="2.286"/>
<text x="-1.27" y="3.81" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="2.54" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="S4B-PH">
<wire x1="-6" y1="2" x2="-6" y2="-7" width="0.3048" layer="51"/>
<wire x1="-6" y1="-7" x2="6" y2="-7" width="0.3048" layer="51"/>
<wire x1="6" y1="-7" x2="6" y2="2" width="0.3048" layer="51"/>
<wire x1="6" y1="2" x2="-6" y2="2" width="0.3048" layer="51"/>
<smd name="1" x="-3" y="-4.7" dx="1" dy="4.6" layer="1"/>
<smd name="2" x="-1" y="-4.7" dx="1" dy="4.6" layer="1"/>
<smd name="3" x="1" y="-4.7" dx="1" dy="4.6" layer="1"/>
<smd name="4" x="3" y="-4.7" dx="1" dy="4.6" layer="1"/>
<smd name="P$1" x="-5.4" y="0.5" dx="3.4" dy="1.6" layer="1" rot="R90"/>
<smd name="P$2" x="5.4" y="0.5" dx="3.4" dy="1.6" layer="1" rot="R90"/>
</package>
<package name="USB-MINIB">
<description>&lt;b&gt;USB Series Mini-B Surface Mounted&lt;/b&gt;</description>
<wire x1="-1.3" y1="3.8" x2="0.8" y2="3.8" width="0.2032" layer="21"/>
<wire x1="3.3" y1="3.1" x2="3.3" y2="2.2" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2.2" x2="3.3" y2="-3.1" width="0.2032" layer="21"/>
<wire x1="0.8" y1="-3.8" x2="-1.3" y2="-3.8" width="0.2032" layer="21"/>
<wire x1="-5.9" y1="3.8" x2="-5.9" y2="-3.8" width="0.2032" layer="51"/>
<wire x1="-5.9" y1="-3.8" x2="-4.5" y2="-3.8" width="0.2032" layer="51"/>
<wire x1="-5.9" y1="3.8" x2="-4.5" y2="3.8" width="0.2032" layer="51"/>
<smd name="D+" x="2.5" y="0" dx="2.5" dy="0.5" layer="1"/>
<smd name="D-" x="2.5" y="0.8" dx="2.5" dy="0.5" layer="1"/>
<smd name="GND" x="2.5" y="-1.6" dx="2.5" dy="0.5" layer="1"/>
<smd name="ID" x="2.5" y="-0.8" dx="2.5" dy="0.5" layer="1"/>
<smd name="MTN3" x="-3" y="-4.5" dx="2.5" dy="2" layer="1"/>
<smd name="MTN1" x="-3" y="4.5" dx="2.5" dy="2" layer="1"/>
<smd name="MTN4" x="2.5" y="-4.5" dx="2.5" dy="2" layer="1"/>
<smd name="MTN2" x="2.5" y="4.5" dx="2.5" dy="2" layer="1"/>
<smd name="VBUS" x="2.5" y="1.6" dx="2.5" dy="0.5" layer="1"/>
<text x="-3.81" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-3.81" y="0" size="0.4064" layer="27">&gt;VALUE</text>
<hole x="0" y="2.2" drill="0.9"/>
<hole x="0" y="-2.2" drill="0.9"/>
</package>
<package name="USB-A-PCB">
<wire x1="-5" y1="6" x2="3.7" y2="6" width="0.127" layer="51"/>
<wire x1="3.7" y1="6" x2="3.7" y2="-6" width="0.127" layer="51"/>
<wire x1="3.7" y1="-6" x2="-5" y2="-6" width="0.127" layer="51"/>
<wire x1="-5" y1="-6" x2="-5" y2="6" width="0.127" layer="51"/>
<smd name="5V" x="-0.2" y="-3.5" dx="7.5" dy="1.5" layer="1"/>
<smd name="USB_M" x="0.3" y="-1" dx="6.5" dy="1" layer="1"/>
<smd name="USB_P" x="0.3" y="1" dx="6.5" dy="1" layer="1"/>
<smd name="GND" x="-0.2" y="3.5" dx="7.5" dy="1.5" layer="1"/>
<text x="-1.27" y="5.08" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="-5.08" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="USB-B-PTH-VERTICAL">
<description>&lt;b&gt;USB Series B Hole Mounted&lt;/b&gt;</description>
<wire x1="0" y1="0" x2="11.938" y2="0" width="0.254" layer="21"/>
<wire x1="11.938" y1="0" x2="11.938" y2="11.303" width="0.254" layer="21"/>
<wire x1="11.938" y1="11.303" x2="0" y2="11.303" width="0.254" layer="21"/>
<wire x1="0" y1="11.303" x2="0" y2="0" width="0.254" layer="21"/>
<wire x1="1.27" y1="1.27" x2="10.795" y2="1.27" width="0.254" layer="51"/>
<wire x1="10.795" y1="1.27" x2="10.795" y2="8.255" width="0.254" layer="51"/>
<wire x1="10.795" y1="8.255" x2="8.89" y2="10.16" width="0.254" layer="51"/>
<wire x1="8.89" y1="10.16" x2="3.175" y2="10.16" width="0.254" layer="51"/>
<wire x1="3.175" y1="10.16" x2="1.27" y2="8.255" width="0.254" layer="51"/>
<wire x1="1.27" y1="8.255" x2="1.27" y2="1.27" width="0.254" layer="51"/>
<pad name="GND" x="7.3152" y="4.3942" drill="0.9144" diameter="1.6764" rot="R90"/>
<pad name="VBUS" x="7.3152" y="7.5946" drill="0.9144" diameter="1.6764" rot="R90"/>
<pad name="D-" x="4.826" y="7.5946" drill="0.9144" diameter="1.6764" rot="R270"/>
<pad name="D+" x="4.826" y="4.3942" drill="0.9144" diameter="1.6764" rot="R270"/>
<pad name="P$1" x="0" y="4.9022" drill="2.286"/>
<pad name="P$2" x="12.0396" y="4.9022" drill="2.286"/>
<text x="8.89" y="-1.27" size="0.8128" layer="25">&gt;NAME</text>
<text x="0" y="-1.27" size="0.8128" layer="27">&gt;VALUE</text>
</package>
<package name="USB-A-S-NOSILK">
<wire x1="3.6957" y1="6.5659" x2="-10.287" y2="6.5659" width="0.127" layer="51"/>
<wire x1="3.6957" y1="-6.5659" x2="-10.287" y2="-6.5659" width="0.127" layer="51"/>
<wire x1="-10.287" y1="6.477" x2="-10.287" y2="-6.477" width="0.127" layer="51"/>
<wire x1="3.7084" y1="6.5024" x2="3.7084" y2="-6.5024" width="0.127" layer="51"/>
<wire x1="-2.54" y1="-5.08" x2="-8.89" y2="-4.445" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-4.445" x2="-8.89" y2="-1.27" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-1.27" x2="-2.54" y2="-0.635" width="0.127" layer="51"/>
<wire x1="-2.54" y1="5.08" x2="-8.89" y2="4.445" width="0.127" layer="51"/>
<wire x1="-8.89" y1="4.445" x2="-8.89" y2="1.27" width="0.127" layer="51"/>
<wire x1="-8.89" y1="1.27" x2="-2.54" y2="0.635" width="0.127" layer="51"/>
<pad name="P$5" x="0" y="-6.5659" drill="2.3114" rot="R270"/>
<pad name="P$6" x="0" y="6.5659" drill="2.3114" rot="R270"/>
<smd name="D-" x="3.45" y="1" dx="3" dy="0.9" layer="1"/>
<smd name="VBUS" x="3.45" y="3" dx="3" dy="0.9" layer="1"/>
<smd name="D+" x="3.45" y="-1" dx="3" dy="0.9" layer="1"/>
<smd name="GND" x="3.45" y="-3" dx="3" dy="0.9" layer="1"/>
<text x="5.715" y="3.81" size="1.27" layer="51" rot="R90">&gt;NAME</text>
</package>
<package name="USB-A-S-NOSILK-FEMALE">
<wire x1="3.6957" y1="6.5659" x2="-10.287" y2="6.5659" width="0.127" layer="51"/>
<wire x1="3.6957" y1="-6.5659" x2="-10.287" y2="-6.5659" width="0.127" layer="51"/>
<wire x1="-10.287" y1="6.477" x2="-10.287" y2="-6.477" width="0.127" layer="51"/>
<wire x1="3.7084" y1="6.5024" x2="3.7084" y2="-6.5024" width="0.127" layer="51"/>
<wire x1="-2.54" y1="-5.08" x2="-8.89" y2="-4.445" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-4.445" x2="-8.89" y2="-1.27" width="0.127" layer="51"/>
<wire x1="-8.89" y1="-1.27" x2="-2.54" y2="-0.635" width="0.127" layer="51"/>
<wire x1="-2.54" y1="5.08" x2="-8.89" y2="4.445" width="0.127" layer="51"/>
<wire x1="-8.89" y1="4.445" x2="-8.89" y2="1.27" width="0.127" layer="51"/>
<wire x1="-8.89" y1="1.27" x2="-2.54" y2="0.635" width="0.127" layer="51"/>
<pad name="P$5" x="0" y="-6.5659" drill="2.3114" rot="R270"/>
<pad name="P$6" x="0" y="6.5659" drill="2.3114" rot="R270"/>
<smd name="D-" x="4.212" y="1" dx="3" dy="0.9" layer="1"/>
<smd name="VBUS" x="4.212" y="3.5" dx="3" dy="0.9" layer="1"/>
<smd name="D+" x="4.212" y="-1" dx="3" dy="0.9" layer="1"/>
<smd name="GND" x="4.212" y="-3.5" dx="3" dy="0.9" layer="1"/>
<text x="8.46" y="-7.205" size="1.27" layer="51" rot="R180">&gt;NAME</text>
</package>
<package name="USB-MINIB-NOSTOP">
<wire x1="-1.3" y1="3.8" x2="0.8" y2="3.8" width="0.2032" layer="21"/>
<wire x1="3.3" y1="3.1" x2="3.3" y2="2.2" width="0.2032" layer="21"/>
<wire x1="3.3" y1="-2.2" x2="3.3" y2="-3.1" width="0.2032" layer="21"/>
<wire x1="0.8" y1="-3.8" x2="-1.3" y2="-3.8" width="0.2032" layer="21"/>
<wire x1="-5.9" y1="3.8" x2="-5.9" y2="-3.8" width="0.2032" layer="51"/>
<wire x1="-5.9" y1="-3.8" x2="-4.5" y2="-3.8" width="0.2032" layer="51"/>
<wire x1="-5.9" y1="3.8" x2="-4.5" y2="3.8" width="0.2032" layer="51"/>
<circle x="0" y="2.2" radius="0.35" width="0.41" layer="29"/>
<circle x="0" y="-2.2" radius="0.35" width="0.41" layer="29"/>
<pad name="H1" x="0" y="2.2" drill="0.9" diameter="0.8" stop="no"/>
<pad name="H2" x="0" y="-2.2" drill="0.9" diameter="0.7874" stop="no"/>
<smd name="D+" x="2.5" y="0" dx="2.5" dy="0.5" layer="1"/>
<smd name="D-" x="2.5" y="0.8" dx="2.5" dy="0.5" layer="1"/>
<smd name="GND" x="2.5" y="-1.6" dx="2.5" dy="0.5" layer="1"/>
<smd name="ID" x="2.5" y="-0.8" dx="2.5" dy="0.5" layer="1"/>
<smd name="G1" x="-3" y="-4.5" dx="2.5" dy="2" layer="1"/>
<smd name="G2" x="-3" y="4.5" dx="2.5" dy="2" layer="1"/>
<smd name="G4" x="2.5" y="-4.5" dx="2.5" dy="2" layer="1"/>
<smd name="G3" x="2.5" y="4.5" dx="2.5" dy="2" layer="1"/>
<smd name="VBUS" x="2.5" y="1.6" dx="2.5" dy="0.5" layer="1"/>
<text x="-3.81" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-3.81" y="0" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="USB-A-S-SILK-FEMALE">
<wire x1="6.6957" y1="6.5659" x2="-7.287" y2="6.5659" width="0.127" layer="51"/>
<wire x1="6.6957" y1="-6.5659" x2="-7.287" y2="-6.5659" width="0.127" layer="51"/>
<wire x1="-7.287" y1="6.477" x2="-7.287" y2="-6.477" width="0.127" layer="51"/>
<wire x1="6.7084" y1="6.5024" x2="6.7084" y2="-6.5024" width="0.127" layer="51"/>
<wire x1="0.46" y1="-5.08" x2="-5.89" y2="-4.445" width="0.127" layer="51"/>
<wire x1="-5.89" y1="-4.445" x2="-5.89" y2="-1.27" width="0.127" layer="51"/>
<wire x1="-5.89" y1="-1.27" x2="0.46" y2="-0.635" width="0.127" layer="51"/>
<wire x1="0.46" y1="5.08" x2="-5.89" y2="4.445" width="0.127" layer="51"/>
<wire x1="-5.89" y1="4.445" x2="-5.89" y2="1.27" width="0.127" layer="51"/>
<wire x1="-5.89" y1="1.27" x2="0.46" y2="0.635" width="0.127" layer="51"/>
<wire x1="-7.366" y1="6.604" x2="0.508" y2="6.604" width="0.2032" layer="21"/>
<wire x1="-7.366" y1="6.604" x2="-7.366" y2="-6.604" width="0.2032" layer="21"/>
<wire x1="-7.366" y1="-6.604" x2="0.508" y2="-6.604" width="0.2032" layer="21"/>
<wire x1="5.08" y1="-6.604" x2="6.858" y2="-6.604" width="0.2032" layer="21"/>
<wire x1="6.858" y1="-6.604" x2="6.858" y2="-4.318" width="0.2032" layer="21"/>
<wire x1="6.858" y1="4.318" x2="6.858" y2="6.604" width="0.2032" layer="21"/>
<wire x1="6.858" y1="6.604" x2="5.08" y2="6.604" width="0.2032" layer="21"/>
<pad name="P$5" x="3" y="-6.5659" drill="2.3114" rot="R270"/>
<pad name="P$6" x="3" y="6.5659" drill="2.3114" rot="R270"/>
<smd name="D-" x="7.212" y="1" dx="3" dy="0.9" layer="1"/>
<smd name="VBUS" x="7.212" y="3.5" dx="3" dy="0.9" layer="1"/>
<smd name="D+" x="7.212" y="-1" dx="3" dy="0.9" layer="1"/>
<smd name="GND" x="7.212" y="-3.5" dx="3" dy="0.9" layer="1"/>
<text x="-3.81" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-3.81" y="-3.81" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="USB-MICROB">
<description>Micro USB Package</description>
<wire x1="-3.4" y1="-2.15" x2="-3" y2="-2.15" width="0.127" layer="51"/>
<wire x1="3" y1="-2.15" x2="3.4" y2="-2.15" width="0.127" layer="51"/>
<wire x1="-3.4" y1="-2.15" x2="-3.4" y2="-1.45" width="0.127" layer="51"/>
<wire x1="-3.4" y1="-1.45" x2="-3.4" y2="2.85" width="0.127" layer="51"/>
<wire x1="3.4" y1="2.85" x2="2.2" y2="2.85" width="0.127" layer="51"/>
<wire x1="3.4" y1="2.85" x2="3.4" y2="-1.45" width="0.127" layer="51"/>
<wire x1="3.4" y1="-1.45" x2="3.4" y2="-2.15" width="0.127" layer="51"/>
<wire x1="-3.4" y1="-1.45" x2="3.4" y2="-1.45" width="0.127" layer="51"/>
<wire x1="-3.4" y1="1.25" x2="-3.4" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="2.85" x2="-2.2" y2="2.85" width="0.2032" layer="21"/>
<wire x1="3.4" y1="2.85" x2="2.2" y2="2.85" width="0.2032" layer="21"/>
<wire x1="3.4" y1="1.25" x2="3.4" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="-1.45" x2="3.4" y2="-1.45" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="1.45" x2="2.2" y2="1.45" width="0.127" layer="51"/>
<wire x1="2.2" y1="1.45" x2="2.2" y2="2.85" width="0.127" layer="51"/>
<wire x1="-2.2" y1="1.45" x2="-2.2" y2="2.85" width="0.127" layer="51"/>
<wire x1="-3.4" y1="2.85" x2="-2.2" y2="2.85" width="0.127" layer="51"/>
<wire x1="-2.2" y1="2.85" x2="-2.2" y2="1.45" width="0.2032" layer="21"/>
<wire x1="-2.2" y1="1.45" x2="2.2" y2="1.45" width="0.2032" layer="21"/>
<wire x1="2.2" y1="1.45" x2="2.2" y2="2.85" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="-2.15" x2="-4" y2="-2.75" width="0.2032" layer="51"/>
<wire x1="3.4" y1="-2.15" x2="4" y2="-2.75" width="0.2032" layer="51"/>
<wire x1="-3" y1="-2.15" x2="-3" y2="-2.55" width="0.127" layer="51"/>
<wire x1="-2.8" y1="-2.8" x2="2.75" y2="-2.8" width="0.127" layer="51"/>
<wire x1="3" y1="-2.6" x2="3" y2="-2.15" width="0.127" layer="51"/>
<wire x1="-3" y1="-2.55" x2="-2.8" y2="-2.8" width="0.127" layer="51" curve="84.547378"/>
<wire x1="2.75" y1="-2.8" x2="3" y2="-2.6" width="0.127" layer="51" curve="84.547378"/>
<smd name="VBUS" x="-1.3" y="2.65" dx="1.4" dy="0.35" layer="1" rot="R90"/>
<smd name="GND" x="1.3" y="2.65" dx="1.4" dy="0.35" layer="1" rot="R90"/>
<smd name="D-" x="-0.65" y="2.65" dx="1.4" dy="0.35" layer="1" rot="R90"/>
<smd name="D+" x="0" y="2.65" dx="1.4" dy="0.35" layer="1" rot="R90"/>
<smd name="ID" x="0.65" y="2.65" dx="1.4" dy="0.35" layer="1" rot="R90"/>
<smd name="MT1" x="-4" y="0" dx="1.8" dy="1.9" layer="1"/>
<smd name="MT2" x="4" y="0" dx="1.8" dy="1.9" layer="1"/>
<text x="-1.6" y="-0.35" size="0.762" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="0.762" layer="27">&gt;VALUE</text>
</package>
<package name="CAP-PTH-SMALL">
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651"/>
<text x="0.508" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="0.254" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="CAP-PTH-SMALL2">
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="1.27" x2="3.81" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-1.27" x2="-1.27" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="-1.27" y2="1.27" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.54" y="0" drill="0.7" diameter="1.651"/>
<text x="-1.27" y="1.905" size="0.6096" layer="25">&gt;Name</text>
<text x="-1.27" y="-2.54" size="0.6096" layer="27">&gt;Value</text>
</package>
<package name="CAP-PTH-LARGE">
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.2032" layer="21"/>
<pad name="1" x="-4.826" y="0" drill="0.9" diameter="1.905"/>
<pad name="2" x="4.572" y="0" drill="0.9" diameter="1.905"/>
<text x="-0.762" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.016" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="GRM43D">
<wire x1="2.25" y1="1.6" x2="1.1" y2="1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="1.6" x2="-1.1" y2="1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="1.6" x2="-2.25" y2="1.6" width="0.127" layer="51"/>
<wire x1="-2.25" y1="1.6" x2="-2.25" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-2.25" y1="-1.6" x2="-1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="-1.6" x2="1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="-1.6" x2="2.25" y2="-1.6" width="0.127" layer="51"/>
<wire x1="2.25" y1="-1.6" x2="2.25" y2="1.6" width="0.127" layer="51"/>
<wire x1="1.1" y1="1.6" x2="1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-1.1" y1="1.6" x2="-1.1" y2="-1.6" width="0.127" layer="51"/>
<wire x1="-2.3" y1="1.8" x2="2.3" y2="1.8" width="0.127" layer="21"/>
<wire x1="-2.3" y1="-1.8" x2="2.3" y2="-1.8" width="0.127" layer="21"/>
<smd name="A" x="1.927" y="0" dx="3.2" dy="1.65" layer="1" rot="R90"/>
<smd name="C" x="-1.927" y="0" dx="3.2" dy="1.65" layer="1" rot="R90"/>
<text x="-2" y="2" size="0.4064" layer="25">&gt;NAME</text>
<text x="0" y="-2" size="0.4064" layer="27" rot="R180">&gt;VALUE</text>
<rectangle x1="-2.2" y1="-1.6" x2="-1.1" y2="1.6" layer="51"/>
<rectangle x1="1.1" y1="-1.6" x2="2.2" y2="1.6" layer="51"/>
</package>
<package name="0603-CAP">
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<wire x1="0" y1="0.0305" x2="0" y2="-0.0305" width="0.5588" layer="21"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-0.889" y="0.762" size="0.4064" layer="25" font="vector">&gt;NAME</text>
<text x="-1.016" y="-1.143" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
</package>
<package name="0402-CAP">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="0" y1="0.0305" x2="0" y2="-0.0305" width="0.4064" layer="21"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.889" y="0.6985" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.0795" y="-1.143" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
</package>
<package name="CAP-PTH-5MM">
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.5" y="0" drill="0.7" diameter="1.651"/>
<text x="-0.762" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.016" y="-1.524" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="AXIAL-5MM">
<wire x1="-1.14" y1="0.762" x2="1.14" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0.762" x2="1.14" y2="0" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0" x2="1.14" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="-0.762" x2="-1.14" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="-0.762" x2="-1.14" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="0" x2="-1.14" y2="0.762" width="0.2032" layer="21"/>
<wire x1="1.14" y1="0" x2="1.394" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.14" y1="0" x2="-1.394" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-2.5" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="2.5" y="0" drill="0.9" diameter="1.8796"/>
<text x="-2.54" y="1.17" size="0.4" layer="25">&gt;Name</text>
<text x="-1.032" y="-0.208" size="0.4" layer="21" ratio="15">&gt;Value</text>
</package>
<package name="1206">
<wire x1="-2.473" y1="0.983" x2="2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="-0.983" x2="-2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-2.473" y1="-0.983" x2="-2.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="2.473" y1="0.983" x2="2.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-0.965" y1="0.787" x2="0.965" y2="0.787" width="0.1016" layer="51"/>
<wire x1="-0.965" y1="-0.787" x2="0.965" y2="-0.787" width="0.1016" layer="51"/>
<smd name="1" x="-1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<smd name="2" x="1.4" y="0" dx="1.6" dy="1.8" layer="1"/>
<text x="-1.27" y="1.143" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.397" y="-1.524" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-1.7018" y1="-0.8509" x2="-0.9517" y2="0.8491" layer="51"/>
<rectangle x1="0.9517" y1="-0.8491" x2="1.7018" y2="0.8509" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
</package>
<package name="CTZ3">
<description>CTZ3 Series land pattern for variable capacitor - CTZ3E-50C-W1-PF</description>
<wire x1="-1.6" y1="1.4" x2="-1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-1.6" y1="-2.25" x2="1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.4" x2="1.6" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-0.5" y1="0" x2="0.5" y2="0" width="0.127" layer="51"/>
<wire x1="-1.6" y1="1.4" x2="-1" y2="2.2" width="0.127" layer="51"/>
<wire x1="1.6" y1="1.4" x2="1" y2="2.2" width="0.127" layer="51"/>
<wire x1="-1" y1="2.2" x2="1" y2="2.2" width="0.127" layer="51"/>
<wire x1="0" y1="0.8" x2="0" y2="-0.8" width="0.127" layer="51"/>
<wire x1="-0.8" y1="0" x2="0.8" y2="0" width="0.127" layer="51"/>
<wire x1="-1.05" y1="2.25" x2="-1.7" y2="1.45" width="0.127" layer="21"/>
<wire x1="-1.7" y1="1.45" x2="-1.7" y2="-2.35" width="0.127" layer="21"/>
<wire x1="-1.7" y1="-2.35" x2="-1.05" y2="-2.35" width="0.127" layer="21"/>
<wire x1="1.05" y1="2.25" x2="1.7" y2="1.4" width="0.127" layer="21"/>
<wire x1="1.7" y1="1.4" x2="1.7" y2="-2.35" width="0.127" layer="21"/>
<wire x1="1.7" y1="-2.35" x2="1.05" y2="-2.35" width="0.127" layer="21"/>
<smd name="+" x="0" y="2.05" dx="1.5" dy="1.2" layer="1"/>
<smd name="-" x="0" y="-2.05" dx="1.5" dy="1.2" layer="1"/>
<text x="-2" y="3" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2" y="-3.4" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="AXIAL-0.3">
<wire x1="-2.54" y1="0.762" x2="2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0.762" x2="2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="-0.762" x2="-2.54" y2="-0.762" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="-0.762" x2="-2.54" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="0.762" width="0.2032" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.2032" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.2032" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="3.81" y="0" drill="0.9" diameter="1.8796"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.032" y="-0.381" size="1.016" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="R2010">
<description>&lt;b&gt;RESISTOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-1.662" y1="1.245" x2="1.662" y2="1.245" width="0.1524" layer="51"/>
<wire x1="-1.637" y1="-1.245" x2="1.687" y2="-1.245" width="0.1524" layer="51"/>
<wire x1="-3.473" y1="1.483" x2="3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="1.483" x2="3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="3.473" y1="-1.483" x2="-3.473" y2="-1.483" width="0.0508" layer="39"/>
<wire x1="-3.473" y1="-1.483" x2="-3.473" y2="1.483" width="0.0508" layer="39"/>
<wire x1="-1.027" y1="1.245" x2="1.027" y2="1.245" width="0.1524" layer="21"/>
<wire x1="-1.002" y1="-1.245" x2="1.016" y2="-1.245" width="0.1524" layer="21"/>
<smd name="1" x="-2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<smd name="2" x="2.2" y="0" dx="1.8" dy="2.7" layer="1"/>
<text x="-2.54" y="1.5875" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.032" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-2.4892" y1="-1.3208" x2="-1.6393" y2="1.3292" layer="51"/>
<rectangle x1="1.651" y1="-1.3208" x2="2.5009" y2="1.3292" layer="51"/>
</package>
<package name="0603-RES">
<wire x1="-1.473" y1="0.983" x2="1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.983" x2="1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.983" x2="-1.473" y2="-0.983" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.983" x2="-1.473" y2="0.983" width="0.0508" layer="39"/>
<wire x1="-0.356" y1="0.432" x2="0.356" y2="0.432" width="0.1016" layer="51"/>
<wire x1="-0.356" y1="-0.419" x2="0.356" y2="-0.419" width="0.1016" layer="51"/>
<smd name="1" x="-0.85" y="0" dx="1.1" dy="1" layer="1"/>
<smd name="2" x="0.85" y="0" dx="1.1" dy="1" layer="1"/>
<text x="-0.889" y="0.762" size="0.4064" layer="25" font="vector">&gt;NAME</text>
<text x="-1.016" y="-1.143" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.8382" y1="-0.4699" x2="-0.3381" y2="0.4801" layer="51"/>
<rectangle x1="0.3302" y1="-0.4699" x2="0.8303" y2="0.4801" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<rectangle x1="-0.2286" y1="-0.381" x2="0.2286" y2="0.381" layer="21"/>
</package>
<package name="0402-RES">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;&lt;p&gt;
chip</description>
<wire x1="-0.245" y1="0.224" x2="0.245" y2="0.224" width="0.1524" layer="51"/>
<wire x1="0.245" y1="-0.224" x2="-0.245" y2="-0.224" width="0.1524" layer="51"/>
<wire x1="-1.473" y1="0.483" x2="1.473" y2="0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="0.483" x2="1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="1.473" y1="-0.483" x2="-1.473" y2="-0.483" width="0.0508" layer="39"/>
<wire x1="-1.473" y1="-0.483" x2="-1.473" y2="0.483" width="0.0508" layer="39"/>
<smd name="1" x="-0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<smd name="2" x="0.65" y="0" dx="0.7" dy="0.9" layer="1"/>
<text x="-0.889" y="0.6985" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.0795" y="-1.143" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-0.554" y1="-0.3048" x2="-0.254" y2="0.2951" layer="51"/>
<rectangle x1="0.2588" y1="-0.3048" x2="0.5588" y2="0.2951" layer="51"/>
<rectangle x1="-0.1999" y1="-0.3" x2="0.1999" y2="0.3" layer="35"/>
<rectangle x1="-0.2032" y1="-0.3556" x2="0.2032" y2="0.3556" layer="21"/>
</package>
<package name="1/6W-RES">
<description>1/6W Thru-hole Resistor - *UNPROVEN*</description>
<wire x1="-1.55" y1="0.85" x2="-1.55" y2="-0.85" width="0.2032" layer="21"/>
<wire x1="-1.55" y1="-0.85" x2="1.55" y2="-0.85" width="0.2032" layer="21"/>
<wire x1="1.55" y1="-0.85" x2="1.55" y2="0.85" width="0.2032" layer="21"/>
<wire x1="1.55" y1="0.85" x2="-1.55" y2="0.85" width="0.2032" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.762"/>
<pad name="2" x="2.5" y="0" drill="0.762"/>
<text x="-1.2662" y="0.9552" size="0.6096" layer="25">&gt;NAME</text>
<text x="-1.423" y="-0.4286" size="0.8128" layer="21" ratio="15">&gt;VALUE</text>
</package>
<package name="R2512">
<wire x1="-2.362" y1="1.473" x2="2.387" y2="1.473" width="0.1524" layer="51"/>
<wire x1="-2.362" y1="-1.473" x2="2.387" y2="-1.473" width="0.1524" layer="51"/>
<smd name="1" x="-2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<smd name="2" x="2.8" y="0" dx="1.8" dy="3.2" layer="1"/>
<text x="-2.54" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-3.2004" y1="-1.5494" x2="-2.3505" y2="1.5507" layer="51"/>
<rectangle x1="2.3622" y1="-1.5494" x2="3.2121" y2="1.5507" layer="51"/>
</package>
<package name="AXIAL-0.4">
<description>1/4W Resistor, 0.4" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-3.15" y1="-1.2" x2="-3.15" y2="1.2" width="0.2032" layer="21"/>
<wire x1="-3.15" y1="1.2" x2="3.15" y2="1.2" width="0.2032" layer="21"/>
<wire x1="3.15" y1="1.2" x2="3.15" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="3.15" y1="-1.2" x2="-3.15" y2="-1.2" width="0.2032" layer="21"/>
<pad name="P$1" x="-5.08" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="5.08" y="0" drill="0.9" diameter="1.8796"/>
<text x="-3.175" y="1.905" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-2.286" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.5">
<description>1/2W Resistor, 0.5" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-4.5" y1="-1.65" x2="-4.5" y2="1.65" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="1.65" x2="4.5" y2="1.65" width="0.2032" layer="21"/>
<wire x1="4.5" y1="1.65" x2="4.5" y2="-1.65" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-1.65" x2="-4.5" y2="-1.65" width="0.2032" layer="21"/>
<pad name="P$1" x="-6.35" y="0" drill="0.9" diameter="1.8796"/>
<pad name="P$2" x="6.35" y="0" drill="0.9" diameter="1.8796"/>
<text x="-4.445" y="2.54" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-3.429" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.6">
<description>1W Resistor, 0.6" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-5.75" y1="-2.25" x2="-5.75" y2="2.25" width="0.2032" layer="21"/>
<wire x1="-5.75" y1="2.25" x2="5.75" y2="2.25" width="0.2032" layer="21"/>
<wire x1="5.75" y1="2.25" x2="5.75" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="5.75" y1="-2.25" x2="-5.75" y2="-2.25" width="0.2032" layer="21"/>
<pad name="P$1" x="-7.62" y="0" drill="1.2" diameter="1.8796"/>
<pad name="P$2" x="7.62" y="0" drill="1.2" diameter="1.8796"/>
<text x="-5.715" y="3.175" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-4.064" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="AXIAL-0.8">
<description>2W Resistor, 0.8" wide&lt;p&gt;

Yageo CFR series &lt;a href="http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf"&gt;http://www.yageo.com/pdf/yageo/Leaded-R_CFR_2008.pdf&lt;/a&gt;</description>
<wire x1="-7.75" y1="-2.5" x2="-7.75" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-7.75" y1="2.5" x2="7.75" y2="2.5" width="0.2032" layer="21"/>
<wire x1="7.75" y1="2.5" x2="7.75" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="7.75" y1="-2.5" x2="-7.75" y2="-2.5" width="0.2032" layer="21"/>
<pad name="P$1" x="-10.16" y="0" drill="1.2" diameter="1.8796"/>
<pad name="P$2" x="10.16" y="0" drill="1.2" diameter="1.8796"/>
<text x="-7.62" y="3.175" size="0.8128" layer="25" font="vector" ratio="15">&gt;Name</text>
<text x="-5.969" y="-0.381" size="0.8128" layer="21" font="vector" ratio="15">&gt;Value</text>
</package>
<package name="EIA3528-KIT">
<description>&lt;h3&gt;EIA3528-KIT&lt;/h3&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has longer pads to make hand soldering easier.&lt;br&gt;</description>
<wire x1="-0.9" y1="-1.6" x2="-3.1" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-1.6" x2="-3.1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="1.55" x2="-0.9" y2="1.55" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.55" x2="2.7" y2="-1.55" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-1.55" x2="3.1" y2="-1.2" width="0.2032" layer="21"/>
<wire x1="3.1" y1="-1.2" x2="3.1" y2="1.25" width="0.2032" layer="21"/>
<wire x1="3.1" y1="1.25" x2="2.7" y2="1.55" width="0.2032" layer="21"/>
<wire x1="2.7" y1="1.55" x2="1" y2="1.55" width="0.2032" layer="21"/>
<wire x1="0.609" y1="1.311" x2="0.609" y2="-1.286" width="0.4" layer="21" style="longdash"/>
<smd name="C" x="-1.9" y="0" dx="1.7" dy="2.5" layer="1"/>
<smd name="A" x="1.9" y="0" dx="1.7" dy="2.5" layer="1"/>
<text x="-2.27" y="-1.27" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.24" y="-1.37" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="CAP-PTH-SMALL-KIT">
<description>&lt;h3&gt;CAP-PTH-SMALL-KIT&lt;/h3&gt;
Commonly used for small ceramic capacitors. Like our 0.1uF (http://www.sparkfun.com/products/8375) or 22pF caps (http://www.sparkfun.com/products/8571).&lt;br&gt;
&lt;br&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.254" layer="21"/>
<wire x1="-2.667" y1="1.27" x2="2.667" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.667" y1="1.27" x2="2.667" y2="-1.27" width="0.254" layer="21"/>
<wire x1="2.667" y1="-1.27" x2="-2.667" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-2.667" y1="-1.27" x2="-2.667" y2="1.27" width="0.254" layer="21"/>
<pad name="1" x="-1.397" y="0" drill="1.016" diameter="2.032" stop="no"/>
<pad name="2" x="1.397" y="0" drill="1.016" diameter="2.032" stop="no"/>
<polygon width="0.127" layer="30">
<vertex x="-1.4021" y="-0.9475" curve="-90"/>
<vertex x="-2.357" y="-0.0178" curve="-90.011749"/>
<vertex x="-1.4046" y="0.9576" curve="-90"/>
<vertex x="-0.4546" y="-0.0204" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-1.4046" y="-0.4395" curve="-90.012891"/>
<vertex x="-1.8491" y="-0.0153" curve="-90"/>
<vertex x="-1.4046" y="0.452" curve="-90"/>
<vertex x="-0.9627" y="-0.0051" curve="-90.012967"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="1.397" y="-0.9475" curve="-90"/>
<vertex x="0.4421" y="-0.0178" curve="-90.011749"/>
<vertex x="1.3945" y="0.9576" curve="-90"/>
<vertex x="2.3445" y="-0.0204" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="1.3945" y="-0.4395" curve="-90.012891"/>
<vertex x="0.95" y="-0.0153" curve="-90"/>
<vertex x="1.3945" y="0.452" curve="-90"/>
<vertex x="1.8364" y="-0.0051" curve="-90.012967"/>
</polygon>
</package>
<package name="AXIAL-0.3-KIT">
<description>&lt;h3&gt;AXIAL-0.3-KIT&lt;/h3&gt;

Commonly used for 1/4W through-hole resistors. 0.3" pitch between holes.&lt;br&gt;
&lt;br&gt;

&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of the AXIAL-0.3 package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="0" width="0.254" layer="21"/>
<wire x1="2.54" y1="0" x2="2.54" y2="-1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="-2.54" y2="-1.27" width="0.254" layer="21"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="0" width="0.254" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="0" x2="2.794" y2="0" width="0.254" layer="21"/>
<wire x1="-2.54" y1="0" x2="-2.794" y2="0" width="0.254" layer="21"/>
<pad name="P$1" x="-3.81" y="0" drill="1.016" diameter="2.032" stop="no"/>
<pad name="P$2" x="3.81" y="0" drill="1.016" diameter="2.032" stop="no"/>
<text x="-2.54" y="1.27" size="0.4064" layer="25" font="vector">&gt;Name</text>
<text x="-2.159" y="-0.762" size="1.27" layer="21" font="vector" ratio="15">&gt;Value</text>
<polygon width="0.127" layer="30">
<vertex x="3.8201" y="-0.9449" curve="-90"/>
<vertex x="2.8652" y="-0.0152" curve="-90.011749"/>
<vertex x="3.8176" y="0.9602" curve="-90"/>
<vertex x="4.7676" y="-0.0178" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="3.8176" y="-0.4369" curve="-90.012891"/>
<vertex x="3.3731" y="-0.0127" curve="-90"/>
<vertex x="3.8176" y="0.4546" curve="-90"/>
<vertex x="4.2595" y="-0.0025" curve="-90.012967"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="-3.8075" y="-0.9525" curve="-90"/>
<vertex x="-4.7624" y="-0.0228" curve="-90.011749"/>
<vertex x="-3.81" y="0.9526" curve="-90"/>
<vertex x="-2.86" y="-0.0254" curve="-90.024193"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-3.81" y="-0.4445" curve="-90.012891"/>
<vertex x="-4.2545" y="-0.0203" curve="-90"/>
<vertex x="-3.81" y="0.447" curve="-90"/>
<vertex x="-3.3681" y="-0.0101" curve="-90.012967"/>
</polygon>
</package>
</packages>
<symbols>
<symbol name="CAP_POL">
<wire x1="-2.54" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202" cap="flat"/>
<wire x1="-2.4669" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.376341" cap="flat"/>
<text x="1.016" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.253" y1="0.668" x2="-1.364" y2="0.795" layer="94"/>
<rectangle x1="-1.872" y1="0.287" x2="-1.745" y2="1.176" layer="94"/>
<pin name="+" x="0" y="2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="-" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="3.3V">
<wire x1="0.762" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="-0.762" y2="1.27" width="0.254" layer="94"/>
<text x="-1.016" y="3.556" size="1.778" layer="96">&gt;VALUE</text>
<pin name="3.3V" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
<symbol name="USB">
<wire x1="5.08" y1="8.89" x2="0" y2="8.89" width="0.254" layer="94"/>
<wire x1="0" y1="8.89" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="5.08" y2="-1.27" width="0.254" layer="94"/>
<text x="3.81" y="0" size="2.54" layer="94" rot="R90">USB</text>
<pin name="D+" x="-2.54" y="7.62" visible="pad" length="short"/>
<pin name="D-" x="-2.54" y="5.08" visible="pad" length="short"/>
<pin name="VBUS" x="-2.54" y="2.54" visible="pad" length="short"/>
<pin name="GND" x="-2.54" y="0" visible="pad" length="short"/>
</symbol>
<symbol name="CAP">
<wire x1="0" y1="2.54" x2="0" y2="2.032" width="0.1524" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="0.508" width="0.1524" layer="94"/>
<text x="1.524" y="2.921" size="1.778" layer="95">&gt;NAME</text>
<text x="1.524" y="-2.159" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-2.032" y1="0.508" x2="2.032" y2="1.016" layer="94"/>
<rectangle x1="-2.032" y1="1.524" x2="2.032" y2="2.032" layer="94"/>
<pin name="1" x="0" y="5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="0" y="-2.54" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
</symbol>
<symbol name="RESISTOR">
<wire x1="-2.54" y1="0" x2="-2.159" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-2.159" y1="1.016" x2="-1.524" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-1.524" y1="-1.016" x2="-0.889" y2="1.016" width="0.1524" layer="94"/>
<wire x1="-0.889" y1="1.016" x2="-0.254" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="-0.254" y1="-1.016" x2="0.381" y2="1.016" width="0.1524" layer="94"/>
<wire x1="0.381" y1="1.016" x2="1.016" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-1.016" x2="1.651" y2="1.016" width="0.1524" layer="94"/>
<wire x1="1.651" y1="1.016" x2="2.286" y2="-1.016" width="0.1524" layer="94"/>
<wire x1="2.286" y1="-1.016" x2="2.54" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CAP_POL" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor Polarized&lt;/b&gt;
These are standard SMD and PTH capacitors. Normally 10uF, 47uF, and 100uF in electrolytic and tantalum varieties. Always verify the external diameter of the through hole cap, it varies with capacity, voltage, and manufacturer. The EIA devices should be standard.</description>
<gates>
<gate name="G$1" symbol="CAP_POL" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="EIA3216">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528" package="EIA3528">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="CPOL-RADIAL-100UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CPOL-RADIAL-10UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="7343" package="EIA7343">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="G" package="PANASONIC_G">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="E" package="PANASONIC_E">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="C" package="PANASONIC_C">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="F80" package="NIPPON_F80">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="D" package="PANASONIC_D">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH3" package="CPOL-RADIAL-1000UF-63V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH4" package="CPOL-RADIAL-1000UF-25V">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="VISHAY_C">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="H13" package="PANASONIC_H13">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="6032" package="EIA6032">
<connects>
<connect gate="G$1" pin="+" pad="P$1"/>
<connect gate="G$1" pin="-" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EN_J2" package="EN_J2">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3528-KIT" package="EIA3528-KIT">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206-KIT" package="EIA3216-KIT">
<connects>
<connect gate="G$1" pin="+" pad="A"/>
<connect gate="G$1" pin="-" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="3.3V" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="3.3V" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USB" prefix="X">
<description>&lt;b&gt;USB Connectors&lt;/b&gt;
&lt;p&gt;USB-B-PTH is fully proven SKU : PRT-00139
&lt;p&gt;USB-miniB is fully proven SKU : PRT-00587
&lt;p&gt;USB-A-PCB is untested.
&lt;p&gt;USB-A-H is throughly reviewed, but untested. Spark Fun Electronics SKU : PRT-00437
&lt;p&gt;USB-B-SMT is throughly reviewed, but untested. Needs silkscreen touching up.
&lt;p&gt;USB-A-S has not been used/tested
&lt;p&gt;USB-MB-H has not been used/tested</description>
<gates>
<gate name="G$1" symbol="USB" x="0" y="0"/>
</gates>
<devices>
<device name="-A-H" package="USB-A-H">
<connects>
<connect gate="G$1" pin="D+" pad="D-"/>
<connect gate="G$1" pin="D-" pad="D+"/>
<connect gate="G$1" pin="GND" pad="VBUS"/>
<connect gate="G$1" pin="VBUS" pad="GND"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-A-S" package="USB-A-S">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-MB-H" package="USB-MB-H">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-B-S" package="USB-B-SMT">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VUSB"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="OLD" package="USB-MINIB-OLD">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH" package="USB-B-PTH">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-JST-2MM-SMT" package="S4B-PH">
<connects>
<connect gate="G$1" pin="D+" pad="2"/>
<connect gate="G$1" pin="D-" pad="3"/>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="VBUS" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="USB-MINIB">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PCB" package="USB-A-PCB">
<connects>
<connect gate="G$1" pin="D+" pad="USB_P"/>
<connect gate="G$1" pin="D-" pad="USB_M"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="5V"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-VERTICAL" package="USB-B-PTH-VERTICAL">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="USB-A-S-NOSILK" package="USB-A-S-NOSILK">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-A-SMD" package="USB-A-S-NOSILK-FEMALE">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-SMD-NS" package="USB-MINIB-NOSTOP">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_" package="USB-A-S-SILK-FEMALE">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-MICROB" package="USB-MICROB">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP" prefix="C" uservalue="yes">
<description>&lt;b&gt;Capacitor&lt;/b&gt;
Standard 0603 ceramic capacitor, and 0.1" leaded capacitor.</description>
<gates>
<gate name="G$1" symbol="CAP" x="0" y="0"/>
</gates>
<devices>
<device name="PTH" package="CAP-PTH-SMALL">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH2" package="CAP-PTH-SMALL2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH3" package="CAP-PTH-LARGE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="GRM43D">
<connects>
<connect gate="G$1" pin="1" pad="A"/>
<connect gate="G$1" pin="2" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603-CAP" package="0603-CAP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402-CAP" package="0402-CAP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH1" package="CAP-PTH-5MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="_" package="AXIAL-5MM">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1210" package="1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="ASMD" package="CTZ3">
<connects>
<connect gate="G$1" pin="1" pad="+"/>
<connect gate="G$1" pin="2" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KIT" package="CAP-PTH-SMALL-KIT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RESISTOR" prefix="R" uservalue="yes">
<description>&lt;b&gt;Resistor&lt;/b&gt;
Basic schematic elements and footprints for 0603, 1206, and PTH resistors.</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AXIAL-0.3" package="AXIAL-0.3">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2010" package="R2010">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805-RES" package="0805">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603-RES" package="0603-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0402-RES" package="0402-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/6W" package="1/6W-RES">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2512" package="R2512">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/4W" package="AXIAL-0.4">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1/2W" package="AXIAL-0.5">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-1W" package="AXIAL-0.6">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH-2W" package="AXIAL-0.8">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="KIT" package="AXIAL-0.3-KIT">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="crystal">
<packages>
<package name="86SMX">
<description>&lt;b&gt;CRYSTAL RESONATOR&lt;/b&gt;</description>
<wire x1="-3.81" y1="1.905" x2="2.413" y2="1.905" width="0.0508" layer="21"/>
<wire x1="-3.81" y1="2.286" x2="2.413" y2="2.286" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-1.905" x2="2.413" y2="-1.905" width="0.0508" layer="21"/>
<wire x1="-3.81" y1="-2.286" x2="2.413" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="-6.604" y1="-2.286" x2="-6.604" y2="2.286" width="0.1524" layer="21"/>
<wire x1="-5.334" y1="1.905" x2="-5.334" y2="1.016" width="0.0508" layer="51"/>
<wire x1="-5.334" y1="-1.905" x2="-3.81" y2="-1.905" width="0.0508" layer="51"/>
<wire x1="-6.35" y1="-2.286" x2="-5.969" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="-5.969" y1="-2.286" x2="-4.191" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="-4.191" y1="-2.286" x2="-3.81" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="-5.969" y1="-2.54" x2="-4.191" y2="-2.54" width="0.1524" layer="51"/>
<wire x1="-6.35" y1="-2.2098" x2="-6.604" y2="-2.286" width="0.0508" layer="21"/>
<wire x1="-6.604" y1="-2.286" x2="-6.35" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="-5.969" y1="-2.54" x2="-5.969" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="-5.334" y1="1.016" x2="-5.334" y2="-1.016" width="0.0508" layer="21"/>
<wire x1="-5.334" y1="-1.016" x2="-5.334" y2="-1.905" width="0.0508" layer="51"/>
<wire x1="-5.334" y1="-1.905" x2="-6.35" y2="-2.2098" width="0.0508" layer="51"/>
<wire x1="-4.191" y1="-2.54" x2="-4.191" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="-5.969" y1="2.54" x2="-4.191" y2="2.54" width="0.1524" layer="51"/>
<wire x1="-5.334" y1="1.905" x2="-3.81" y2="1.905" width="0.0508" layer="51"/>
<wire x1="-6.35" y1="2.286" x2="-5.969" y2="2.286" width="0.1524" layer="51"/>
<wire x1="-5.969" y1="2.286" x2="-4.191" y2="2.286" width="0.1524" layer="51"/>
<wire x1="-4.191" y1="2.286" x2="-3.81" y2="2.286" width="0.1524" layer="51"/>
<wire x1="-6.604" y1="2.286" x2="-6.35" y2="2.286" width="0.1524" layer="21"/>
<wire x1="-6.35" y1="2.2098" x2="-6.604" y2="2.286" width="0.0508" layer="21"/>
<wire x1="-5.969" y1="2.54" x2="-5.969" y2="2.286" width="0.1524" layer="51"/>
<wire x1="-5.334" y1="1.905" x2="-6.35" y2="2.2098" width="0.0508" layer="51"/>
<wire x1="-4.191" y1="2.54" x2="-4.191" y2="2.286" width="0.1524" layer="51"/>
<wire x1="6.604" y1="2.286" x2="6.604" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="6.223" y1="-1.905" x2="6.223" y2="1.905" width="0.0508" layer="21"/>
<wire x1="6.223" y1="-1.905" x2="6.604" y2="-2.286" width="0.0508" layer="21"/>
<wire x1="6.223" y1="-2.286" x2="6.604" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="2.794" y1="-2.54" x2="5.842" y2="-2.54" width="0.1524" layer="51"/>
<wire x1="2.794" y1="-2.286" x2="2.794" y2="-2.54" width="0.1524" layer="51"/>
<wire x1="5.842" y1="-2.54" x2="5.842" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="2.413" y1="-2.286" x2="6.223" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="2.413" y1="-1.905" x2="6.223" y2="-1.905" width="0.0508" layer="51"/>
<wire x1="6.223" y1="1.905" x2="6.604" y2="2.286" width="0.0508" layer="21"/>
<wire x1="6.223" y1="2.286" x2="6.604" y2="2.286" width="0.1524" layer="21"/>
<wire x1="2.794" y1="2.54" x2="5.842" y2="2.54" width="0.1524" layer="51"/>
<wire x1="2.794" y1="2.286" x2="2.794" y2="2.54" width="0.1524" layer="51"/>
<wire x1="5.842" y1="2.54" x2="5.842" y2="2.286" width="0.1524" layer="51"/>
<wire x1="2.413" y1="1.905" x2="6.223" y2="1.905" width="0.0508" layer="51"/>
<wire x1="2.413" y1="2.286" x2="6.223" y2="2.286" width="0.1524" layer="51"/>
<wire x1="-0.254" y1="1.651" x2="-0.254" y2="0.381" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="0.381" x2="0.254" y2="0.381" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.381" x2="0.254" y2="1.651" width="0.1524" layer="21"/>
<wire x1="0.254" y1="1.651" x2="-0.254" y2="1.651" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.651" x2="0.635" y2="1.016" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.016" x2="0.635" y2="0.381" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.016" x2="1.016" y2="1.016" width="0.0508" layer="21"/>
<wire x1="-0.635" y1="1.651" x2="-0.635" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.016" x2="-0.635" y2="0.381" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.016" x2="-1.016" y2="1.016" width="0.0508" layer="21"/>
<smd name="2" x="4.318" y="-2.286" dx="3.556" dy="2.1844" layer="1"/>
<smd name="3" x="4.318" y="2.286" dx="3.556" dy="2.1844" layer="1"/>
<smd name="1" x="-5.08" y="-2.286" dx="2.286" dy="2.1844" layer="1"/>
<smd name="4" x="-5.08" y="2.286" dx="2.286" dy="2.1844" layer="1"/>
<text x="-3.683" y="2.54" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.683" y="-3.81" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="HC49/S">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-3.048" y1="-2.159" x2="3.048" y2="-2.159" width="0.4064" layer="21"/>
<wire x1="-3.048" y1="2.159" x2="3.048" y2="2.159" width="0.4064" layer="21"/>
<wire x1="-3.048" y1="-1.651" x2="3.048" y2="-1.651" width="0.1524" layer="21"/>
<wire x1="3.048" y1="1.651" x2="-3.048" y2="1.651" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="0.762" x2="0.254" y2="0.762" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.762" x2="0.254" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="0.254" y1="-0.762" x2="-0.254" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-0.762" x2="-0.254" y2="0.762" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0.762" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0.762" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="1.27" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-1.27" y2="0" width="0.1524" layer="21"/>
<wire x1="-3.048" y1="2.159" x2="-3.048" y2="-2.159" width="0.4064" layer="21" curve="180"/>
<wire x1="3.048" y1="-2.159" x2="3.048" y2="2.159" width="0.4064" layer="21" curve="180"/>
<wire x1="-3.048" y1="1.651" x2="-3.048" y2="-1.651" width="0.1524" layer="21" curve="180"/>
<wire x1="3.048" y1="-1.651" x2="3.048" y2="1.651" width="0.1524" layer="21" curve="180"/>
<pad name="1" x="-2.413" y="0" drill="0.8128"/>
<pad name="2" x="2.413" y="0" drill="0.8128"/>
<text x="-5.08" y="2.667" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-3.937" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-4.445" y1="-2.54" x2="4.445" y2="2.54" layer="43"/>
<rectangle x1="-5.08" y1="-1.905" x2="-4.445" y2="1.905" layer="43"/>
<rectangle x1="-5.715" y1="-1.27" x2="-5.08" y2="1.27" layer="43"/>
<rectangle x1="4.445" y1="-1.905" x2="5.08" y2="1.905" layer="43"/>
<rectangle x1="5.08" y1="-1.27" x2="5.715" y2="1.27" layer="43"/>
</package>
<package name="HC49GW">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-5.08" y1="-6.35" x2="5.08" y2="-6.35" width="0.8128" layer="21"/>
<wire x1="4.445" y1="6.731" x2="1.016" y2="6.731" width="0.1524" layer="21"/>
<wire x1="1.016" y1="6.731" x2="-1.016" y2="6.731" width="0.1524" layer="51"/>
<wire x1="-1.016" y1="6.731" x2="-4.445" y2="6.731" width="0.1524" layer="21"/>
<wire x1="4.445" y1="6.731" x2="5.08" y2="6.096" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.08" y1="6.096" x2="-4.445" y2="6.731" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.3302" y1="5.08" x2="-0.3302" y2="2.54" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="2.54" x2="0.3048" y2="2.54" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="2.54" x2="0.3048" y2="5.08" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="5.08" x2="-0.3302" y2="5.08" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="5.08" x2="0.9398" y2="3.81" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="5.08" x2="-0.9398" y2="3.81" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="3.81" x2="2.032" y2="3.81" width="0.1524" layer="21"/>
<wire x1="0.9398" y1="3.81" x2="0.9398" y2="2.54" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="3.81" x2="-2.032" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-0.9398" y1="3.81" x2="-0.9398" y2="2.54" width="0.3048" layer="21"/>
<wire x1="-2.413" y1="-6.604" x2="-2.413" y2="-8.255" width="0.6096" layer="51"/>
<wire x1="2.413" y1="-6.477" x2="2.413" y2="-8.382" width="0.6096" layer="51"/>
<wire x1="5.08" y1="-6.35" x2="5.08" y2="6.096" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="6.096" x2="-5.08" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="0" y1="8.382" x2="0" y2="6.985" width="0.6096" layer="51"/>
<smd name="1" x="-2.413" y="-8.001" dx="1.27" dy="2.54" layer="1"/>
<smd name="2" x="2.413" y="-8.001" dx="1.27" dy="2.54" layer="1"/>
<smd name="3" x="0" y="8.001" dx="1.27" dy="2.794" layer="1"/>
<text x="-5.588" y="-5.08" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-2.54" y="-5.08" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-5.715" y1="-8.255" x2="5.715" y2="8.255" layer="43"/>
</package>
<package name="HC49TL-H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="5.334" y1="-5.715" x2="-5.461" y2="-5.715" width="0.8128" layer="21"/>
<wire x1="4.445" y1="7.366" x2="1.143" y2="7.366" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="7.366" x2="-4.445" y2="7.366" width="0.1524" layer="21"/>
<wire x1="4.445" y1="7.366" x2="5.08" y2="6.731" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.08" y1="6.731" x2="-4.445" y2="7.366" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.3302" y1="5.715" x2="-0.3302" y2="3.175" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="3.175" x2="0.3048" y2="3.175" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="3.175" x2="0.3048" y2="5.715" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="5.715" x2="-0.3302" y2="5.715" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="5.715" x2="0.9398" y2="4.445" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="5.715" x2="-0.9398" y2="4.445" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="4.445" x2="2.032" y2="4.445" width="0.1524" layer="21"/>
<wire x1="0.9398" y1="4.445" x2="0.9398" y2="3.175" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="4.445" x2="-2.032" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-0.9398" y1="4.445" x2="-0.9398" y2="3.175" width="0.3048" layer="21"/>
<wire x1="-2.413" y1="-5.842" x2="-2.413" y2="-7.62" width="0.6096" layer="51"/>
<wire x1="2.413" y1="-5.842" x2="2.413" y2="-7.62" width="0.6096" layer="51"/>
<wire x1="5.08" y1="-5.715" x2="5.08" y2="6.731" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="6.731" x2="-5.08" y2="-5.715" width="0.1524" layer="21"/>
<wire x1="1.143" y1="7.366" x2="-1.143" y2="7.366" width="0.1524" layer="51"/>
<wire x1="0" y1="7.874" x2="0" y2="7.62" width="0.6096" layer="51"/>
<pad name="1" x="-2.413" y="-7.62" drill="0.8128"/>
<pad name="2" x="2.413" y="-7.62" drill="0.8128"/>
<pad name="3" x="0" y="7.874" drill="0.8128"/>
<text x="-5.461" y="-4.445" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-2.54" y="-4.699" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-0.3048" y1="7.366" x2="0.3048" y2="7.5692" layer="51"/>
<rectangle x1="-6.35" y1="-6.985" x2="6.35" y2="-4.445" layer="43"/>
<rectangle x1="-5.715" y1="-4.445" x2="5.715" y2="8.255" layer="43"/>
</package>
<package name="HC49U-H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-5.08" y1="-3.175" x2="5.08" y2="-3.175" width="0.8128" layer="21"/>
<wire x1="4.445" y1="9.906" x2="-4.445" y2="9.906" width="0.1524" layer="21"/>
<wire x1="4.445" y1="9.906" x2="5.08" y2="9.271" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.08" y1="9.271" x2="-4.445" y2="9.906" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.3302" y1="8.255" x2="-0.3302" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="5.715" x2="0.3048" y2="5.715" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="5.715" x2="0.3048" y2="8.255" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="8.255" x2="-0.3302" y2="8.255" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="8.255" x2="0.9398" y2="6.985" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="8.255" x2="-0.9398" y2="6.985" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="6.985" x2="1.905" y2="6.985" width="0.1524" layer="21"/>
<wire x1="0.9398" y1="6.985" x2="0.9398" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="6.985" x2="-1.905" y2="6.985" width="0.1524" layer="21"/>
<wire x1="-0.9398" y1="6.985" x2="-0.9398" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-2.413" y1="-3.302" x2="-2.413" y2="-5.08" width="0.6096" layer="51"/>
<wire x1="2.413" y1="-3.302" x2="2.413" y2="-5.08" width="0.6096" layer="51"/>
<wire x1="5.08" y1="-3.175" x2="5.08" y2="9.271" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="9.271" x2="-5.08" y2="-3.175" width="0.1524" layer="21"/>
<pad name="1" x="-2.413" y="-5.08" drill="0.8128"/>
<pad name="2" x="2.413" y="-5.08" drill="0.8128"/>
<text x="-5.461" y="-1.397" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-2.54" y="-2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-6.35" y1="-4.445" x2="6.35" y2="-1.905" layer="43"/>
<rectangle x1="-5.715" y1="-1.905" x2="5.715" y2="10.795" layer="43"/>
</package>
<package name="HC49U-LM">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-5.08" y1="-3.175" x2="5.08" y2="-3.175" width="0.8128" layer="21"/>
<wire x1="4.445" y1="9.906" x2="-4.445" y2="9.906" width="0.1524" layer="21"/>
<wire x1="4.445" y1="9.906" x2="5.08" y2="9.271" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.08" y1="9.271" x2="-4.445" y2="9.906" width="0.1524" layer="21" curve="-90"/>
<wire x1="-4.572" y1="3.81" x2="4.572" y2="3.81" width="0.6096" layer="21"/>
<wire x1="-0.3302" y1="8.255" x2="-0.3302" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="5.715" x2="0.3048" y2="5.715" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="5.715" x2="0.3048" y2="8.255" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="8.255" x2="-0.3302" y2="8.255" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="8.255" x2="0.9398" y2="6.985" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="8.255" x2="-0.9398" y2="6.985" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="6.985" x2="2.54" y2="6.985" width="0.1524" layer="21"/>
<wire x1="0.9398" y1="6.985" x2="0.9398" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="6.985" x2="-2.54" y2="6.985" width="0.1524" layer="21"/>
<wire x1="-0.9398" y1="6.985" x2="-0.9398" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-2.413" y1="-3.302" x2="-2.413" y2="-5.08" width="0.6096" layer="51"/>
<wire x1="2.413" y1="-3.302" x2="2.413" y2="-5.08" width="0.6096" layer="51"/>
<wire x1="5.08" y1="3.048" x2="5.08" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="5.08" y1="4.572" x2="5.08" y2="9.271" width="0.1524" layer="21"/>
<wire x1="4.572" y1="3.81" x2="5.08" y2="3.81" width="0.6096" layer="51"/>
<wire x1="5.08" y1="3.81" x2="5.715" y2="3.81" width="0.6096" layer="51"/>
<wire x1="5.08" y1="3.81" x2="5.08" y2="3.048" width="0.1524" layer="51"/>
<wire x1="5.08" y1="3.81" x2="5.08" y2="4.572" width="0.1524" layer="51"/>
<wire x1="-5.08" y1="3.175" x2="-5.08" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="4.445" x2="-5.08" y2="9.271" width="0.1524" layer="21"/>
<wire x1="-4.699" y1="3.81" x2="-5.715" y2="3.81" width="0.6096" layer="51"/>
<wire x1="-5.08" y1="4.445" x2="-5.08" y2="3.175" width="0.1524" layer="51"/>
<pad name="1" x="-2.413" y="-5.08" drill="0.8128"/>
<pad name="2" x="2.413" y="-5.08" drill="0.8128"/>
<pad name="M" x="-5.715" y="3.81" drill="0.8128"/>
<pad name="M1" x="5.715" y="3.81" drill="0.8128"/>
<text x="-5.08" y="10.414" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.572" y="0" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-5.715" y1="-5.08" x2="5.715" y2="10.795" layer="43"/>
</package>
<package name="HC49U-V">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-2.921" y1="-2.286" x2="2.921" y2="-2.286" width="0.4064" layer="21"/>
<wire x1="-2.921" y1="2.286" x2="2.921" y2="2.286" width="0.4064" layer="21"/>
<wire x1="-2.921" y1="-1.778" x2="2.921" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="2.921" y1="1.778" x2="-2.921" y2="1.778" width="0.1524" layer="21"/>
<wire x1="2.921" y1="1.778" x2="2.921" y2="-1.778" width="0.1524" layer="21" curve="-180"/>
<wire x1="2.921" y1="2.286" x2="2.921" y2="-2.286" width="0.4064" layer="21" curve="-180"/>
<wire x1="-2.921" y1="2.286" x2="-2.921" y2="-2.286" width="0.4064" layer="21" curve="180"/>
<wire x1="-2.921" y1="1.778" x2="-2.921" y2="-1.778" width="0.1524" layer="21" curve="180"/>
<wire x1="-0.254" y1="0.889" x2="0.254" y2="0.889" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.889" x2="0.254" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="0.254" y1="-0.889" x2="-0.254" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-0.889" x2="-0.254" y2="0.889" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0.889" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0.889" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.889" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="1.27" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-1.27" y2="0" width="0.1524" layer="21"/>
<pad name="1" x="-2.413" y="0" drill="0.8128"/>
<pad name="2" x="2.413" y="0" drill="0.8128"/>
<text x="-5.08" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.81" y1="-2.794" x2="3.81" y2="2.794" layer="43"/>
<rectangle x1="-4.318" y1="-2.54" x2="-3.81" y2="2.54" layer="43"/>
<rectangle x1="-4.826" y1="-2.286" x2="-4.318" y2="2.286" layer="43"/>
<rectangle x1="-5.334" y1="-1.778" x2="-4.826" y2="1.778" layer="43"/>
<rectangle x1="-5.588" y1="-1.27" x2="-5.334" y2="1.016" layer="43"/>
<rectangle x1="3.81" y1="-2.54" x2="4.318" y2="2.54" layer="43"/>
<rectangle x1="4.318" y1="-2.286" x2="4.826" y2="2.286" layer="43"/>
<rectangle x1="4.826" y1="-1.778" x2="5.334" y2="1.778" layer="43"/>
<rectangle x1="5.334" y1="-1.016" x2="5.588" y2="1.016" layer="43"/>
</package>
<package name="HC49U70">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-3.048" y1="-2.54" x2="3.048" y2="-2.54" width="0.4064" layer="21"/>
<wire x1="-3.048" y1="2.54" x2="3.048" y2="2.54" width="0.4064" layer="21"/>
<wire x1="-3.048" y1="-2.032" x2="3.048" y2="-2.032" width="0.1524" layer="21"/>
<wire x1="-0.3302" y1="1.016" x2="-0.3302" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-0.3302" y1="-1.016" x2="0.3048" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="0.3048" y1="-1.016" x2="0.3048" y2="1.016" width="0.1524" layer="21"/>
<wire x1="0.3048" y1="1.016" x2="-0.3302" y2="1.016" width="0.1524" layer="21"/>
<wire x1="0.6858" y1="1.016" x2="0.6858" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.6858" y1="1.016" x2="-0.6858" y2="0" width="0.1524" layer="21"/>
<wire x1="0.6858" y1="0" x2="1.397" y2="0" width="0.1524" layer="21"/>
<wire x1="0.6858" y1="0" x2="0.6858" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-0.6858" y1="0" x2="-1.397" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.6858" y1="0" x2="-0.6858" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-3.048" y1="2.54" x2="-3.048" y2="-2.54" width="0.4064" layer="21" curve="180"/>
<wire x1="3.048" y1="2.54" x2="3.048" y2="-2.54" width="0.4064" layer="21" curve="-180"/>
<wire x1="-3.048" y1="-2.032" x2="-3.048" y2="2.032" width="0.1524" layer="21" curve="-180"/>
<wire x1="3.048" y1="2.032" x2="3.048" y2="-2.032" width="0.1524" layer="21" curve="-180"/>
<wire x1="3.048" y1="2.032" x2="-3.048" y2="2.032" width="0.1524" layer="21"/>
<pad name="1" x="-2.413" y="0" drill="0.8128"/>
<pad name="2" x="2.413" y="0" drill="0.8128"/>
<text x="-5.08" y="3.175" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-4.445" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-4.572" y1="-2.794" x2="-4.064" y2="2.794" layer="43"/>
<rectangle x1="-5.08" y1="-2.54" x2="-4.572" y2="2.54" layer="43"/>
<rectangle x1="-5.588" y1="-2.032" x2="-5.08" y2="2.032" layer="43"/>
<rectangle x1="-5.842" y1="-1.27" x2="-5.588" y2="1.27" layer="43"/>
<rectangle x1="-4.064" y1="-3.048" x2="4.064" y2="3.048" layer="43"/>
<rectangle x1="4.064" y1="-2.794" x2="4.572" y2="2.794" layer="43"/>
<rectangle x1="4.572" y1="-2.54" x2="5.08" y2="2.54" layer="43"/>
<rectangle x1="5.08" y1="-2.032" x2="5.588" y2="2.032" layer="43"/>
<rectangle x1="5.588" y1="-1.27" x2="5.842" y2="1.27" layer="43"/>
</package>
<package name="HC49UP">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-5.1091" y1="1.143" x2="-3.429" y2="2.0321" width="0.0508" layer="21" curve="-55.770993"/>
<wire x1="-5.715" y1="1.143" x2="-5.715" y2="2.159" width="0.1524" layer="21"/>
<wire x1="3.429" y1="2.032" x2="5.1091" y2="1.143" width="0.0508" layer="21" curve="-55.772485"/>
<wire x1="5.715" y1="1.143" x2="5.715" y2="2.159" width="0.1524" layer="21"/>
<wire x1="3.429" y1="-1.27" x2="-3.429" y2="-1.27" width="0.0508" layer="21"/>
<wire x1="3.429" y1="-2.032" x2="-3.429" y2="-2.032" width="0.0508" layer="21"/>
<wire x1="-3.429" y1="1.27" x2="3.429" y2="1.27" width="0.0508" layer="21"/>
<wire x1="5.461" y1="-2.413" x2="-5.461" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="5.715" y1="-0.381" x2="6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="5.715" y1="0.381" x2="6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="6.477" y1="-0.381" x2="6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="5.461" y1="-2.413" x2="5.715" y2="-2.159" width="0.1524" layer="21" curve="90"/>
<wire x1="5.715" y1="-1.143" x2="5.715" y2="1.143" width="0.1524" layer="51"/>
<wire x1="5.715" y1="-2.159" x2="5.715" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="3.429" y1="-1.27" x2="3.9826" y2="-1.143" width="0.0508" layer="21" curve="25.842828"/>
<wire x1="3.429" y1="1.27" x2="3.9826" y2="1.143" width="0.0508" layer="21" curve="-25.842828"/>
<wire x1="3.429" y1="-2.032" x2="5.109" y2="-1.1429" width="0.0508" layer="21" curve="55.771157"/>
<wire x1="3.9826" y1="-1.143" x2="3.9826" y2="1.143" width="0.0508" layer="51" curve="128.314524"/>
<wire x1="5.1091" y1="-1.143" x2="5.1091" y2="1.143" width="0.0508" layer="51" curve="68.456213"/>
<wire x1="-5.1091" y1="-1.143" x2="-3.429" y2="-2.032" width="0.0508" layer="21" curve="55.772485"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.9826" y2="1.143" width="0.0508" layer="51" curve="-128.314524"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.429" y2="-1.27" width="0.0508" layer="21" curve="25.842828"/>
<wire x1="-3.9826" y1="1.143" x2="-3.429" y2="1.27" width="0.0508" layer="21" curve="-25.842828"/>
<wire x1="-6.477" y1="-0.381" x2="-6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.1091" y1="-1.143" x2="-5.1091" y2="1.143" width="0.0508" layer="51" curve="-68.456213"/>
<wire x1="-5.715" y1="-1.143" x2="-5.715" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="-0.381" x2="-5.715" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="0.381" x2="-5.715" y2="1.143" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="-2.159" x2="-5.715" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.159" x2="-5.461" y2="-2.413" width="0.1524" layer="21" curve="90"/>
<wire x1="-5.715" y1="-0.381" x2="-6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="0.381" x2="-6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-3.429" y1="2.032" x2="3.429" y2="2.032" width="0.0508" layer="21"/>
<wire x1="5.461" y1="2.413" x2="-5.461" y2="2.413" width="0.1524" layer="21"/>
<wire x1="5.461" y1="2.413" x2="5.715" y2="2.159" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.715" y1="2.159" x2="-5.461" y2="2.413" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.254" y1="0.635" x2="-0.254" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-0.635" x2="0.254" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="-0.635" x2="0.254" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.635" x2="-0.254" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0.635" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-1.016" y2="0" width="0.0508" layer="21"/>
<wire x1="0.635" y1="0.635" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="1.016" y2="0" width="0.0508" layer="21"/>
<smd name="1" x="-4.826" y="0" dx="5.334" dy="1.9304" layer="1"/>
<smd name="2" x="4.826" y="0" dx="5.334" dy="1.9304" layer="1"/>
<text x="-5.715" y="2.794" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.715" y="-4.191" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-6.604" y1="-3.048" x2="6.604" y2="3.048" layer="43"/>
</package>
<package name="HC13U-H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-9.906" y1="-3.048" x2="-9.271" y2="-3.048" width="1.27" layer="21"/>
<wire x1="-9.271" y1="-3.048" x2="9.271" y2="-3.048" width="1.27" layer="21"/>
<wire x1="9.271" y1="-3.048" x2="9.906" y2="-3.048" width="1.27" layer="21"/>
<wire x1="8.636" y1="33.401" x2="-8.636" y2="33.401" width="0.1524" layer="21"/>
<wire x1="-9.271" y1="32.766" x2="-8.636" y2="33.401" width="0.1524" layer="21" curve="-90"/>
<wire x1="8.636" y1="33.401" x2="9.271" y2="32.766" width="0.1524" layer="21" curve="-90"/>
<wire x1="-9.017" y1="15.24" x2="9.017" y2="15.24" width="0.6096" layer="21"/>
<wire x1="-0.3302" y1="21.59" x2="-0.3302" y2="19.05" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="19.05" x2="0.3048" y2="19.05" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="19.05" x2="0.3048" y2="21.59" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="21.59" x2="-0.3302" y2="21.59" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="21.59" x2="0.9398" y2="20.32" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="21.59" x2="-0.9398" y2="20.32" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="20.32" x2="1.905" y2="20.32" width="0.1524" layer="21"/>
<wire x1="0.9398" y1="20.32" x2="0.9398" y2="19.05" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="20.32" x2="-1.905" y2="20.32" width="0.1524" layer="21"/>
<wire x1="-0.9398" y1="20.32" x2="-0.9398" y2="19.05" width="0.3048" layer="21"/>
<wire x1="9.144" y1="15.24" x2="10.16" y2="15.24" width="0.6096" layer="51"/>
<wire x1="-10.16" y1="15.24" x2="-9.144" y2="15.24" width="0.6096" layer="51"/>
<wire x1="-6.223" y1="-3.175" x2="-6.223" y2="-5.08" width="0.8128" layer="51"/>
<wire x1="6.223" y1="-3.175" x2="6.223" y2="-5.08" width="0.8128" layer="51"/>
<wire x1="9.271" y1="15.748" x2="9.271" y2="32.766" width="0.1524" layer="21"/>
<wire x1="9.271" y1="14.732" x2="9.271" y2="-3.048" width="0.1524" layer="21"/>
<wire x1="9.271" y1="15.748" x2="9.271" y2="14.732" width="0.1524" layer="51"/>
<wire x1="-9.271" y1="14.732" x2="-9.271" y2="-3.048" width="0.1524" layer="21"/>
<wire x1="-9.271" y1="15.748" x2="-9.271" y2="32.766" width="0.1524" layer="21"/>
<wire x1="-9.271" y1="15.748" x2="-9.271" y2="14.732" width="0.1524" layer="51"/>
<pad name="1" x="-6.223" y="-5.08" drill="1.016"/>
<pad name="2" x="6.223" y="-5.08" drill="1.016"/>
<pad name="M" x="-10.16" y="15.24" drill="0.8128"/>
<pad name="M1" x="10.16" y="15.24" drill="0.8128"/>
<text x="-10.16" y="0" size="1.778" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-5.08" y="-1.27" size="1.778" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-10.795" y1="-5.08" x2="10.795" y2="34.925" layer="43"/>
</package>
<package name="HC18U-H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="5.461" y1="-3.175" x2="5.08" y2="-3.175" width="0.8128" layer="21"/>
<wire x1="5.08" y1="-3.175" x2="-5.08" y2="-3.175" width="0.8128" layer="21"/>
<wire x1="-5.08" y1="-3.175" x2="-5.461" y2="-3.175" width="0.8128" layer="21"/>
<wire x1="4.445" y1="10.16" x2="-4.445" y2="10.16" width="0.1524" layer="21"/>
<wire x1="4.445" y1="10.16" x2="5.08" y2="9.525" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.08" y1="9.525" x2="-4.445" y2="10.16" width="0.1524" layer="21" curve="-90"/>
<wire x1="-4.572" y1="3.81" x2="4.572" y2="3.81" width="0.6096" layer="21"/>
<wire x1="-0.3302" y1="8.255" x2="-0.3302" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="5.715" x2="0.3048" y2="5.715" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="5.715" x2="0.3048" y2="8.255" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="8.255" x2="-0.3302" y2="8.255" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="8.255" x2="0.9398" y2="6.985" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="8.255" x2="-0.9398" y2="6.985" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="6.985" x2="2.54" y2="6.985" width="0.1524" layer="21"/>
<wire x1="0.9398" y1="6.985" x2="0.9398" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="6.985" x2="-2.54" y2="6.985" width="0.1524" layer="21"/>
<wire x1="-0.9398" y1="6.985" x2="-0.9398" y2="5.715" width="0.3048" layer="21"/>
<wire x1="-2.54" y1="-3.302" x2="-2.54" y2="-5.08" width="0.6096" layer="51"/>
<wire x1="2.54" y1="-3.302" x2="2.54" y2="-5.08" width="0.6096" layer="51"/>
<wire x1="5.08" y1="3.048" x2="5.08" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="5.08" y1="4.572" x2="5.08" y2="9.525" width="0.1524" layer="21"/>
<wire x1="4.572" y1="3.81" x2="5.08" y2="3.81" width="0.6096" layer="51"/>
<wire x1="5.08" y1="3.81" x2="5.715" y2="3.81" width="0.6096" layer="51"/>
<wire x1="5.08" y1="3.81" x2="5.08" y2="3.048" width="0.1524" layer="51"/>
<wire x1="5.08" y1="3.81" x2="5.08" y2="4.572" width="0.1524" layer="51"/>
<wire x1="-5.08" y1="3.175" x2="-5.08" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="4.445" x2="-5.08" y2="9.525" width="0.1524" layer="21"/>
<wire x1="-4.699" y1="3.81" x2="-5.715" y2="3.81" width="0.6096" layer="51"/>
<wire x1="-5.08" y1="4.445" x2="-5.08" y2="3.175" width="0.1524" layer="51"/>
<pad name="1" x="-2.54" y="-5.08" drill="0.8128"/>
<pad name="2" x="2.54" y="-5.08" drill="0.8128"/>
<pad name="M" x="-5.715" y="3.81" drill="0.8128"/>
<pad name="M1" x="5.715" y="3.81" drill="0.8128"/>
<text x="-5.08" y="10.668" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="-0.889" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-6.35" y1="-5.08" x2="6.35" y2="10.795" layer="43"/>
</package>
<package name="HC18U-V">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="1.905" width="0.4064" layer="21"/>
<wire x1="-5.08" y1="1.905" x2="-5.08" y2="-1.905" width="0.4064" layer="21"/>
<wire x1="-4.445" y1="2.54" x2="4.445" y2="2.54" width="0.4064" layer="21"/>
<wire x1="-4.445" y1="-2.54" x2="4.445" y2="-2.54" width="0.4064" layer="21"/>
<wire x1="4.445" y1="-2.54" x2="5.08" y2="-1.905" width="0.4064" layer="21" curve="90"/>
<wire x1="4.445" y1="2.54" x2="5.08" y2="1.905" width="0.4064" layer="21" curve="-90"/>
<wire x1="-5.08" y1="1.905" x2="-4.445" y2="2.54" width="0.4064" layer="21" curve="-90"/>
<wire x1="-5.08" y1="-1.905" x2="-4.445" y2="-2.54" width="0.4064" layer="21" curve="90"/>
<wire x1="-4.318" y1="-1.905" x2="4.318" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="4.318" y1="-1.905" x2="4.445" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.778" x2="4.445" y2="1.778" width="0.1524" layer="21"/>
<wire x1="4.318" y1="1.905" x2="4.445" y2="1.778" width="0.1524" layer="21"/>
<wire x1="4.318" y1="1.905" x2="-4.318" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.778" x2="-4.318" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.778" x2="-4.445" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="-4.318" y1="-1.905" x2="-4.445" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="-0.3302" y1="1.27" x2="-0.3302" y2="-1.27" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="-1.27" x2="0.3048" y2="-1.27" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="-1.27" x2="0.3048" y2="1.27" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="1.27" x2="-0.3302" y2="1.27" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="1.27" x2="0.9398" y2="0" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="1.27" x2="-0.9398" y2="0" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0.9398" y1="0" x2="0.9398" y2="-1.27" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="0" x2="-1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.9398" y1="0" x2="-0.9398" y2="-1.27" width="0.3048" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="0.8128"/>
<pad name="2" x="2.54" y="0" drill="0.8128"/>
<text x="-5.0546" y="3.2766" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-4.6228" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-5.715" y1="-3.175" x2="5.715" y2="3.175" layer="43"/>
</package>
<package name="HC33U-H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-9.906" y1="-3.048" x2="-9.271" y2="-3.048" width="1.27" layer="21"/>
<wire x1="-9.271" y1="-3.048" x2="9.271" y2="-3.048" width="1.27" layer="21"/>
<wire x1="9.271" y1="-3.048" x2="9.906" y2="-3.048" width="1.27" layer="21"/>
<wire x1="8.636" y1="16.51" x2="-8.636" y2="16.51" width="0.1524" layer="21"/>
<wire x1="-9.271" y1="15.875" x2="-8.636" y2="16.51" width="0.1524" layer="21" curve="-90"/>
<wire x1="8.636" y1="16.51" x2="9.271" y2="15.875" width="0.1524" layer="21" curve="-90"/>
<wire x1="-9.017" y1="7.62" x2="9.017" y2="7.62" width="0.6096" layer="21"/>
<wire x1="-0.3302" y1="13.97" x2="-0.3302" y2="11.43" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="11.43" x2="0.3048" y2="11.43" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="11.43" x2="0.3048" y2="13.97" width="0.3048" layer="21"/>
<wire x1="0.3048" y1="13.97" x2="-0.3302" y2="13.97" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="13.97" x2="0.9398" y2="12.7" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="13.97" x2="-0.9398" y2="12.7" width="0.3048" layer="21"/>
<wire x1="0.9398" y1="12.7" x2="1.905" y2="12.7" width="0.1524" layer="21"/>
<wire x1="0.9398" y1="12.7" x2="0.9398" y2="11.43" width="0.3048" layer="21"/>
<wire x1="-0.9398" y1="12.7" x2="-1.905" y2="12.7" width="0.1524" layer="21"/>
<wire x1="-0.9398" y1="12.7" x2="-0.9398" y2="11.43" width="0.3048" layer="21"/>
<wire x1="9.144" y1="7.62" x2="10.16" y2="7.62" width="0.6096" layer="51"/>
<wire x1="-10.16" y1="7.62" x2="-9.144" y2="7.62" width="0.6096" layer="51"/>
<wire x1="-6.223" y1="-3.175" x2="-6.223" y2="-5.08" width="0.8128" layer="51"/>
<wire x1="6.223" y1="-3.175" x2="6.223" y2="-5.08" width="0.8128" layer="51"/>
<wire x1="9.271" y1="8.128" x2="9.271" y2="15.875" width="0.1524" layer="21"/>
<wire x1="9.271" y1="7.112" x2="9.271" y2="-3.048" width="0.1524" layer="21"/>
<wire x1="9.271" y1="8.128" x2="9.271" y2="7.112" width="0.1524" layer="51"/>
<wire x1="-9.271" y1="7.112" x2="-9.271" y2="-3.048" width="0.1524" layer="21"/>
<wire x1="-9.271" y1="8.128" x2="-9.271" y2="15.875" width="0.1524" layer="21"/>
<wire x1="-9.271" y1="8.128" x2="-9.271" y2="7.112" width="0.1524" layer="51"/>
<pad name="1" x="-6.223" y="-5.08" drill="1.016"/>
<pad name="2" x="6.223" y="-5.08" drill="1.016"/>
<pad name="M" x="-10.16" y="7.62" drill="0.8128"/>
<pad name="M1" x="10.16" y="7.62" drill="0.8128"/>
<text x="-7.62" y="17.272" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-6.35" y="2.54" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-7.62" y1="-3.175" x2="-6.985" y2="16.51" layer="21"/>
<rectangle x1="6.985" y1="-3.175" x2="7.62" y2="16.51" layer="21"/>
<rectangle x1="-10.795" y1="-5.715" x2="10.795" y2="17.145" layer="43"/>
</package>
<package name="HC33U-V">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-0.3302" y1="2.54" x2="-0.3302" y2="0" width="0.3048" layer="21"/>
<wire x1="-0.3302" y1="0" x2="0.3302" y2="0" width="0.3048" layer="21"/>
<wire x1="0.3302" y1="0" x2="0.3302" y2="2.54" width="0.3048" layer="21"/>
<wire x1="0.3302" y1="2.54" x2="-0.3302" y2="2.54" width="0.3048" layer="21"/>
<wire x1="0.9652" y1="2.54" x2="0.9652" y2="1.27" width="0.3048" layer="21"/>
<wire x1="-0.9652" y1="2.54" x2="-0.9652" y2="1.27" width="0.3048" layer="21"/>
<wire x1="0.9652" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.9652" y1="1.27" x2="0.9652" y2="0" width="0.3048" layer="21"/>
<wire x1="-0.9652" y1="1.27" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.9652" y1="1.27" x2="-0.9652" y2="0" width="0.3048" layer="21"/>
<wire x1="-5.207" y1="4.064" x2="5.207" y2="4.064" width="0.254" layer="21"/>
<wire x1="-5.207" y1="-4.064" x2="5.207" y2="-4.064" width="0.254" layer="21"/>
<wire x1="-5.207" y1="-3.683" x2="5.207" y2="-3.683" width="0.0508" layer="21"/>
<wire x1="-5.207" y1="3.683" x2="5.207" y2="3.683" width="0.0508" layer="21"/>
<wire x1="-5.207" y1="-3.683" x2="-5.207" y2="3.683" width="0.0508" layer="21" curve="-180"/>
<wire x1="5.207" y1="3.683" x2="5.207" y2="-3.683" width="0.0508" layer="21" curve="-180"/>
<wire x1="5.207" y1="4.064" x2="5.207" y2="-4.064" width="0.254" layer="21" curve="-180"/>
<wire x1="-5.207" y1="4.064" x2="-5.207" y2="-4.064" width="0.254" layer="21" curve="180"/>
<pad name="1" x="-6.223" y="0" drill="1.016"/>
<pad name="2" x="6.223" y="0" drill="1.016"/>
<text x="-5.08" y="4.826" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-2.54" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-8.255" y1="-3.81" x2="-6.985" y2="3.81" layer="43"/>
<rectangle x1="-8.89" y1="-3.175" x2="-8.255" y2="3.175" layer="43"/>
<rectangle x1="-9.525" y1="-2.54" x2="-8.89" y2="2.54" layer="43"/>
<rectangle x1="-6.985" y1="-4.445" x2="6.985" y2="4.445" layer="43"/>
<rectangle x1="6.985" y1="-3.81" x2="8.255" y2="3.81" layer="43"/>
<rectangle x1="8.255" y1="-3.175" x2="8.89" y2="3.175" layer="43"/>
<rectangle x1="8.89" y1="-2.54" x2="9.525" y2="2.54" layer="43"/>
</package>
<package name="SM49">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="3.429" y1="-2.032" x2="5.109" y2="-1.1429" width="0.0508" layer="21" curve="55.771157"/>
<wire x1="5.715" y1="-1.143" x2="5.715" y2="-2.159" width="0.1524" layer="21"/>
<wire x1="-5.1091" y1="-1.143" x2="-3.429" y2="-2.032" width="0.0508" layer="21" curve="55.772485"/>
<wire x1="-5.715" y1="-1.143" x2="-5.715" y2="-2.159" width="0.1524" layer="21"/>
<wire x1="-3.429" y1="1.27" x2="3.429" y2="1.27" width="0.0508" layer="21"/>
<wire x1="-3.429" y1="2.032" x2="3.429" y2="2.032" width="0.0508" layer="21"/>
<wire x1="3.429" y1="-1.27" x2="-3.429" y2="-1.27" width="0.0508" layer="21"/>
<wire x1="-5.461" y1="2.413" x2="5.461" y2="2.413" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="0.381" x2="-6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="-0.381" x2="-6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-6.477" y1="0.381" x2="-6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="2.159" x2="-5.461" y2="2.413" width="0.1524" layer="21" curve="-90"/>
<wire x1="-5.715" y1="1.143" x2="-5.715" y2="-1.143" width="0.1524" layer="51"/>
<wire x1="-5.715" y1="2.159" x2="-5.715" y2="1.143" width="0.1524" layer="21"/>
<wire x1="-3.9826" y1="1.143" x2="-3.429" y2="1.27" width="0.0508" layer="21" curve="-25.842828"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.429" y2="-1.27" width="0.0508" layer="21" curve="25.842828"/>
<wire x1="-5.1091" y1="1.143" x2="-3.429" y2="2.0321" width="0.0508" layer="21" curve="-55.770993"/>
<wire x1="-3.9826" y1="1.143" x2="-3.9826" y2="-1.143" width="0.0508" layer="51" curve="128.314524"/>
<wire x1="-5.1091" y1="1.143" x2="-5.1091" y2="-1.143" width="0.0508" layer="51" curve="68.456213"/>
<wire x1="3.429" y1="2.032" x2="5.1091" y2="1.143" width="0.0508" layer="21" curve="-55.772485"/>
<wire x1="3.9826" y1="1.143" x2="3.9826" y2="-1.143" width="0.0508" layer="51" curve="-128.314524"/>
<wire x1="3.429" y1="1.27" x2="3.9826" y2="1.143" width="0.0508" layer="21" curve="-25.842828"/>
<wire x1="3.429" y1="-1.27" x2="3.9826" y2="-1.143" width="0.0508" layer="21" curve="25.842828"/>
<wire x1="6.477" y1="0.381" x2="6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="5.1091" y1="1.143" x2="5.1091" y2="-1.143" width="0.0508" layer="51" curve="-68.456213"/>
<wire x1="5.715" y1="1.143" x2="5.715" y2="0.381" width="0.1524" layer="51"/>
<wire x1="5.715" y1="0.381" x2="5.715" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="5.715" y1="-0.381" x2="5.715" y2="-1.143" width="0.1524" layer="51"/>
<wire x1="5.715" y1="2.159" x2="5.715" y2="1.143" width="0.1524" layer="21"/>
<wire x1="5.461" y1="2.413" x2="5.715" y2="2.159" width="0.1524" layer="21" curve="-90"/>
<wire x1="5.715" y1="0.381" x2="6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="5.715" y1="-0.381" x2="6.477" y2="-0.381" width="0.1524" layer="51"/>
<wire x1="3.429" y1="-2.032" x2="-3.429" y2="-2.032" width="0.0508" layer="21"/>
<wire x1="-5.461" y1="-2.413" x2="5.461" y2="-2.413" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="-2.159" x2="-5.461" y2="-2.413" width="0.1524" layer="21" curve="90"/>
<wire x1="5.461" y1="-2.413" x2="5.715" y2="-2.159" width="0.1524" layer="21" curve="90"/>
<wire x1="-0.254" y1="0.635" x2="-0.254" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.254" y1="-0.635" x2="0.254" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="-0.635" x2="0.254" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.635" x2="-0.254" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0.635" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="0" x2="-1.143" y2="0" width="0.0508" layer="21"/>
<wire x1="0.635" y1="0.635" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="1.143" y2="0" width="0.0508" layer="21"/>
<smd name="1" x="-4.826" y="0" dx="5.08" dy="1.778" layer="1"/>
<smd name="2" x="4.826" y="0" dx="5.08" dy="1.778" layer="1"/>
<text x="-5.715" y="2.667" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.715" y="-4.064" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-6.604" y1="-2.54" x2="6.604" y2="2.794" layer="43"/>
</package>
<package name="TC26H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-0.889" y1="1.651" x2="0.889" y2="1.651" width="0.1524" layer="21"/>
<wire x1="0.762" y1="7.747" x2="1.016" y2="7.493" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.016" y1="7.493" x2="-0.762" y2="7.747" width="0.1524" layer="21" curve="-90"/>
<wire x1="-0.762" y1="7.747" x2="0.762" y2="7.747" width="0.1524" layer="21"/>
<wire x1="0.889" y1="1.651" x2="0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.032" x2="1.016" y2="7.493" width="0.1524" layer="21"/>
<wire x1="-0.889" y1="1.651" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="2.032" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.016" y1="2.032" x2="-1.016" y2="7.493" width="0.1524" layer="21"/>
<wire x1="0.508" y1="0.762" x2="0.508" y2="1.143" width="0.4064" layer="21"/>
<wire x1="-0.508" y1="0.762" x2="-0.508" y2="1.27" width="0.4064" layer="21"/>
<wire x1="0.635" y1="0.635" x2="1.27" y2="0" width="0.4064" layer="51"/>
<wire x1="-0.635" y1="0.635" x2="-1.27" y2="0" width="0.4064" layer="51"/>
<wire x1="-0.508" y1="4.953" x2="-0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="0.508" y1="4.572" x2="-0.508" y2="4.572" width="0.1524" layer="21"/>
<wire x1="0.508" y1="4.572" x2="0.508" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="4.953" x2="0.508" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="5.334" x2="0" y2="5.334" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="4.191" x2="0" y2="4.191" width="0.1524" layer="21"/>
<wire x1="0" y1="4.191" x2="0" y2="3.683" width="0.1524" layer="21"/>
<wire x1="0" y1="4.191" x2="0.508" y2="4.191" width="0.1524" layer="21"/>
<wire x1="0" y1="5.334" x2="0" y2="5.842" width="0.1524" layer="21"/>
<wire x1="0" y1="5.334" x2="0.508" y2="5.334" width="0.1524" layer="21"/>
<wire x1="1.016" y1="2.032" x2="0.889" y2="2.032" width="0.1524" layer="21"/>
<wire x1="0.889" y1="2.032" x2="-0.889" y2="2.032" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="0.8128"/>
<pad name="2" x="1.27" y="0" drill="0.8128"/>
<text x="-1.397" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="2.667" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="0.762" x2="1.778" y2="8.382" layer="43"/>
</package>
<package name="TC26V">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-0.127" y1="-0.508" x2="0.127" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="0.127" y1="0.508" x2="0.127" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="0.127" y1="0.508" x2="-0.127" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-0.127" y1="-0.508" x2="-0.127" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-0.381" y1="-0.508" x2="-0.381" y2="0" width="0.1524" layer="51"/>
<wire x1="0.381" y1="-0.508" x2="0.381" y2="0" width="0.1524" layer="51"/>
<wire x1="0.381" y1="0" x2="0.762" y2="0" width="0.1524" layer="51"/>
<wire x1="0.381" y1="0" x2="0.381" y2="0.508" width="0.1524" layer="51"/>
<wire x1="-0.381" y1="0" x2="-0.762" y2="0" width="0.1524" layer="51"/>
<wire x1="-0.381" y1="0" x2="-0.381" y2="0.508" width="0.1524" layer="51"/>
<wire x1="0" y1="1.016" x2="0.7184" y2="0.7184" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="-0.7184" y1="0.7184" x2="0" y2="1.016" width="0.1524" layer="21" curve="-44.999323"/>
<wire x1="-0.7184" y1="-0.7184" x2="0" y2="-1.016" width="0.1524" layer="21" curve="44.999323"/>
<wire x1="0" y1="-1.016" x2="0.7184" y2="-0.7184" width="0.1524" layer="21" curve="44.999323"/>
<circle x="0" y="0" radius="1.016" width="0.1524" layer="51"/>
<pad name="1" x="-1.27" y="0" drill="0.8128"/>
<pad name="2" x="1.27" y="0" drill="0.8128"/>
<text x="-2.032" y="1.397" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.032" y="-2.667" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="TC38H">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-1.397" y1="1.651" x2="1.397" y2="1.651" width="0.1524" layer="21"/>
<wire x1="1.27" y1="9.906" x2="1.524" y2="9.652" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="9.652" x2="-1.27" y2="9.906" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.27" y1="9.906" x2="1.27" y2="9.906" width="0.1524" layer="21"/>
<wire x1="1.397" y1="1.651" x2="1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.524" y1="2.032" x2="1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="1.524" y1="2.032" x2="1.524" y2="9.652" width="0.1524" layer="21"/>
<wire x1="-1.397" y1="1.651" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="2.032" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="2.032" x2="-1.524" y2="9.652" width="0.1524" layer="21"/>
<wire x1="1.397" y1="2.032" x2="-1.397" y2="2.032" width="0.1524" layer="21"/>
<wire x1="0.5588" y1="0.7112" x2="0.508" y2="0.762" width="0.4064" layer="21"/>
<wire x1="0.508" y1="0.762" x2="0.508" y2="1.143" width="0.4064" layer="21"/>
<wire x1="-0.508" y1="0.762" x2="-0.508" y2="1.016" width="0.4064" layer="21"/>
<wire x1="-0.5588" y1="0.7112" x2="-0.508" y2="0.762" width="0.4064" layer="21"/>
<wire x1="0.635" y1="0.635" x2="1.27" y2="0" width="0.1524" layer="51"/>
<wire x1="-0.635" y1="0.635" x2="-1.27" y2="0" width="0.1524" layer="51"/>
<wire x1="-0.762" y1="5.588" x2="-0.762" y2="5.207" width="0.1524" layer="21"/>
<wire x1="0.762" y1="5.207" x2="-0.762" y2="5.207" width="0.1524" layer="21"/>
<wire x1="0.762" y1="5.207" x2="0.762" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="5.588" x2="0.762" y2="5.588" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="5.969" x2="0" y2="5.969" width="0.1524" layer="21"/>
<wire x1="-0.762" y1="4.826" x2="0" y2="4.826" width="0.1524" layer="21"/>
<wire x1="0" y1="4.826" x2="0" y2="4.318" width="0.1524" layer="21"/>
<wire x1="0" y1="4.826" x2="0.762" y2="4.826" width="0.1524" layer="21"/>
<wire x1="0" y1="5.969" x2="0" y2="6.477" width="0.1524" layer="21"/>
<wire x1="0" y1="5.969" x2="0.762" y2="5.969" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="0.8128"/>
<pad name="2" x="1.27" y="0" drill="0.8128"/>
<text x="-1.905" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.175" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="1.016" x2="1.778" y2="10.414" layer="43"/>
</package>
<package name="MM20SS">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-2.032" y1="-1.27" x2="2.032" y2="-1.27" width="0.0508" layer="21"/>
<wire x1="-2.032" y1="-1.778" x2="2.032" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="2.032" y1="1.27" x2="-2.032" y2="1.27" width="0.0508" layer="21"/>
<wire x1="-2.032" y1="1.778" x2="2.032" y2="1.778" width="0.1524" layer="21"/>
<wire x1="-4.064" y1="-1.778" x2="-4.064" y2="1.778" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="0.381" x2="-2.921" y2="-0.381" width="0.0508" layer="21"/>
<wire x1="-4.064" y1="-1.778" x2="-3.556" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="-3.556" y1="-1.552" x2="-4.064" y2="-1.778" width="0.0508" layer="21"/>
<wire x1="-2.032" y1="1.27" x2="-2.921" y2="1.27" width="0.0508" layer="51"/>
<wire x1="-2.921" y1="1.27" x2="-2.921" y2="0.381" width="0.0508" layer="51"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="-1.778" width="0.1524" layer="51"/>
<wire x1="-3.048" y1="-1.905" x2="-3.048" y2="-1.778" width="0.1524" layer="51"/>
<wire x1="-3.048" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="51"/>
<wire x1="-2.921" y1="-0.381" x2="-2.921" y2="-1.27" width="0.0508" layer="51"/>
<wire x1="-2.921" y1="-1.27" x2="-2.032" y2="-1.27" width="0.0508" layer="51"/>
<wire x1="-3.556" y1="-1.778" x2="-2.032" y2="-1.778" width="0.1524" layer="51"/>
<wire x1="-2.921" y1="-1.27" x2="-3.556" y2="-1.552" width="0.0508" layer="51"/>
<wire x1="-4.064" y1="1.778" x2="-3.556" y2="1.778" width="0.1524" layer="21"/>
<wire x1="-3.556" y1="1.552" x2="-4.064" y2="1.778" width="0.0508" layer="21"/>
<wire x1="-2.921" y1="1.27" x2="-3.556" y2="1.552" width="0.0508" layer="51"/>
<wire x1="-3.048" y1="1.778" x2="-3.048" y2="1.905" width="0.1524" layer="51"/>
<wire x1="-2.54" y1="1.905" x2="-2.54" y2="1.778" width="0.1524" layer="51"/>
<wire x1="-3.048" y1="1.905" x2="-2.54" y2="1.905" width="0.1524" layer="51"/>
<wire x1="-3.556" y1="1.778" x2="-2.032" y2="1.778" width="0.1524" layer="51"/>
<wire x1="4.064" y1="-1.778" x2="4.064" y2="1.778" width="0.1524" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.0508" layer="21"/>
<wire x1="3.81" y1="-1.27" x2="4.064" y2="-1.778" width="0.0508" layer="21"/>
<wire x1="3.556" y1="-1.27" x2="3.81" y2="-1.27" width="0.0508" layer="21"/>
<wire x1="3.556" y1="-1.778" x2="4.064" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.556" y2="1.27" width="0.0508" layer="21"/>
<wire x1="3.556" y1="1.27" x2="2.032" y2="1.27" width="0.0508" layer="51"/>
<wire x1="3.048" y1="-1.905" x2="3.048" y2="-1.778" width="0.1524" layer="51"/>
<wire x1="2.54" y1="-1.778" x2="2.54" y2="-1.905" width="0.1524" layer="51"/>
<wire x1="2.54" y1="-1.905" x2="3.048" y2="-1.905" width="0.1524" layer="51"/>
<wire x1="2.032" y1="-1.27" x2="3.556" y2="-1.27" width="0.0508" layer="51"/>
<wire x1="2.032" y1="-1.778" x2="3.556" y2="-1.778" width="0.1524" layer="51"/>
<wire x1="3.81" y1="1.27" x2="4.064" y2="1.778" width="0.0508" layer="21"/>
<wire x1="3.556" y1="1.778" x2="4.064" y2="1.778" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="2.54" y2="1.778" width="0.1524" layer="51"/>
<wire x1="3.048" y1="1.778" x2="3.048" y2="1.905" width="0.1524" layer="51"/>
<wire x1="2.54" y1="1.905" x2="3.048" y2="1.905" width="0.1524" layer="51"/>
<wire x1="2.032" y1="1.778" x2="3.556" y2="1.778" width="0.1524" layer="51"/>
<wire x1="-1.778" y1="-0.254" x2="-0.508" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="-0.254" x2="-0.508" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-0.508" y1="0.254" x2="-1.778" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="0.254" x2="-1.778" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="0.635" x2="-1.143" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="0.635" x2="-0.508" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="0.635" x2="-1.143" y2="1.016" width="0.0508" layer="21"/>
<wire x1="-1.778" y1="-0.635" x2="-1.143" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-0.635" x2="-0.508" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="-0.635" x2="-1.143" y2="-1.016" width="0.0508" layer="21"/>
<circle x="3.048" y="0" radius="0.254" width="0.1524" layer="21"/>
<smd name="1" x="-2.794" y="-1.524" dx="1.27" dy="1.8796" layer="1"/>
<smd name="2" x="2.794" y="-1.524" dx="1.27" dy="1.8796" layer="1"/>
<smd name="3" x="2.794" y="1.524" dx="1.27" dy="1.8796" layer="1"/>
<smd name="4" x="-2.794" y="1.524" dx="1.27" dy="1.8796" layer="1"/>
<text x="-2.54" y="2.54" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-3.81" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="MM39SL">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-3.683" y1="-1.651" x2="3.683" y2="-1.651" width="0.0508" layer="21"/>
<wire x1="-3.683" y1="-2.286" x2="3.683" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="-3.683" y1="2.286" x2="3.683" y2="2.286" width="0.1524" layer="21"/>
<wire x1="3.683" y1="1.651" x2="-3.683" y2="1.651" width="0.0508" layer="21"/>
<wire x1="-6.223" y1="-2.286" x2="-6.223" y2="2.286" width="0.1524" layer="21"/>
<wire x1="-4.826" y1="1.651" x2="-4.826" y2="0.762" width="0.0508" layer="51"/>
<wire x1="-5.715" y1="-2.286" x2="-3.683" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="-4.826" y1="-1.651" x2="-3.683" y2="-1.651" width="0.0508" layer="51"/>
<wire x1="-5.715" y1="-2.055" x2="-6.223" y2="-2.286" width="0.0508" layer="21"/>
<wire x1="-6.223" y1="-2.286" x2="-5.715" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="-4.826" y1="0.762" x2="-4.826" y2="-0.762" width="0.0508" layer="21"/>
<wire x1="-4.826" y1="-0.762" x2="-4.826" y2="-1.651" width="0.0508" layer="51"/>
<wire x1="-4.826" y1="-1.651" x2="-5.715" y2="-2.055" width="0.0508" layer="51"/>
<wire x1="-5.715" y1="2.286" x2="-3.683" y2="2.286" width="0.1524" layer="51"/>
<wire x1="-3.683" y1="1.651" x2="-4.826" y2="1.651" width="0.0508" layer="51"/>
<wire x1="-6.223" y1="2.286" x2="-5.715" y2="2.286" width="0.1524" layer="21"/>
<wire x1="-5.715" y1="2.055" x2="-6.223" y2="2.286" width="0.0508" layer="21"/>
<wire x1="-4.826" y1="1.651" x2="-5.715" y2="2.055" width="0.0508" layer="51"/>
<wire x1="6.223" y1="-2.286" x2="6.223" y2="2.286" width="0.1524" layer="21"/>
<wire x1="5.842" y1="-1.651" x2="5.842" y2="1.651" width="0.0508" layer="21"/>
<wire x1="5.842" y1="-1.651" x2="6.223" y2="-2.286" width="0.0508" layer="21"/>
<wire x1="5.715" y1="-2.286" x2="6.223" y2="-2.286" width="0.1524" layer="21"/>
<wire x1="3.683" y1="-2.286" x2="5.715" y2="-2.286" width="0.1524" layer="51"/>
<wire x1="5.715" y1="-1.651" x2="5.842" y2="-1.651" width="0.0508" layer="21"/>
<wire x1="3.683" y1="-1.651" x2="5.715" y2="-1.651" width="0.0508" layer="51"/>
<wire x1="5.842" y1="1.651" x2="6.223" y2="2.286" width="0.0508" layer="21"/>
<wire x1="5.842" y1="1.651" x2="5.715" y2="1.651" width="0.0508" layer="21"/>
<wire x1="5.715" y1="2.286" x2="6.223" y2="2.286" width="0.1524" layer="21"/>
<wire x1="3.683" y1="2.286" x2="5.715" y2="2.286" width="0.1524" layer="51"/>
<wire x1="5.715" y1="1.651" x2="3.683" y2="1.651" width="0.0508" layer="51"/>
<wire x1="-3.81" y1="-0.254" x2="-2.54" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.254" x2="-2.54" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.254" x2="-3.81" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.254" x2="-3.81" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="0.635" x2="-3.175" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="0.635" x2="-3.175" y2="1.016" width="0.1016" layer="21"/>
<wire x1="-3.81" y1="-0.635" x2="-3.175" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-0.635" x2="-3.175" y2="-1.016" width="0.1016" layer="21"/>
<circle x="5.08" y="0" radius="0.254" width="0.1524" layer="21"/>
<smd name="1" x="-4.699" y="-1.778" dx="1.778" dy="1.778" layer="1"/>
<smd name="2" x="4.699" y="-1.778" dx="1.778" dy="1.778" layer="1"/>
<smd name="3" x="4.699" y="1.778" dx="1.778" dy="1.778" layer="1"/>
<smd name="4" x="-4.699" y="1.778" dx="1.778" dy="1.778" layer="1"/>
<text x="-2.54" y="2.54" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.032" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="CTS406">
<description>&lt;b&gt;Model 406 6.0x3.5mm Low Cost Surface Mount Crystal&lt;/b&gt;&lt;p&gt;
Source: 008-0260-0_E.pdf</description>
<wire x1="-2.475" y1="1.65" x2="-1.05" y2="1.65" width="0.2032" layer="51"/>
<wire x1="-1.05" y1="1.65" x2="1.05" y2="1.65" width="0.2032" layer="21"/>
<wire x1="1.05" y1="1.65" x2="2.475" y2="1.65" width="0.2032" layer="51"/>
<wire x1="2.9" y1="1.225" x2="2.9" y2="0.3" width="0.2032" layer="51"/>
<wire x1="2.9" y1="0.3" x2="2.9" y2="-0.3" width="0.2032" layer="21"/>
<wire x1="2.9" y1="-0.3" x2="2.9" y2="-1.225" width="0.2032" layer="51"/>
<wire x1="2.475" y1="-1.65" x2="1.05" y2="-1.65" width="0.2032" layer="51"/>
<wire x1="1.05" y1="-1.65" x2="-1.05" y2="-1.65" width="0.2032" layer="21"/>
<wire x1="-1.05" y1="-1.65" x2="-2.475" y2="-1.65" width="0.2032" layer="51"/>
<wire x1="-2.9" y1="-1.225" x2="-2.9" y2="-0.3" width="0.2032" layer="51"/>
<wire x1="-2.9" y1="-0.3" x2="-2.9" y2="0.3" width="0.2032" layer="21"/>
<wire x1="-2.9" y1="0.3" x2="-2.9" y2="1.225" width="0.2032" layer="51"/>
<wire x1="-2.9" y1="1.225" x2="-2.475" y2="1.65" width="0.2032" layer="51" curve="89.516721"/>
<wire x1="2.475" y1="1.65" x2="2.9" y2="1.225" width="0.2032" layer="51" curve="89.516721"/>
<wire x1="2.9" y1="-1.225" x2="2.475" y2="-1.65" width="0.2032" layer="51" curve="89.516721"/>
<wire x1="-2.475" y1="-1.65" x2="-2.9" y2="-1.225" width="0.2032" layer="51" curve="89.516721"/>
<circle x="-2.05" y="-0.2" radius="0.182" width="0" layer="21"/>
<smd name="1" x="-2.2" y="-1.2" dx="1.9" dy="1.4" layer="1"/>
<smd name="2" x="2.2" y="-1.2" dx="1.9" dy="1.4" layer="1"/>
<smd name="3" x="2.2" y="1.2" dx="1.9" dy="1.4" layer="1"/>
<smd name="4" x="-2.2" y="1.2" dx="1.9" dy="1.4" layer="1"/>
<text x="-2.54" y="2.54" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-3.81" size="1.27" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="Q">
<wire x1="1.016" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.016" y2="0" width="0.1524" layer="94"/>
<wire x1="-0.381" y1="1.524" x2="-0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-0.381" y1="-1.524" x2="0.381" y2="-1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="-1.524" x2="0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="0.381" y1="1.524" x2="-0.381" y2="1.524" width="0.254" layer="94"/>
<wire x1="1.016" y1="1.778" x2="1.016" y2="-1.778" width="0.254" layer="94"/>
<wire x1="-1.016" y1="1.778" x2="-1.016" y2="-1.778" width="0.254" layer="94"/>
<text x="2.54" y="1.016" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.159" y="-1.143" size="0.8636" layer="93">1</text>
<text x="1.524" y="-1.143" size="0.8636" layer="93">2</text>
<pin name="2" x="2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-2.54" y="0" visible="off" length="point" direction="pas" swaplevel="1"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CRYSTAL" prefix="Q" uservalue="yes">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="Q" x="0" y="0"/>
</gates>
<devices>
<device name="HC49S" package="HC49/S">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="1667008" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC49GW" package="HC49GW">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC49TL-H" package="HC49TL-H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC49U-H" package="HC49U-H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="1666973" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC49U-LM" package="HC49U-LM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="1666956" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC49U-V" package="HC49U-V">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="1666969" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC49U70" package="HC49U70">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC49UP" package="HC49UP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC13U-H" package="HC13U-H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC18U-H" package="HC18U-H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC18U-V" package="HC18U-V">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC33U-H" package="HC33U-H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="HC33U-V" package="HC33U-V">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="SM49" package="SM49">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="TC26H" package="TC26H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="TC26V" package="TC26V">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="TC38H" package="TC38H">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="68SMX" package="86SMX">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="6344860" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="MM20SS" package="MM20SS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="MM39SL" package="MM39SL">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="4"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="CTS406" package="CTS406">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="3"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
<class number="1" name="+5V_A" width="0.4" drill="0.5">
</class>
<class number="2" name="+3.3V_A" width="0.4" drill="0.5">
</class>
<class number="3" name="GND_A" width="0.4" drill="0.5">
</class>
</classes>
<parts>
<part name="C6" library="SparkFun" deviceset="CAP_POL" device="1206-KIT" value="10uF/6.3v"/>
<part name="P+1" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND1" library="SparkFun" deviceset="GND" device=""/>
<part name="ZQ1" library="crystal" deviceset="CRYSTAL" device="68SMX" value="8M"/>
<part name="C11" library="SparkFun" deviceset="CAP" device="0805" value="20pF"/>
<part name="C12" library="SparkFun" deviceset="CAP" device="0805" value="20pF"/>
<part name="GND8" library="SparkFun" deviceset="GND" device=""/>
<part name="P+6" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND9" library="SparkFun" deviceset="GND" device=""/>
<part name="R7" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="C13" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="X1" library="SparkFun" deviceset="USB" device="-SMD-NS"/>
<part name="GND14" library="SparkFun" deviceset="GND" device=""/>
<part name="R12" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="33"/>
<part name="R13" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="33"/>
<part name="XP1" library="barthess" deviceset="2X10" device="-PSEUDO_SMD"/>
<part name="P+11" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND22" library="SparkFun" deviceset="GND" device=""/>
<part name="JP2" library="barthess" deviceset="2X5" device=""/>
<part name="GND26" library="SparkFun" deviceset="GND" device=""/>
<part name="P+14" library="SparkFun" deviceset="3.3V" device=""/>
<part name="R30" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="68"/>
<part name="R60" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="0"/>
<part name="S2" library="barthess" deviceset="BUTTON_6X3.5" device="" value="RESET"/>
<part name="JP3" library="barthess" deviceset="STAND-OFF" device=""/>
<part name="JP7" library="barthess" deviceset="STAND-OFF" device=""/>
<part name="JP8" library="barthess" deviceset="STAND-OFF" device=""/>
<part name="JP9" library="barthess" deviceset="STAND-OFF" device=""/>
<part name="C23" library="SparkFun" deviceset="CAP" device="0805" value="2.2uF"/>
<part name="GND12" library="SparkFun" deviceset="GND" device=""/>
<part name="U$3" library="barthess" deviceset="PLS_2X32" device=""/>
<part name="U$4" library="barthess" deviceset="STM32F407I" device=""/>
<part name="R1" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="C7" library="SparkFun" deviceset="CAP" device="0805" value="2.2uF"/>
<part name="C8" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C9" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C10" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C14" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C15" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C16" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C17" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C18" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C19" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C20" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C21" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C22" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C24" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C25" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C26" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="P+2" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND3" library="SparkFun" deviceset="GND" device=""/>
<part name="GND4" library="SparkFun" deviceset="GND" device=""/>
<part name="GND5" library="SparkFun" deviceset="GND" device=""/>
<part name="GND6" library="SparkFun" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="C6" gate="G$1" x="-66.04" y="38.1"/>
<instance part="P+1" gate="G$1" x="-66.04" y="43.18"/>
<instance part="GND1" gate="1" x="-66.04" y="27.94"/>
<instance part="ZQ1" gate="G$1" x="-71.12" y="15.24" rot="R270"/>
<instance part="C11" gate="G$1" x="-76.2" y="17.78" rot="R90"/>
<instance part="C12" gate="G$1" x="-83.82" y="12.7" rot="R90"/>
<instance part="GND8" gate="1" x="-93.98" y="12.7" rot="R270"/>
<instance part="P+6" gate="G$1" x="-22.86" y="187.96"/>
<instance part="GND9" gate="1" x="-22.86" y="162.56"/>
<instance part="R7" gate="G$1" x="-22.86" y="180.34" rot="R90"/>
<instance part="C13" gate="G$1" x="-22.86" y="170.18"/>
<instance part="X1" gate="G$1" x="-157.48" y="101.6" rot="MR0"/>
<instance part="GND14" gate="1" x="-154.94" y="96.52"/>
<instance part="R12" gate="G$1" x="-134.62" y="106.68"/>
<instance part="R13" gate="G$1" x="-144.78" y="109.22"/>
<instance part="XP1" gate="G$1" x="-139.7" y="162.56" rot="MR0"/>
<instance part="P+11" gate="G$1" x="-149.86" y="182.88"/>
<instance part="GND22" gate="1" x="-149.86" y="139.7"/>
<instance part="JP2" gate="G$1" x="71.12" y="218.44"/>
<instance part="GND26" gate="1" x="83.82" y="205.74"/>
<instance part="P+14" gate="G$1" x="55.88" y="223.52" rot="R90"/>
<instance part="R30" gate="G$1" x="63.5" y="152.4" rot="MR180"/>
<instance part="R60" gate="G$1" x="71.12" y="149.86" rot="MR180"/>
<instance part="S2" gate="1" x="-30.48" y="170.18"/>
<instance part="JP3" gate="G$1" x="-127" y="-124.46" rot="R90"/>
<instance part="JP7" gate="G$1" x="-127" y="-119.38" rot="R90"/>
<instance part="JP8" gate="G$1" x="-119.38" y="-124.46" rot="R90"/>
<instance part="JP9" gate="G$1" x="-119.38" y="-119.38" rot="R90"/>
<instance part="C23" gate="G$1" x="-55.88" y="114.3" rot="R90"/>
<instance part="GND12" gate="1" x="-68.58" y="114.3" rot="R270"/>
<instance part="U$3" gate="G$1" x="53.34" y="73.66" rot="MR0"/>
<instance part="U$4" gate="G$1" x="-2.54" y="0"/>
<instance part="R1" gate="G$1" x="-144.78" y="104.14" rot="R180"/>
<instance part="C7" gate="G$1" x="-48.26" y="111.76" rot="R90"/>
<instance part="C8" gate="G$1" x="-71.12" y="88.9" rot="R90"/>
<instance part="C9" gate="G$1" x="-63.5" y="86.36" rot="R90"/>
<instance part="C10" gate="G$1" x="-71.12" y="83.82" rot="R90"/>
<instance part="C14" gate="G$1" x="-63.5" y="81.28" rot="R90"/>
<instance part="C15" gate="G$1" x="-71.12" y="78.74" rot="R90"/>
<instance part="C16" gate="G$1" x="-63.5" y="76.2" rot="R90"/>
<instance part="C17" gate="G$1" x="-71.12" y="73.66" rot="R90"/>
<instance part="C18" gate="G$1" x="-63.5" y="71.12" rot="R90"/>
<instance part="C19" gate="G$1" x="-71.12" y="68.58" rot="R90"/>
<instance part="C20" gate="G$1" x="-63.5" y="66.04" rot="R90"/>
<instance part="C21" gate="G$1" x="-71.12" y="63.5" rot="R90"/>
<instance part="C22" gate="G$1" x="-63.5" y="60.96" rot="R90"/>
<instance part="C24" gate="G$1" x="-71.12" y="58.42" rot="R90"/>
<instance part="C25" gate="G$1" x="-63.5" y="55.88" rot="R90"/>
<instance part="C26" gate="G$1" x="-71.12" y="53.34" rot="R90"/>
<instance part="P+2" gate="G$1" x="-83.82" y="104.14" rot="R90"/>
<instance part="GND3" gate="1" x="-53.34" y="93.98" rot="R270"/>
<instance part="GND4" gate="1" x="-86.36" y="88.9" rot="R270"/>
<instance part="GND5" gate="1" x="-55.88" y="20.32" rot="R270"/>
<instance part="GND6" gate="1" x="-55.88" y="7.62" rot="R270"/>
</instances>
<busses>
</busses>
<nets>
<net name="3.3V" class="0">
<segment>
<pinref part="C6" gate="G$1" pin="+"/>
<wire x1="-66.04" y1="43.18" x2="-66.04" y2="40.64" width="0.1524" layer="91"/>
<pinref part="P+1" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="-22.86" y1="185.42" x2="-22.86" y2="187.96" width="0.1524" layer="91"/>
<pinref part="R7" gate="G$1" pin="2"/>
<pinref part="P+6" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="-149.86" y1="182.88" x2="-149.86" y2="180.34" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="180.34" x2="-129.54" y2="180.34" width="0.1524" layer="91"/>
<wire x1="-132.08" y1="172.72" x2="-129.54" y2="172.72" width="0.1524" layer="91"/>
<wire x1="-129.54" y1="172.72" x2="-129.54" y2="180.34" width="0.1524" layer="91"/>
<wire x1="-147.32" y1="172.72" x2="-149.86" y2="172.72" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="172.72" x2="-149.86" y2="180.34" width="0.1524" layer="91"/>
<junction x="-149.86" y="180.34"/>
<pinref part="P+11" gate="G$1" pin="3.3V"/>
<pinref part="XP1" gate="G$1" pin="1"/>
<pinref part="XP1" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="63.5" y1="223.52" x2="55.88" y2="223.52" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="1"/>
<pinref part="P+14" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<pinref part="C26" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="53.34" x2="-58.42" y2="53.34" width="0.1524" layer="91"/>
<pinref part="C25" gate="G$1" pin="2"/>
<wire x1="-58.42" y1="53.34" x2="-68.58" y2="53.34" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="55.88" x2="-58.42" y2="55.88" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="55.88" x2="-60.96" y2="55.88" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="53.34" x2="-58.42" y2="55.88" width="0.1524" layer="91"/>
<junction x="-58.42" y="53.34"/>
<junction x="-58.42" y="55.88"/>
<pinref part="C24" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="58.42" x2="-58.42" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="58.42" x2="-68.58" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="55.88" x2="-58.42" y2="58.42" width="0.1524" layer="91"/>
<junction x="-58.42" y="58.42"/>
<pinref part="C22" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="60.96" x2="-58.42" y2="60.96" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="60.96" x2="-60.96" y2="60.96" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="58.42" x2="-58.42" y2="60.96" width="0.1524" layer="91"/>
<junction x="-58.42" y="60.96"/>
<pinref part="C21" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="63.5" x2="-58.42" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="63.5" x2="-68.58" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="60.96" x2="-58.42" y2="63.5" width="0.1524" layer="91"/>
<junction x="-58.42" y="63.5"/>
<pinref part="C20" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="66.04" x2="-58.42" y2="66.04" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="66.04" x2="-60.96" y2="66.04" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="63.5" x2="-58.42" y2="66.04" width="0.1524" layer="91"/>
<junction x="-58.42" y="66.04"/>
<pinref part="C19" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="68.58" x2="-58.42" y2="68.58" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="68.58" x2="-68.58" y2="68.58" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="66.04" x2="-58.42" y2="68.58" width="0.1524" layer="91"/>
<junction x="-58.42" y="68.58"/>
<pinref part="C18" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="71.12" x2="-58.42" y2="71.12" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="71.12" x2="-60.96" y2="71.12" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="68.58" x2="-58.42" y2="71.12" width="0.1524" layer="91"/>
<junction x="-58.42" y="71.12"/>
<pinref part="C17" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="73.66" x2="-58.42" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="73.66" x2="-68.58" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="71.12" x2="-58.42" y2="73.66" width="0.1524" layer="91"/>
<junction x="-58.42" y="73.66"/>
<pinref part="C16" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="76.2" x2="-58.42" y2="76.2" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="76.2" x2="-60.96" y2="76.2" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="73.66" x2="-58.42" y2="76.2" width="0.1524" layer="91"/>
<junction x="-58.42" y="76.2"/>
<pinref part="C15" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="78.74" x2="-58.42" y2="78.74" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="78.74" x2="-68.58" y2="78.74" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="76.2" x2="-58.42" y2="78.74" width="0.1524" layer="91"/>
<junction x="-58.42" y="78.74"/>
<pinref part="C14" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="81.28" x2="-58.42" y2="81.28" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="81.28" x2="-60.96" y2="81.28" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="78.74" x2="-58.42" y2="81.28" width="0.1524" layer="91"/>
<junction x="-58.42" y="81.28"/>
<pinref part="C10" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="83.82" x2="-58.42" y2="83.82" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="83.82" x2="-68.58" y2="83.82" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="81.28" x2="-58.42" y2="83.82" width="0.1524" layer="91"/>
<junction x="-58.42" y="83.82"/>
<pinref part="U$4" gate="G$1" pin="VDD@1"/>
<pinref part="C9" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="86.36" x2="-58.42" y2="86.36" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="86.36" x2="-60.96" y2="86.36" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="83.82" x2="-58.42" y2="86.36" width="0.1524" layer="91"/>
<junction x="-58.42" y="86.36"/>
<pinref part="U$4" gate="G$1" pin="VDD@0"/>
<pinref part="C8" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="88.9" x2="-58.42" y2="88.9" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="88.9" x2="-68.58" y2="88.9" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="86.36" x2="-58.42" y2="88.9" width="0.1524" layer="91"/>
<junction x="-58.42" y="88.9"/>
<wire x1="-58.42" y1="88.9" x2="-58.42" y2="99.06" width="0.1524" layer="91"/>
<pinref part="P+2" gate="G$1" pin="3.3V"/>
<wire x1="-58.42" y1="99.06" x2="-58.42" y2="104.14" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="104.14" x2="-83.82" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="V_BAT"/>
<wire x1="-43.18" y1="104.14" x2="-58.42" y2="104.14" width="0.1524" layer="91"/>
<junction x="-58.42" y="104.14"/>
<pinref part="U$4" gate="G$1" pin="VDD_A"/>
<wire x1="-43.18" y1="96.52" x2="-48.26" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="VREF+"/>
<wire x1="-43.18" y1="99.06" x2="-48.26" y2="99.06" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="99.06" x2="-48.26" y2="96.52" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="99.06" x2="-58.42" y2="99.06" width="0.1524" layer="91"/>
<junction x="-48.26" y="99.06"/>
<junction x="-58.42" y="99.06"/>
<pinref part="U$4" gate="G$1" pin="VDD@6"/>
<pinref part="U$4" gate="G$1" pin="VDD@5"/>
<pinref part="U$4" gate="G$1" pin="VDD@2"/>
<pinref part="U$4" gate="G$1" pin="VDD@3"/>
<pinref part="U$4" gate="G$1" pin="VDD@4"/>
<pinref part="U$4" gate="G$1" pin="VDD@7"/>
<pinref part="U$4" gate="G$1" pin="VDD@8"/>
<pinref part="U$4" gate="G$1" pin="VDD@9"/>
<pinref part="U$4" gate="G$1" pin="VDD@10"/>
<pinref part="U$4" gate="G$1" pin="VDD@11"/>
<pinref part="U$4" gate="G$1" pin="VDD@12"/>
<pinref part="U$4" gate="G$1" pin="VDD@13"/>
<pinref part="U$4" gate="G$1" pin="VDD@14"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<wire x1="-88.9" y1="12.7" x2="-91.44" y2="12.7" width="0.1524" layer="91"/>
<wire x1="-91.44" y1="12.7" x2="-91.44" y2="17.78" width="0.1524" layer="91"/>
<wire x1="-91.44" y1="17.78" x2="-81.28" y2="17.78" width="0.1524" layer="91"/>
<junction x="-91.44" y="12.7"/>
<pinref part="C12" gate="G$1" pin="1"/>
<pinref part="C11" gate="G$1" pin="1"/>
<pinref part="GND8" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="-30.48" y1="165.1" x2="-22.86" y2="165.1" width="0.1524" layer="91"/>
<wire x1="-22.86" y1="165.1" x2="-22.86" y2="167.64" width="0.1524" layer="91"/>
<junction x="-22.86" y="165.1"/>
<pinref part="C13" gate="G$1" pin="2"/>
<pinref part="GND9" gate="1" pin="GND"/>
<pinref part="S2" gate="1" pin="P"/>
</segment>
<segment>
<wire x1="-154.94" y1="99.06" x2="-154.94" y2="101.6" width="0.1524" layer="91"/>
<pinref part="GND14" gate="1" pin="GND"/>
<pinref part="X1" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="-149.86" y1="142.24" x2="-149.86" y2="149.86" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="149.86" x2="-147.32" y2="149.86" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="149.86" x2="-149.86" y2="152.4" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="152.4" x2="-147.32" y2="152.4" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="152.4" x2="-149.86" y2="154.94" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="154.94" x2="-147.32" y2="154.94" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="154.94" x2="-149.86" y2="157.48" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="157.48" x2="-147.32" y2="157.48" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="157.48" x2="-149.86" y2="160.02" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="160.02" x2="-147.32" y2="160.02" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="160.02" x2="-149.86" y2="162.56" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="162.56" x2="-147.32" y2="162.56" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="162.56" x2="-149.86" y2="165.1" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="165.1" x2="-147.32" y2="165.1" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="165.1" x2="-149.86" y2="167.64" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="167.64" x2="-147.32" y2="167.64" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="167.64" x2="-149.86" y2="170.18" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="170.18" x2="-147.32" y2="170.18" width="0.1524" layer="91"/>
<junction x="-149.86" y="149.86"/>
<junction x="-149.86" y="152.4"/>
<junction x="-149.86" y="154.94"/>
<junction x="-149.86" y="157.48"/>
<junction x="-149.86" y="160.02"/>
<junction x="-149.86" y="162.56"/>
<junction x="-149.86" y="165.1"/>
<junction x="-149.86" y="167.64"/>
<pinref part="GND22" gate="1" pin="GND"/>
<pinref part="XP1" gate="G$1" pin="20"/>
<pinref part="XP1" gate="G$1" pin="18"/>
<pinref part="XP1" gate="G$1" pin="16"/>
<pinref part="XP1" gate="G$1" pin="14"/>
<pinref part="XP1" gate="G$1" pin="12"/>
<pinref part="XP1" gate="G$1" pin="10"/>
<pinref part="XP1" gate="G$1" pin="8"/>
<pinref part="XP1" gate="G$1" pin="6"/>
<pinref part="XP1" gate="G$1" pin="4"/>
</segment>
<segment>
<wire x1="78.74" y1="213.36" x2="83.82" y2="213.36" width="0.1524" layer="91"/>
<wire x1="83.82" y1="213.36" x2="83.82" y2="208.28" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="10"/>
<pinref part="GND26" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="-60.96" y1="114.3" x2="-63.5" y2="114.3" width="0.1524" layer="91"/>
<pinref part="C23" gate="G$1" pin="1"/>
<pinref part="GND12" gate="1" pin="GND"/>
<pinref part="C7" gate="G$1" pin="1"/>
<wire x1="-63.5" y1="114.3" x2="-66.04" y2="114.3" width="0.1524" layer="91"/>
<wire x1="-53.34" y1="111.76" x2="-63.5" y2="111.76" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="111.76" x2="-63.5" y2="114.3" width="0.1524" layer="91"/>
<junction x="-63.5" y="114.3"/>
</segment>
<segment>
<pinref part="GND1" gate="1" pin="GND"/>
<pinref part="C6" gate="G$1" pin="-"/>
<wire x1="-66.04" y1="33.02" x2="-66.04" y2="30.48" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="GND_A"/>
<pinref part="GND3" gate="1" pin="GND"/>
<wire x1="-43.18" y1="93.98" x2="-50.8" y2="93.98" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C8" gate="G$1" pin="1"/>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="-76.2" y1="88.9" x2="-78.74" y2="88.9" width="0.1524" layer="91"/>
<pinref part="C9" gate="G$1" pin="1"/>
<wire x1="-78.74" y1="88.9" x2="-83.82" y2="88.9" width="0.1524" layer="91"/>
<wire x1="-68.58" y1="86.36" x2="-78.74" y2="86.36" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="86.36" x2="-78.74" y2="88.9" width="0.1524" layer="91"/>
<junction x="-78.74" y="88.9"/>
<pinref part="C10" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="83.82" x2="-78.74" y2="83.82" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="83.82" x2="-78.74" y2="86.36" width="0.1524" layer="91"/>
<junction x="-78.74" y="86.36"/>
<pinref part="C14" gate="G$1" pin="1"/>
<wire x1="-68.58" y1="81.28" x2="-78.74" y2="81.28" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="81.28" x2="-78.74" y2="83.82" width="0.1524" layer="91"/>
<junction x="-78.74" y="83.82"/>
<pinref part="C15" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="78.74" x2="-78.74" y2="78.74" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="78.74" x2="-78.74" y2="81.28" width="0.1524" layer="91"/>
<junction x="-78.74" y="81.28"/>
<pinref part="C16" gate="G$1" pin="1"/>
<wire x1="-68.58" y1="76.2" x2="-78.74" y2="76.2" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="76.2" x2="-78.74" y2="78.74" width="0.1524" layer="91"/>
<junction x="-78.74" y="78.74"/>
<pinref part="C17" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="73.66" x2="-78.74" y2="73.66" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="73.66" x2="-78.74" y2="76.2" width="0.1524" layer="91"/>
<junction x="-78.74" y="76.2"/>
<pinref part="C18" gate="G$1" pin="1"/>
<wire x1="-68.58" y1="71.12" x2="-78.74" y2="71.12" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="71.12" x2="-78.74" y2="73.66" width="0.1524" layer="91"/>
<junction x="-78.74" y="73.66"/>
<pinref part="C19" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="68.58" x2="-78.74" y2="68.58" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="68.58" x2="-78.74" y2="71.12" width="0.1524" layer="91"/>
<junction x="-78.74" y="71.12"/>
<pinref part="C20" gate="G$1" pin="1"/>
<wire x1="-68.58" y1="66.04" x2="-78.74" y2="66.04" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="66.04" x2="-78.74" y2="68.58" width="0.1524" layer="91"/>
<junction x="-78.74" y="68.58"/>
<pinref part="C21" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="63.5" x2="-78.74" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="63.5" x2="-78.74" y2="66.04" width="0.1524" layer="91"/>
<junction x="-78.74" y="66.04"/>
<pinref part="C22" gate="G$1" pin="1"/>
<wire x1="-68.58" y1="60.96" x2="-78.74" y2="60.96" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="60.96" x2="-78.74" y2="63.5" width="0.1524" layer="91"/>
<junction x="-78.74" y="63.5"/>
<pinref part="C24" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="58.42" x2="-78.74" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="58.42" x2="-78.74" y2="60.96" width="0.1524" layer="91"/>
<junction x="-78.74" y="60.96"/>
<pinref part="C25" gate="G$1" pin="1"/>
<wire x1="-68.58" y1="55.88" x2="-78.74" y2="55.88" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="55.88" x2="-78.74" y2="58.42" width="0.1524" layer="91"/>
<junction x="-78.74" y="58.42"/>
<pinref part="C26" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="53.34" x2="-78.74" y2="53.34" width="0.1524" layer="91"/>
<wire x1="-78.74" y1="53.34" x2="-78.74" y2="55.88" width="0.1524" layer="91"/>
<junction x="-78.74" y="55.88"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="GND@11"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="-43.18" y1="20.32" x2="-48.26" y2="20.32" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="GND@10"/>
<wire x1="-48.26" y1="20.32" x2="-53.34" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="22.86" x2="-48.26" y2="22.86" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="22.86" x2="-48.26" y2="20.32" width="0.1524" layer="91"/>
<junction x="-48.26" y="20.32"/>
<pinref part="U$4" gate="G$1" pin="GND@9"/>
<wire x1="-43.18" y1="25.4" x2="-48.26" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="25.4" x2="-48.26" y2="22.86" width="0.1524" layer="91"/>
<junction x="-48.26" y="22.86"/>
<pinref part="U$4" gate="G$1" pin="GND@8"/>
<wire x1="-43.18" y1="27.94" x2="-48.26" y2="27.94" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="27.94" x2="-48.26" y2="25.4" width="0.1524" layer="91"/>
<junction x="-48.26" y="25.4"/>
<pinref part="U$4" gate="G$1" pin="GND@7"/>
<wire x1="-43.18" y1="30.48" x2="-48.26" y2="30.48" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="30.48" x2="-48.26" y2="27.94" width="0.1524" layer="91"/>
<junction x="-48.26" y="27.94"/>
<pinref part="U$4" gate="G$1" pin="GND@6"/>
<wire x1="-43.18" y1="33.02" x2="-48.26" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="33.02" x2="-48.26" y2="30.48" width="0.1524" layer="91"/>
<junction x="-48.26" y="30.48"/>
<pinref part="U$4" gate="G$1" pin="GND@5"/>
<wire x1="-43.18" y1="35.56" x2="-48.26" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="35.56" x2="-48.26" y2="33.02" width="0.1524" layer="91"/>
<junction x="-48.26" y="33.02"/>
<pinref part="U$4" gate="G$1" pin="GND@4"/>
<wire x1="-43.18" y1="38.1" x2="-48.26" y2="38.1" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="38.1" x2="-48.26" y2="35.56" width="0.1524" layer="91"/>
<junction x="-48.26" y="35.56"/>
<pinref part="U$4" gate="G$1" pin="GND@3"/>
<wire x1="-43.18" y1="40.64" x2="-48.26" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="40.64" x2="-48.26" y2="38.1" width="0.1524" layer="91"/>
<junction x="-48.26" y="38.1"/>
<pinref part="U$4" gate="G$1" pin="GND@2"/>
<wire x1="-43.18" y1="43.18" x2="-48.26" y2="43.18" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="43.18" x2="-48.26" y2="40.64" width="0.1524" layer="91"/>
<junction x="-48.26" y="40.64"/>
<pinref part="U$4" gate="G$1" pin="GND@1"/>
<wire x1="-43.18" y1="45.72" x2="-48.26" y2="45.72" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="45.72" x2="-48.26" y2="43.18" width="0.1524" layer="91"/>
<junction x="-48.26" y="43.18"/>
<pinref part="U$4" gate="G$1" pin="GND@0"/>
<wire x1="-43.18" y1="48.26" x2="-48.26" y2="48.26" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="48.26" x2="-48.26" y2="45.72" width="0.1524" layer="91"/>
<junction x="-48.26" y="45.72"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="BOOT_0"/>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="-43.18" y1="7.62" x2="-53.34" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="RESET" class="0">
<segment>
<wire x1="-30.48" y1="175.26" x2="-22.86" y2="175.26" width="0.1524" layer="91"/>
<wire x1="-22.86" y1="175.26" x2="-12.7" y2="175.26" width="0.1524" layer="91"/>
<junction x="-22.86" y="175.26"/>
<label x="-12.7" y="175.26" size="1.27" layer="95" xref="yes"/>
<pinref part="C13" gate="G$1" pin="1"/>
<pinref part="R7" gate="G$1" pin="1"/>
<pinref part="S2" gate="1" pin="S"/>
</segment>
<segment>
<wire x1="-132.08" y1="154.94" x2="-124.46" y2="154.94" width="0.1524" layer="91"/>
<label x="-124.46" y="154.94" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="15"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="NRST"/>
<wire x1="-43.18" y1="-12.7" x2="-53.34" y2="-12.7" width="0.1524" layer="91"/>
<label x="-53.34" y="-12.7" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<wire x1="-139.7" y1="106.68" x2="-154.94" y2="106.68" width="0.1524" layer="91"/>
<pinref part="X1" gate="G$1" pin="D-"/>
<pinref part="R12" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<wire x1="-149.86" y1="109.22" x2="-154.94" y2="109.22" width="0.1524" layer="91"/>
<pinref part="X1" gate="G$1" pin="D+"/>
<pinref part="R13" gate="G$1" pin="1"/>
</segment>
</net>
<net name="USB_DM" class="0">
<segment>
<wire x1="-129.54" y1="106.68" x2="-127" y2="106.68" width="0.1524" layer="91"/>
<label x="-127" y="106.68" size="1.27" layer="95" xref="yes"/>
<pinref part="R12" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="PA11"/>
<wire x1="-43.18" y1="-45.72" x2="-53.34" y2="-45.72" width="0.1524" layer="91"/>
<label x="-53.34" y="-45.72" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="USB_DP" class="0">
<segment>
<wire x1="-139.7" y1="109.22" x2="-127" y2="109.22" width="0.1524" layer="91"/>
<label x="-127" y="109.22" size="1.27" layer="95" xref="yes"/>
<pinref part="R13" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="U$4" gate="G$1" pin="PA12"/>
<wire x1="-43.18" y1="-48.26" x2="-53.34" y2="-48.26" width="0.1524" layer="91"/>
<label x="-53.34" y="-48.26" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="5V_USB" class="0">
<segment>
<wire x1="-149.86" y1="104.14" x2="-154.94" y2="104.14" width="0.1524" layer="91"/>
<pinref part="X1" gate="G$1" pin="VBUS"/>
<pinref part="R1" gate="G$1" pin="2"/>
</segment>
</net>
<net name="TRST" class="0">
<segment>
<wire x1="-132.08" y1="170.18" x2="-124.46" y2="170.18" width="0.1524" layer="91"/>
<label x="-124.46" y="170.18" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="3"/>
</segment>
</net>
<net name="TDI" class="0">
<segment>
<wire x1="-132.08" y1="167.64" x2="-124.46" y2="167.64" width="0.1524" layer="91"/>
<label x="-124.46" y="167.64" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="5"/>
</segment>
</net>
<net name="TMS" class="0">
<segment>
<label x="-124.46" y="165.1" size="1.27" layer="95" xref="yes"/>
<wire x1="-124.46" y1="165.1" x2="-132.08" y2="165.1" width="0.1524" layer="91"/>
<pinref part="XP1" gate="G$1" pin="7"/>
</segment>
</net>
<net name="TCK" class="0">
<segment>
<wire x1="-132.08" y1="162.56" x2="-124.46" y2="162.56" width="0.1524" layer="91"/>
<label x="-124.46" y="162.56" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="9"/>
</segment>
</net>
<net name="TDO" class="0">
<segment>
<wire x1="-124.46" y1="157.48" x2="-132.08" y2="157.48" width="0.1524" layer="91"/>
<label x="-124.46" y="157.48" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="13"/>
</segment>
</net>
<net name="TO_GPS" class="0">
<segment>
<wire x1="63.5" y1="220.98" x2="55.88" y2="220.98" width="0.1524" layer="91"/>
<label x="55.88" y="220.98" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP2" gate="G$1" pin="3"/>
</segment>
</net>
<net name="FROM_GPS" class="0">
<segment>
<wire x1="78.74" y1="223.52" x2="86.36" y2="223.52" width="0.1524" layer="91"/>
<label x="86.36" y="223.52" size="1.27" layer="95" xref="yes"/>
<pinref part="JP2" gate="G$1" pin="2"/>
</segment>
</net>
<net name="GPS_PPS" class="0">
<segment>
<wire x1="78.74" y1="220.98" x2="86.36" y2="220.98" width="0.1524" layer="91"/>
<label x="86.36" y="220.98" size="1.27" layer="95" xref="yes"/>
<pinref part="JP2" gate="G$1" pin="4"/>
</segment>
</net>
<net name="GPS_ENABLE" class="0">
<segment>
<wire x1="63.5" y1="215.9" x2="55.88" y2="215.9" width="0.1524" layer="91"/>
<label x="55.88" y="215.9" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP2" gate="G$1" pin="7"/>
</segment>
</net>
<net name="LED_G" class="0">
<segment>
<wire x1="76.2" y1="149.86" x2="78.74" y2="149.86" width="0.1524" layer="91"/>
<label x="78.74" y="149.86" size="1.27" layer="95" rot="MR180" xref="yes"/>
<pinref part="R60" gate="G$1" pin="2"/>
</segment>
</net>
<net name="LED_R" class="0">
<segment>
<wire x1="68.58" y1="152.4" x2="78.74" y2="152.4" width="0.1524" layer="91"/>
<label x="78.74" y="152.4" size="1.27" layer="95" rot="MR180" xref="yes"/>
<pinref part="R30" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="R30" gate="G$1" pin="1"/>
<wire x1="58.42" y1="152.4" x2="55.88" y2="152.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="R60" gate="G$1" pin="1"/>
<wire x1="66.04" y1="149.86" x2="55.88" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="USB_PRESENT" class="0">
<segment>
<pinref part="R1" gate="G$1" pin="1"/>
<wire x1="-139.7" y1="104.14" x2="-127" y2="104.14" width="0.1524" layer="91"/>
<label x="-127" y="104.14" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="VCAP_2"/>
<pinref part="C23" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="114.3" x2="-53.34" y2="114.3" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="VCAP_1"/>
<pinref part="C7" gate="G$1" pin="2"/>
<wire x1="-43.18" y1="111.76" x2="-45.72" y2="111.76" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="PH0(OSC_IN)"/>
<wire x1="-43.18" y1="12.7" x2="-71.12" y2="12.7" width="0.1524" layer="91"/>
<wire x1="-81.28" y1="12.7" x2="-71.12" y2="12.7" width="0.1524" layer="91"/>
<pinref part="C12" gate="G$1" pin="2"/>
<pinref part="ZQ1" gate="G$1" pin="2"/>
<junction x="-71.12" y="12.7"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="PH1(OSC_OUT)"/>
<wire x1="-43.18" y1="15.24" x2="-66.04" y2="15.24" width="0.1524" layer="91"/>
<wire x1="-66.04" y1="15.24" x2="-66.04" y2="17.78" width="0.1524" layer="91"/>
<wire x1="-71.12" y1="17.78" x2="-73.66" y2="17.78" width="0.1524" layer="91"/>
<pinref part="ZQ1" gate="G$1" pin="1"/>
<pinref part="C11" gate="G$1" pin="2"/>
<wire x1="-66.04" y1="17.78" x2="-71.12" y2="17.78" width="0.1524" layer="91"/>
<junction x="-71.12" y="17.78"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
