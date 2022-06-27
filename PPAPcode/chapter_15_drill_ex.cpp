#include <iostream>
#include <vector>
#include <math.h>
#include <functional>
#include "Simple_window.h"
#include "Graph.h"
// constants
const int width_window = 1920;
const int height_window = 1080;




double parabola(double x);

int chapter_15_drill_ex()
try
{
	Graph_lib::Point pxstart(50, 50);
	Graph_lib::Simple_window win(pxstart, width_window / 2, height_window / 2, "Chapter 15");

	//Graph_lib::Group 

	Graph_lib::Function s;
	s.set_color(fl_color_cube(3, 5, 2));
	//win.attach(s);

	Graph_lib::Function l1(Graph_lib::line4);
	l1.set_color(fl_color_cube(4, 4, 4));
	//win.attach(l1);

	Graph_lib::Function s3(parabola, -10, 11, Graph_lib::Point(200, 50), 400, 25, 25);
	win.attach(s3);
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



