module Nut_8()
	{
			cylinder(h=3.9,r=10/2,$fn=6);
	}
	

module Nut_10()
	{
			cylinder(h=4.15,r=11/2,$fn=6);
	}
	

module Nut_8Full()
	{
	rotate([0,0,-30]){
	union()
			{
			cylinder(h=5.9,r=10/2,$fn=6);
			
	rotate([0,0,30])
	translate([0,-9.8/2,0])
				
				
			cube([10,9.8,5.9]);
				
				
			}
		}
	}


module Nut_10Full()
	{
	rotate([0,0,-30]){
	union()
			{
			cylinder(h=6.15,r=11/2,$fn=6);
			
	rotate([0,0,30])
	translate([0,-10.8/2,0])
				
				
			cube([10,10.8,6.15]);
				
				
			}
		}
	}


