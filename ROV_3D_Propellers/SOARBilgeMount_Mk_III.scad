/*Hardware required 8-32 for clamp, 10-24 for nut base.
SOAR DOllar Bay HS. 9.20.14
Use with middle wedge and bottom wedge to attach a bilge pump motor to 1/2 inch PVC "T"
*/

use <write.scad>
use <NutPocketCodes.scad>

//variables
res=180;	//Resolution for rendering

motorCylIn=20.00; //inner radius around bilge motor
motorCylOut=motorCylIn+4; //outer radius around bilge motor 
motorLength=20; //length of constant cylinder around motor

propCylIn=30; // propeller inner radius
propCylOut=propCylIn+3; // propeller outer radius
propLength=22; // length of constant cylinder around propeller
taperLength=40; // length of taper between motor and propeller sections.


//Pillar Info

nPillar=4; // Number of pillars, best between 3 and 6
pillarThick=5; // Diameter of the circles in the pillar
pillarLength_1=propLength; //Length of pillar segment on prop guard
pillarLength_2=taperLength; //Length of middle pillar segment
pillarLength_3=motorLength; //Length of pillar segment on motor guard
pillarExtrude=5.5; //Extrusion length where segments 1 & 2 connect.
pillarExtrude_base=3.5;//Extrusion length where segments 2 & 3 connect 
pillarExtrude_total=0; //Use this variable to change the total pillar's extrusion


pillarXscale=1; // X scale of the overall pillar
pillarYscale=1.5;// Y scale of the overall pillar. Use this variable to change the pillar's width
pillarZscale=1;// Z scale of the overall pillar


//Clamp
clampThick=18;
clampHeight=20;
clampWidth=12;
nutRad=5.3;
nutHeight=8;
boltRad=2.45;
boltLength=motorCylOut*2+5;
slitThick=2;
slitWidth=clampWidth+8;

//groove
grooveDepth=4.0;
grooveWidth=7.1;
grooveLength=20;

//bolt head groove hole
headRad=5;
headDepth=6;

nickOff=20;

use <write.scad>

difference(){
	union(){
//groove
	
		rotate(91,[0,0,1])
		translate([motorCylOut,0,grooveLength/2])
		rotate(90,[0,0,0])
		cube([grooveDepth, grooveWidth, grooveLength],center=true);
//groove top remove


//motor base
		cylinder(h=motorLength,r=motorCylOut,center=false,$fn=res);
//clamp box
		difference(){rotate(180,[0,0,1])
		translate([motorCylOut+clampWidth/3,0,clampHeight/2])
		cube([clampWidth, clampThick, clampHeight],center=true);

} //end of difference



//Pillar building

for ( i = [0 : (nPillar-1)] )
	rotate( i*360/nPillar+225,[0,0,1]	)



scale([pillarXscale,pillarYscale,pillarZscale])

union(){


// creates the pillar segment on the prop guard

	hull(){

		hull(){

		translate([propCylOut,0,motorLength+pillarLength_2])
		cylinder(h=.1,r=pillarThick/2,center=false,$fn=res);

		translate([propCylOut+pillarExtrude+pillarExtrude_total,0,motorLength+pillarLength_2])
		cylinder(h=.1,r=pillarThick/2,center=false,$fn=res);} // end of hull

	translate([propCylOut-pillarThick/8,0,motorLength+pillarLength_2+pillarLength_1-.1])
	cylinder(h=.1,r=pillarThick/8,center=false,$fn=res);} // end of hull


//creates the pillar segment connecting the prop guard to the motor cylinder

	union(){
		hull(){

				hull(){
		
				translate([propCylOut,0,motorLength+pillarLength_2])
				cylinder(h=.1,r=pillarThick/2,center=false,$fn=res);

				translate([propCylOut+pillarExtrude+pillarExtrude_total,0,motorLength+pillarLength_2])
				cylinder(h=.1,r=pillarThick/2,center=false,$fn=res);} //end of hull

		hull(){
		translate([motorCylIn+3,0,motorLength])
		cylinder(h=.1,r=pillarThick/2,center=false,$fn=res);

		translate([motorCylIn+3+pillarExtrude_base+pillarExtrude_total,0,motorLength])
		cylinder(h=.1,r=pillarThick/2,center=false,$fn=res);} //end of hull

} //end of hull
		

// creates the pillar segment on the motor cylinder

hull(){
		hull(){
		translate([motorCylIn+3,0,motorLength])
		cylinder(h=.1,r=pillarThick/2,center=false,$fn=res);

		translate([motorCylIn+3+pillarExtrude_base+pillarExtrude_total,0,motorLength])
		cylinder(h=.1,r=pillarThick/2,center=false,$fn=res);} //end of hull

		translate([motorCylOut-pillarThick/8,0,0])
		cylinder(h=.1,r=pillarThick/8,center=false,$fn=res);} //end of hull
	} //end of union
} // end of union

//prop guard
		translate([0,0,propLength/2+taperLength+motorLength])
		cylinder(h=propLength,r=propCylOut,center=true,$fn=res);
} //end of union

//motor remove inside
	translate([0,0,-.05])
	cylinder(h=motorLength+.2,r=motorCylIn,center=false,$fn=res);
//prop guard remove inside
	translate([0,0,propLength/2+taperLength+motorLength])
	cylinder(h=propLength+.2,r=propCylIn,center=true,$fn=res);
writecylinder("SOAR",[0,0,propLength/2+taperLength+motorLength],propCylOut,0,h=12,t=1.5); // creates "SOAR" text. The code is found in "write.scad"

//bolt hole
	rotate(60,[0,0,1])
	translate([0,0,grooveLength/2])
	rotate(90,[-.6,1,0])
	cylinder(r1=boltRad+1,r2=boltRad,h=boltLength,center=true, $fn=res);
//bolthead
	rotate(91,[0,0,1])
	translate([(motorCylIn+motorCylOut)/2,0,grooveLength/2])
	rotate(90,[0,1,0])
	cylinder(r1=headRad,r2=boltRad,h=headDepth,center=true, $fn=res);



	
//clamp nut hole
	rotate(180,[0,0,1])
	translate([motorCylOut+clampWidth/3,clampThick/2+.1,motorLength/2])
	rotate(90,[1,0,0
])
	Nut_10(); //code for the No.10 nut pocket is in "Nut Pocket Codes.scad"
	
//clamp bolt hole	
	rotate(180,[0,0,1])
	translate([motorCylOut+clampWidth/3,0,motorLength/2])
	rotate(90,[1,0,0])
	cylinder(r=boltRad,boltLength,center=true, $fn=res);

// clamp slit
	rotate(180,[0,0,1])
	translate([motorCylOut+clampWidth/2,0,clampHeight/2])

	cube([slitWidth+2, slitThick, clampHeight],center=true);


} // end of difference



//end of code