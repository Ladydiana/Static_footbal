#include "WorldDrawer2d.h"
#define _USE_MATH_DEFINES
#include <math.h>
//#include <windows.h>
bool WorldDrawer2d::animation=true;


//used global vars
CoordinateSystem2d *cs1, *cs2,*cs3, *cs4, *cs5, *cf66, *css1b, *css2b, *css3b, *css1o, *css2o, *css3o, *w;
Object2d *o1, *o2, *o3, *o4, *o5, *of66, *sb1, *sb2, *sb3, *so1, *so2, *so3, *winner;
int r, onShoot, scoreBlue, scoreOrange, already_marked_so1, already_marked_so2, already_marked_so3, already_marked_sb1, already_marked_sb2, already_marked_sb3;
static int iteration;
float tx,ty;


//add
void WorldDrawer2d::init(){
	float x0,y0;
	int i;
	iteration=1;
	scoreBlue=0;
	scoreOrange=0;
	float a[9]; a[0]=0; a[1]=float(3.14/4); a[2]=float(3.14/2); a[3]=float(3*3.14/4); a[4]=float(3.14); a[5]=5*3.14/4; a[6]=3*3.14/2; a[7]=7*3.14/4; a[8]=2*3.14;
	glClearColor(0, 0.3, 0, 0);
	r=rand()%4;
	onShoot=0;
	already_marked_so1=0;
	already_marked_so2=0;
	already_marked_so3=0;
	already_marked_sb1=0;
	already_marked_sb2=0;
	already_marked_sb3=0;

	//creeaza sistem de coordonate client
	cs1 = new CoordinateSystem2d();
	cs2 = new CoordinateSystem2d();	
	cs3 = new CoordinateSystem2d();
	cs4 = new CoordinateSystem2d();
	cs5 = new CoordinateSystem2d();
	cf66 = new CoordinateSystem2d();
	css1b = new CoordinateSystem2d();
	css2b = new CoordinateSystem2d();
	css3b = new CoordinateSystem2d();
	css1o = new CoordinateSystem2d();
	css2o = new CoordinateSystem2d();
	css3o = new CoordinateSystem2d();
	w = new CoordinateSystem2d();
	cs_used.push_back(cs1);
	cs_used.push_back(cs2);
	cs_used.push_back(cs3);
	cs_used.push_back(cs4);
	cs_used.push_back(cs5);
	cs_used.push_back(cf66);
	cs_used.push_back(css1b);
	cs_used.push_back(css2b);
	cs_used.push_back(css3b);
	cs_used.push_back(css1o);
	cs_used.push_back(css2o);
	cs_used.push_back(css3o);
	cs_used.push_back(w);
	
	/*		THE RED BALL
	 *	~pozitie initiala (0,0)
	 */
	std::vector<Point2d> points;
	std::vector<int> topology;
	x0=0;y0=0;
	points.push_back(Point2d(x0,y0));
	for(i=0;i<=8;++i){
		points.push_back(Point2d(x0+0.5*cos(a[i]),y0+0.5*sin(a[i])));
	}	
	for(i=1;i<=8;i++){
		if(i==8){
			topology.push_back(1);
			topology.push_back(0);
			topology.push_back(8);
		}
		else {
			topology.push_back(0);
			topology.push_back(i);
			topology.push_back(i+1);
		}
	}
	o1 = new Object2d(points,topology);
	o1->setcolor(1,0,0);
	cs1->objectAdd(o1);

	// ~BLUE TEAM
	//(player1 = o2)	
	std::vector<Point2d> points2;
	std::vector<int> topology2;
	x0=-5;y0=-5;
	points2.push_back(Point2d(x0,y0));
	for(i=0;i<=8;++i){
		points2.push_back(Point2d(x0+cos(a[i]),y0+sin(a[i])));
	}	
	for(i=1;i<=8;i++){
		if(i==8){
			topology2.push_back(1);
			topology2.push_back(0);
			topology2.push_back(8);
		}
		else {
			topology2.push_back(0);
			topology2.push_back(i);
			topology2.push_back(i+1);
		}
	}
	o2 = new Object2d(points2,topology2);
	o2->setcolor(0,0,1);
	cs2->objectAdd(o2);

	// Player 2 -o3
	std::vector<Point2d> points3;
	std::vector<int> topology3;
	x0=5;y0=5;
	points3.push_back(Point2d(x0,y0));
	for(i=0;i<=8;++i){
		points3.push_back(Point2d(x0+cos(a[i]),y0+sin(a[i])));
	}	
	for(i=1;i<=8;i++){
		if(i==8){
			topology3.push_back(1);
			topology3.push_back(0);
			topology3.push_back(8);
		}
		else {
			topology3.push_back(0);
			topology3.push_back(i);
			topology3.push_back(i+1);
		}
	}
	o3 = new Object2d(points3,topology3);
	o3->setcolor(0,0,1);
	cs3->objectAdd(o3);

	// ORANGE TEAM
	// Player1 = 04
	std::vector<Point2d> points4;
	std::vector<int> topology4;
	x0=5;y0=-5;
	points4.push_back(Point2d(x0,y0));
	for(i=0;i<=8;++i){
		points4.push_back(Point2d(x0+cos(a[i]),y0+sin(a[i])));
	}	
	for(i=1;i<=8;i++){
		if(i==8){
			topology4.push_back(1);
			topology4.push_back(0);
			topology4.push_back(8);
		}
		else {
			topology4.push_back(0);
			topology4.push_back(i);
			topology4.push_back(i+1);
		}
	}
	o4 = new Object2d(points4,topology4);
	o4->setcolor(1,0.5,0);
	cs4->objectAdd(o4);
	
	//Player2 = 05
	std::vector<Point2d> points5;
	std::vector<int> topology5;
	x0=-5;y0=5;
	points5.push_back(Point2d(x0,y0));
	for(i=0;i<=8;++i){
		points5.push_back(Point2d(x0+cos(a[i]),y0+sin(a[i])));
	}	
	for(i=1;i<=8;i++){
		if(i==8){
			topology5.push_back(1);
			topology5.push_back(0);
			topology5.push_back(8);
		}
		else {
			topology5.push_back(0);
			topology5.push_back(i);
			topology5.push_back(i+1);
		}
	}
	o5 = new Object2d(points5,topology5);
	o5->setcolor(1,0.5,0);
	cs5->objectAdd(o5);

	//Retusuri la teren
	CoordinateSystem2d *cf1, *cf2, *cf3, *cf4, *cf5, *cf6, *cf7, *cf8;
	Object2d *of1, *of2, *of3, *of4, *of5, *of6, *of7, *of8;
	cf1 = new CoordinateSystem2d();
	cf2 = new CoordinateSystem2d();	
	cf3 = new CoordinateSystem2d();
	cf4 = new CoordinateSystem2d();
	cf5 = new CoordinateSystem2d();
	cf6 = new CoordinateSystem2d();
	cf7 = new CoordinateSystem2d();
	cf8 = new CoordinateSystem2d();
	cs_used.push_back(cf1);
	cs_used.push_back(cf2);
	cs_used.push_back(cf3);
	cs_used.push_back(cf4);
	cs_used.push_back(cf5);
	cs_used.push_back(cf6);
	cs_used.push_back(cf7);
	cs_used.push_back(cf8);
	
	//Bara marcaj stanga
	std::vector<Point2d> pointf1;
	std::vector<int> topologyf1;
	pointf1.push_back(Point2d(-15,-16));
	pointf1.push_back(Point2d(-15,16));
	pointf1.push_back(Point2d(-14,16));
	pointf1.push_back(Point2d(-14,-16));
	topologyf1.push_back(0);
	topologyf1.push_back(1);
	topologyf1.push_back(2);
	topologyf1.push_back(2);
	topologyf1.push_back(3);
	topologyf1.push_back(0);
	of1 = new Object2d(pointf1,topologyf1);
	of1->setcolor(1,1,1);
	cf1->objectAdd(of1);
	
	//Bara marcaj dreapta
	std::vector<Point2d> pointf2;
	std::vector<int> topologyf2;
	pointf2.push_back(Point2d(15,-16));
	pointf2.push_back(Point2d(15,16));
	pointf2.push_back(Point2d(14,16));
	pointf2.push_back(Point2d(14,-16));
	topologyf2.push_back(0);
	topologyf2.push_back(1);
	topologyf2.push_back(2);
	topologyf2.push_back(2);
	topologyf2.push_back(3);
	topologyf2.push_back(0);
	of2 = new Object2d(pointf2,topologyf2);
	of2->setcolor(1,1,1);
	cf2->objectAdd(of2);

	//Bara marcaj stanga jos
	std::vector<Point2d> pointf3;
	std::vector<int> topologyf3;
	pointf3.push_back(Point2d(-14,-16));
	pointf3.push_back(Point2d(-4,-16));
	pointf3.push_back(Point2d(-4,-15));
	pointf3.push_back(Point2d(-14,-15));
	topologyf3.push_back(0);
	topologyf3.push_back(1);
	topologyf3.push_back(2);
	topologyf3.push_back(2);
	topologyf3.push_back(3);
	topologyf3.push_back(0);
	of3 = new Object2d(pointf3,topologyf3);
	of3->setcolor(1,1,1);
	cf3->objectAdd(of3);

	// Bara marcaj stanga-sus
	std::vector<Point2d> pointf4;
	std::vector<int> topologyf4;
	pointf4.push_back(Point2d(-14,15));
	pointf4.push_back(Point2d(-4,15));
	pointf4.push_back(Point2d(-4,16));
	pointf4.push_back(Point2d(-14,16));
	topologyf4.push_back(0);
	topologyf4.push_back(1);
	topologyf4.push_back(2);
	topologyf4.push_back(2);
	topologyf4.push_back(3);
	topologyf4.push_back(0);
	of4 = new Object2d(pointf4,topologyf4);
	of4->setcolor(1,1,1);
	cf4->objectAdd(of4);

	//Bara marcaj dreapta-jos
	std::vector<Point2d> pointf5;
	std::vector<int> topologyf5;
	pointf5.push_back(Point2d(4,-16));
	pointf5.push_back(Point2d(14,-16));
	pointf5.push_back(Point2d(14,-15));
	pointf5.push_back(Point2d(4,-15));
	topologyf5.push_back(0);
	topologyf5.push_back(1);
	topologyf5.push_back(2);
	topologyf5.push_back(2);
	topologyf5.push_back(3);
	topologyf5.push_back(0);
	of5 = new Object2d(pointf5,topologyf5);
	of5->setcolor(1,1,1);
	cf5->objectAdd(of5);

	//Bara marcaj dreapta-sus
	std::vector<Point2d> pointf6;
	std::vector<int> topologyf6;
	pointf6.push_back(Point2d(4,15));
	pointf6.push_back(Point2d(14,15));
	pointf6.push_back(Point2d(14,16));
	pointf6.push_back(Point2d(4,16));
	topologyf6.push_back(0);
	topologyf6.push_back(1);
	topologyf6.push_back(2);
	topologyf6.push_back(2);
	topologyf6.push_back(3);
	topologyf6.push_back(0);
	of6 = new Object2d(pointf6,topologyf6);
	of6->setcolor(1,1,1);
	cf6->objectAdd(of6);

	//Bara centru-jos
	std::vector<Point2d> pointf7;
	std::vector<int> topologyf7;
	pointf7.push_back(Point2d(-4,-16));
	pointf7.push_back(Point2d(4,-16));
	pointf7.push_back(Point2d(4,-15));
	pointf7.push_back(Point2d(-4,-15));
	topologyf7.push_back(0);
	topologyf7.push_back(1);
	topologyf7.push_back(2);
	topologyf7.push_back(2);
	topologyf7.push_back(3);
	topologyf7.push_back(0);
	of7 = new Object2d(pointf7,topologyf7);
	of7->setcolor(0,0,1);
	cf7->objectAdd(of7);
	
	//Bara centru-sus
	std::vector<Point2d> pointf8;
	std::vector<int> topologyf8;
	pointf8.push_back(Point2d(-4,15));
	pointf8.push_back(Point2d(4,15));
	pointf8.push_back(Point2d(4,16));
	pointf8.push_back(Point2d(-4,16));
	topologyf8.push_back(0);
	topologyf8.push_back(1);
	topologyf8.push_back(2);
	topologyf8.push_back(2);
	topologyf8.push_back(3);
	topologyf8.push_back(0);
	of8 = new Object2d(pointf8,topologyf8);
	of8->setcolor(1,0.5,0);
	cf8->objectAdd(of8);

	//Bara marcaj centru
	std::vector<Point2d> pointf66;
	std::vector<int> topologyf66;
	pointf66.push_back(Point2d(-15,-0.2));
	pointf66.push_back(Point2d(15,-0.2));
	pointf66.push_back(Point2d(15,0.2));
	pointf66.push_back(Point2d(-15,0.2));
	topologyf66.push_back(0);
	topologyf66.push_back(1);
	topologyf66.push_back(2);
	topologyf66.push_back(2);
	topologyf66.push_back(3);
	topologyf66.push_back(0);
	of66 = new Object2d(pointf66,topologyf66);
	of66->setcolor(1,1,1);
	cf66->objectAdd(of66);
	
	//Barele de scor. Le adaug cand inscriu
	std::vector<Point2d> pointso1;
	std::vector<int> topologyso1;
	pointso1.push_back(Point2d(16,3));
	pointso1.push_back(Point2d(16.5,3));
	pointso1.push_back(Point2d(16.5,6));
	pointso1.push_back(Point2d(16,6));
	topologyso1.push_back(0);
	topologyso1.push_back(1);
	topologyso1.push_back(2);
	topologyso1.push_back(2);
	topologyso1.push_back(3);
	topologyso1.push_back(0);
	so1 = new Object2d(pointso1,topologyso1);
	so1->setcolor(0,0.3,0);
	css1o->objectAdd(so1);

	std::vector<Point2d> pointso2;
	std::vector<int> topologyso2;
	pointso2.push_back(Point2d(17,3));
	pointso2.push_back(Point2d(17.5,3));
	pointso2.push_back(Point2d(17.5,6));
	pointso2.push_back(Point2d(17,6));
	topologyso2.push_back(0);
	topologyso2.push_back(1);
	topologyso2.push_back(2);
	topologyso2.push_back(2);
	topologyso2.push_back(3);
	topologyso2.push_back(0);
	so2 = new Object2d(pointso2,topologyso2);
	so2->setcolor(0,0.3,0);
	css2o->objectAdd(so2);

	std::vector<Point2d> pointso3;
	std::vector<int> topologyso3;
	pointso3.push_back(Point2d(18,3));
	pointso3.push_back(Point2d(18.5,3));
	pointso3.push_back(Point2d(18.5,6));
	pointso3.push_back(Point2d(18,6));
	topologyso3.push_back(0);
	topologyso3.push_back(1);
	topologyso3.push_back(2);
	topologyso3.push_back(2);
	topologyso3.push_back(3);
	topologyso3.push_back(0);
	so3 = new Object2d(pointso3,topologyso3);
	so3->setcolor(0,0.3,0);
	css3o->objectAdd(so3);

	std::vector<Point2d> pointsb1;
	std::vector<int> topologysb1;
	pointsb1.push_back(Point2d(16,-3));
	pointsb1.push_back(Point2d(16.5,-3));
	pointsb1.push_back(Point2d(16.5,-6));
	pointsb1.push_back(Point2d(16,-6));
	topologysb1.push_back(0);
	topologysb1.push_back(1);
	topologysb1.push_back(2);
	topologysb1.push_back(2);
	topologysb1.push_back(3);
	topologysb1.push_back(0);
	sb1 = new Object2d(pointsb1,topologysb1);
	sb1->setcolor(0,0.3,0);
	css1b->objectAdd(sb1);

	std::vector<Point2d> pointsb2;
	std::vector<int> topologysb2;
	pointsb2.push_back(Point2d(17,-3));
	pointsb2.push_back(Point2d(17.5,-3));
	pointsb2.push_back(Point2d(17.5,-6));
	pointsb2.push_back(Point2d(17,-6));
	topologysb2.push_back(0);
	topologysb2.push_back(1);
	topologysb2.push_back(2);
	topologysb2.push_back(2);
	topologysb2.push_back(3);
	topologysb2.push_back(0);
	sb2 = new Object2d(pointsb2,topologysb2);
	sb2->setcolor(0,0.3,0);
	css2b->objectAdd(sb2);

	std::vector<Point2d> pointsb3;
	std::vector<int> topologysb3;
	pointsb3.push_back(Point2d(18,-3));
	pointsb3.push_back(Point2d(18.5,-3));
	pointsb3.push_back(Point2d(18.5,-6));
	pointsb3.push_back(Point2d(18,-6));
	topologysb3.push_back(0);
	topologysb3.push_back(1);
	topologysb3.push_back(2);
	topologysb3.push_back(2);
	topologysb3.push_back(3);
	topologysb3.push_back(0);
	sb3 = new Object2d(pointsb3,topologysb3);
	sb3->setcolor(0,0.3,0);
	css3b->objectAdd(sb3);

	//The SPELLING of WINNER (Jesus cate puncte!!!)
	std::vector<Point2d> pointw;
	std::vector<int> topologyw;
	pointw.push_back(Point2d(-20,8.5));		//0
	pointw.push_back(Point2d(-19.5,8.5));	//1
	pointw.push_back(Point2d(-19.5,6.5));	//2
	pointw.push_back(Point2d(-20,6.5));		//3
	pointw.push_back(Point2d(-19.5,7));		//4
	pointw.push_back(Point2d(-18,7));		//5
	pointw.push_back(Point2d(-18,6.5));		//6
	pointw.push_back(Point2d(-18,8.5));		//7
	pointw.push_back(Point2d(-17.5,8.5));	//8
	pointw.push_back(Point2d(-17.5,6.5));	//9
	pointw.push_back(Point2d(-19,6.5));		//10
	pointw.push_back(Point2d(-18.5,6.5));	//11
	pointw.push_back(Point2d(-18.5,8.5));	//12
	pointw.push_back(Point2d(-19,8.5));		//13
	pointw.push_back(Point2d(-19,3.5));		//14
	pointw.push_back(Point2d(-18.5,3.5));	//15
	pointw.push_back(Point2d(-18.5,5.5));	//16
	pointw.push_back(Point2d(-19,5.5));		//17
	pointw.push_back(Point2d(-20,2.5));		//18
	pointw.push_back(Point2d(-19.5,2.5));	//19
	pointw.push_back(Point2d(-19.5,0.5));	//20
	pointw.push_back(Point2d(-20,0.5));		//21
	pointw.push_back(Point2d(-18,0.5));		//22
	pointw.push_back(Point2d(-18,2.5));		//23	
	pointw.push_back(Point2d(-17.5,2.5));	//24
	pointw.push_back(Point2d(-17.5,0.5));	//25
	pointw.push_back(Point2d(-20,-2.5));	//26
	pointw.push_back(Point2d(-19.5,-2.5));	//27
	pointw.push_back(Point2d(-19.5,-0.5));	//28
	pointw.push_back(Point2d(-20,-0.5));	//29
	pointw.push_back(Point2d(-18,-0.5));	//30
	pointw.push_back(Point2d(-18,-2.5));	//31	
	pointw.push_back(Point2d(-17.5,-2.5));	//32
	pointw.push_back(Point2d(-17.5,-0.5));	//33
	pointw.push_back(Point2d(-20,-3.5));	//34
	pointw.push_back(Point2d(-19.5,-3.5));	//35
	pointw.push_back(Point2d(-19.5,-5.5));	//36
	pointw.push_back(Point2d(-20,-5.5));	//37
	pointw.push_back(Point2d(-19.5,-4));	//38
	pointw.push_back(Point2d(-18,-4));		//39
	pointw.push_back(Point2d(-18,-3.5));	//40
	pointw.push_back(Point2d(-19.5,-5));	//41
	pointw.push_back(Point2d(-18,-5));		//42
	pointw.push_back(Point2d(-18,-5.5));	//43
	pointw.push_back(Point2d(-19.5,-4.4));	//44
	pointw.push_back(Point2d(-18.5,-4.4));	//45
	pointw.push_back(Point2d(-18.5,-4.6));	//46
	pointw.push_back(Point2d(-19.5,-4.6));	//47
	pointw.push_back(Point2d(-20,-6.5));	//48
	pointw.push_back(Point2d(-19.5,-6.5));	//49
	pointw.push_back(Point2d(-19.5,-8.5));	//50
	pointw.push_back(Point2d(-20,-8.5));	//51
	pointw.push_back(Point2d(-18,-6.5));	//52
	pointw.push_back(Point2d(-18,-7.5));	//53
	pointw.push_back(Point2d(-20,-7.5));	//54
	pointw.push_back(Point2d(-19.5,-7.5));	//55
	pointw.push_back(Point2d(-17.5,-8.5));	//56
	pointw.push_back(Point2d(-18,-8.5));	//57
	topologyw.push_back(0);
	topologyw.push_back(1);
	topologyw.push_back(2);
	topologyw.push_back(2);
	topologyw.push_back(3);
	topologyw.push_back(0);
	topologyw.push_back(2);
	topologyw.push_back(4);
	topologyw.push_back(5);
	topologyw.push_back(5);
	topologyw.push_back(6);
	topologyw.push_back(2);
	topologyw.push_back(6);
	topologyw.push_back(7);
	topologyw.push_back(8);
	topologyw.push_back(8);
	topologyw.push_back(9);
	topologyw.push_back(6);
	topologyw.push_back(10);
	topologyw.push_back(11);
	topologyw.push_back(12);
	topologyw.push_back(12);
	topologyw.push_back(13);
	topologyw.push_back(10);
	topologyw.push_back(14);
	topologyw.push_back(15);
	topologyw.push_back(16);
	topologyw.push_back(16);
	topologyw.push_back(17);
	topologyw.push_back(14);
	topologyw.push_back(18);
	topologyw.push_back(19);
	topologyw.push_back(20);
	topologyw.push_back(20);
	topologyw.push_back(21);
	topologyw.push_back(18);
	topologyw.push_back(22);
	topologyw.push_back(23);
	topologyw.push_back(24);
	topologyw.push_back(24);
	topologyw.push_back(25);
	topologyw.push_back(22);
	topologyw.push_back(18);
	topologyw.push_back(19);
	topologyw.push_back(25);
	topologyw.push_back(25);
	topologyw.push_back(22);
	topologyw.push_back(18);
	topologyw.push_back(26);
	topologyw.push_back(27);
	topologyw.push_back(28);
	topologyw.push_back(28);
	topologyw.push_back(29);
	topologyw.push_back(26);
	topologyw.push_back(30);
	topologyw.push_back(31);
	topologyw.push_back(32);
	topologyw.push_back(32);
	topologyw.push_back(33);
	topologyw.push_back(30);
	topologyw.push_back(29);
	topologyw.push_back(28);
	topologyw.push_back(32);
	topologyw.push_back(32);
	topologyw.push_back(31);
	topologyw.push_back(29);
	topologyw.push_back(34);
	topologyw.push_back(35);
	topologyw.push_back(36);
	topologyw.push_back(36);
	topologyw.push_back(37);
	topologyw.push_back(34);
	topologyw.push_back(35);
	topologyw.push_back(40);
	topologyw.push_back(39);
	topologyw.push_back(39);
	topologyw.push_back(38);
	topologyw.push_back(35);
	topologyw.push_back(36);
	topologyw.push_back(41);
	topologyw.push_back(42);
	topologyw.push_back(42);
	topologyw.push_back(43);
	topologyw.push_back(36);
	topologyw.push_back(44);
	topologyw.push_back(45);
	topologyw.push_back(46);
	topologyw.push_back(46);
	topologyw.push_back(47);
	topologyw.push_back(44);
	topologyw.push_back(48);
	topologyw.push_back(49);
	topologyw.push_back(50);
	topologyw.push_back(50);
	topologyw.push_back(51);
	topologyw.push_back(48);
	topologyw.push_back(48);
	topologyw.push_back(52);
	topologyw.push_back(53);
	topologyw.push_back(53);
	topologyw.push_back(54);
	topologyw.push_back(48);
	topologyw.push_back(54);
	topologyw.push_back(55);
	topologyw.push_back(56);
	topologyw.push_back(56);
	topologyw.push_back(57);
	topologyw.push_back(54);
	winner = new Object2d(pointw,topologyw);
	winner->setcolor(0,0.3,0);
	w->objectAdd(winner);
}


void WorldDrawer2d::onIdle(){	//per frame
	static int iteration=1;
	static bool o1dir=true;
	static bool o2dir=true;
	static bool o3dir=true;
	static bool o3dir2=true;
	
	if(animation){
		
		if(iteration==-100){
			winner->setcolor(0,0.3,0);
			o1->setcolor(1,0,0);
			o2->setcolor(0,0,1);
			o3->setcolor(0,0,1);
			o4->setcolor(1,0.5,0);
			o5->setcolor(1,0.5,0);
		}
		
		if((fabs(o1->points.at(0).x-o2->points.at(0).x)>1.2) || (fabs(o1->points.at(0).y-o2->points.at(0).y)>1.2))
			if((fabs(o1->points.at(0).x-o3->points.at(0).x)>1.2) || (fabs(o1->points.at(0).y-o3->points.at(0).y)>1.2))
				if((fabs(o1->points.at(0).x-o4->points.at(0).x)>1.2) || (fabs(o1->points.at(0).y-o4->points.at(0).y)>1.2))
					if((fabs(o1->points.at(0).x-o5->points.at(0).x)>1.2) || (fabs(o1->points.at(0).y-o5->points.at(0).y)>1.2))
						if(onShoot==0){
							if( (iteration >100) &&(iteration <10000) && (iteration %100)){
								if(r==0)
									o1->translate(0.1,0.1);
								if(r==1)
									o1->translate(-0.1,-0.1);
								if(r==2)
									o1->translate(-0.1,0.1);
								if(r==3)
									o1->translate(-0.1,0.1);
							}
						}
						else if(onShoot==1){
							o1->translate(tx/50,ty/50);
						}
						
		if( (o1->points.at(0).x<-14) || (o1->points.at(0).x>14) || (o1->points.at(0).y>15) || (o1->points.at(0).y<-15)){
			if((o1->points.at(0).x>=-4)&&(o1->points.at(0).x<=4)&&(o1->points.at(0).y<=-15)){
				scoreOrange++;
				if((scoreOrange==1) && (already_marked_so1==0) ){
					already_marked_so1=1;
					so1->setcolor(1,0.5,0);
				}
				if((scoreOrange==2) && (already_marked_so2==0)){
					already_marked_so2=1;
					so2->setcolor(1,0.5,0);
				}
				if((scoreOrange==3)&&(already_marked_so3==0)){
					already_marked_so3=1;
					so3->setcolor(1,0.5,0);
					//Sleep(10000);
				}
			}
			if((o1->points.at(0).x>=-4)&&(o1->points.at(0).x<=4)&&(o1->points.at(0).y>=15)){
				scoreBlue++;
				if((scoreBlue==1)&&(already_marked_sb1==0)){
					already_marked_sb1=1;
					sb1->setcolor(0,0,1);
				}
				if((scoreBlue==2)&&(already_marked_sb2==0)){
					already_marked_sb2=1;
					sb2->setcolor(0,0,1);
				}
				if((scoreBlue==3)&&(already_marked_sb3==0)){
					already_marked_sb3=1;
					sb3->setcolor(0,0,1);
					//Sleep(10000);
				}
			} 
			iteration=1;
			o1->translate(-o1->points.at(0).x,-o1->points.at(0).y);
			r=rand()%4;
			onShoot=0;
		}
		
		
		if(scoreBlue==3 || scoreOrange==3){
			if(scoreBlue==3)
				winner->setcolor(0,0,1);
			if(scoreOrange==3)
				winner->setcolor(1,0.5,0);
			o1->setcolor(1,1,1);
			o2->setcolor(0,0.3,0);
			o3->setcolor(0,0.3,0);
			o4->setcolor(0,0.3,0);
			o5->setcolor(0,0.3,0);
			scoreBlue=0;
			scoreOrange=0;
			sb1->setcolor(0,0.3,0);
			sb2->setcolor(0,0.3,0);
			sb3->setcolor(0,0.3,0);
			so1->setcolor(0,0.3,0);
			so2->setcolor(0,0.3,0);
			so3->setcolor(0,0.3,0);
			already_marked_so1=0;
			already_marked_so2=0;
			already_marked_so3=0;
			already_marked_sb1=0;
			already_marked_sb2=0;
			already_marked_sb3=0;
			iteration=-1000;
		}
		iteration++;
	}

}

void WorldDrawer2d::onKey(unsigned char key){
	Point2d p(0,0);
	float angle_left=M_PI/4;
	float angle_right=-M_PI/4;
	
	if((fabs(o1->points.at(0).x-o2->points.at(0).x)<=1.2) && (fabs(o1->points.at(0).y-o2->points.at(0).y)<=1.2)){
		onShoot=0;
		p.x=o2->points.at(0).x;
		p.y=o2->points.at(0).y;
	}
	if((fabs(o1->points.at(0).x-o3->points.at(0).x)<=1.2) && (fabs(o1->points.at(0).y-o3->points.at(0).y)<=1.2)){
		onShoot=0;
		p.x=o3->points.at(0).x;
		p.y=o3->points.at(0).y;
	}
	if((fabs(o1->points.at(0).x-o4->points.at(0).x)<=1.2) && (fabs(o1->points.at(0).y-o4->points.at(0).y)<=1.2)){
		onShoot=0;
		p.x=o4->points.at(0).x;
		p.y=o4->points.at(0).y;
	}
	if((fabs(o1->points.at(0).x-o5->points.at(0).x)<=1.2) && (fabs(o1->points.at(0).y-o5->points.at(0).y)<=1.2)){
		onShoot=0;
		p.x=o5->points.at(0).x;
		p.y=o5->points.at(0).y;
	}

	if(p.x!=0 && p.y!=0)
		switch(key){
			case 'w':
				o1->rotateRelativeToPoint(p,angle_left);
				break;
			case 'a':
				o1->rotateRelativeToPoint(p,angle_left);
				break;
			case 'd':
				o1->rotateRelativeToPoint(p,angle_right);
				break;
			case 's':
				tx=o1->points.at(0).x-p.x;
				ty=o1->points.at(0).y-p.y;
				o1->translate(tx,ty);
				onShoot=1;
				break;
			default:
				break;
		}
}


int main(int argc, char** argv){
	WorldDrawer2d wd2d(argc,argv,600,600,200,100,std::string("Lab 1"));
	wd2d.init();
	wd2d.run();
	return 0;
}