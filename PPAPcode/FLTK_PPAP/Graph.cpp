

#include "Graph.h"
//#include <initializer_list>
#include <windows.h>
#include<map>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>




namespace Graph_lib {


Shape::Shape(std::initializer_list<Point> lst)
{
    for(auto p : lst)
        add(p);
}

void Shape::draw_lines() const
{
	if (color().visibility() && 1<points.size())
		for (unsigned int i=1; i<points.size(); ++i)
			fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);
}



void Shape::draw() const
{
	Fl_Color oldc = fl_color(); // save the current color
	// there is no good portable way of retrieving the current style
	fl_color(lcolor.as_int());
	fl_line_style(ls.style(),ls.width());
	draw_lines();
	fl_color(oldc);	// reset color (to pevious) and style (to default)
	fl_line_style(0);
}



// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel)
{
    double x1 = p1.x;
    double x2 = p2.x;
	double x3 = p3.x;
	double x4 = p4.x;
	double y1 = p1.y;
	double y2 = p2.y;
	double y3 = p3.y;
	double y4 = p4.y;

	double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
	if (denom == 0){
		parallel= true;
		return pair<double,double>(0,0);
	}
	parallel = false;
	return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
								((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}


//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
}

void Polygon::add(Point p)
{
	int np = number_of_points();

	if (1<np) {	// check that thenew line isn't parallel to the previous one
		if (p==point(np-1)) error("polygon point equal to previous point");
		bool parallel;
		line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
		if (parallel)
			error("two polygon points lie in a straight line");
	}

	for (int i = 1; i<np-1; ++i) {	// check that new segment doesn't interset and old point
		Point ignore(0,0);
		if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
			error("intersect in polygon");
	}


	Closed_polyline::add(p);
}


void Polygon::draw_lines() const
{
		if (number_of_points() < 3) error("less than 3 points in a Polygon");
		Closed_polyline::draw_lines();
}

//----------------------------------------------------
Regular_hexagon::Regular_hexagon(Point p, int dis_center, double theta)
: c{p}, r{dis_center}, t{theta*PI/180}
{
    double x=0.0;
    double y=0.0;

    int sides = 6;
    for(int s = 0; s<sides; s++)
    {
        x = r*cos(t)+1-0.5;
        y = r*sin(t)+1-0.5;
        add(Point(c.x+x,c.y+y));
        t+=PI/3;
        //std::cout << "x, y, angle " << x << ','<< y<<',' << t << '\n';
        //std::cout << "angle rad " << t << '\n';
        //std::cout << "angle stopnie " << t*180/pi << '\n';
    }
}
    // x = r*cos t
    // y = r*sin t
   // OR
   // x^2 + y^2 = r^2
   // y = x*tg(angle)  //
   // x^2 + x^2*(tg(angle))^2 = r^2
   // x^2*(1 + (tg(angle))^2) = r^2
   //  x = r/sqrt(1+tg(angle))^2
   // -pi/2 < alpha < pi/2 + but what about sign:(


   /* x = r/sqrt(1+pow(tan(angle),2));
        std::cout << "x, y, angle " << x << ','<< y<<',' << angle << '\n';
        if((angle>(pi/2) && angle<pi) || (angle>3/2*pi && angle < 2*pi))
            x=-x;
        y = x*tan(angle);
        std::cout << "x, y, angle " << x << ','<< y<<',' << angle << '\n';
        add(Point(c.x+x,c.y+y));
        std::cout << "angle rad " << angle << '\n';
        std::cout << "angle stopnie " << angle*180/pi << '\n';
        //if(angle>2*pi)
        //    angle/=2*pi;
        angle+=pi/3;
        if(angle>2*pi)
            angle/=2*pi;
        std::cout << "angle rad " << angle << '\n';
        std::cout << "angle stopnie " << angle*180/pi << '\n';*/
/*
void Regular_hexagon::draw_lines() const
{
     Polygon::draw_lines();

}
  */
//----------------------------------------------------


Regular_polygon::Regular_polygon(Point p, int dis_center, int sides, double theta)
: c{p}, r{dis_center}, s{sides}, t{theta*PI/180}
{
    double x=0.0;
    double y=0.0;
    double angle_change = (360.0 / s) * PI/180;
    for(int side = 0; side<s; side++)
    {
        x = r*cos(t)+1-0.5;
        y = r*sin(t)+1-0.5;
        add(Point(c.x+x,c.y+y));
        t+=angle_change;
        //std::cout << "x, y, angle " << x << ','<< y<<',' << t << '\n';
        //std::cout << "angle rad " << t << '\n';
        //std::cout << "angle stopnie " << t*180/pi << '\n';
    }
}
/*
void Regular_polygon::draw_lines() const
{
     Polygon::draw_lines();

}
*/
//----------------------------------------------------
/* // a,b points of diagonal
Right_triangle::Right_triangle(Point a, Point b, double bac)
: ang_abc{bac*PI/180}
{
    // find Point c;

    // y= mx+w
    // m = rise/run;
    double vx, vy, vu;
    vy = b.y - a.y  ;
    vx = b.x - a.x;
    vu = sqrt(pow(vx,2)+ pow(vy,2));


    double ab_x_angle, ac_x_angle;

    if(vx!=0)
        ab_x_angle = std::atan(vy/vx);
    else
        ab_x_angle = 90*PI/180;

    ac_x_angle = ab_x_angle-ang_abc;
    double vx_ac, vy_ac, vu_ac;
    vu_ac = cos(ang_abc)*vu;
    vy_ac = sin(ac_x_angle)*vu_ac;
    vx_ac = cos(ac_x_angle)*vu_ac;
    double xdif = a.x+vx_ac;
    double ydif = a.y+vy_ac;
    std::cout << "x:"<< xdif <<'\n';
    std::cout << "y:"<< ydif <<'\n';
    Point c = Point(xdif, ydif);
    std::cout << "c.x:" << c.x <<'\n';
    std::cout << "c.y:" << c.y <<'\n';

    add(a);
    add(b);
    add(c);
}
*/

// points a, b are on base of  right triangle
Right_triangle::Right_triangle(Point a, Point b, double bac )
: ang_bac{bac*PI/180}
{
     // y= mx+w  // m = rise/run;
     // find Point c
     double vx_ab, vy_ab, vu_ab;

    vy_ab = b.y - a.y  ;
    vx_ab = b.x - a.x;
    vu_ab = sqrt(pow(vx_ab,2)+ pow(vy_ab,2));

     //    vx   +  -
     // vy
     //  +      I   II
    //   -      IV    III
    //

    double xab_angle, xac_angle;
  //  calculate xab_angle
    if(vy_ab*vx_ab > 0)
        xab_angle = std::atan(vy_ab/vx_ab);
    else if(vy_ab*vx_ab<0)
        xab_angle = std::atan(vy_ab/vx_ab);
    else if(vy_ab==0)
        xab_angle = 0;
    else if(vx_ab==0)
        xab_angle = 90*PI/180;
    // caculate xac_angle
    if(vx_ab>=0 && vy_ab>=0)  // I
        xac_angle = xab_angle+ang_bac;
    else if(vx_ab<=0&&vy_ab>=0)  // II
        xac_angle = PI+xab_angle-ang_bac;
    else if(vx_ab>0&&vy_ab<0)    // IV
        xac_angle = xab_angle-ang_bac;
    else if(vx_ab<=0 && vy_ab<=0)     // III
        xac_angle = PI+xab_angle+ang_bac;


    /*  cout values of angles
    std::cout << "xab_angle: " << xab_angle*180/PI << '\n';
    std::cout << "xac_angle: " << xac_angle*180/PI << '\n';
    std::cout << "bac_angle: " << ang_bac*180/PI << '\n';
      */
    double vx_ac, vy_ac, vu_ac;
    // cos (ang_bac) = vu_ab/vu_ac
    vu_ac = vu_ab/cos(ang_bac);
    //
    vy_ac = sin(xac_angle) * vu_ac;
    vx_ac = cos(xac_angle) * vu_ac;
    Point c = Point(a.x+vx_ac, a.y+vy_ac);
    add(a);
    add(b);
    add(c);
    add(a);

}


void Right_triangle::draw_lines()  const
{
    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i=0; i<number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int());	// reset color
    }

    if (color().visibility())
        Shape::draw_lines();
}

//----------------------------------------------------


void Open_polyline::draw_lines() const
{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for(int i=0; i<number_of_points(); ++i){
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
			Shape::draw_lines();
}


void Closed_polyline::draw_lines() const
{
	Open_polyline::draw_lines();

	if (color().visibility())	// draw closing line:
		fl_line(point(number_of_points()-1).x,point(number_of_points()-1).y,point(0).x,point(0).y);
}

//----------------------------------------------------

void Shape::move(int dx, int dy)
{
	for (unsigned int i = 0; i<points.size(); ++i) {
		points[i].x+=dx;
		points[i].y+=dy;
	}
}

//----------------------------------------------------
void Lines::draw_lines() const
{
//	if (number_of_points()%2==1) error("odd number of points in set of lines");
	if (color().visibility())
		for (int i=1; i<number_of_points(); i+=2)
			fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
}

//----------------------------------------------------

 void Arrow::draw_lines() const
{
    Line::draw_lines();

    const int arrow_height =6;
    const int arrow_side =3;
    double pc1x,pc1y,pc2x, pc2y, pox,poy; // triangle's Point corner 1 and 2 and middle of base
    // length of vector p1p2
    double vu = sqrt(pow((point(1).y-point(0).y), 2) + pow((point(1).x-point(0).x), 2));
    // length of vector p1p2 for axis x
    double vy = point(1).y - point(0).y;
    // length of vector p1p2 for axis y
    double vx = point(1).x - point(0).x;
    // p2.x minus project arrow_height on x axis
    pox = point(1).x - (vx/vu) * arrow_height ;
    // p2.y minus project arrow_height on y axis
    poy =  point(1).y - (vy/vu) * arrow_height ;
    // sin ph =  vy/vu;
    // cos ph = vx / vu;
    // svx = sin ph * arrow_side;
    // svy = cos ph * arrow_side

    pc1x = pox + (vy/vu) * arrow_side; //
    pc1y = poy - (vx/vu) * arrow_side;
    pc2x = pox - (vy/vu) * arrow_side;
    pc2y = poy + (vx/vu) * arrow_side;

    if(color().visibility())    {
        fl_begin_complex_polygon();
        fl_vertex(point(1).x, point(1).y);
        fl_vertex(pc1x, pc1y);
        fl_vertex(pc2x,  pc2y);
        fl_end_complex_polygon();
    }

}
//----------------------------------------------------
Arc::Arc(Point p, int width, int height, int b_ang, int e_ang)
    : w(width), h(height), ang{make_pair(b_ang, e_ang)}
    {
        if(ang.first > ang.second) error("First angle cannot be bigger than second angle. Arc::Arc");
        add(p);
    };


//----------------------------------------------------
void Arc::draw_lines() const
{
    if(fill_color().visibility()){
            fl_color(fill_color().as_int());
            fl_pie(point(0).x, point(0).y, major(), minor(), angle_beg(), angle_end());
            fl_color(color().as_int());

    }
    if(color().visibility()){
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, w, h,
               ang.first, ang.second);

    }
}
 // fl_arc (int x, int y, int w, int h, double beg_arc, double end_arc)s
 // the passed bounding box x, y, w, h
 // x, y == Point, left top corner
 //  w, h == rectanle,  ellipse is fit inside the given rectangle w, h
 // beg_arc, end_arc == two angles measured in degrees counter-clockwise
 // from 3 o'clock

 // -----------------------------------------------------
Box::Box(Point p, int width, int height, int radius)
: w(width), h(height), r(radius)
{
    if(!(width>r+r && height > r+r && (width>0 && height>0)))
        error("Box: Given values are wrong. Width or height are smaller then 2xradius");
    else
        add(p);
}

Box::Box(Point p, int width, int height)
:   w(width), h(height), r(5)
{
    if(!(width>r+r && height > r+r && (width>0 && height>0)))
        error("Box: Given values are wrong. Width or height are smaller then 2xradius");
    else
        add(p);
}

void Box::draw_lines() const
{

    if(fill_color().visibility()){

        // draw  complex polygon, fill
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        fl_vertex(point(0).x+w-r+1, point(0).y);
        fl_vertex(point(0).x+r, point(0).y);
        fl_vertex(point(0).x, point(0).y+r);
        fl_vertex(point(0).x, point(0).y+h-r);
        fl_vertex(point(0).x+r, point(0).y+h);
        fl_vertex(point(0).x+w-r, point(0).y+h);
        fl_vertex(point(0).x+w, point(0).y+h-r+1);
        fl_vertex(point(0).x+w, point(0).y+r);
        fl_end_complex_polygon();

        // draw filled arcs
        //fl_pie(point(0).x, point(0).y, major(), minor(), angle_beg(), angle_end());
        fl_pie(point(0).x, point(0).y, r+r, r+r, 90, 180);
        fl_pie(point(0).x+w-r-r+1, point(0).y, r+r, r+r, 0, 90);
        fl_pie(point(0).x, point(0).y+h-r-r+1, r+r, r+r, 180, 270);
        fl_pie(point(0).x+w-r-r+1, point(0).y+h-r-r+1, r+r, r+r, 270, 360);
        fl_color(color().as_int());
    }

    if(color().visibility()){
        fl_color(color().as_int());
        // draw lines for arcs
        //fl_arc(point(0).x, point(0).y, w, h, ang.first, ang.second);
        fl_arc(point(0).x, point(0).y, r+r, r+r, 90, 180);
        fl_arc(point(0).x+w-r-r+1, point(0).y, r+r, r+r, 0, 90);
        fl_arc(point(0).x, point(0).y+h-r-r+1, r+r, r+r, 180, 270);
        fl_arc(point(0).x+w-r-r+1, point(0).y+h-r-r+1, r+r, r+r, 270, 360);
        // draw lines
        //fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
        fl_line(point(0).x+w-r+1, point(0).y,
                point(0).x+r, point(0).y);
        fl_line(point(0).x, point(0).y+r,
                point(0).x, point(0).y+h-r);
        fl_line(point(0).x+r, point(0).y+h,
                point(0).x+w-r, point(0).y+h);
        fl_line(point(0).x+w, point(0).y+h-r+1,
                point(0).x+w, point(0).y+r);
    }
}



Point n(const Box & b)
{
    return Point(b.point(0).x+b.w/2, b.point(0).y);
}

Point s(const Box & b)
{
    return Point(b.point(0).x+b.w/2, b.point(0).y+b.h);
}
Point e(const Box & b);
Point w(const Box & b);
Point center(const Box & b);
Point ne(const Box & b);
Point se(const Box & b);
Point sw(const Box & b);
Point nw(const Box & b);
// -----------------------------------------------------

void Text::draw_lines() const
{
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(),fnt_sz);
	fl_draw(lab.c_str(), point(0).x, point(0).y);
	fl_font(ofnt,osz);
}

// -----------------------------------------------------

Text_Box::Text_Box(Point p, int width, int height, int radius, const std::string str)
 : b{p, width, height, radius},
 Text{Point(p.x+6, p.y+18), str}
{
};

Text_Box::Text_Box(Point p, int width, const std::string str)
:b{p, width, h_tb},
 Text{Point(p.x+6, p.y+18), str}
{

}

void Text_Box::draw_lines() const
{
    b.draw();
    Text::draw_lines();
}

void Text_Box::move(int dx, int dy)
{
    b.move(dx,dy);
    Text::move(dx,dy);
}
// -----------------------------------------------------
Function::Function(Fct f, double r1, double r2, Point xy, int count, double xscale, double yscale)
// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
// x coordinates are scaled by xscale and y coordinates scaled by yscale
{
	if (r2-r1<=0) error("bad graphing range");
	if (count<=0) error("non-positive graphing count");
	double dist = (r2-r1)/count;
	double r = r1;
	for (int i = 0; i<count; ++i) {
		add(Point(xy.x+int(r*xscale),xy.y-int(f(r)*yscale)));
		r += dist;
	}
}

//Function::Function(Fct2 f, double r1, double r2, Point xy, int count, double xscale, double yscale)
//// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
//// x coordinates are scaled by xscale and y coordinates scaled by yscale
//{
//    if (r2 - r1 <= 0) error("bad graphing range");
//    if (count <= 0) error("non-positive graphing count");
//    double dist = (r2 - r1) / count;
//    double r = r1;
//    for (int i = 0; i < count; ++i) {
//        add(Point(xy.x + int(r * xscale), xy.y - int(f(r) * yscale)));
//        r += dist;
//    }
//}


// -----------------------------------------------------
void Rectangle::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x,point(0).y,w,h);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {	// edge on top of fill
		fl_color(color().as_int());
		fl_rect(point(0).x,point(0).y,w,h);
	}
}
//-------------------------------------------
Point n(const Graph_lib::Rectangle & r)
{
    return Point(r.point(0).x+r.width()/2, r.point(0).y);
}

Point s(const Rectangle & r)
{
    return Point(r.point(0).x+r.width()/2, r.point(0).y+r.height());
}

Point e(const Rectangle & r)
{
    return Point(r.point(0).x+r.width(), r.point(0).y+r.height()/2);
}

Point w(const Rectangle & r)
{
    return Point(r.point(0).x, r.point(0).y+r.height()/2);
}

Point center(const Rectangle & r)
{
    return Point(r.point(0).x+r.width()/2, r.point(0).y+r.height()/2);
}

Point ne(const Rectangle & r)
{
     return Point(r.point(0).x+r.width(), r.point(0).y);
}

Point se(const Rectangle & r)
{
    return Point(r.point(0).x+r.width(), r.point(0).y+r.height());
}

Point sw(const Rectangle & r)
{
    return Point(r.point(0).x, r.point(0).y+r.height());
}

Point nw(const Rectangle & r)
{
    return Point(r.point(0).x, r.point(0).y);
}
//-------------------------------------------


Axis::Axis(Orientation d, Point xy, int length, int n, string lab)
	:label(Point(0,0),lab)
{
	if (length<0) error("bad axis length");
	switch (d){
	case Axis::x:
		{	Shape::add(xy);	// axis line
			Shape::add(Point(xy.x+length,xy.y));	// axis line
			if (1<n) {
				int dist = length/n;
				int x = xy.x+dist;
				for (int i = 0; i<n; ++i) {
					notches.add(Point(x,xy.y),Point(x,xy.y-5));
				x += dist;
			}
		}
		// label under the line
		//label.move(length/3,xy.y+20);
		label.move(xy.x+length+10,xy.y+20);
		break;
	}
	case Axis::y:
		{	Shape::add(xy);	// a y-axis goes up
			Shape::add(Point(xy.x,xy.y-length));
			if (1<n) {
			int dist = length/n;
			int y = xy.y-dist;
			for (int i = 0; i<n; ++i) {
				notches.add(Point(xy.x,y),Point(xy.x+5,y));
				y -= dist;
			}
		}
		// label at top
		label.move(xy.x-10,xy.y-length-10);
		break;
	}
	case Axis::z:
		error("z axis not implemented");
	}
}

void Axis::draw_lines() const
{
	Shape::draw_lines();	// the line
	notches.draw();	// the notches may have a different color from the line
	label.draw();	// the label may have a different color from the line
}


void Axis::set_color(Color c)
{
	Shape::set_color(c);
	notches.set_color(c);
	label.set_color(c);
}

void Axis::move(int dx, int dy)
{
	Shape::move(dx,dy);
	notches.move(dx,dy);
	label.move(dx,dy);
}

void Circle::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,point(0).y,r+r-1,r+r-1,0,360);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
	}
}

Point give_point(const Circle & c, double angle)
// the equation of the Circle
// x = r * cos(Theta);
// y = r * sin(Theta;
// -
{
    double x = c.radius()*cos(angle*PI/180);
    double y = c.radius()*sin(angle*PI/180);
    return Point(c.center().x+x, c.center().y-y);
}
//double t  = angle;// std::atan(double(e.minor())/e.major());
    //    std::cout << t<< '\n';

Point n(const Circle & c)
{
    return Point(c.center().x, c.center().y-c.radius());
}
Point s(const Circle & c)
{
   return Point(c.center().x, c.center().y+c.radius());
}
Point e(const Circle & c)
{
    return Point(c.center().x+c.radius(), c.center().y);
}
Point w(const Circle & c)
{
    return Point(c.center().x-c.radius(), c.center().y);
}
Point center(const Circle & c)
{
    return c.center();
}
// y/x = angle{45}
// y = x tg(angle); tg 45 = 1;
// x^2 + y^2 = r^2;
// x^2 + x^2 = r^2;
// x = r/sqrt(2);
Point ne(const Circle & c)
{
    // x==y==dif
    double dif = c.radius()/ sqrt(2);
    return Point(center(c).x + dif, center(c).y - dif);
}
Point se(const Circle & c)
{
   // x==y==dif
    double dif = c.radius()/ sqrt(2);
    return Point(center(c).x + dif, center(c).y + dif);
}
Point sw(const Circle & c)
{
    // x==y==dif
    double dif = c.radius()/ sqrt(2);
    return Point(center(c).x - dif, center(c).y + dif);
}
Point nw(const Circle & c)
{
    // x==y==dif
    double dif = c.radius()/ sqrt(2);
    return Point(center(c).x - dif, center(c).y - dif);
}

//-------------------------------------------

void Ellipse::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,point(0).y,w+w,h+h,0,360);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,w+w,h+h,0,360);
	}
}

Point give_point(const Ellipse & e, double angle)
// the equation of the ellipse
// x = r * cos(Theta);
// y = r * sin(Theta;
{
    double x = e.major()*cos(angle*PI/180);
    double y = e.minor()*sin(angle*PI/180);
    return Point(e.center().x+x, e.center().y-y);
}

Point n(const Ellipse & e)
{
    return Point(e.center().x, e.center().y-e.minor());
}
Point s(const Ellipse & e)
{
    return Point(e.center().x, e.center().y+e.minor());
}
Point e(const Ellipse & e)
{
    return Point(e.center().x+e.major(), e.center().y);
}
Point w(const Ellipse & e)
{
    return Point(e.center().x-e.major(), e.center().y);
}
Point center(const Ellipse & e)
{
    return e.center();
}
Point ne(const Ellipse & e)
// the equation of the ellipse is x^2/a^2 + y^2/b^2 = 1
// The equation of the line is y = x tan(alpha)
// x^2/a^2 + (x*tan(alpha))^2)/b^2 = 1 or x = +/- a*b/ (sqrt(b^2+a^2*(tan(alpha))^2))
// -pi/2 < alpha < pi/2 +
{
    double t  = std::atan(double(e.minor())/e.major());
//    std::cout << t<< '\n';
    double x = round((e.minor())*e.major()*sqrt(1/(pow(e.minor(),2)+pow(e.major(), 2)*pow(t,2))));
    double y = t*x;
    return Point(e.center().x+x, e.center().y-y);
}
Point se(const Ellipse & e)
{
    double t  = std::atan(double(e.minor())/e.major());
//    std::cout << t<< '\n';
    double x = round((e.minor())*e.major()*sqrt(1/(pow(e.minor(),2)+pow(e.major(), 2)*pow(t,2))));
    double y = t*x;
    return Point(e.center().x+x, e.center().y+y);
}
Point sw(const Ellipse & e)
{
    double t  = std::atan(double(e.minor())/e.major());
//    std::cout << t<< '\n';
    double x = round((e.minor())*e.major()*sqrt(1/(pow(e.minor(),2)+pow(e.major(), 2)*pow(t,2))));
    double y = t*x;
    return Point(e.center().x-x, e.center().y+y);
}
Point nw(const Ellipse & e)
{
    double t  = std::atan(double(e.minor())/e.major());
//    std::cout << t<< '\n';
    double x = round((e.minor())*e.major()*sqrt(1/(pow(e.minor(),2)+pow(e.major(), 2)*pow(t,2))));
    double y = t*x;
    return Point(e.center().x-x, e.center().y-y);
}

//-------------------------------------------

void draw_mark(Point xy, char c)
{
	static const int dx = 4;
	static const int dy = 4;
	string m(1,c);
	fl_draw(m.c_str(),xy.x-dx,xy.y+dy);
}

void Marked_polyline::draw_lines() const
{
	Open_polyline::draw_lines();
	for (int i=0; i<number_of_points(); ++i)
		draw_mark(point(i),mark[i%mark.size()]);
}
/*
void Marks::draw_lines() const
{
	for (int i=0; i<number_of_points(); ++i)
		fl_draw(mark.c_str(),point(i).x-4,point(i).y+4);
}
*/


std::map<string,Suffix::Encoding> suffix_map;

int init_suffix_map()
{
	suffix_map["jpg"] = Suffix::jpg;
	suffix_map["JPG"] = Suffix::jpg;
	suffix_map["jpeg"] = Suffix::jpg;
	suffix_map["JPEG"] = Suffix::jpg;
	suffix_map["gif"] = Suffix::gif;
	suffix_map["GIF"] = Suffix::gif;
	suffix_map["bmp"] = Suffix::bmp;
	suffix_map["BMP"] = Suffix::bmp;
	return 0;
}

Suffix::Encoding get_encoding(const string& s)
		// try to deduce type from file name using a lookup table
{
	static int x = init_suffix_map();

	string::const_iterator p = find(s.begin(),s.end(),'.');
	if (p==s.end()) return Suffix::none;	// no suffix

	string suf(p+1,s.end());
	return suffix_map[suf];
}

bool can_open(const string& s)
            // check if a file named s exists and can be opened for reading
{
	std::ifstream ff(s.c_str());
	return bool(ff);
}


// somewhat overelaborate constructor
// because errors related to image files can be such a pain to debug
Image::Image(Point xy,  string s, Suffix::Encoding e)
	:w(0), h(0), fn(xy,"")
{
	add(xy);

	if (!can_open(s)) {
		fn.set_label("cannot open \""+s+'\"');
		p = new Bad_image(30,20);	// the "error image"
		return;
	}

	if (e == Suffix::none) e = get_encoding(s);

	switch(e) {
	case Suffix::jpg:
		p = new Fl_JPEG_Image(s.c_str());
		break;
	case Suffix::gif:
		p = new Fl_GIF_Image(s.c_str());
		break;
//	case Suffix::bmp:
//		p = new Fl_BMP_Image(s.c_str());
//		break;
	default:	// Unsupported image encoding
		fn.set_label("unsupported file type \""+s+'\"');
		p = new Bad_image(30,20);	// the "error image"
	}
}

void Image::draw_lines() const
{
	if (fn.label()!="") fn.draw_lines();

	if (w&&h)
		p->draw(point(0).x,point(0).y,w,h,cx,cy);
	else
		p->draw(point(0).x,point(0).y);
}

//------------------------------------------------------------------------------
// chapter 14
void Smiley::draw_lines() const
{
    Circle::draw_lines();
    if(fill_color().visibility()){
        // drawing fill eyes
        fl_color(fill_color().as_int());
        fl_pie(point(0).x + radius()/2, point(0).y + radius()/2,
                radius()/2, radius()/2, 0, 360);

        fl_pie(point(0).x + radius()/2, point(0).y + radius()/2,
                radius()/2, radius()/2, 0, 360);
        // drawing fill mouth
        fl_pie(point(0).x, point(0).y + radius()/2,
                radius()/2, radius()/2, 180, 360);
        fl_color(color().as_int()); // reset color
    }

    if(color().visibility()){
        // drawing  eyes
        fl_color(color().as_int());
        fl_arc(point(0).x + 2*radius()/8, point(0).y + 3*radius()/8,
               radius()/2, radius()/2, 0, 360);

        fl_arc(point(0).x + radius()+2*radius()/8, point(0).y + 3*radius()/8,
               radius()/2, radius()/2, 0, 360);
        // drawing mouth
        fl_arc(point(0).x + radius()-radius()/4, point(0).y + radius(),
               radius()/2, radius()/2, 180, 360);

    }
}

void Smiley_hat::draw_lines() const
{

    Smiley::draw_lines(); // drawing Smiley

    if(fill_color().visibility()){
        // drawing hat
        fl_color(fill_color().as_int());
        fl_pie(point(0).x + radius()/2, point(0).y+radius()/2,
               radius()*2, radius()*2, 0, 360);
    }
    if(color().visibility()){
        fl_color(color().as_int());
        // drawing line
        fl_line(point(0).x-radius(),point(0).y+radius(),point(0).x+3*radius(),point(0).y+radius());
        // drawing arc
        //fl_arc(point(0).x , point(0).y,
        //       radius()*6, radius()*6 , 0, 360);
    }
}


void Frowny::draw_lines() const
{
    Circle::draw_lines();
    if(fill_color().visibility()){
        // drawing fill eyes
        fl_color(fill_color().as_int());
        fl_pie(point(0).x + radius()/2, point(0).y + radius()/2,
                radius()/2, radius()/2, 0, 360);

        fl_pie(point(0).x + radius()/2, point(0).y + radius()/2,
                radius()/2, radius()/2, 0, 360);
        // drawing fill mouth
        fl_pie(point(0).x, point(0).y + radius()/2,
                radius()/2, radius()/2, 0, 180);
        fl_color(color().as_int()); // reset color
    }

    if(color().visibility()){
        // drawing  eyes
        fl_color(color().as_int());
        fl_arc(point(0).x + 2*radius()/8, point(0).y + 3*radius()/8,
               radius()/2, radius()/2, 0, 360);

        fl_arc(point(0).x + radius()+2*radius()/8, point(0).y + 3*radius()/8,
               radius()/2, radius()/2, 0, 360);
        // drawing mouth
        fl_arc(point(0).x + radius()-radius()/4, point(0).y + radius(),
               radius()/2, radius()/2, 0, 180);

    }
}

 void Frowny_hat::draw_lines()  const
 {
     Frowny::draw_lines();
 }

//------------------------------------------------------------------------------

void Striped_rectangle::draw_lines() const
{
    static int start{};
    if(fill_color().visibility()){
        fl_color(fill_color().as_int());
        if (start) {
            for (int h = 1; h < height(); h++) {
                fl_line(point(0).x + 1, point(0).y + h, point(0).x + width() - 1, point(0).y + h);
            }
        }
        else {
            for (int h = 1; h < height(); h++) {
                fl_line(point(0).x + 1, point(0).y + h, point(0).x + width() - 1, point(0).y + h);
                Sleep(10);      // [miliseconds]
            }
            start = 1;
        }
        fl_color(color().as_int());
    }

    if(color().visibility())
    {
        fl_color(color().as_int());
        fl_rect(point(0).x, point(0).y, width(), height());
    }
    
}

// drawing in x-direction, horizontal
//
void Striped_circle::draw_lines() const
{
    static int start{};
    if(fill_color().visibility()){
        fl_color(fill_color().as_int());
        if (start) {
            // for fill and not fill line dify+=2
            for (int dify = -radius(); dify < radius(); dify++) {
                // (x-x0)^2 + (y-y0)^2 = r^2 - circle on x,y, x0, y0 == 0
                int difx = round(sqrt(radius() * radius() - dify * dify)) - 1;
                fl_line(center().x - difx, center().y + dify, center().x + difx, center().y + dify);
            }
        }
        else {            
            for (int dify = -radius(); dify < radius(); dify++) {
                int difx = round(sqrt(radius() * radius() - dify * dify)) - 1;
                fl_line(center().x - difx, center().y + dify, center().x + difx, center().y + dify);
                Sleep(10); // [miliseconds]
            }
            start = 1;
        }
        
        fl_color(color().as_int());
    }

    if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,2*radius(),2*radius(),0,360);
	}
}

void Striped_closed_polyline::draw_lines() const
{
    if(fill_color().as_int()){
        fl_color(fill_color().as_int());
        int x_min = point(0).x;
        int x_max = point(0).x;
        int y_min = point(0).y;
        int y_max = point(0).y;
        static int start{};
        //static int change{};
        for(int n = 0; n<number_of_points(); n++){
            if(x_min>point(n).x) x_min = point(n).x;
            if(x_max<point(n).x) x_max = point(n).x;
            if(y_min>point(n).y) y_min = point(n).y;
            if(y_max<point(n).y) y_max = point(n).y;
        }
        std::cout << x_min << ' ' << x_max << ' '
                  << y_min << ' ' << y_max << '\n';
        x_min-=10;
        x_max+=10;

        for(int y = y_min; y<y_max; y+=2){
            Point intersection;
            std::vector<Point> inters_vect;
            for(int n=1; n<number_of_points(); n++){
                if(line_segment_intersect(Point(x_min, y), Point(x_max, y), point(n), point(n-1), intersection))
                    inters_vect.push_back(intersection);
            }

            if(line_segment_intersect(Point(x_min, y), Point(x_max, y), point(number_of_points()-1),point(0), intersection))
                inters_vect.push_back(intersection);

            //
                //sort()
            if (start) {
                for (int i = 1; i < inters_vect.size(); i++) {
                        fl_line(inters_vect[i - 1].x, inters_vect[i - 1].y, inters_vect[i].x, inters_vect[i].y);
                }
            }
            else {
                for (int i = 1; i < inters_vect.size(); i++) {
                    fl_line(inters_vect[i - 1].x, inters_vect[i - 1].y, inters_vect[i].x, inters_vect[i].y);
                    Sleep(20);
                }
            }

        }
        //std::cout << "par" << par << " intersection: " <<
        start = { 1 };
        fl_color(color().as_int());
    }
    if (color().visibility()) {
        Shape::draw_lines();
        // draw closing line
        fl_line(point(number_of_points()-1).x,
             point(number_of_points()-1).y,
             point(0).x,
             point(0).y);
    }
}

//------------------------------------------------------------------------------
//
/*
	void Group::move(int dx, int dy){
	    for(int i = 0; i<size(); i++)
            shape_v[i]->move(dx,dy);
    }

    void Group::draw() const
    {
        for(int i = 0; i<size(); i++)
            shape_v[i]->draw();
    }

    void Group::set_color(Color col)
    {
        for(int i = 0; i<size(); i++)
            shape_v[i]->set_color(col);
    }


	void Group::set_style(Line_style sty)
	{
	    for(int i = 0; i<size(); i++)
            shape_v[i]->set_style(sty);
	}


	void Group::set_fill_color(Color col)
	{
	    for(int i = 0; i<size(); i++)
            shape_v[i]->set_fill_color(col);
	}
	*/
 ///*
 	void Group::move(int dx, int dy){
	    for(int i = 0; i<size(); i++)
            shape_v[i].move(dx,dy);
    }

 /*   void Group::draw() const
    {
        for(int i = 0; i<size(); i++)
            shape_v[i].draw();
    }
    */
    void Group::set_color(Color col)
    {
        for(int i = 0; i<size(); i++)
            shape_v[i].set_color(col);
    }


	void Group::set_style(Line_style sty)
	{
	    for(int i = 0; i<size(); i++)
            shape_v[i].set_style(sty);
	}


	void Group::set_fill_color(Color col)
	{
	    for(int i = 0; i<size(); i++)
            shape_v[i].set_fill_color(col);
	}


    void Group::draw_lines() const
    {
        for (int i = 0; i < size(); i++)
            shape_v[i].draw();
    }
 //---------------------------------------------------------------------------------
    Tiles::Tiles(Point p1, Point p2, int slq)
    {
        add(p1); // North-West point
        add(p2); // South-east point

        for (int dy = 0, oddy = 0; dy < point(1).y-point(0).y; dy += slq)
        {
            for (int dx = 0, oddx = oddy; dx < point(1).x -point(0).x; dx += slq) {
                (*this).add_Shape(new Graph_lib::Rectangle(Graph_lib::Point(point(0).x + dx, point(0).y + dy), slq, slq));
                if (oddx % 2)
                    (*this)[(*this).size() - 1].set_fill_color(Graph_lib::Color::blue);
                else
                    (*this)[(*this).size() - 1].set_fill_color(Graph_lib::Color::black);
                ++oddx;
            }
            ++oddy;
        }
    }

    void Tiles::change_color_squares(Fl_Color firstc, Fl_Color secondc)
    {
        
        for (int s = 0, oddy = 0, oddx = 0; s < (*this).size(); s++) {
            if (oddx % 2)
                (*this)[s].set_fill_color(firstc);
            else
                (*this)[s].set_fill_color(secondc);
            ++oddx;
            if ((*this).size() > s + 1 && (*this)[s + 1].point(0).y != (*this)[s].point(0).y) {
                ++oddy;
                oddx = oddy;
            }

        }
    }

 //---------------------------------------------------------------------------------
Binary_tree::Binary_tree(int levels, int size, Point pnorthwest)
    : lvls(levels), shape_size{ size }
{
    add(pnorthwest);
    pbottom_lvl.y = point(0).y + 0.5 * shape_size;
    int shape_count = pow(2, lvls-1); // size for the c 
    while (shape_count >c.size())
    {
        add_lvl();
    }
    //print_pmid_psoutheast();// points mid, southeast
 }


void Binary_tree::add_lvl()
{
    int c_count_bottom_lvl = pow(2, bottom_lvl); // how many circles at the bottom lvl, // (2^n)/2
    pbottom_lvl.x = point(0).x + shape_size * (pow(2, lvls - 1 - bottom_lvl) - 1) + 0.5 * shape_size;
    int csize = c.size();
    int dxc = 0;
    // add circles
    for (int count = 0; count < c_count_bottom_lvl; count++) {
        c.add_Shape(new Graph_lib::Circle(Point(pbottom_lvl.x + dxc, pbottom_lvl.y), shape_size / 2));
        c.set_color(Graph_lib::Color::blue);
        dxc += shape_size* pow(2, lvls  - bottom_lvl);
    }
    
    int dxt = shape_size * 0.25; // difference for text in x
    int dyt = shape_size * 0.6;   // difference for text in y
    if (csize > 0) {
        // add arrows
        int pnodes = c_count_bottom_lvl / 2; // how many parent nodes
       // std::cout << "nodes: " << pnodes << '\n';
        for (int count = 0, node = 0; count < c_count_bottom_lvl && node < pnodes; count++) {
            a.add_Shape(new Graph_lib::Arrow(s((const Circle&)c[csize - pnodes + node]), n((const Circle&)c[count + csize])));
            a.set_color(Graph_lib::Color::blue);
            if (count % 2)
                node++;
        }
        
        // add Text
        std::string ct = "l"; // text
        for (int count = 0, node = 0; count < c_count_bottom_lvl && node < pnodes; count++) {
            gtext.add_Shape(new Graph_lib::Text(Point(((const Circle&)c[csize + count]).point(0).x + dxt, ((const Circle&)c[csize + count]).point(0).y + dyt), ((const Text&)gtext[csize - pnodes+node]).label() + ct));
            gtext.set_color(Graph_lib::Color::blue);
            if (count % 2)
                ct = "l";
            else
                ct = "r";
            if (count % 2)
                node++;
        }
    } 
    else {
        gtext.add_Shape(new Graph_lib::Text(Point(((const Circle&)c[0]).point(0).x+dxt, ((const Circle&)c[0]).point(0).y+dyt), std::string("rl")));
        gtext.set_color(Graph_lib::Color::blue);
    }
    // update variables values
    bottom_lvl++;
    pbottom_lvl.y += 2*shape_size;
}

void Binary_tree::print_pmid_psoutheast() const
{
    int shape_count = pow(2, lvls - 1);
    Point psoutheast(0, 0);
    int last_lvl = lvls - 1;
    int differencex = shape_size * pow(2, lvls - (last_lvl));
    int differencey = 2 * shape_size; // const 
    psoutheast.x = differencex * (shape_count)+point(0).x - shape_size;
    psoutheast.y = differencey * (lvls - 1) + point(0).y + shape_size;  
    int xmid = (psoutheast.x - point(0).x) / 2 + point(0).x;
    int ymid = (psoutheast.y - point(0).y) / 2 + point(0).y;
    std::cout << "southeast x:" << psoutheast.x << "y:" << psoutheast.y << '\n';
    std::cout << "northwest x:" <<point(0).x << "y:" << point(0).y << '\n';
    // Graphic visual for the points, if you need it, remove const from function declaration
    //a.add_Shape(new Graph_lib::Mark(point(0), 'x'));
    //a.add_Shape(new Graph_lib::Mark(psoutheast, 'x'));
   
}


void Binary_tree::add_arrows(int s)
{}

void Binary_tree::ccentre(int lvl, int pixels)
{
    int c_count_move = pow(2, lvl - 1);


}

void Binary_tree::draw_lines() const
{
    for (int i = 0; i < a.size(); i++)
        a[i].draw();
    for (int i = 0; i < c.size(); i++)
        c[i].draw();
    for (int i = 0; i < gtext.size(); i++)
        gtext[i].draw();

}

//----------------------------------------------------------------------------------

Binary_tree_triangle::Binary_tree_triangle(int levels, int size, Point pnorthwest)
    : Binary_tree(size, pnorthwest)
{
    lvls = {levels };
    int shape_count = pow(2, lvls) - 1;
    add(pnorthwest);
    pbottom_lvl.y = point(0).y + shape_size;
    while (shape_count > c.size())
    {
        add_lvl();
    }
}


void Binary_tree_triangle::add_lvl()
{
    int c_count_bottom_lvl = pow(2, bottom_lvl); // how many triangles at the bottom lvl // (2^n)/2
    int ang_bac = 30;
    double theta = ang_bac * PI / 180;
    pbottom_lvl.x = point(0).x + shape_size * (pow(2, lvls - 1 - bottom_lvl) - 1) +(shape_size/cos(theta)); // it's aproximation
    int csize = c.size();
    int dxc = 0;
    // add circles
    for (int count = 0; count < c_count_bottom_lvl; count++) {
        // THere is need to correct shape_size value for Regular_polygon(...dis_center!=shape_size,...)
        c.add_Shape(new Graph_lib::Regular_polygon(Point(pbottom_lvl.x + dxc, pbottom_lvl.y), shape_size, 3, ang_bac));
        c.set_color(Graph_lib::Color::blue);
        dxc += shape_size * pow(2, lvls - bottom_lvl);
    }

    int dxt = shape_size * -1.2; // difference for text in x
    int dyt = shape_size * -0.5;   // difference for text in y
    // add arrows
    if (csize > 0) {

        int pnodes = c_count_bottom_lvl / 2; // how many parent nodes
       // std::cout << "nodes: " << pnodes << '\n';
        /*
        for (int count = 0, node = 0; count < c_count_bottom_lvl && node < pnodes; count++) {
            a.add_Shape(new Graph_lib::Arrow((const Right_triangle&)c[csize - pnodes + node])->point[], (const Right_triangle&)c[count + csize])));
            a.set_color(Graph_lib::Color::blue);
            if (count % 2)
                node++;
        }
*/
                // add Text
        std::string ct = "l"; // text
        for (int count = 0, node = 0; count < c_count_bottom_lvl && node < pnodes; count++) {
            gtext.add_Shape(new Graph_lib::Text(Point(((const Circle&)c[csize + count]).point(0).x + dxt, ((const Circle&)c[csize + count]).point(0).y + dyt), ((const Text&)gtext[csize - pnodes+node]).label() + ct));
            gtext.set_color(Graph_lib::Color::blue);
            if (count % 2)
                ct = "l";
            else
                ct = "r";
            if (count % 2)
                node++;
        }
  
    }
    else {
        gtext.add_Shape(new Graph_lib::Text(Point(((const Circle&)c[0]).point(0).x + dxt, ((const Circle&)c[0]).point(0).y + dyt), std::string("rl")));
        gtext.set_color(Graph_lib::Color::blue);
    }
    
    // update variables to default values for the next add_lvl
    bottom_lvl++;
    pbottom_lvl.y += shape_size*2;
}

void Binary_tree_triangle::ccentre(int lvl, int pixels)
{
    int c_count_move = pow(2, lvl - 1);

}


void Binary_tree_triangle::draw_lines() const
{
    /*
    for (int i = 0; i < a.size(); i++)
        a[i].draw();
    */
    //  draw triangles 
    for (int i = 0; i < c.size(); i++)
        c[i].draw();

    // draw text
    for (int i = 0; i < c.size(); i++)
        gtext[i].draw();

}

//---------------------------------------------------------------------------------
void S_Controller::show() const { 
    std::cout << "Controller show():\n"
        << "set on: " << state << '\n'
        << "level :" << lvl << '\n';
};

void test_Controller_Status::show() const
{
    std::cout << "test_Controller Status show()" << '\n'
        << "set on: " << state << '\n'
        << "level :" << lvl << '\n';
   
}
void Controller_Status::show()
{
    std::cout << "Controller Status show() is calling to Controller::show()\n";
    c.show();
}

//-------------------------

void Shape_Controller::on()
{
    shape_p->set_color(Color::visible);
    shape_p->set_fill_color(Color::visible);
}

void Shape_Controller::off()
{
    shape_p->set_color(Color::invisible);
    shape_p->set_fill_color(Color::invisible);
}

void Shape_Controller::set_level(int level)
{
    //if (474 > level) shp->set_color(fl_color_cube(level / 100, level / 10, level % 10));
    if(256>level)
        shape_p->set_color(level);
}

void Shape_Controller::set_fill_level(int level)
{
    if (256 > level) shape_p->set_fill_color(level);
}


void Shape_Controller::show() const 
{
    std::cout << "Shape_Controller is set: " << (( Color::visible == shape_p->color().visibility())? "on":"off") << '\n'
    << "Color as int: " << shape_p->color().as_int() << '\n'
    << "Fill color as int: " << shape_p->fill_color().as_int() << '\n';
}

//---------------------------------------------------------------------------------

//Function::Function()
//{
//    for (int i = -70; i < 70; i++) {
//        add(Graph_lib::Point(i + 200, parabola(i) + 100));
//    }
//}
//
//Function::Function(Fct f)
//{
//    for (int i = -70; i < width_window / 6; i++) {
//        add(Graph_lib::Point(i + 300, f(i) + 100));
//    }
//}
//
//Function::Function(Fct f, double r_min, double r_max, Graph_lib::Point xy,
//    int count, double xscale, double yscale)
//{
//    double dis = (r_max - r_min) / count;
//    double r = r_min;
//    for (int i = 0; i < count; i++) {
//        add(Graph_lib::Point(xy.x + xscale * r, xy.y + yscale * f(r)));
//        r += dis;
//    }
//
//}
//void Function::draw_lines() const
//{
//    if (color().visibility())
//        Shape::draw_lines();
//}



    double exPower(double x, int n)
    {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += term(x, n);
        }
        return sum;
    }


} // Graph
