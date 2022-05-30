
#ifndef GRAPH_GUARD
#define GRAPH_GUARD 


//#include<vector>
//#include<string>
//#include<cmath>

#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include <std_lib_facilities.h>
#include <Point.h>

namespace Graph_lib {
// defense against ill-behaved Linux macros:
#undef major
#undef minor

    const static double PI = 3.14159265;

//------------------------------------------------------------------------------

struct Color {
	enum Color_type {
		red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
		yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
		magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
		dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
		dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
	};
	enum Transparency { invisible = 0, visible=255 };

	Color(Color_type cc) :c(Fl_Color(cc)), v(visible) { }
	Color(Color_type cc, Transparency vv) :c(Fl_Color(cc)), v(vv) { }
	Color(int cc) :c(Fl_Color(cc)), v(visible) { }
	Color(Transparency vv) :c(Fl_Color()), v(vv) { }

	int as_int() const { return c; }
	char visibility() const { return v; }
	void set_visibility(Transparency vv) { v=vv; }
private:
	unsigned char v;	// 0 or 1 for now
	Fl_Color c;
};

//------------------------------------------------------------------------------

struct Line_style {
	enum Line_style_type {
		solid=FL_SOLID,				// -------
		dash=FL_DASH,				// - - - -
		dot=FL_DOT,					// .......
		dashdot=FL_DASHDOT,			// - . - .
		dashdotdot=FL_DASHDOTDOT,	// -..-..
	};
	Line_style(Line_style_type ss) :s(ss), w(0) { }
	Line_style(Line_style_type lst, int ww) :s(lst), w(ww) { }
	Line_style(int ss) :s(ss), w(0) { }

	int width() const { return w; }
	int style() const { return s; }
private:
	int s;
	int w;
};

//------------------------------------------------------------------------------

class Font {
public:
	enum Font_type {
		helvetica=FL_HELVETICA,
		helvetica_bold=FL_HELVETICA_BOLD,
		helvetica_italic=FL_HELVETICA_ITALIC,
		helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
		courier=FL_COURIER,
  		courier_bold=FL_COURIER_BOLD,
  		courier_italic=FL_COURIER_ITALIC,
  		courier_bold_italic=FL_COURIER_BOLD_ITALIC,
		times=FL_TIMES,
		times_bold=FL_TIMES_BOLD,
		times_italic=FL_TIMES_ITALIC,
		times_bold_italic=FL_TIMES_BOLD_ITALIC,
		symbol=FL_SYMBOL,
		screen=FL_SCREEN,
		screen_bold=FL_SCREEN_BOLD,
		zapf_dingbats=FL_ZAPF_DINGBATS
	};

	Font(Font_type ff) :f(ff) { }
	Font(int ff) :f(ff) { }

	int as_int() const { return f; }
private:
	int f;
};

//------------------------------------------------------------------------------

template<class T> class Vector_ref {

	std::vector<T*> v;
	std::vector<T*> owned;
public:
	Vector_ref() {}

	Vector_ref(T* a, T* b=0, T* c=0, T* d=0)
	{
			if (a) push_back(a);
			if (b) push_back(b);
			if (c) push_back(c);
			if (d) push_back(d);
	}

	~Vector_ref() { for (int i=0; i<owned.size(); ++i) delete owned[i]; }

	void push_back(T& s) { v.push_back(&s); }
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	// ???void erase(???)

	T& operator[](int i) { return *v[i]; }
	const T& operator[](int i) const { return *v[i]; }
	int size() const { return v.size(); }
};

//------------------------------------------------------------------------------

typedef double Fct(double);

class Shape  {	// deals with color and style, and holds sequence of lines
protected:
	Shape() { };
	Shape(std::initializer_list<Point> lst);  // add() the Points to this Shape

//	Shape() : lcolor(fl_color()),
//		ls(0),
//		fcolor(Color::invisible) { }

	void add(Point p){ points.push_back(p); }
	void set_point(int i, Point p) { points[i] = p; }
public:
	void draw() const;					// deal with color and draw_lines
protected:
	virtual void draw_lines() const;	// simply draw the appropriate lines
public:
	virtual void move(int dx, int dy);	// move the shape +=dx and +=dy

	void set_color(Color col) { lcolor = col; }
	Color color() const { return lcolor; }

	void set_style(Line_style sty) { ls = sty; }
	Line_style style() const { return ls; }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() const { return fcolor; }

	Point point(int i) const { return points[i]; }
	int number_of_points() const { return int(points.size()); }

	virtual ~Shape() { }
	/*
	struct Window* attached;
	Shape(const Sh ape& a)
		:attached(a.attached), points(a.points), line_color(a.line_color), ls(a.ls)
	{
		if (a.attached)error("attempt to copy attached shape");
	}
	*/
	//Shape(const Shape&) = delete;
	//Shape& operator=(const Shape&) = delete;
private:
	vector<Point> points;	// not used by all shapes
	Color lcolor {fl_color()};
	Line_style ls {0};
	Color fcolor {Color::invisible};

//	Shape(const Shape&);
//	Shape& operator=(const Shape&);
};

//------------------------------------------------------------------------------

struct Function : Shape {
	// the function parameters are not stored
	Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
	//Function(Point orig, Fct f, double r1, double r2, int count, double xscale = 1, double yscale = 1);
};

//------------------------------------------------------------------------------

struct Fill {
	Fill() :no_fill(true), fcolor(0) { }
	Fill(Color c) :no_fill(false), fcolor(c) { }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() { return fcolor; }
protected:
	bool no_fill;
	Color fcolor;
};

//------------------------------------------------------------------------------

struct Line : Shape {
	Line(Point p1, Point p2) { add(p1); add(p2); }
};

//------------------------------------------------------------------------------

struct Arrow : Line {
    Arrow(Point p, Point p1) : Line(p, p1) {}
    virtual void draw_lines() const;
};

//----------------------------------------------------

struct Rectangle : Shape {

	Rectangle(Point xy, int ww, int hh) :w{ ww }, h{ hh }
	{
		if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
		add(xy);
	}
	Rectangle(Point x, Point y) :w{ y.x - x.x }, h{ y.y - x.y }
	{
		if (h<=0 || w<=0) error("Bad rectangle: first point is not top left");
		add(x);
	}
	virtual void draw_lines() const  override;

//	void set_fill_color(Color col) { fcolor = col; }
//	Color fill_color() { return fcolor; }

	int height() const { return h; }
	int width() const { return w; }
private:
	int h;			// height
	int w;			// width
//	Color fcolor;	// fill color; 0 means "no fill"
};

//-------------------------------------------

Point n(const Rectangle & r);
Point s(const Rectangle & r);
Point e(const Rectangle & r);
Point w(const Rectangle & r);
Point center(const Rectangle & r);
Point ne(const Rectangle & r);
Point se(const Rectangle & r);
Point sw(const Rectangle & r);
Point nw(const Rectangle & r);

//------------------------------------------------------------------------------

bool intersect(Point p1, Point p2, Point p3, Point p4);

struct Open_polyline : Shape {	// open sequence of lines
	using Shape::Shape; // use Shape's constructors
	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
};

//------------------------------------------------------------------------------

struct Closed_polyline : Open_polyline {	// closed sequence of lines
	using Open_polyline::Open_polyline;
	void draw_lines() const;

//	void add(Point p) { Shape::add(p); }
};

//------------------------------------------------------------------------------

struct Polygon : Closed_polyline {	// closed sequence of non-intersecting lines
	using Closed_polyline::Closed_polyline;
	void add(Point p);
	void draw_lines() const;
};

//------------------------------------------------------------------------------

struct Regular_hexagon : Polygon
{
    Regular_hexagon(Point p, int dis_center, double theta = 0.0);

    //virtual void draw_lines() const;
    Point center(){return c;}
private:
    Point c;
    int r;
    double t;
};

//------------------------------------

struct Regular_polygon : Polygon
{
    Regular_polygon(Point p, int dis_center, int sides, double theta = 0.0);

    //virtual void draw_lines() const;
    Point center(){return c;}
private:
    Point c;
    int r;
    int s;
    double t;
};

//------------------------------------

struct Right_triangle : public Shape
{
    Right_triangle(Point a, Point b, double theta_bac = 30.0);
    //Right_triangle(Point a, Point b, double height_triangle);


    virtual void draw_lines() const;
    //Point center(){return c;}
private:
    //Point a;
    //Point b;
    double ang_bac;
    //Point c;
};

//------------------------------------
struct Lines : Shape {	// indepentdent lines
	Lines() {}
	Lines(initializer_list<Point> lst) : Shape{lst}
	{ if (lst.size() % 2) error("odd number of points for Lines"); }
	void draw_lines() const;
	void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
};

//------------------------------------------------------------------------------

struct Text : Shape {
	// the point is the bottom left of the first letter
	Text(Point x, const string& s) : lab{ s } { add(x); }

	void draw_lines() const;

	void set_label(const string& s) { lab = s; }
	string label() const { return lab; }

	void set_font(Font f) { fnt = f; }
	Font font() const { return Font(fnt); }

	void set_font_size(int s) { fnt_sz = s; }
	int font_size() const { return fnt_sz; }
private:
	string lab;	// label
	Font fnt{ fl_font() };
	int fnt_sz{ (14<fl_size()) ? fl_size() : 14 };	// at least 14 point
};

//------------------------------------------------------------------------------
//
// use of class Arc
// Arc(Point p, int width, int height, double start, double end);
// the bounding box of ellipse is rectangle with a Point and width x height
// The Point is a top left corner of rectangle.
// start and end are angles
// Angles are measured from 3 o'clock counter-clockwise

struct Arc : Shape
{
    Arc(Point p, int w, int h, int b_ang, int e_ang);

    Point center() const {return Point(point(0).x+w/2, point(0).y+h/2);}
    int angle_beg()const {return ang.first;};
    int angle_end()const {return ang.second;};
    int major()const {return w;};
    void set_major(int width_axis){ w=width_axis;}
    int minor()const {return h;};
    void set_minor(int height_axis) {h=height_axis;}

    void set_angles(double a1, double a2)
    {
        if(a1>a2) error("First angle cannot be bigger than second angle. Arc::set_angles");
        ang.first=a1;
        ang.second=a2;
    }

    void set_angle_first(double a1)
    {
        if(a1>ang.second) error("First angle cannot be bigger than second angle. Arc::set_angle_first");
        ang.first=a1;
    }
    void set_angle_second(double a2)
    {
        if(ang.first>a2) error("First angle cannot be bigger than second angle. Arc::set_angle_second");
        ang.second = a2;

    }

protected:
    virtual void draw_lines() const;
private:
    // rectangle
    int w;
    int h;
    std::pair<int, int> ang; // angles

};


//-------------------------------------------
 /*
Point n(const Arc & ar);
Point s(const Arc & ar);
Point e(const Arc & ar);
Point w(const Arc & ar);
Point center(const Arc & ar);
Point ne(const Arc & ar);
Point se(const Arc & ar);
Point sw(const Arc & ar);
Point nw(const Arc & ar);
*/
//-------------------------------------------

struct Box : Shape
{
public:
    Box(Point p, int width, int height, int radius);
    Box(Point p, int width, int height);

protected:
    virtual void draw_lines() const;

public:
    int r;
    int w;
    int h;

};

//-------------------------------------------

Point n(const Box & b);
Point s(const Box & b);
Point e(const Box & b);
Point w(const Box & b);
Point center(const Box & b);
Point ne(const Box & b);
Point se(const Box & b);
Point sw(const Box & b);
Point nw(const Box & b);

//-------------------------------------------

struct Text_Box : public Text
{
    Text_Box(Point p, int width, int height, int radius, const std::string s);
    Text_Box(Point p, int width, const std::string s);
protected:
    virtual void draw_lines() const;

public:
    Box b;
    virtual void move(int dx, int dy);

private :
    static const  int h_tb = 26;


};

//-------------------------------------------
struct Axis : Shape {
	// representation left public
	enum Orientation { x, y, z };
	Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");

	void draw_lines() const;
	void move(int dx, int dy);

	void set_color(Color c);

	Text label;
	Lines notches;
//	Orientation orin;
//	int notches;
};

//------------------------------------------------------------------------------

struct Circle : Shape {
	Circle(Point p, int rr)	// center and radius
	:r{ rr } {
		add(Point{ p.x - r, p.y - r });
	}

	void draw_lines() const;

	Point center() const { return { point(0).x + r, point(0).y + r }; }

	void set_radius(int rr) { r=rr; }
	int radius() const { return r; }
private:
	int r;
};

//-------------------------------------------
Point give_point(const Circle & c, double angle_rad);
Point n(const Circle & c);
Point s(const Circle & c);
Point e(const Circle & c);
Point w(const Circle & c);
Point center(const Circle & c);
Point ne(const Circle & c);
Point se(const Circle & c);
Point sw(const Circle & c);
Point nw(const Circle & c);


//------------------------------------------------------------------------------

struct Ellipse : Shape {
	Ellipse(Point p, int ww, int hh)	// center, min, and max distance from center
	:w{ ww }, h{ hh } {
		add(Point{ p.x - ww, p.y - hh });
	}

	void draw_lines() const;

	Point center() const { return{ point(0).x + w, point(0).y + h }; }
	Point focus1() const { return{ center().x + int(sqrt(double(w*w - h*h))), center().y }; }
	Point focus2() const { return{ center().x - int(sqrt(double(w*w - h*h))), center().y }; }

	void set_major(int ww) { w=ww; }
	int major() const { return w; }
	void set_minor(int hh) { h=hh; }
	int minor() const { return h; }
private:
	int w;
	int h;
};

//-------------------------------------------

Point give_point(const Ellipse & e, double angle);
Point n(const Ellipse & e);
Point s(const Ellipse & e);
Point e(const Ellipse & e);
Point w(const Ellipse & e);
Point center(const Ellipse & e);
Point ne(const Ellipse & e);
Point se(const Ellipse & e);
Point sw(const Ellipse & e);
Point nw(const Ellipse & e);

//-------------------------------------------
/*
struct Mark : Text {
	static const int dw = 4;
	static const int dh = 4;
	Mark(Point xy, char c) : Text(Point(xy.x-dw, xy.y+dh),string(1,c)) {}
};
*/

//------------------------------------------------------------------------------

struct Marked_polyline : Open_polyline {
	Marked_polyline(const string& m) :mark(m) { }
	void draw_lines() const;
private:
	string mark;
};

//------------------------------------------------------------------------------

struct Marks : Marked_polyline {
	Marks(const string& m) :Marked_polyline(m)
	{ set_color(Color(Color::invisible)); }
};

//------------------------------------------------------------------------------

struct Mark : Marks {
	Mark(Point xy, char c) : Marks(string(1,c)) {add(xy); }
};

/*

struct Marks : Shape {
	Marks(char m) : mark(string(1,m)) { }
	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
private:
	string mark;
};
*/

//------------------------------------------------------------------------------

struct Bad_image : Fl_Image {
	Bad_image(int h, int w) : Fl_Image(h,w,0) { }
	void draw(int x,int y, int, int, int, int) { draw_empty(x,y); }
};

//------------------------------------------------------------------------------

struct Suffix {
	enum Encoding { none, jpg, gif, bmp };
};

//------------------------------------------------------------------------------

Suffix::Encoding get_encoding(const string& s);

struct Image : Shape {
	Image(Point xy,  string s, Suffix::Encoding e = Suffix::none);
	~Image() { delete p; }
	void draw_lines() const;
	void set_mask(Point xy, int ww, int hh) { w=ww; h=hh; cx=xy.x; cy=xy.y; }
	void move(int dx,int dy) { Shape::move(dx,dy); p->draw(point(0).x,point(0).y); }
private:
	int w,h,cx,cy; // define "masking box" within image relative to position (cx,cy)
	Fl_Image* p;
	Text fn;
};

//------------------------------------------------------------------------------
// chapeter 14
class Smiley : public Circle
{
public:
     Smiley() = delete;
     Smiley(Point p, int rr)// center and radius
     : Circle(p, rr)
     {}
protected:
     void draw_lines() const override;
};

class Frowny : public Circle
{
public:
    Frowny() = delete;
    Frowny(Point p, int rr)// center and radius
    :  Circle(p, rr)
    {}
protected:
    void draw_lines() const override;

};

class  Smiley_hat: public Smiley
{
public:
    Smiley_hat(Point p, int width)
    :   Smiley(p, width)
        //Arc(p,width,2*width,0,180), Smiley(Point{p.x+width/2-width/8, p.y+width/8}, width)
    {}
private:

     void draw_lines() const override;
};

class  Frowny_hat: public Frowny
{
public:

    void draw_lines() const override;

};

class Immobile_Circle : public Circle
{
    using Circle::Circle;
protected:
   //void move(int dx, int dy) {Circle::move(dx, dy);};
   using Circle::move;

};

class  Striped_rectangle : public Rectangle
{
public:
    using  Rectangle::Rectangle;
    void draw_lines() const override;
};

class Striped_circle : public Circle
{
    using Circle::Circle;
    void draw_lines() const override;
};

class Striped_closed_polyline : public Closed_polyline
{
    using Closed_polyline::Closed_polyline;
    void draw_lines() const override;
};

struct Octagon : public Regular_polygon
{
    Octagon(Point p, int dis_center, double theta)
    : Regular_polygon(p, dis_center, 8, theta)
    {}

protected:
    //void add(Point p){ Regular_polygon::add(p); }
    using Regular_polygon::add;
};

struct Group : public Shape
{

public:
//    Group(){};
    void add_Shape(Shape* s){ shape_v.push_back(s); }
	//void draw() const;					// deal with color and draw_lines
	virtual void move(int dx, int dy);// override;	// move the shape +=dx and +=dy

	void set_color(Color col);

    void set_style(Line_style sty);

	void set_fill_color(Color col);

    int size() const { return shape_v.size(); };
	Shape& operator[](int n) {
		if (shape_v.size() > n) return shape_v[n];
		throw std::runtime_error("shape_v[n] - Group::size() < n");
	}
    const  Shape& operator[](int n) const  { 
		if (shape_v.size() > n)return shape_v[n]; 
		throw std::runtime_error("shape_v[n] - Group::size() < n");
	}
    virtual ~Group() {}
private:
    Vector_ref<Shape> shape_v;
   //using Shape::point;
  // using Shape::number_of_points;
   //using Shape::set_point;
   virtual void draw_lines() const;
};


class Binary_tree :public Shape
{
protected:
	int lvls;
	
	Point pbottom_lvl{ 300, 50 };
	int shape_size; // [pixels]	
	const int dx =2 * shape_size;
	const int dy = 2 * shape_size;
	int c_count_bottom_lvl=0; // how many circles in lvl, // (2^n)/2
	int bottom_lvl=0; 
private:
	// centre circles from lvl to root 
	void ccentre(int lvl, int pixels);
	void add_arrows(int s);
public:
	Group c; // node shape: circle
	Group a; // arrows
	Binary_tree(int size = 20, Point pnorthwest = Point(300, 50)) : lvls(0), shape_size(size) { add(pnorthwest); };
	Binary_tree(int levels, int size, Point pnorthwest = Point(300, 50));
	virtual void add_lvl_left();  // to change or remove
	virtual void add_lvl_center(); // to change or remove
	virtual void add_lvl(); // change to  reccursion function
	

	virtual void draw_lines() const override;

};




class Binary_tree_triangle : public Binary_tree
{
private:
	// centre circles from lvl to root 
	void ccentre(int lvl, int pixels);
public:
	Binary_tree_triangle(int size=20):Binary_tree(0,size) {};
	Binary_tree_triangle(int levels, int size=20);
	virtual void add_lvl_left();
	virtual void add_lvl_center();
	virtual void add_lvl();


	virtual void draw_lines() const override;

};


}
#endif

