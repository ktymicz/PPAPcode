#include <iostream>
#include <vector>
#include <math.h>
#include <functional>
#include <algorithm>
#include "Simple_window.h"
#include "Graph.h"

// constants
constexpr int width_window = 800;//1920/2;
constexpr int height_window = 800;///1080/2;

Graph_lib::Point find_point_window(const Graph_lib::Function& s, const Graph_lib::Point& up);

int chapter_15_drill_ex()
try
{
	constexpr  int x_org = width_window / 2;
	constexpr  int y_org = height_window / 2;
	constexpr int dif_g = 100; // make axis smaller in graph
	constexpr  int x_length = width_window - dif_g;
	constexpr  int y_length = height_window - dif_g;
	constexpr int xscale = 25;
	constexpr int yscale = 25;

	const Graph_lib::Point orig{ x_org, y_org };

	constexpr int len = 10; // length of the graph
	//const int len = 100; // length of the graph

	Graph_lib::Simple_window win(orig, width_window, height_window, "Chapter 15");

	
	// parabola x*x
	Graph_lib::Function pal(Graph_lib::parabola, -10, 11, orig, 100, xscale, yscale);
	pal.set_color(fl_color_cube(0, 7, 4));
	win.attach(pal);
	Graph_lib::Point ppal;
	ppal.x = pal.point(0).x - xscale / 2;
	ppal.y = pal.point(0).y - yscale / 2;
	std::cout << "pal x:" << pal.point(0).x << " "
			 << "pal y:" << pal.point(0).y << '\n';
	
	ppal = find_point_window(pal, Graph_lib::Point(50, 50));
	std::cout << "new ppal x:" << ppal.x << " "
		<< "ppal y:" << ppal.y << '\n';
	
	Graph_lib::Text tpal(ppal, "x*x");
	tpal.set_color(fl_color_cube(0, 7, 4));
	win.attach(tpal);

	// lines y=x etc.
	Graph_lib::Function xy([](double x) {return x; }, -len, len + 1, orig, 21, xscale, yscale); // y = x
	xy.set_color(fl_color_cube(0, 7, 3));
	win.attach(xy);
	Graph_lib::Point pline;
	pline.x = xy.point(0).x - xscale/2;
	pline.y = xy.point(0).y - yscale / 2;
	Graph_lib::Text txy(pline, "y=x");
	txy.set_color(fl_color_cube(0, 7, 3));
	win.attach(txy);


	Graph_lib::Function xy_d2([](double x) {return x / 2; }, -len, len + 1, orig, 21, xscale, yscale); // y = x / 2
	xy_d2.set_color(fl_color_cube(2, 0, 3));
	win.attach(xy_d2);
	pline.x = xy_d2.point(0).x - xscale / 2;
	pline.y = xy_d2.point(0).y - yscale / 2;
	Graph_lib::Text txy_d2(pline, "y=x/2");
	txy_d2.set_color(fl_color_cube(2, 0, 3));
	win.attach(txy_d2);
	
	
	Graph_lib::Function m_xy_d2([](double x) {return -x / 2; }, -len, len + 1, orig, 21, xscale, yscale);
	m_xy_d2.set_color(fl_color_cube(3, 4, 2));
	win.attach(m_xy_d2);
	Graph_lib::Point pt{ m_xy_d2.point(0).x, m_xy_d2.point(0).y - yscale/2 }; // y = -x/2
	Graph_lib::Text t_m_xy_d2(pt , "-x/2");
	t_m_xy_d2.set_color(fl_color_cube(3, 4, 2));
	win.attach(t_m_xy_d2);


	Graph_lib::Function s(Graph_lib::line4, -len, len + 1, orig, xscale, yscale);
	s.set_color(fl_color_cube(3, 5, 2));
	win.attach(s);

	Graph_lib::Axis x_axis(Graph_lib::Axis::Orientation::x, Graph_lib::Point(dif_g/2, y_org), x_length, x_length/xscale, "x axis");
	x_axis.set_color(fl_color_cube(0, 4, 4));
	win.attach(x_axis);

	Graph_lib::Axis y_axis(Graph_lib::Axis::Orientation::y, Graph_lib::Point(x_org, y_length+dif_g/2), y_length, y_length/yscale, "y axis");
	y_axis.set_color(fl_color_cube(0, 4, 4));
	win.attach(y_axis);
	
	//Graph_lib::Function l1(Graph_lib::line4);
	//l1.set_color(fl_color_cube(4, 4, 4));
	////win.attach(l1);

	//Graph_lib::Function s3(Graph_lib::parabola, -10, 11, Graph_lib::Point(200, 50), 400, 25, 25);
	//win.attach(s3);
	win.wait_for_button();
	return 0;
}
catch (std::exception& e)
{
	std::cerr << "exception: " << e.what() << '\n';
	keep_window_open();
}
catch (...)
{
	std::cerr << "exception\n";
	keep_window_open();
}



Graph_lib::Point find_point_window(const Graph_lib::Function& s, const Graph_lib::Point& up)
{
	
	auto point = std::upper_bound(s.points.begin(), s.points.end(), up, 
		[](const Graph_lib::Point& up, const Graph_lib::Point& pred)
		{
			return (up.x < pred.x && up.y < pred.y);
		});
	return Graph_lib::Point(point->x, point->y);
	
//		std::upper_bound(s.point.begin(), s.point.end(), up, 
}