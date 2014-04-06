<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
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
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
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
<package name="MICROSD">
<wire x1="-7.3" y1="7.2" x2="-7.3" y2="5.9" width="0.127" layer="51"/>
<wire x1="-7.3" y1="5.9" x2="-6.2" y2="5.9" width="0.127" layer="51"/>
<wire x1="-6.2" y1="5.9" x2="-6.2" y2="5.4" width="0.127" layer="51"/>
<wire x1="-6.2" y1="5.4" x2="-7.3" y2="5.4" width="0.127" layer="51"/>
<wire x1="-7.3" y1="5.4" x2="-7.3" y2="-8" width="0.127" layer="51"/>
<wire x1="-7.3" y1="-8" x2="-1.8" y2="-8" width="0.127" layer="51"/>
<wire x1="-1.8" y1="-8" x2="-1.8" y2="-7" width="0.127" layer="51"/>
<wire x1="-1.8" y1="-7" x2="-1.5" y2="-7" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-7" x2="-1.5" y2="-8" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-8" x2="-0.1" y2="-8" width="0.127" layer="51"/>
<wire x1="-0.1" y1="-8" x2="-0.1" y2="-7" width="0.127" layer="51"/>
<wire x1="-0.1" y1="-7" x2="0.3" y2="-7" width="0.127" layer="51"/>
<wire x1="0.3" y1="-7" x2="0.3" y2="-8" width="0.127" layer="51"/>
<wire x1="0.3" y1="-8" x2="2.022" y2="-8" width="0.127" layer="51"/>
<wire x1="2.022" y1="-8" x2="2.022" y2="-7" width="0.127" layer="51"/>
<wire x1="2.022" y1="-7" x2="2.449" y2="-7" width="0.127" layer="51"/>
<wire x1="2.449" y1="-7" x2="2.449" y2="-8" width="0.127" layer="51"/>
<wire x1="2.449" y1="-8" x2="5.6" y2="-8" width="0.127" layer="51"/>
<wire x1="5.6" y1="-8" x2="5.6" y2="-7" width="0.127" layer="51"/>
<wire x1="5.6" y1="-7" x2="6" y2="-7" width="0.127" layer="51"/>
<wire x1="6" y1="-7" x2="6" y2="-8" width="0.127" layer="51"/>
<wire x1="6" y1="-8" x2="7" y2="-8" width="0.127" layer="51"/>
<wire x1="7" y1="-8" x2="7" y2="6.3" width="0.127" layer="51"/>
<wire x1="7" y1="6.3" x2="6.5" y2="6.3" width="0.127" layer="51"/>
<wire x1="-7.3" y1="7.2" x2="-5" y2="7.2" width="0.127" layer="51"/>
<wire x1="-5" y1="7.2" x2="-5" y2="6.5" width="0.127" layer="51"/>
<wire x1="-5" y1="6.5" x2="6.4" y2="6.2" width="0.127" layer="51" curve="57.449475"/>
<wire x1="6.4" y1="6.2" x2="6.5" y2="6.3" width="0.127" layer="51"/>
<wire x1="-4.9" y1="6.4" x2="-4.9" y2="8.1597" width="0" layer="51"/>
<wire x1="-4.9" y1="8.1597" x2="-4.2597" y2="8.8" width="0" layer="51" curve="-90"/>
<wire x1="-4.2597" y1="8.8" x2="5.6929" y2="8.8" width="0" layer="51"/>
<wire x1="5.6929" y1="8.8" x2="6.4" y2="8.0929" width="0" layer="51" curve="-89.983796"/>
<wire x1="6.4" y1="8.0929" x2="6.4" y2="6.3" width="0" layer="51"/>
<wire x1="-4.9" y1="8.6" x2="-4.9" y2="11.9597" width="0" layer="51"/>
<wire x1="-4.9" y1="11.9597" x2="-4.2597" y2="12.6" width="0" layer="51" curve="-90"/>
<wire x1="-4.2597" y1="12.6" x2="5.6929" y2="12.6" width="0" layer="51"/>
<wire x1="5.6929" y1="12.6" x2="6.4" y2="11.8929" width="0" layer="51" curve="-89.983796"/>
<wire x1="6.4" y1="11.8929" x2="6.4" y2="8.4" width="0" layer="51"/>
<wire x1="-7.3" y1="4.9" x2="-7.3" y2="-8" width="0.127" layer="21"/>
<wire x1="-7.3" y1="-8" x2="-2.05" y2="-8" width="0.127" layer="21"/>
<wire x1="6.125" y1="-8" x2="7" y2="-8" width="0.127" layer="21"/>
<wire x1="7" y1="-8" x2="7" y2="3.8" width="0.127" layer="21"/>
<wire x1="0.425" y1="-8" x2="1.643" y2="-8" width="0.127" layer="21"/>
<wire x1="-5" y1="6.5" x2="5.4614" y2="5.7728" width="0.127" layer="21" curve="57.453442"/>
<smd name="9" x="6.55" y="5.55" dx="1.4" dy="1.9" layer="1"/>
<smd name="10" x="-6.85" y="6.55" dx="1.4" dy="1.9" layer="1"/>
<smd name="12" x="5.077" y="-7.6" dx="1.4" dy="1.4" layer="1"/>
<smd name="11" x="-0.75" y="-7.6" dx="1.8" dy="1.4" layer="1"/>
<smd name="8" x="5.76" y="2.7" dx="0.8" dy="1.5" layer="1"/>
<smd name="7" x="4.66" y="2.7" dx="0.8" dy="1.5" layer="1"/>
<smd name="6" x="3.56" y="2.9" dx="0.8" dy="1.5" layer="1"/>
<smd name="5" x="2.46" y="2.7" dx="0.8" dy="1.5" layer="1"/>
<smd name="4" x="1.36" y="2.9" dx="0.8" dy="1.5" layer="1"/>
<smd name="3" x="0.26" y="2.7" dx="0.8" dy="1.5" layer="1"/>
<smd name="2" x="-0.84" y="2.3" dx="0.8" dy="1.5" layer="1"/>
<smd name="1" x="-1.94" y="2.7" dx="0.8" dy="1.5" layer="1"/>
<smd name="13" x="3.56" y="-7.641" dx="0.8" dy="1.5" layer="1"/>
<text x="-0.7" y="7.8" size="0.8128" layer="51">card IN</text>
<text x="-1.3" y="11.6" size="0.8128" layer="51">card OUT</text>
<text x="-2.667" y="-9.906" size="1.016" layer="51">MicroSD</text>
<text x="-2.54" y="0" size="1.27" layer="21">1</text>
<text x="5.715" y="0" size="1.27" layer="21">8</text>
</package>
<package name="LED-1206">
<wire x1="-1" y1="1" x2="-2.4" y2="1" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="1" x2="-2.4" y2="-1" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="-1" x2="-1" y2="-1" width="0.2032" layer="21"/>
<wire x1="1" y1="1" x2="2.4" y2="1" width="0.2032" layer="21"/>
<wire x1="2.4" y1="1" x2="2.4" y2="-1" width="0.2032" layer="21"/>
<wire x1="2.4" y1="-1" x2="1" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.3" y1="0.7" x2="0.3" y2="0" width="0.2032" layer="21"/>
<wire x1="0.3" y1="0" x2="0.3" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="0.3" y1="0" x2="-0.3" y2="0.6" width="0.2032" layer="21"/>
<wire x1="-0.3" y1="0.6" x2="-0.3" y2="-0.6" width="0.2032" layer="21"/>
<wire x1="-0.3" y1="-0.6" x2="0.3" y2="0" width="0.2032" layer="21"/>
<smd name="A" x="-1.5" y="0" dx="1.2" dy="1.4" layer="1"/>
<smd name="C" x="1.5" y="0" dx="1.2" dy="1.4" layer="1"/>
<text x="-0.889" y="1.397" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.778" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="LED-0603">
<wire x1="0.46" y1="0.17" x2="0" y2="0.17" width="0.2032" layer="21"/>
<wire x1="-0.46" y1="0.17" x2="0" y2="0.17" width="0.2032" layer="21"/>
<wire x1="0" y1="0.17" x2="0.2338" y2="-0.14" width="0.2032" layer="21"/>
<wire x1="-0.0254" y1="0.1546" x2="-0.2184" y2="-0.14" width="0.2032" layer="21"/>
<smd name="C" x="0" y="0.75" dx="0.8" dy="0.8" layer="1"/>
<smd name="A" x="0" y="-0.75" dx="0.8" dy="0.8" layer="1"/>
<text x="-0.6985" y="-0.889" size="0.4064" layer="25" rot="R90">&gt;NAME</text>
<text x="1.0795" y="-1.016" size="0.4064" layer="27" rot="R90">&gt;VALUE</text>
</package>
<package name="LED-0805">
<wire x1="0.2446" y1="-0.5415" x2="0.244" y2="0.5236" width="0.1524" layer="21"/>
<wire x1="-0.188" y1="-0.3656" x2="0.2134" y2="-0.0547" width="0.1524" layer="21"/>
<wire x1="-0.1778" y1="0.3937" x2="0.2185" y2="0.0573" width="0.1524" layer="21"/>
<smd name="A" x="-0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<smd name="C" x="0.9" y="0" dx="0.8" dy="1.2" layer="1"/>
<text x="-0.762" y="0.8255" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.397" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="2X10-SHROUDED">
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
<package name="2X10-PSEUDOSMD">
<wire x1="11.26" y1="16.5" x2="2.26" y2="16.5" width="0.127" layer="51"/>
<wire x1="2.26" y1="16.5" x2="2.26" y2="-16.5" width="0.127" layer="51"/>
<wire x1="2.26" y1="-16.5" x2="11.26" y2="-16.5" width="0.127" layer="51"/>
<wire x1="11.26" y1="-16.5" x2="11.26" y2="-2.365" width="0.127" layer="51"/>
<wire x1="11.26" y1="-2.365" x2="11.26" y2="16.5" width="0.127" layer="51"/>
<wire x1="11.16" y1="2.365" x2="3.76" y2="2.365" width="0.127" layer="51"/>
<wire x1="3.76" y1="2.365" x2="3.76" y2="-2.365" width="0.127" layer="51"/>
<wire x1="3.76" y1="-2.365" x2="11.26" y2="-2.365" width="0.127" layer="51"/>
<circle x="-0.635" y="13.335" radius="0.449" width="0.254" layer="21"/>
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
<package name="MSOP8">
<description>&lt;b&gt;8M, 8-Lead, 0.118" Wide, Miniature Small Outline Package&lt;/b&gt;&lt;p&gt;
MSOP&lt;br&gt;
8M-Package doc1097.pdf</description>
<wire x1="-1.48" y1="1.23" x2="-1.23" y2="1.48" width="0.1524" layer="21" curve="-90" cap="flat"/>
<wire x1="1.23" y1="1.48" x2="1.48" y2="1.23" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.23" y1="-1.49" x2="1.48" y2="-1.24" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.48" y1="-1.24" x2="-1.23" y2="-1.49" width="0.1524" layer="21" curve="90" cap="flat"/>
<wire x1="1.24" y1="-1.49" x2="-1.22" y2="-1.49" width="0.1524" layer="21"/>
<wire x1="-1.22" y1="1.48" x2="1.24" y2="1.48" width="0.1524" layer="21"/>
<wire x1="-1.48" y1="1.23" x2="-1.48" y2="-1.23" width="0.1524" layer="21"/>
<wire x1="1.48" y1="-1.24" x2="1.48" y2="1.23" width="0.1524" layer="21"/>
<circle x="-0.65" y="-0.65" radius="0.325" width="0.254" layer="21"/>
<smd name="1" x="-0.975" y="-2.25" dx="0.4" dy="1.1" layer="1"/>
<smd name="2" x="-0.325" y="-2.25" dx="0.4" dy="1.1" layer="1"/>
<smd name="3" x="0.325" y="-2.25" dx="0.4" dy="1.1" layer="1"/>
<smd name="4" x="0.975" y="-2.25" dx="0.4" dy="1.1" layer="1"/>
<smd name="5" x="0.975" y="2.25" dx="0.4" dy="1.1" layer="1"/>
<smd name="6" x="0.325" y="2.25" dx="0.4" dy="1.1" layer="1"/>
<smd name="7" x="-0.325" y="2.25" dx="0.4" dy="1.1" layer="1"/>
<smd name="8" x="-0.975" y="2.25" dx="0.4" dy="1.1" layer="1"/>
<text x="-2.54" y="-1.27" size="0.4064" layer="25" rot="R90">&gt;NAME</text>
<text x="2.54" y="-1.27" size="0.4064" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.175" y1="-2.45" x2="-0.775" y2="-1.55" layer="51"/>
<rectangle x1="-0.525" y1="-2.45" x2="-0.125" y2="-1.55" layer="51"/>
<rectangle x1="0.125" y1="-2.45" x2="0.525" y2="-1.55" layer="51"/>
<rectangle x1="0.775" y1="-2.45" x2="1.175" y2="-1.55" layer="51"/>
<rectangle x1="0.775" y1="1.55" x2="1.175" y2="2.45" layer="51"/>
<rectangle x1="0.125" y1="1.55" x2="0.525" y2="2.45" layer="51"/>
<rectangle x1="-0.525" y1="1.55" x2="-0.125" y2="2.45" layer="51"/>
<rectangle x1="-1.175" y1="1.55" x2="-0.775" y2="2.45" layer="51"/>
</package>
<package name="SO-08M">
<description>&lt;B&gt;Small Outline Medium Plastic Gull Wing&lt;/B&gt;&lt;p&gt;
207-mil body, package type SM</description>
<wire x1="2.4" y1="2.43" x2="2.4" y2="-1.93" width="0.2032" layer="21"/>
<wire x1="2.4" y1="-1.93" x2="2.4" y2="-2.43" width="0.2032" layer="21"/>
<wire x1="2.4" y1="-2.43" x2="-2.4" y2="-2.43" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="-2.43" x2="-2.4" y2="-1.93" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="-1.93" x2="-2.4" y2="2.43" width="0.2032" layer="21"/>
<wire x1="-2.4" y1="2.43" x2="2.4" y2="2.43" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-1.93" x2="-2.4" y2="-1.93" width="0.2032" layer="21"/>
<smd name="2" x="-0.635" y="-3.33" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="-0.635" y="3.33" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-1.905" y="-3.33" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="0.635" y="-3.33" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="1.905" y="-3.33" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="-1.905" y="3.33" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="0.635" y="3.33" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="1.905" y="3.33" dx="0.6" dy="2.2" layer="1"/>
<text x="-2.667" y="-2.54" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.937" y="-2.54" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<text x="-1.905" y="-1.27" size="0.3048" layer="48">SO8 Medium</text>
<text x="-1.905" y="-0.635" size="0.3048" layer="48">Microchip</text>
<rectangle x1="-2.1501" y1="-4.05" x2="-1.6599" y2="-2.5301" layer="21"/>
<rectangle x1="-0.8801" y1="-4.05" x2="-0.3899" y2="-2.5301" layer="21"/>
<rectangle x1="0.3899" y1="-4.05" x2="0.8801" y2="-2.5301" layer="21"/>
<rectangle x1="1.6599" y1="-4.05" x2="2.1501" y2="-2.5301" layer="21"/>
<rectangle x1="1.6599" y1="2.5301" x2="2.1501" y2="4.05" layer="21"/>
<rectangle x1="0.3899" y1="2.5301" x2="0.8801" y2="4.05" layer="21"/>
<rectangle x1="-0.8801" y1="2.5301" x2="-0.3899" y2="4.05" layer="21"/>
<rectangle x1="-2.1501" y1="2.5301" x2="-1.6599" y2="4.05" layer="21"/>
</package>
<package name="SO-14">
<description>&lt;B&gt;Small Outline Narrow Plastic Gull Wing&lt;/B&gt;&lt;p&gt;
150-mil body, package type SL</description>
<wire x1="-4.895" y1="3.9" x2="4.895" y2="3.9" width="0.1998" layer="39"/>
<wire x1="4.895" y1="-3.9" x2="-4.895" y2="-3.9" width="0.1998" layer="39"/>
<wire x1="-4.895" y1="-3.9" x2="-4.895" y2="3.9" width="0.1998" layer="39"/>
<wire x1="4.305" y1="-1.9" x2="-4.305" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-4.305" y1="-1.9" x2="-4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-4.305" y1="-1.4" x2="-4.305" y2="1.9" width="0.2032" layer="51"/>
<wire x1="4.305" y1="-1.4" x2="-4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.305" y1="1.9" x2="4.305" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="4.305" y1="-1.4" x2="4.305" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="4.895" y1="3.9" x2="4.895" y2="-3.9" width="0.1998" layer="39"/>
<wire x1="-4.305" y1="1.9" x2="4.305" y2="1.9" width="0.2032" layer="51"/>
<smd name="2" x="-2.54" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="13" x="-2.54" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-3.81" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="-1.27" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="0" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="14" x="-3.81" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="12" x="-1.27" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="11" x="0" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="2.54" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="9" x="2.54" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="1.27" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="3.81" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="10" x="1.27" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="3.81" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<text x="-4.572" y="-1.905" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="5.842" y="-1.905" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<text x="-3.81" y="0.365" size="0.3048" layer="48">JEDEC MS-012 AB</text>
<text x="-3.81" y="-0.635" size="0.4064" layer="48">IPC SO14</text>
<rectangle x1="-4.0551" y1="-3.1001" x2="-3.5649" y2="-2" layer="51"/>
<rectangle x1="-2.7851" y1="-3.1001" x2="-2.2949" y2="-2" layer="51"/>
<rectangle x1="-1.5151" y1="-3.1001" x2="-1.0249" y2="-2" layer="51"/>
<rectangle x1="-0.2451" y1="-3.1001" x2="0.2451" y2="-2" layer="51"/>
<rectangle x1="-0.2451" y1="2" x2="0.2451" y2="3.1001" layer="51"/>
<rectangle x1="-1.5151" y1="2" x2="-1.0249" y2="3.1001" layer="51"/>
<rectangle x1="-2.7851" y1="2" x2="-2.2949" y2="3.1001" layer="51"/>
<rectangle x1="-4.0551" y1="2" x2="-3.5649" y2="3.1001" layer="51"/>
<rectangle x1="1.0249" y1="-3.1001" x2="1.5151" y2="-2" layer="51"/>
<rectangle x1="2.2949" y1="-3.1001" x2="2.7851" y2="-2" layer="51"/>
<rectangle x1="3.5649" y1="-3.1001" x2="4.0551" y2="-2" layer="51"/>
<rectangle x1="3.5649" y1="2" x2="4.0551" y2="3.1001" layer="51"/>
<rectangle x1="2.2949" y1="2" x2="2.7851" y2="3.1001" layer="51"/>
<rectangle x1="1.0249" y1="2" x2="1.5151" y2="3.1001" layer="51"/>
</package>
<package name="DIL8">
<description>&lt;B&gt;Dual In Line&lt;/B&gt;&lt;p&gt;
package type P</description>
<wire x1="-5.08" y1="-0.635" x2="-5.08" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21" curve="180"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="2.54" x2="5.08" y2="2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<pad name="1" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90" first="yes"/>
<pad name="2" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-5.2578" y="-2.54" size="1.778" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="7.239" y="-2.54" size="1.778" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
</package>
<package name="SO-08">
<description>&lt;B&gt;Small Outline Narrow Plastic Gull Wing&lt;/B&gt;&lt;p&gt;
150-mil body, package type SN</description>
<wire x1="-2.9" y1="3.9" x2="2.9" y2="3.9" width="0.1998" layer="39"/>
<wire x1="2.9" y1="3.9" x2="2.9" y2="-3.9" width="0.1998" layer="39"/>
<wire x1="2.9" y1="-3.9" x2="-2.9" y2="-3.9" width="0.1998" layer="39"/>
<wire x1="-2.9" y1="-3.9" x2="-2.9" y2="3.9" width="0.1998" layer="39"/>
<wire x1="2.4" y1="1.9" x2="2.4" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-1.4" x2="2.4" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-1.9" x2="-2.4" y2="-1.9" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="-1.9" x2="-2.4" y2="-1.4" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="-1.4" x2="-2.4" y2="1.9" width="0.2032" layer="51"/>
<wire x1="-2.4" y1="1.9" x2="2.4" y2="1.9" width="0.2032" layer="51"/>
<wire x1="2.4" y1="-1.4" x2="-2.4" y2="-1.4" width="0.2032" layer="51"/>
<smd name="2" x="-0.635" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="7" x="-0.635" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="1" x="-1.905" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="3" x="0.635" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="4" x="1.905" y="-2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="8" x="-1.905" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="6" x="0.635" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<smd name="5" x="1.905" y="2.6" dx="0.6" dy="2.2" layer="1"/>
<text x="-2.667" y="-1.905" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="3.937" y="-1.905" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<text x="-1.905" y="-0.635" size="0.4064" layer="48">IPC SO8</text>
<text x="-1.905" y="0.365" size="0.3048" layer="48">JEDEC MS-012 AA</text>
<rectangle x1="-2.1501" y1="-3.1001" x2="-1.6599" y2="-2" layer="51"/>
<rectangle x1="-0.8801" y1="-3.1001" x2="-0.3899" y2="-2" layer="51"/>
<rectangle x1="0.3899" y1="-3.1001" x2="0.8801" y2="-2" layer="51"/>
<rectangle x1="1.6599" y1="-3.1001" x2="2.1501" y2="-2" layer="51"/>
<rectangle x1="1.6599" y1="2" x2="2.1501" y2="3.1001" layer="51"/>
<rectangle x1="0.3899" y1="2" x2="0.8801" y2="3.1001" layer="51"/>
<rectangle x1="-0.8801" y1="2" x2="-0.3899" y2="3.1001" layer="51"/>
<rectangle x1="-2.1501" y1="2" x2="-1.6599" y2="3.1001" layer="51"/>
<rectangle x1="-1" y1="-1" x2="1" y2="1" layer="35"/>
</package>
<package name="TSSOP8">
<description>&lt;b&gt;Thin Shrink Small Outline Package&lt;/b&gt;&lt;p&gt;
package type ST</description>
<wire x1="1.4" y1="-2.15" x2="1.4" y2="2.15" width="0.2032" layer="21"/>
<wire x1="1.4" y1="2.15" x2="-1.4" y2="2.15" width="0.2032" layer="21"/>
<wire x1="-1.4" y1="2.15" x2="-1.4" y2="-2.15" width="0.2032" layer="21"/>
<wire x1="-1.4" y1="-2.15" x2="1.4" y2="-2.15" width="0.2032" layer="21"/>
<circle x="-0.65" y="-1.625" radius="0.325" width="0" layer="21"/>
<smd name="1" x="-0.975" y="-2.925" dx="0.35" dy="1.2" layer="1"/>
<smd name="2" x="-0.325" y="-2.925" dx="0.35" dy="1.2" layer="1"/>
<smd name="3" x="0.325" y="-2.925" dx="0.35" dy="1.2" layer="1"/>
<smd name="4" x="0.975" y="-2.925" dx="0.35" dy="1.2" layer="1"/>
<smd name="5" x="0.975" y="2.925" dx="0.35" dy="1.2" layer="1"/>
<smd name="6" x="0.325" y="2.925" dx="0.35" dy="1.2" layer="1"/>
<smd name="7" x="-0.325" y="2.925" dx="0.35" dy="1.2" layer="1"/>
<smd name="8" x="-0.975" y="2.925" dx="0.35" dy="1.2" layer="1"/>
<text x="-1.625" y="-2.925" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="2.925" y="-3.25" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.1" y1="-3.2" x2="-0.85" y2="-2.2" layer="51"/>
<rectangle x1="-0.45" y1="-3.2" x2="-0.2" y2="-2.2" layer="51"/>
<rectangle x1="0.2" y1="-3.2" x2="0.45" y2="-2.2" layer="51"/>
<rectangle x1="0.85" y1="-3.2" x2="1.1" y2="-2.2" layer="51"/>
<rectangle x1="0.85" y1="2.2" x2="1.1" y2="3.2" layer="51"/>
<rectangle x1="0.2" y1="2.2" x2="0.45" y2="3.2" layer="51"/>
<rectangle x1="-0.45" y1="2.2" x2="-0.2" y2="3.2" layer="51"/>
<rectangle x1="-1.1" y1="2.2" x2="-0.85" y2="3.2" layer="51"/>
</package>
<package name="BMP085">
<wire x1="2.5" y1="2.5" x2="2.5" y2="-2.5" width="0.127" layer="51"/>
<wire x1="2.5" y1="-2.5" x2="-2.5" y2="-2.5" width="0.127" layer="51"/>
<wire x1="-2.5" y1="2.5" x2="-2.5" y2="-2.5" width="0.127" layer="51"/>
<wire x1="2.5" y1="2.5" x2="-2.5" y2="2.5" width="0.127" layer="51"/>
<wire x1="-2.5" y1="2.5" x2="-2.5" y2="1.9" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="2.5" x2="-1.9" y2="2.5" width="0.2032" layer="21"/>
<wire x1="2.5" y1="2.5" x2="1.9" y2="2.5" width="0.2032" layer="21"/>
<wire x1="2.5" y1="2.5" x2="2.5" y2="1.9" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-2.5" x2="-2.5" y2="-1.9" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-2.5" x2="-1.8" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-2.5" x2="1.8" y2="-2.5" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-2.5" x2="2.5" y2="-1.9" width="0.2032" layer="21"/>
<circle x="-2.1" y="2.1" radius="0.2" width="0.127" layer="21"/>
<smd name="8" x="0" y="1.65" dx="2.5" dy="0.8" layer="1" rot="R90"/>
<smd name="4" x="0" y="-2.065" dx="1.67" dy="0.8" layer="1" rot="R90"/>
<smd name="7" x="2.065" y="1.27" dx="0.8" dy="1.67" layer="1" rot="R270"/>
<smd name="6" x="2.065" y="0" dx="0.8" dy="1.67" layer="1" rot="R270"/>
<smd name="5" x="2.065" y="-1.27" dx="0.8" dy="1.67" layer="1" rot="R270"/>
<smd name="3" x="-2.065" y="-1.27" dx="0.8" dy="1.67" layer="1" rot="R270"/>
<smd name="2" x="-2.065" y="0" dx="0.8" dy="1.67" layer="1" rot="R270"/>
<smd name="1" x="-2.065" y="1.27" dx="0.8" dy="1.67" layer="1" rot="R270"/>
</package>
<package name="1812">
<description>&lt;b&gt;CAPACITOR&lt;/b&gt;</description>
<wire x1="-2.973" y1="1.983" x2="2.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="2.973" y1="-1.983" x2="-2.973" y2="-1.983" width="0.0508" layer="39"/>
<wire x1="-2.973" y1="-1.983" x2="-2.973" y2="1.983" width="0.0508" layer="39"/>
<wire x1="-1.4732" y1="1.6002" x2="1.4732" y2="1.6002" width="0.1016" layer="51"/>
<wire x1="-1.4478" y1="-1.6002" x2="1.4732" y2="-1.6002" width="0.1016" layer="51"/>
<wire x1="2.973" y1="1.983" x2="2.973" y2="-1.983" width="0.0508" layer="39"/>
<smd name="1" x="-1.95" y="0" dx="1.9" dy="3.4" layer="1"/>
<smd name="2" x="1.95" y="0" dx="1.9" dy="3.4" layer="1"/>
<text x="-1.905" y="2.54" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.81" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.3876" y1="-1.651" x2="-1.4376" y2="1.649" layer="51"/>
<rectangle x1="1.4478" y1="-1.651" x2="2.3978" y2="1.649" layer="51"/>
<rectangle x1="-0.3" y1="-0.4001" x2="0.3" y2="0.4001" layer="35"/>
</package>
<package name="SOD80C">
<description>&lt;B&gt;DIODE&lt;/B&gt;</description>
<wire x1="1.3208" y1="0.7874" x2="-1.3208" y2="0.7874" width="0.1524" layer="51"/>
<wire x1="1.3208" y1="-0.7874" x2="-1.3208" y2="-0.7874" width="0.1524" layer="51"/>
<wire x1="0.627" y1="0.6" x2="-0.373" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.373" y1="0" x2="0.627" y2="-0.6" width="0.2032" layer="21"/>
<wire x1="0.627" y1="-0.6" x2="0.627" y2="0.6" width="0.2032" layer="21"/>
<smd name="C" x="-1.7" y="0" dx="1.4" dy="1.8" layer="1"/>
<smd name="A" x="1.7" y="0" dx="1.4" dy="1.8" layer="1"/>
<text x="-1.524" y="1.143" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.524" y="-2.413" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.8542" y1="-0.8636" x2="-1.2954" y2="0.8636" layer="51"/>
<rectangle x1="1.2954" y1="-0.8636" x2="1.8542" y2="0.8636" layer="51"/>
<rectangle x1="-0.8636" y1="-0.7874" x2="-0.254" y2="0.7874" layer="21"/>
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
<circle x="-0.635" y="6.985" radius="0.449" width="0.254" layer="21"/>
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
<text x="-1.451" y="-7.682" size="0.4064" layer="104">&gt;NAME</text>
<rectangle x1="-1.27" y1="4.7625" x2="8.255" y2="5.3975" layer="51"/>
<rectangle x1="-1.27" y1="2.2225" x2="8.255" y2="2.8575" layer="51"/>
<rectangle x1="-1.27" y1="-0.3175" x2="8.255" y2="0.3175" layer="51"/>
<rectangle x1="-1.27" y1="-2.8575" x2="8.255" y2="-2.2225" layer="51"/>
<rectangle x1="-1.27" y1="-5.3975" x2="8.255" y2="-4.7625" layer="51"/>
</package>
<package name="BUTTON_6X3.5">
<wire x1="0" y1="0" x2="6" y2="0" width="0.127" layer="21"/>
<wire x1="6" y1="0" x2="6" y2="-3.5" width="0.127" layer="21"/>
<wire x1="6" y1="-3.5" x2="0" y2="-3.5" width="0.127" layer="21"/>
<wire x1="0" y1="-3.5" x2="0" y2="0" width="0.127" layer="21"/>
<wire x1="1" y1="-2" x2="2" y2="-2" width="0.127" layer="51"/>
<wire x1="2" y1="-2" x2="3" y2="-1" width="0.127" layer="51"/>
<wire x1="3" y1="-2" x2="4.75" y2="-2" width="0.127" layer="51"/>
<wire x1="0" y1="-0.5" x2="0" y2="0" width="0.254" layer="51"/>
<wire x1="0" y1="0" x2="6" y2="0" width="0.254" layer="51"/>
<wire x1="6" y1="0" x2="6" y2="-0.5" width="0.254" layer="51"/>
<wire x1="0" y1="-3" x2="0" y2="-3.5" width="0.254" layer="51"/>
<wire x1="0" y1="-3.5" x2="6" y2="-3.5" width="0.254" layer="51"/>
<wire x1="6" y1="-3.5" x2="6" y2="-3" width="0.254" layer="51"/>
<smd name="P" x="0" y="-1.75" dx="1.5" dy="1.5" layer="1"/>
<smd name="S" x="6" y="-1.75" dx="1.5" dy="1.5" layer="1"/>
<text x="0" y="0.5" size="1.27" layer="25">&gt;NAME</text>
<text x="0" y="-5.25" size="1.27" layer="25">&gt;VALUE</text>
</package>
<package name="SOT23-5">
<description>&lt;b&gt;Small Outline Transistor&lt;/b&gt;, 5 lead</description>
<wire x1="-1.544" y1="0.713" x2="1.544" y2="0.713" width="0.1524" layer="21"/>
<wire x1="1.544" y1="0.713" x2="1.544" y2="-0.712" width="0.1524" layer="21"/>
<wire x1="1.544" y1="-0.712" x2="-1.544" y2="-0.712" width="0.1524" layer="21"/>
<wire x1="-1.544" y1="-0.712" x2="-1.544" y2="0.713" width="0.1524" layer="21"/>
<smd name="5" x="-0.95" y="1.306" dx="0.6" dy="1.2" layer="1"/>
<smd name="4" x="0.95" y="1.306" dx="0.6" dy="1.2" layer="1"/>
<smd name="1" x="-0.95" y="-1.306" dx="0.6" dy="1.2" layer="1"/>
<smd name="2" x="0" y="-1.306" dx="0.6" dy="1.2" layer="1"/>
<smd name="3" x="0.95" y="-1.306" dx="0.6" dy="1.2" layer="1"/>
<text x="-1.778" y="-1.778" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.048" y="-1.778" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.1875" y1="0.7126" x2="-0.7125" y2="1.5439" layer="51"/>
<rectangle x1="0.7125" y1="0.7126" x2="1.1875" y2="1.5439" layer="51"/>
<rectangle x1="-1.1875" y1="-1.5437" x2="-0.7125" y2="-0.7124" layer="51"/>
<rectangle x1="-0.2375" y1="-1.5437" x2="0.2375" y2="-0.7124" layer="51"/>
<rectangle x1="0.7125" y1="-1.5437" x2="1.1875" y2="-0.7124" layer="51"/>
</package>
<package name="1X2-PSEUDOSMD">
<wire x1="1.1" y1="2.53" x2="-1.55" y2="2.53" width="0.127" layer="51"/>
<wire x1="-1.55" y1="2.53" x2="-1.55" y2="-2.53" width="0.127" layer="51"/>
<wire x1="-1.55" y1="-2.53" x2="1.1" y2="-2.53" width="0.127" layer="51"/>
<wire x1="1.1" y1="-2.53" x2="1.1" y2="2.53" width="0.127" layer="51"/>
<circle x="-6.985" y="1.27" radius="0.449" width="0.254" layer="21"/>
<smd name="1" x="-3.81" y="1.27" dx="4" dy="2" layer="1"/>
<smd name="2" x="-3.81" y="-1.27" dx="4" dy="2" layer="1" rot="R180"/>
<text x="-1.451" y="2.859" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<text x="-1.451" y="-3.237" size="0.4064" layer="25">&gt;NAME</text>
<rectangle x1="-3.81" y1="0.9525" x2="5.715" y2="1.5875" layer="51"/>
<rectangle x1="-3.81" y1="-1.5875" x2="5.715" y2="-0.9525" layer="51"/>
</package>
<package name="1X02">
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="482">
<wire x1="-5.334" y1="-6.35" x2="6.858" y2="-6.35" width="0.127" layer="51"/>
<wire x1="6.858" y1="-6.35" x2="6.858" y2="5.842" width="0.127" layer="51"/>
<wire x1="6.858" y1="5.842" x2="5.588" y2="5.842" width="0.127" layer="51"/>
<wire x1="5.588" y1="5.842" x2="3.81" y2="5.842" width="0.127" layer="51"/>
<wire x1="3.81" y1="5.842" x2="-2.032" y2="5.842" width="0.127" layer="51"/>
<wire x1="-2.032" y1="5.842" x2="-3.81" y2="5.842" width="0.127" layer="51"/>
<wire x1="-3.81" y1="5.842" x2="-5.334" y2="5.842" width="0.127" layer="51"/>
<wire x1="-5.334" y1="5.842" x2="-5.334" y2="-6.35" width="0.127" layer="51"/>
<wire x1="-3.81" y1="5.842" x2="-3.81" y2="12.192" width="0.127" layer="51"/>
<wire x1="-3.81" y1="12.192" x2="-2.032" y2="12.192" width="0.127" layer="51"/>
<wire x1="-2.032" y1="12.192" x2="-2.032" y2="5.842" width="0.127" layer="51"/>
<wire x1="5.588" y1="5.842" x2="5.588" y2="12.192" width="0.127" layer="51"/>
<wire x1="5.588" y1="12.192" x2="3.81" y2="12.192" width="0.127" layer="51"/>
<wire x1="3.81" y1="12.192" x2="3.81" y2="5.842" width="0.127" layer="51"/>
<wire x1="-5.334" y1="-6.35" x2="-5.334" y2="5.842" width="0.254" layer="21"/>
<wire x1="-5.334" y1="5.842" x2="6.858" y2="5.842" width="0.254" layer="21"/>
<wire x1="6.858" y1="5.842" x2="6.858" y2="-6.35" width="0.254" layer="21"/>
<wire x1="6.858" y1="-6.35" x2="-5.334" y2="-6.35" width="0.254" layer="21"/>
<circle x="-3.81" y="4.318" radius="0.8032" width="0.254" layer="21"/>
<smd name="1" x="-7.62" y="3.81" dx="2.54" dy="1.524" layer="1"/>
<smd name="2" x="-7.62" y="1.27" dx="2.54" dy="1.524" layer="1"/>
<smd name="3" x="-7.62" y="-1.27" dx="2.54" dy="1.524" layer="1"/>
<smd name="4" x="-7.62" y="-3.81" dx="2.54" dy="1.524" layer="1"/>
<smd name="5" x="9.144" y="-3.81" dx="2.54" dy="1.524" layer="1"/>
<smd name="6" x="9.144" y="-1.27" dx="2.54" dy="1.524" layer="1"/>
<smd name="7" x="9.144" y="1.27" dx="2.54" dy="1.524" layer="1"/>
<smd name="8" x="9.144" y="3.81" dx="2.54" dy="1.524" layer="1"/>
<text x="-1.905" y="6.35" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-5.08" y="-8.255" size="1.27" layer="27" font="vector">&gt;VALUE</text>
</package>
<package name="TQFP100">
<wire x1="-7" y1="6.25" x2="-6.25" y2="7" width="0.254" layer="21"/>
<wire x1="-6.25" y1="7" x2="6.75" y2="7" width="0.254" layer="21"/>
<wire x1="6.75" y1="7" x2="7" y2="6.75" width="0.254" layer="21"/>
<wire x1="7" y1="6.75" x2="7" y2="-6.75" width="0.254" layer="21"/>
<wire x1="7" y1="-6.75" x2="6.75" y2="-7" width="0.254" layer="21"/>
<wire x1="6.75" y1="-7" x2="-6.75" y2="-7" width="0.254" layer="21"/>
<wire x1="-6.75" y1="-7" x2="-7" y2="-6.75" width="0.254" layer="21"/>
<wire x1="-7" y1="-6.75" x2="-7" y2="6.25" width="0.254" layer="21"/>
<circle x="-6" y="6" radius="0.2499" width="0.254" layer="21"/>
<smd name="1" x="-8" y="6" dx="1.5" dy="0.3" layer="1"/>
<smd name="2" x="-8" y="5.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="3" x="-8" y="5" dx="1.5" dy="0.3" layer="1"/>
<smd name="4" x="-8" y="4.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="5" x="-8" y="4" dx="1.5" dy="0.3" layer="1"/>
<smd name="6" x="-8" y="3.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="7" x="-8" y="3" dx="1.5" dy="0.3" layer="1"/>
<smd name="8" x="-8" y="2.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="9" x="-8" y="2" dx="1.5" dy="0.3" layer="1"/>
<smd name="10" x="-8" y="1.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="11" x="-8" y="1" dx="1.5" dy="0.3" layer="1"/>
<smd name="12" x="-8" y="0.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="13" x="-8" y="0" dx="1.5" dy="0.3" layer="1"/>
<smd name="14" x="-8" y="-0.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="15" x="-8" y="-1" dx="1.5" dy="0.3" layer="1"/>
<smd name="16" x="-8" y="-1.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="17" x="-8" y="-2" dx="1.5" dy="0.3" layer="1"/>
<smd name="18" x="-8" y="-2.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="19" x="-8" y="-3" dx="1.5" dy="0.3" layer="1"/>
<smd name="20" x="-8" y="-3.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="21" x="-8" y="-4" dx="1.5" dy="0.3" layer="1"/>
<smd name="22" x="-8" y="-4.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="23" x="-8" y="-5" dx="1.5" dy="0.3" layer="1"/>
<smd name="24" x="-8" y="-5.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="25" x="-8" y="-6" dx="1.5" dy="0.3" layer="1"/>
<smd name="26" x="-6" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="27" x="-5.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="28" x="-5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="29" x="-4.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="30" x="-4" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="31" x="-3.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="32" x="-3" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="33" x="-2.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="34" x="-2" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="35" x="-1.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="36" x="-1" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="37" x="-0.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="38" x="0" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="39" x="0.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="40" x="1" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="41" x="1.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="42" x="2" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="43" x="2.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="44" x="3" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="45" x="3.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="46" x="4" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="47" x="4.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="48" x="5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="49" x="5.5" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="50" x="6" y="-8" dx="0.3" dy="1.5" layer="1"/>
<smd name="51" x="8" y="-6" dx="1.5" dy="0.3" layer="1"/>
<smd name="52" x="8" y="-5.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="53" x="8" y="-5" dx="1.5" dy="0.3" layer="1"/>
<smd name="54" x="8" y="-4.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="55" x="8" y="-4" dx="1.5" dy="0.3" layer="1"/>
<smd name="56" x="8" y="-3.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="57" x="8" y="-3" dx="1.5" dy="0.3" layer="1"/>
<smd name="58" x="8" y="-2.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="59" x="8" y="-2" dx="1.5" dy="0.3" layer="1"/>
<smd name="60" x="8" y="-1.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="61" x="8" y="-1" dx="1.5" dy="0.3" layer="1"/>
<smd name="62" x="8" y="-0.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="63" x="8" y="0" dx="1.5" dy="0.3" layer="1"/>
<smd name="64" x="8" y="0.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="65" x="8" y="1" dx="1.5" dy="0.3" layer="1"/>
<smd name="66" x="8" y="1.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="67" x="8" y="2" dx="1.5" dy="0.3" layer="1"/>
<smd name="68" x="8" y="2.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="69" x="8" y="3" dx="1.5" dy="0.3" layer="1"/>
<smd name="70" x="8" y="3.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="71" x="8" y="4" dx="1.5" dy="0.3" layer="1"/>
<smd name="72" x="8" y="4.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="73" x="8" y="5" dx="1.5" dy="0.3" layer="1"/>
<smd name="74" x="8" y="5.5" dx="1.5" dy="0.3" layer="1"/>
<smd name="75" x="8" y="6" dx="1.5" dy="0.3" layer="1"/>
<smd name="76" x="6" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="77" x="5.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="78" x="5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="79" x="4.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="80" x="4" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="81" x="3.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="82" x="3" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="83" x="2.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="84" x="2" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="85" x="1.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="86" x="1" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="87" x="0.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="88" x="0" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="89" x="-0.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="90" x="-1" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="91" x="-1.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="92" x="-2" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="93" x="-2.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="94" x="-3" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="95" x="-3.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="96" x="-4" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="97" x="-4.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="98" x="-5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="99" x="-5.5" y="8" dx="0.3" dy="1.5" layer="1"/>
<smd name="100" x="-6" y="8" dx="0.3" dy="1.5" layer="1"/>
<text x="-5.76" y="9.2451" size="1.016" layer="25" ratio="18">&gt;NAME</text>
<text x="-6.3551" y="-0.3749" size="0.8128" layer="27">&gt;VALUE</text>
<rectangle x1="-8.1999" y1="5.8499" x2="-7.1501" y2="6.1501" layer="51"/>
<rectangle x1="-8.1999" y1="5.35" x2="-7.1501" y2="5.65" layer="51"/>
<rectangle x1="-8.1999" y1="4.8499" x2="-7.1501" y2="5.1501" layer="51"/>
<rectangle x1="-8.1999" y1="4.35" x2="-7.1501" y2="4.65" layer="51"/>
<rectangle x1="-8.1999" y1="3.8499" x2="-7.1501" y2="4.1501" layer="51"/>
<rectangle x1="-8.1999" y1="3.35" x2="-7.1501" y2="3.65" layer="51"/>
<rectangle x1="-8.1999" y1="2.8499" x2="-7.1501" y2="3.1501" layer="51"/>
<rectangle x1="-8.1999" y1="2.35" x2="-7.1501" y2="2.65" layer="51"/>
<rectangle x1="-8.1999" y1="1.8499" x2="-7.1501" y2="2.1501" layer="51"/>
<rectangle x1="-8.1999" y1="1.35" x2="-7.1501" y2="1.65" layer="51"/>
<rectangle x1="-8.1999" y1="0.8499" x2="-7.1501" y2="1.1501" layer="51"/>
<rectangle x1="-8.1999" y1="0.35" x2="-7.1501" y2="0.65" layer="51"/>
<rectangle x1="-8.1999" y1="-0.1501" x2="-7.1501" y2="0.1501" layer="51"/>
<rectangle x1="-8.1999" y1="-0.65" x2="-7.1501" y2="-0.35" layer="51"/>
<rectangle x1="-8.1999" y1="-1.1501" x2="-7.1501" y2="-0.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-1.65" x2="-7.1501" y2="-1.35" layer="51"/>
<rectangle x1="-8.1999" y1="-2.1501" x2="-7.1501" y2="-1.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-2.65" x2="-7.1501" y2="-2.35" layer="51"/>
<rectangle x1="-8.1999" y1="-3.1501" x2="-7.1501" y2="-2.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-3.65" x2="-7.1501" y2="-3.35" layer="51"/>
<rectangle x1="-8.1999" y1="-4.1501" x2="-7.1501" y2="-3.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-4.65" x2="-7.1501" y2="-4.35" layer="51"/>
<rectangle x1="-8.1999" y1="-5.1501" x2="-7.1501" y2="-4.8499" layer="51"/>
<rectangle x1="-8.1999" y1="-5.65" x2="-7.1501" y2="-5.35" layer="51"/>
<rectangle x1="-8.1999" y1="-6.1501" x2="-7.1501" y2="-5.8499" layer="51"/>
<rectangle x1="-6.1501" y1="-8.1999" x2="-5.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-5.65" y1="-8.1999" x2="-5.35" y2="-7.1501" layer="51"/>
<rectangle x1="-5.1501" y1="-8.1999" x2="-4.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-4.65" y1="-8.1999" x2="-4.35" y2="-7.1501" layer="51"/>
<rectangle x1="-4.1501" y1="-8.1999" x2="-3.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-3.65" y1="-8.1999" x2="-3.35" y2="-7.1501" layer="51"/>
<rectangle x1="-3.1501" y1="-8.1999" x2="-2.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-2.65" y1="-8.1999" x2="-2.35" y2="-7.1501" layer="51"/>
<rectangle x1="-2.1501" y1="-8.1999" x2="-1.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-1.65" y1="-8.1999" x2="-1.35" y2="-7.1501" layer="51"/>
<rectangle x1="-1.1501" y1="-8.1999" x2="-0.8499" y2="-7.1501" layer="51"/>
<rectangle x1="-0.65" y1="-8.1999" x2="-0.35" y2="-7.1501" layer="51"/>
<rectangle x1="-0.1501" y1="-8.1999" x2="0.1501" y2="-7.1501" layer="51"/>
<rectangle x1="0.35" y1="-8.1999" x2="0.65" y2="-7.1501" layer="51"/>
<rectangle x1="0.8499" y1="-8.1999" x2="1.1501" y2="-7.1501" layer="51"/>
<rectangle x1="1.35" y1="-8.1999" x2="1.65" y2="-7.1501" layer="51"/>
<rectangle x1="1.8499" y1="-8.1999" x2="2.1501" y2="-7.1501" layer="51"/>
<rectangle x1="2.35" y1="-8.1999" x2="2.65" y2="-7.1501" layer="51"/>
<rectangle x1="2.8499" y1="-8.1999" x2="3.1501" y2="-7.1501" layer="51"/>
<rectangle x1="3.35" y1="-8.1999" x2="3.65" y2="-7.1501" layer="51"/>
<rectangle x1="3.8499" y1="-8.1999" x2="4.1501" y2="-7.1501" layer="51"/>
<rectangle x1="4.35" y1="-8.1999" x2="4.65" y2="-7.1501" layer="51"/>
<rectangle x1="4.8499" y1="-8.1999" x2="5.1501" y2="-7.1501" layer="51"/>
<rectangle x1="5.35" y1="-8.1999" x2="5.65" y2="-7.1501" layer="51"/>
<rectangle x1="5.8499" y1="-8.1999" x2="6.1501" y2="-7.1501" layer="51"/>
<rectangle x1="7.1501" y1="-6.1501" x2="8.1999" y2="-5.8499" layer="51"/>
<rectangle x1="7.1501" y1="-5.65" x2="8.1999" y2="-5.35" layer="51"/>
<rectangle x1="7.1501" y1="-5.1501" x2="8.1999" y2="-4.8499" layer="51"/>
<rectangle x1="7.1501" y1="-4.65" x2="8.1999" y2="-4.35" layer="51"/>
<rectangle x1="7.1501" y1="-4.1501" x2="8.1999" y2="-3.8499" layer="51"/>
<rectangle x1="7.1501" y1="-3.65" x2="8.1999" y2="-3.35" layer="51"/>
<rectangle x1="7.1501" y1="-3.1501" x2="8.1999" y2="-2.8499" layer="51"/>
<rectangle x1="7.1501" y1="-2.65" x2="8.1999" y2="-2.35" layer="51"/>
<rectangle x1="7.1501" y1="-2.1501" x2="8.1999" y2="-1.8499" layer="51"/>
<rectangle x1="7.1501" y1="-1.65" x2="8.1999" y2="-1.35" layer="51"/>
<rectangle x1="7.1501" y1="-1.1501" x2="8.1999" y2="-0.8499" layer="51"/>
<rectangle x1="7.1501" y1="-0.65" x2="8.1999" y2="-0.35" layer="51"/>
<rectangle x1="7.1501" y1="-0.1501" x2="8.1999" y2="0.1501" layer="51"/>
<rectangle x1="7.1501" y1="0.35" x2="8.1999" y2="0.65" layer="51"/>
<rectangle x1="7.1501" y1="0.8499" x2="8.1999" y2="1.1501" layer="51"/>
<rectangle x1="7.1501" y1="1.35" x2="8.1999" y2="1.65" layer="51"/>
<rectangle x1="7.1501" y1="1.8499" x2="8.1999" y2="2.1501" layer="51"/>
<rectangle x1="7.1501" y1="2.35" x2="8.1999" y2="2.65" layer="51"/>
<rectangle x1="7.1501" y1="2.8499" x2="8.1999" y2="3.1501" layer="51"/>
<rectangle x1="7.1501" y1="3.35" x2="8.1999" y2="3.65" layer="51"/>
<rectangle x1="7.1501" y1="3.8499" x2="8.1999" y2="4.1501" layer="51"/>
<rectangle x1="7.1501" y1="4.35" x2="8.1999" y2="4.65" layer="51"/>
<rectangle x1="7.1501" y1="4.8499" x2="8.1999" y2="5.1501" layer="51"/>
<rectangle x1="7.1501" y1="5.35" x2="8.1999" y2="5.65" layer="51"/>
<rectangle x1="7.1501" y1="5.8499" x2="8.1999" y2="6.1501" layer="51"/>
<rectangle x1="5.8499" y1="7.1501" x2="6.1501" y2="8.1999" layer="51"/>
<rectangle x1="5.35" y1="7.1501" x2="5.65" y2="8.1999" layer="51"/>
<rectangle x1="4.8499" y1="7.1501" x2="5.1501" y2="8.1999" layer="51"/>
<rectangle x1="4.35" y1="7.1501" x2="4.65" y2="8.1999" layer="51"/>
<rectangle x1="3.8499" y1="7.1501" x2="4.1501" y2="8.1999" layer="51"/>
<rectangle x1="3.35" y1="7.1501" x2="3.65" y2="8.1999" layer="51"/>
<rectangle x1="2.8499" y1="7.1501" x2="3.1501" y2="8.1999" layer="51"/>
<rectangle x1="2.35" y1="7.1501" x2="2.65" y2="8.1999" layer="51"/>
<rectangle x1="1.8499" y1="7.1501" x2="2.1501" y2="8.1999" layer="51"/>
<rectangle x1="1.35" y1="7.1501" x2="1.65" y2="8.1999" layer="51"/>
<rectangle x1="0.8499" y1="7.1501" x2="1.1501" y2="8.1999" layer="51"/>
<rectangle x1="0.35" y1="7.1501" x2="0.65" y2="8.1999" layer="51"/>
<rectangle x1="-0.1501" y1="7.1501" x2="0.1501" y2="8.1999" layer="51"/>
<rectangle x1="-0.65" y1="7.1501" x2="-0.35" y2="8.1999" layer="51"/>
<rectangle x1="-1.1501" y1="7.1501" x2="-0.8499" y2="8.1999" layer="51"/>
<rectangle x1="-1.65" y1="7.1501" x2="-1.35" y2="8.1999" layer="51"/>
<rectangle x1="-2.1501" y1="7.1501" x2="-1.8499" y2="8.1999" layer="51"/>
<rectangle x1="-2.65" y1="7.1501" x2="-2.35" y2="8.1999" layer="51"/>
<rectangle x1="-3.1501" y1="7.1501" x2="-2.8499" y2="8.1999" layer="51"/>
<rectangle x1="-3.65" y1="7.1501" x2="-3.35" y2="8.1999" layer="51"/>
<rectangle x1="-4.1501" y1="7.1501" x2="-3.8499" y2="8.1999" layer="51"/>
<rectangle x1="-4.65" y1="7.1501" x2="-4.35" y2="8.1999" layer="51"/>
<rectangle x1="-5.1501" y1="7.1501" x2="-4.8499" y2="8.1999" layer="51"/>
<rectangle x1="-5.65" y1="7.1501" x2="-5.35" y2="8.1999" layer="51"/>
<rectangle x1="-6.1501" y1="7.1501" x2="-5.8499" y2="8.1999" layer="51"/>
</package>
<package name="R1206">
<wire x1="-2.1" y1="1.1" x2="2.1" y2="1.1" width="0.0508" layer="39"/>
<wire x1="2.1" y1="-1.1" x2="-2.1" y2="-1.1" width="0.0508" layer="39"/>
<wire x1="-2.1" y1="-1.1" x2="-2.1" y2="1.1" width="0.0508" layer="39"/>
<wire x1="2.1" y1="1.1" x2="2.1" y2="-1.1" width="0.0508" layer="39"/>
<wire x1="-0.7" y1="0.725" x2="0.7" y2="0.725" width="0.2032" layer="21"/>
<wire x1="-0.7" y1="-0.725" x2="0.7" y2="-0.725" width="0.2032" layer="21"/>
<wire x1="-1.35" y1="0.725" x2="1.35" y2="0.725" width="0.127" layer="51"/>
<wire x1="-1.325" y1="-0.725" x2="1.35" y2="-0.725" width="0.127" layer="51"/>
<smd name="1" x="-1.45" y="0" dx="0.9" dy="1.6" layer="1"/>
<smd name="2" x="1.45" y="0" dx="0.9" dy="1.6" layer="1"/>
<text x="-1.07" y="1.143" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.197" y="-1.524" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-1.475" y1="-0.8" x2="-1" y2="0.8" layer="51"/>
<rectangle x1="1" y1="-0.8" x2="1.475" y2="0.8" layer="51"/>
</package>
<package name="R0805">
<wire x1="-0.4" y1="0.575" x2="0.3" y2="0.575" width="0.2032" layer="21"/>
<wire x1="-0.4" y1="-0.575" x2="0.3" y2="-0.575" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="-0.95" x2="1.4" y2="-0.95" width="0.05" layer="39"/>
<wire x1="1.4" y1="-0.95" x2="1.4" y2="0.95" width="0.05" layer="39"/>
<wire x1="1.4" y1="0.95" x2="-1.5" y2="0.95" width="0.05" layer="39"/>
<wire x1="-1.5" y1="0.95" x2="-1.5" y2="-0.95" width="0.05" layer="39"/>
<wire x1="-1" y1="0.575" x2="0.9" y2="0.575" width="0.127" layer="51"/>
<wire x1="-1" y1="-0.575" x2="0.9" y2="-0.575" width="0.127" layer="51"/>
<smd name="1" x="-1" y="0" dx="0.7" dy="1.3" layer="1"/>
<smd name="2" x="0.9" y="0" dx="0.7" dy="1.3" layer="1"/>
<text x="-0.762" y="0.9255" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-1.297" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="0.55" y1="-0.65" x2="1" y2="0.65" layer="51"/>
<rectangle x1="-1.1" y1="-0.65" x2="-0.65" y2="0.65" layer="51"/>
</package>
<package name="TO252">
<description>&lt;b&gt;SMALL OUTLINE TRANSISTOR&lt;/b&gt;&lt;p&gt;
TS-003</description>
<wire x1="3.2766" y1="3.8354" x2="3.277" y2="-2.159" width="0.2032" layer="21"/>
<wire x1="3.277" y1="-2.159" x2="-3.277" y2="-2.159" width="0.2032" layer="21"/>
<wire x1="-3.277" y1="-2.159" x2="-3.2766" y2="3.8354" width="0.2032" layer="21"/>
<wire x1="-3.277" y1="3.835" x2="3.2774" y2="3.8346" width="0.2032" layer="51"/>
<wire x1="-2.5654" y1="3.937" x2="-2.5654" y2="4.6482" width="0.2032" layer="51"/>
<wire x1="-2.5654" y1="4.6482" x2="-2.1082" y2="5.1054" width="0.2032" layer="51"/>
<wire x1="-2.1082" y1="5.1054" x2="2.1082" y2="5.1054" width="0.2032" layer="51"/>
<wire x1="2.1082" y1="5.1054" x2="2.5654" y2="4.6482" width="0.2032" layer="51"/>
<wire x1="2.5654" y1="4.6482" x2="2.5654" y2="3.937" width="0.2032" layer="51"/>
<wire x1="2.5654" y1="3.937" x2="-2.5654" y2="3.937" width="0.2032" layer="51"/>
<smd name="3" x="0" y="2.5" dx="5.4" dy="6.2" layer="1"/>
<smd name="1" x="-2.28" y="-4.8" dx="1" dy="1.6" layer="1"/>
<smd name="2" x="2.28" y="-4.8" dx="1" dy="1.6" layer="1"/>
<text x="-3.81" y="-2.54" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="5.08" y="-2.54" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-2.7178" y1="-5.1562" x2="-1.8542" y2="-2.2606" layer="51"/>
<rectangle x1="1.8542" y1="-5.1562" x2="2.7178" y2="-2.2606" layer="51"/>
<rectangle x1="-0.4318" y1="-3.0226" x2="0.4318" y2="-2.2606" layer="21"/>
<polygon width="0.1998" layer="51">
<vertex x="-2.5654" y="3.937"/>
<vertex x="-2.5654" y="4.6482"/>
<vertex x="-2.1082" y="5.1054"/>
<vertex x="2.1082" y="5.1054"/>
<vertex x="2.5654" y="4.6482"/>
<vertex x="2.5654" y="3.937"/>
</polygon>
</package>
<package name="ADIS16480">
<hole x="0" y="0" drill="2.8"/>
<hole x="0" y="42.6" drill="2.8"/>
<hole x="39.6" y="42.6" drill="2.8"/>
<hole x="39.6" y="0" drill="2.8"/>
<hole x="14.8" y="1.642" drill="0.6"/>
<hole x="24.8" y="1.642" drill="0.6"/>
<smd name="24" x="14.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="22" x="15.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="20" x="16.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="18" x="17.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="16" x="18.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="14" x="19.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="12" x="20.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="10" x="21.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="8" x="22.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="6" x="23.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="4" x="24.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="3" x="24.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="5" x="23.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="7" x="22.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="9" x="21.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="11" x="20.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="13" x="19.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="15" x="18.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="17" x="17.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="19" x="16.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="21" x="15.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="23" x="14.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<text x="26.47" y="-0.365" size="1.016" layer="21">1</text>
<text x="26.47" y="2.865" size="1.016" layer="21">2</text>
<text x="11.895" y="2.865" size="1.016" layer="21">24</text>
<text x="11.895" y="-0.365" size="1.016" layer="21">23</text>
<wire x1="-2.25" y1="-2.25" x2="-2.25" y2="44.75" width="0.6096" layer="21" style="longdash"/>
<wire x1="-2.25" y1="44.75" x2="41.75" y2="44.75" width="0.6096" layer="21" style="longdash"/>
<wire x1="41.75" y1="44.75" x2="41.75" y2="-2.25" width="0.6096" layer="21" style="longdash"/>
<wire x1="41.75" y1="-2.25" x2="-2.25" y2="-2.25" width="0.6096" layer="21" style="longdash"/>
<smd name="2" x="25.3" y="3.25" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<smd name="1" x="25.3" y="0.05" dx="1.37" dy="0.61" layer="1" rot="R90"/>
<wire x1="-2.25" y1="-2.25" x2="-2.25" y2="44.75" width="0.127" layer="51"/>
<wire x1="-2.25" y1="44.75" x2="41.75" y2="44.75" width="0.127" layer="51"/>
<wire x1="41.75" y1="44.75" x2="41.75" y2="-2.25" width="0.127" layer="51"/>
<wire x1="41.75" y1="-2.25" x2="29.5" y2="-2.25" width="0.127" layer="51"/>
<wire x1="29.5" y1="-2.25" x2="10.25" y2="-2.25" width="0.127" layer="51"/>
<wire x1="-2.25" y1="-2.25" x2="10.25" y2="-2.25" width="0.127" layer="51"/>
<wire x1="10.25" y1="-2.25" x2="10.25" y2="7" width="0.127" layer="51"/>
<wire x1="10.25" y1="7" x2="29.5" y2="7" width="0.127" layer="51"/>
<wire x1="29.5" y1="7" x2="29.5" y2="-2.25" width="0.127" layer="51"/>
<text x="15" y="-4.8" size="1.016" layer="21">&gt;NAME</text>
<text x="15.5" y="24.75" size="1.016" layer="21">&gt;VALUE</text>
<circle x="0" y="42.6" radius="2.690721875" width="0.127" layer="40"/>
<circle x="39.6" y="42.6" radius="2.690721875" width="0.127" layer="40"/>
<circle x="39.6" y="0" radius="2.690721875" width="0.127" layer="40"/>
<circle x="0" y="0" radius="2.690721875" width="0.127" layer="40"/>
</package>
<package name="TO92">
<description>&lt;b&gt;TO-92&lt;/b&gt;</description>
<wire x1="-2.1" y1="-1.6" x2="2.1" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.1" y1="-1.6" x2="-1.4" y2="2.3" width="0.2032" layer="21" curve="-98.057233"/>
<wire x1="2.1" y1="-1.6" x2="1.4" y2="2.3" width="0.2032" layer="21" curve="99.798366"/>
<wire x1="-1.4" y1="2.3" x2="1.4" y2="2.3" width="0.2032" layer="51" curve="-63.781584"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="0" y="1.905" drill="0.8128" shape="octagon"/>
<pad name="3" x="1.27" y="0" drill="0.8128" shape="octagon"/>
<text x="2.413" y="1.651" size="1.27" layer="25" ratio="18">&gt;NAME</text>
<text x="2.921" y="-1.27" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="QFN-24-NP">
<wire x1="1.65" y1="-2" x2="2" y2="-2" width="0.2032" layer="21"/>
<wire x1="2" y1="-1.65" x2="2" y2="-2" width="0.2032" layer="21"/>
<wire x1="-1.65" y1="-2" x2="-2" y2="-2" width="0.2032" layer="21"/>
<wire x1="-2" y1="-2" x2="-2" y2="-1.65" width="0.2032" layer="21"/>
<wire x1="2" y1="1.65" x2="2" y2="2" width="0.2032" layer="21"/>
<wire x1="2" y1="2" x2="1.65" y2="2" width="0.2032" layer="21"/>
<wire x1="-1.65" y1="2" x2="-2" y2="1.65" width="0.2032" layer="21"/>
<wire x1="-1.016" y1="0.508" x2="-1.016" y2="-0.889" width="0.0762" layer="51"/>
<wire x1="-1.016" y1="-0.889" x2="1.016" y2="-0.889" width="0.0762" layer="51"/>
<wire x1="1.143" y1="1.143" x2="0.635" y2="1.143" width="0.0762" layer="51" curve="-270"/>
<wire x1="1.143" y1="1.143" x2="1.0668" y2="0.9144" width="0.0762" layer="51"/>
<wire x1="1.143" y1="1.143" x2="1.397" y2="1.0414" width="0.0762" layer="51"/>
<wire x1="-0.7874" y1="-0.3048" x2="-0.7874" y2="0.0762" width="0.0762" layer="51" curve="-280.388858"/>
<wire x1="-0.7874" y1="0.2794" x2="-0.7874" y2="0.0762" width="0.0762" layer="51"/>
<wire x1="-0.7874" y1="0.0762" x2="-0.889" y2="-0.0254" width="0.0762" layer="51"/>
<wire x1="0.5334" y1="-1.1176" x2="0.508" y2="-0.635" width="0.0762" layer="51" curve="-248.760689"/>
<wire x1="0.381" y1="-1.016" x2="0.5334" y2="-1.1176" width="0.0762" layer="51"/>
<wire x1="0.5334" y1="-1.1176" x2="0.4826" y2="-1.2954" width="0.0762" layer="51"/>
<smd name="1" x="-2" y="1.25" dx="0.8" dy="0.3" layer="1" rot="R180"/>
<smd name="2" x="-2" y="0.75" dx="0.8" dy="0.3" layer="1" rot="R180"/>
<smd name="3" x="-2" y="0.25" dx="0.8" dy="0.3" layer="1" rot="R180"/>
<smd name="4" x="-2" y="-0.25" dx="0.8" dy="0.3" layer="1" rot="R180"/>
<smd name="5" x="-2" y="-0.75" dx="0.8" dy="0.3" layer="1" rot="R180"/>
<smd name="6" x="-2" y="-1.25" dx="0.8" dy="0.3" layer="1" rot="R180"/>
<smd name="7" x="-1.25" y="-2" dx="0.8" dy="0.3" layer="1" rot="R90"/>
<smd name="8" x="-0.75" y="-2" dx="0.8" dy="0.3" layer="1" rot="R90"/>
<smd name="9" x="-0.25" y="-2" dx="0.8" dy="0.3" layer="1" rot="R90"/>
<smd name="10" x="0.25" y="-2" dx="0.8" dy="0.3" layer="1" rot="R90"/>
<smd name="11" x="0.75" y="-2" dx="0.8" dy="0.3" layer="1" rot="R90"/>
<smd name="12" x="1.25" y="-2" dx="0.8" dy="0.3" layer="1" rot="R90"/>
<smd name="13" x="2" y="-1.25" dx="0.8" dy="0.3" layer="1"/>
<smd name="14" x="2" y="-0.75" dx="0.8" dy="0.3" layer="1"/>
<smd name="15" x="2" y="-0.25" dx="0.8" dy="0.3" layer="1"/>
<smd name="16" x="2" y="0.25" dx="0.8" dy="0.3" layer="1"/>
<smd name="17" x="2" y="0.75" dx="0.8" dy="0.3" layer="1"/>
<smd name="18" x="2" y="1.25" dx="0.8" dy="0.3" layer="1"/>
<smd name="19" x="1.25" y="2" dx="0.8" dy="0.3" layer="1" rot="R270"/>
<smd name="20" x="0.75" y="2" dx="0.8" dy="0.3" layer="1" rot="R270"/>
<smd name="21" x="0.25" y="2" dx="0.8" dy="0.3" layer="1" rot="R270"/>
<smd name="22" x="-0.25" y="2" dx="0.8" dy="0.3" layer="1" rot="R270"/>
<smd name="23" x="-0.75" y="2" dx="0.8" dy="0.3" layer="1" rot="R270"/>
<smd name="24" x="-1.25" y="2" dx="0.8" dy="0.3" layer="1" rot="R270"/>
<text x="-2.45" y="2.8" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.5" y="-4.15" size="1.27" layer="27">&gt;VALUE</text>
<text x="1.1176" y="-1.1938" size="0.4064" layer="51">X</text>
<text x="-1.2192" y="0.6604" size="0.4064" layer="51">Y</text>
<text x="0" y="0.8636" size="0.4064" layer="51">Z</text>
</package>
<package name="LGA14">
<wire x1="2.5" y1="1.5" x2="-2.5" y2="1.5" width="0.127" layer="51"/>
<wire x1="-2.5" y1="1.5" x2="-2.5" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-2.5" y1="-1.5" x2="2.5" y2="-1.5" width="0.127" layer="51"/>
<wire x1="2.5" y1="-1.5" x2="2.5" y2="1.5" width="0.127" layer="51"/>
<wire x1="2.5" y1="1.5" x2="2.5" y2="0.7" width="0.2032" layer="21"/>
<wire x1="2.5" y1="-0.7" x2="2.5" y2="-1.5" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="-1.5" x2="-2.5" y2="-0.7" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="0.7" x2="-2.5" y2="1.5" width="0.2032" layer="21"/>
<wire x1="0.254" y1="-0.127" x2="0.508" y2="-0.127" width="0.0508" layer="51"/>
<wire x1="0.508" y1="-0.127" x2="0.381" y2="0" width="0.0508" layer="51"/>
<wire x1="0.508" y1="-0.127" x2="0.381" y2="-0.254" width="0.0508" layer="51"/>
<wire x1="-0.381" y1="0.127" x2="-0.381" y2="0.381" width="0.0508" layer="51"/>
<wire x1="-0.381" y1="0.381" x2="-0.508" y2="0.254" width="0.0508" layer="51"/>
<wire x1="-0.381" y1="0.381" x2="-0.254" y2="0.254" width="0.0508" layer="51"/>
<circle x="1" y="0" radius="0.1" width="0.2032" layer="21"/>
<circle x="0.254" y="0.254" radius="0.127" width="0.0508" layer="51"/>
<circle x="0.254" y="0.254" radius="0.0254" width="0.0508" layer="51"/>
<smd name="6" x="-2" y="1.1" dx="0.5" dy="1.2" layer="1" rot="R180"/>
<smd name="5" x="-1.2" y="1.1" dx="0.5" dy="1.2" layer="1" rot="R180"/>
<smd name="4" x="-0.4" y="1.1" dx="0.5" dy="1.2" layer="1" rot="R180"/>
<smd name="3" x="0.4" y="1.1" dx="0.5" dy="1.2" layer="1" rot="R180"/>
<smd name="2" x="1.2" y="1.1" dx="0.5" dy="1.2" layer="1" rot="R180"/>
<smd name="1" x="2" y="1.1" dx="0.5" dy="1.2" layer="1"/>
<smd name="14" x="2.1" y="0" dx="0.5" dy="1.2" layer="1" rot="R90"/>
<smd name="13" x="2" y="-1.1" dx="0.5" dy="1.2" layer="1"/>
<smd name="12" x="1.2" y="-1.1" dx="0.5" dy="1.2" layer="1"/>
<smd name="11" x="0.4" y="-1.1" dx="0.5" dy="1.2" layer="1"/>
<smd name="10" x="-0.4" y="-1.1" dx="0.5" dy="1.2" layer="1"/>
<smd name="9" x="-1.2" y="-1.1" dx="0.5" dy="1.2" layer="1" rot="R180"/>
<smd name="8" x="-2" y="-1.1" dx="0.5" dy="1.2" layer="1" rot="R180"/>
<smd name="7" x="-2.1" y="0" dx="0.5" dy="1.2" layer="1" rot="R270"/>
<text x="-2.032" y="2.159" size="0.4064" layer="25">&gt;Name</text>
<text x="-2.032" y="-2.413" size="0.4064" layer="27">&gt;Value</text>
<text x="-0.127" y="-0.254" size="0.3048" layer="51" ratio="15">X</text>
<text x="-0.508" y="-0.254" size="0.3048" layer="51" ratio="15">Y</text>
<text x="-0.127" y="0.127" size="0.3048" layer="51" ratio="15">Z</text>
</package>
<package name="MSOP10">
<wire x1="-1.48" y1="1.23" x2="-1.23" y2="1.48" width="0.1524" layer="21" curve="-90" cap="flat"/>
<wire x1="1.23" y1="1.48" x2="1.48" y2="1.23" width="0.1524" layer="21" curve="-90"/>
<wire x1="1.23" y1="-1.49" x2="1.48" y2="-1.24" width="0.1524" layer="21" curve="90"/>
<wire x1="-1.48" y1="-1.24" x2="-1.23" y2="-1.49" width="0.1524" layer="21" curve="90" cap="flat"/>
<wire x1="1.24" y1="-1.49" x2="-1.22" y2="-1.49" width="0.1524" layer="21"/>
<wire x1="-1.22" y1="1.48" x2="1.24" y2="1.48" width="0.1524" layer="21"/>
<wire x1="-1.48" y1="1.23" x2="-1.48" y2="-1.23" width="0.1524" layer="21"/>
<wire x1="1.48" y1="-1.24" x2="1.48" y2="1.23" width="0.1524" layer="21"/>
<circle x="-0.7" y="-0.65" radius="0.325" width="0.254" layer="21"/>
<smd name="1" x="-1" y="-2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<smd name="2" x="-0.5" y="-2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<smd name="3" x="0" y="-2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<smd name="4" x="0.5" y="-2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<smd name="5" x="1" y="-2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<smd name="6" x="1" y="2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<smd name="7" x="0.5" y="2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<smd name="8" x="0" y="2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<text x="-1.84" y="-0.97" size="0.4064" layer="25" rot="R90">&gt;NAME</text>
<text x="2.14" y="-1.17" size="0.4064" layer="27" rot="R90">&gt;VALUE</text>
<smd name="9" x="-0.5" y="2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<smd name="10" x="-1" y="2.25" dx="1.1" dy="0.3" layer="1" rot="R90"/>
<rectangle x1="-0.65" y1="-2.5" x2="-0.35" y2="-1.5" layer="51"/>
<rectangle x1="-0.15" y1="-2.5" x2="0.15" y2="-1.5" layer="51"/>
<rectangle x1="0.35" y1="-2.5" x2="0.65" y2="-1.5" layer="51"/>
<rectangle x1="0.85" y1="-2.5" x2="1.15" y2="-1.5" layer="51"/>
<rectangle x1="0.85" y1="1.5" x2="1.15" y2="2.5" layer="51"/>
<rectangle x1="0.35" y1="1.5" x2="0.65" y2="2.5" layer="51"/>
<rectangle x1="-0.15" y1="1.5" x2="0.15" y2="2.5" layer="51"/>
<rectangle x1="-0.65" y1="1.5" x2="-0.35" y2="2.5" layer="51"/>
<rectangle x1="-1.15" y1="1.5" x2="-0.85" y2="2.5" layer="51"/>
<rectangle x1="-1.15" y1="-2.5" x2="-0.85" y2="-1.5" layer="51"/>
</package>
<package name="SOT23-3">
<wire x1="1.4224" y1="0.6604" x2="1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="1.4224" y1="-0.6604" x2="-1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="-0.6604" x2="-1.4224" y2="0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="0.6604" x2="1.4224" y2="0.6604" width="0.1524" layer="51"/>
<wire x1="-0.8" y1="0.7" x2="-1.4" y2="0.7" width="0.2032" layer="21"/>
<wire x1="-1.4" y1="0.7" x2="-1.4" y2="-0.1" width="0.2032" layer="21"/>
<wire x1="0.8" y1="0.7" x2="1.4" y2="0.7" width="0.2032" layer="21"/>
<wire x1="1.4" y1="0.7" x2="1.4" y2="-0.1" width="0.2032" layer="21"/>
<smd name="3" x="0" y="1.1" dx="0.8" dy="0.9" layer="1"/>
<smd name="2" x="0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<smd name="1" x="-0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<text x="-0.8255" y="1.778" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-0.1905" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="AVR_ICSP">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-1.905" y1="6.35" x2="-2.54" y2="5.715" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="4.445" x2="-1.905" y2="3.81" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="3.81" x2="-2.54" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="1.905" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-3.175" x2="-1.905" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="6.35" x2="1.905" y2="6.35" width="0.1524" layer="21"/>
<wire x1="1.905" y1="6.35" x2="2.54" y2="5.715" width="0.1524" layer="21"/>
<wire x1="2.54" y1="5.715" x2="2.54" y2="4.445" width="0.1524" layer="21"/>
<wire x1="2.54" y1="4.445" x2="1.905" y2="3.81" width="0.1524" layer="21"/>
<wire x1="1.905" y1="3.81" x2="2.54" y2="3.175" width="0.1524" layer="21"/>
<wire x1="2.54" y1="3.175" x2="2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="1.905" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-3.175" x2="1.905" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="1.905" y1="3.81" x2="-1.905" y2="3.81" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-3.81" x2="-1.905" y2="-3.81" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="3.175" x2="-2.54" y2="1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="5.715" x2="-2.54" y2="4.445" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-3.81" x2="-2.54" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-5.715" x2="-1.905" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-3.81" x2="2.54" y2="-4.445" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-4.445" x2="2.54" y2="-5.715" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-5.715" x2="1.905" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-6.35" x2="-1.905" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-4.445" x2="-2.54" y2="-5.715" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="5.715" x2="-3.175" y2="4.445" width="0.2032" layer="21"/>
<pad name="1" x="-1.27" y="5.08" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="2" x="1.27" y="5.08" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="3" x="-1.27" y="2.54" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="4" x="1.27" y="2.54" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="5" x="-1.27" y="0" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="6" x="1.27" y="0" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="7" x="-1.27" y="-2.54" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="8" x="1.27" y="-2.54" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="9" x="-1.27" y="-5.08" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<pad name="10" x="1.27" y="-5.08" drill="1.016" diameter="1.8796" shape="octagon" rot="R270"/>
<text x="-2.794" y="-3.302" size="0.4064" layer="25" rot="R90">&gt;NAME</text>
<text x="-2.794" y="-0.254" size="0.4064" layer="27" font="vector" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.524" y1="4.826" x2="-1.016" y2="5.334" layer="51"/>
<rectangle x1="1.016" y1="4.826" x2="1.524" y2="5.334" layer="51"/>
<rectangle x1="1.016" y1="2.286" x2="1.524" y2="2.794" layer="51"/>
<rectangle x1="-1.524" y1="2.286" x2="-1.016" y2="2.794" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="21"/>
<rectangle x1="1.016" y1="-5.334" x2="1.524" y2="-4.826" layer="51"/>
<rectangle x1="-1.524" y1="-5.334" x2="-1.016" y2="-4.826" layer="51"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51"/>
</package>
<package name="2X5-RA">
<wire x1="-3.175" y1="5.715" x2="-3.175" y2="4.445" width="0.2032" layer="21"/>
<wire x1="2.8" y1="6.3" x2="5.3" y2="6.3" width="0.2032" layer="21"/>
<wire x1="5.3" y1="6.3" x2="5.3" y2="-6.3" width="0.2032" layer="21"/>
<wire x1="5.3" y1="-6.3" x2="2.8" y2="-6.3" width="0.2032" layer="21"/>
<wire x1="2.8" y1="-6.3" x2="2.8" y2="6.3" width="0.2032" layer="21"/>
<wire x1="5.3" y1="0" x2="11.3" y2="0" width="0.127" layer="51"/>
<wire x1="5.3" y1="-2.54" x2="11.3" y2="-2.54" width="0.127" layer="51"/>
<wire x1="5.3" y1="-5.08" x2="11.3" y2="-5.08" width="0.127" layer="51"/>
<wire x1="5.3" y1="2.54" x2="11.3" y2="2.54" width="0.127" layer="51"/>
<wire x1="5.3" y1="5.08" x2="11.3" y2="5.08" width="0.127" layer="51"/>
<wire x1="8.2" y1="7" x2="8.2" y2="-6.9" width="0.127" layer="51"/>
<wire x1="13.8" y1="6.3" x2="13.8" y2="-6.3" width="0.127" layer="51"/>
<wire x1="5.3" y1="6.3" x2="13.8" y2="6.3" width="0.127" layer="51"/>
<wire x1="5.3" y1="-6.3" x2="13.8" y2="-6.3" width="0.127" layer="51"/>
<pad name="1" x="-1.27" y="5.08" drill="1" shape="octagon" rot="R270"/>
<pad name="2" x="1.27" y="5.08" drill="1" rot="R270"/>
<pad name="3" x="-1.27" y="2.54" drill="1" rot="R270"/>
<pad name="4" x="1.27" y="2.54" drill="1" rot="R270"/>
<pad name="5" x="-1.27" y="0" drill="1" rot="R270"/>
<pad name="6" x="1.27" y="0" drill="1" rot="R270"/>
<pad name="7" x="-1.27" y="-2.54" drill="1" rot="R270"/>
<pad name="8" x="1.27" y="-2.54" drill="1" rot="R270"/>
<pad name="9" x="-1.27" y="-5.08" drill="1" rot="R270"/>
<pad name="10" x="1.27" y="-5.08" drill="1" rot="R270"/>
<text x="-2" y="-8.2" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.9" y="7" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-1.524" y1="4.826" x2="-1.016" y2="5.334" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="4.826" x2="1.524" y2="5.334" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="2.286" x2="1.524" y2="2.794" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="2.286" x2="-1.016" y2="2.794" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-5.334" x2="1.524" y2="-4.826" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-5.334" x2="-1.016" y2="-4.826" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51" rot="R270"/>
</package>
<package name="2X5-RAF">
<wire x1="-3.175" y1="5.715" x2="-3.175" y2="4.445" width="0.2032" layer="21"/>
<wire x1="2.7" y1="6.3" x2="11.2" y2="6.3" width="0.2032" layer="21"/>
<wire x1="11.2" y1="6.3" x2="11.2" y2="-6.3" width="0.2032" layer="21"/>
<wire x1="11.2" y1="-6.3" x2="2.7" y2="-6.3" width="0.2032" layer="21"/>
<wire x1="2.7" y1="-6.3" x2="2.7" y2="6.3" width="0.2032" layer="21"/>
<wire x1="8.2" y1="7" x2="8.2" y2="-6.9" width="0.127" layer="51"/>
<pad name="1" x="-1.27" y="5.08" drill="1" shape="octagon" rot="R270"/>
<pad name="2" x="1.27" y="5.08" drill="1" rot="R270"/>
<pad name="3" x="-1.27" y="2.54" drill="1" rot="R270"/>
<pad name="4" x="1.27" y="2.54" drill="1" rot="R270"/>
<pad name="5" x="-1.27" y="0" drill="1" rot="R270"/>
<pad name="6" x="1.27" y="0" drill="1" rot="R270"/>
<pad name="7" x="-1.27" y="-2.54" drill="1" rot="R270"/>
<pad name="8" x="1.27" y="-2.54" drill="1" rot="R270"/>
<pad name="9" x="-1.27" y="-5.08" drill="1" rot="R270"/>
<pad name="10" x="1.27" y="-5.08" drill="1" rot="R270"/>
<text x="-2" y="-8.2" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.9" y="7" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-1.524" y1="4.826" x2="-1.016" y2="5.334" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="4.826" x2="1.524" y2="5.334" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="2.286" x2="1.524" y2="2.794" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="2.286" x2="-1.016" y2="2.794" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-5.334" x2="1.524" y2="-4.826" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-5.334" x2="-1.016" y2="-4.826" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51" rot="R270"/>
</package>
<package name="2X5-SHROUDED">
<wire x1="-2.775" y1="5.715" x2="-2.775" y2="4.445" width="0.2032" layer="21"/>
<wire x1="4.5" y1="10.1" x2="4.5" y2="-10.1" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="-10.1" x2="-4.5" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="-2.2" x2="-4.5" y2="2.2" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="2.2" x2="-4.5" y2="10.1" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="10.1" x2="4.4" y2="10.1" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-10.1" x2="-4.5" y2="-10.1" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="9" x2="3.4" y2="9" width="0.2032" layer="51"/>
<wire x1="3.4" y1="9" x2="3.4" y2="-9" width="0.2032" layer="51"/>
<wire x1="-3.4" y1="-9" x2="3.4" y2="-9" width="0.2032" layer="51"/>
<wire x1="-4.5" y1="2.2" x2="-3" y2="2.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="2.2" x2="-3" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="-2.2" x2="-4.5" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="9" x2="-3.4" y2="2.2" width="0.2032" layer="51"/>
<wire x1="-3.4" y1="-9" x2="-3.4" y2="-2.2" width="0.2032" layer="51"/>
<pad name="1" x="-1.27" y="5.08" drill="1" shape="octagon" rot="R270"/>
<pad name="2" x="1.27" y="5.08" drill="1" rot="R270"/>
<pad name="3" x="-1.27" y="2.54" drill="1" rot="R270"/>
<pad name="4" x="1.27" y="2.54" drill="1" rot="R270"/>
<pad name="5" x="-1.27" y="0" drill="1" rot="R270"/>
<pad name="6" x="1.27" y="0" drill="1" rot="R270"/>
<pad name="7" x="-1.27" y="-2.54" drill="1" rot="R270"/>
<pad name="8" x="1.27" y="-2.54" drill="1" rot="R270"/>
<pad name="9" x="-1.27" y="-5.08" drill="1" rot="R270"/>
<pad name="10" x="1.27" y="-5.08" drill="1" rot="R270"/>
<text x="-2.921" y="10.414" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<text x="-2.921" y="-10.922" size="0.4064" layer="104">&gt;NAME</text>
<rectangle x1="-1.524" y1="4.826" x2="-1.016" y2="5.334" layer="51"/>
<rectangle x1="1.016" y1="4.826" x2="1.524" y2="5.334" layer="51"/>
<rectangle x1="1.016" y1="2.286" x2="1.524" y2="2.794" layer="51"/>
<rectangle x1="-1.524" y1="2.286" x2="-1.016" y2="2.794" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51"/>
<rectangle x1="1.016" y1="-5.334" x2="1.524" y2="-4.826" layer="51"/>
<rectangle x1="-1.524" y1="-5.334" x2="-1.016" y2="-4.826" layer="51"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51"/>
</package>
<package name="2X5-SHROUDED_LOCK">
<wire x1="-2.775" y1="5.715" x2="-2.775" y2="4.445" width="0.2032" layer="21"/>
<wire x1="4.5" y1="10.1" x2="4.5" y2="-10.1" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="-10.1" x2="-4.5" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="-2.2" x2="-4.5" y2="2.2" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="2.2" x2="-4.5" y2="10.1" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="10.1" x2="4.4" y2="10.1" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-10.1" x2="-4.5" y2="-10.1" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="9" x2="3.4" y2="9" width="0.2032" layer="51"/>
<wire x1="3.4" y1="9" x2="3.4" y2="-9" width="0.2032" layer="51"/>
<wire x1="-3.4" y1="-9" x2="3.4" y2="-9" width="0.2032" layer="51"/>
<wire x1="-4.5" y1="2.2" x2="-3" y2="2.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="2.2" x2="-3" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="-2.2" x2="-4.5" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="9" x2="-3.4" y2="2.2" width="0.2032" layer="51"/>
<wire x1="-3.4" y1="-9" x2="-3.4" y2="-2.2" width="0.2032" layer="51"/>
<pad name="1" x="-1.397" y="5.08" drill="1" shape="octagon" rot="R270"/>
<pad name="2" x="1.397" y="5.08" drill="1" rot="R270"/>
<pad name="3" x="-1.397" y="2.54" drill="1" rot="R270"/>
<pad name="4" x="1.397" y="2.54" drill="1" rot="R270"/>
<pad name="5" x="-1.397" y="0" drill="1" rot="R270"/>
<pad name="6" x="1.397" y="0" drill="1" rot="R270"/>
<pad name="7" x="-1.397" y="-2.54" drill="1" rot="R270"/>
<pad name="8" x="1.397" y="-2.54" drill="1" rot="R270"/>
<pad name="9" x="-1.397" y="-5.08" drill="1" rot="R270"/>
<pad name="10" x="1.397" y="-5.08" drill="1" rot="R270"/>
<text x="-2.921" y="10.414" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<text x="-2.921" y="-10.922" size="0.4064" layer="104">&gt;NAME</text>
<rectangle x1="-1.524" y1="4.826" x2="-1.016" y2="5.334" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="4.826" x2="1.524" y2="5.334" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="2.286" x2="1.524" y2="2.794" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="2.286" x2="-1.016" y2="2.794" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-5.334" x2="1.524" y2="-4.826" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-5.334" x2="-1.016" y2="-4.826" layer="51" rot="R270"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51" rot="R270"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51" rot="R270"/>
</package>
<package name="2X5-SHROUDED_SMD">
<wire x1="-2.775" y1="5.715" x2="-2.775" y2="4.445" width="0.2032" layer="21"/>
<wire x1="4.5" y1="10.1" x2="4.5" y2="-10.1" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="-10.1" x2="-4.5" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="-2.2" x2="-4.5" y2="2.2" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="2.2" x2="-4.5" y2="10.1" width="0.2032" layer="21"/>
<wire x1="-4.5" y1="10.1" x2="4.4" y2="10.1" width="0.2032" layer="21"/>
<wire x1="4.5" y1="-10.1" x2="-4.5" y2="-10.1" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="9" x2="3.4" y2="9" width="0.2032" layer="51"/>
<wire x1="3.4" y1="9" x2="3.4" y2="-9" width="0.2032" layer="51"/>
<wire x1="-3.4" y1="-9" x2="3.4" y2="-9" width="0.2032" layer="51"/>
<wire x1="-4.5" y1="2.2" x2="-3" y2="2.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="2.2" x2="-3" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-3" y1="-2.2" x2="-4.5" y2="-2.2" width="0.2032" layer="21"/>
<wire x1="-3.4" y1="9" x2="-3.4" y2="2.2" width="0.2032" layer="51"/>
<wire x1="-3.4" y1="-9" x2="-3.4" y2="-2.2" width="0.2032" layer="51"/>
<smd name="1" x="-2.794" y="5.08" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="2" x="2.794" y="5.08" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="3" x="-2.794" y="2.54" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="4" x="2.794" y="2.54" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="5" x="-2.794" y="0" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="6" x="2.794" y="0" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="7" x="-2.794" y="-2.54" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="8" x="2.794" y="-2.54" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="9" x="-2.794" y="-5.08" dx="4.15" dy="1" layer="1" roundness="50"/>
<smd name="10" x="2.794" y="-5.08" dx="4.15" dy="1" layer="1" roundness="50"/>
<text x="-2.921" y="10.414" size="0.4064" layer="27" font="vector">&gt;VALUE</text>
<text x="-2.921" y="-10.922" size="0.4064" layer="104">&gt;NAME</text>
<rectangle x1="-1.524" y1="4.826" x2="-1.016" y2="5.334" layer="51"/>
<rectangle x1="1.016" y1="4.826" x2="1.524" y2="5.334" layer="51"/>
<rectangle x1="1.016" y1="2.286" x2="1.524" y2="2.794" layer="51"/>
<rectangle x1="-1.524" y1="2.286" x2="-1.016" y2="2.794" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51"/>
<rectangle x1="1.016" y1="-5.334" x2="1.524" y2="-4.826" layer="51"/>
<rectangle x1="-1.524" y1="-5.334" x2="-1.016" y2="-4.826" layer="51"/>
<rectangle x1="-1.524" y1="-2.794" x2="-1.016" y2="-2.286" layer="51"/>
<rectangle x1="1.016" y1="-2.794" x2="1.524" y2="-2.286" layer="51"/>
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
<package name="EIA3528-KIT">
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
<package name="EIA3216-KIT">
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
<package name="CAP-IONISTOR-5MM">
<wire x1="-2.5" y1="6" x2="2.5" y2="6" width="0.127" layer="21"/>
<wire x1="2.5" y1="6" x2="2.5" y2="-6" width="0.127" layer="21"/>
<wire x1="2.5" y1="-6" x2="-2.5" y2="-6" width="0.127" layer="21"/>
<wire x1="-2.5" y1="-6" x2="-2.5" y2="6" width="0.127" layer="21"/>
<pad name="1" x="-2.5" y="0" drill="0.7" diameter="1.651"/>
<pad name="2" x="2.5" y="0" drill="0.7" diameter="1.651"/>
<text x="3.23" y="1.738" size="0.4064" layer="25" rot="R90">&gt;Name</text>
<text x="-2.976" y="1.484" size="0.4064" layer="27" rot="R90">&gt;Value</text>
</package>
</packages>
<symbols>
<symbol name="STM32F407V">
<wire x1="-27.94" y1="78.74" x2="-5.08" y2="78.74" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="78.74" x2="7.62" y2="78.74" width="0.1524" layer="94"/>
<wire x1="7.62" y1="78.74" x2="35.56" y2="78.74" width="0.1524" layer="94"/>
<wire x1="35.56" y1="78.74" x2="35.56" y2="-81.28" width="0.1524" layer="94"/>
<wire x1="35.56" y1="-81.28" x2="7.62" y2="-81.28" width="0.1524" layer="94"/>
<wire x1="7.62" y1="-81.28" x2="-5.08" y2="-81.28" width="0.1524" layer="94"/>
<wire x1="-5.08" y1="-81.28" x2="-27.94" y2="-81.28" width="0.1524" layer="94"/>
<wire x1="-27.94" y1="-81.28" x2="-27.94" y2="78.74" width="0.1524" layer="94"/>
<text x="0" y="79.756" size="1.524" layer="95">&gt;NAME</text>
<text x="-2.794" y="-84.582" size="1.524" layer="95">&gt;VALUE</text>
<pin name="PE2" x="40.64" y="0" length="middle" rot="R180"/>
<pin name="PE3" x="40.64" y="-2.54" length="middle" rot="R180"/>
<pin name="PE4" x="40.64" y="-5.08" length="middle" rot="R180"/>
<pin name="PE5" x="40.64" y="-7.62" length="middle" rot="R180"/>
<pin name="PE6" x="40.64" y="-10.16" length="middle" rot="R180"/>
<pin name="V_BAT" x="-33.02" y="68.58" length="middle" direction="pwr"/>
<pin name="PC13(TAMPER-RTC)" x="40.64" y="-71.12" length="middle" rot="R180"/>
<pin name="PC14(OSC32_IN)" x="40.64" y="-73.66" length="middle" rot="R180"/>
<pin name="PC15(OSC32_OUT)" x="40.64" y="-76.2" length="middle" rot="R180"/>
<pin name="GND@4" x="-33.02" y="15.24" length="middle" direction="pwr"/>
<pin name="VDD@6" x="-33.02" y="33.02" length="middle" direction="pwr"/>
<pin name="OSC_IN" x="-33.02" y="2.54" length="middle" direction="in"/>
<pin name="OSC_OUT" x="-33.02" y="0" length="middle" direction="out"/>
<pin name="NRST" x="-33.02" y="71.12" length="middle"/>
<pin name="PC0" x="40.64" y="-38.1" length="middle" rot="R180"/>
<pin name="PC1" x="40.64" y="-40.64" length="middle" rot="R180"/>
<pin name="PC2" x="40.64" y="-43.18" length="middle" rot="R180"/>
<pin name="PC3" x="40.64" y="-45.72" length="middle" rot="R180"/>
<pin name="VDD@1" x="-33.02" y="45.72" length="middle" direction="pwr"/>
<pin name="VSS_A" x="-33.02" y="58.42" length="middle" direction="pwr"/>
<pin name="VREF+" x="-33.02" y="63.5" length="middle" direction="pwr"/>
<pin name="VDD_A" x="-33.02" y="60.96" length="middle" direction="pwr"/>
<pin name="PA0" x="40.64" y="40.64" length="middle" rot="R180"/>
<pin name="PA1" x="40.64" y="38.1" length="middle" rot="R180"/>
<pin name="PA2" x="40.64" y="35.56" length="middle" rot="R180"/>
<pin name="PA3" x="40.64" y="33.02" length="middle" rot="R180"/>
<pin name="GND@3" x="-33.02" y="17.78" length="middle" direction="pwr"/>
<pin name="VDD@5" x="-33.02" y="35.56" length="middle" direction="pwr"/>
<pin name="PA4" x="40.64" y="30.48" length="middle" rot="R180"/>
<pin name="PA5" x="40.64" y="27.94" length="middle" rot="R180"/>
<pin name="PA6" x="40.64" y="25.4" length="middle" rot="R180"/>
<pin name="PA7" x="40.64" y="22.86" length="middle" rot="R180"/>
<pin name="PC4" x="40.64" y="-48.26" length="middle" rot="R180"/>
<pin name="PC5" x="40.64" y="-50.8" length="middle" rot="R180"/>
<pin name="PB0" x="40.64" y="76.2" length="middle" rot="R180"/>
<pin name="PB1" x="40.64" y="73.66" length="middle" rot="R180"/>
<pin name="BOOT_1(PB2)" x="-33.02" y="-10.16" length="middle"/>
<pin name="PE7" x="40.64" y="-12.7" length="middle" rot="R180"/>
<pin name="PE8" x="40.64" y="-15.24" length="middle" rot="R180"/>
<pin name="PE9" x="40.64" y="-17.78" length="middle" rot="R180"/>
<pin name="PE10" x="40.64" y="-20.32" length="middle" rot="R180"/>
<pin name="PE11" x="40.64" y="-22.86" length="middle" rot="R180"/>
<pin name="PE12" x="40.64" y="-25.4" length="middle" rot="R180"/>
<pin name="PE13" x="40.64" y="-27.94" length="middle" rot="R180"/>
<pin name="PE14" x="40.64" y="-30.48" length="middle" rot="R180"/>
<pin name="PE15" x="40.64" y="-33.02" length="middle" rot="R180"/>
<pin name="PB10" x="40.64" y="58.42" length="middle" rot="R180"/>
<pin name="PB11" x="40.64" y="55.88" length="middle" rot="R180"/>
<pin name="VCAP_1" x="-33.02" y="25.4" length="middle" direction="pwr"/>
<pin name="VDD@2" x="-33.02" y="43.18" length="middle" direction="pwr"/>
<pin name="PB12" x="40.64" y="53.34" length="middle" rot="R180"/>
<pin name="PB13" x="40.64" y="50.8" length="middle" rot="R180"/>
<pin name="PB14" x="40.64" y="48.26" length="middle" rot="R180"/>
<pin name="PB15" x="40.64" y="45.72" length="middle" rot="R180"/>
<pin name="PD8" x="-33.02" y="-58.42" length="middle"/>
<pin name="PD9" x="-33.02" y="-60.96" length="middle"/>
<pin name="PD10" x="-33.02" y="-63.5" length="middle"/>
<pin name="PD11" x="-33.02" y="-66.04" length="middle"/>
<pin name="PD12" x="-33.02" y="-68.58" length="middle"/>
<pin name="PD13" x="-33.02" y="-71.12" length="middle"/>
<pin name="PD14" x="-33.02" y="-73.66" length="middle"/>
<pin name="PD15" x="-33.02" y="-76.2" length="middle"/>
<pin name="PC6" x="40.64" y="-53.34" length="middle" rot="R180"/>
<pin name="PC7" x="40.64" y="-55.88" length="middle" rot="R180"/>
<pin name="PC8" x="40.64" y="-58.42" length="middle" rot="R180"/>
<pin name="PC9" x="40.64" y="-60.96" length="middle" rot="R180"/>
<pin name="PA8" x="40.64" y="20.32" length="middle" rot="R180"/>
<pin name="PA9" x="40.64" y="17.78" length="middle" rot="R180"/>
<pin name="PA10" x="40.64" y="15.24" length="middle" rot="R180"/>
<pin name="PA11" x="40.64" y="12.7" length="middle" rot="R180"/>
<pin name="PA12" x="40.64" y="10.16" length="middle" rot="R180"/>
<pin name="JTMS(PA13)" x="-33.02" y="-17.78" length="middle"/>
<pin name="GND@1" x="-33.02" y="22.86" length="middle" direction="pwr"/>
<pin name="VDD@3" x="-33.02" y="40.64" length="middle" direction="pwr"/>
<pin name="JTCK(PA14)" x="-33.02" y="-20.32" length="middle"/>
<pin name="JTDI(PA15)" x="-33.02" y="-22.86" length="middle"/>
<pin name="PC10" x="40.64" y="-63.5" length="middle" rot="R180"/>
<pin name="PC11" x="40.64" y="-66.04" length="middle" rot="R180"/>
<pin name="PC12" x="40.64" y="-68.58" length="middle" rot="R180"/>
<pin name="PD0" x="-33.02" y="-38.1" length="middle"/>
<pin name="PD1" x="-33.02" y="-40.64" length="middle"/>
<pin name="PD2" x="-33.02" y="-43.18" length="middle"/>
<pin name="PD3" x="-33.02" y="-45.72" length="middle"/>
<pin name="PD4" x="-33.02" y="-48.26" length="middle"/>
<pin name="PD5" x="-33.02" y="-50.8" length="middle"/>
<pin name="PD6" x="-33.02" y="-53.34" length="middle"/>
<pin name="PD7" x="-33.02" y="-55.88" length="middle"/>
<pin name="JTDO(PB3)" x="-33.02" y="-27.94" length="middle"/>
<pin name="NJTRST(PB4)" x="-33.02" y="-25.4" length="middle"/>
<pin name="PB5" x="40.64" y="71.12" length="middle" rot="R180"/>
<pin name="PB6" x="40.64" y="68.58" length="middle" rot="R180"/>
<pin name="PB7" x="40.64" y="66.04" length="middle" rot="R180"/>
<pin name="BOOT_0" x="-33.02" y="-7.62" length="middle" direction="in"/>
<pin name="PB8" x="40.64" y="63.5" length="middle" rot="R180"/>
<pin name="PB9" x="40.64" y="60.96" length="middle" rot="R180"/>
<pin name="PE0" x="40.64" y="5.08" length="middle" rot="R180"/>
<pin name="PE1" x="40.64" y="2.54" length="middle" rot="R180"/>
<pin name="GND@2" x="-33.02" y="20.32" length="middle" direction="pwr"/>
<pin name="VDD@4" x="-33.02" y="38.1" length="middle" direction="pwr"/>
<pin name="VCAP_2" x="-33.02" y="76.2" length="middle"/>
<wire x1="-5.08" y1="-81.28" x2="-5.08" y2="78.74" width="0.1524" layer="94"/>
<wire x1="7.62" y1="78.74" x2="7.62" y2="-81.28" width="0.1524" layer="94"/>
</symbol>
<symbol name="MICROSD_SDIO">
<wire x1="-2.54" y1="15.24" x2="10.16" y2="15.24" width="0.254" layer="94"/>
<wire x1="10.16" y1="15.24" x2="10.16" y2="-22.86" width="0.254" layer="94"/>
<wire x1="10.16" y1="-22.86" x2="-2.54" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-22.86" x2="-2.54" y2="15.24" width="0.254" layer="94"/>
<text x="-2.54" y="15.748" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-25.4" size="1.778" layer="96">&gt;VALUE</text>
<pin name="SD_D3" x="-7.62" y="7.62" length="middle"/>
<pin name="SD_CMD" x="-7.62" y="5.08" length="middle"/>
<pin name="GND" x="-7.62" y="-20.32" length="middle" direction="pwr"/>
<pin name="VCC" x="-7.62" y="12.7" length="middle" direction="pwr"/>
<pin name="SD_CK" x="-7.62" y="2.54" length="middle" direction="in"/>
<pin name="SD_D1" x="-7.62" y="-2.54" length="middle"/>
<pin name="SD_D0" x="-7.62" y="0" length="middle"/>
<pin name="SD_D2" x="-7.62" y="10.16" length="middle"/>
<pin name="SHIELD@3" x="-7.62" y="-15.24" length="middle" direction="pwr"/>
<pin name="SHIELD@1" x="-7.62" y="-10.16" length="middle" direction="pwr"/>
<pin name="SHIELD@2" x="-7.62" y="-12.7" length="middle" direction="pwr"/>
<pin name="SHIELD@4" x="-7.62" y="-17.78" length="middle" direction="pwr"/>
<pin name="DETECT" x="-7.62" y="-5.08" length="middle" direction="out"/>
</symbol>
<symbol name="LED">
<wire x1="1.27" y1="0" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="-2.032" y1="-0.762" x2="-3.429" y2="-2.159" width="0.1524" layer="94"/>
<wire x1="-1.905" y1="-1.905" x2="-3.302" y2="-3.302" width="0.1524" layer="94"/>
<text x="3.556" y="-4.572" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="5.715" y="-4.572" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="C" x="0" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="A" x="0" y="2.54" visible="off" length="short" direction="pas" rot="R270"/>
<polygon width="0.1524" layer="94">
<vertex x="-3.429" y="-2.159"/>
<vertex x="-3.048" y="-1.27"/>
<vertex x="-2.54" y="-1.778"/>
</polygon>
<polygon width="0.1524" layer="94">
<vertex x="-3.302" y="-3.302"/>
<vertex x="-2.921" y="-2.413"/>
<vertex x="-2.413" y="-2.921"/>
</polygon>
</symbol>
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
<symbol name="TMP75">
<wire x1="-10.16" y1="5.08" x2="7.62" y2="5.08" width="0.254" layer="94"/>
<wire x1="7.62" y1="5.08" x2="7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="-10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-7.62" x2="-10.16" y2="5.08" width="0.254" layer="94"/>
<text x="-10.16" y="5.334" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="-9.906" size="1.778" layer="95">&gt;VALUE</text>
<pin name="SDA" x="-12.7" y="2.54" length="short" direction="oc"/>
<pin name="SCL" x="-12.7" y="0" length="short" direction="oc"/>
<pin name="ALERT" x="-12.7" y="-2.54" length="short" direction="out"/>
<pin name="GND" x="-12.7" y="-5.08" length="short" direction="pwr"/>
<pin name="A2" x="10.16" y="-5.08" length="short" direction="in" rot="R180"/>
<pin name="A1" x="10.16" y="-2.54" length="short" direction="in" rot="R180"/>
<pin name="A0" x="10.16" y="0" length="short" direction="in" rot="R180"/>
<pin name="VDD" x="10.16" y="2.54" length="short" direction="pwr" rot="R180"/>
</symbol>
<symbol name="24AA">
<wire x1="-7.62" y1="5.08" x2="10.16" y2="5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="5.08" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-7.62" x2="-7.62" y2="5.08" width="0.254" layer="94"/>
<text x="-7.62" y="6.35" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<pin name="VCC" x="12.7" y="2.54" length="short" direction="pwr" rot="R180"/>
<pin name="GND" x="-10.16" y="-5.08" length="short" direction="pwr"/>
<pin name="SCL" x="12.7" y="-2.54" length="short" direction="oc" rot="R180"/>
<pin name="SDA" x="12.7" y="-5.08" length="short" direction="oc" rot="R180"/>
<pin name="A0" x="-10.16" y="2.54" length="short" direction="in"/>
<pin name="A1" x="-10.16" y="0" length="short" direction="in"/>
<pin name="A2" x="-10.16" y="-2.54" length="short" direction="in"/>
<pin name="WP" x="12.7" y="0" length="short" direction="in" rot="R180"/>
</symbol>
<symbol name="BMP085">
<wire x1="-7.62" y1="-7.62" x2="-7.62" y2="5.08" width="0.254" layer="94"/>
<wire x1="-7.62" y1="5.08" x2="10.16" y2="5.08" width="0.254" layer="94"/>
<wire x1="10.16" y1="5.08" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<text x="-7.62" y="5.588" size="1.778" layer="95">&gt;Name</text>
<text x="-7.62" y="-10.16" size="1.778" layer="95">&gt;Value</text>
<pin name="XCLR" x="15.24" y="-5.08" length="middle" direction="in" function="dot" rot="R180"/>
<pin name="SDA" x="15.24" y="2.54" length="middle" direction="oc" rot="R180"/>
<pin name="SCL" x="15.24" y="0" length="middle" direction="oc" rot="R180"/>
<pin name="NC" x="-12.7" y="-2.54" length="middle" direction="nc"/>
<pin name="VDDD" x="-12.7" y="0" length="middle" direction="pwr"/>
<pin name="VDDA" x="-12.7" y="2.54" length="middle" direction="pwr"/>
<pin name="EOC" x="15.24" y="-2.54" length="middle" direction="out" rot="R180"/>
<pin name="GND" x="-12.7" y="-5.08" length="middle" direction="pwr"/>
</symbol>
<symbol name="PTC">
<wire x1="5.08" y1="1.27" x2="5.08" y2="-1.27" width="0.254" layer="94"/>
<wire x1="5.08" y1="-1.27" x2="-2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-1.27" x2="-2.54" y2="1.27" width="0.254" layer="94"/>
<wire x1="-2.54" y1="1.27" x2="5.08" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.524" y1="-2.54" x2="3.81" y2="2.54" width="0.254" layer="94"/>
<wire x1="3.81" y1="2.54" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<text x="-2.54" y="3.048" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.302" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
<pin name="2" x="7.62" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="D">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="0.508" y2="1.27" width="0.254" layer="94"/>
<text x="2.54" y="0.4826" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-2.3114" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
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
<symbol name="5V">
<wire x1="0.762" y1="1.27" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="-0.762" y2="1.27" width="0.254" layer="94"/>
<text x="-1.016" y="3.556" size="1.778" layer="96">&gt;VALUE</text>
<pin name="6V" x="0" y="0" visible="off" length="short" direction="sup" rot="R90"/>
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
<symbol name="INA194">
<wire x1="-7.62" y1="-7.62" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="7.62" x2="-7.62" y2="7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<text x="-5.08" y="8.255" size="1.778" layer="95" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-10.16" size="1.778" layer="96" ratio="10">&gt;VALUE</text>
<pin name="IN-" x="-10.16" y="5.08" length="short" direction="in"/>
<pin name="IN+" x="-10.16" y="-5.08" length="short" direction="in"/>
<pin name="OUT" x="12.7" y="0" length="short" direction="out" rot="R180"/>
<pin name="V+" x="12.7" y="5.08" length="short" direction="pwr" rot="R180"/>
<pin name="GND" x="12.7" y="-5.08" length="short" direction="pwr" rot="R180"/>
</symbol>
<symbol name="JUMPER-2">
<wire x1="0" y1="0" x2="0" y2="1.27" width="0.1524" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="1.27" width="0.4064" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="1.27" width="0.1524" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="1.27" width="0.4064" layer="94"/>
<wire x1="-0.635" y1="0" x2="3.175" y2="0" width="0.4064" layer="94"/>
<wire x1="3.175" y1="0" x2="3.175" y2="0.635" width="0.4064" layer="94"/>
<wire x1="3.175" y1="0.635" x2="-0.635" y2="0.635" width="0.4064" layer="94"/>
<wire x1="-0.635" y1="0.635" x2="-0.635" y2="0" width="0.4064" layer="94"/>
<text x="-1.27" y="0" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="5.715" y="0" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="1" x="0" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="2" x="2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
<symbol name="MPXV5010DP">
<wire x1="-7.62" y1="7.62" x2="7.62" y2="7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="7.62" x2="7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-7.62" x2="-7.62" y2="7.62" width="0.254" layer="94"/>
<text x="2.54" y="10.16" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<pin name="VCC" x="0" y="12.7" length="middle" direction="pwr" rot="R270"/>
<pin name="OUT" x="12.7" y="0" length="middle" direction="out" rot="R180"/>
<pin name="GND" x="0" y="-12.7" length="middle" direction="pwr" rot="R90"/>
</symbol>
<symbol name="RESISTOR">
<wire x1="-2.54" y1="-0.889" x2="2.54" y2="-0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="2.54" y1="-0.889" x2="2.54" y2="0.889" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-0.889" x2="-2.54" y2="0.889" width="0.254" layer="94"/>
<text x="-3.81" y="1.4986" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="2" x="5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
<pin name="1" x="-5.08" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
</symbol>
<symbol name="78ADJ-3PIN">
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="5.08" y2="2.54" width="0.4064" layer="94"/>
<wire x1="5.08" y1="2.54" x2="-5.08" y2="2.54" width="0.4064" layer="94"/>
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="-5.08" width="0.4064" layer="94"/>
<text x="-4.826" y="3.048" size="1.778" layer="95">&gt;NAME</text>
<text x="1.27" y="-7.366" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.032" y="-4.318" size="1.524" layer="95">ADJ</text>
<text x="-4.445" y="-0.635" size="1.524" layer="95">IN</text>
<text x="0.635" y="-0.635" size="1.524" layer="95">OUT</text>
<pin name="IN" x="-7.62" y="0" visible="pad" length="short" direction="pwr"/>
<pin name="ADJ" x="0" y="-7.62" visible="pad" length="short" direction="in" rot="R90"/>
<pin name="OUT" x="7.62" y="0" visible="pad" length="short" direction="pwr" rot="R180"/>
</symbol>
<symbol name="LP2980">
<wire x1="-7.62" y1="-10.16" x2="10.16" y2="-10.16" width="0.4064" layer="94"/>
<wire x1="10.16" y1="-10.16" x2="10.16" y2="5.08" width="0.4064" layer="94"/>
<wire x1="10.16" y1="5.08" x2="-7.62" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-7.62" y1="5.08" x2="-7.62" y2="-10.16" width="0.4064" layer="94"/>
<text x="-7.366" y="5.588" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-12.446" size="1.778" layer="96">&gt;VALUE</text>
<pin name="IN" x="-10.16" y="2.54" length="short" direction="pwr"/>
<pin name="GND" x="12.7" y="-2.54" length="short" direction="in" rot="R180"/>
<pin name="OUT" x="12.7" y="2.54" length="short" direction="pwr" rot="R180"/>
<pin name="EN" x="-10.16" y="-2.54" length="short" direction="in"/>
<pin name="BYPASS" x="12.7" y="-7.62" length="short" direction="in" rot="R180"/>
</symbol>
<symbol name="ADIS16480">
<pin name="DIO4" x="-20.32" y="-12.7" length="middle"/>
<pin name="DOUT" x="-20.32" y="5.08" length="middle" direction="out"/>
<pin name="!CS" x="-20.32" y="2.54" length="middle" direction="in"/>
<pin name="!RST" x="-20.32" y="0" length="middle" direction="in"/>
<pin name="VDD@1" x="22.86" y="10.16" length="middle" direction="pwr" rot="R180"/>
<pin name="VDD@2" x="22.86" y="7.62" length="middle" direction="pwr" rot="R180"/>
<pin name="GND@1" x="22.86" y="-2.54" length="middle" direction="pwr" rot="R180"/>
<pin name="DIO3" x="-20.32" y="-10.16" length="middle"/>
<pin name="SCLK" x="-20.32" y="10.16" length="middle" direction="in"/>
<pin name="DIN" x="-20.32" y="7.62" length="middle" direction="in"/>
<pin name="DIO1" x="-20.32" y="-5.08" length="middle"/>
<pin name="DIO2" x="-20.32" y="-7.62" length="middle"/>
<pin name="VDD@3" x="22.86" y="5.08" length="middle" direction="pwr" rot="R180"/>
<pin name="GND@2" x="22.86" y="-5.08" length="middle" direction="pwr" rot="R180"/>
<pin name="GND@3" x="22.86" y="-7.62" length="middle" direction="pwr" rot="R180"/>
<pin name="VDDRTC" x="22.86" y="2.54" length="middle" direction="pwr" rot="R180"/>
<wire x1="-15.24" y1="12.7" x2="-5.08" y2="12.7" width="0.254" layer="94"/>
<wire x1="-5.08" y1="12.7" x2="5.08" y2="12.7" width="0.254" layer="94"/>
<wire x1="5.08" y1="12.7" x2="17.78" y2="12.7" width="0.254" layer="94"/>
<wire x1="17.78" y1="12.7" x2="17.78" y2="-15.24" width="0.254" layer="94"/>
<wire x1="17.78" y1="-15.24" x2="5.08" y2="-15.24" width="0.254" layer="94"/>
<wire x1="5.08" y1="-15.24" x2="-5.08" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-15.24" x2="-15.24" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-15.24" x2="-15.24" y2="12.7" width="0.254" layer="94"/>
<wire x1="-5.08" y1="12.7" x2="-5.08" y2="-15.24" width="0.254" layer="94"/>
<wire x1="5.08" y1="12.7" x2="5.08" y2="-15.24" width="0.254" layer="94"/>
<text x="-2.54" y="15.24" size="1.27" layer="95">&gt;NAME</text>
<text x="-5.08" y="-17.78" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="MAX44246">
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<pin name="-IN" x="-7.62" y="2.54" visible="pad" length="short" direction="in"/>
<pin name="+IN" x="-7.62" y="-2.54" visible="pad" length="short" direction="in"/>
<pin name="-V" x="0" y="-7.62" visible="pad" length="middle" direction="pwr" rot="R90"/>
<pin name="+V" x="0" y="7.62" visible="pad" length="middle" direction="pwr" rot="R270"/>
<pin name="OUT" x="7.62" y="0" visible="pad" length="short" direction="out" rot="R180"/>
<text x="-4.318" y="1.778" size="1.778" layer="94">-</text>
<text x="-4.318" y="-3.302" size="1.778" layer="94">+</text>
<text x="2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<text x="2.54" y="5.08" size="1.778" layer="95">&gt;NAME</text>
</symbol>
<symbol name="MAX44246_2">
<wire x1="-5.08" y1="5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<pin name="-IN" x="-7.62" y="2.54" visible="pad" length="short" direction="in"/>
<pin name="+IN" x="-7.62" y="-2.54" visible="pad" length="short" direction="in"/>
<pin name="OUT" x="7.62" y="0" visible="pad" length="short" direction="out" rot="R180"/>
<text x="-4.318" y="1.524" size="1.778" layer="94">-</text>
<text x="-4.318" y="-3.302" size="1.778" layer="94">+</text>
<text x="-2.54" y="5.08" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="AD22100">
<pin name="VDD" x="10.16" y="5.08" length="middle" direction="pwr" rot="R180"/>
<pin name="GND" x="10.16" y="-5.08" length="middle" direction="pwr" rot="R180"/>
<pin name="OUT" x="10.16" y="0" length="middle" direction="out" rot="R180"/>
<wire x1="5.08" y1="-7.62" x2="-5.08" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-7.62" x2="-5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="-5.08" y1="7.62" x2="5.08" y2="7.62" width="0.254" layer="94"/>
<wire x1="5.08" y1="7.62" x2="5.08" y2="-7.62" width="0.254" layer="94"/>
<text x="-2.54" y="10.16" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="MPU-9150">
<description>MPU-9150: 9DOF (3mag, 3accel, 3rotat)</description>
<wire x1="-12.7" y1="17.78" x2="-12.7" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-15.24" x2="12.7" y2="-15.24" width="0.254" layer="94"/>
<wire x1="12.7" y1="-15.24" x2="12.7" y2="17.78" width="0.254" layer="94"/>
<wire x1="12.7" y1="17.78" x2="-12.7" y2="17.78" width="0.254" layer="94"/>
<pin name="VLOGIC" x="-17.78" y="15.24" length="middle"/>
<pin name="VDD@3" x="-17.78" y="12.7" length="middle"/>
<pin name="VDD@13" x="-17.78" y="10.16" length="middle"/>
<pin name="AD0" x="17.78" y="2.54" length="middle" rot="R180"/>
<pin name="CPOUT" x="-17.78" y="2.54" length="middle"/>
<pin name="GND@18" x="-17.78" y="-7.62" length="middle"/>
<pin name="GND@17" x="-17.78" y="-10.16" length="middle"/>
<pin name="GND@15" x="-17.78" y="-12.7" length="middle"/>
<pin name="FSYNC" x="-17.78" y="-2.54" length="middle"/>
<pin name="REGOUT" x="-17.78" y="5.08" length="middle"/>
<pin name="CLKIN" x="-17.78" y="-5.08" length="middle"/>
<pin name="E_SDA" x="17.78" y="-12.7" length="middle" rot="R180"/>
<pin name="E_SCL" x="17.78" y="-10.16" length="middle" rot="R180"/>
<pin name="INT" x="17.78" y="5.08" length="middle" rot="R180"/>
<pin name="SCL" x="17.78" y="12.7" length="middle" rot="R180"/>
<pin name="SDA" x="17.78" y="15.24" length="middle" rot="R180"/>
<text x="-5.08" y="19.05" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-17.78" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="LSM303DLHC">
<wire x1="-15.24" y1="12.7" x2="12.7" y2="12.7" width="0.254" layer="94"/>
<wire x1="12.7" y1="12.7" x2="12.7" y2="-12.7" width="0.254" layer="94"/>
<wire x1="12.7" y1="-12.7" x2="-15.24" y2="-12.7" width="0.254" layer="94"/>
<wire x1="-15.24" y1="-12.7" x2="-15.24" y2="12.7" width="0.254" layer="94"/>
<text x="-15.24" y="13.208" size="1.9304" layer="95">&gt;Name</text>
<text x="-15.24" y="-15.24" size="1.9304" layer="96">&gt;Value</text>
<pin name="GND@1" x="-17.78" y="-5.08" length="short"/>
<pin name="VDD" x="-17.78" y="10.16" length="short"/>
<pin name="SETC" x="15.24" y="-10.16" length="short" rot="R180"/>
<pin name="C1" x="-17.78" y="0" length="short"/>
<pin name="SETP" x="15.24" y="-7.62" length="short" rot="R180"/>
<pin name="DRDY" x="15.24" y="2.54" length="short" rot="R180"/>
<pin name="VDD_IO" x="-17.78" y="7.62" length="short"/>
<pin name="SCL" x="15.24" y="7.62" length="short" rot="R180"/>
<pin name="SDA" x="15.24" y="10.16" length="short" rot="R180"/>
<pin name="INT1" x="15.24" y="-2.54" length="short" rot="R180"/>
<pin name="INT2" x="15.24" y="0" length="short" rot="R180"/>
<pin name="GND@2" x="-17.78" y="-7.62" length="short"/>
<pin name="GND@3" x="-17.78" y="-10.16" length="short"/>
</symbol>
<symbol name="AD52XX">
<pin name="VDD" x="-15.24" y="5.08" length="middle"/>
<pin name="CLK" x="-15.24" y="2.54" length="middle"/>
<pin name="!CS" x="-15.24" y="0" length="middle"/>
<pin name="SDI" x="-15.24" y="-2.54" length="middle"/>
<pin name="GND" x="-15.24" y="-5.08" length="middle"/>
<pin name="B" x="17.78" y="5.08" length="middle" rot="R180"/>
<pin name="W" x="17.78" y="2.54" length="middle" rot="R180"/>
<pin name="VSS" x="17.78" y="-5.08" length="middle" rot="R180"/>
<pin name="A" x="17.78" y="0" length="middle" rot="R180"/>
<pin name="!SHDN" x="17.78" y="-2.54" length="middle" rot="R180"/>
<wire x1="-10.16" y1="7.62" x2="-10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="-7.62" x2="12.7" y2="-7.62" width="0.254" layer="94"/>
<wire x1="12.7" y1="-7.62" x2="12.7" y2="7.62" width="0.254" layer="94"/>
<wire x1="12.7" y1="7.62" x2="-10.16" y2="7.62" width="0.254" layer="94"/>
<text x="-5.08" y="10.16" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="DIODE_SCHOTTKY">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="1.016" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="-1.016" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<text x="-2.286" y="1.905" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.286" y="-3.429" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
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
</symbols>
<devicesets>
<deviceset name="STM32F407V" prefix="DD">
<gates>
<gate name="G$1" symbol="STM32F407V" x="-50.8" y="15.24"/>
</gates>
<devices>
<device name="" package="TQFP100">
<connects>
<connect gate="G$1" pin="BOOT_0" pad="94"/>
<connect gate="G$1" pin="BOOT_1(PB2)" pad="37"/>
<connect gate="G$1" pin="GND@1" pad="74"/>
<connect gate="G$1" pin="GND@2" pad="99"/>
<connect gate="G$1" pin="GND@3" pad="27"/>
<connect gate="G$1" pin="GND@4" pad="10"/>
<connect gate="G$1" pin="JTCK(PA14)" pad="76"/>
<connect gate="G$1" pin="JTDI(PA15)" pad="77"/>
<connect gate="G$1" pin="JTDO(PB3)" pad="89"/>
<connect gate="G$1" pin="JTMS(PA13)" pad="72"/>
<connect gate="G$1" pin="NJTRST(PB4)" pad="90"/>
<connect gate="G$1" pin="NRST" pad="14"/>
<connect gate="G$1" pin="OSC_IN" pad="12"/>
<connect gate="G$1" pin="OSC_OUT" pad="13"/>
<connect gate="G$1" pin="PA0" pad="23"/>
<connect gate="G$1" pin="PA1" pad="24"/>
<connect gate="G$1" pin="PA10" pad="69"/>
<connect gate="G$1" pin="PA11" pad="70"/>
<connect gate="G$1" pin="PA12" pad="71"/>
<connect gate="G$1" pin="PA2" pad="25"/>
<connect gate="G$1" pin="PA3" pad="26"/>
<connect gate="G$1" pin="PA4" pad="29"/>
<connect gate="G$1" pin="PA5" pad="30"/>
<connect gate="G$1" pin="PA6" pad="31"/>
<connect gate="G$1" pin="PA7" pad="32"/>
<connect gate="G$1" pin="PA8" pad="67"/>
<connect gate="G$1" pin="PA9" pad="68"/>
<connect gate="G$1" pin="PB0" pad="35"/>
<connect gate="G$1" pin="PB1" pad="36"/>
<connect gate="G$1" pin="PB10" pad="47"/>
<connect gate="G$1" pin="PB11" pad="48"/>
<connect gate="G$1" pin="PB12" pad="51"/>
<connect gate="G$1" pin="PB13" pad="52"/>
<connect gate="G$1" pin="PB14" pad="53"/>
<connect gate="G$1" pin="PB15" pad="54"/>
<connect gate="G$1" pin="PB5" pad="91"/>
<connect gate="G$1" pin="PB6" pad="92"/>
<connect gate="G$1" pin="PB7" pad="93"/>
<connect gate="G$1" pin="PB8" pad="95"/>
<connect gate="G$1" pin="PB9" pad="96"/>
<connect gate="G$1" pin="PC0" pad="15"/>
<connect gate="G$1" pin="PC1" pad="16"/>
<connect gate="G$1" pin="PC10" pad="78"/>
<connect gate="G$1" pin="PC11" pad="79"/>
<connect gate="G$1" pin="PC12" pad="80"/>
<connect gate="G$1" pin="PC13(TAMPER-RTC)" pad="7"/>
<connect gate="G$1" pin="PC14(OSC32_IN)" pad="8"/>
<connect gate="G$1" pin="PC15(OSC32_OUT)" pad="9"/>
<connect gate="G$1" pin="PC2" pad="17"/>
<connect gate="G$1" pin="PC3" pad="18"/>
<connect gate="G$1" pin="PC4" pad="33"/>
<connect gate="G$1" pin="PC5" pad="34"/>
<connect gate="G$1" pin="PC6" pad="63"/>
<connect gate="G$1" pin="PC7" pad="64"/>
<connect gate="G$1" pin="PC8" pad="65"/>
<connect gate="G$1" pin="PC9" pad="66"/>
<connect gate="G$1" pin="PD0" pad="81"/>
<connect gate="G$1" pin="PD1" pad="82"/>
<connect gate="G$1" pin="PD10" pad="57"/>
<connect gate="G$1" pin="PD11" pad="58"/>
<connect gate="G$1" pin="PD12" pad="59"/>
<connect gate="G$1" pin="PD13" pad="60"/>
<connect gate="G$1" pin="PD14" pad="61"/>
<connect gate="G$1" pin="PD15" pad="62"/>
<connect gate="G$1" pin="PD2" pad="83"/>
<connect gate="G$1" pin="PD3" pad="84"/>
<connect gate="G$1" pin="PD4" pad="85"/>
<connect gate="G$1" pin="PD5" pad="86"/>
<connect gate="G$1" pin="PD6" pad="87"/>
<connect gate="G$1" pin="PD7" pad="88"/>
<connect gate="G$1" pin="PD8" pad="55"/>
<connect gate="G$1" pin="PD9" pad="56"/>
<connect gate="G$1" pin="PE0" pad="97"/>
<connect gate="G$1" pin="PE1" pad="98"/>
<connect gate="G$1" pin="PE10" pad="41"/>
<connect gate="G$1" pin="PE11" pad="42"/>
<connect gate="G$1" pin="PE12" pad="43"/>
<connect gate="G$1" pin="PE13" pad="44"/>
<connect gate="G$1" pin="PE14" pad="45"/>
<connect gate="G$1" pin="PE15" pad="46"/>
<connect gate="G$1" pin="PE2" pad="1"/>
<connect gate="G$1" pin="PE3" pad="2"/>
<connect gate="G$1" pin="PE4" pad="3"/>
<connect gate="G$1" pin="PE5" pad="4"/>
<connect gate="G$1" pin="PE6" pad="5"/>
<connect gate="G$1" pin="PE7" pad="38"/>
<connect gate="G$1" pin="PE8" pad="39"/>
<connect gate="G$1" pin="PE9" pad="40"/>
<connect gate="G$1" pin="VCAP_1" pad="49"/>
<connect gate="G$1" pin="VCAP_2" pad="73"/>
<connect gate="G$1" pin="VDD@1" pad="19"/>
<connect gate="G$1" pin="VDD@2" pad="50"/>
<connect gate="G$1" pin="VDD@3" pad="75"/>
<connect gate="G$1" pin="VDD@4" pad="100"/>
<connect gate="G$1" pin="VDD@5" pad="28"/>
<connect gate="G$1" pin="VDD@6" pad="11"/>
<connect gate="G$1" pin="VDD_A" pad="22"/>
<connect gate="G$1" pin="VREF+" pad="21"/>
<connect gate="G$1" pin="VSS_A" pad="20"/>
<connect gate="G$1" pin="V_BAT" pad="6"/>
</connects>
<technologies>
<technology name=""/>
<technology name="GT6"/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MICROSD_SDIO" prefix="DD">
<description>&lt;b&gt;microSD Socket&lt;/b&gt;
Push-push type uSD socket. Schematic element for SDIO pin names.</description>
<gates>
<gate name="G$1" symbol="MICROSD_SDIO" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MICROSD">
<connects>
<connect gate="G$1" pin="DETECT" pad="13"/>
<connect gate="G$1" pin="GND" pad="6"/>
<connect gate="G$1" pin="SD_CK" pad="5"/>
<connect gate="G$1" pin="SD_CMD" pad="3"/>
<connect gate="G$1" pin="SD_D0" pad="7"/>
<connect gate="G$1" pin="SD_D1" pad="8"/>
<connect gate="G$1" pin="SD_D2" pad="1"/>
<connect gate="G$1" pin="SD_D3" pad="2"/>
<connect gate="G$1" pin="SHIELD@1" pad="9"/>
<connect gate="G$1" pin="SHIELD@2" pad="10"/>
<connect gate="G$1" pin="SHIELD@3" pad="11"/>
<connect gate="G$1" pin="SHIELD@4" pad="12"/>
<connect gate="G$1" pin="VCC" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LED" prefix="VD" uservalue="yes">
<description>&lt;b&gt;LEDs&lt;/b&gt;
Standard schematic elements and footprints for 5mm, 3mm, 1206, and 0603 sized LEDs. 5mm - Spark Fun Electronics SKU : COM-00529 (and others)</description>
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="LED-1206">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0603" package="LED-0603">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="LED-0805">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="2X10" prefix="XP">
<description>Standard 10x2 JTAG header for ARM.</description>
<gates>
<gate name="G$1" symbol="M10X2" x="0" y="0"/>
</gates>
<devices>
<device name="-SHROUDED" package="2X10-SHROUDED">
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
<device name="-PSEUDO_SMD" package="2X10-PSEUDOSMD">
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
<deviceset name="TMP75" prefix="U">
<gates>
<gate name="G$1" symbol="TMP75" x="0" y="0"/>
</gates>
<devices>
<device name="DGK" package="MSOP8">
<connects>
<connect gate="G$1" pin="A0" pad="7"/>
<connect gate="G$1" pin="A1" pad="6"/>
<connect gate="G$1" pin="A2" pad="5"/>
<connect gate="G$1" pin="ALERT" pad="3"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="SCL" pad="2"/>
<connect gate="G$1" pin="SDA" pad="1"/>
<connect gate="G$1" pin="VDD" pad="8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="24*" prefix="DD">
<description>Serial &lt;B&gt;EEPROM&lt;/B&gt;&lt;p&gt;
I2C</description>
<gates>
<gate name="G$1" symbol="24AA" x="0" y="0"/>
</gates>
<devices>
<device name="SM" package="SO-08M">
<connects>
<connect gate="G$1" pin="A0" pad="1"/>
<connect gate="G$1" pin="A1" pad="2"/>
<connect gate="G$1" pin="A2" pad="3"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="SCL" pad="6"/>
<connect gate="G$1" pin="SDA" pad="5"/>
<connect gate="G$1" pin="VCC" pad="8"/>
<connect gate="G$1" pin="WP" pad="7"/>
</connects>
<technologies>
<technology name="AA01">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA01-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331268" constant="no"/>
<attribute name="OC_NEWARK" value="92C6793" constant="no"/>
</technology>
<technology name="AA02">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA02-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331272" constant="no"/>
<attribute name="OC_NEWARK" value="92C6803" constant="no"/>
</technology>
<technology name="AA04">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA04-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331276" constant="no"/>
<attribute name="OC_NEWARK" value="92C6814" constant="no"/>
</technology>
<technology name="AA08">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA08-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331282" constant="no"/>
<attribute name="OC_NEWARK" value="92C6826" constant="no"/>
</technology>
<technology name="AA128">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA128-I/MS" constant="no"/>
<attribute name="OC_FARNELL" value="1331285" constant="no"/>
<attribute name="OC_NEWARK" value="92C6839" constant="no"/>
</technology>
<technology name="AA16">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA16-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331289" constant="no"/>
<attribute name="OC_NEWARK" value="96K4056" constant="no"/>
</technology>
<technology name="AA32A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA32A-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1617659" constant="no"/>
<attribute name="OC_NEWARK" value="83C5815" constant="no"/>
</technology>
<technology name="C01A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24C01C/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1362638" constant="no"/>
<attribute name="OC_NEWARK" value="96K4061" constant="no"/>
</technology>
<technology name="C02A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24C02C/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1084339" constant="no"/>
<attribute name="OC_NEWARK" value="96K4065" constant="no"/>
</technology>
<technology name="C04A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="M24C04-WMN6P" constant="no"/>
<attribute name="OC_FARNELL" value="9882812" constant="no"/>
<attribute name="OC_NEWARK" value="83K1376" constant="no"/>
</technology>
<technology name="C08B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="AT24C08BN-SH-B" constant="no"/>
<attribute name="OC_FARNELL" value="1362645" constant="no"/>
<attribute name="OC_NEWARK" value="50M3318" constant="no"/>
</technology>
<technology name="C32A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="IS24C32A-2GLI" constant="no"/>
<attribute name="OC_FARNELL" value="1718129" constant="no"/>
<attribute name="OC_NEWARK" value="43M4588" constant="no"/>
</technology>
<technology name="C64">
<attribute name="MF" value="RAMTRON INTERNATIONAL CORP" constant="no"/>
<attribute name="MPN" value="FM24C64-S" constant="no"/>
<attribute name="OC_FARNELL" value="9882685" constant="no"/>
<attribute name="OC_NEWARK" value="98H0189" constant="no"/>
</technology>
<technology name="CL04B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="FM24CL04-S" constant="no"/>
<attribute name="OC_FARNELL" value="1607928" constant="no"/>
<attribute name="OC_NEWARK" value="97H6443" constant="no"/>
</technology>
<technology name="LC08B">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC08BT-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1818714" constant="no"/>
<attribute name="OC_NEWARK" value="92C7127" constant="no"/>
</technology>
<technology name="LC128">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC128-I/SM" constant="no"/>
<attribute name="OC_FARNELL" value="9757937" constant="no"/>
<attribute name="OC_NEWARK" value="92C7134" constant="no"/>
</technology>
<technology name="LC16B">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC16B/SN" constant="no"/>
<attribute name="OC_FARNELL" value="9757945" constant="no"/>
<attribute name="OC_NEWARK" value="12C2012" constant="no"/>
</technology>
<technology name="LC32A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC32A/SM" constant="no"/>
<attribute name="OC_FARNELL" value="1212670" constant="no"/>
<attribute name="OC_NEWARK" value="96K4080" constant="no"/>
</technology>
<technology name="LC64">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC64T-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="9758070" constant="no"/>
<attribute name="OC_NEWARK" value="12C2021" constant="no"/>
</technology>
</technologies>
</device>
<device name="SL" package="SO-14">
<connects>
<connect gate="G$1" pin="A0" pad="2"/>
<connect gate="G$1" pin="A1" pad="3"/>
<connect gate="G$1" pin="A2" pad="5"/>
<connect gate="G$1" pin="GND" pad="6"/>
<connect gate="G$1" pin="SCL" pad="10"/>
<connect gate="G$1" pin="SDA" pad="9"/>
<connect gate="G$1" pin="VCC" pad="13"/>
<connect gate="G$1" pin="WP" pad="12"/>
</connects>
<technologies>
<technology name="AA04">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="AA08">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="AA16">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="C01A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="C02A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="C04A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="C08B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="C16B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="CL04A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="LC08B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="LC16B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="P" package="DIL8">
<connects>
<connect gate="G$1" pin="A0" pad="1"/>
<connect gate="G$1" pin="A1" pad="2"/>
<connect gate="G$1" pin="A2" pad="3"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="SCL" pad="6"/>
<connect gate="G$1" pin="SDA" pad="5"/>
<connect gate="G$1" pin="VCC" pad="8"/>
<connect gate="G$1" pin="WP" pad="7"/>
</connects>
<technologies>
<technology name="AA01">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24AA01-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331266" constant="no"/>
<attribute name="OC_NEWARK" value="35M0692" constant="no"/>
</technology>
<technology name="AA02">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24AA02-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331271" constant="no"/>
<attribute name="OC_NEWARK" value="95M2072" constant="no"/>
</technology>
<technology name="AA04">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24AA04-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331275" constant="no"/>
<attribute name="OC_NEWARK" value="35M0696" constant="no"/>
</technology>
<technology name="AA08">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA08-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331281" constant="no"/>
<attribute name="OC_NEWARK" value="92C6825" constant="no"/>
</technology>
<technology name="AA128">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA128-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="92C6840" constant="no"/>
</technology>
<technology name="AA16">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24AA16-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331287" constant="no"/>
<attribute name="OC_NEWARK" value="35M0705" constant="no"/>
</technology>
<technology name="AA256">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA256-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331294" constant="no"/>
<attribute name="OC_NEWARK" value="92C6872" constant="no"/>
</technology>
<technology name="AA32A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA32A-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331297" constant="no"/>
<attribute name="OC_NEWARK" value="92C6885" constant="no"/>
</technology>
<technology name="AA64">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA64-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331303" constant="no"/>
<attribute name="OC_NEWARK" value="92C6909" constant="no"/>
</technology>
<technology name="C01A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="M24C01-WBN6P" constant="no"/>
<attribute name="OC_FARNELL" value="9882782" constant="no"/>
<attribute name="OC_NEWARK" value="24M5067" constant="no"/>
</technology>
<technology name="C02A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24C02C-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1755843" constant="no"/>
<attribute name="OC_NEWARK" value="96K4062" constant="no"/>
</technology>
<technology name="C04A">
<attribute name="MF" value="RAMTRON INTERNATIONAL CORP" constant="no"/>
<attribute name="MPN" value="FM24C04A-P" constant="no"/>
<attribute name="OC_FARNELL" value="1094258" constant="no"/>
<attribute name="OC_NEWARK" value="97H6447" constant="no"/>
</technology>
<technology name="C08B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="AT24C08B-PU" constant="no"/>
<attribute name="OC_FARNELL" value="1362644" constant="no"/>
<attribute name="OC_NEWARK" value="50M3317" constant="no"/>
</technology>
<technology name="C16B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="AT24C16B-PU" constant="no"/>
<attribute name="OC_FARNELL" value="1362650" constant="no"/>
<attribute name="OC_NEWARK" value="50M3323" constant="no"/>
</technology>
<technology name="C32A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="AT24C32C-PU" constant="no"/>
<attribute name="OC_FARNELL" value="1362652" constant="no"/>
<attribute name="OC_NEWARK" value="50M3325" constant="no"/>
</technology>
<technology name="C64">
<attribute name="MF" value="RAMTRON INTERNATIONAL CORP" constant="no"/>
<attribute name="MPN" value="FM24C64-P" constant="no"/>
<attribute name="OC_FARNELL" value="1362657" constant="no"/>
<attribute name="OC_NEWARK" value="97H6452" constant="no"/>
</technology>
<technology name="CL04B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
<technology name="LC01">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24LC01BH-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1200025" constant="no"/>
<attribute name="OC_NEWARK" value="77M3542" constant="no"/>
</technology>
<technology name="LC024">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24LC024-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1331317" constant="no"/>
<attribute name="OC_NEWARK" value="35M0731" constant="no"/>
</technology>
<technology name="LC025">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC025-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="92C7098" constant="no"/>
</technology>
<technology name="LC04">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC04B-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="1196811" constant="no"/>
<attribute name="OC_NEWARK" value="62K0576" constant="no"/>
</technology>
<technology name="LC08B">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC08B/P" constant="no"/>
<attribute name="OC_FARNELL" value="1084245" constant="no"/>
<attribute name="OC_NEWARK" value="96K4073" constant="no"/>
</technology>
<technology name="LC128">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC128-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="9757929" constant="no"/>
<attribute name="OC_NEWARK" value="12C2007" constant="no"/>
</technology>
<technology name="LC16B">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC16B/P" constant="no"/>
<attribute name="OC_FARNELL" value="1200026" constant="no"/>
<attribute name="OC_NEWARK" value="69K7671" constant="no"/>
</technology>
<technology name="LC256">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC256-E/P" constant="no"/>
<attribute name="OC_FARNELL" value="9757970" constant="no"/>
<attribute name="OC_NEWARK" value="92C7169" constant="no"/>
</technology>
<technology name="LC32A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC32A/P" constant="no"/>
<attribute name="OC_FARNELL" value="1084246" constant="no"/>
<attribute name="OC_NEWARK" value="75K1884" constant="no"/>
</technology>
<technology name="LC64">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC64-I/P" constant="no"/>
<attribute name="OC_FARNELL" value="9758054" constant="no"/>
<attribute name="OC_NEWARK" value="62K0584" constant="no"/>
</technology>
<technology name="LCS52">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LCS52-I/PG" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="89H3098" constant="no"/>
</technology>
</technologies>
</device>
<device name="SN" package="SO-08">
<connects>
<connect gate="G$1" pin="A0" pad="1"/>
<connect gate="G$1" pin="A1" pad="2"/>
<connect gate="G$1" pin="A2" pad="3"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="SCL" pad="6"/>
<connect gate="G$1" pin="SDA" pad="5"/>
<connect gate="G$1" pin="VCC" pad="8"/>
<connect gate="G$1" pin="WP" pad="7"/>
</connects>
<technologies>
<technology name="AA01">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA01/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331268" constant="no"/>
<attribute name="OC_NEWARK" value="89C9792" constant="no"/>
</technology>
<technology name="AA02">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24AA02/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331272" constant="no"/>
<attribute name="OC_NEWARK" value="89C9793" constant="no"/>
</technology>
<technology name="AA04">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA04/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331276" constant="no"/>
<attribute name="OC_NEWARK" value="92C6818" constant="no"/>
</technology>
<technology name="AA08">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA08-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1579568" constant="no"/>
<attribute name="OC_NEWARK" value="92C6826" constant="no"/>
</technology>
<technology name="AA128">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA128-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="92C6842" constant="no"/>
</technology>
<technology name="AA16">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA16-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331289" constant="no"/>
<attribute name="OC_NEWARK" value="96K4056" constant="no"/>
</technology>
<technology name="AA256">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24AA256T-I/SM" constant="no"/>
<attribute name="OC_FARNELL" value="1579570" constant="no"/>
<attribute name="OC_NEWARK" value="08N6838" constant="no"/>
</technology>
<technology name="AA32A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA32A-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1617659" constant="no"/>
<attribute name="OC_NEWARK" value="83C5815" constant="no"/>
</technology>
<technology name="AA64">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA64-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1331304" constant="no"/>
<attribute name="OC_NEWARK" value="85C2288" constant="no"/>
</technology>
<technology name="C08B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="AT24C08BN-SH-B" constant="no"/>
<attribute name="OC_FARNELL" value="1362645" constant="no"/>
<attribute name="OC_NEWARK" value="50M3318" constant="no"/>
</technology>
<technology name="C16B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="AT24C16BN-SH-B" constant="no"/>
<attribute name="OC_FARNELL" value="1362651" constant="no"/>
<attribute name="OC_NEWARK" value="50M3324" constant="no"/>
</technology>
<technology name="C32A">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="IS24C32A-2GLI" constant="no"/>
<attribute name="OC_FARNELL" value="1224413" constant="no"/>
<attribute name="OC_NEWARK" value="43M4588" constant="no"/>
</technology>
<technology name="CL04B">
<attribute name="MF" value="RAMTRON INTERNATIONAL CORP" constant="no"/>
<attribute name="MPN" value="FM24CL04-G" constant="no"/>
<attribute name="OC_FARNELL" value="1607928" constant="no"/>
<attribute name="OC_NEWARK" value="10J0444" constant="no"/>
</technology>
<technology name="LC024">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC024/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1659744" constant="no"/>
<attribute name="OC_NEWARK" value="92C7092" constant="no"/>
</technology>
<technology name="LC025">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC025/SN" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="92C7103" constant="no"/>
</technology>
<technology name="LC08B">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24LC08B/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1212669" constant="no"/>
<attribute name="OC_NEWARK" value="12C2005" constant="no"/>
</technology>
<technology name="LC128">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC128-I/SNG" constant="no"/>
<attribute name="OC_FARNELL" value="9757937" constant="no"/>
<attribute name="OC_NEWARK" value="30H1511" constant="no"/>
</technology>
<technology name="LC16B">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC16B/SN" constant="no"/>
<attribute name="OC_FARNELL" value="9757945" constant="no"/>
<attribute name="OC_NEWARK" value="12C2012" constant="no"/>
</technology>
<technology name="LC256">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC256-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="9757996" constant="no"/>
<attribute name="OC_NEWARK" value="27C9144" constant="no"/>
</technology>
<technology name="LC32A">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC32A/SN" constant="no"/>
<attribute name="OC_FARNELL" value="9758003" constant="no"/>
<attribute name="OC_NEWARK" value="33C2976" constant="no"/>
</technology>
<technology name="LC64">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC64-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="9758070" constant="no"/>
<attribute name="OC_NEWARK" value="12C2020" constant="no"/>
</technology>
<technology name="LCS52">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LCS52-I/SN" constant="no"/>
<attribute name="OC_FARNELL" value="1816066" constant="no"/>
<attribute name="OC_NEWARK" value="92C7032" constant="no"/>
</technology>
</technologies>
</device>
<device name="ST" package="TSSOP8">
<connects>
<connect gate="G$1" pin="A0" pad="1"/>
<connect gate="G$1" pin="A1" pad="2"/>
<connect gate="G$1" pin="A2" pad="3"/>
<connect gate="G$1" pin="GND" pad="4"/>
<connect gate="G$1" pin="SCL" pad="6"/>
<connect gate="G$1" pin="SDA" pad="5"/>
<connect gate="G$1" pin="VCC" pad="8"/>
<connect gate="G$1" pin="WP" pad="7"/>
</connects>
<technologies>
<technology name="AA128">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24AA128-I/ST" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="92C6843" constant="no"/>
</technology>
<technology name="AA64">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="25AA640A-I/ST" constant="no"/>
<attribute name="OC_FARNELL" value="1818513" constant="no"/>
<attribute name="OC_NEWARK" value="27M1300" constant="no"/>
</technology>
<technology name="C64">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="CAT24C64YI-GT3" constant="no"/>
<attribute name="OC_FARNELL" value="1718133" constant="no"/>
<attribute name="OC_NEWARK" value="08R5418" constant="no"/>
</technology>
<technology name="LC024">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="24LC024H-I/ST" constant="no"/>
<attribute name="OC_FARNELL" value="1659745" constant="no"/>
<attribute name="OC_NEWARK" value="77M3584" constant="no"/>
</technology>
<technology name="LC025">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC025-I/ST" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="92C7100" constant="no"/>
</technology>
<technology name="LC128">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC128-I/ST" constant="no"/>
<attribute name="OC_FARNELL" value="1296573" constant="no"/>
<attribute name="OC_NEWARK" value="62K0578" constant="no"/>
</technology>
<technology name="LC64">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LC64X-I/ST" constant="no"/>
<attribute name="OC_FARNELL" value="1296582" constant="no"/>
<attribute name="OC_NEWARK" value="96K4081" constant="no"/>
</technology>
<technology name="LCS52">
<attribute name="MF" value="MICROCHIP" constant="no"/>
<attribute name="MPN" value="24LCS52T/ST" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="92C7040" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BMP085" prefix="DD">
<description>&lt;b&gt;BMP085 Pressure Sensor&lt;/b&gt; Great little MEMS pressure sensor. SKU: COM-09603</description>
<gates>
<gate name="G$1" symbol="BMP085" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BMP085">
<connects>
<connect gate="G$1" pin="EOC" pad="2"/>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="NC" pad="5"/>
<connect gate="G$1" pin="SCL" pad="6"/>
<connect gate="G$1" pin="SDA" pad="7"/>
<connect gate="G$1" pin="VDDA" pad="3"/>
<connect gate="G$1" pin="VDDD" pad="4"/>
<connect gate="G$1" pin="XCLR" pad="8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="POLYSWITCH" prefix="F">
<description>&lt;b&gt;Resettable Fuse PTC&lt;/b&gt;
Resettable Fuse. Spark Fun Electronics SKU : COM-08357</description>
<gates>
<gate name="G$1" symbol="PTC" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1812">
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
<deviceset name="BZV55" prefix="VD">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
high speed</description>
<gates>
<gate name="G$1" symbol="D" x="0" y="0"/>
</gates>
<devices>
<device name="-C3V3" package="SOD80C">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
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
<deviceset name="6V">
<gates>
<gate name="6V" symbol="5V" x="0" y="0"/>
</gates>
<devices>
<device name="">
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
<deviceset name="INA194" prefix="IC">
<description>&lt;b&gt;High-Side Measurement Current Shunt Monitor&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="INA194" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT23-5">
<connects>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="IN+" pad="3"/>
<connect gate="G$1" pin="IN-" pad="4"/>
<connect gate="G$1" pin="OUT" pad="1"/>
<connect gate="G$1" pin="V+" pad="5"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="TEXAS INSTRUMENTS" constant="no"/>
<attribute name="MPN" value="INA168NA/250" constant="no"/>
<attribute name="OC_FARNELL" value="4375737" constant="no"/>
<attribute name="OC_NEWARK" value="35C1744" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="1X2" prefix="XP">
<description>Standard 1x2 header.</description>
<gates>
<gate name="G$1" symbol="JUMPER-2" x="0" y="2.54"/>
</gates>
<devices>
<device name="PSEUDOSMD" package="1X2-PSEUDOSMD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="DIP" package="1X02">
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
<deviceset name="MPXV5010DP" prefix="DA">
<gates>
<gate name="G$1" symbol="MPXV5010DP" x="0" y="0"/>
</gates>
<devices>
<device name="" package="482">
<connects>
<connect gate="G$1" pin="GND" pad="3"/>
<connect gate="G$1" pin="OUT" pad="4"/>
<connect gate="G$1" pin="VCC" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RESISTOR" prefix="R" uservalue="yes">
<description>&lt;b&gt;Resistor&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="1206" package="R1206">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="0805" package="R0805">
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
<deviceset name="LM1117DTX" prefix="DA" uservalue="yes">
<description>&lt;b&gt;Voltage Regulator LM1117&lt;/b&gt;
Standard adjustable voltage regulator but in SMD form. Spark Fun Electronics SKU : COM-00595</description>
<gates>
<gate name="G$1" symbol="78ADJ-3PIN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO252">
<connects>
<connect gate="G$1" pin="ADJ" pad="1"/>
<connect gate="G$1" pin="IN" pad="2"/>
<connect gate="G$1" pin="OUT" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LP2985" prefix="DA">
<gates>
<gate name="G$1" symbol="LP2980" x="2.54" y="0"/>
</gates>
<devices>
<device name="" package="SOT23-5">
<connects>
<connect gate="G$1" pin="BYPASS" pad="4"/>
<connect gate="G$1" pin="EN" pad="3"/>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="IN" pad="1"/>
<connect gate="G$1" pin="OUT" pad="5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ADIS16480" prefix="DD">
<gates>
<gate name="G$1" symbol="ADIS16480" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ADIS16480">
<connects>
<connect gate="G$1" pin="!CS" pad="20"/>
<connect gate="G$1" pin="!RST" pad="18"/>
<connect gate="G$1" pin="DIN" pad="19"/>
<connect gate="G$1" pin="DIO1" pad="17"/>
<connect gate="G$1" pin="DIO2" pad="15"/>
<connect gate="G$1" pin="DIO3" pad="23"/>
<connect gate="G$1" pin="DIO4" pad="24"/>
<connect gate="G$1" pin="DOUT" pad="22"/>
<connect gate="G$1" pin="GND@1" pad="11"/>
<connect gate="G$1" pin="GND@2" pad="12"/>
<connect gate="G$1" pin="GND@3" pad="9"/>
<connect gate="G$1" pin="SCLK" pad="21"/>
<connect gate="G$1" pin="VDD@1" pad="16"/>
<connect gate="G$1" pin="VDD@2" pad="13"/>
<connect gate="G$1" pin="VDD@3" pad="14"/>
<connect gate="G$1" pin="VDDRTC" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MAX44246" prefix="DA">
<description>Low-noise, high-speed rail-to-rail CMOS op-amp</description>
<gates>
<gate name=":1" symbol="MAX44246" x="-22.86" y="2.54"/>
<gate name=":2" symbol="MAX44246_2" x="20.32" y="0"/>
</gates>
<devices>
<device name="" package="MSOP8">
<connects>
<connect gate=":1" pin="+IN" pad="3"/>
<connect gate=":1" pin="+V" pad="8"/>
<connect gate=":1" pin="-IN" pad="2"/>
<connect gate=":1" pin="-V" pad="4"/>
<connect gate=":1" pin="OUT" pad="1"/>
<connect gate=":2" pin="+IN" pad="5"/>
<connect gate=":2" pin="-IN" pad="6"/>
<connect gate=":2" pin="OUT" pad="7"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="AD22100" prefix="DA">
<gates>
<gate name="G$1" symbol="AD22100" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TO92">
<connects>
<connect gate="G$1" pin="GND" pad="3"/>
<connect gate="G$1" pin="OUT" pad="2"/>
<connect gate="G$1" pin="VDD" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MPU-9150" prefix="DD" uservalue="yes">
<description>9DOF (3mag, 3accel, 3rotat). I2C interface.</description>
<gates>
<gate name="G$1" symbol="MPU-9150" x="0" y="0"/>
</gates>
<devices>
<device name="QFN-24-NP" package="QFN-24-NP">
<connects>
<connect gate="G$1" pin="AD0" pad="9"/>
<connect gate="G$1" pin="CLKIN" pad="1"/>
<connect gate="G$1" pin="CPOUT" pad="20"/>
<connect gate="G$1" pin="E_SCL" pad="7"/>
<connect gate="G$1" pin="E_SDA" pad="6"/>
<connect gate="G$1" pin="FSYNC" pad="11"/>
<connect gate="G$1" pin="GND@15" pad="15"/>
<connect gate="G$1" pin="GND@17" pad="17"/>
<connect gate="G$1" pin="GND@18" pad="18"/>
<connect gate="G$1" pin="INT" pad="12"/>
<connect gate="G$1" pin="REGOUT" pad="10"/>
<connect gate="G$1" pin="SCL" pad="23"/>
<connect gate="G$1" pin="SDA" pad="24"/>
<connect gate="G$1" pin="VDD@13" pad="13"/>
<connect gate="G$1" pin="VDD@3" pad="3"/>
<connect gate="G$1" pin="VLOGIC" pad="8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LSM303DLHC" prefix="DD">
<description>I2C accelerometer/magnetometer/tilt compensated compass</description>
<gates>
<gate name="G$1" symbol="LSM303DLHC" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LGA14">
<connects>
<connect gate="G$1" pin="C1" pad="6"/>
<connect gate="G$1" pin="DRDY" pad="9"/>
<connect gate="G$1" pin="GND@1" pad="7"/>
<connect gate="G$1" pin="GND@2" pad="10"/>
<connect gate="G$1" pin="GND@3" pad="11"/>
<connect gate="G$1" pin="INT1" pad="5"/>
<connect gate="G$1" pin="INT2" pad="4"/>
<connect gate="G$1" pin="SCL" pad="2"/>
<connect gate="G$1" pin="SDA" pad="3"/>
<connect gate="G$1" pin="SETC" pad="13"/>
<connect gate="G$1" pin="SETP" pad="12"/>
<connect gate="G$1" pin="VDD" pad="14"/>
<connect gate="G$1" pin="VDD_IO" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="AD5200" prefix="DA">
<gates>
<gate name="G$1" symbol="AD52XX" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MSOP10">
<connects>
<connect gate="G$1" pin="!CS" pad="4"/>
<connect gate="G$1" pin="!SHDN" pad="7"/>
<connect gate="G$1" pin="A" pad="10"/>
<connect gate="G$1" pin="B" pad="1"/>
<connect gate="G$1" pin="CLK" pad="6"/>
<connect gate="G$1" pin="GND" pad="3"/>
<connect gate="G$1" pin="SDI" pad="5"/>
<connect gate="G$1" pin="VDD" pad="8"/>
<connect gate="G$1" pin="VSS" pad="2"/>
<connect gate="G$1" pin="W" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BAR43" prefix="VD">
<description>&lt;b&gt;Silicon Schottky Diodes&lt;/b&gt;&lt;p&gt;
General-purpose diode</description>
<gates>
<gate name="1" symbol="DIODE_SCHOTTKY" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT23-3">
<connects>
<connect gate="1" pin="A" pad="1"/>
<connect gate="1" pin="C" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="M05X2" prefix="JP">
<description>&lt;b&gt;Header 5x2&lt;/b&gt;
Standard 10-pin dual row 0.1" header. Commonly used with AVR-ISP. Use with Spark Fun Electronics SKU: PRT-00778</description>
<gates>
<gate name="G$1" symbol="M05X2" x="0" y="0"/>
</gates>
<devices>
<device name="PTH" package="AVR_ICSP">
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
<device name="RA" package="2X5-RA">
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
<device name="RAF" package="2X5-RAF">
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
<device name="SHD" package="2X5-SHROUDED">
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
<device name="SHD_LOCK" package="2X5-SHROUDED_LOCK">
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
<device name="SHD_SMD" package="2X5-SHROUDED_SMD">
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
<device name="IONISTOR" package="CAP-IONISTOR-5MM">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
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
<package name="EIA3528-KIT">
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
<package name="EIA3216-KIT">
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
<package name="SJ_3">
<wire x1="1.27" y1="-1.016" x2="-1.27" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.27" y1="1.016" x2="1.524" y2="0.762" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="0.762" x2="-1.27" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="-0.762" x2="-1.27" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="1.27" y1="-1.016" x2="1.524" y2="-0.762" width="0.1524" layer="21" curve="90"/>
<wire x1="1.524" y1="-0.762" x2="1.524" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-0.762" x2="-1.524" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="1.016" x2="1.27" y2="1.016" width="0.1524" layer="21"/>
<smd name="1" x="-0.889" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<smd name="2" x="0" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<smd name="3" x="0.889" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.1001" y="0" size="0.02" layer="27">&gt;VALUE</text>
<text x="-1.27" y="-1.905" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X03">
<wire x1="3.81" y1="0.635" x2="4.445" y2="1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.715" y2="1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="1.27" x2="6.35" y2="0.635" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-0.635" x2="5.715" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="5.715" y1="-1.27" x2="4.445" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="6.35" y1="0.635" x2="6.35" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="3" x="5.08" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="4.826" y1="-0.254" x2="5.334" y2="0.254" layer="51"/>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="SJ_3_PASTE1&amp;2">
<wire x1="1.27" y1="-1.016" x2="-1.27" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.27" y1="1.016" x2="1.524" y2="0.762" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="0.762" x2="-1.27" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="-0.762" x2="-1.27" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="1.27" y1="-1.016" x2="1.524" y2="-0.762" width="0.1524" layer="21" curve="90"/>
<wire x1="1.524" y1="-0.762" x2="1.524" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-0.762" x2="-1.524" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="1.016" x2="1.27" y2="1.016" width="0.1524" layer="21"/>
<wire x1="0.1905" y1="0.508" x2="-1.016" y2="0.508" width="0.127" layer="51"/>
<wire x1="-1.016" y1="0.508" x2="-1.016" y2="-0.508" width="0.127" layer="51"/>
<wire x1="-1.016" y1="-0.508" x2="0.1905" y2="-0.508" width="0.127" layer="51"/>
<wire x1="0.1905" y1="-0.508" x2="0.1905" y2="0.508" width="0.127" layer="51"/>
<smd name="1" x="-0.8128" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<smd name="2" x="0" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<smd name="3" x="0.8128" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.1001" y="0" size="0.02" layer="27">&gt;VALUE</text>
<text x="-1.27" y="-1.905" size="0.4064" layer="27">&gt;VALUE</text>
<text x="-0.762" y="-0.4445" size="0.254" layer="51" rot="R40">PASTE</text>
<rectangle x1="-1.4478" y1="-1.016" x2="0.2794" y2="0.9398" layer="31"/>
</package>
<package name="SJ_3_PASTE2&amp;3">
<wire x1="1.27" y1="-1.016" x2="-1.27" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="1.27" y1="1.016" x2="1.524" y2="0.762" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="0.762" x2="-1.27" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-1.524" y1="-0.762" x2="-1.27" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="1.27" y1="-1.016" x2="1.524" y2="-0.762" width="0.1524" layer="21" curve="90"/>
<wire x1="1.524" y1="-0.762" x2="1.524" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-1.524" y1="-0.762" x2="-1.524" y2="0.762" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="1.016" x2="1.27" y2="1.016" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.508" x2="-0.1905" y2="0.508" width="0.127" layer="51"/>
<wire x1="-0.1905" y1="0.508" x2="-0.1905" y2="-0.508" width="0.127" layer="51"/>
<wire x1="-0.1905" y1="-0.508" x2="1.016" y2="-0.508" width="0.127" layer="51"/>
<wire x1="1.016" y1="-0.508" x2="1.016" y2="0.508" width="0.127" layer="51"/>
<smd name="1" x="-0.8128" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<smd name="2" x="0" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<smd name="3" x="0.8128" y="0" dx="0.635" dy="1.27" layer="1" cream="no"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.1001" y="0" size="0.02" layer="27">&gt;VALUE</text>
<text x="-1.27" y="-1.905" size="0.4064" layer="27">&gt;VALUE</text>
<text x="0.0635" y="-0.4445" size="0.254" layer="51" rot="R40">PASTE</text>
<rectangle x1="-0.2794" y1="-1.016" x2="1.4224" y2="0.9906" layer="31"/>
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
<package name="BATTERY-AAA">
<wire x1="-13.97" y1="3.81" x2="-13.97" y2="-3.81" width="0.127" layer="51"/>
<wire x1="-13.97" y1="-3.81" x2="-23.495" y2="-3.81" width="0.127" layer="51"/>
<wire x1="-23.495" y1="-3.81" x2="-23.495" y2="3.81" width="0.127" layer="51"/>
<wire x1="-23.495" y1="3.81" x2="-13.97" y2="3.81" width="0.127" layer="51"/>
<wire x1="23.368" y1="3.81" x2="13.97" y2="3.81" width="0.127" layer="51"/>
<wire x1="13.97" y1="3.81" x2="13.97" y2="-3.81" width="0.127" layer="51"/>
<wire x1="13.97" y1="-3.81" x2="23.368" y2="-3.81" width="0.127" layer="51"/>
<wire x1="23.368" y1="-3.81" x2="23.368" y2="3.81" width="0.127" layer="51"/>
<wire x1="-12.7" y1="3.81" x2="12.7" y2="3.81" width="0.127" layer="51"/>
<wire x1="12.7" y1="-3.81" x2="-12.7" y2="-3.81" width="0.127" layer="51"/>
<pad name="PWR@2" x="-13.97" y="0" drill="1.7018"/>
<pad name="PWR@1" x="-21.59" y="0" drill="1.7018"/>
<pad name="GND@2" x="13.97" y="0" drill="1.7018"/>
<pad name="GND@1" x="21.59" y="0" drill="1.7018"/>
<text x="-11.43" y="-1.27" size="2.54" layer="21" ratio="12">+</text>
<text x="8.89" y="-1.27" size="2.54" layer="21" ratio="12">-</text>
</package>
<package name="BATTERY">
<description>&lt;B&gt;BATTERY&lt;/B&gt;&lt;p&gt;
22 mm</description>
<wire x1="0.635" y1="2.54" x2="0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-3.175" x2="2.54" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-2.54" x2="1.905" y2="-3.81" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="11.43" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="10.2362" width="0.1524" layer="21"/>
<pad name="-" x="-5.715" y="0" drill="1.016" shape="long"/>
<pad name="+" x="9.525" y="-5.08" drill="1.016" shape="long"/>
<pad name="+@1" x="9.525" y="5.08" drill="1.016" shape="long"/>
<text x="-4.1656" y="6.35" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-4.445" y="3.81" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-0.635" y1="-1.27" x2="0" y2="1.27" layer="21"/>
</package>
<package name="BATTERY-AA">
<wire x1="-17.526" y1="-4.826" x2="-27.051" y2="-4.826" width="0.254" layer="41"/>
<wire x1="-27.051" y1="-4.826" x2="-27.051" y2="4.826" width="0.254" layer="41"/>
<wire x1="-27.051" y1="4.826" x2="-17.526" y2="4.826" width="0.254" layer="41"/>
<wire x1="27.051" y1="4.826" x2="17.526" y2="4.826" width="0.254" layer="21"/>
<wire x1="17.526" y1="-4.826" x2="27.051" y2="-4.826" width="0.254" layer="21"/>
<wire x1="27.051" y1="-4.826" x2="27.051" y2="4.826" width="0.254" layer="21"/>
<wire x1="-26.67" y1="7.62" x2="26.67" y2="7.62" width="0.127" layer="51"/>
<wire x1="26.67" y1="-7.62" x2="-26.67" y2="-7.62" width="0.127" layer="51"/>
<wire x1="-17.526" y1="4.826" x2="-17.526" y2="-4.826" width="0.254" layer="41"/>
<wire x1="17.526" y1="4.826" x2="17.526" y2="2.159" width="0.254" layer="21"/>
<wire x1="17.526" y1="-2.159" x2="17.526" y2="-4.826" width="0.254" layer="21"/>
<wire x1="-17.526" y1="-4.826" x2="-27.051" y2="-4.826" width="0.254" layer="21"/>
<wire x1="-27.051" y1="-4.826" x2="-27.051" y2="4.826" width="0.254" layer="21"/>
<wire x1="-27.051" y1="4.826" x2="-17.526" y2="4.826" width="0.254" layer="21"/>
<wire x1="-17.526" y1="4.826" x2="-17.526" y2="2.159" width="0.254" layer="21"/>
<wire x1="-17.526" y1="-2.159" x2="-17.526" y2="-4.826" width="0.254" layer="21"/>
<wire x1="17.526" y1="4.826" x2="27.051" y2="4.826" width="0.254" layer="41"/>
<wire x1="27.051" y1="4.826" x2="27.051" y2="-4.826" width="0.254" layer="41"/>
<wire x1="27.051" y1="-4.826" x2="17.526" y2="-4.826" width="0.254" layer="41"/>
<wire x1="17.526" y1="-4.826" x2="17.526" y2="4.826" width="0.254" layer="41"/>
<pad name="PWR@2" x="-17.78" y="0" drill="1.8542" rot="R90"/>
<pad name="PWR@1" x="-25.146" y="0" drill="1.8542"/>
<pad name="GND@2" x="17.78" y="0" drill="1.8542"/>
<pad name="GND@1" x="25.146" y="0" drill="1.8542"/>
<text x="-14.732" y="-1.27" size="2.54" layer="21" ratio="12">+</text>
<text x="12.7" y="-1.27" size="2.54" layer="21" ratio="12">-</text>
</package>
<package name="BATTCON_12MM_PTH">
<wire x1="-6.35" y1="-3.81" x2="-3.81" y2="-6.35" width="0.2032" layer="21"/>
<wire x1="-3.81" y1="-6.35" x2="3.81" y2="-6.35" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-6.35" x2="6.35" y2="-3.81" width="0.2032" layer="21"/>
<wire x1="6.35" y1="-3.81" x2="6.35" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="-6.35" y1="-3.81" x2="-6.35" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="-6.35" y1="2.54" x2="-6.35" y2="4.064" width="0.2032" layer="21"/>
<wire x1="6.35" y1="2.54" x2="6.35" y2="4.064" width="0.2032" layer="21"/>
<wire x1="-3.175" y1="5.588" x2="3.175" y2="5.588" width="0.2032" layer="21" curve="102.56384"/>
<wire x1="-6.35" y1="4.064" x2="-3.175" y2="5.588" width="0.2032" layer="21" curve="-123.398919"/>
<wire x1="6.35" y1="4.064" x2="3.175" y2="5.588" width="0.2032" layer="21" curve="128.77667"/>
<pad name="VCC@1" x="-6.604" y="0" drill="1.8542" shape="square"/>
<pad name="VCC@2" x="6.604" y="0" drill="1.8542" shape="square"/>
<smd name="GND" x="0" y="0" dx="7.62" dy="7.62" layer="1"/>
<text x="-3.81" y="-3.81" size="0.4064" layer="25">&gt;NAME</text>
<text x="-3.81" y="-5.08" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="BATTCON_20MM">
<wire x1="-3.7" y1="-10.57" x2="3.7" y2="-10.57" width="0.2032" layer="21"/>
<wire x1="-3.7" y1="-10.57" x2="-10.5" y2="-4.5" width="0.2032" layer="21"/>
<wire x1="3.7" y1="-10.57" x2="10.5" y2="-4.5" width="0.2032" layer="21"/>
<wire x1="-5.3" y1="8.3" x2="5.3" y2="8.3" width="0.2032" layer="21" curve="69.999889"/>
<wire x1="10.5" y1="-4.5" x2="10.5" y2="-3.4" width="0.2032" layer="21"/>
<wire x1="-10.5" y1="-4.5" x2="-10.5" y2="-3.4" width="0.2032" layer="21"/>
<wire x1="-10.5" y1="6.3" x2="-5.3" y2="8.3" width="0.2032" layer="21" curve="-139.635474"/>
<wire x1="10.5" y1="6.3" x2="5.3" y2="8.3" width="0.2032" layer="21" curve="136.99875"/>
<wire x1="-10.5" y1="6.3" x2="-10.5" y2="3.4" width="0.2032" layer="21"/>
<wire x1="10.5" y1="6.3" x2="10.5" y2="3.4" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="10" width="0.2032" layer="51"/>
<smd name="2" x="0" y="0" dx="6.07" dy="6.07" layer="1"/>
<smd name="1" x="-12.5" y="0" dx="6.07" dy="6.07" layer="1"/>
<smd name="3" x="12.5" y="0" dx="6.07" dy="6.07" layer="1"/>
<text x="-6.985" y="0.635" size="0.4064" layer="25">&gt;NAME</text>
<text x="-6.985" y="-0.635" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="BATTCON_245MM">
<wire x1="-6.24" y1="-12.44" x2="6.24" y2="-12.44" width="0.2032" layer="21"/>
<wire x1="-6.24" y1="-12.44" x2="-13.04" y2="-8.24" width="0.2032" layer="21"/>
<wire x1="6.24" y1="-12.44" x2="13.04" y2="-8.24" width="0.2032" layer="21"/>
<wire x1="-7.84" y1="12.38" x2="7.94" y2="12.48" width="0.2032" layer="21" curve="94.032201"/>
<wire x1="13.04" y1="-8.24" x2="13.04" y2="-3" width="0.2032" layer="21"/>
<wire x1="-13.04" y1="-8.24" x2="-13.04" y2="-3" width="0.2032" layer="21"/>
<wire x1="-13.04" y1="10.38" x2="-7.84" y2="12.38" width="0.2032" layer="21" curve="-139.635474"/>
<wire x1="13.04" y1="10.38" x2="7.84" y2="12.38" width="0.2032" layer="21" curve="136.99875"/>
<wire x1="-13.04" y1="10.38" x2="-13.04" y2="3" width="0.2032" layer="21"/>
<wire x1="13.04" y1="10.38" x2="13.04" y2="3" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="12.25" width="0.2032" layer="51"/>
<smd name="2" x="0" y="0" dx="4.064" dy="4.064" layer="1"/>
<smd name="1" x="-15.367" y="0" dx="5.08" dy="5.08" layer="1"/>
<smd name="3" x="15.367" y="0" dx="5.08" dy="5.08" layer="1"/>
<text x="-9.525" y="0.635" size="0.4064" layer="25">&gt;NAME</text>
<text x="-9.525" y="-0.635" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="BATTCOM_20MM_PTH">
<wire x1="19" y1="-4" x2="19" y2="4" width="0.2032" layer="21" curve="-316.397181"/>
<wire x1="19" y1="4" x2="22" y2="4" width="0.2032" layer="21"/>
<wire x1="22" y1="4" x2="22" y2="-4" width="0.2032" layer="21"/>
<wire x1="22" y1="-4" x2="19" y2="-4" width="0.2032" layer="21"/>
<circle x="9.06" y="0.1" radius="10" width="0.2032" layer="51"/>
<pad name="2" x="0" y="0" drill="1.3" rot="R90"/>
<pad name="1" x="20" y="0" drill="1.3" rot="R90"/>
<text x="-6.985" y="0.635" size="0.4064" layer="25">&gt;NAME</text>
<text x="-6.985" y="-0.635" size="0.4064" layer="27">&gt;VALUE</text>
<text x="17.285" y="-0.6" size="1.27" layer="51">+</text>
<text x="1.95" y="-0.6" size="1.27" layer="51">-</text>
</package>
<package name="BATTCON_245MM_PTH">
<wire x1="-3.81" y1="-12.7" x2="3.81" y2="-12.7" width="0.2032" layer="21"/>
<wire x1="-3.81" y1="-12.7" x2="-12.7" y2="-6.35" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-12.7" x2="12.7" y2="-6.35" width="0.2032" layer="21"/>
<wire x1="-7.62" y1="9.779" x2="7.62" y2="9.779" width="0.2032" layer="21" curve="63.785901"/>
<wire x1="12.7" y1="-6.35" x2="12.7" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="-12.7" y1="-6.35" x2="-12.7" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="-12.7" y1="6.35" x2="-7.62" y2="9.779" width="0.2032" layer="21" curve="-123.780121"/>
<wire x1="12.7" y1="6.35" x2="7.62" y2="9.779" width="0.2032" layer="21" curve="123.773101"/>
<wire x1="-12.7" y1="6.35" x2="-12.7" y2="2.54" width="0.2032" layer="21"/>
<wire x1="12.7" y1="6.35" x2="12.7" y2="2.54" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="12.25" width="0.2032" layer="51"/>
<pad name="1" x="-12.7" y="0" drill="1.8542" shape="square"/>
<pad name="3" x="12.7" y="0" drill="1.8542" shape="square"/>
<smd name="2" x="0" y="0" dx="4.064" dy="4.064" layer="1"/>
<text x="-9.525" y="0.635" size="0.4064" layer="25">&gt;NAME</text>
<text x="-9.525" y="-0.635" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="LIPO-1100MAH">
<wire x1="-17" y1="-26" x2="17" y2="-26" width="0.2032" layer="51"/>
<wire x1="17" y1="-26" x2="17" y2="26" width="0.2032" layer="51"/>
<wire x1="17" y1="26" x2="-17" y2="26" width="0.2032" layer="51"/>
<wire x1="-17" y1="26" x2="-17" y2="-26" width="0.2032" layer="51"/>
<wire x1="-1" y1="34" x2="-1" y2="30" width="0.127" layer="51"/>
<wire x1="1" y1="34" x2="1" y2="30" width="0.127" layer="51"/>
<pad name="+" x="-5" y="32" drill="1.397" diameter="2.54"/>
<pad name="-" x="5" y="32" drill="1.397" diameter="2.54"/>
</package>
<package name="BATTERY-AA-PANEL">
<wire x1="29.46" y1="8.255" x2="-29.46" y2="8.255" width="0.127" layer="51"/>
<wire x1="-29.46" y1="8.255" x2="-29.46" y2="-8.255" width="0.127" layer="51"/>
<wire x1="-29.46" y1="-8.255" x2="29.46" y2="-8.255" width="0.127" layer="51"/>
<wire x1="29.46" y1="-8.255" x2="29.46" y2="8.255" width="0.127" layer="51"/>
<wire x1="24" y1="1" x2="24" y2="-1" width="0.25" layer="21"/>
<wire x1="23" y1="0" x2="25" y2="0" width="0.25" layer="21"/>
<wire x1="-25" y1="1" x2="-25" y2="-1" width="0.25" layer="21"/>
<pad name="-" x="-27.43" y="0" drill="1.17" diameter="2.3"/>
<pad name="+" x="27.43" y="0" drill="1.17" diameter="2.3"/>
<text x="-29.5" y="8.5" size="0.4064" layer="25">&gt;NAME</text>
<text x="-29.5" y="-8.9" size="0.4064" layer="27">&gt;VALUE</text>
<text x="-6" y="7" size="0.6096" layer="49">(layout parts on top layer)</text>
<hole x="17.27" y="0" drill="3.18"/>
<hole x="-17.27" y="0" drill="3.18"/>
<hole x="27.43" y="7.47" drill="1.7"/>
</package>
<package name="BATTERY_20MM_PTH_COMPACT">
<wire x1="-3.7" y1="-9.9" x2="3.7" y2="-9.9" width="0.2032" layer="21"/>
<wire x1="-3.7" y1="-9.9" x2="-10.5" y2="-5.7" width="0.2032" layer="21"/>
<wire x1="3.7" y1="-9.9" x2="10.5" y2="-5.7" width="0.2032" layer="21"/>
<wire x1="-5.3" y1="7.3" x2="5.4" y2="7.4" width="0.2032" layer="21" curve="94.031579"/>
<wire x1="10.5" y1="-5.7" x2="10.5" y2="-3.5" width="0.2032" layer="21"/>
<wire x1="-10.5" y1="-5.7" x2="-10.5" y2="-3.5" width="0.2032" layer="21"/>
<wire x1="-5.3" y1="7.3" x2="-10.5" y2="5.3" width="0.2032" layer="21" curve="139.635474"/>
<wire x1="10.5" y1="5.3" x2="5.3" y2="7.3" width="0.2032" layer="21" curve="137.002565"/>
<wire x1="-10.5" y1="5.3" x2="-10.5" y2="3.5" width="0.2032" layer="21"/>
<wire x1="10.5" y1="5.3" x2="10.5" y2="3.5" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="10" width="0.2032" layer="51"/>
<pad name="1" x="-10.5" y="0" drill="1.8542" shape="long" rot="R90"/>
<pad name="3" x="10.5" y="0" drill="1.8542" shape="long" rot="R90"/>
<smd name="2" x="0" y="0" dx="4.064" dy="4.064" layer="1"/>
<text x="-6.985" y="0.635" size="0.4064" layer="25">&gt;NAME</text>
<text x="-6.985" y="-0.635" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="BATTCON_12MM">
<wire x1="-6.096" y1="4.318" x2="-3.81" y2="5.334" width="0.127" layer="21" curve="-90"/>
<wire x1="3.81" y1="5.334" x2="6.096" y2="4.318" width="0.127" layer="21" curve="-90"/>
<wire x1="6.096" y1="4.318" x2="6.096" y2="-3.302" width="0.127" layer="21"/>
<wire x1="6.096" y1="-3.302" x2="3.048" y2="-6.35" width="0.127" layer="21"/>
<wire x1="3.048" y1="-6.35" x2="-3.048" y2="-6.35" width="0.127" layer="21"/>
<wire x1="-3.048" y1="-6.35" x2="-6.096" y2="-3.302" width="0.127" layer="21"/>
<wire x1="-6.096" y1="-3.302" x2="-6.096" y2="4.318" width="0.127" layer="21"/>
<wire x1="3.81" y1="5.334" x2="-3.81" y2="5.334" width="0.127" layer="21" curve="-90"/>
<smd name="GND" x="0" y="0" dx="3.9624" dy="3.9624" layer="1"/>
<smd name="PWR@1" x="-7.874" y="0" dx="3.175" dy="3.175" layer="1"/>
<smd name="PWR@2" x="7.874" y="0" dx="3.175" dy="3.175" layer="1"/>
</package>
<package name="BATTCON_20MM_4LEGS">
<wire x1="-7.5" y1="7.35" x2="7.5" y2="7.35" width="0.2032" layer="21"/>
<wire x1="-7.5" y1="7.35" x2="-10.55" y2="4.65" width="0.2032" layer="21"/>
<wire x1="7.5" y1="7.35" x2="10.55" y2="4.65" width="0.2032" layer="21"/>
<wire x1="10.55" y1="2.55" x2="10.55" y2="0.55" width="0.2032" layer="51"/>
<wire x1="10.55" y1="-0.55" x2="10.55" y2="-2.55" width="0.2032" layer="51"/>
<wire x1="-10.55" y1="2.55" x2="-10.55" y2="0.55" width="0.2032" layer="51"/>
<wire x1="-10.55" y1="-0.55" x2="-10.55" y2="-2.55" width="0.2032" layer="51"/>
<wire x1="10.55" y1="2.55" x2="11.45" y2="2.55" width="0.2032" layer="51"/>
<wire x1="11.45" y1="2.55" x2="11.45" y2="0.55" width="0.2032" layer="51"/>
<wire x1="11.45" y1="0.55" x2="10.55" y2="0.55" width="0.2032" layer="51"/>
<wire x1="10.55" y1="-0.55" x2="11.45" y2="-0.55" width="0.2032" layer="51"/>
<wire x1="11.45" y1="-0.55" x2="11.45" y2="-2.55" width="0.2032" layer="51"/>
<wire x1="11.45" y1="-2.55" x2="10.55" y2="-2.55" width="0.2032" layer="51"/>
<wire x1="-10.55" y1="-2.55" x2="-11.45" y2="-2.55" width="0.2032" layer="51"/>
<wire x1="-11.45" y1="-2.55" x2="-11.45" y2="-0.55" width="0.2032" layer="51"/>
<wire x1="-11.45" y1="-0.55" x2="-10.55" y2="-0.55" width="0.2032" layer="51"/>
<wire x1="-10.55" y1="0.55" x2="-11.45" y2="0.55" width="0.2032" layer="51"/>
<wire x1="-11.45" y1="0.55" x2="-11.45" y2="2.55" width="0.2032" layer="51"/>
<wire x1="-11.45" y1="2.55" x2="-10.55" y2="2.55" width="0.2032" layer="51"/>
<wire x1="10.55" y1="-4.55" x2="5.55" y2="-7.95" width="0.2032" layer="21"/>
<wire x1="5.55" y1="-7.95" x2="-5.55" y2="-7.95" width="0.2032" layer="21" curve="62.415735"/>
<wire x1="-5.55" y1="-7.95" x2="-10.55" y2="-4.55" width="0.2032" layer="21"/>
<wire x1="10.55" y1="4.65" x2="10.55" y2="3.2" width="0.2032" layer="21"/>
<wire x1="-10.55" y1="3.2" x2="-10.55" y2="4.65" width="0.2032" layer="21"/>
<wire x1="-10.55" y1="-4.55" x2="-10.55" y2="-3.2" width="0.2032" layer="21"/>
<wire x1="10.55" y1="-4.55" x2="10.55" y2="-3.2" width="0.2032" layer="21"/>
<circle x="0" y="0" radius="10" width="0.2032" layer="51"/>
<smd name="1" x="-11" y="1.55" dx="2.54" dy="1.778" layer="1" rot="R90"/>
<smd name="2" x="0" y="0" dx="13" dy="8" layer="1" roundness="100" cream="no"/>
<smd name="3" x="11" y="1.55" dx="2.54" dy="1.778" layer="1" rot="R90"/>
<smd name="P$1" x="-11" y="-1.55" dx="2.54" dy="1.778" layer="1" rot="R90"/>
<smd name="P$2" x="11" y="-1.55" dx="2.54" dy="1.778" layer="1" rot="R90"/>
<text x="-0.889" y="5.969" size="0.4064" layer="25">&gt;NAME</text>
<text x="-0.889" y="4.699" size="0.4064" layer="27">&gt;VALUE</text>
<rectangle x1="-2" y1="-2" x2="2" y2="2" layer="31"/>
</package>
<package name="BATTERY-AA-KIT">
<wire x1="-17.526" y1="-4.826" x2="-27.051" y2="-4.826" width="0.254" layer="41"/>
<wire x1="-27.051" y1="-4.826" x2="-27.051" y2="4.826" width="0.254" layer="41"/>
<wire x1="-27.051" y1="4.826" x2="-17.526" y2="4.826" width="0.254" layer="41"/>
<wire x1="27.051" y1="4.826" x2="17.526" y2="4.826" width="0.254" layer="21"/>
<wire x1="17.526" y1="-4.826" x2="27.051" y2="-4.826" width="0.254" layer="21"/>
<wire x1="27.051" y1="-4.826" x2="27.051" y2="4.826" width="0.254" layer="21"/>
<wire x1="-26.67" y1="7.62" x2="26.67" y2="7.62" width="0.127" layer="51"/>
<wire x1="26.67" y1="-7.62" x2="-26.67" y2="-7.62" width="0.127" layer="51"/>
<wire x1="-17.526" y1="4.826" x2="-17.526" y2="-4.826" width="0.254" layer="41"/>
<wire x1="-17.526" y1="-4.826" x2="-27.051" y2="-4.826" width="0.254" layer="21"/>
<wire x1="-27.051" y1="-4.826" x2="-27.051" y2="4.826" width="0.254" layer="21"/>
<wire x1="-27.051" y1="4.826" x2="-17.526" y2="4.826" width="0.254" layer="21"/>
<wire x1="17.526" y1="4.826" x2="27.051" y2="4.826" width="0.254" layer="41"/>
<wire x1="27.051" y1="4.826" x2="27.051" y2="-4.826" width="0.254" layer="41"/>
<wire x1="27.051" y1="-4.826" x2="17.526" y2="-4.826" width="0.254" layer="41"/>
<wire x1="17.526" y1="-4.826" x2="17.526" y2="4.826" width="0.254" layer="41"/>
<wire x1="-24.0157" y1="-0.0482" x2="-18.9129" y2="-0.0457" width="0.4064" layer="49"/>
<wire x1="18.9103" y1="-0.0482" x2="24.0131" y2="-0.0457" width="0.4064" layer="49"/>
<wire x1="13.97" y1="2.54" x2="-12.7" y2="2.54" width="0.4064" layer="21"/>
<wire x1="-12.7" y1="2.54" x2="-12.7" y2="0.5842" width="0.4064" layer="21"/>
<wire x1="-12.7" y1="0.5842" x2="-12.7" y2="-0.6858" width="0.4064" layer="21"/>
<wire x1="-12.7" y1="-0.6858" x2="-12.7" y2="-2.54" width="0.4064" layer="21"/>
<wire x1="-12.7" y1="-2.54" x2="13.97" y2="-2.54" width="0.4064" layer="21"/>
<wire x1="13.97" y1="-2.54" x2="13.97" y2="2.54" width="0.4064" layer="21"/>
<wire x1="-12.7" y1="0.5842" x2="-13.97" y2="0.5842" width="0.4064" layer="21"/>
<wire x1="-13.97" y1="0.5842" x2="-13.97" y2="-0.6858" width="0.4064" layer="21"/>
<wire x1="-13.97" y1="-0.6858" x2="-12.7" y2="-0.6858" width="0.4064" layer="21"/>
<wire x1="12.065" y1="0" x2="10.795" y2="0" width="0.4064" layer="21"/>
<wire x1="-9.525" y1="0" x2="-10.795" y2="0" width="0.4064" layer="21"/>
<wire x1="-10.16" y1="0.635" x2="-10.16" y2="-0.635" width="0.4064" layer="21"/>
<pad name="GND@1" x="25.146" y="0" drill="1.8542" stop="no"/>
<pad name="GND@2" x="18.034" y="0" drill="1.8542" stop="no"/>
<pad name="PWR@1" x="-25.146" y="0" drill="1.8542" stop="no"/>
<pad name="PWR@2" x="-18.034" y="0" drill="1.8542" rot="R90" stop="no"/>
<polygon width="0.127" layer="30">
<vertex x="-23.8252" y="-0.0508" curve="90"/>
<vertex x="-25.146" y="1.3462" curve="90"/>
<vertex x="-26.4668" y="-0.0762" curve="90"/>
<vertex x="-25.146" y="-1.3462" curve="90"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-25.1206" y="-0.8636" curve="-90.090301"/>
<vertex x="-26.0096" y="-0.0508" curve="-90"/>
<vertex x="-25.1714" y="0.8636" curve="-89.987112"/>
<vertex x="-24.2824" y="0" curve="-90"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="26.4668" y="-0.0508" curve="90"/>
<vertex x="25.146" y="1.3462" curve="90"/>
<vertex x="23.8252" y="-0.0762" curve="90"/>
<vertex x="25.146" y="-1.3462" curve="90"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="25.1714" y="-0.8636" curve="-90.090301"/>
<vertex x="24.2824" y="-0.0508" curve="-90"/>
<vertex x="25.1206" y="0.8636" curve="-89.987112"/>
<vertex x="26.0096" y="0" curve="-90"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="-16.7132" y="-0.0508" curve="90"/>
<vertex x="-18.034" y="1.3462" curve="90"/>
<vertex x="-19.3548" y="-0.0762" curve="90"/>
<vertex x="-18.034" y="-1.3462" curve="90"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-18.0086" y="-0.8636" curve="-90.090301"/>
<vertex x="-18.8976" y="-0.0508" curve="-90"/>
<vertex x="-18.0594" y="0.8636" curve="-89.987112"/>
<vertex x="-17.1704" y="0" curve="-90"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="19.3548" y="-0.0508" curve="90"/>
<vertex x="18.034" y="1.3462" curve="90"/>
<vertex x="16.7132" y="-0.0762" curve="90"/>
<vertex x="18.034" y="-1.3462" curve="90"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="18.0594" y="-0.8636" curve="-90.090301"/>
<vertex x="17.1704" y="-0.0508" curve="-90"/>
<vertex x="18.0086" y="0.8636" curve="-89.987112"/>
<vertex x="18.8976" y="0" curve="-90"/>
</polygon>
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
<package name="CAP-PTH-SMALL-KIT">
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
<package name="LED-TRICOLOR-SMD">
<wire x1="-1.3" y1="1.3" x2="-1.6" y2="1.3" width="0.2032" layer="21"/>
<wire x1="-1.6" y1="1.3" x2="-1.6" y2="-1.3" width="0.2032" layer="21"/>
<wire x1="-1.6" y1="-1.3" x2="-1.3" y2="-1.3" width="0.2032" layer="21"/>
<wire x1="1.3" y1="1.3" x2="1.6" y2="1.3" width="0.2032" layer="21"/>
<wire x1="1.6" y1="1.3" x2="1.6" y2="-1.3" width="0.2032" layer="21"/>
<wire x1="1.6" y1="-1.3" x2="1.3" y2="-1.3" width="0.2032" layer="21"/>
<wire x1="0" y1="-1.6" x2="0" y2="-1.8" width="0.2032" layer="21"/>
<smd name="G" x="-0.7" y="1.5" dx="0.7" dy="1.2" layer="1"/>
<smd name="B" x="0.7" y="1.5" dx="0.7" dy="1.2" layer="1"/>
<smd name="R" x="-0.7" y="-1.5" dx="0.7" dy="1.2" layer="1"/>
<smd name="A" x="0.7" y="-1.5" dx="0.7" dy="1.2" layer="1"/>
<text x="-1.016" y="0.127" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.016" y="-0.635" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="STAND-OFF">
<description>&lt;b&gt;Stand Off&lt;/b&gt;&lt;p&gt;
This is the mechanical footprint for a #4 phillips button head screw. Use the keepout ring to avoid running the screw head into surrounding components. SKU : PRT-00447</description>
<wire x1="0" y1="1.8542" x2="0" y2="-1.8542" width="0.2032" layer="41" curve="-180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="41" curve="-180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="42" curve="180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="42" curve="-180"/>
<circle x="0" y="0" radius="2.794" width="0.127" layer="39"/>
<hole x="0" y="0" drill="3.302"/>
</package>
<package name="STAND-OFF-TIGHT">
<description>&lt;b&gt;Stand Off&lt;/b&gt;&lt;p&gt;
This is the mechanical footprint for a #4 phillips button head screw. Use the keepout ring to avoid running the screw head into surrounding components. SKU : PRT-00447</description>
<wire x1="0" y1="1.8542" x2="0" y2="-1.8542" width="0.2032" layer="41" curve="-180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="41" curve="-180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="42" curve="180"/>
<wire x1="0" y1="-1.8542" x2="0" y2="1.8542" width="0.2032" layer="42" curve="-180"/>
<circle x="0" y="0" radius="2.794" width="0.127" layer="39"/>
<hole x="0" y="0" drill="3.048"/>
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
<package name="AXIAL-0.3-KIT">
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
<symbol name="JUMPER-3">
<wire x1="0" y1="0" x2="0" y2="1.27" width="0.1524" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="1.27" width="0.4064" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="1.27" width="0.1524" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="1.27" width="0.4064" layer="94"/>
<wire x1="-0.635" y1="0" x2="2.54" y2="0" width="0.4064" layer="94"/>
<wire x1="2.54" y1="0" x2="5.08" y2="0" width="0.4064" layer="94"/>
<wire x1="5.08" y1="0" x2="5.715" y2="0" width="0.4064" layer="94"/>
<wire x1="5.715" y1="0" x2="5.715" y2="0.635" width="0.4064" layer="94"/>
<wire x1="5.715" y1="0.635" x2="-0.635" y2="0.635" width="0.4064" layer="94"/>
<wire x1="-0.635" y1="0.635" x2="-0.635" y2="0" width="0.4064" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="1.27" width="0.4064" layer="94"/>
<wire x1="5.08" y1="0" x2="5.08" y2="1.27" width="0.1524" layer="94"/>
<text x="-1.27" y="0" size="1.778" layer="95" rot="R90">&gt;NAME</text>
<text x="8.255" y="0" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="1" x="0" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="2" x="2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="3" x="5.08" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
<symbol name="BATTERY">
<wire x1="-1.27" y1="3.81" x2="-1.27" y2="-3.81" width="0.4064" layer="94"/>
<wire x1="0" y1="1.27" x2="0" y2="-1.27" width="0.4064" layer="94"/>
<wire x1="1.27" y1="3.81" x2="1.27" y2="-3.81" width="0.4064" layer="94"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="-1.27" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.524" y2="0" width="0.1524" layer="94"/>
<text x="-3.81" y="5.08" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-6.35" size="1.778" layer="96">&gt;VALUE</text>
<pin name="-" x="5.08" y="0" visible="off" length="short" direction="pwr" rot="R180"/>
<pin name="+" x="-5.08" y="0" visible="off" length="short" direction="pwr"/>
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
<symbol name="LED-TRICOLORSMD">
<wire x1="10.16" y1="2.54" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-7.62" x2="-7.62" y2="2.54" width="0.254" layer="94"/>
<wire x1="-7.62" y1="2.54" x2="10.16" y2="2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-3.81" x2="2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="2.54" y1="-1.27" x2="1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="2.54" y2="-3.81" width="0.254" layer="94"/>
<wire x1="1.27" y1="-3.81" x2="1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="0" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="3.81" y2="-2.54" width="0.254" layer="94"/>
<text x="-7.62" y="3.302" size="1.778" layer="95">&gt;NAME</text>
<text x="-7.62" y="-10.16" size="1.778" layer="95">&gt;VALUE</text>
<pin name="GRN" x="-10.16" y="-5.08" visible="pin" length="short"/>
<pin name="BLU" x="-10.16" y="-2.54" visible="pin" length="short"/>
<pin name="A" x="12.7" y="-2.54" visible="pin" length="short" rot="R180"/>
<pin name="RED" x="-10.16" y="0" visible="pin" length="short"/>
</symbol>
<symbol name="STAND-OFF">
<circle x="0" y="0" radius="1.27" width="0.254" layer="94"/>
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
<deviceset name="JUMPER-3" prefix="JP">
<gates>
<gate name="G$1" symbol="JUMPER-3" x="-2.54" y="0"/>
</gates>
<devices>
<device name="SMD" package="SJ_3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH" package="1X03">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1-2" package="SJ_3_PASTE1&amp;2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2-3" package="SJ_3_PASTE2&amp;3">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BATTERY" prefix="BAT" uservalue="yes">
<description>&lt;b&gt;Battery Holders&lt;/b&gt;
Various common sizes : AA, AAA, 20mm coin cell and 12mm coin cell.</description>
<gates>
<gate name="G$1" symbol="BATTERY" x="0" y="0"/>
</gates>
<devices>
<device name="AAA" package="BATTERY-AAA">
<connects>
<connect gate="G$1" pin="+" pad="PWR@1"/>
<connect gate="G$1" pin="-" pad="GND@1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="20PTH2" package="BATTERY">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AA" package="BATTERY-AA">
<connects>
<connect gate="G$1" pin="+" pad="PWR@1"/>
<connect gate="G$1" pin="-" pad="GND@1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="12PTH" package="BATTCON_12MM_PTH">
<connects>
<connect gate="G$1" pin="+" pad="VCC@1"/>
<connect gate="G$1" pin="-" pad="GND"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="20SMD" package="BATTCON_20MM">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="245MM" package="BATTCON_245MM">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="20PTH" package="BATTCOM_20MM_PTH">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="245PTH" package="BATTCON_245MM_PTH">
<connects>
<connect gate="G$1" pin="+" pad="3"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1100" package="LIPO-1100MAH">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AA-PANEL" package="BATTERY-AA-PANEL">
<connects>
<connect gate="G$1" pin="+" pad="+"/>
<connect gate="G$1" pin="-" pad="-"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="FOB" package="BATTERY_20MM_PTH_COMPACT">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="12MM" package="BATTCON_12MM">
<connects>
<connect gate="G$1" pin="+" pad="PWR@1"/>
<connect gate="G$1" pin="-" pad="GND"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="20MM_4LEGS" package="BATTCON_20MM_4LEGS">
<connects>
<connect gate="G$1" pin="+" pad="1"/>
<connect gate="G$1" pin="-" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AA-KIT" package="BATTERY-AA-KIT">
<connects>
<connect gate="G$1" pin="+" pad="PWR@1"/>
<connect gate="G$1" pin="-" pad="GND@1"/>
</connects>
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
<deviceset name="LED-TRICOLOR">
<description>&lt;b&gt;Tri-Color LED SMD&lt;/b&gt;
Proven layout and schematic for triple color LED in SMD package - common anode. Spark Fun Electronics SKU : COM-07844</description>
<gates>
<gate name="G$1" symbol="LED-TRICOLORSMD" x="0" y="2.54"/>
</gates>
<devices>
<device name="" package="LED-TRICOLOR-SMD">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="BLU" pad="B"/>
<connect gate="G$1" pin="GRN" pad="G"/>
<connect gate="G$1" pin="RED" pad="R"/>
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
<library name="transistor">
<packages>
<package name="SOT23">
<description>&lt;b&gt;SOT-23&lt;/b&gt;</description>
<wire x1="1.4224" y1="0.6604" x2="1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="1.4224" y1="-0.6604" x2="-1.4224" y2="-0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="-0.6604" x2="-1.4224" y2="0.6604" width="0.1524" layer="51"/>
<wire x1="-1.4224" y1="0.6604" x2="1.4224" y2="0.6604" width="0.1524" layer="51"/>
<smd name="3" x="0" y="1.1" dx="1" dy="1.4" layer="1"/>
<smd name="2" x="0.95" y="-1.1" dx="1" dy="1.4" layer="1"/>
<smd name="1" x="-0.95" y="-1.1" dx="1" dy="1.4" layer="1"/>
<text x="-1.905" y="1.905" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.2286" y1="0.7112" x2="0.2286" y2="1.2954" layer="51"/>
<rectangle x1="0.7112" y1="-1.2954" x2="1.1684" y2="-0.7112" layer="51"/>
<rectangle x1="-1.1684" y1="-1.2954" x2="-0.7112" y2="-0.7112" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="NPN">
<wire x1="2.54" y1="2.54" x2="0.508" y2="1.524" width="0.1524" layer="94"/>
<wire x1="1.778" y1="-1.524" x2="2.54" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="1.27" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.778" y2="-1.524" width="0.1524" layer="94"/>
<wire x1="1.54" y1="-2.04" x2="0.308" y2="-1.424" width="0.1524" layer="94"/>
<wire x1="1.524" y1="-2.413" x2="2.286" y2="-2.413" width="0.254" layer="94"/>
<wire x1="2.286" y1="-2.413" x2="1.778" y2="-1.778" width="0.254" layer="94"/>
<wire x1="1.778" y1="-1.778" x2="1.524" y2="-2.286" width="0.254" layer="94"/>
<wire x1="1.524" y1="-2.286" x2="1.905" y2="-2.286" width="0.254" layer="94"/>
<wire x1="1.905" y1="-2.286" x2="1.778" y2="-2.032" width="0.254" layer="94"/>
<text x="-10.16" y="7.62" size="1.778" layer="95">&gt;NAME</text>
<text x="-10.16" y="5.08" size="1.778" layer="96">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-2.54" x2="0.508" y2="2.54" layer="94"/>
<pin name="B" x="-2.54" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="E" x="2.54" y="-5.08" visible="off" length="short" direction="pas" swaplevel="3" rot="R90"/>
<pin name="C" x="2.54" y="5.08" visible="off" length="short" direction="pas" swaplevel="2" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="BC848" prefix="T">
<description>&lt;b&gt;NPN TRANSISTOR&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="NPN" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOT23">
<connects>
<connect gate="G$1" pin="B" pad="1"/>
<connect gate="G$1" pin="C" pad="3"/>
<connect gate="G$1" pin="E" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diode">
<packages>
<package name="DO13M">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 6.35 mm metall, horizontal, grid 20.32 mm</description>
<wire x1="-7.239" y1="3.175" x2="-7.239" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="-7.239" y1="-3.175" x2="1.905" y2="-3.175" width="0.1524" layer="21"/>
<wire x1="1.905" y1="3.175" x2="-7.239" y2="3.175" width="0.1524" layer="21"/>
<wire x1="7.239" y1="-1.27" x2="7.239" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-3.175" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="3.175" width="0.1524" layer="21"/>
<wire x1="10.16" y1="0" x2="8.636" y2="0" width="0.9144" layer="51"/>
<wire x1="-8.636" y1="0" x2="-10.16" y2="0" width="0.9144" layer="51"/>
<wire x1="-4.191" y1="0" x2="-2.921" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="0" x2="-1.778" y2="0.5842" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="0.5842" x2="-1.778" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="-1.778" y1="-0.5842" x2="-2.921" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="0" x2="-0.635" y2="0" width="0.1524" layer="21"/>
<wire x1="-3.302" y1="0.4572" x2="-3.302" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.302" y1="0.635" x2="-2.921" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="0.635" x2="-2.921" y2="0" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.4572" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-2.921" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.921" y1="-0.635" x2="-2.921" y2="0" width="0.1524" layer="21"/>
<wire x1="2.794" y1="-1.27" x2="6.35" y2="-1.27" width="0.1524" layer="21" curve="-86.050132"/>
<wire x1="2.794" y1="1.27" x2="6.35" y2="1.27" width="0.1524" layer="21" curve="86.050132"/>
<wire x1="7.239" y1="1.27" x2="6.35" y2="1.27" width="0.1524" layer="21"/>
<wire x1="2.794" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="2.794" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="6.35" y1="-1.27" x2="7.239" y2="-1.27" width="0.1524" layer="21"/>
<pad name="C" x="-10.16" y="0" drill="1.1938" shape="long"/>
<pad name="A" x="10.16" y="0" drill="1.1938" shape="long"/>
<text x="-7.239" y="3.429" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.461" y="-2.159" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="7.239" y1="-0.4318" x2="8.7122" y2="0.4318" layer="21"/>
<rectangle x1="-8.7122" y1="-0.4318" x2="-7.239" y2="0.4318" layer="21"/>
<rectangle x1="-6.731" y1="-3.175" x2="-6.096" y2="3.175" layer="21"/>
</package>
<package name="C4111-15">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 5.3 mm, horizontal, grid 15.24 mm</description>
<wire x1="-1.27" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.27" y2="0.5842" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.5842" x2="1.27" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.5842" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-2.667" x2="-5.08" y2="2.667" width="0.1524" layer="21"/>
<wire x1="5.08" y1="2.667" x2="5.08" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="2.667" x2="5.08" y2="2.667" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-2.667" x2="-5.08" y2="-2.667" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.5842" x2="0.381" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0" x2="6.223" y2="0" width="1.27" layer="51"/>
<wire x1="-7.62" y1="0" x2="-6.223" y2="0" width="1.27" layer="51"/>
<wire x1="-0.381" y1="0.5842" x2="0" y2="0.5842" width="0.1524" layer="21"/>
<wire x1="0" y1="0.5842" x2="0" y2="0" width="0.1524" layer="21"/>
<pad name="C" x="-7.62" y="0" drill="1.4986" shape="long"/>
<pad name="A" x="7.62" y="0" drill="1.4986" shape="long"/>
<text x="-2.54" y="-2.159" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.08" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<rectangle x1="-5.969" y1="-0.635" x2="-5.08" y2="0.635" layer="21"/>
<rectangle x1="5.08" y1="-0.635" x2="5.969" y2="0.635" layer="21"/>
<rectangle x1="-4.318" y1="-2.667" x2="-3.302" y2="2.667" layer="21"/>
</package>
<package name="P6T15">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 9 mm, horizontal, grid 15.24 mm</description>
<wire x1="-4.699" y1="-4.572" x2="-4.699" y2="4.572" width="0.1524" layer="21"/>
<wire x1="4.699" y1="4.572" x2="4.699" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="-4.699" y1="4.572" x2="4.699" y2="4.572" width="0.1524" layer="21"/>
<wire x1="4.699" y1="-4.572" x2="-4.699" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0" x2="6.223" y2="0" width="1.27" layer="51"/>
<wire x1="-7.62" y1="0" x2="-6.223" y2="0" width="1.27" layer="51"/>
<wire x1="-0.381" y1="0.508" x2="-0.381" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-0.381" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0.381" y1="-0.508" x2="0.381" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.381" y1="-0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<pad name="C" x="-7.62" y="0" drill="1.4986" shape="long"/>
<pad name="A" x="7.62" y="0" drill="1.4986" shape="long"/>
<text x="-4.6736" y="4.8514" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.3622" y="-3.302" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.429" y1="-4.572" x2="-2.921" y2="4.572" layer="21"/>
<rectangle x1="4.699" y1="-0.635" x2="5.969" y2="0.635" layer="21"/>
<rectangle x1="-5.969" y1="-0.635" x2="-4.699" y2="0.635" layer="21"/>
</package>
<package name="CB429-17">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 5 mm, horizontal, grid 17 mm</description>
<wire x1="-1.27" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.27" y2="0.5842" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.5842" x2="1.27" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.5842" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="2.54" x2="5.08" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.5842" x2="0.381" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="8.89" y1="0" x2="7.366" y2="0" width="1.016" layer="51"/>
<wire x1="-8.89" y1="0" x2="-7.366" y2="0" width="1.016" layer="51"/>
<wire x1="0" y1="0.5842" x2="0" y2="0" width="0.1524" layer="21"/>
<pad name="C" x="-8.89" y="0" drill="1.397" shape="long"/>
<pad name="A" x="8.89" y="0" drill="1.397" shape="long"/>
<text x="-2.54" y="-2.159" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.08" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<rectangle x1="-4.318" y1="-2.54" x2="-3.302" y2="2.54" layer="21"/>
<rectangle x1="5.08" y1="-0.508" x2="7.239" y2="0.508" layer="21"/>
<rectangle x1="-7.239" y1="-0.508" x2="-5.08" y2="0.508" layer="21"/>
</package>
<package name="DO201T15">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 5.6 mm, horizontal, grid 15.24 mm</description>
<wire x1="-1.27" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.143" y2="0.5842" width="0.1524" layer="21"/>
<wire x1="1.143" y1="0.5842" x2="1.143" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-0.5842" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="2.286" y2="0" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-2.794" x2="-5.08" y2="2.794" width="0.1524" layer="21"/>
<wire x1="5.08" y1="2.794" x2="5.08" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="2.794" x2="5.08" y2="2.794" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-2.794" x2="-5.08" y2="-2.794" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0" x2="6.223" y2="0" width="1.27" layer="51"/>
<wire x1="-7.62" y1="0" x2="-6.223" y2="0" width="1.27" layer="51"/>
<wire x1="-0.381" y1="0.4572" x2="-0.381" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-0.381" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0.381" y1="-0.4572" x2="0.381" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.381" y1="-0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<pad name="C" x="-7.62" y="0" drill="1.4986" shape="long"/>
<pad name="A" x="7.62" y="0" drill="1.4986" shape="long"/>
<text x="-5.08" y="3.175" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-2.159" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-4.191" y1="-2.794" x2="-3.429" y2="2.794" layer="21"/>
<rectangle x1="-5.969" y1="-0.635" x2="-5.08" y2="0.635" layer="21"/>
<rectangle x1="5.08" y1="-0.635" x2="5.969" y2="0.635" layer="21"/>
</package>
<package name="DO35-7">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 2 mm, horizontal, grid 7.62 mm</description>
<wire x1="3.81" y1="0" x2="2.921" y2="0" width="0.508" layer="51"/>
<wire x1="-3.81" y1="0" x2="-2.921" y2="0" width="0.508" layer="51"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.635" x2="1.016" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.016" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.032" y1="1.016" x2="2.286" y2="0.762" width="0.1524" layer="21" curve="-90"/>
<wire x1="2.286" y1="0.762" x2="2.286" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="2.032" y1="-1.016" x2="2.286" y2="-0.762" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.286" y1="0.762" x2="-2.032" y2="1.016" width="0.1524" layer="21" curve="-90"/>
<wire x1="-2.286" y1="-0.762" x2="-2.032" y2="-1.016" width="0.1524" layer="21" curve="90"/>
<wire x1="-2.032" y1="-1.016" x2="2.032" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="0.762" x2="-2.286" y2="-0.762" width="0.1524" layer="21"/>
<wire x1="-2.032" y1="1.016" x2="2.032" y2="1.016" width="0.1524" layer="21"/>
<pad name="C" x="-3.81" y="0" drill="0.8128" shape="long"/>
<pad name="A" x="3.81" y="0" drill="0.8128" shape="long"/>
<text x="-2.286" y="1.27" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.286" y="-2.667" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-1.905" y1="-1.016" x2="-1.397" y2="1.016" layer="21"/>
<rectangle x1="2.286" y1="-0.254" x2="2.921" y2="0.254" layer="21"/>
<rectangle x1="-2.921" y1="-0.254" x2="-2.286" y2="0.254" layer="21"/>
</package>
<package name="F126Z12">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 3 mm, horizontal, grid 12.7 mm</description>
<wire x1="-3.175" y1="-1.524" x2="3.175" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.524" x2="-3.175" y2="1.524" width="0.1524" layer="21"/>
<wire x1="3.175" y1="-1.524" x2="3.175" y2="1.524" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.524" x2="-3.175" y2="-1.524" width="0.1524" layer="21"/>
<wire x1="6.35" y1="0" x2="4.826" y2="0" width="0.8128" layer="51"/>
<wire x1="-6.35" y1="0" x2="-4.826" y2="0" width="0.8128" layer="51"/>
<wire x1="-0.635" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="1.016" y1="0.635" x2="1.016" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.016" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.524" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.016" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.254" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<pad name="C" x="-6.35" y="0" drill="1.016" shape="long"/>
<pad name="A" x="6.35" y="0" drill="1.016" shape="long"/>
<text x="-3.175" y="1.778" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-3.175" y="-3.048" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-2.54" y1="-1.524" x2="-1.778" y2="1.524" layer="21"/>
<rectangle x1="-4.8514" y1="-0.4064" x2="-3.175" y2="0.4064" layer="21"/>
<rectangle x1="3.175" y1="-0.4064" x2="4.8514" y2="0.4064" layer="21"/>
</package>
<package name="AG">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 9 mm, horizontal, grid 10.16 mm</description>
<wire x1="-4.699" y1="-4.572" x2="-4.699" y2="4.572" width="0.1524" layer="21"/>
<wire x1="4.699" y1="4.572" x2="4.699" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="-4.699" y1="4.572" x2="4.699" y2="4.572" width="0.1524" layer="21"/>
<wire x1="4.699" y1="-4.572" x2="-4.699" y2="-4.572" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.27" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0" x2="5.842" y2="0" width="1.4732" layer="51"/>
<wire x1="-7.62" y1="0" x2="-5.842" y2="0" width="1.4732" layer="51"/>
<wire x1="-0.381" y1="0.508" x2="-0.381" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-0.381" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0.381" y1="-0.508" x2="0.381" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0.381" y1="-0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="0" y2="0" width="0.1524" layer="21"/>
<pad name="C" x="-7.62" y="0" drill="1.8034" shape="long"/>
<pad name="A" x="7.62" y="0" drill="1.8034" shape="long"/>
<text x="-4.8006" y="4.8514" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.4892" y="-3.302" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.81" y1="-4.572" x2="-3.302" y2="4.572" layer="21"/>
<rectangle x1="4.699" y1="-0.7112" x2="5.6134" y2="0.7112" layer="21"/>
<rectangle x1="-5.6134" y1="-0.7112" x2="-4.699" y2="0.7112" layer="21"/>
</package>
<package name="TO92H">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
2-lead plastic, vertical</description>
<wire x1="-2.286" y1="-1.27" x2="2.286" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.286" y1="-1.27" x2="2.2705" y2="-1.2974" width="0.1524" layer="21" curve="-238.798935"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="1.27" y="0" drill="0.8128" shape="octagon"/>
<text x="3.175" y="0.635" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="3.175" y="-1.27" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="CB417-15">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 3.5 mm, horizontal, grid 15.24 mm</description>
<wire x1="-4.572" y1="-1.778" x2="-4.572" y2="1.778" width="0.1524" layer="21"/>
<wire x1="4.572" y1="1.778" x2="-4.572" y2="1.778" width="0.1524" layer="21"/>
<wire x1="4.572" y1="1.778" x2="4.572" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="-4.572" y1="-1.778" x2="4.572" y2="-1.778" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0" x2="6.35" y2="0" width="1.1176" layer="51"/>
<wire x1="-7.62" y1="0" x2="-6.35" y2="0" width="1.1176" layer="51"/>
<pad name="C" x="-7.62" y="0" drill="1.397" shape="long"/>
<pad name="A" x="7.62" y="0" drill="1.397" shape="long"/>
<text x="-4.572" y="2.159" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.794" y="-1.397" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="-3.81" y1="-1.778" x2="-3.302" y2="1.778" layer="21"/>
<rectangle x1="4.572" y1="-0.5334" x2="6.223" y2="0.5334" layer="21"/>
<rectangle x1="-6.223" y1="-0.5334" x2="-4.572" y2="0.5334" layer="21"/>
</package>
<package name="CB429-15">
<description>&lt;B&gt;DIODE&lt;/B&gt;&lt;p&gt;
diameter 5 mm, horizontal, grid 15.24 mm</description>
<wire x1="-1.27" y1="0" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="1.27" y2="0.5842" width="0.1524" layer="21"/>
<wire x1="1.27" y1="0.5842" x2="1.27" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="1.27" y1="-0.5842" x2="0" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.1524" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-2.54" x2="-5.08" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="2.54" x2="5.08" y2="2.54" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="-5.08" y2="-2.54" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.5842" x2="0.381" y2="-0.5842" width="0.1524" layer="21"/>
<wire x1="7.62" y1="0" x2="6.096" y2="0" width="1.016" layer="51"/>
<wire x1="-7.62" y1="0" x2="-6.096" y2="0" width="1.016" layer="51"/>
<wire x1="0" y1="0.5842" x2="0" y2="0" width="0.1524" layer="21"/>
<pad name="C" x="-7.62" y="0" drill="1.397" shape="long"/>
<pad name="A" x="7.62" y="0" drill="1.397" shape="long"/>
<text x="-2.54" y="-2.159" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.08" y="2.921" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<rectangle x1="-4.318" y1="-2.54" x2="-3.302" y2="2.54" layer="21"/>
<rectangle x1="-5.969" y1="-0.508" x2="-5.08" y2="0.508" layer="21"/>
<rectangle x1="5.08" y1="-0.508" x2="5.969" y2="0.508" layer="21"/>
</package>
<package name="SMB">
<description>&lt;B&gt;DIODE&lt;/B&gt;</description>
<wire x1="-2.2606" y1="1.905" x2="2.2606" y2="1.905" width="0.1016" layer="21"/>
<wire x1="-2.2606" y1="-1.905" x2="2.2606" y2="-1.905" width="0.1016" layer="21"/>
<wire x1="-2.2606" y1="-1.905" x2="-2.2606" y2="1.905" width="0.1016" layer="51"/>
<wire x1="2.2606" y1="-1.905" x2="2.2606" y2="1.905" width="0.1016" layer="51"/>
<wire x1="0.193" y1="1" x2="-0.83" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.83" y1="0" x2="0.193" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.193" y1="-1" x2="0.193" y2="1" width="0.2032" layer="21"/>
<smd name="C" x="-2.2" y="0" dx="2.4" dy="2.4" layer="1"/>
<smd name="A" x="2.2" y="0" dx="2.4" dy="2.4" layer="1"/>
<text x="-2.159" y="2.159" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.159" y="-3.429" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.794" y1="-1.0922" x2="-2.2606" y2="1.0922" layer="51"/>
<rectangle x1="2.2606" y1="-1.0922" x2="2.794" y2="1.0922" layer="51"/>
<rectangle x1="-1.35" y1="-1.9" x2="-0.8" y2="1.9" layer="51"/>
</package>
<package name="SMC">
<description>&lt;b&gt;DIODE&lt;/b&gt;</description>
<wire x1="-3.5606" y1="3.105" x2="3.5606" y2="3.105" width="0.1016" layer="21"/>
<wire x1="-3.5606" y1="-3.105" x2="3.5606" y2="-3.105" width="0.1016" layer="21"/>
<wire x1="-3.5606" y1="-3.105" x2="-3.5606" y2="3.105" width="0.1016" layer="51"/>
<wire x1="3.5606" y1="-3.105" x2="3.5606" y2="3.105" width="0.1016" layer="51"/>
<wire x1="0.543" y1="1" x2="-0.83" y2="0" width="0.2032" layer="21"/>
<wire x1="-0.83" y1="0" x2="0.543" y2="-1" width="0.2032" layer="21"/>
<wire x1="0.543" y1="-1" x2="0.543" y2="1" width="0.2032" layer="21"/>
<smd name="C" x="-3.7" y="0" dx="2.8" dy="3.8" layer="1"/>
<smd name="A" x="3.7" y="0" dx="2.8" dy="3.8" layer="1"/>
<text x="-3.459" y="3.359" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.459" y="-4.629" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-4.094" y1="-1.0922" x2="-3.5606" y2="1.0922" layer="51"/>
<rectangle x1="3.5606" y1="-1.0922" x2="4.094" y2="1.0922" layer="51"/>
<rectangle x1="-2.1" y1="-3.1" x2="-0.85" y2="3.1" layer="21"/>
</package>
<package name="SMBG">
<description>&lt;b&gt;DO-214AA GULL-WING&lt;/b&gt;&lt;p&gt;
Source: www.rsonline.de .. SMBJ12/C/15/C/24/C/30/C/5.0/C/7.5/C Voltage Suppressor. Data Sheet</description>
<wire x1="2.24" y1="1.85" x2="2.24" y2="-1.85" width="0.1016" layer="21"/>
<wire x1="2.24" y1="-1.85" x2="-2.24" y2="-1.85" width="0.1016" layer="21"/>
<wire x1="-2.24" y1="-1.85" x2="-2.24" y2="1.85" width="0.1016" layer="21"/>
<wire x1="-2.24" y1="1.85" x2="2.24" y2="1.85" width="0.1016" layer="21"/>
<smd name="C" x="-3.17" y="0" dx="1.27" dy="2.16" layer="1"/>
<smd name="A" x="3.17" y="0" dx="1.27" dy="2.16" layer="1" rot="R180"/>
<text x="-1.905" y="2.54" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.81" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-3.24" y1="-1.05" x2="-2.23" y2="1.05" layer="51"/>
<rectangle x1="2.24" y1="-1.05" x2="3.24" y2="1.05" layer="51"/>
</package>
<package name="SMBJ">
<description>&lt;b&gt;DO-214AA Modified J_BEND&lt;/b&gt;&lt;p&gt;
Source: www.rsonline.de .. SMBJ12/C/15/C/24/C/30/C/5.0/C/7.5/C Voltage Suppressor. Data Sheet</description>
<wire x1="2.24" y1="1.92" x2="2.24" y2="-1.92" width="0.1016" layer="51"/>
<wire x1="2.24" y1="-1.92" x2="-2.24" y2="-1.92" width="0.1016" layer="21"/>
<wire x1="-2.24" y1="-1.92" x2="-2.24" y2="1.92" width="0.1016" layer="51"/>
<wire x1="-2.24" y1="1.92" x2="2.24" y2="1.92" width="0.1016" layer="21"/>
<smd name="C" x="-2.03" y="0" dx="1.78" dy="2.16" layer="1"/>
<smd name="A" x="2.04" y="0" dx="1.78" dy="2.16" layer="1" rot="R180"/>
<text x="-1.905" y="2.54" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.905" y="-3.81" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-2.8" y1="-1.1" x2="-2.25" y2="1.1" layer="51"/>
<rectangle x1="2.25" y1="-1.1" x2="2.8" y2="1.1" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="SCHOTTKY">
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.905" y1="1.27" x2="1.905" y2="1.016" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0.635" y1="-1.016" x2="0.635" y2="-1.27" width="0.254" layer="94"/>
<text x="-2.286" y="1.905" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.286" y="-3.429" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
<pin name="C" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="SUPPRESSOR">
<wire x1="1.27" y1="-1.27" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.905" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="0" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-1.27" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="1.27" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="0.635" width="0.254" layer="94"/>
<text x="2.794" y="1.905" size="1.778" layer="95">&gt;NAME</text>
<text x="2.794" y="-0.889" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="0" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="C" x="0" y="2.54" visible="off" length="short" direction="pas" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="SCHOTTKY-DIODE" prefix="D" uservalue="yes">
<description>Schottky Diode</description>
<gates>
<gate name="G$1" symbol="SCHOTTKY" x="0" y="0"/>
</gates>
<devices>
<device name="DO13M" package="DO13M">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="C4111-15" package="C4111-15">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="P6T15" package="P6T15">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CB429-17" package="CB429-17">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="DO201T15" package="DO201T15">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="DO35-7" package="DO35-7">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="F126Z12" package="F126Z12">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AG" package="AG">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TO92H" package="TO92H">
<connects>
<connect gate="G$1" pin="A" pad="1"/>
<connect gate="G$1" pin="C" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CB417-15" package="CB417-15">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CB429-15" package="CB429-15">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="SMB">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMC" package="SMC">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SUPPRESSOR-" prefix="D" uservalue="yes">
<description>&lt;b&gt;Suppressor diode&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="SUPPRESSOR" x="0" y="0"/>
</gates>
<devices>
<device name="SMBG" package="SMBG">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMBJ" package="SMBJ">
<connects>
<connect gate="G$1" pin="A" pad="A"/>
<connect gate="G$1" pin="C" pad="C"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="linear">
<packages>
<package name="TO92">
<description>&lt;b&gt;TO-92&lt;/b&gt;</description>
<wire x1="-2.095" y1="-1.651" x2="-0.7869" y2="2.5484" width="0.1524" layer="21" curve="-111.097684"/>
<wire x1="0.7869" y1="2.5484" x2="2.095" y2="-1.651" width="0.1524" layer="21" curve="-111.097684"/>
<wire x1="-2.095" y1="-1.651" x2="2.095" y2="-1.651" width="0.1524" layer="21"/>
<wire x1="-2.254" y1="-0.254" x2="-0.286" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="-2.655" y1="-0.254" x2="-2.254" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="-0.286" y1="-0.254" x2="0.286" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="2.254" y1="-0.254" x2="2.655" y2="-0.254" width="0.1524" layer="21"/>
<wire x1="0.286" y1="-0.254" x2="2.254" y2="-0.254" width="0.1524" layer="51"/>
<wire x1="-0.7864" y1="2.5484" x2="0.7864" y2="2.5484" width="0.1524" layer="51" curve="-34.298964"/>
<pad name="1" x="-1.27" y="0" drill="0.8128" shape="octagon"/>
<pad name="2" x="0" y="1.905" drill="0.8128" shape="octagon"/>
<pad name="3" x="1.27" y="0" drill="0.8128" shape="octagon"/>
<text x="2.413" y="1.651" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="2.921" y="-1.27" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="DPACK">
<description>&lt;b&gt;DPAK&lt;/b&gt;&lt;p&gt;
(Motorola)</description>
<wire x1="3.2766" y1="3.8354" x2="3.277" y2="-2.159" width="0.2032" layer="21"/>
<wire x1="3.277" y1="-2.159" x2="-3.277" y2="-2.159" width="0.2032" layer="21"/>
<wire x1="-3.277" y1="-2.159" x2="-3.2766" y2="3.8354" width="0.2032" layer="21"/>
<wire x1="-3.277" y1="3.835" x2="3.2774" y2="3.8346" width="0.2032" layer="51"/>
<wire x1="-2.5654" y1="3.937" x2="-2.5654" y2="4.6482" width="0.2032" layer="51"/>
<wire x1="-2.5654" y1="4.6482" x2="-2.1082" y2="5.1054" width="0.2032" layer="51"/>
<wire x1="-2.1082" y1="5.1054" x2="2.1082" y2="5.1054" width="0.2032" layer="51"/>
<wire x1="2.1082" y1="5.1054" x2="2.5654" y2="4.6482" width="0.2032" layer="51"/>
<wire x1="2.5654" y1="4.6482" x2="2.5654" y2="3.937" width="0.2032" layer="51"/>
<wire x1="2.5654" y1="3.937" x2="-2.5654" y2="3.937" width="0.2032" layer="51"/>
<smd name="2" x="0" y="2.5" dx="5.4" dy="6.2" layer="1"/>
<smd name="1" x="-2.28" y="-4.8" dx="1" dy="1.6" layer="1"/>
<smd name="3" x="2.28" y="-4.8" dx="1" dy="1.6" layer="1"/>
<text x="-3.81" y="-2.54" size="1.27" layer="25" rot="R90">&gt;NAME</text>
<text x="5.08" y="-2.54" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-2.7178" y1="-5.1562" x2="-1.8542" y2="-2.2606" layer="51"/>
<rectangle x1="1.8542" y1="-5.1562" x2="2.7178" y2="-2.2606" layer="51"/>
<rectangle x1="-0.4318" y1="-3.0226" x2="0.4318" y2="-2.2606" layer="21"/>
<polygon width="0.1998" layer="51">
<vertex x="-2.5654" y="3.937"/>
<vertex x="-2.5654" y="4.6482"/>
<vertex x="-2.1082" y="5.1054"/>
<vertex x="2.1082" y="5.1054"/>
<vertex x="2.5654" y="4.6482"/>
<vertex x="2.5654" y="3.937"/>
</polygon>
</package>
</packages>
<symbols>
<symbol name="LP2950">
<wire x1="-5.08" y1="5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<text x="-2.032" y="-3.81" size="1.524" layer="95">GND</text>
<text x="-5.08" y="6.35" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<pin name="I" x="-7.62" y="2.54" length="short" direction="in"/>
<pin name="O" x="7.62" y="2.54" length="short" direction="in" rot="R180"/>
<pin name="GND" x="0" y="-7.62" visible="pad" length="short" direction="pwr" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="LP2950" prefix="IC">
<description>&lt;b&gt;100 mA, Low Power Low Dropout Voltage Regulator&lt;/b&gt;&lt;p&gt;
Source: http://www.onsemi.com/pub/Collateral/LP2950-D.PDF</description>
<gates>
<gate name="G$1" symbol="LP2950" x="0" y="0"/>
</gates>
<devices>
<device name="Z" package="TO92">
<connects>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="I" pad="3"/>
<connect gate="G$1" pin="O" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="" package="DPACK">
<connects>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="I" pad="1"/>
<connect gate="G$1" pin="O" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="transistor-power">
<packages>
<package name="MICRO3">
<description>&lt;b&gt;Micro3 TM Package Outline&lt;/b&gt;&lt;p&gt;
www.irf.com / irlml5203.pdf</description>
<wire x1="-1.45" y1="0.65" x2="-0.6" y2="0.65" width="0.1016" layer="21"/>
<wire x1="-0.6" y1="0.65" x2="0.6" y2="0.65" width="0.1016" layer="51"/>
<wire x1="0.6" y1="0.65" x2="1.45" y2="0.65" width="0.1016" layer="21"/>
<wire x1="1.45" y1="0.65" x2="1.45" y2="-0.65" width="0.1016" layer="21"/>
<wire x1="1.45" y1="-0.65" x2="0.35" y2="-0.65" width="0.1016" layer="51"/>
<wire x1="0.35" y1="-0.65" x2="-0.35" y2="-0.65" width="0.1016" layer="21"/>
<wire x1="-0.35" y1="-0.65" x2="-1.45" y2="-0.65" width="0.1016" layer="51"/>
<wire x1="-1.45" y1="-0.65" x2="-1.45" y2="0.65" width="0.1016" layer="21"/>
<smd name="1" x="-0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<smd name="2" x="0.95" y="-1" dx="0.8" dy="0.9" layer="1"/>
<smd name="3" x="0" y="1" dx="0.8" dy="0.9" layer="1"/>
<text x="-1.6" y="1.6" size="1.778" layer="25">&gt;NAME</text>
<text x="-1.5" y="-3.4" size="1.778" layer="27">&gt;VALUE</text>
<rectangle x1="-0.27" y1="0.66" x2="0.27" y2="1.25" layer="51"/>
<rectangle x1="-1.22" y1="-1.25" x2="-0.68" y2="-0.65" layer="51"/>
<rectangle x1="0.68" y1="-1.25" x2="1.22" y2="-0.64" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="MFPS">
<wire x1="-1.016" y1="-2.54" x2="-1.016" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.016" y1="2.54" x2="-2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-1.905" x2="0.5334" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="0" x2="2.54" y2="1.905" width="0.1524" layer="94"/>
<wire x1="0.508" y1="1.905" x2="2.54" y2="1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="2.54" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="5.08" y1="1.905" x2="2.54" y2="1.905" width="0.1524" layer="94"/>
<wire x1="2.54" y1="1.905" x2="2.54" y2="2.54" width="0.1524" layer="94"/>
<wire x1="2.2352" y1="0" x2="2.286" y2="0" width="0.1524" layer="94"/>
<wire x1="2.286" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="2.286" y1="0" x2="1.016" y2="-0.508" width="0.1524" layer="94"/>
<wire x1="1.016" y1="-0.508" x2="1.016" y2="0.508" width="0.1524" layer="94"/>
<wire x1="1.016" y1="0.508" x2="2.286" y2="0" width="0.1524" layer="94"/>
<wire x1="1.143" y1="0" x2="0.254" y2="0" width="0.1524" layer="94"/>
<wire x1="1.143" y1="0.254" x2="2.032" y2="0" width="0.3048" layer="94"/>
<wire x1="2.032" y1="0" x2="1.143" y2="-0.254" width="0.3048" layer="94"/>
<wire x1="1.143" y1="-0.254" x2="1.143" y2="0" width="0.3048" layer="94"/>
<wire x1="1.143" y1="0" x2="1.397" y2="0" width="0.3048" layer="94"/>
<wire x1="5.08" y1="1.905" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="5.08" y2="-1.905" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="5.715" y2="-0.635" width="0.1524" layer="94"/>
<wire x1="5.715" y1="-0.635" x2="4.445" y2="-0.635" width="0.1524" layer="94"/>
<wire x1="4.445" y1="-0.635" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.715" y1="0.762" x2="5.08" y2="0.762" width="0.1524" layer="94"/>
<wire x1="5.08" y1="0.762" x2="4.445" y2="0.762" width="0.1524" layer="94"/>
<wire x1="4.445" y1="0.762" x2="4.191" y2="1.016" width="0.1524" layer="94"/>
<wire x1="5.715" y1="0.762" x2="5.969" y2="0.508" width="0.1524" layer="94"/>
<circle x="2.54" y="1.905" radius="0.127" width="0.4064" layer="94"/>
<circle x="2.54" y="-1.905" radius="0.127" width="0.4064" layer="94"/>
<text x="7.62" y="2.54" size="1.778" layer="95">&gt;NAME</text>
<text x="7.62" y="0" size="1.778" layer="96">&gt;VALUE</text>
<text x="1.524" y="-3.302" size="0.8128" layer="93">D</text>
<text x="1.524" y="2.54" size="0.8128" layer="93">S</text>
<text x="-2.286" y="1.27" size="0.8128" layer="93">G</text>
<rectangle x1="-0.254" y1="1.27" x2="0.508" y2="2.54" layer="94"/>
<rectangle x1="-0.254" y1="-2.54" x2="0.508" y2="-1.27" layer="94"/>
<rectangle x1="-0.254" y1="-0.889" x2="0.508" y2="0.889" layer="94"/>
<pin name="G" x="-2.54" y="2.54" visible="off" length="point" direction="pas"/>
<pin name="D" x="2.54" y="-5.08" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="S" x="2.54" y="5.08" visible="off" length="short" direction="pas" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="IRLML5203" prefix="Q">
<description>&lt;b&gt;HEXFET P-Channel Power MOSFET&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MFPS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MICRO3">
<connects>
<connect gate="G$1" pin="D" pad="3"/>
<connect gate="G$1" pin="G" pad="1"/>
<connect gate="G$1" pin="S" pad="2"/>
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
<package name="CRYSTAL-SMD-5X3">
<wire x1="-0.6" y1="1.6" x2="0.6" y2="1.6" width="0.2032" layer="21"/>
<wire x1="2.5" y1="0.3" x2="2.5" y2="-0.3" width="0.2032" layer="21"/>
<wire x1="0.6" y1="-1.6" x2="-0.6" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.5" y1="0.3" x2="-2.5" y2="-0.3" width="0.2032" layer="21"/>
<smd name="1" x="-1.85" y="-1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="3" x="1.85" y="1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="4" x="-1.85" y="1.15" dx="1.9" dy="1.1" layer="1"/>
<smd name="2" x="1.85" y="-1.15" dx="1.9" dy="1.1" layer="1"/>
<text x="-2.54" y="1.905" size="0.4064" layer="25">&gt;NAME</text>
<text x="-2.54" y="-2.54" size="0.4064" layer="27">&gt;VALUE</text>
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
<pad name="1" x="-2.413" y="0" drill="0.8"/>
<pad name="2" x="2.413" y="0" drill="0.8"/>
<text x="-2.54" y="2.921" size="1.016" layer="25" ratio="18">&gt;NAME</text>
<text x="-2.54" y="-3.556" size="0.8128" layer="27" ratio="10">&gt;VALUE</text>
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
<pad name="1" x="-1.27" y="0" drill="0.8"/>
<pad name="2" x="1.27" y="0" drill="0.8"/>
<text x="-1.905" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="3.175" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="1.016" x2="1.778" y2="10.414" layer="43"/>
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
<pad name="1" x="-1.27" y="0" drill="0.8"/>
<pad name="2" x="1.27" y="0" drill="0.8"/>
<text x="-1.397" y="2.032" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="2.667" y="2.032" size="1.27" layer="27" ratio="10" rot="R90">&gt;VALUE</text>
<rectangle x1="0.3048" y1="1.016" x2="0.7112" y2="1.6002" layer="21"/>
<rectangle x1="-0.7112" y1="1.016" x2="-0.3048" y2="1.6002" layer="21"/>
<rectangle x1="-1.778" y1="0.762" x2="1.778" y2="8.382" layer="43"/>
</package>
<package name="HC49UP">
<description>&lt;b&gt;CRYSTAL&lt;/b&gt;</description>
<wire x1="-5.1091" y1="1.143" x2="-3.429" y2="2.0321" width="0.0508" layer="21" curve="-55.770993" cap="flat"/>
<wire x1="-5.715" y1="1.143" x2="-5.715" y2="2.159" width="0.1524" layer="21"/>
<wire x1="3.429" y1="2.032" x2="5.1091" y2="1.143" width="0.0508" layer="21" curve="-55.772485" cap="flat"/>
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
<wire x1="3.429" y1="-1.27" x2="3.9826" y2="-1.143" width="0.0508" layer="21" curve="25.842828" cap="flat"/>
<wire x1="3.429" y1="1.27" x2="3.9826" y2="1.143" width="0.0508" layer="21" curve="-25.842828" cap="flat"/>
<wire x1="3.429" y1="-2.032" x2="5.109" y2="-1.1429" width="0.0508" layer="21" curve="55.771157" cap="flat"/>
<wire x1="3.9826" y1="-1.143" x2="3.9826" y2="1.143" width="0.0508" layer="51" curve="128.314524" cap="flat"/>
<wire x1="5.1091" y1="-1.143" x2="5.1091" y2="1.143" width="0.0508" layer="51" curve="68.456213" cap="flat"/>
<wire x1="-5.1091" y1="-1.143" x2="-3.429" y2="-2.032" width="0.0508" layer="21" curve="55.772485" cap="flat"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.9826" y2="1.143" width="0.0508" layer="51" curve="-128.314524" cap="flat"/>
<wire x1="-3.9826" y1="-1.143" x2="-3.429" y2="-1.27" width="0.0508" layer="21" curve="25.842828" cap="flat"/>
<wire x1="-3.9826" y1="1.143" x2="-3.429" y2="1.27" width="0.0508" layer="21" curve="-25.842828" cap="flat"/>
<wire x1="-6.477" y1="-0.381" x2="-6.477" y2="0.381" width="0.1524" layer="51"/>
<wire x1="-5.1091" y1="-1.143" x2="-5.1091" y2="1.143" width="0.0508" layer="51" curve="-68.456213" cap="flat"/>
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
<package name="HC49US">
<description>&lt;B&gt;CRYSTAL&lt;/B&gt;</description>
<wire x1="-3.429" y1="-2.286" x2="3.429" y2="-2.286" width="0.2032" layer="21"/>
<wire x1="3.429" y1="2.286" x2="-3.429" y2="2.286" width="0.2032" layer="21"/>
<wire x1="3.429" y1="2.286" x2="3.429" y2="-2.286" width="0.2032" layer="21" curve="-180"/>
<wire x1="-3.429" y1="2.286" x2="-3.429" y2="-2.286" width="0.2032" layer="21" curve="180"/>
<pad name="1" x="-2.54" y="0" drill="0.8" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="0.8" rot="R90"/>
<text x="-2.54" y="-3.302" size="0.8128" layer="27" ratio="10">&gt;VALUE</text>
<text x="-3.175" y="2.667" size="1.016" layer="25" ratio="18">&gt;NAME</text>
</package>
<package name="CRYSTAL-32KHZ-SMD">
<smd name="X1" x="-1.27" y="0" dx="1" dy="2.5" layer="1"/>
<smd name="X2" x="1.27" y="0" dx="1" dy="2.5" layer="1"/>
<smd name="SHEILD" x="0" y="5.08" dx="2.5" dy="6" layer="1"/>
<text x="-0.635" y="8.255" size="0.4064" layer="25">&gt;Name</text>
<text x="-0.635" y="-1.905" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="CRYSTAL-32KHZ-SMD_EPSON_MC146">
<wire x1="0.2" y1="0" x2="7.2" y2="0" width="0.127" layer="51"/>
<wire x1="7.2" y1="0" x2="7.2" y2="1.5" width="0.127" layer="51"/>
<wire x1="7.2" y1="1.5" x2="0.2" y2="1.5" width="0.127" layer="51"/>
<wire x1="0.2" y1="1.5" x2="0.2" y2="0" width="0.127" layer="51"/>
<wire x1="6.2" y1="1.4" x2="5.9" y2="1.4" width="0.127" layer="21"/>
<wire x1="5.9" y1="1.4" x2="5.9" y2="0.1" width="0.127" layer="21"/>
<wire x1="5.9" y1="0.1" x2="6.2" y2="0.1" width="0.127" layer="21"/>
<wire x1="1.3" y1="1.4" x2="1.9" y2="1.4" width="0.127" layer="21"/>
<wire x1="1.3" y1="0.1" x2="1.9" y2="0.1" width="0.127" layer="21"/>
<smd name="P$1" x="0.6" y="0.3" dx="1.2" dy="0.6" layer="1"/>
<smd name="P$2" x="0.6" y="1.2" dx="1.2" dy="0.6" layer="1"/>
<smd name="NC2" x="6.9" y="0.3" dx="1.2" dy="0.6" layer="1"/>
<smd name="NC1" x="6.9" y="1.2" dx="1.2" dy="0.6" layer="1"/>
</package>
<package name="CRYSTAL-SMD-10.5X4.8-2PIN">
<wire x1="-6.2" y1="1.5" x2="-6.2" y2="2.4" width="0.127" layer="21"/>
<wire x1="-6.2" y1="2.4" x2="6.2" y2="2.4" width="0.127" layer="21"/>
<wire x1="6.2" y1="2.4" x2="6.2" y2="1.5" width="0.127" layer="21"/>
<wire x1="-6.2" y1="-1.5" x2="-6.2" y2="-2.4" width="0.127" layer="21"/>
<wire x1="-6.2" y1="-2.4" x2="6.2" y2="-2.4" width="0.127" layer="21"/>
<wire x1="6.2" y1="-2.4" x2="6.2" y2="-1.5" width="0.127" layer="21"/>
<smd name="P$1" x="-4.3" y="0" dx="5.5" dy="1.5" layer="1"/>
<smd name="P$2" x="4.3" y="0" dx="5.5" dy="1.5" layer="1"/>
</package>
<package name="CRYSTAL-32KHZ-SMD-3.2X1.5">
<smd name="P$1" x="-1.3" y="0.05" dx="1.1" dy="1.9" layer="1"/>
<smd name="P$2" x="1.2" y="0.05" dx="1.1" dy="1.9" layer="1"/>
<rectangle x1="-0.75" y1="-0.9" x2="0.65" y2="1" layer="39"/>
<text x="-1.85" y="1.55" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.85" y="-2.65" size="1.27" layer="27">&gt;VALUE</text>
<wire x1="-0.65" y1="1.2" x2="0.55" y2="1.2" width="0.2" layer="21"/>
<wire x1="-0.65" y1="-1.1" x2="0.55" y2="-1.1" width="0.2" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="ZQ">
<wire x1="-0.516" y1="1.5" x2="0.484" y2="1.5" width="0.1524" layer="94"/>
<wire x1="0.484" y1="1.5" x2="0.484" y2="-1.5" width="0.1524" layer="94"/>
<wire x1="0.484" y1="-1.5" x2="-0.516" y2="-1.5" width="0.1524" layer="94"/>
<wire x1="-0.516" y1="-1.5" x2="-0.516" y2="1.5" width="0.1524" layer="94"/>
<wire x1="-1.016" y1="1" x2="-1.016" y2="0" width="0.1524" layer="94"/>
<wire x1="-1.016" y1="0" x2="-1.016" y2="-1" width="0.1524" layer="94"/>
<wire x1="0.984" y1="1" x2="0.984" y2="-1" width="0.1524" layer="94"/>
<pin name="P$1" x="-2.54" y="0" visible="off" length="point" swaplevel="1"/>
<pin name="P$2" x="2.54" y="0" visible="off" length="point" swaplevel="1" rot="R180"/>
<wire x1="-1.016" y1="0" x2="-2.54" y2="0" width="0.1524" layer="94"/>
<wire x1="1.016" y1="0" x2="2.54" y2="0" width="0.1524" layer="94"/>
<text x="1.676" y="1.808" size="1.524" layer="95">&gt;NAME</text>
<text x="1.73" y="-2.376" size="1.524" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="CRYSTAL" prefix="ZQ" uservalue="yes">
<description>&lt;b&gt;Crystals&lt;/b&gt;
Various standard crystals. Proven footprints. Spark Fun Electronics SKU : COM-00534</description>
<gates>
<gate name="G$1" symbol="ZQ" x="0" y="0"/>
</gates>
<devices>
<device name="HC49UV" package="HC49U-V">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TC38H" package="TC38H">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="TC26H" package="TC26H">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="HC49UP">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="HC49US" package="HC49US">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="32-SMD" package="CRYSTAL-32KHZ-SMD">
<connects>
<connect gate="G$1" pin="P$1" pad="X1"/>
<connect gate="G$1" pin="P$2" pad="X2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="5X3" package="CRYSTAL-SMD-5X3">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="EPSONMC146" package="CRYSTAL-32KHZ-SMD_EPSON_MC146">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="10.5X4.8" package="CRYSTAL-SMD-10.5X4.8-2PIN">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.2X.1.5" package="CRYSTAL-32KHZ-SMD-3.2X1.5">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ferrite">
<packages>
<package name="L0603">
<description>&lt;B&gt;SMD INDUCTOR&lt;/B&gt; - 0603</description>
<wire x1="-0.432" y1="-0.356" x2="0.432" y2="-0.356" width="0.1016" layer="51"/>
<wire x1="0.432" y1="0.356" x2="-0.432" y2="0.356" width="0.1016" layer="51"/>
<wire x1="0" y1="-0.381" x2="0" y2="0.381" width="0.2032" layer="21"/>
<smd name="1" x="-0.7938" y="0" dx="1" dy="1.1" layer="1"/>
<smd name="2" x="0.7938" y="0" dx="1" dy="1.1" layer="1"/>
<text x="-1.27" y="0.7938" size="1.016" layer="25" ratio="18">&gt;NAME</text>
<text x="-1.27" y="-1.5875" size="0.8128" layer="27" ratio="10">&gt;VALUE</text>
<rectangle x1="0.4318" y1="-0.4318" x2="0.8382" y2="0.4318" layer="51"/>
<rectangle x1="-0.8382" y1="-0.4318" x2="-0.4318" y2="0.4318" layer="51"/>
<rectangle x1="-0.1999" y1="-0.4001" x2="0.1999" y2="0.4001" layer="35"/>
</package>
</packages>
<symbols>
<symbol name="INDUCTOR_CORED">
<wire x1="-5.08" y1="0" x2="-3.81" y2="1.27" width="0.1524" layer="94" curve="-90" cap="flat"/>
<wire x1="-2.54" y1="0" x2="-3.81" y2="1.27" width="0.1524" layer="94" curve="90" cap="flat"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="1.27" width="0.1524" layer="94" curve="-90" cap="flat"/>
<wire x1="0" y1="0" x2="-1.27" y2="1.27" width="0.1524" layer="94" curve="90" cap="flat"/>
<wire x1="0" y1="0" x2="1.27" y2="1.27" width="0.1524" layer="94" curve="-90" cap="flat"/>
<wire x1="2.54" y1="0" x2="1.27" y2="1.27" width="0.1524" layer="94" curve="90" cap="flat"/>
<wire x1="2.54" y1="0" x2="3.81" y2="1.27" width="0.1524" layer="94" curve="-90" cap="flat"/>
<wire x1="5.08" y1="0" x2="3.81" y2="1.27" width="0.1524" layer="94" curve="90" cap="flat"/>
<wire x1="5.08" y1="2.54" x2="-5.08" y2="2.54" width="0.1524" layer="94"/>
<text x="-3.302" y="3.048" size="1.524" layer="95">&gt;NAME</text>
<text x="-3.556" y="-2.032" size="1.524" layer="96">&gt;VALUE</text>
<pin name="1" x="-7.62" y="0" visible="off" length="short" direction="pas" swaplevel="1"/>
<pin name="2" x="7.62" y="0" visible="off" length="short" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="EXC3BP" prefix="L">
<description>Chip Bead Core</description>
<gates>
<gate name="G$1" symbol="INDUCTOR_CORED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="L0603">
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
<part name="DD1" library="barthess" deviceset="STM32F407V" device="" technology="GT6"/>
<part name="DD4" library="barthess" deviceset="MICROSD_SDIO" device=""/>
<part name="C1" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C2" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C3" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C4" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C5" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C6" library="SparkFun" deviceset="CAP_POL" device="1206-KIT" value="10uF/6.3v"/>
<part name="P+1" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND1" library="SparkFun" deviceset="GND" device=""/>
<part name="C7" library="SparkFun" deviceset="CAP_POL" device="1206-KIT" value="47uF/6.3v"/>
<part name="P+2" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND2" library="SparkFun" deviceset="GND" device=""/>
<part name="C8" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="GND3" library="SparkFun" deviceset="GND" device=""/>
<part name="GND4" library="SparkFun" deviceset="GND" device=""/>
<part name="R1" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="P+3" library="SparkFun" deviceset="3.3V" device=""/>
<part name="R2" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R3" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="JP4" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="boot_0"/>
<part name="JP5" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="boot_1"/>
<part name="P+4" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND5" library="SparkFun" deviceset="GND" device=""/>
<part name="GND6" library="SparkFun" deviceset="GND" device=""/>
<part name="P+5" library="SparkFun" deviceset="3.3V" device=""/>
<part name="R5" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="100"/>
<part name="R4" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="100"/>
<part name="LED1" library="barthess" deviceset="LED" device="0805" value="RED"/>
<part name="LED2" library="barthess" deviceset="LED" device="0805" value="RED"/>
<part name="ZQ1" library="crystal" deviceset="CRYSTAL" device="5X3" value="8M"/>
<part name="ZQ2" library="crystal" deviceset="CRYSTAL" device="3.2X.1.5" value="32k"/>
<part name="C9" library="SparkFun" deviceset="CAP" device="0805" value="10pF"/>
<part name="C10" library="SparkFun" deviceset="CAP" device="0805" value="10pF"/>
<part name="C11" library="SparkFun" deviceset="CAP" device="0805" value="20pF"/>
<part name="C12" library="SparkFun" deviceset="CAP" device="0805" value="20pF"/>
<part name="GND7" library="SparkFun" deviceset="GND" device=""/>
<part name="GND8" library="SparkFun" deviceset="GND" device=""/>
<part name="P+6" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND9" library="SparkFun" deviceset="GND" device=""/>
<part name="R7" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="C13" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="GND11" library="SparkFun" deviceset="GND" device=""/>
<part name="C14" library="SparkFun" deviceset="CAP_POL" device="1206-KIT" value="10uF/16v"/>
<part name="C15" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="L1" library="ferrite" deviceset="EXC3BP" device="" value="1uH"/>
<part name="GND13" library="SparkFun" deviceset="GND" device=""/>
<part name="X1" library="SparkFun" deviceset="USB" device="-SMD-NS"/>
<part name="GND14" library="SparkFun" deviceset="GND" device=""/>
<part name="R12" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="33"/>
<part name="R13" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="33"/>
<part name="XP1" library="barthess" deviceset="2X10" device="-PSEUDO_SMD"/>
<part name="P+11" library="SparkFun" deviceset="3.3V" device=""/>
<part name="R17" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R18" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R19" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R20" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R21" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R22" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R23" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R24" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="GND21" library="SparkFun" deviceset="GND" device=""/>
<part name="GND22" library="SparkFun" deviceset="GND" device=""/>
<part name="JP1" library="barthess" deviceset="2X5" device=""/>
<part name="GND24" library="SparkFun" deviceset="GND" device=""/>
<part name="P+13" library="SparkFun" deviceset="3.3V" device=""/>
<part name="JP2" library="barthess" deviceset="2X5" device=""/>
<part name="GND26" library="SparkFun" deviceset="GND" device=""/>
<part name="P+14" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND28" library="SparkFun" deviceset="GND" device=""/>
<part name="GND30" library="SparkFun" deviceset="GND" device=""/>
<part name="P+18" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND31" library="SparkFun" deviceset="GND" device=""/>
<part name="R27" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="2.7k"/>
<part name="P+16" library="SparkFun" deviceset="3.3V" device=""/>
<part name="R28" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="2.7k"/>
<part name="U44" library="barthess" deviceset="BMP085" device=""/>
<part name="U2" library="barthess" deviceset="TMP75" device="DGK"/>
<part name="IC1" library="barthess" deviceset="24*" device="SN" technology="AA32A"/>
<part name="C20" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="P+12" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND23" library="SparkFun" deviceset="GND" device=""/>
<part name="GND25" library="SparkFun" deviceset="GND" device=""/>
<part name="C21" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C27" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="GND32" library="SparkFun" deviceset="GND" device=""/>
<part name="P+19" library="SparkFun" deviceset="3.3V" device=""/>
<part name="BAT1" library="SparkFun" deviceset="BATTERY" device="20PTH" value="3V"/>
<part name="VD8" library="barthess" deviceset="BZV55" device="-C3V3"/>
<part name="XP2" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="RECEIVER"/>
<part name="GND15" library="SparkFun" deviceset="GND" device=""/>
<part name="R29" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="1k"/>
<part name="R32" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="100k"/>
<part name="XP6" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="sonar"/>
<part name="XP8" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="PWM1"/>
<part name="XP9" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="PWM2"/>
<part name="XP10" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="PWM3"/>
<part name="XP11" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="PWM4"/>
<part name="XP12" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="PWM5"/>
<part name="XP13" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="PWM6"/>
<part name="XP14" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="PWM7"/>
<part name="XP15" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="PWM8"/>
<part name="GND44" library="SparkFun" deviceset="GND" device=""/>
<part name="R33" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="100k"/>
<part name="R45" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="C50" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="DA3" library="barthess" deviceset="MPXV5010DP" device=""/>
<part name="R47" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="100k"/>
<part name="R48" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R54" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R55" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="R56" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="1k"/>
<part name="R57" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="1k"/>
<part name="U$13" library="barthess" deviceset="6V" device=""/>
<part name="C51" library="SparkFun" deviceset="CAP_POL" device="1206-KIT" value="10uF/16v"/>
<part name="C52" library="SparkFun" deviceset="CAP_POL" device="1206-KIT" value="10uF/6.3v"/>
<part name="U$5" library="barthess" deviceset="6V" device=""/>
<part name="Q1" library="transistor-power" deviceset="IRLML5203" device=""/>
<part name="R58" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="1k"/>
<part name="R59" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="C54" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C55" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="IC3" library="linear" deviceset="LP2950" device="Z"/>
<part name="U$7" library="SparkFun" deviceset="LED-TRICOLOR" device=""/>
<part name="P+23" library="SparkFun" deviceset="3.3V" device=""/>
<part name="R30" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="68"/>
<part name="R31" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="68"/>
<part name="R60" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="68"/>
<part name="T3" library="transistor" deviceset="BC848" device=""/>
<part name="R61" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="1k"/>
<part name="U$1" library="barthess" deviceset="6V" device=""/>
<part name="D2" library="diode" deviceset="SCHOTTKY-DIODE" device="SMD" value="10BQ060"/>
<part name="F3" library="barthess" deviceset="POLYSWITCH" device=""/>
<part name="D3" library="diode" deviceset="SUPPRESSOR-" device="SMBJ" value="SM6T12V"/>
<part name="GND57" library="SparkFun" deviceset="GND" device=""/>
<part name="S2" library="barthess" deviceset="BUTTON_6X3.5" device="" value="RESET"/>
<part name="C24" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="XP17" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="power"/>
<part name="R36" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="47"/>
<part name="R51" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="47"/>
<part name="IC2" library="barthess" deviceset="INA194" device=""/>
<part name="C45" library="SparkFun" deviceset="CAP" device="1206" value="10uF"/>
<part name="XP18" library="barthess" deviceset="1X2" device="DIP" value="current_sens"/>
<part name="JP3" library="SparkFun" deviceset="STAND-OFF" device="TIGHT"/>
<part name="JP7" library="SparkFun" deviceset="STAND-OFF" device="TIGHT"/>
<part name="JP8" library="SparkFun" deviceset="STAND-OFF" device="TIGHT"/>
<part name="JP9" library="SparkFun" deviceset="STAND-OFF" device="TIGHT"/>
<part name="C31" library="barthess" deviceset="CAP_POL" device="7343" value="330uF/10v"/>
<part name="C34" library="barthess" deviceset="CAP_POL" device="7343" value="470uF/6.3v"/>
<part name="XP16" library="SparkFun" deviceset="JUMPER-3" device="PTH" value="tacho"/>
<part name="GND10" library="SparkFun" deviceset="GND" device=""/>
<part name="P+27" library="SparkFun" deviceset="3.3V" device=""/>
<part name="R75" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="1k"/>
<part name="R64" library="barthess" deviceset="RESISTOR" device="1206" value="0"/>
<part name="C22" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C23" library="SparkFun" deviceset="CAP" device="0805" value="2.2uF"/>
<part name="GND12" library="SparkFun" deviceset="GND" device=""/>
<part name="C44" library="SparkFun" deviceset="CAP" device="0805" value="2.2uF"/>
<part name="DA1" library="barthess" deviceset="LM1117DTX" device="" value="LM1117-3.3"/>
<part name="D1" library="diode" deviceset="SCHOTTKY-DIODE" device="SMD" value="10BQ060"/>
<part name="U$3" library="barthess" deviceset="6V" device=""/>
<part name="DA4" library="barthess" deviceset="LP2985" device=""/>
<part name="C16" library="SparkFun" deviceset="CAP" device="0805" value="0.01uF"/>
<part name="P+7" library="SparkFun" deviceset="3.3V" device=""/>
<part name="DD2" library="barthess" deviceset="ADIS16480" device=""/>
<part name="GND16" library="SparkFun" deviceset="GND" device=""/>
<part name="R8" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="P+9" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND17" library="SparkFun" deviceset="GND" device=""/>
<part name="DA5" library="barthess" deviceset="MAX44246" device=""/>
<part name="DA2" library="barthess" deviceset="AD22100" device=""/>
<part name="C17" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="R10" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="C18" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="VD1" library="barthess" deviceset="BZV55" device="-C3V3"/>
<part name="DD3" library="barthess" deviceset="MPU-9150" device="QFN-24-NP" value="MPU9150"/>
<part name="GND19" library="SparkFun" deviceset="GND" device=""/>
<part name="C19" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C25" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="P+10" library="SparkFun" deviceset="3.3V" device=""/>
<part name="C26" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C28" library="SparkFun" deviceset="CAP" device="0805" value="2.2nF/50v"/>
<part name="R14" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="1k"/>
<part name="C29" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="Q3" library="transistor-power" deviceset="IRLML5203" device=""/>
<part name="R15" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="P+17" library="SparkFun" deviceset="3.3V" device=""/>
<part name="Q4" library="transistor-power" deviceset="IRLML5203" device=""/>
<part name="R16" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="10k"/>
<part name="VD2" library="barthess" deviceset="BZV55" device="-C3V3"/>
<part name="VD3" library="barthess" deviceset="BZV55" device="-C3V3"/>
<part name="DD5" library="barthess" deviceset="LSM303DLHC" device=""/>
<part name="GND18" library="SparkFun" deviceset="GND" device=""/>
<part name="P+15" library="SparkFun" deviceset="3.3V" device=""/>
<part name="C30" library="SparkFun" deviceset="CAP" device="0805" value="0.22uF"/>
<part name="C32" library="SparkFun" deviceset="CAP" device="0805" value="4.7uF"/>
<part name="C33" library="SparkFun" deviceset="CAP_POL" device="1206-KIT" value="10uF"/>
<part name="C35" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C36" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C37" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="C39" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="R11" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="2.7k"/>
<part name="P+20" library="SparkFun" deviceset="3.3V" device=""/>
<part name="R25" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="2.7k"/>
<part name="R26" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="0"/>
<part name="R37" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="0"/>
<part name="R38" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="330"/>
<part name="R39" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="330"/>
<part name="R40" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="330"/>
<part name="R41" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="330"/>
<part name="R42" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="330"/>
<part name="R43" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="330"/>
<part name="R44" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="330"/>
<part name="R46" library="SparkFun" deviceset="RESISTOR" device="0805-RES" value="330"/>
<part name="C38" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="DA6" library="barthess" deviceset="AD5200" device=""/>
<part name="GND20" library="SparkFun" deviceset="GND" device=""/>
<part name="P+8" library="SparkFun" deviceset="3.3V" device=""/>
<part name="VD4" library="barthess" deviceset="BAR43" device=""/>
<part name="C40" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="JP6" library="barthess" deviceset="M05X2" device="SHD"/>
<part name="P+22" library="SparkFun" deviceset="3.3V" device=""/>
<part name="GND27" library="SparkFun" deviceset="GND" device=""/>
<part name="C41" library="SparkFun" deviceset="CAP" device="1206" value="10uF"/>
<part name="C42" library="SparkFun" deviceset="CAP" device="0805" value="0.1uF"/>
<part name="GND29" library="SparkFun" deviceset="GND" device=""/>
<part name="C43" library="SparkFun" deviceset="CAP" device="0805" value="2.2uF"/>
<part name="R6" library="barthess" deviceset="RESISTOR" device="1206" value="0"/>
</parts>
<sheets>
<sheet>
<plain>
<text x="320.04" y="101.6" size="1.778" layer="98">1001(a2)(a1)(a0) -- tmp75</text>
<text x="320.04" y="99.06" size="1.778" layer="98">110100(AD0)     -- mpu9150</text>
<text x="320.04" y="96.52" size="1.778" layer="98">1010(a2)(a1)(a0) -- 24AA32</text>
<text x="320.04" y="93.98" size="1.778" layer="98">1110111        -- bmp085</text>
<text x="320.04" y="91.44" size="1.778" layer="98">0011110        -- lsm303_M</text>
<text x="-51.308" y="-46.482" size="1.27" layer="98">usart2_cts_resvd</text>
<text x="-51.308" y="-49.022" size="1.27" layer="98">usart2_rts_resvd</text>
<text x="-51.308" y="-51.562" size="1.27" layer="98">usart2_tx_resvd</text>
<text x="-51.308" y="-54.102" size="1.27" layer="98">usart2_rx_resvd</text>
<text x="177.8" y="131.572" size="1.27" layer="98">xbee_sleep</text>
<text x="41.91" y="-51.308" size="1.27" layer="98">an_reserved</text>
</plain>
<instances>
<instance part="DD1" gate="G$1" x="0" y="0"/>
<instance part="DD4" gate="G$1" x="134.62" y="-160.02"/>
<instance part="C1" gate="G$1" x="-73.66" y="27.94"/>
<instance part="C2" gate="G$1" x="-83.82" y="27.94"/>
<instance part="C3" gate="G$1" x="-93.98" y="27.94"/>
<instance part="C4" gate="G$1" x="-104.14" y="27.94"/>
<instance part="C5" gate="G$1" x="-114.3" y="27.94"/>
<instance part="C6" gate="G$1" x="-139.7" y="30.48"/>
<instance part="P+1" gate="G$1" x="-139.7" y="45.72" rot="R90"/>
<instance part="GND1" gate="1" x="-142.24" y="15.24" rot="R270"/>
<instance part="C7" gate="G$1" x="109.22" y="-142.24" rot="R180"/>
<instance part="P+2" gate="G$1" x="73.66" y="-162.56" rot="R180"/>
<instance part="GND2" gate="1" x="124.46" y="-182.88"/>
<instance part="C8" gate="G$1" x="116.84" y="-142.24"/>
<instance part="GND3" gate="1" x="116.84" y="-132.08" rot="R180"/>
<instance part="GND4" gate="1" x="109.22" y="-132.08" rot="R180"/>
<instance part="R1" gate="G$1" x="116.84" y="-170.18" rot="R270"/>
<instance part="P+3" gate="G$1" x="116.84" y="-180.34" rot="R180"/>
<instance part="R2" gate="G$1" x="45.72" y="139.7" smashed="yes">
<attribute name="NAME" x="41.91" y="141.1986" size="1.778" layer="95"/>
<attribute name="VALUE" x="46.99" y="141.478" size="1.778" layer="96"/>
</instance>
<instance part="R3" gate="G$1" x="50.8" y="177.8" smashed="yes">
<attribute name="NAME" x="46.99" y="179.2986" size="1.778" layer="95"/>
<attribute name="VALUE" x="52.07" y="179.578" size="1.778" layer="96"/>
</instance>
<instance part="JP4" gate="G$1" x="30.48" y="175.26" rot="R90"/>
<instance part="JP5" gate="G$1" x="30.48" y="137.16" rot="R90"/>
<instance part="P+4" gate="G$1" x="33.02" y="144.78"/>
<instance part="GND5" gate="1" x="33.02" y="119.38"/>
<instance part="GND6" gate="1" x="33.02" y="157.48"/>
<instance part="P+5" gate="G$1" x="33.02" y="182.88"/>
<instance part="R5" gate="G$1" x="40.64" y="172.72" rot="R270"/>
<instance part="R4" gate="G$1" x="40.64" y="134.62" rot="R270"/>
<instance part="LED1" gate="G$1" x="40.64" y="165.1"/>
<instance part="LED2" gate="G$1" x="40.64" y="127"/>
<instance part="ZQ1" gate="G$1" x="-43.18" y="2.54" rot="R270"/>
<instance part="ZQ2" gate="G$1" x="48.26" y="-81.28" rot="R180"/>
<instance part="C9" gate="G$1" x="43.18" y="-91.44"/>
<instance part="C10" gate="G$1" x="53.34" y="-91.44"/>
<instance part="C11" gate="G$1" x="-48.26" y="5.08" rot="R90"/>
<instance part="C12" gate="G$1" x="-55.88" y="0" rot="R90"/>
<instance part="GND7" gate="1" x="53.34" y="-99.06"/>
<instance part="GND8" gate="1" x="-66.04" y="0" rot="R270"/>
<instance part="P+6" gate="G$1" x="-22.86" y="187.96"/>
<instance part="GND9" gate="1" x="-22.86" y="162.56"/>
<instance part="R7" gate="G$1" x="-22.86" y="180.34" rot="R90"/>
<instance part="C13" gate="G$1" x="-22.86" y="170.18"/>
<instance part="GND11" gate="1" x="-185.42" y="-91.44" rot="R90"/>
<instance part="C14" gate="G$1" x="-287.02" y="-60.96"/>
<instance part="C15" gate="G$1" x="-271.78" y="-63.5"/>
<instance part="L1" gate="G$1" x="-302.26" y="-55.88"/>
<instance part="GND13" gate="1" x="-96.52" y="60.96" rot="R270"/>
<instance part="X1" gate="G$1" x="-157.48" y="101.6" rot="MR0"/>
<instance part="GND14" gate="1" x="-154.94" y="96.52"/>
<instance part="R12" gate="G$1" x="-134.62" y="106.68"/>
<instance part="R13" gate="G$1" x="-144.78" y="109.22"/>
<instance part="XP1" gate="G$1" x="-139.7" y="162.56" rot="MR0"/>
<instance part="P+11" gate="G$1" x="-152.4" y="187.96" rot="R90"/>
<instance part="R17" gate="G$1" x="-124.46" y="180.34" rot="R90"/>
<instance part="R18" gate="G$1" x="-116.84" y="180.34" rot="R90"/>
<instance part="R19" gate="G$1" x="-109.22" y="180.34" rot="R90"/>
<instance part="R20" gate="G$1" x="-101.6" y="180.34" rot="R90"/>
<instance part="R21" gate="G$1" x="-93.98" y="180.34" rot="R90"/>
<instance part="R22" gate="G$1" x="-124.46" y="142.24" rot="R90"/>
<instance part="R23" gate="G$1" x="-116.84" y="142.24" rot="R90"/>
<instance part="R24" gate="G$1" x="-109.22" y="142.24" rot="R90"/>
<instance part="GND21" gate="1" x="-109.22" y="132.08"/>
<instance part="GND22" gate="1" x="-149.86" y="132.08"/>
<instance part="JP1" gate="G$1" x="198.12" y="137.16"/>
<instance part="GND24" gate="1" x="210.82" y="124.46"/>
<instance part="P+13" gate="G$1" x="182.88" y="142.24" rot="R90"/>
<instance part="JP2" gate="G$1" x="198.12" y="167.64"/>
<instance part="GND26" gate="1" x="210.82" y="154.94"/>
<instance part="P+14" gate="G$1" x="182.88" y="172.72" rot="R90"/>
<instance part="GND28" gate="1" x="-238.76" y="-20.32"/>
<instance part="GND30" gate="1" x="-269.24" y="-20.32"/>
<instance part="P+18" gate="G$1" x="-218.44" y="2.54"/>
<instance part="GND31" gate="1" x="-218.44" y="-20.32"/>
<instance part="R27" gate="G$1" x="76.2" y="78.74" rot="R90"/>
<instance part="P+16" gate="G$1" x="66.04" y="86.36"/>
<instance part="R28" gate="G$1" x="66.04" y="76.2" rot="R90"/>
<instance part="U44" gate="G$1" x="309.88" y="17.78"/>
<instance part="U2" gate="G$1" x="309.88" y="-12.7"/>
<instance part="IC1" gate="G$1" x="83.82" y="-215.9"/>
<instance part="C20" gate="G$1" x="327.66" y="-15.24"/>
<instance part="P+12" gate="G$1" x="327.66" y="-7.62"/>
<instance part="GND23" gate="1" x="294.64" y="-27.94"/>
<instance part="GND25" gate="1" x="71.12" y="-228.6"/>
<instance part="C21" gate="G$1" x="104.14" y="-208.28" rot="MR180"/>
<instance part="C27" gate="G$1" x="287.02" y="17.78" rot="MR180"/>
<instance part="GND32" gate="1" x="287.02" y="7.62"/>
<instance part="P+19" gate="G$1" x="284.48" y="20.32" rot="R90"/>
<instance part="BAT1" gate="G$1" x="-83.82" y="68.58" rot="R180"/>
<instance part="VD8" gate="G$1" x="129.54" y="139.7" rot="R90"/>
<instance part="XP2" gate="G$1" x="109.22" y="142.24" rot="MR270"/>
<instance part="GND15" gate="1" x="114.3" y="132.08"/>
<instance part="R29" gate="G$1" x="121.92" y="142.24"/>
<instance part="R32" gate="G$1" x="63.5" y="-76.2" rot="R270"/>
<instance part="XP6" gate="G$1" x="-154.94" y="-170.18" rot="MR270"/>
<instance part="XP8" gate="G$1" x="-101.6" y="-160.02"/>
<instance part="XP9" gate="G$1" x="-88.9" y="-160.02"/>
<instance part="XP10" gate="G$1" x="-76.2" y="-160.02"/>
<instance part="XP11" gate="G$1" x="-63.5" y="-160.02"/>
<instance part="XP12" gate="G$1" x="-50.8" y="-160.02"/>
<instance part="XP13" gate="G$1" x="-38.1" y="-160.02"/>
<instance part="XP14" gate="G$1" x="-25.4" y="-160.02"/>
<instance part="XP15" gate="G$1" x="-12.7" y="-160.02"/>
<instance part="GND44" gate="1" x="27.94" y="-167.64" rot="R90"/>
<instance part="R33" gate="G$1" x="350.52" y="-215.9"/>
<instance part="R45" gate="G$1" x="340.36" y="-215.9" rot="MR180"/>
<instance part="C50" gate="G$1" x="284.48" y="-246.38"/>
<instance part="DA3" gate="G$1" x="304.8" y="-243.84" smashed="yes">
<attribute name="NAME" x="306.324" y="-234.95" size="1.778" layer="95"/>
<attribute name="VALUE" x="306.07" y="-254" size="1.778" layer="96"/>
</instance>
<instance part="R47" gate="G$1" x="345.44" y="-251.46" rot="MR90"/>
<instance part="R48" gate="G$1" x="325.12" y="-243.84" rot="MR0"/>
<instance part="R54" gate="G$1" x="119.38" y="-45.72"/>
<instance part="R55" gate="G$1" x="119.38" y="-48.26"/>
<instance part="R56" gate="G$1" x="111.76" y="-58.42" rot="R90"/>
<instance part="R57" gate="G$1" x="91.44" y="-58.42" rot="R90"/>
<instance part="U$13" gate="6V" x="127" y="-48.26" rot="R270"/>
<instance part="C51" gate="G$1" x="-266.7" y="-106.68"/>
<instance part="C52" gate="G$1" x="-218.44" y="-106.68"/>
<instance part="U$5" gate="6V" x="-269.24" y="12.7"/>
<instance part="Q1" gate="G$1" x="-269.24" y="-93.98"/>
<instance part="R58" gate="G$1" x="-287.02" y="-91.44"/>
<instance part="R59" gate="G$1" x="-292.1" y="-86.36" rot="R270"/>
<instance part="C54" gate="G$1" x="-281.94" y="-96.52"/>
<instance part="C55" gate="G$1" x="-248.92" y="-109.22"/>
<instance part="IC3" gate="G$1" x="-236.22" y="-101.6"/>
<instance part="U$7" gate="G$1" x="198.12" y="96.52" rot="MR180"/>
<instance part="P+23" gate="G$1" x="213.36" y="99.06" rot="MR90"/>
<instance part="R30" gate="G$1" x="165.1" y="101.6" rot="MR0"/>
<instance part="R31" gate="G$1" x="175.26" y="99.06" rot="MR0"/>
<instance part="R60" gate="G$1" x="165.1" y="96.52" rot="MR0"/>
<instance part="T3" gate="G$1" x="-302.26" y="-96.52"/>
<instance part="R61" gate="G$1" x="-312.42" y="-96.52" rot="R180"/>
<instance part="U$1" gate="6V" x="114.3" y="152.4"/>
<instance part="D2" gate="G$1" x="-279.4" y="5.08"/>
<instance part="F3" gate="G$1" x="-304.8" y="-2.54"/>
<instance part="D3" gate="G$1" x="-289.56" y="-10.16"/>
<instance part="GND57" gate="1" x="-289.56" y="-20.32"/>
<instance part="S2" gate="1" x="-30.48" y="170.18"/>
<instance part="C24" gate="G$1" x="363.22" y="-210.82" rot="R90"/>
<instance part="XP17" gate="G$1" x="0" y="-160.02"/>
<instance part="R36" gate="G$1" x="302.26" y="-119.38" rot="MR180"/>
<instance part="R51" gate="G$1" x="302.26" y="-129.54" rot="MR180"/>
<instance part="IC2" gate="G$1" x="330.2" y="-124.46"/>
<instance part="C45" gate="G$1" x="309.88" y="-127"/>
<instance part="XP18" gate="G$1" x="289.56" y="-121.92" rot="MR270"/>
<instance part="JP3" gate="G$1" x="-248.92" y="-175.26" rot="R90"/>
<instance part="JP7" gate="G$1" x="-248.92" y="-170.18" rot="R90"/>
<instance part="JP8" gate="G$1" x="-241.3" y="-175.26" rot="R90"/>
<instance part="JP9" gate="G$1" x="-241.3" y="-170.18" rot="R90"/>
<instance part="C31" gate="G$1" x="-269.24" y="-10.16"/>
<instance part="C34" gate="G$1" x="-218.44" y="-10.16"/>
<instance part="XP16" gate="G$1" x="-154.94" y="-160.02" rot="R90"/>
<instance part="GND10" gate="1" x="-129.54" y="-154.94" rot="R90"/>
<instance part="P+27" gate="G$1" x="-137.16" y="-157.48" rot="R270"/>
<instance part="R75" gate="G$1" x="335.28" y="15.24" rot="MR0"/>
<instance part="R64" gate="G$1" x="15.24" y="-167.64"/>
<instance part="C22" gate="G$1" x="353.06" y="-119.38" rot="R90"/>
<instance part="C23" gate="G$1" x="-35.56" y="81.28"/>
<instance part="GND12" gate="1" x="-35.56" y="91.44" rot="R180"/>
<instance part="C44" gate="G$1" x="-40.64" y="25.4" rot="R90"/>
<instance part="DA1" gate="G$1" x="-238.76" y="-2.54"/>
<instance part="D1" gate="G$1" x="-320.04" y="-2.54"/>
<instance part="U$3" gate="6V" x="-312.42" y="-55.88" rot="R90"/>
<instance part="DA4" gate="G$1" x="-246.38" y="-58.42"/>
<instance part="C16" gate="G$1" x="-231.14" y="-71.12"/>
<instance part="P+7" gate="G$1" x="337.82" y="160.02" rot="R270"/>
<instance part="DD2" gate="G$1" x="304.8" y="149.86"/>
<instance part="GND16" gate="1" x="327.66" y="127"/>
<instance part="R8" gate="G$1" x="279.4" y="134.62" rot="MR270"/>
<instance part="P+9" gate="G$1" x="-132.08" y="-172.72" rot="R270"/>
<instance part="GND17" gate="1" x="-147.32" y="-177.8"/>
<instance part="DA5" gate=":1" x="358.14" y="-233.68"/>
<instance part="DA2" gate="G$1" x="287.02" y="-180.34"/>
<instance part="C17" gate="G$1" x="307.34" y="-175.26" rot="R90"/>
<instance part="R10" gate="G$1" x="317.5" y="-177.8"/>
<instance part="C18" gate="G$1" x="325.12" y="-182.88"/>
<instance part="VD1" gate="G$1" x="335.28" y="-182.88" rot="R90"/>
<instance part="DD3" gate="G$1" x="337.82" y="63.5"/>
<instance part="GND19" gate="1" x="358.14" y="38.1"/>
<instance part="C19" gate="G$1" x="294.64" y="60.96" rot="R180"/>
<instance part="C25" gate="G$1" x="284.48" y="58.42" rot="MR0"/>
<instance part="P+10" gate="G$1" x="259.08" y="78.74" rot="MR270"/>
<instance part="C26" gate="G$1" x="274.32" y="60.96" rot="R180"/>
<instance part="C28" gate="G$1" x="312.42" y="60.96" rot="R180"/>
<instance part="R14" gate="G$1" x="363.22" y="68.58" rot="MR180"/>
<instance part="C29" gate="G$1" x="264.16" y="60.96" rot="R180"/>
<instance part="Q3" gate="G$1" x="86.36" y="-149.86" rot="R90"/>
<instance part="R15" gate="G$1" x="78.74" y="-157.48"/>
<instance part="P+17" gate="G$1" x="139.7" y="-218.44" rot="R270"/>
<instance part="Q4" gate="G$1" x="119.38" y="-210.82" rot="R270"/>
<instance part="R16" gate="G$1" x="132.08" y="-213.36" rot="R90"/>
<instance part="VD2" gate="G$1" x="101.6" y="-58.42" rot="R90"/>
<instance part="VD3" gate="G$1" x="81.28" y="-58.42" rot="R90"/>
<instance part="DD5" gate="G$1" x="345.44" y="-60.96"/>
<instance part="GND18" gate="1" x="320.04" y="-83.82"/>
<instance part="P+15" gate="G$1" x="320.04" y="-43.18"/>
<instance part="C30" gate="G$1" x="370.84" y="-71.12"/>
<instance part="C32" gate="G$1" x="309.88" y="-68.58"/>
<instance part="C33" gate="G$1" x="281.94" y="-66.04"/>
<instance part="C35" gate="G$1" x="289.56" y="-68.58"/>
<instance part="C36" gate="G$1" x="299.72" y="-68.58"/>
<instance part="C37" gate="G$1" x="106.68" y="-55.88" rot="MR180"/>
<instance part="C39" gate="G$1" x="86.36" y="-55.88" rot="MR180"/>
<instance part="R11" gate="G$1" x="114.3" y="68.58" rot="R90"/>
<instance part="P+20" gate="G$1" x="104.14" y="76.2"/>
<instance part="R25" gate="G$1" x="104.14" y="66.04" rot="R90"/>
<instance part="R26" gate="G$1" x="76.2" y="50.8" rot="MR0"/>
<instance part="R37" gate="G$1" x="76.2" y="45.72" rot="MR0"/>
<instance part="R38" gate="G$1" x="-101.6" y="-175.26" rot="R90"/>
<instance part="R39" gate="G$1" x="-88.9" y="-175.26" rot="R90"/>
<instance part="R40" gate="G$1" x="-76.2" y="-175.26" rot="R90"/>
<instance part="R41" gate="G$1" x="-63.5" y="-175.26" rot="R90"/>
<instance part="R42" gate="G$1" x="-50.8" y="-175.26" rot="R90"/>
<instance part="R43" gate="G$1" x="-38.1" y="-175.26" rot="R90"/>
<instance part="R44" gate="G$1" x="-25.4" y="-175.26" rot="R90"/>
<instance part="R46" gate="G$1" x="-12.7" y="-175.26" rot="R90"/>
<instance part="C38" gate="G$1" x="-124.46" y="27.94"/>
<instance part="DA6" gate="G$1" x="304.8" y="-218.44"/>
<instance part="GND20" gate="1" x="287.02" y="-226.06"/>
<instance part="P+8" gate="G$1" x="289.56" y="-208.28"/>
<instance part="VD4" gate="1" x="-73.66" y="68.58"/>
<instance part="C40" gate="G$1" x="-53.34" y="63.5" rot="MR0"/>
<instance part="JP6" gate="G$1" x="198.12" y="195.58"/>
<instance part="P+22" gate="G$1" x="185.42" y="200.66"/>
<instance part="GND27" gate="1" x="210.82" y="203.2" rot="R180"/>
<instance part="C41" gate="G$1" x="-213.36" y="-63.5"/>
<instance part="C42" gate="G$1" x="-256.54" y="-12.7"/>
<instance part="GND29" gate="1" x="-256.54" y="-20.32"/>
<instance part="C43" gate="G$1" x="332.74" y="-254"/>
<instance part="R6" gate="G$1" x="-195.58" y="-91.44"/>
</instances>
<busses>
</busses>
<nets>
<net name="3.3V" class="0">
<segment>
<pinref part="C6" gate="G$1" pin="+"/>
<wire x1="-139.7" y1="45.72" x2="-139.7" y2="33.02" width="0.1524" layer="91"/>
<pinref part="P+1" gate="G$1" pin="3.3V"/>
<wire x1="-33.02" y1="33.02" x2="-73.66" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="35.56" x2="-73.66" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="35.56" x2="-83.82" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-83.82" y1="35.56" x2="-83.82" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="33.02" x2="-73.66" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="38.1" x2="-73.66" y2="38.1" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="38.1" x2="-93.98" y2="38.1" width="0.1524" layer="91"/>
<wire x1="-93.98" y1="38.1" x2="-93.98" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="35.56" x2="-73.66" y2="38.1" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="40.64" x2="-73.66" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="40.64" x2="-104.14" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-104.14" y1="40.64" x2="-104.14" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="38.1" x2="-73.66" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="43.18" x2="-73.66" y2="43.18" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="40.64" x2="-73.66" y2="43.18" width="0.1524" layer="91"/>
<junction x="-73.66" y="33.02"/>
<junction x="-73.66" y="35.56"/>
<junction x="-73.66" y="38.1"/>
<junction x="-73.66" y="40.64"/>
<pinref part="C1" gate="G$1" pin="1"/>
<pinref part="C2" gate="G$1" pin="1"/>
<pinref part="C3" gate="G$1" pin="1"/>
<pinref part="C4" gate="G$1" pin="1"/>
<pinref part="DD1" gate="G$1" pin="VDD@6"/>
<pinref part="DD1" gate="G$1" pin="VDD@5"/>
<pinref part="DD1" gate="G$1" pin="VDD@2"/>
<pinref part="DD1" gate="G$1" pin="VDD@3"/>
<pinref part="DD1" gate="G$1" pin="VDD@4"/>
<pinref part="DD1" gate="G$1" pin="VDD@1"/>
<wire x1="-33.02" y1="45.72" x2="-73.66" y2="45.72" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="45.72" x2="-73.66" y2="43.18" width="0.1524" layer="91"/>
<junction x="-73.66" y="43.18"/>
<wire x1="-73.66" y1="45.72" x2="-124.46" y2="45.72" width="0.1524" layer="91"/>
<junction x="-73.66" y="45.72"/>
<pinref part="C5" gate="G$1" pin="1"/>
<wire x1="-114.3" y1="43.18" x2="-114.3" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="43.18" x2="-114.3" y2="43.18" width="0.1524" layer="91"/>
<pinref part="C38" gate="G$1" pin="1"/>
<wire x1="-124.46" y1="45.72" x2="-124.46" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="45.72" x2="-139.7" y2="45.72" width="0.1524" layer="91"/>
<junction x="-124.46" y="45.72"/>
<junction x="-139.7" y="45.72"/>
</segment>
<segment>
<wire x1="116.84" y1="-180.34" x2="116.84" y2="-175.26" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="2"/>
<pinref part="P+3" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="33.02" y1="142.24" x2="33.02" y2="144.78" width="0.1524" layer="91"/>
<pinref part="JP5" gate="G$1" pin="3"/>
<pinref part="P+4" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="33.02" y1="182.88" x2="33.02" y2="180.34" width="0.1524" layer="91"/>
<pinref part="JP4" gate="G$1" pin="3"/>
<pinref part="P+5" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="-22.86" y1="185.42" x2="-22.86" y2="187.96" width="0.1524" layer="91"/>
<pinref part="R7" gate="G$1" pin="2"/>
<pinref part="P+6" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="-152.4" y1="187.96" x2="-149.86" y2="187.96" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="187.96" x2="-129.54" y2="187.96" width="0.1524" layer="91"/>
<wire x1="-129.54" y1="187.96" x2="-124.46" y2="187.96" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="187.96" x2="-124.46" y2="185.42" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="187.96" x2="-116.84" y2="187.96" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="187.96" x2="-116.84" y2="185.42" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="187.96" x2="-109.22" y2="187.96" width="0.1524" layer="91"/>
<wire x1="-109.22" y1="187.96" x2="-109.22" y2="185.42" width="0.1524" layer="91"/>
<wire x1="-109.22" y1="187.96" x2="-101.6" y2="187.96" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="187.96" x2="-101.6" y2="185.42" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="187.96" x2="-93.98" y2="187.96" width="0.1524" layer="91"/>
<wire x1="-93.98" y1="187.96" x2="-93.98" y2="185.42" width="0.1524" layer="91"/>
<wire x1="-132.08" y1="172.72" x2="-129.54" y2="172.72" width="0.1524" layer="91"/>
<wire x1="-129.54" y1="172.72" x2="-129.54" y2="187.96" width="0.1524" layer="91"/>
<wire x1="-147.32" y1="172.72" x2="-149.86" y2="172.72" width="0.1524" layer="91"/>
<wire x1="-149.86" y1="172.72" x2="-149.86" y2="187.96" width="0.1524" layer="91"/>
<junction x="-124.46" y="187.96"/>
<junction x="-116.84" y="187.96"/>
<junction x="-109.22" y="187.96"/>
<junction x="-101.6" y="187.96"/>
<junction x="-129.54" y="187.96"/>
<junction x="-149.86" y="187.96"/>
<pinref part="P+11" gate="G$1" pin="3.3V"/>
<pinref part="R17" gate="G$1" pin="2"/>
<pinref part="R18" gate="G$1" pin="2"/>
<pinref part="R19" gate="G$1" pin="2"/>
<pinref part="R20" gate="G$1" pin="2"/>
<pinref part="R21" gate="G$1" pin="2"/>
<pinref part="XP1" gate="G$1" pin="1"/>
<pinref part="XP1" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="190.5" y1="142.24" x2="182.88" y2="142.24" width="0.1524" layer="91"/>
<pinref part="JP1" gate="G$1" pin="1"/>
<pinref part="P+13" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="190.5" y1="172.72" x2="182.88" y2="172.72" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="1"/>
<pinref part="P+14" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="66.04" y1="86.36" x2="66.04" y2="83.82" width="0.1524" layer="91"/>
<wire x1="66.04" y1="83.82" x2="66.04" y2="81.28" width="0.1524" layer="91"/>
<wire x1="66.04" y1="83.82" x2="76.2" y2="83.82" width="0.1524" layer="91"/>
<junction x="66.04" y="83.82"/>
<pinref part="P+16" gate="G$1" pin="3.3V"/>
<pinref part="R28" gate="G$1" pin="2"/>
<pinref part="R27" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="327.66" y1="-10.16" x2="320.04" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="327.66" y1="-10.16" x2="327.66" y2="-7.62" width="0.1524" layer="91"/>
<junction x="327.66" y="-10.16"/>
<pinref part="C20" gate="G$1" pin="1"/>
<pinref part="U2" gate="G$1" pin="VDD"/>
<pinref part="P+12" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<wire x1="287.02" y1="20.32" x2="284.48" y2="20.32" width="0.1524" layer="91"/>
<wire x1="297.18" y1="20.32" x2="287.02" y2="20.32" width="0.1524" layer="91"/>
<wire x1="297.18" y1="17.78" x2="297.18" y2="20.32" width="0.1524" layer="91"/>
<wire x1="325.12" y1="12.7" x2="327.66" y2="12.7" width="0.1524" layer="91"/>
<wire x1="327.66" y1="12.7" x2="327.66" y2="27.94" width="0.1524" layer="91"/>
<wire x1="327.66" y1="27.94" x2="287.02" y2="27.94" width="0.1524" layer="91"/>
<wire x1="287.02" y1="27.94" x2="287.02" y2="20.32" width="0.1524" layer="91"/>
<junction x="287.02" y="20.32"/>
<junction x="297.18" y="20.32"/>
<pinref part="U44" gate="G$1" pin="VDDA"/>
<pinref part="P+19" gate="G$1" pin="3.3V"/>
<pinref part="C27" gate="G$1" pin="2"/>
<pinref part="U44" gate="G$1" pin="VDDD"/>
<pinref part="U44" gate="G$1" pin="XCLR"/>
</segment>
<segment>
<wire x1="-218.44" y1="-2.54" x2="-231.14" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="-218.44" y1="-7.62" x2="-218.44" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="-218.44" y1="2.54" x2="-218.44" y2="-2.54" width="0.1524" layer="91"/>
<junction x="-218.44" y="-2.54"/>
<junction x="-218.44" y="-2.54"/>
<pinref part="P+18" gate="G$1" pin="3.3V"/>
<pinref part="C34" gate="G$1" pin="+"/>
<pinref part="DA1" gate="G$1" pin="OUT"/>
</segment>
<segment>
<wire x1="213.36" y1="99.06" x2="210.82" y2="99.06" width="0.1524" layer="91"/>
<pinref part="P+23" gate="G$1" pin="3.3V"/>
<pinref part="U$7" gate="G$1" pin="A"/>
</segment>
<segment>
<wire x1="-152.4" y1="-157.48" x2="-137.16" y2="-157.48" width="0.1524" layer="91"/>
<pinref part="XP16" gate="G$1" pin="2"/>
<pinref part="P+27" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<pinref part="DD2" gate="G$1" pin="VDDRTC"/>
<pinref part="DD2" gate="G$1" pin="VDD@3"/>
<wire x1="327.66" y1="152.4" x2="327.66" y2="154.94" width="0.1524" layer="91"/>
<pinref part="DD2" gate="G$1" pin="VDD@2"/>
<wire x1="327.66" y1="154.94" x2="327.66" y2="157.48" width="0.1524" layer="91"/>
<junction x="327.66" y="154.94"/>
<pinref part="DD2" gate="G$1" pin="VDD@1"/>
<wire x1="327.66" y1="157.48" x2="327.66" y2="160.02" width="0.1524" layer="91"/>
<junction x="327.66" y="157.48"/>
<pinref part="P+7" gate="G$1" pin="3.3V"/>
<wire x1="327.66" y1="160.02" x2="337.82" y2="160.02" width="0.1524" layer="91"/>
<junction x="327.66" y="160.02"/>
</segment>
<segment>
<wire x1="-152.4" y1="-172.72" x2="-132.08" y2="-172.72" width="0.1524" layer="91"/>
<pinref part="XP6" gate="G$1" pin="2"/>
<pinref part="P+9" gate="G$1" pin="3.3V"/>
</segment>
<segment>
<pinref part="C29" gate="G$1" pin="2"/>
<wire x1="264.16" y1="63.5" x2="264.16" y2="78.74" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="VLOGIC"/>
<wire x1="264.16" y1="78.74" x2="284.48" y2="78.74" width="0.1524" layer="91"/>
<pinref part="P+10" gate="G$1" pin="3.3V"/>
<wire x1="284.48" y1="78.74" x2="320.04" y2="78.74" width="0.1524" layer="91"/>
<wire x1="264.16" y1="78.74" x2="259.08" y2="78.74" width="0.1524" layer="91"/>
<junction x="264.16" y="78.74"/>
<pinref part="C25" gate="G$1" pin="1"/>
<wire x1="284.48" y1="63.5" x2="284.48" y2="73.66" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="VDD@13"/>
<wire x1="284.48" y1="73.66" x2="320.04" y2="73.66" width="0.1524" layer="91"/>
<pinref part="C26" gate="G$1" pin="2"/>
<wire x1="274.32" y1="63.5" x2="274.32" y2="76.2" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="VDD@3"/>
<wire x1="274.32" y1="76.2" x2="284.48" y2="76.2" width="0.1524" layer="91"/>
<wire x1="284.48" y1="76.2" x2="320.04" y2="76.2" width="0.1524" layer="91"/>
<wire x1="284.48" y1="73.66" x2="284.48" y2="76.2" width="0.1524" layer="91"/>
<junction x="284.48" y="73.66"/>
<junction x="284.48" y="76.2"/>
<wire x1="284.48" y1="76.2" x2="284.48" y2="78.74" width="0.1524" layer="91"/>
<junction x="284.48" y="78.74"/>
</segment>
<segment>
<pinref part="Q3" gate="G$1" pin="S"/>
<wire x1="81.28" y1="-147.32" x2="73.66" y2="-147.32" width="0.1524" layer="91"/>
<pinref part="R15" gate="G$1" pin="1"/>
<wire x1="73.66" y1="-147.32" x2="73.66" y2="-157.48" width="0.1524" layer="91"/>
<pinref part="P+2" gate="G$1" pin="3.3V"/>
<wire x1="73.66" y1="-157.48" x2="73.66" y2="-162.56" width="0.1524" layer="91"/>
<junction x="73.66" y="-157.48"/>
</segment>
<segment>
<pinref part="Q4" gate="G$1" pin="S"/>
<wire x1="124.46" y1="-213.36" x2="124.46" y2="-218.44" width="0.1524" layer="91"/>
<pinref part="R16" gate="G$1" pin="1"/>
<wire x1="124.46" y1="-218.44" x2="132.08" y2="-218.44" width="0.1524" layer="91"/>
<pinref part="P+17" gate="G$1" pin="3.3V"/>
<wire x1="132.08" y1="-218.44" x2="139.7" y2="-218.44" width="0.1524" layer="91"/>
<junction x="132.08" y="-218.44"/>
</segment>
<segment>
<pinref part="C36" gate="G$1" pin="1"/>
<wire x1="299.72" y1="-63.5" x2="299.72" y2="-53.34" width="0.1524" layer="91"/>
<pinref part="DD5" gate="G$1" pin="VDD_IO"/>
<wire x1="299.72" y1="-53.34" x2="320.04" y2="-53.34" width="0.1524" layer="91"/>
<pinref part="P+15" gate="G$1" pin="3.3V"/>
<wire x1="320.04" y1="-53.34" x2="327.66" y2="-53.34" width="0.1524" layer="91"/>
<wire x1="320.04" y1="-53.34" x2="320.04" y2="-50.8" width="0.1524" layer="91"/>
<junction x="320.04" y="-53.34"/>
<pinref part="DD5" gate="G$1" pin="VDD"/>
<wire x1="320.04" y1="-50.8" x2="320.04" y2="-43.18" width="0.1524" layer="91"/>
<wire x1="327.66" y1="-50.8" x2="320.04" y2="-50.8" width="0.1524" layer="91"/>
<junction x="320.04" y="-50.8"/>
<pinref part="C33" gate="G$1" pin="+"/>
<wire x1="281.94" y1="-50.8" x2="281.94" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="320.04" y1="-50.8" x2="281.94" y2="-50.8" width="0.1524" layer="91"/>
<pinref part="C35" gate="G$1" pin="1"/>
<wire x1="289.56" y1="-63.5" x2="289.56" y2="-53.34" width="0.1524" layer="91"/>
<wire x1="289.56" y1="-53.34" x2="299.72" y2="-53.34" width="0.1524" layer="91"/>
<junction x="299.72" y="-53.34"/>
</segment>
<segment>
<wire x1="104.14" y1="76.2" x2="104.14" y2="73.66" width="0.1524" layer="91"/>
<wire x1="104.14" y1="73.66" x2="104.14" y2="71.12" width="0.1524" layer="91"/>
<wire x1="104.14" y1="73.66" x2="114.3" y2="73.66" width="0.1524" layer="91"/>
<junction x="104.14" y="73.66"/>
<pinref part="P+20" gate="G$1" pin="3.3V"/>
<pinref part="R25" gate="G$1" pin="2"/>
<pinref part="R11" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="DA6" gate="G$1" pin="VDD"/>
<pinref part="P+8" gate="G$1" pin="3.3V"/>
<wire x1="289.56" y1="-208.28" x2="289.56" y2="-213.36" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="1"/>
<pinref part="P+22" gate="G$1" pin="3.3V"/>
<wire x1="190.5" y1="200.66" x2="185.42" y2="200.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<wire x1="124.46" y1="-180.34" x2="124.46" y2="-177.8" width="0.1524" layer="91"/>
<wire x1="124.46" y1="-177.8" x2="127" y2="-177.8" width="0.1524" layer="91"/>
<wire x1="124.46" y1="-177.8" x2="124.46" y2="-175.26" width="0.1524" layer="91"/>
<wire x1="124.46" y1="-175.26" x2="127" y2="-175.26" width="0.1524" layer="91"/>
<wire x1="124.46" y1="-175.26" x2="124.46" y2="-172.72" width="0.1524" layer="91"/>
<wire x1="124.46" y1="-172.72" x2="127" y2="-172.72" width="0.1524" layer="91"/>
<wire x1="124.46" y1="-172.72" x2="124.46" y2="-170.18" width="0.1524" layer="91"/>
<wire x1="124.46" y1="-170.18" x2="127" y2="-170.18" width="0.1524" layer="91"/>
<wire x1="127" y1="-180.34" x2="124.46" y2="-180.34" width="0.1524" layer="91"/>
<junction x="124.46" y="-177.8"/>
<junction x="124.46" y="-175.26"/>
<junction x="124.46" y="-172.72"/>
<junction x="124.46" y="-177.8"/>
<junction x="124.46" y="-180.34"/>
<pinref part="DD4" gate="G$1" pin="SHIELD@4"/>
<pinref part="DD4" gate="G$1" pin="SHIELD@3"/>
<pinref part="DD4" gate="G$1" pin="SHIELD@2"/>
<pinref part="DD4" gate="G$1" pin="SHIELD@1"/>
<pinref part="GND2" gate="1" pin="GND"/>
<pinref part="DD4" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="116.84" y1="-134.62" x2="116.84" y2="-137.16" width="0.1524" layer="91"/>
<pinref part="C8" gate="G$1" pin="1"/>
<pinref part="GND3" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="109.22" y1="-134.62" x2="109.22" y2="-137.16" width="0.1524" layer="91"/>
<pinref part="C7" gate="G$1" pin="-"/>
<pinref part="GND4" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="33.02" y1="137.16" x2="33.02" y2="121.92" width="0.1524" layer="91"/>
<wire x1="40.64" y1="121.92" x2="33.02" y2="121.92" width="0.1524" layer="91"/>
<junction x="33.02" y="121.92"/>
<pinref part="JP5" gate="G$1" pin="1"/>
<pinref part="GND5" gate="1" pin="GND"/>
<pinref part="LED2" gate="G$1" pin="C"/>
</segment>
<segment>
<wire x1="33.02" y1="160.02" x2="33.02" y2="175.26" width="0.1524" layer="91"/>
<wire x1="40.64" y1="160.02" x2="33.02" y2="160.02" width="0.1524" layer="91"/>
<junction x="33.02" y="160.02"/>
<pinref part="JP4" gate="G$1" pin="1"/>
<pinref part="GND6" gate="1" pin="GND"/>
<pinref part="LED1" gate="G$1" pin="C"/>
</segment>
<segment>
<wire x1="43.18" y1="-93.98" x2="53.34" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="53.34" y1="-93.98" x2="53.34" y2="-96.52" width="0.1524" layer="91"/>
<wire x1="53.34" y1="-93.98" x2="63.5" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="63.5" y1="-93.98" x2="63.5" y2="-81.28" width="0.1524" layer="91"/>
<junction x="53.34" y="-93.98"/>
<pinref part="C9" gate="G$1" pin="2"/>
<pinref part="C10" gate="G$1" pin="2"/>
<pinref part="GND7" gate="1" pin="GND"/>
<pinref part="R32" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="-60.96" y1="0" x2="-63.5" y2="0" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="0" x2="-63.5" y2="5.08" width="0.1524" layer="91"/>
<wire x1="-63.5" y1="5.08" x2="-53.34" y2="5.08" width="0.1524" layer="91"/>
<junction x="-63.5" y="0"/>
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
<pinref part="GND13" gate="1" pin="GND"/>
<pinref part="BAT1" gate="G$1" pin="-"/>
<pinref part="C40" gate="G$1" pin="2"/>
<wire x1="-53.34" y1="60.96" x2="-93.98" y2="60.96" width="0.1524" layer="91"/>
<junction x="-93.98" y="60.96"/>
<wire x1="-93.98" y1="60.96" x2="-93.98" y2="68.58" width="0.1524" layer="91"/>
<wire x1="-93.98" y1="68.58" x2="-88.9" y2="68.58" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="-154.94" y1="99.06" x2="-154.94" y2="101.6" width="0.1524" layer="91"/>
<pinref part="GND14" gate="1" pin="GND"/>
<pinref part="X1" gate="G$1" pin="GND"/>
</segment>
<segment>
<wire x1="-124.46" y1="137.16" x2="-124.46" y2="134.62" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="134.62" x2="-116.84" y2="134.62" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="134.62" x2="-116.84" y2="137.16" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="134.62" x2="-109.22" y2="134.62" width="0.1524" layer="91"/>
<wire x1="-109.22" y1="134.62" x2="-109.22" y2="137.16" width="0.1524" layer="91"/>
<junction x="-116.84" y="134.62"/>
<junction x="-109.22" y="134.62"/>
<pinref part="R22" gate="G$1" pin="1"/>
<pinref part="R23" gate="G$1" pin="1"/>
<pinref part="R24" gate="G$1" pin="1"/>
<pinref part="GND21" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="-149.86" y1="134.62" x2="-149.86" y2="149.86" width="0.1524" layer="91"/>
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
<wire x1="205.74" y1="132.08" x2="210.82" y2="132.08" width="0.1524" layer="91"/>
<wire x1="210.82" y1="132.08" x2="210.82" y2="127" width="0.1524" layer="91"/>
<pinref part="JP1" gate="G$1" pin="10"/>
<pinref part="GND24" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="205.74" y1="162.56" x2="210.82" y2="162.56" width="0.1524" layer="91"/>
<wire x1="210.82" y1="162.56" x2="210.82" y2="157.48" width="0.1524" layer="91"/>
<pinref part="JP2" gate="G$1" pin="10"/>
<pinref part="GND26" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="-238.76" y1="-17.78" x2="-238.76" y2="-10.16" width="0.1524" layer="91"/>
<pinref part="GND28" gate="1" pin="GND"/>
<pinref part="DA1" gate="G$1" pin="ADJ"/>
</segment>
<segment>
<wire x1="-218.44" y1="-17.78" x2="-218.44" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="GND31" gate="1" pin="GND"/>
<pinref part="C34" gate="G$1" pin="-"/>
</segment>
<segment>
<wire x1="297.18" y1="-17.78" x2="294.64" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="294.64" y1="-17.78" x2="294.64" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="320.04" y1="-12.7" x2="322.58" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="322.58" y1="-12.7" x2="322.58" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="322.58" y1="-15.24" x2="320.04" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="322.58" y1="-15.24" x2="322.58" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="322.58" y1="-17.78" x2="320.04" y2="-17.78" width="0.1524" layer="91"/>
<wire x1="322.58" y1="-17.78" x2="322.58" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="322.58" y1="-25.4" x2="294.64" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="327.66" y1="-17.78" x2="327.66" y2="-25.4" width="0.1524" layer="91"/>
<wire x1="327.66" y1="-25.4" x2="322.58" y2="-25.4" width="0.1524" layer="91"/>
<junction x="322.58" y="-15.24"/>
<junction x="322.58" y="-17.78"/>
<junction x="294.64" y="-25.4"/>
<junction x="322.58" y="-25.4"/>
<pinref part="U2" gate="G$1" pin="GND"/>
<pinref part="GND23" gate="1" pin="GND"/>
<pinref part="U2" gate="G$1" pin="A0"/>
<pinref part="U2" gate="G$1" pin="A1"/>
<pinref part="U2" gate="G$1" pin="A2"/>
<pinref part="C20" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="71.12" y1="-213.36" x2="73.66" y2="-213.36" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-215.9" x2="71.12" y2="-213.36" width="0.1524" layer="91"/>
<wire x1="73.66" y1="-215.9" x2="71.12" y2="-215.9" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-226.06" x2="71.12" y2="-220.98" width="0.1524" layer="91"/>
<wire x1="73.66" y1="-220.98" x2="71.12" y2="-220.98" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-220.98" x2="71.12" y2="-218.44" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-218.44" x2="71.12" y2="-215.9" width="0.1524" layer="91"/>
<wire x1="73.66" y1="-218.44" x2="71.12" y2="-218.44" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-213.36" x2="71.12" y2="-205.74" width="0.1524" layer="91"/>
<wire x1="96.52" y1="-215.9" x2="99.06" y2="-215.9" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-205.74" x2="99.06" y2="-205.74" width="0.1524" layer="91"/>
<wire x1="99.06" y1="-205.74" x2="99.06" y2="-215.9" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-205.74" x2="99.06" y2="-205.74" width="0.1524" layer="91"/>
<junction x="71.12" y="-215.9"/>
<junction x="71.12" y="-220.98"/>
<junction x="71.12" y="-218.44"/>
<junction x="71.12" y="-213.36"/>
<junction x="99.06" y="-205.74"/>
<pinref part="IC1" gate="G$1" pin="A0"/>
<pinref part="IC1" gate="G$1" pin="A1"/>
<pinref part="GND25" gate="1" pin="GND"/>
<pinref part="IC1" gate="G$1" pin="GND"/>
<pinref part="IC1" gate="G$1" pin="A2"/>
<pinref part="IC1" gate="G$1" pin="WP"/>
<pinref part="C21" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="297.18" y1="12.7" x2="287.02" y2="12.7" width="0.1524" layer="91"/>
<wire x1="287.02" y1="10.16" x2="287.02" y2="12.7" width="0.1524" layer="91"/>
<junction x="287.02" y="12.7"/>
<pinref part="U44" gate="G$1" pin="GND"/>
<pinref part="C27" gate="G$1" pin="1"/>
<pinref part="GND32" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="-289.56" y1="-17.78" x2="-289.56" y2="-12.7" width="0.1524" layer="91"/>
<pinref part="GND57" gate="1" pin="GND"/>
<pinref part="D3" gate="G$1" pin="A"/>
</segment>
<segment>
<wire x1="-269.24" y1="-17.78" x2="-269.24" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="GND30" gate="1" pin="GND"/>
<pinref part="C31" gate="G$1" pin="-"/>
</segment>
<segment>
<wire x1="-152.4" y1="-154.94" x2="-132.08" y2="-154.94" width="0.1524" layer="91"/>
<pinref part="XP16" gate="G$1" pin="3"/>
<pinref part="GND10" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="114.3" y1="134.62" x2="114.3" y2="137.16" width="0.1524" layer="91"/>
<wire x1="114.3" y1="137.16" x2="111.76" y2="137.16" width="0.1524" layer="91"/>
<wire x1="129.54" y1="137.16" x2="114.3" y2="137.16" width="0.1524" layer="91"/>
<junction x="114.3" y="137.16"/>
<pinref part="GND15" gate="1" pin="GND"/>
<pinref part="XP2" gate="G$1" pin="3"/>
<pinref part="VD8" gate="G$1" pin="A"/>
</segment>
<segment>
<wire x1="20.32" y1="-167.64" x2="25.4" y2="-167.64" width="0.1524" layer="91"/>
<pinref part="R64" gate="G$1" pin="2"/>
<pinref part="GND44" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="-35.56" y1="86.36" x2="-35.56" y2="88.9" width="0.1524" layer="91"/>
<pinref part="C23" gate="G$1" pin="1"/>
<pinref part="GND12" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="-83.82" y1="22.86" x2="-83.82" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="22.86" x2="-83.82" y2="22.86" width="0.1524" layer="91"/>
<wire x1="-93.98" y1="20.32" x2="-93.98" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="20.32" x2="-73.66" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="20.32" x2="-93.98" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-104.14" y1="17.78" x2="-104.14" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="17.78" x2="-73.66" y2="17.78" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="17.78" x2="-104.14" y2="17.78" width="0.1524" layer="91"/>
<wire x1="-114.3" y1="15.24" x2="-114.3" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-114.3" y1="15.24" x2="-124.46" y2="15.24" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="15.24" x2="-139.7" y2="15.24" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="15.24" x2="-45.72" y2="15.24" width="0.1524" layer="91"/>
<wire x1="-45.72" y1="15.24" x2="-73.66" y2="15.24" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="15.24" x2="-114.3" y2="15.24" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="15.24" x2="-73.66" y2="17.78" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="17.78" x2="-73.66" y2="20.32" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="20.32" x2="-73.66" y2="22.86" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="22.86" x2="-73.66" y2="25.4" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="22.86" x2="-73.66" y2="22.86" width="0.1524" layer="91"/>
<wire x1="-45.72" y1="25.4" x2="-45.72" y2="15.24" width="0.1524" layer="91"/>
<junction x="-114.3" y="15.24"/>
<junction x="-73.66" y="15.24"/>
<junction x="-73.66" y="17.78"/>
<junction x="-73.66" y="20.32"/>
<junction x="-73.66" y="22.86"/>
<junction x="-45.72" y="15.24"/>
<pinref part="C1" gate="G$1" pin="2"/>
<pinref part="C2" gate="G$1" pin="2"/>
<pinref part="C3" gate="G$1" pin="2"/>
<pinref part="C4" gate="G$1" pin="2"/>
<pinref part="GND1" gate="1" pin="GND"/>
<pinref part="C5" gate="G$1" pin="2"/>
<pinref part="C44" gate="G$1" pin="1"/>
<pinref part="DD1" gate="G$1" pin="GND@4"/>
<pinref part="DD1" gate="G$1" pin="GND@3"/>
<pinref part="DD1" gate="G$1" pin="GND@1"/>
<pinref part="DD1" gate="G$1" pin="GND@2"/>
<pinref part="C38" gate="G$1" pin="2"/>
<wire x1="-124.46" y1="25.4" x2="-124.46" y2="15.24" width="0.1524" layer="91"/>
<junction x="-124.46" y="15.24"/>
<pinref part="C6" gate="G$1" pin="-"/>
<wire x1="-139.7" y1="25.4" x2="-139.7" y2="15.24" width="0.1524" layer="91"/>
<junction x="-139.7" y="15.24"/>
</segment>
<segment>
<pinref part="GND16" gate="1" pin="GND"/>
<pinref part="DD2" gate="G$1" pin="GND@3"/>
<wire x1="327.66" y1="129.54" x2="327.66" y2="142.24" width="0.1524" layer="91"/>
<pinref part="DD2" gate="G$1" pin="GND@2"/>
<wire x1="327.66" y1="142.24" x2="327.66" y2="144.78" width="0.1524" layer="91"/>
<junction x="327.66" y="142.24"/>
<pinref part="DD2" gate="G$1" pin="GND@1"/>
<wire x1="327.66" y1="144.78" x2="327.66" y2="147.32" width="0.1524" layer="91"/>
<junction x="327.66" y="144.78"/>
<pinref part="R8" gate="G$1" pin="2"/>
<wire x1="327.66" y1="129.54" x2="279.4" y2="129.54" width="0.1524" layer="91"/>
<junction x="327.66" y="129.54"/>
</segment>
<segment>
<wire x1="-147.32" y1="-175.26" x2="-152.4" y2="-175.26" width="0.1524" layer="91"/>
<pinref part="XP6" gate="G$1" pin="3"/>
<pinref part="GND17" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="GND19" gate="1" pin="GND"/>
<wire x1="358.14" y1="40.64" x2="358.14" y2="43.18" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="AD0"/>
<wire x1="358.14" y1="43.18" x2="358.14" y2="66.04" width="0.1524" layer="91"/>
<wire x1="358.14" y1="66.04" x2="355.6" y2="66.04" width="0.1524" layer="91"/>
<wire x1="358.14" y1="43.18" x2="317.5" y2="43.18" width="0.1524" layer="91"/>
<junction x="358.14" y="43.18"/>
<wire x1="317.5" y1="43.18" x2="317.5" y2="50.8" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="GND@18"/>
<wire x1="317.5" y1="50.8" x2="317.5" y2="53.34" width="0.1524" layer="91"/>
<wire x1="317.5" y1="53.34" x2="317.5" y2="55.88" width="0.1524" layer="91"/>
<wire x1="317.5" y1="55.88" x2="320.04" y2="55.88" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="GND@17"/>
<wire x1="317.5" y1="53.34" x2="320.04" y2="53.34" width="0.1524" layer="91"/>
<junction x="317.5" y="53.34"/>
<pinref part="DD3" gate="G$1" pin="GND@15"/>
<wire x1="317.5" y1="50.8" x2="320.04" y2="50.8" width="0.1524" layer="91"/>
<junction x="317.5" y="50.8"/>
<wire x1="317.5" y1="55.88" x2="317.5" y2="58.42" width="0.1524" layer="91"/>
<junction x="317.5" y="55.88"/>
<pinref part="DD3" gate="G$1" pin="CLKIN"/>
<wire x1="317.5" y1="58.42" x2="320.04" y2="58.42" width="0.1524" layer="91"/>
<wire x1="317.5" y1="58.42" x2="317.5" y2="60.96" width="0.1524" layer="91"/>
<junction x="317.5" y="58.42"/>
<pinref part="DD3" gate="G$1" pin="FSYNC"/>
<wire x1="317.5" y1="60.96" x2="320.04" y2="60.96" width="0.1524" layer="91"/>
<wire x1="317.5" y1="43.18" x2="312.42" y2="43.18" width="0.1524" layer="91"/>
<junction x="317.5" y="43.18"/>
<wire x1="312.42" y1="43.18" x2="312.42" y2="55.88" width="0.1524" layer="91"/>
<pinref part="C28" gate="G$1" pin="1"/>
<wire x1="312.42" y1="58.42" x2="312.42" y2="55.88" width="0.1524" layer="91"/>
<junction x="312.42" y="55.88"/>
<wire x1="312.42" y1="43.18" x2="294.64" y2="43.18" width="0.1524" layer="91"/>
<junction x="312.42" y="43.18"/>
<pinref part="C19" gate="G$1" pin="1"/>
<wire x1="294.64" y1="43.18" x2="294.64" y2="55.88" width="0.1524" layer="91"/>
<pinref part="C29" gate="G$1" pin="1"/>
<wire x1="264.16" y1="55.88" x2="264.16" y2="43.18" width="0.1524" layer="91"/>
<wire x1="264.16" y1="43.18" x2="274.32" y2="43.18" width="0.1524" layer="91"/>
<junction x="294.64" y="43.18"/>
<pinref part="C26" gate="G$1" pin="1"/>
<wire x1="274.32" y1="43.18" x2="284.48" y2="43.18" width="0.1524" layer="91"/>
<wire x1="284.48" y1="43.18" x2="294.64" y2="43.18" width="0.1524" layer="91"/>
<wire x1="274.32" y1="55.88" x2="274.32" y2="43.18" width="0.1524" layer="91"/>
<junction x="274.32" y="43.18"/>
<pinref part="C25" gate="G$1" pin="2"/>
<wire x1="284.48" y1="55.88" x2="284.48" y2="43.18" width="0.1524" layer="91"/>
<junction x="284.48" y="43.18"/>
</segment>
<segment>
<pinref part="GND18" gate="1" pin="GND"/>
<wire x1="320.04" y1="-81.28" x2="320.04" y2="-78.74" width="0.1524" layer="91"/>
<pinref part="DD5" gate="G$1" pin="GND@3"/>
<wire x1="320.04" y1="-78.74" x2="320.04" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="320.04" y1="-71.12" x2="327.66" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="320.04" y1="-71.12" x2="320.04" y2="-68.58" width="0.1524" layer="91"/>
<junction x="320.04" y="-71.12"/>
<pinref part="DD5" gate="G$1" pin="GND@2"/>
<wire x1="320.04" y1="-68.58" x2="327.66" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="320.04" y1="-68.58" x2="320.04" y2="-66.04" width="0.1524" layer="91"/>
<junction x="320.04" y="-68.58"/>
<pinref part="DD5" gate="G$1" pin="GND@1"/>
<wire x1="320.04" y1="-66.04" x2="327.66" y2="-66.04" width="0.1524" layer="91"/>
<wire x1="320.04" y1="-78.74" x2="309.88" y2="-78.74" width="0.1524" layer="91"/>
<junction x="320.04" y="-78.74"/>
<pinref part="C32" gate="G$1" pin="2"/>
<wire x1="309.88" y1="-78.74" x2="309.88" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="309.88" y1="-78.74" x2="299.72" y2="-78.74" width="0.1524" layer="91"/>
<junction x="309.88" y="-78.74"/>
<pinref part="C36" gate="G$1" pin="2"/>
<wire x1="299.72" y1="-78.74" x2="299.72" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="299.72" y1="-78.74" x2="289.56" y2="-78.74" width="0.1524" layer="91"/>
<junction x="299.72" y="-78.74"/>
<pinref part="C35" gate="G$1" pin="2"/>
<wire x1="289.56" y1="-78.74" x2="289.56" y2="-71.12" width="0.1524" layer="91"/>
<wire x1="289.56" y1="-78.74" x2="281.94" y2="-78.74" width="0.1524" layer="91"/>
<junction x="289.56" y="-78.74"/>
<pinref part="C33" gate="G$1" pin="-"/>
<wire x1="281.94" y1="-78.74" x2="281.94" y2="-71.12" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND20" gate="1" pin="GND"/>
<pinref part="DA6" gate="G$1" pin="GND"/>
<wire x1="287.02" y1="-223.52" x2="289.56" y2="-223.52" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND27" gate="1" pin="GND"/>
<pinref part="JP6" gate="G$1" pin="2"/>
<wire x1="210.82" y1="200.66" x2="205.74" y2="200.66" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="GND11" gate="1" pin="GND"/>
<wire x1="-190.5" y1="-91.44" x2="-187.96" y2="-91.44" width="0.1524" layer="91"/>
<pinref part="R6" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="GND29" gate="1" pin="GND"/>
<pinref part="C42" gate="G$1" pin="2"/>
<wire x1="-256.54" y1="-17.78" x2="-256.54" y2="-15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SDIO_DETECT" class="0">
<segment>
<wire x1="127" y1="-165.1" x2="116.84" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="116.84" y1="-165.1" x2="111.76" y2="-165.1" width="0.1524" layer="91"/>
<junction x="116.84" y="-165.1"/>
<label x="111.76" y="-165.1" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD4" gate="G$1" pin="DETECT"/>
<pinref part="R1" gate="G$1" pin="1"/>
</segment>
<segment>
<label x="48.26" y="-25.4" size="1.27" layer="95" xref="yes"/>
<wire x1="48.26" y1="-25.4" x2="40.64" y2="-25.4" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PE12"/>
</segment>
</net>
<net name="SDIO_D2" class="0">
<segment>
<wire x1="127" y1="-149.86" x2="111.76" y2="-149.86" width="0.1524" layer="91"/>
<label x="111.76" y="-149.86" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD4" gate="G$1" pin="SD_D2"/>
</segment>
<segment>
<wire x1="40.64" y1="-63.5" x2="48.26" y2="-63.5" width="0.1524" layer="91"/>
<label x="48.26" y="-63.5" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PC10"/>
</segment>
</net>
<net name="SDIO_D3" class="0">
<segment>
<wire x1="127" y1="-152.4" x2="111.76" y2="-152.4" width="0.1524" layer="91"/>
<label x="111.76" y="-152.4" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD4" gate="G$1" pin="SD_D3"/>
</segment>
<segment>
<wire x1="40.64" y1="-66.04" x2="48.26" y2="-66.04" width="0.1524" layer="91"/>
<label x="48.26" y="-66.04" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PC11"/>
</segment>
</net>
<net name="SDIO_CMD" class="0">
<segment>
<wire x1="127" y1="-154.94" x2="111.76" y2="-154.94" width="0.1524" layer="91"/>
<label x="111.76" y="-154.94" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD4" gate="G$1" pin="SD_CMD"/>
</segment>
<segment>
<wire x1="-33.02" y1="-43.18" x2="-38.1" y2="-43.18" width="0.1524" layer="91"/>
<label x="-38.1" y="-43.18" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PD2"/>
</segment>
</net>
<net name="SDIO_CK" class="0">
<segment>
<wire x1="127" y1="-157.48" x2="111.76" y2="-157.48" width="0.1524" layer="91"/>
<label x="111.76" y="-157.48" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD4" gate="G$1" pin="SD_CK"/>
</segment>
<segment>
<wire x1="40.64" y1="-68.58" x2="48.26" y2="-68.58" width="0.1524" layer="91"/>
<label x="48.26" y="-68.58" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PC12"/>
</segment>
</net>
<net name="SDIO_D0" class="0">
<segment>
<wire x1="127" y1="-160.02" x2="111.76" y2="-160.02" width="0.1524" layer="91"/>
<label x="111.76" y="-160.02" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD4" gate="G$1" pin="SD_D0"/>
</segment>
<segment>
<wire x1="40.64" y1="-58.42" x2="48.26" y2="-58.42" width="0.1524" layer="91"/>
<label x="48.26" y="-58.42" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PC8"/>
</segment>
</net>
<net name="SDIO_D1" class="0">
<segment>
<wire x1="127" y1="-162.56" x2="111.76" y2="-162.56" width="0.1524" layer="91"/>
<label x="111.76" y="-162.56" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD4" gate="G$1" pin="SD_D1"/>
</segment>
<segment>
<wire x1="40.64" y1="-60.96" x2="48.26" y2="-60.96" width="0.1524" layer="91"/>
<label x="48.26" y="-60.96" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PC9"/>
</segment>
</net>
<net name="BOOT_0" class="0">
<segment>
<wire x1="55.88" y1="177.8" x2="60.96" y2="177.8" width="0.1524" layer="91"/>
<label x="60.96" y="177.8" size="1.27" layer="95" xref="yes"/>
<pinref part="R3" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="-33.02" y1="-7.62" x2="-38.1" y2="-7.62" width="0.1524" layer="91"/>
<label x="-38.1" y="-7.62" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="BOOT_0"/>
</segment>
</net>
<net name="BOOT_1" class="0">
<segment>
<wire x1="50.8" y1="139.7" x2="60.96" y2="139.7" width="0.1524" layer="91"/>
<label x="60.96" y="139.7" size="1.27" layer="95" xref="yes"/>
<pinref part="R2" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="-33.02" y1="-10.16" x2="-38.1" y2="-10.16" width="0.1524" layer="91"/>
<label x="-38.1" y="-10.16" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="BOOT_1(PB2)"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="R4" gate="G$1" pin="2"/>
<pinref part="LED2" gate="G$1" pin="A"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<wire x1="40.64" y1="139.7" x2="33.02" y2="139.7" width="0.1524" layer="91"/>
<junction x="40.64" y="139.7"/>
<pinref part="R4" gate="G$1" pin="1"/>
<pinref part="JP5" gate="G$1" pin="2"/>
<pinref part="R2" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="R5" gate="G$1" pin="2"/>
<pinref part="LED1" gate="G$1" pin="A"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<wire x1="40.64" y1="-76.2" x2="43.18" y2="-76.2" width="0.1524" layer="91"/>
<wire x1="43.18" y1="-76.2" x2="43.18" y2="-81.28" width="0.1524" layer="91"/>
<wire x1="43.18" y1="-81.28" x2="43.18" y2="-86.36" width="0.1524" layer="91"/>
<wire x1="45.72" y1="-81.28" x2="43.18" y2="-81.28" width="0.1524" layer="91"/>
<junction x="43.18" y="-81.28"/>
<pinref part="C9" gate="G$1" pin="1"/>
<pinref part="ZQ2" gate="G$1" pin="P$2"/>
<pinref part="DD1" gate="G$1" pin="PC15(OSC32_OUT)"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<wire x1="40.64" y1="-73.66" x2="53.34" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="53.34" y1="-86.36" x2="53.34" y2="-81.28" width="0.1524" layer="91"/>
<wire x1="53.34" y1="-81.28" x2="53.34" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="50.8" y1="-81.28" x2="53.34" y2="-81.28" width="0.1524" layer="91"/>
<junction x="53.34" y="-81.28"/>
<pinref part="C10" gate="G$1" pin="1"/>
<pinref part="ZQ2" gate="G$1" pin="P$1"/>
<pinref part="DD1" gate="G$1" pin="PC14(OSC32_IN)"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="OSC_OUT"/>
<wire x1="-53.34" y1="0" x2="-43.18" y2="0" width="0.1524" layer="91"/>
<junction x="-43.18" y="0"/>
<pinref part="C12" gate="G$1" pin="2"/>
<pinref part="ZQ1" gate="G$1" pin="P$2"/>
<wire x1="-33.02" y1="0" x2="-43.18" y2="0" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<wire x1="-38.1" y1="2.54" x2="-38.1" y2="5.08" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="2.54" x2="-38.1" y2="2.54" width="0.1524" layer="91"/>
<wire x1="-38.1" y1="5.08" x2="-43.18" y2="5.08" width="0.1524" layer="91"/>
<wire x1="-43.18" y1="5.08" x2="-45.72" y2="5.08" width="0.1524" layer="91"/>
<junction x="-43.18" y="5.08"/>
<pinref part="ZQ1" gate="G$1" pin="P$1"/>
<pinref part="C11" gate="G$1" pin="2"/>
<pinref part="DD1" gate="G$1" pin="OSC_IN"/>
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
<wire x1="-33.02" y1="71.12" x2="-38.1" y2="71.12" width="0.1524" layer="91"/>
<label x="-38.1" y="71.12" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="NRST"/>
</segment>
<segment>
<wire x1="-132.08" y1="154.94" x2="-86.36" y2="154.94" width="0.1524" layer="91"/>
<label x="-86.36" y="154.94" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="15"/>
</segment>
</net>
<net name="+3.3V_A" class="2">
<segment>
<wire x1="345.44" y1="-109.22" x2="345.44" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="345.44" y1="-119.38" x2="342.9" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="347.98" y1="-119.38" x2="345.44" y2="-119.38" width="0.1524" layer="91"/>
<junction x="345.44" y="-119.38"/>
<label x="345.44" y="-109.22" size="1.27" layer="95" rot="R90" xref="yes"/>
<pinref part="IC2" gate="G$1" pin="V+"/>
<pinref part="C22" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="-33.02" y1="63.5" x2="-35.56" y2="63.5" width="0.1524" layer="91"/>
<label x="-38.1" y="63.5" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="VREF+"/>
<pinref part="DD1" gate="G$1" pin="VDD_A"/>
<wire x1="-35.56" y1="63.5" x2="-38.1" y2="63.5" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="60.96" x2="-35.56" y2="60.96" width="0.1524" layer="91"/>
<wire x1="-35.56" y1="60.96" x2="-35.56" y2="63.5" width="0.1524" layer="91"/>
<junction x="-35.56" y="63.5"/>
</segment>
<segment>
<wire x1="-233.68" y1="-55.88" x2="-213.36" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="-213.36" y1="-55.88" x2="-213.36" y2="-53.34" width="0.1524" layer="91"/>
<label x="-213.36" y="-53.34" size="1.27" layer="95" rot="R90" xref="yes"/>
<pinref part="DA4" gate="G$1" pin="OUT"/>
<pinref part="C41" gate="G$1" pin="1"/>
<wire x1="-213.36" y1="-58.42" x2="-213.36" y2="-55.88" width="0.1524" layer="91"/>
<junction x="-213.36" y="-55.88"/>
</segment>
<segment>
<wire x1="358.14" y1="-203.2" x2="358.14" y2="-210.82" width="0.1524" layer="91"/>
<wire x1="358.14" y1="-210.82" x2="358.14" y2="-226.06" width="0.1524" layer="91"/>
<junction x="358.14" y="-210.82"/>
<pinref part="C24" gate="G$1" pin="1"/>
<label x="358.14" y="-203.2" size="1.27" layer="95" rot="R90" xref="yes"/>
<pinref part="DA5" gate=":1" pin="+V"/>
<pinref part="DA6" gate="G$1" pin="A"/>
<wire x1="322.58" y1="-218.44" x2="325.12" y2="-218.44" width="0.1524" layer="91"/>
<wire x1="325.12" y1="-218.44" x2="325.12" y2="-210.82" width="0.1524" layer="91"/>
<wire x1="325.12" y1="-210.82" x2="358.14" y2="-210.82" width="0.1524" layer="91"/>
<junction x="358.14" y="-210.82"/>
<pinref part="DA6" gate="G$1" pin="!SHDN"/>
<wire x1="322.58" y1="-220.98" x2="325.12" y2="-220.98" width="0.1524" layer="91"/>
<wire x1="325.12" y1="-220.98" x2="325.12" y2="-218.44" width="0.1524" layer="91"/>
<junction x="325.12" y="-218.44"/>
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
<wire x1="40.64" y1="12.7" x2="48.26" y2="12.7" width="0.1524" layer="91"/>
<label x="48.26" y="12.7" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PA11"/>
</segment>
</net>
<net name="USB_DP" class="0">
<segment>
<wire x1="-139.7" y1="109.22" x2="-127" y2="109.22" width="0.1524" layer="91"/>
<label x="-127" y="109.22" size="1.27" layer="95" xref="yes"/>
<pinref part="R13" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="40.64" y1="10.16" x2="48.26" y2="10.16" width="0.1524" layer="91"/>
<label x="48.26" y="10.16" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PA12"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<wire x1="33.02" y1="177.8" x2="40.64" y2="177.8" width="0.1524" layer="91"/>
<wire x1="40.64" y1="177.8" x2="45.72" y2="177.8" width="0.1524" layer="91"/>
<junction x="40.64" y="177.8"/>
<pinref part="JP4" gate="G$1" pin="2"/>
<pinref part="R5" gate="G$1" pin="1"/>
<pinref part="R3" gate="G$1" pin="1"/>
</segment>
</net>
<net name="5V_USB" class="0">
<segment>
<label x="-149.86" y="104.14" size="1.27" layer="95" xref="yes"/>
<wire x1="-149.86" y1="104.14" x2="-154.94" y2="104.14" width="0.1524" layer="91"/>
<pinref part="X1" gate="G$1" pin="VBUS"/>
</segment>
<segment>
<wire x1="-281.94" y1="5.08" x2="-287.02" y2="5.08" width="0.1524" layer="91"/>
<label x="-287.02" y="5.08" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="D2" gate="G$1" pin="A"/>
</segment>
</net>
<net name="TRST" class="0">
<segment>
<wire x1="-132.08" y1="170.18" x2="-124.46" y2="170.18" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="170.18" x2="-86.36" y2="170.18" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="175.26" x2="-124.46" y2="170.18" width="0.1524" layer="91"/>
<junction x="-124.46" y="170.18"/>
<label x="-86.36" y="170.18" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="3"/>
<pinref part="R17" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="-33.02" y1="-25.4" x2="-38.1" y2="-25.4" width="0.1524" layer="91"/>
<label x="-38.1" y="-25.4" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="NJTRST(PB4)"/>
</segment>
</net>
<net name="TDI" class="0">
<segment>
<wire x1="-132.08" y1="167.64" x2="-116.84" y2="167.64" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="167.64" x2="-86.36" y2="167.64" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="175.26" x2="-116.84" y2="167.64" width="0.1524" layer="91"/>
<junction x="-116.84" y="167.64"/>
<label x="-86.36" y="167.64" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="5"/>
<pinref part="R18" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="-33.02" y1="-22.86" x2="-38.1" y2="-22.86" width="0.1524" layer="91"/>
<label x="-38.1" y="-22.86" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="JTDI(PA15)"/>
</segment>
</net>
<net name="TMS" class="0">
<segment>
<wire x1="-33.02" y1="-17.78" x2="-38.1" y2="-17.78" width="0.1524" layer="91"/>
<label x="-38.1" y="-17.78" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="JTMS(PA13)"/>
</segment>
<segment>
<label x="-86.36" y="165.1" size="1.27" layer="95" xref="yes"/>
<wire x1="-86.36" y1="165.1" x2="-109.22" y2="165.1" width="0.1524" layer="91"/>
<wire x1="-109.22" y1="165.1" x2="-132.08" y2="165.1" width="0.1524" layer="91"/>
<wire x1="-109.22" y1="175.26" x2="-109.22" y2="165.1" width="0.1524" layer="91"/>
<junction x="-109.22" y="165.1"/>
<pinref part="XP1" gate="G$1" pin="7"/>
<pinref part="R19" gate="G$1" pin="1"/>
</segment>
</net>
<net name="TCK" class="0">
<segment>
<wire x1="-132.08" y1="162.56" x2="-101.6" y2="162.56" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="162.56" x2="-86.36" y2="162.56" width="0.1524" layer="91"/>
<wire x1="-101.6" y1="175.26" x2="-101.6" y2="162.56" width="0.1524" layer="91"/>
<junction x="-101.6" y="162.56"/>
<label x="-86.36" y="162.56" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="9"/>
<pinref part="R20" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="-33.02" y1="-20.32" x2="-38.1" y2="-20.32" width="0.1524" layer="91"/>
<label x="-38.1" y="-20.32" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="JTCK(PA14)"/>
</segment>
</net>
<net name="TDO" class="0">
<segment>
<wire x1="-33.02" y1="-27.94" x2="-38.1" y2="-27.94" width="0.1524" layer="91"/>
<label x="-38.1" y="-27.94" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="JTDO(PB3)"/>
</segment>
<segment>
<wire x1="-93.98" y1="157.48" x2="-132.08" y2="157.48" width="0.1524" layer="91"/>
<wire x1="-93.98" y1="175.26" x2="-93.98" y2="157.48" width="0.1524" layer="91"/>
<wire x1="-86.36" y1="157.48" x2="-93.98" y2="157.48" width="0.1524" layer="91"/>
<junction x="-93.98" y="157.48"/>
<label x="-86.36" y="157.48" size="1.27" layer="95" xref="yes"/>
<pinref part="XP1" gate="G$1" pin="13"/>
<pinref part="R21" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<wire x1="-132.08" y1="149.86" x2="-124.46" y2="149.86" width="0.1524" layer="91"/>
<wire x1="-124.46" y1="149.86" x2="-124.46" y2="147.32" width="0.1524" layer="91"/>
<pinref part="XP1" gate="G$1" pin="19"/>
<pinref part="R22" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<wire x1="-132.08" y1="152.4" x2="-116.84" y2="152.4" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="152.4" x2="-116.84" y2="147.32" width="0.1524" layer="91"/>
<pinref part="XP1" gate="G$1" pin="17"/>
<pinref part="R23" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<wire x1="-132.08" y1="160.02" x2="-109.22" y2="160.02" width="0.1524" layer="91"/>
<wire x1="-109.22" y1="160.02" x2="-109.22" y2="147.32" width="0.1524" layer="91"/>
<pinref part="XP1" gate="G$1" pin="11"/>
<pinref part="R24" gate="G$1" pin="2"/>
</segment>
</net>
<net name="FROM_XBEE" class="0">
<segment>
<wire x1="205.74" y1="142.24" x2="213.36" y2="142.24" width="0.1524" layer="91"/>
<label x="213.36" y="142.24" size="1.27" layer="95" xref="yes"/>
<pinref part="JP1" gate="G$1" pin="2"/>
</segment>
<segment>
<label x="-38.1" y="-60.96" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PD9"/>
<wire x1="-33.02" y1="-60.96" x2="-38.1" y2="-60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="TO_XBEE" class="0">
<segment>
<wire x1="190.5" y1="139.7" x2="182.88" y2="139.7" width="0.1524" layer="91"/>
<label x="182.88" y="139.7" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP1" gate="G$1" pin="3"/>
</segment>
<segment>
<label x="-38.1" y="-58.42" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PD8"/>
<wire x1="-33.02" y1="-58.42" x2="-38.1" y2="-58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="XBEE_RESET" class="0">
<segment>
<wire x1="190.5" y1="137.16" x2="182.88" y2="137.16" width="0.1524" layer="91"/>
<label x="182.88" y="137.16" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP1" gate="G$1" pin="5"/>
</segment>
<segment>
<label x="-38.1" y="-55.88" size="1.27" layer="95" rot="R180" xref="yes"/>
<wire x1="-38.1" y1="-55.88" x2="-33.02" y2="-55.88" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PD7"/>
</segment>
</net>
<net name="XBEE_CTS" class="0">
<segment>
<wire x1="205.74" y1="139.7" x2="213.36" y2="139.7" width="0.1524" layer="91"/>
<label x="213.36" y="139.7" size="1.27" layer="95" xref="yes"/>
<pinref part="JP1" gate="G$1" pin="4"/>
</segment>
<segment>
<label x="-38.1" y="-66.04" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PD11"/>
<wire x1="-33.02" y1="-66.04" x2="-38.1" y2="-66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="XBEE_RTS" class="0">
<segment>
<wire x1="205.74" y1="137.16" x2="213.36" y2="137.16" width="0.1524" layer="91"/>
<label x="213.36" y="137.16" size="1.27" layer="95" xref="yes"/>
<pinref part="JP1" gate="G$1" pin="6"/>
</segment>
<segment>
<pinref part="R37" gate="G$1" pin="1"/>
<wire x1="81.28" y1="45.72" x2="83.82" y2="45.72" width="0.1524" layer="91"/>
<label x="83.82" y="45.72" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="TO_GPS" class="0">
<segment>
<wire x1="190.5" y1="170.18" x2="182.88" y2="170.18" width="0.1524" layer="91"/>
<label x="182.88" y="170.18" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP2" gate="G$1" pin="3"/>
</segment>
<segment>
<wire x1="40.64" y1="17.78" x2="48.26" y2="17.78" width="0.1524" layer="91"/>
<label x="48.26" y="17.78" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PA9"/>
</segment>
</net>
<net name="FROM_GPS" class="0">
<segment>
<wire x1="205.74" y1="172.72" x2="213.36" y2="172.72" width="0.1524" layer="91"/>
<label x="213.36" y="172.72" size="1.27" layer="95" xref="yes"/>
<pinref part="JP2" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="40.64" y1="15.24" x2="48.26" y2="15.24" width="0.1524" layer="91"/>
<label x="48.26" y="15.24" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PA10"/>
</segment>
</net>
<net name="GPS_PPS" class="0">
<segment>
<wire x1="40.64" y1="5.08" x2="48.26" y2="5.08" width="0.1524" layer="91"/>
<label x="48.26" y="5.08" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PE0"/>
</segment>
<segment>
<wire x1="205.74" y1="170.18" x2="213.36" y2="170.18" width="0.1524" layer="91"/>
<label x="213.36" y="170.18" size="1.27" layer="95" xref="yes"/>
<pinref part="JP2" gate="G$1" pin="4"/>
</segment>
</net>
<net name="GPS_ENABLE" class="0">
<segment>
<wire x1="190.5" y1="165.1" x2="182.88" y2="165.1" width="0.1524" layer="91"/>
<label x="182.88" y="165.1" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP2" gate="G$1" pin="7"/>
</segment>
<segment>
<label x="48.26" y="40.64" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PA0"/>
<wire x1="48.26" y1="40.64" x2="40.64" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="I2C_FAST_SCL" class="0">
<segment>
<wire x1="66.04" y1="71.12" x2="66.04" y2="68.58" width="0.1524" layer="91"/>
<wire x1="66.04" y1="68.58" x2="81.28" y2="68.58" width="0.1524" layer="91"/>
<label x="81.28" y="68.58" size="1.27" layer="95" xref="yes"/>
<pinref part="R28" gate="G$1" pin="1"/>
<pinref part="DD1" gate="G$1" pin="PB6"/>
<wire x1="66.04" y1="68.58" x2="40.64" y2="68.58" width="0.1524" layer="91"/>
<junction x="66.04" y="68.58"/>
</segment>
<segment>
<wire x1="355.6" y1="76.2" x2="363.22" y2="76.2" width="0.1524" layer="91"/>
<label x="363.22" y="76.2" size="1.27" layer="95" xref="yes"/>
<pinref part="DD3" gate="G$1" pin="SCL"/>
</segment>
<segment>
<pinref part="DD5" gate="G$1" pin="SCL"/>
<wire x1="360.68" y1="-53.34" x2="368.3" y2="-53.34" width="0.1524" layer="91"/>
<label x="368.3" y="-53.34" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="TMP75_ALERT" class="0">
<segment>
<wire x1="297.18" y1="-15.24" x2="294.64" y2="-15.24" width="0.1524" layer="91"/>
<label x="294.64" y="-15.24" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="U2" gate="G$1" pin="ALERT"/>
</segment>
<segment>
<label x="48.26" y="-10.16" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PE6"/>
<wire x1="48.26" y1="-10.16" x2="40.64" y2="-10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PRESS_DIFF" class="0">
<segment>
<wire x1="355.6" y1="-215.9" x2="365.76" y2="-215.9" width="0.1524" layer="91"/>
<wire x1="365.76" y1="-215.9" x2="365.76" y2="-233.68" width="0.1524" layer="91"/>
<wire x1="365.76" y1="-233.68" x2="375.92" y2="-233.68" width="0.1524" layer="91"/>
<label x="375.92" y="-233.68" size="1.27" layer="95" xref="yes"/>
<pinref part="R33" gate="G$1" pin="2"/>
<pinref part="DA5" gate=":1" pin="OUT"/>
<junction x="365.76" y="-233.68"/>
</segment>
<segment>
<label x="48.26" y="-38.1" size="1.27" layer="95" xref="yes"/>
<wire x1="48.26" y1="-38.1" x2="40.64" y2="-38.1" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PC0"/>
</segment>
</net>
<net name="BMP085_EOC" class="0">
<segment>
<label x="48.26" y="-5.08" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PE4"/>
<wire x1="48.26" y1="-5.08" x2="40.64" y2="-5.08" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="340.36" y1="15.24" x2="345.44" y2="15.24" width="0.1524" layer="91"/>
<label x="345.44" y="15.24" size="1.27" layer="95" xref="yes"/>
<pinref part="R75" gate="G$1" pin="1"/>
</segment>
</net>
<net name="MAG_INT" class="0">
<segment>
<label x="48.26" y="-7.62" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PE5"/>
<wire x1="48.26" y1="-7.62" x2="40.64" y2="-7.62" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="DD5" gate="G$1" pin="DRDY"/>
<wire x1="360.68" y1="-58.42" x2="368.3" y2="-58.42" width="0.1524" layer="91"/>
<label x="368.3" y="-58.42" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="MPU9150_INT" class="0">
<segment>
<label x="48.26" y="-2.54" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PE3"/>
<wire x1="48.26" y1="-2.54" x2="40.64" y2="-2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="370.84" y1="68.58" x2="368.3" y2="68.58" width="0.1524" layer="91"/>
<label x="370.84" y="68.58" size="1.27" layer="95" xref="yes"/>
<pinref part="R14" gate="G$1" pin="2"/>
</segment>
</net>
<net name="PWM1" class="0">
<segment>
<wire x1="-101.6" y1="-162.56" x2="-101.6" y2="-170.18" width="0.1524" layer="91"/>
<pinref part="XP8" gate="G$1" pin="1"/>
<pinref part="R38" gate="G$1" pin="2"/>
</segment>
</net>
<net name="PWM2" class="0">
<segment>
<wire x1="-88.9" y1="-162.56" x2="-88.9" y2="-170.18" width="0.1524" layer="91"/>
<pinref part="XP9" gate="G$1" pin="1"/>
<pinref part="R39" gate="G$1" pin="2"/>
</segment>
</net>
<net name="PWM3" class="0">
<segment>
<wire x1="-76.2" y1="-162.56" x2="-76.2" y2="-170.18" width="0.1524" layer="91"/>
<pinref part="XP10" gate="G$1" pin="1"/>
<pinref part="R40" gate="G$1" pin="2"/>
</segment>
</net>
<net name="PWM4" class="0">
<segment>
<wire x1="-63.5" y1="-162.56" x2="-63.5" y2="-170.18" width="0.1524" layer="91"/>
<pinref part="XP11" gate="G$1" pin="1"/>
<pinref part="R41" gate="G$1" pin="2"/>
</segment>
</net>
<net name="RECEIVER_PPM" class="0">
<segment>
<wire x1="129.54" y1="142.24" x2="127" y2="142.24" width="0.1524" layer="91"/>
<wire x1="129.54" y1="142.24" x2="137.16" y2="142.24" width="0.1524" layer="91"/>
<junction x="129.54" y="142.24"/>
<label x="137.16" y="142.24" size="1.27" layer="95" xref="yes"/>
<pinref part="R29" gate="G$1" pin="2"/>
<pinref part="VD8" gate="G$1" pin="C"/>
</segment>
<segment>
<label x="48.26" y="60.96" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PB9"/>
<wire x1="48.26" y1="60.96" x2="40.64" y2="60.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="PWM8" class="0">
<segment>
<wire x1="-12.7" y1="-162.56" x2="-12.7" y2="-170.18" width="0.1524" layer="91"/>
<pinref part="XP15" gate="G$1" pin="1"/>
<pinref part="R46" gate="G$1" pin="2"/>
</segment>
</net>
<net name="PWM7" class="0">
<segment>
<wire x1="-25.4" y1="-162.56" x2="-25.4" y2="-170.18" width="0.1524" layer="91"/>
<pinref part="XP14" gate="G$1" pin="1"/>
<pinref part="R44" gate="G$1" pin="2"/>
</segment>
</net>
<net name="PWM6" class="0">
<segment>
<wire x1="-38.1" y1="-162.56" x2="-38.1" y2="-170.18" width="0.1524" layer="91"/>
<pinref part="XP13" gate="G$1" pin="1"/>
<pinref part="R43" gate="G$1" pin="2"/>
</segment>
</net>
<net name="PWM5" class="0">
<segment>
<wire x1="-50.8" y1="-162.56" x2="-50.8" y2="-170.18" width="0.1524" layer="91"/>
<pinref part="XP12" gate="G$1" pin="1"/>
<pinref part="R42" gate="G$1" pin="2"/>
</segment>
</net>
<net name="I2C_FAST_SDA" class="0">
<segment>
<wire x1="76.2" y1="73.66" x2="76.2" y2="66.04" width="0.1524" layer="91"/>
<wire x1="76.2" y1="66.04" x2="81.28" y2="66.04" width="0.1524" layer="91"/>
<label x="81.28" y="66.04" size="1.27" layer="95" xref="yes"/>
<pinref part="R27" gate="G$1" pin="1"/>
<pinref part="DD1" gate="G$1" pin="PB7"/>
<wire x1="76.2" y1="66.04" x2="40.64" y2="66.04" width="0.1524" layer="91"/>
<junction x="76.2" y="66.04"/>
</segment>
<segment>
<wire x1="355.6" y1="78.74" x2="363.22" y2="78.74" width="0.1524" layer="91"/>
<label x="363.22" y="78.74" size="1.27" layer="95" xref="yes"/>
<pinref part="DD3" gate="G$1" pin="SDA"/>
</segment>
<segment>
<pinref part="DD5" gate="G$1" pin="SDA"/>
<wire x1="360.68" y1="-50.8" x2="368.3" y2="-50.8" width="0.1524" layer="91"/>
<label x="368.3" y="-50.8" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<wire x1="40.64" y1="-71.12" x2="63.5" y2="-71.12" width="0.1524" layer="91"/>
<pinref part="R32" gate="G$1" pin="1"/>
<pinref part="DD1" gate="G$1" pin="PC13(TAMPER-RTC)"/>
</segment>
</net>
<net name="MAIN_SUPPLY" class="0">
<segment>
<wire x1="124.46" y1="-45.72" x2="127" y2="-45.72" width="0.1524" layer="91"/>
<label x="127" y="-45.72" size="1.27" layer="95" xref="yes"/>
<pinref part="R54" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="297.18" y1="-129.54" x2="292.1" y2="-129.54" width="0.1524" layer="91"/>
<wire x1="292.1" y1="-129.54" x2="292.1" y2="-124.46" width="0.1524" layer="91"/>
<junction x="292.1" y="-129.54"/>
<label x="292.1" y="-129.54" size="1.27" layer="95" rot="R270" xref="yes"/>
<pinref part="R51" gate="G$1" pin="1"/>
<pinref part="XP18" gate="G$1" pin="2"/>
</segment>
</net>
<net name="6V" class="0">
<segment>
<wire x1="124.46" y1="-48.26" x2="127" y2="-48.26" width="0.1524" layer="91"/>
<pinref part="R55" gate="G$1" pin="2"/>
<pinref part="U$13" gate="6V" pin="6V"/>
</segment>
<segment>
<wire x1="114.3" y1="152.4" x2="114.3" y2="139.7" width="0.1524" layer="91"/>
<wire x1="114.3" y1="139.7" x2="111.76" y2="139.7" width="0.1524" layer="91"/>
<pinref part="U$1" gate="6V" pin="6V"/>
<pinref part="XP2" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="-246.38" y1="-2.54" x2="-256.54" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="-256.54" y1="-2.54" x2="-269.24" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="-276.86" y1="5.08" x2="-269.24" y2="5.08" width="0.1524" layer="91"/>
<wire x1="-269.24" y1="5.08" x2="-269.24" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="-289.56" y1="-2.54" x2="-297.18" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="-289.56" y1="-7.62" x2="-289.56" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="-269.24" y1="-2.54" x2="-289.56" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="-269.24" y1="12.7" x2="-269.24" y2="5.08" width="0.1524" layer="91"/>
<wire x1="-269.24" y1="-7.62" x2="-269.24" y2="-2.54" width="0.1524" layer="91"/>
<junction x="-269.24" y="-2.54"/>
<junction x="-289.56" y="-2.54"/>
<junction x="-269.24" y="5.08"/>
<pinref part="D2" gate="G$1" pin="C"/>
<pinref part="F3" gate="G$1" pin="2"/>
<pinref part="D3" gate="G$1" pin="C"/>
<pinref part="U$5" gate="6V" pin="6V"/>
<pinref part="C31" gate="G$1" pin="+"/>
<pinref part="DA1" gate="G$1" pin="IN"/>
<pinref part="C42" gate="G$1" pin="1"/>
<wire x1="-256.54" y1="-7.62" x2="-256.54" y2="-2.54" width="0.1524" layer="91"/>
<junction x="-256.54" y="-2.54"/>
</segment>
<segment>
<pinref part="U$3" gate="6V" pin="6V"/>
<pinref part="L1" gate="G$1" pin="1"/>
<wire x1="-312.42" y1="-55.88" x2="-309.88" y2="-55.88" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<wire x1="317.5" y1="-243.84" x2="320.04" y2="-243.84" width="0.1524" layer="91"/>
<pinref part="R48" gate="G$1" pin="2"/>
<pinref part="DA3" gate="G$1" pin="OUT"/>
</segment>
</net>
<net name="N$46" class="0">
<segment>
<wire x1="345.44" y1="-215.9" x2="345.44" y2="-231.14" width="0.1524" layer="91"/>
<junction x="345.44" y="-215.9"/>
<pinref part="R33" gate="G$1" pin="1"/>
<pinref part="R45" gate="G$1" pin="2"/>
<pinref part="DA5" gate=":1" pin="-IN"/>
<wire x1="345.44" y1="-231.14" x2="350.52" y2="-231.14" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$47" class="0">
<segment>
<wire x1="330.2" y1="-243.84" x2="332.74" y2="-243.84" width="0.1524" layer="91"/>
<wire x1="332.74" y1="-243.84" x2="345.44" y2="-243.84" width="0.1524" layer="91"/>
<wire x1="345.44" y1="-243.84" x2="345.44" y2="-246.38" width="0.1524" layer="91"/>
<pinref part="R48" gate="G$1" pin="1"/>
<pinref part="R47" gate="G$1" pin="2"/>
<wire x1="332.74" y1="-248.92" x2="332.74" y2="-243.84" width="0.1524" layer="91"/>
<junction x="332.74" y="-243.84"/>
<pinref part="DA5" gate=":1" pin="+IN"/>
<junction x="345.44" y="-243.84"/>
<wire x1="345.44" y1="-243.84" x2="345.44" y2="-236.22" width="0.1524" layer="91"/>
<wire x1="345.44" y1="-236.22" x2="350.52" y2="-236.22" width="0.1524" layer="91"/>
<pinref part="C43" gate="G$1" pin="1"/>
</segment>
</net>
<net name="TACHOMETER" class="0">
<segment>
<wire x1="-152.4" y1="-160.02" x2="-149.86" y2="-160.02" width="0.1524" layer="91"/>
<label x="-149.86" y="-160.02" size="1.27" layer="95" xref="yes"/>
<pinref part="XP16" gate="G$1" pin="1"/>
</segment>
<segment>
<label x="48.26" y="63.5" size="1.27" layer="95" xref="yes"/>
<wire x1="40.64" y1="63.5" x2="48.26" y2="63.5" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PB8"/>
</segment>
</net>
<net name="N$52" class="0">
<segment>
<wire x1="114.3" y1="-45.72" x2="111.76" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="111.76" y1="-53.34" x2="111.76" y2="-45.72" width="0.1524" layer="91"/>
<junction x="111.76" y="-45.72"/>
<pinref part="R54" gate="G$1" pin="1"/>
<pinref part="R56" gate="G$1" pin="2"/>
<pinref part="VD2" gate="G$1" pin="C"/>
<wire x1="101.6" y1="-45.72" x2="106.68" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="106.68" y1="-45.72" x2="111.76" y2="-45.72" width="0.1524" layer="91"/>
<wire x1="101.6" y1="-55.88" x2="101.6" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="C37" gate="G$1" pin="2"/>
<wire x1="106.68" y1="-53.34" x2="106.68" y2="-45.72" width="0.1524" layer="91"/>
<junction x="106.68" y="-45.72"/>
<pinref part="DD1" gate="G$1" pin="PC3"/>
<wire x1="101.6" y1="-45.72" x2="40.64" y2="-45.72" width="0.1524" layer="91"/>
<junction x="101.6" y="-45.72"/>
</segment>
</net>
<net name="N$54" class="0">
<segment>
<wire x1="91.44" y1="-53.34" x2="91.44" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="114.3" y1="-48.26" x2="91.44" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="91.44" y1="-48.26" x2="86.36" y2="-48.26" width="0.1524" layer="91"/>
<junction x="91.44" y="-48.26"/>
<pinref part="R57" gate="G$1" pin="2"/>
<pinref part="R55" gate="G$1" pin="1"/>
<pinref part="VD3" gate="G$1" pin="C"/>
<wire x1="86.36" y1="-48.26" x2="81.28" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="81.28" y1="-48.26" x2="40.64" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="81.28" y1="-55.88" x2="81.28" y2="-48.26" width="0.1524" layer="91"/>
<junction x="81.28" y="-48.26"/>
<pinref part="C39" gate="G$1" pin="2"/>
<wire x1="86.36" y1="-53.34" x2="86.36" y2="-48.26" width="0.1524" layer="91"/>
<junction x="86.36" y="-48.26"/>
<pinref part="DD1" gate="G$1" pin="PC4"/>
</segment>
</net>
<net name="ADIS_NSS" class="0">
<segment>
<label x="274.32" y="152.4" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD2" gate="G$1" pin="!CS"/>
<wire x1="274.32" y1="152.4" x2="284.48" y2="152.4" width="0.1524" layer="91"/>
</segment>
<segment>
<label x="48.26" y="30.48" size="1.27" layer="95" xref="yes"/>
<wire x1="48.26" y1="30.48" x2="40.64" y2="30.48" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PA4"/>
</segment>
</net>
<net name="ADIS_SCK" class="0">
<segment>
<wire x1="284.48" y1="160.02" x2="274.32" y2="160.02" width="0.1524" layer="91"/>
<label x="274.32" y="160.02" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD2" gate="G$1" pin="SCLK"/>
</segment>
<segment>
<wire x1="40.64" y1="27.94" x2="48.26" y2="27.94" width="0.1524" layer="91"/>
<label x="48.26" y="27.94" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PA5"/>
</segment>
</net>
<net name="ADIS_MISO" class="0">
<segment>
<wire x1="284.48" y1="154.94" x2="274.32" y2="154.94" width="0.1524" layer="91"/>
<label x="274.32" y="154.94" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD2" gate="G$1" pin="DOUT"/>
</segment>
<segment>
<label x="48.26" y="25.4" size="1.27" layer="95" xref="yes"/>
<wire x1="48.26" y1="25.4" x2="40.64" y2="25.4" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PA6"/>
</segment>
</net>
<net name="ADIS_MOSI" class="0">
<segment>
<wire x1="284.48" y1="157.48" x2="274.32" y2="157.48" width="0.1524" layer="91"/>
<label x="274.32" y="157.48" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD2" gate="G$1" pin="DIN"/>
</segment>
<segment>
<wire x1="40.64" y1="22.86" x2="48.26" y2="22.86" width="0.1524" layer="91"/>
<label x="48.26" y="22.86" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PA7"/>
</segment>
</net>
<net name="N$53" class="0">
<segment>
<wire x1="-281.94" y1="-91.44" x2="-271.78" y2="-91.44" width="0.1524" layer="91"/>
<junction x="-281.94" y="-91.44"/>
<pinref part="Q1" gate="G$1" pin="G"/>
<pinref part="R58" gate="G$1" pin="2"/>
<pinref part="C54" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$55" class="0">
<segment>
<wire x1="-243.84" y1="-99.06" x2="-248.92" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="-248.92" y1="-99.06" x2="-266.7" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="-266.7" y1="-99.06" x2="-281.94" y2="-99.06" width="0.1524" layer="91"/>
<junction x="-266.7" y="-99.06"/>
<pinref part="IC3" gate="G$1" pin="I"/>
<pinref part="Q1" gate="G$1" pin="D"/>
<pinref part="C54" gate="G$1" pin="2"/>
<pinref part="C51" gate="G$1" pin="+"/>
<wire x1="-266.7" y1="-104.14" x2="-266.7" y2="-99.06" width="0.1524" layer="91"/>
<pinref part="C55" gate="G$1" pin="1"/>
<wire x1="-248.92" y1="-104.14" x2="-248.92" y2="-99.06" width="0.1524" layer="91"/>
<junction x="-248.92" y="-99.06"/>
</segment>
</net>
<net name="5V_ENABLE" class="0">
<segment>
<label x="48.26" y="20.32" size="1.27" layer="95" xref="yes"/>
<wire x1="40.64" y1="20.32" x2="48.26" y2="20.32" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PA8"/>
</segment>
<segment>
<wire x1="-317.5" y1="-96.52" x2="-320.04" y2="-96.52" width="0.1524" layer="91"/>
<label x="-320.04" y="-96.52" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="R61" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$56" class="0">
<segment>
<wire x1="187.96" y1="99.06" x2="180.34" y2="99.06" width="0.1524" layer="91"/>
<pinref part="U$7" gate="G$1" pin="BLU"/>
<pinref part="R31" gate="G$1" pin="1"/>
</segment>
</net>
<net name="LED_G" class="0">
<segment>
<wire x1="160.02" y1="96.52" x2="157.48" y2="96.52" width="0.1524" layer="91"/>
<label x="157.48" y="96.52" size="1.27" layer="95" rot="MR0" xref="yes"/>
<pinref part="R60" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PB1"/>
<wire x1="48.26" y1="73.66" x2="40.64" y2="73.66" width="0.1524" layer="91"/>
<label x="48.26" y="73.66" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="LED_B" class="0">
<segment>
<wire x1="170.18" y1="99.06" x2="157.48" y2="99.06" width="0.1524" layer="91"/>
<label x="157.48" y="99.06" size="1.27" layer="95" rot="MR0" xref="yes"/>
<pinref part="R31" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PB5"/>
<wire x1="48.26" y1="71.12" x2="40.64" y2="71.12" width="0.1524" layer="91"/>
<label x="48.26" y="71.12" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="LED_R" class="0">
<segment>
<wire x1="160.02" y1="101.6" x2="157.48" y2="101.6" width="0.1524" layer="91"/>
<label x="157.48" y="101.6" size="1.27" layer="95" rot="MR0" xref="yes"/>
<pinref part="R30" gate="G$1" pin="2"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PB0"/>
<wire x1="48.26" y1="76.2" x2="40.64" y2="76.2" width="0.1524" layer="91"/>
<label x="48.26" y="76.2" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$59" class="0">
<segment>
<wire x1="-307.34" y1="-96.52" x2="-304.8" y2="-96.52" width="0.1524" layer="91"/>
<pinref part="R61" gate="G$1" pin="1"/>
<pinref part="T3" gate="G$1" pin="B"/>
</segment>
</net>
<net name="V_IN" class="0">
<segment>
<label x="-332.74" y="-2.54" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="D1" gate="G$1" pin="A"/>
<wire x1="-322.58" y1="-2.54" x2="-332.74" y2="-2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="-99.06" y1="-165.1" x2="-86.36" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-86.36" y1="-165.1" x2="-73.66" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="-165.1" x2="-60.96" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-60.96" y1="-165.1" x2="-48.26" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="-165.1" x2="-35.56" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-35.56" y1="-165.1" x2="-22.86" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-99.06" y1="-165.1" x2="-99.06" y2="-162.56" width="0.1524" layer="91"/>
<wire x1="-86.36" y1="-162.56" x2="-86.36" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-73.66" y1="-162.56" x2="-73.66" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-60.96" y1="-162.56" x2="-60.96" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-48.26" y1="-162.56" x2="-48.26" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-35.56" y1="-162.56" x2="-35.56" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-22.86" y1="-162.56" x2="-22.86" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="-162.56" x2="-10.16" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-22.86" y1="-165.1" x2="-10.16" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="-99.06" y1="-165.1" x2="-106.68" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="2.54" y1="-162.56" x2="2.54" y2="-165.1" width="0.1524" layer="91"/>
<wire x1="2.54" y1="-165.1" x2="-10.16" y2="-165.1" width="0.1524" layer="91"/>
<junction x="-86.36" y="-165.1"/>
<junction x="-73.66" y="-165.1"/>
<junction x="-60.96" y="-165.1"/>
<junction x="-48.26" y="-165.1"/>
<junction x="-35.56" y="-165.1"/>
<junction x="-22.86" y="-165.1"/>
<junction x="-99.06" y="-165.1"/>
<junction x="-10.16" y="-165.1"/>
<label x="-106.68" y="-165.1" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="XP8" gate="G$1" pin="2"/>
<pinref part="XP9" gate="G$1" pin="2"/>
<pinref part="XP10" gate="G$1" pin="2"/>
<pinref part="XP11" gate="G$1" pin="2"/>
<pinref part="XP12" gate="G$1" pin="2"/>
<pinref part="XP13" gate="G$1" pin="2"/>
<pinref part="XP14" gate="G$1" pin="2"/>
<pinref part="XP15" gate="G$1" pin="2"/>
<pinref part="XP17" gate="G$1" pin="2"/>
</segment>
</net>
<net name="SONAR_PWM" class="0">
<segment>
<wire x1="-152.4" y1="-170.18" x2="-147.32" y2="-170.18" width="0.1524" layer="91"/>
<label x="-147.32" y="-170.18" size="1.27" layer="95" xref="yes"/>
<pinref part="XP6" gate="G$1" pin="1"/>
</segment>
<segment>
<label x="48.26" y="35.56" size="1.27" layer="95" xref="yes"/>
<wire x1="48.26" y1="35.56" x2="40.64" y2="35.56" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PA2"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<wire x1="320.04" y1="-119.38" x2="309.88" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="309.88" y1="-119.38" x2="307.34" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="309.88" y1="-121.92" x2="309.88" y2="-119.38" width="0.1524" layer="91"/>
<junction x="309.88" y="-119.38"/>
<pinref part="IC2" gate="G$1" pin="IN-"/>
<pinref part="R36" gate="G$1" pin="2"/>
<pinref part="C45" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$37" class="0">
<segment>
<wire x1="320.04" y1="-129.54" x2="309.88" y2="-129.54" width="0.1524" layer="91"/>
<wire x1="309.88" y1="-129.54" x2="307.34" y2="-129.54" width="0.1524" layer="91"/>
<junction x="309.88" y="-129.54"/>
<pinref part="IC2" gate="G$1" pin="IN+"/>
<pinref part="C45" gate="G$1" pin="2"/>
<pinref part="R51" gate="G$1" pin="2"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<wire x1="297.18" y1="-119.38" x2="292.1" y2="-119.38" width="0.1524" layer="91"/>
<wire x1="292.1" y1="-119.38" x2="292.1" y2="-121.92" width="0.1524" layer="91"/>
<pinref part="R36" gate="G$1" pin="1"/>
<pinref part="XP18" gate="G$1" pin="1"/>
</segment>
</net>
<net name="CURRENT_SENS" class="0">
<segment>
<wire x1="342.9" y1="-124.46" x2="358.14" y2="-124.46" width="0.1524" layer="91"/>
<label x="358.14" y="-124.46" size="1.27" layer="95" xref="yes"/>
<pinref part="IC2" gate="G$1" pin="OUT"/>
</segment>
<segment>
<label x="48.26" y="-43.18" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PC2"/>
<wire x1="48.26" y1="-43.18" x2="40.64" y2="-43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="NET$1" class="0">
<segment>
<wire x1="-292.1" y1="-91.44" x2="-299.72" y2="-91.44" width="0.1524" layer="91"/>
<junction x="-292.1" y="-91.44"/>
<pinref part="R58" gate="G$1" pin="1"/>
<pinref part="R59" gate="G$1" pin="2"/>
<pinref part="T3" gate="G$1" pin="C"/>
</segment>
</net>
<net name="GND_A" class="3">
<segment>
<label x="-38.1" y="58.42" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="VSS_A"/>
<wire x1="-33.02" y1="58.42" x2="-38.1" y2="58.42" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="355.6" y1="-119.38" x2="355.6" y2="-129.54" width="0.1524" layer="91"/>
<wire x1="355.6" y1="-129.54" x2="342.9" y2="-129.54" width="0.1524" layer="91"/>
<wire x1="355.6" y1="-129.54" x2="358.14" y2="-129.54" width="0.1524" layer="91"/>
<junction x="355.6" y="-129.54"/>
<label x="358.14" y="-129.54" size="1.27" layer="95" xref="yes"/>
<pinref part="IC2" gate="G$1" pin="GND"/>
<pinref part="C22" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="111.76" y1="-63.5" x2="106.68" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="106.68" y1="-63.5" x2="101.6" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="101.6" y1="-63.5" x2="91.44" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="127" y1="-63.5" x2="111.76" y2="-63.5" width="0.1524" layer="91"/>
<junction x="111.76" y="-63.5"/>
<label x="127" y="-63.5" size="1.27" layer="95" xref="yes"/>
<pinref part="R56" gate="G$1" pin="1"/>
<pinref part="R57" gate="G$1" pin="1"/>
<wire x1="91.44" y1="-63.5" x2="86.36" y2="-63.5" width="0.1524" layer="91"/>
<junction x="91.44" y="-63.5"/>
<pinref part="VD3" gate="G$1" pin="A"/>
<wire x1="86.36" y1="-63.5" x2="81.28" y2="-63.5" width="0.1524" layer="91"/>
<wire x1="81.28" y1="-63.5" x2="81.28" y2="-60.96" width="0.1524" layer="91"/>
<pinref part="VD2" gate="G$1" pin="A"/>
<wire x1="101.6" y1="-60.96" x2="101.6" y2="-63.5" width="0.1524" layer="91"/>
<junction x="101.6" y="-63.5"/>
<pinref part="C39" gate="G$1" pin="1"/>
<wire x1="86.36" y1="-60.96" x2="86.36" y2="-63.5" width="0.1524" layer="91"/>
<junction x="86.36" y="-63.5"/>
<pinref part="C37" gate="G$1" pin="1"/>
<wire x1="106.68" y1="-60.96" x2="106.68" y2="-63.5" width="0.1524" layer="91"/>
<junction x="106.68" y="-63.5"/>
</segment>
<segment>
<wire x1="-218.44" y1="-111.76" x2="-218.44" y2="-114.3" width="0.1524" layer="91"/>
<pinref part="C52" gate="G$1" pin="-"/>
<wire x1="-236.22" y1="-109.22" x2="-236.22" y2="-114.3" width="0.1524" layer="91"/>
<pinref part="IC3" gate="G$1" pin="GND"/>
<wire x1="-218.44" y1="-114.3" x2="-236.22" y2="-114.3" width="0.1524" layer="91"/>
<wire x1="-266.7" y1="-114.3" x2="-266.7" y2="-111.76" width="0.1524" layer="91"/>
<pinref part="C51" gate="G$1" pin="-"/>
<wire x1="-236.22" y1="-114.3" x2="-248.92" y2="-114.3" width="0.1524" layer="91"/>
<junction x="-236.22" y="-114.3"/>
<junction x="-266.7" y="-114.3"/>
<wire x1="-248.92" y1="-114.3" x2="-266.7" y2="-114.3" width="0.1524" layer="91"/>
<wire x1="-299.72" y1="-114.3" x2="-299.72" y2="-101.6" width="0.1524" layer="91"/>
<pinref part="T3" gate="G$1" pin="E"/>
<wire x1="-266.7" y1="-114.3" x2="-299.72" y2="-114.3" width="0.1524" layer="91"/>
<wire x1="-218.44" y1="-114.3" x2="-203.2" y2="-114.3" width="0.1524" layer="91"/>
<junction x="-218.44" y="-114.3"/>
<wire x1="-218.44" y1="-73.66" x2="-218.44" y2="-60.96" width="0.1524" layer="91"/>
<wire x1="-218.44" y1="-60.96" x2="-233.68" y2="-60.96" width="0.1524" layer="91"/>
<wire x1="-198.12" y1="-73.66" x2="-203.2" y2="-73.66" width="0.1524" layer="91"/>
<label x="-198.12" y="-73.66" size="1.27" layer="95" xref="yes"/>
<wire x1="-203.2" y1="-73.66" x2="-213.36" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="-213.36" y1="-73.66" x2="-218.44" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="-218.44" y1="-73.66" x2="-231.14" y2="-73.66" width="0.1524" layer="91"/>
<junction x="-218.44" y="-73.66"/>
<pinref part="C15" gate="G$1" pin="2"/>
<wire x1="-231.14" y1="-73.66" x2="-271.78" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="-271.78" y1="-73.66" x2="-271.78" y2="-66.04" width="0.1524" layer="91"/>
<wire x1="-271.78" y1="-73.66" x2="-287.02" y2="-73.66" width="0.1524" layer="91"/>
<junction x="-271.78" y="-73.66"/>
<pinref part="C14" gate="G$1" pin="-"/>
<wire x1="-287.02" y1="-73.66" x2="-287.02" y2="-66.04" width="0.1524" layer="91"/>
<pinref part="DA4" gate="G$1" pin="GND"/>
<pinref part="C16" gate="G$1" pin="2"/>
<junction x="-231.14" y="-73.66"/>
<wire x1="-203.2" y1="-114.3" x2="-203.2" y2="-91.44" width="0.1524" layer="91"/>
<junction x="-203.2" y="-73.66"/>
<wire x1="-203.2" y1="-91.44" x2="-203.2" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="-200.66" y1="-91.44" x2="-203.2" y2="-91.44" width="0.1524" layer="91"/>
<junction x="-203.2" y="-91.44"/>
<pinref part="C41" gate="G$1" pin="2"/>
<wire x1="-213.36" y1="-66.04" x2="-213.36" y2="-73.66" width="0.1524" layer="91"/>
<junction x="-213.36" y="-73.66"/>
<pinref part="C55" gate="G$1" pin="2"/>
<wire x1="-248.92" y1="-111.76" x2="-248.92" y2="-114.3" width="0.1524" layer="91"/>
<junction x="-248.92" y="-114.3"/>
<pinref part="R6" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="304.8" y1="-259.08" x2="304.8" y2="-256.54" width="0.1524" layer="91"/>
<label x="304.8" y="-259.08" size="1.27" layer="95" rot="R270" xref="yes"/>
<pinref part="DA3" gate="G$1" pin="GND"/>
<wire x1="304.8" y1="-256.54" x2="284.48" y2="-256.54" width="0.1524" layer="91"/>
<junction x="304.8" y="-256.54"/>
<pinref part="C50" gate="G$1" pin="2"/>
<wire x1="284.48" y1="-256.54" x2="284.48" y2="-248.92" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="332.74" y1="-256.54" x2="332.74" y2="-259.08" width="0.1524" layer="91"/>
<label x="332.74" y="-259.08" size="1.27" layer="95" rot="R270" xref="yes"/>
<pinref part="C43" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="345.44" y1="-256.54" x2="345.44" y2="-259.08" width="0.1524" layer="91"/>
<label x="345.44" y="-259.08" size="1.27" layer="95" rot="R270" xref="yes"/>
<pinref part="R47" gate="G$1" pin="1"/>
</segment>
<segment>
<wire x1="368.3" y1="-210.82" x2="365.76" y2="-210.82" width="0.1524" layer="91"/>
<label x="368.3" y="-210.82" size="1.27" layer="95" xref="yes"/>
<pinref part="C24" gate="G$1" pin="2"/>
</segment>
<segment>
<wire x1="358.14" y1="-259.08" x2="358.14" y2="-241.3" width="0.1524" layer="91"/>
<label x="358.14" y="-259.08" size="1.27" layer="95" rot="R270" xref="yes"/>
<pinref part="DA5" gate=":1" pin="-V"/>
</segment>
<segment>
<pinref part="DA2" gate="G$1" pin="GND"/>
<pinref part="C17" gate="G$1" pin="2"/>
<wire x1="309.88" y1="-175.26" x2="309.88" y2="-185.42" width="0.1524" layer="91"/>
<wire x1="297.18" y1="-185.42" x2="309.88" y2="-185.42" width="0.1524" layer="91"/>
<wire x1="297.18" y1="-185.42" x2="297.18" y2="-187.96" width="0.1524" layer="91"/>
<junction x="297.18" y="-185.42"/>
<label x="297.18" y="-187.96" size="1.27" layer="95" rot="R270" xref="yes"/>
<pinref part="C18" gate="G$1" pin="2"/>
<wire x1="325.12" y1="-185.42" x2="309.88" y2="-185.42" width="0.1524" layer="91"/>
<junction x="309.88" y="-185.42"/>
<pinref part="VD1" gate="G$1" pin="A"/>
<wire x1="325.12" y1="-185.42" x2="335.28" y2="-185.42" width="0.1524" layer="91"/>
<junction x="325.12" y="-185.42"/>
</segment>
<segment>
<pinref part="DA6" gate="G$1" pin="VSS"/>
<wire x1="322.58" y1="-223.52" x2="327.66" y2="-223.52" width="0.1524" layer="91"/>
<label x="330.2" y="-223.52" size="1.27" layer="95" xref="yes"/>
<pinref part="DA6" gate="G$1" pin="B"/>
<wire x1="327.66" y1="-223.52" x2="330.2" y2="-223.52" width="0.1524" layer="91"/>
<wire x1="322.58" y1="-213.36" x2="327.66" y2="-213.36" width="0.1524" layer="91"/>
<wire x1="327.66" y1="-213.36" x2="327.66" y2="-223.52" width="0.1524" layer="91"/>
<junction x="327.66" y="-223.52"/>
</segment>
</net>
<net name="N$74" class="0">
<segment>
<wire x1="325.12" y1="15.24" x2="330.2" y2="15.24" width="0.1524" layer="91"/>
<pinref part="R75" gate="G$1" pin="2"/>
<pinref part="U44" gate="G$1" pin="EOC"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<wire x1="116.84" y1="142.24" x2="111.76" y2="142.24" width="0.1524" layer="91"/>
<pinref part="R29" gate="G$1" pin="1"/>
<pinref part="XP2" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$78" class="0">
<segment>
<wire x1="5.08" y1="-167.64" x2="10.16" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="5.08" y1="-162.56" x2="5.08" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="-162.56" x2="-7.62" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-7.62" y1="-167.64" x2="5.08" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-20.32" y1="-162.56" x2="-20.32" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-20.32" y1="-167.64" x2="-7.62" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="-162.56" x2="-33.02" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-33.02" y1="-167.64" x2="-20.32" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-45.72" y1="-162.56" x2="-45.72" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-45.72" y1="-167.64" x2="-33.02" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="-167.64" x2="-45.72" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-58.42" y1="-162.56" x2="-58.42" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-71.12" y1="-162.56" x2="-71.12" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-83.82" y1="-162.56" x2="-83.82" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-96.52" y1="-162.56" x2="-96.52" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-96.52" y1="-167.64" x2="-83.82" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-83.82" y1="-167.64" x2="-71.12" y2="-167.64" width="0.1524" layer="91"/>
<wire x1="-71.12" y1="-167.64" x2="-58.42" y2="-167.64" width="0.1524" layer="91"/>
<junction x="5.08" y="-167.64"/>
<junction x="-7.62" y="-167.64"/>
<junction x="-20.32" y="-167.64"/>
<junction x="-33.02" y="-167.64"/>
<junction x="-45.72" y="-167.64"/>
<junction x="-83.82" y="-167.64"/>
<junction x="-71.12" y="-167.64"/>
<junction x="-58.42" y="-167.64"/>
<pinref part="R64" gate="G$1" pin="1"/>
<pinref part="XP17" gate="G$1" pin="3"/>
<pinref part="XP15" gate="G$1" pin="3"/>
<pinref part="XP14" gate="G$1" pin="3"/>
<pinref part="XP13" gate="G$1" pin="3"/>
<pinref part="XP12" gate="G$1" pin="3"/>
<pinref part="XP11" gate="G$1" pin="3"/>
<pinref part="XP10" gate="G$1" pin="3"/>
<pinref part="XP9" gate="G$1" pin="3"/>
<pinref part="XP8" gate="G$1" pin="3"/>
</segment>
</net>
<net name="N$81" class="0">
<segment>
<wire x1="-33.02" y1="76.2" x2="-35.56" y2="76.2" width="0.1524" layer="91"/>
<wire x1="-35.56" y1="76.2" x2="-35.56" y2="78.74" width="0.1524" layer="91"/>
<pinref part="C23" gate="G$1" pin="2"/>
<pinref part="DD1" gate="G$1" pin="VCAP_2"/>
</segment>
</net>
<net name="N$82" class="0">
<segment>
<wire x1="-33.02" y1="25.4" x2="-38.1" y2="25.4" width="0.1524" layer="91"/>
<pinref part="C44" gate="G$1" pin="2"/>
<pinref part="DD1" gate="G$1" pin="VCAP_1"/>
</segment>
</net>
<net name="ADIS_INT" class="0">
<segment>
<label x="48.26" y="2.54" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PE1"/>
<wire x1="48.26" y1="2.54" x2="40.64" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="DD2" gate="G$1" pin="DIO2"/>
<wire x1="284.48" y1="142.24" x2="274.32" y2="142.24" width="0.1524" layer="91"/>
<label x="274.32" y="142.24" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="D1" gate="G$1" pin="C"/>
<wire x1="-309.88" y1="-2.54" x2="-317.5" y2="-2.54" width="0.1524" layer="91"/>
<pinref part="F3" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="C16" gate="G$1" pin="1"/>
<pinref part="DA4" gate="G$1" pin="BYPASS"/>
<wire x1="-231.14" y1="-66.04" x2="-233.68" y2="-66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="+5V_A" class="1">
<segment>
<wire x1="-218.44" y1="-99.06" x2="-228.6" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="-218.44" y1="-104.14" x2="-218.44" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="-218.44" y1="-96.52" x2="-218.44" y2="-99.06" width="0.1524" layer="91"/>
<junction x="-218.44" y="-99.06"/>
<pinref part="IC3" gate="G$1" pin="O"/>
<pinref part="C52" gate="G$1" pin="+"/>
<label x="-218.44" y="-96.52" size="1.27" layer="95" rot="R90" xref="yes"/>
</segment>
<segment>
<pinref part="DA3" gate="G$1" pin="VCC"/>
<wire x1="304.8" y1="-231.14" x2="284.48" y2="-231.14" width="0.1524" layer="91"/>
<pinref part="C50" gate="G$1" pin="1"/>
<wire x1="284.48" y1="-231.14" x2="284.48" y2="-241.3" width="0.1524" layer="91"/>
<label x="279.4" y="-231.14" size="1.27" layer="95" rot="R180" xref="yes"/>
<wire x1="279.4" y1="-231.14" x2="284.48" y2="-231.14" width="0.1524" layer="91"/>
<junction x="284.48" y="-231.14"/>
</segment>
<segment>
<pinref part="DA2" gate="G$1" pin="VDD"/>
<pinref part="C17" gate="G$1" pin="1"/>
<wire x1="297.18" y1="-175.26" x2="302.26" y2="-175.26" width="0.1524" layer="91"/>
<wire x1="297.18" y1="-175.26" x2="297.18" y2="-167.64" width="0.1524" layer="91"/>
<junction x="297.18" y="-175.26"/>
<label x="297.18" y="-167.64" size="1.27" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="ADIS_NRST" class="0">
<segment>
<pinref part="DD2" gate="G$1" pin="!RST"/>
<wire x1="284.48" y1="149.86" x2="279.4" y2="149.86" width="0.1524" layer="91"/>
<label x="274.32" y="149.86" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="R8" gate="G$1" pin="1"/>
<wire x1="279.4" y1="149.86" x2="274.32" y2="149.86" width="0.1524" layer="91"/>
<wire x1="279.4" y1="139.7" x2="279.4" y2="149.86" width="0.1524" layer="91"/>
<junction x="279.4" y="149.86"/>
</segment>
<segment>
<wire x1="-38.1" y1="-63.5" x2="-33.02" y2="-63.5" width="0.1524" layer="91"/>
<label x="-38.1" y="-63.5" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PD10"/>
</segment>
</net>
<net name="MPXV_TEMP" class="0">
<segment>
<label x="342.9" y="-177.8" size="1.27" layer="95" xref="yes"/>
<pinref part="R10" gate="G$1" pin="2"/>
<wire x1="325.12" y1="-177.8" x2="335.28" y2="-177.8" width="0.1524" layer="91"/>
<junction x="325.12" y="-177.8"/>
<pinref part="C18" gate="G$1" pin="1"/>
<wire x1="335.28" y1="-177.8" x2="342.9" y2="-177.8" width="0.1524" layer="91"/>
<wire x1="325.12" y1="-177.8" x2="322.58" y2="-177.8" width="0.1524" layer="91"/>
<pinref part="VD1" gate="G$1" pin="C"/>
<wire x1="335.28" y1="-180.34" x2="335.28" y2="-177.8" width="0.1524" layer="91"/>
<junction x="335.28" y="-177.8"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PC1"/>
<wire x1="48.26" y1="-40.64" x2="40.64" y2="-40.64" width="0.1524" layer="91"/>
<label x="48.26" y="-40.64" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="DA2" gate="G$1" pin="OUT"/>
<pinref part="R10" gate="G$1" pin="1"/>
<wire x1="312.42" y1="-177.8" x2="312.42" y2="-180.34" width="0.1524" layer="91"/>
<wire x1="312.42" y1="-180.34" x2="297.18" y2="-180.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<wire x1="355.6" y1="68.58" x2="358.14" y2="68.58" width="0.1524" layer="91"/>
<pinref part="R14" gate="G$1" pin="1"/>
<pinref part="DD3" gate="G$1" pin="INT"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="C28" gate="G$1" pin="2"/>
<wire x1="312.42" y1="63.5" x2="312.42" y2="66.04" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="CPOUT"/>
<wire x1="312.42" y1="66.04" x2="320.04" y2="66.04" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="C19" gate="G$1" pin="2"/>
<wire x1="294.64" y1="63.5" x2="294.64" y2="68.58" width="0.1524" layer="91"/>
<pinref part="DD3" gate="G$1" pin="REGOUT"/>
<wire x1="294.64" y1="68.58" x2="320.04" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<wire x1="109.22" y1="-147.32" x2="109.22" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="109.22" y1="-147.32" x2="116.84" y2="-147.32" width="0.1524" layer="91"/>
<wire x1="116.84" y1="-147.32" x2="116.84" y2="-144.78" width="0.1524" layer="91"/>
<wire x1="116.84" y1="-147.32" x2="127" y2="-147.32" width="0.1524" layer="91"/>
<junction x="116.84" y="-147.32"/>
<pinref part="C7" gate="G$1" pin="+"/>
<pinref part="C8" gate="G$1" pin="2"/>
<pinref part="DD4" gate="G$1" pin="VCC"/>
<pinref part="Q3" gate="G$1" pin="D"/>
<wire x1="109.22" y1="-147.32" x2="91.44" y2="-147.32" width="0.1524" layer="91"/>
<junction x="109.22" y="-147.32"/>
</segment>
</net>
<net name="SDC_PWR_EN" class="0">
<segment>
<pinref part="Q3" gate="G$1" pin="G"/>
<pinref part="R15" gate="G$1" pin="2"/>
<wire x1="83.82" y1="-152.4" x2="83.82" y2="-157.48" width="0.1524" layer="91"/>
<wire x1="83.82" y1="-157.48" x2="83.82" y2="-165.1" width="0.1524" layer="91"/>
<junction x="83.82" y="-157.48"/>
<label x="83.82" y="-165.1" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<label x="48.26" y="-33.02" size="1.27" layer="95" xref="yes"/>
<wire x1="40.64" y1="-33.02" x2="48.26" y2="-33.02" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PE15"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<wire x1="96.52" y1="-213.36" x2="104.14" y2="-213.36" width="0.1524" layer="91"/>
<wire x1="104.14" y1="-213.36" x2="114.3" y2="-213.36" width="0.1524" layer="91"/>
<junction x="104.14" y="-213.36"/>
<pinref part="IC1" gate="G$1" pin="VCC"/>
<pinref part="C21" gate="G$1" pin="1"/>
<pinref part="Q4" gate="G$1" pin="D"/>
</segment>
</net>
<net name="EEPROM_PWR_EN" class="0">
<segment>
<pinref part="Q4" gate="G$1" pin="G"/>
<pinref part="R16" gate="G$1" pin="2"/>
<wire x1="121.92" y1="-208.28" x2="132.08" y2="-208.28" width="0.1524" layer="91"/>
<wire x1="132.08" y1="-208.28" x2="142.24" y2="-208.28" width="0.1524" layer="91"/>
<junction x="132.08" y="-208.28"/>
<label x="142.24" y="-208.28" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<label x="48.26" y="38.1" size="1.27" layer="95" xref="yes"/>
<pinref part="DD1" gate="G$1" pin="PA1"/>
<wire x1="48.26" y1="38.1" x2="40.64" y2="38.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="C30" gate="G$1" pin="1"/>
<wire x1="370.84" y1="-66.04" x2="365.76" y2="-66.04" width="0.1524" layer="91"/>
<wire x1="365.76" y1="-66.04" x2="365.76" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="DD5" gate="G$1" pin="SETP"/>
<wire x1="365.76" y1="-68.58" x2="360.68" y2="-68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="C30" gate="G$1" pin="2"/>
<wire x1="370.84" y1="-73.66" x2="365.76" y2="-73.66" width="0.1524" layer="91"/>
<wire x1="365.76" y1="-73.66" x2="365.76" y2="-71.12" width="0.1524" layer="91"/>
<pinref part="DD5" gate="G$1" pin="SETC"/>
<wire x1="365.76" y1="-71.12" x2="360.68" y2="-71.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="DD5" gate="G$1" pin="C1"/>
<wire x1="327.66" y1="-60.96" x2="309.88" y2="-60.96" width="0.1524" layer="91"/>
<pinref part="C32" gate="G$1" pin="1"/>
<wire x1="309.88" y1="-60.96" x2="309.88" y2="-63.5" width="0.1524" layer="91"/>
</segment>
</net>
<net name="TIM1_CH1" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PE9"/>
<wire x1="40.64" y1="-17.78" x2="48.26" y2="-17.78" width="0.1524" layer="91"/>
<label x="48.26" y="-17.78" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="R38" gate="G$1" pin="1"/>
<wire x1="-101.6" y1="-180.34" x2="-101.6" y2="-182.88" width="0.1524" layer="91"/>
<label x="-101.6" y="-182.88" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="TIM1_CH2" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PE11"/>
<wire x1="40.64" y1="-22.86" x2="48.26" y2="-22.86" width="0.1524" layer="91"/>
<label x="48.26" y="-22.86" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="R39" gate="G$1" pin="1"/>
<wire x1="-88.9" y1="-180.34" x2="-88.9" y2="-182.88" width="0.1524" layer="91"/>
<label x="-88.9" y="-182.88" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="TIM1_CH3" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PE13"/>
<wire x1="40.64" y1="-27.94" x2="48.26" y2="-27.94" width="0.1524" layer="91"/>
<label x="48.26" y="-27.94" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="R40" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="-180.34" x2="-76.2" y2="-182.88" width="0.1524" layer="91"/>
<label x="-76.2" y="-182.88" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="TIM1_CH4" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PE14"/>
<wire x1="40.64" y1="-30.48" x2="48.26" y2="-30.48" width="0.1524" layer="91"/>
<label x="48.26" y="-30.48" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="R41" gate="G$1" pin="1"/>
<wire x1="-63.5" y1="-180.34" x2="-63.5" y2="-182.88" width="0.1524" layer="91"/>
<label x="-63.5" y="-182.88" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="TIM4_CH2" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PD13"/>
<wire x1="-33.02" y1="-71.12" x2="-38.1" y2="-71.12" width="0.1524" layer="91"/>
<label x="-38.1" y="-71.12" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="R43" gate="G$1" pin="1"/>
<wire x1="-38.1" y1="-180.34" x2="-38.1" y2="-182.88" width="0.1524" layer="91"/>
<label x="-38.1" y="-182.88" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="TIM4_CH3" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PD14"/>
<wire x1="-33.02" y1="-73.66" x2="-38.1" y2="-73.66" width="0.1524" layer="91"/>
<label x="-38.1" y="-73.66" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="R44" gate="G$1" pin="1"/>
<wire x1="-25.4" y1="-180.34" x2="-25.4" y2="-182.88" width="0.1524" layer="91"/>
<label x="-25.4" y="-182.88" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="TIM4_CH4" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PD15"/>
<wire x1="-33.02" y1="-76.2" x2="-38.1" y2="-76.2" width="0.1524" layer="91"/>
<label x="-38.1" y="-76.2" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="R46" gate="G$1" pin="1"/>
<wire x1="-12.7" y1="-180.34" x2="-12.7" y2="-182.88" width="0.1524" layer="91"/>
<label x="-12.7" y="-182.88" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="USART6_TX_UEXT" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PC6"/>
<wire x1="40.64" y1="-53.34" x2="48.26" y2="-53.34" width="0.1524" layer="91"/>
<label x="48.26" y="-53.34" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="3"/>
<wire x1="190.5" y1="198.12" x2="185.42" y2="198.12" width="0.1524" layer="91"/>
<label x="185.42" y="198.12" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="USART6_RX_UEXT" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PC7"/>
<wire x1="40.64" y1="-55.88" x2="48.26" y2="-55.88" width="0.1524" layer="91"/>
<label x="48.26" y="-55.88" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="4"/>
<wire x1="205.74" y1="198.12" x2="213.36" y2="198.12" width="0.1524" layer="91"/>
<label x="213.36" y="198.12" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="I2C_SLOW_SCL" class="0">
<segment>
<label x="116.84" y="58.42" size="1.27" layer="95" xref="yes"/>
<pinref part="R25" gate="G$1" pin="1"/>
<wire x1="104.14" y1="58.42" x2="116.84" y2="58.42" width="0.1524" layer="91"/>
<wire x1="104.14" y1="60.96" x2="104.14" y2="58.42" width="0.1524" layer="91"/>
<junction x="104.14" y="58.42"/>
<wire x1="104.14" y1="58.42" x2="40.64" y2="58.42" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PB10"/>
</segment>
<segment>
<wire x1="345.44" y1="17.78" x2="325.12" y2="17.78" width="0.1524" layer="91"/>
<label x="345.44" y="17.78" size="1.27" layer="95" xref="yes"/>
<pinref part="U44" gate="G$1" pin="SCL"/>
</segment>
<segment>
<wire x1="297.18" y1="-12.7" x2="294.64" y2="-12.7" width="0.1524" layer="91"/>
<label x="294.64" y="-12.7" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="U2" gate="G$1" pin="SCL"/>
</segment>
<segment>
<wire x1="96.52" y1="-218.44" x2="101.6" y2="-218.44" width="0.1524" layer="91"/>
<label x="101.6" y="-218.44" size="1.27" layer="95" xref="yes"/>
<pinref part="IC1" gate="G$1" pin="SCL"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="5"/>
<wire x1="190.5" y1="195.58" x2="185.42" y2="195.58" width="0.1524" layer="91"/>
<label x="185.42" y="195.58" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="I2C_SLOW_SDA" class="0">
<segment>
<label x="116.84" y="55.88" size="1.27" layer="95" xref="yes"/>
<pinref part="R11" gate="G$1" pin="1"/>
<wire x1="114.3" y1="55.88" x2="116.84" y2="55.88" width="0.1524" layer="91"/>
<wire x1="114.3" y1="63.5" x2="114.3" y2="55.88" width="0.1524" layer="91"/>
<junction x="114.3" y="55.88"/>
<wire x1="114.3" y1="55.88" x2="40.64" y2="55.88" width="0.1524" layer="91"/>
<pinref part="DD1" gate="G$1" pin="PB11"/>
</segment>
<segment>
<wire x1="345.44" y1="20.32" x2="325.12" y2="20.32" width="0.1524" layer="91"/>
<label x="345.44" y="20.32" size="1.27" layer="95" xref="yes"/>
<pinref part="U44" gate="G$1" pin="SDA"/>
</segment>
<segment>
<wire x1="297.18" y1="-10.16" x2="294.64" y2="-10.16" width="0.1524" layer="91"/>
<label x="294.64" y="-10.16" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="U2" gate="G$1" pin="SDA"/>
</segment>
<segment>
<wire x1="96.52" y1="-220.98" x2="101.6" y2="-220.98" width="0.1524" layer="91"/>
<label x="101.6" y="-220.98" size="1.27" layer="95" xref="yes"/>
<pinref part="IC1" gate="G$1" pin="SDA"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="6"/>
<wire x1="205.74" y1="195.58" x2="213.36" y2="195.58" width="0.1524" layer="91"/>
<label x="213.36" y="195.58" size="1.27" layer="95" xref="yes"/>
<label x="213.36" y="195.58" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="SPI2_NSS_UEXT" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PB12"/>
<wire x1="40.64" y1="53.34" x2="48.26" y2="53.34" width="0.1524" layer="91"/>
<label x="48.26" y="53.34" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="10"/>
<wire x1="205.74" y1="190.5" x2="213.36" y2="190.5" width="0.1524" layer="91"/>
<label x="213.36" y="190.5" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="SPI2_SCK_UEXT" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PB13"/>
<wire x1="40.64" y1="50.8" x2="48.26" y2="50.8" width="0.1524" layer="91"/>
<label x="48.26" y="50.8" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="9"/>
<wire x1="190.5" y1="190.5" x2="185.42" y2="190.5" width="0.1524" layer="91"/>
<label x="185.42" y="190.5" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PB14"/>
<wire x1="40.64" y1="48.26" x2="68.58" y2="48.26" width="0.1524" layer="91"/>
<pinref part="R26" gate="G$1" pin="2"/>
<wire x1="71.12" y1="50.8" x2="68.58" y2="50.8" width="0.1524" layer="91"/>
<wire x1="68.58" y1="50.8" x2="68.58" y2="48.26" width="0.1524" layer="91"/>
<pinref part="R37" gate="G$1" pin="2"/>
<wire x1="71.12" y1="45.72" x2="68.58" y2="45.72" width="0.1524" layer="91"/>
<wire x1="68.58" y1="45.72" x2="68.58" y2="48.26" width="0.1524" layer="91"/>
<junction x="68.58" y="48.26"/>
</segment>
</net>
<net name="SPI2_MOSI_UEXT" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="PB15"/>
<wire x1="40.64" y1="45.72" x2="48.26" y2="45.72" width="0.1524" layer="91"/>
<label x="48.26" y="45.72" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="8"/>
<wire x1="205.74" y1="193.04" x2="213.36" y2="193.04" width="0.1524" layer="91"/>
<label x="213.36" y="193.04" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="SPI2_MISO_UEXT" class="0">
<segment>
<pinref part="R26" gate="G$1" pin="1"/>
<wire x1="81.28" y1="50.8" x2="83.82" y2="50.8" width="0.1524" layer="91"/>
<label x="83.82" y="50.8" size="1.27" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="7"/>
<wire x1="190.5" y1="193.04" x2="185.42" y2="193.04" width="0.1524" layer="91"/>
<label x="185.42" y="193.04" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="TIM4_CH1" class="0">
<segment>
<pinref part="R42" gate="G$1" pin="1"/>
<wire x1="-50.8" y1="-180.34" x2="-50.8" y2="-182.88" width="0.1524" layer="91"/>
<label x="-50.8" y="-182.88" size="1.27" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PD12"/>
<wire x1="-33.02" y1="-68.58" x2="-38.1" y2="-68.58" width="0.1524" layer="91"/>
<label x="-38.1" y="-68.58" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="AD_SDI" class="0">
<segment>
<pinref part="DA6" gate="G$1" pin="SDI"/>
<wire x1="289.56" y1="-220.98" x2="287.02" y2="-220.98" width="0.1524" layer="91"/>
<label x="287.02" y="-220.98" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PD1"/>
<wire x1="-33.02" y1="-40.64" x2="-38.1" y2="-40.64" width="0.1524" layer="91"/>
<label x="-38.1" y="-40.64" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="!AD_CS" class="0">
<segment>
<pinref part="DA6" gate="G$1" pin="!CS"/>
<wire x1="289.56" y1="-218.44" x2="287.02" y2="-218.44" width="0.1524" layer="91"/>
<label x="287.02" y="-218.44" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PD0"/>
<wire x1="-33.02" y1="-38.1" x2="-38.1" y2="-38.1" width="0.1524" layer="91"/>
<label x="-38.1" y="-38.1" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="AD_CLK" class="0">
<segment>
<pinref part="DA6" gate="G$1" pin="CLK"/>
<wire x1="289.56" y1="-215.9" x2="287.02" y2="-215.9" width="0.1524" layer="91"/>
<label x="287.02" y="-215.9" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="DD1" gate="G$1" pin="PA3"/>
<wire x1="40.64" y1="33.02" x2="48.26" y2="33.02" width="0.1524" layer="91"/>
<label x="48.26" y="33.02" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="R45" gate="G$1" pin="1"/>
<pinref part="DA6" gate="G$1" pin="W"/>
<wire x1="335.28" y1="-215.9" x2="322.58" y2="-215.9" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="BAT1" gate="G$1" pin="+"/>
<pinref part="VD4" gate="1" pin="A"/>
<wire x1="-76.2" y1="68.58" x2="-78.74" y2="68.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$30" class="0">
<segment>
<pinref part="Q1" gate="G$1" pin="S"/>
<wire x1="-266.7" y1="-88.9" x2="-266.7" y2="-78.74" width="0.1524" layer="91"/>
<pinref part="R59" gate="G$1" pin="1"/>
<wire x1="-256.54" y1="-55.88" x2="-259.08" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="-256.54" y1="-60.96" x2="-259.08" y2="-60.96" width="0.1524" layer="91"/>
<wire x1="-259.08" y1="-60.96" x2="-259.08" y2="-55.88" width="0.1524" layer="91"/>
<pinref part="L1" gate="G$1" pin="2"/>
<wire x1="-294.64" y1="-55.88" x2="-292.1" y2="-55.88" width="0.1524" layer="91"/>
<junction x="-259.08" y="-55.88"/>
<pinref part="C15" gate="G$1" pin="1"/>
<wire x1="-292.1" y1="-55.88" x2="-287.02" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="-287.02" y1="-55.88" x2="-271.78" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="-271.78" y1="-55.88" x2="-259.08" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="-271.78" y1="-58.42" x2="-271.78" y2="-55.88" width="0.1524" layer="91"/>
<junction x="-271.78" y="-55.88"/>
<pinref part="C14" gate="G$1" pin="+"/>
<wire x1="-287.02" y1="-58.42" x2="-287.02" y2="-55.88" width="0.1524" layer="91"/>
<junction x="-287.02" y="-55.88"/>
<pinref part="DA4" gate="G$1" pin="IN"/>
<pinref part="DA4" gate="G$1" pin="EN"/>
<wire x1="-292.1" y1="-81.28" x2="-292.1" y2="-78.74" width="0.1524" layer="91"/>
<junction x="-292.1" y="-55.88"/>
<wire x1="-292.1" y1="-78.74" x2="-292.1" y2="-55.88" width="0.1524" layer="91"/>
<wire x1="-266.7" y1="-78.74" x2="-292.1" y2="-78.74" width="0.1524" layer="91"/>
<junction x="-292.1" y="-78.74"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="R30" gate="G$1" pin="1"/>
<pinref part="U$7" gate="G$1" pin="GRN"/>
<wire x1="170.18" y1="101.6" x2="187.96" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="R60" gate="G$1" pin="1"/>
<pinref part="U$7" gate="G$1" pin="RED"/>
<wire x1="170.18" y1="96.52" x2="187.96" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="DD1" gate="G$1" pin="V_BAT"/>
<wire x1="-33.02" y1="68.58" x2="-53.34" y2="68.58" width="0.1524" layer="91"/>
<pinref part="VD4" gate="1" pin="C"/>
<pinref part="C40" gate="G$1" pin="1"/>
<wire x1="-53.34" y1="68.58" x2="-71.12" y2="68.58" width="0.1524" layer="91"/>
<junction x="-53.34" y="68.58"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
