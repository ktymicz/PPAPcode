#include <iostream>
#include <vector>
#include <math.h>
#include "Simple_window.h" // get access to our window library
#include "Graph.h"

 const int width_window = 1920;
 const int height_window = 1080;

 void Smiley_Frowny();
 void immobile_Circle();
 void striped_rectangle();
 void striped_circle();
 void striped_closed_polyline();
 void octagon();
 void group_shape();

 int chapter14()
try
{
    /*using namespace Graph_lib;
    Graph_lib::Simple_window win(Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Graph_lib::Immobile_Circle circle_immobile(Point{400, 300}, 40);
    // circle_immobile.move(20,20); // protected in this context :_)
    win.attach(circle_immobile);
    */



    //Smiley_Frowny();
    //immobile_Circle();
    //striped_rectangle();
    //striped_circle();
    //striped_closed_polyline();
    //octagon();
    //group_shape();
    return 0;
}
catch(exception & e)
{
    cerr << "exception: " << e.what() << '\n';
    keep_window_open();
}
catch(...)
{
    cerr << "exception\n";
    keep_window_open();
}

void group_shape()
{
    using namespace Graph_lib;
    Graph_lib::Simple_window win(Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Graph_lib::Group gr;
    //Graph_lib::Rectangle s(Graph_lib::Rectangle(Point(100,100),40,40));
    for(int dy=0; dy<480; dy+=40)
        for(int dx=0; dx<480; dx+=40){
            gr.add_Shape(new Graph_lib::Rectangle(Point(100+dx,100+dy),40,40));
        }

    for(int s=0, odd=0; s<gr.size(); s++){
        if(!(s%12))
            odd++;
        if(s%2 && odd%2 || (((s+1)%2)) && !(odd%2)){
            gr[s].set_fill_color(Color::blue);
        }
        else{
            gr[s].set_fill_color(Color::black);
        }

    }



    //gr.add_Shape(s);

    for(int i = 0; i<gr.size(); i++)
        win.attach(gr[i]);

    win.wait_for_button();
}

void octagon()
{
    using namespace Graph_lib;
    Graph_lib::Simple_window win(Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Octagon octR(Point{200,200}, 50, 15);
    octR.set_fill_color(fl_color_cube(0,7,1));
    octR.set_color(fl_color_cube(0,0,4));
    // octR.add(Point{24,23});  // error protected
    for(int i =0; i<octR.number_of_points(); i++)
        std::cout << "x:"<< octR.point(i).x
                  << ", y:"  << octR.point(i).y
                  << " "<< i << "-point\n";
    octR.set_style(Line_style(Line_style::dashdotdot, 3));

    win.attach(octR);
    win.wait_for_button();
}

void striped_closed_polyline()
{
    using namespace Graph_lib;
    Graph_lib::Simple_window win(Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Striped_closed_polyline scp;
    scp.set_fill_color(fl_color_cube(0,7,1));
    scp.set_color(fl_color_cube(0,0,5));
    scp.add(Point{100,100});
    scp.add(Point{120, 120});
    scp.add(Point{145, 130});
    scp.add( Point{90,145});

    win.attach(scp);

    win.wait_for_button();
}

void striped_circle()
{
    using namespace Graph_lib;
    Graph_lib::Simple_window win(Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Striped_circle sc(Point(100,100),30);
    sc.set_fill_color(fl_color_cube(0,7,1));
    sc.set_color(fl_color_cube(0,0,5));
    win.attach(sc);


    Graph_lib::Circle c(Point(200,200), 40);
    c.set_fill_color(fl_color_cube(0,7,1));
    c.set_color(fl_color_cube(0,0,5));
    win.attach(c);
    win.wait_for_button();
}


void striped_rectangle()
{
    using namespace Graph_lib;
    Graph_lib::Simple_window win(Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Striped_rectangle sr(Point(100,100),88,40);
    sr.set_fill_color(fl_color_cube(0,7,1));
    sr.set_color(fl_color_cube(0,0,5));
    win.attach(sr);


    Graph_lib::Rectangle r(Point(200,200),88,40);
    r.set_fill_color(fl_color_cube(0,7,1));
    r.set_color(fl_color_cube(0,0,5));
    win.attach(r);
    win.wait_for_button();
}


void immobile_Circle()
{
       using namespace Graph_lib;
    Graph_lib::Simple_window win(Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Graph_lib::Immobile_Circle circle_immobile(Point{400, 300}, 40);
    //circle_immobile.move(20,20); // protected in this context :_)
    win.attach(circle_immobile);
    win.wait_for_button();
}

void Smiley_Frowny()
{
    using namespace Graph_lib;
    //using namespace Graph_lib; // our graphics facilities are in Graph_lib
    Graph_lib::Simple_window win(Point(100,100), width_window-1000,height_window-500,"My window");
    Smiley m(Point(100,100), 50);
    Frowny fy(Point(200,100), 50);
    win.attach(m);
    win.attach(fy);

    //Smiley_hat sh(Point(300,200), 50);
    //win.attach(sh);

    win.wait_for_button();
}
