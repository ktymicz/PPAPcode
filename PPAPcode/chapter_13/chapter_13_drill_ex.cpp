#include <iostream>
#include <vector>
#include <math.h>
#include <Simple_window.h> // get access to our window library
#include <Graph.h>


 const int width_window = 1920;
 const int height_window = 1080;


 // ex1 Arc class draws a part of ellipse
 void draw_Arcs();
 // ex2 Box class draws a part of rounded box
 void draw_Boxes();
 // ex3 Arrow class
 void draw_Arrows();
 // ex 4, rectangle functions
 // n(), s(), e(), w(), center(), ne(), se(), sw(), and nw()
 void use_rectangle_functions();
 // ex 5, ellipse and circle functions
 // n(), s(), e(), w(), center(), ne(), se(), sw(), and nw()
 void use_ellipse_functions();
// ex 6
// a class diagram, creating a new Box class with text
 void use_Text_Box();
 // ex 7 RGB color chart
 void rgb_color_chart();
 // ex 8   Regular_hexagons
 void  regular_hexagons();
 // ex 9 Tile of hexagons(8)
 void tile_hexagons();
 // ex 10 Define a class Regular polygons ,
 // Regular_polygons(Point center,  int dist_center_corner, int sides)
 void regular_polygons();
// ex 11
// Foci (focus points) of an ellipse
void foci_ellipse();
// ex 12
// Draw a circle. Move a mark around on the circle, after the "Next" button is pressed
void  move_mark_Circle();
 // ex 13
 // chart without a lines around each color;
 void rgb_color_chart_Invisible();
 // ex 14
 // The right triangle class
 // Make an octagonal shape out of eight right triangles of different colors.
 void rigth_triangles();
 // ex 15
 // Tile a window with small right triangles
 void tile_right_triangles();

int chapter13()
try
{
    using namespace Graph_lib;
    //using namespace Graph_lib; // our graphics facilities are in Graph_lib

    // ex1
    //draw_Arcs();
    // ex2
    //draw_Boxes();
    // ex3
    //draw_Arrows();
    // ex 4
    //use_rectangle_functions();
    // ex 5
    //use_ellipse_functions();
    // ex 6
    //use_Text_Box();
    // ex 7
    //rgb_color_chart();
    // ex 8
    //regular_hexagons();
    // ex 9
    //tile_hexagons();
    // ex 10
    //regular_polygons();
    // ex 11
    //foci_ellipse();
    // ex 12
    move_mark_Circle();
    // ex 13
    //rgb_color_chart_Invisible();
    // ex 14
     //rigth_triangles();
     // ex 15
     //tile_right_triangles();
     // Test
//     Graph_lib::Rectangle m(Point(100,100),Point(150,150));
//
//     Graph_lib::Simple_window win(Point(100,100), width_window-100,height_window-100,"My window");
//     win.attach(m);
//     win.wait_for_button();
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



void draw_Arcs()    // ex1
// Arc(Point p, int width, int hight, double start, double end);
// more information below function def.
{
    using namespace Graph_lib;
    Point pWin{100,100};
    Simple_window win{pWin, width_window-100,height_window-100,"My window"};

    ostringstream sc;

    Text info(Point{0,0}, "Arc inside a rectangle, w==h");
    win.attach(info);
    Graph_lib::Arc s(Point{50,150}, 150,150,0,360);
    s.set_color(Color::dark_blue);
    s.set_fill_color(Color::blue);
    win.attach(s);
    info.move(s.point(0).x - 25, s.point(0).y - 25);

    sc << "Arc blue angle:" << s.angle_beg() << '-' << s.angle_end();
    Text s_text(Point{50, 150}, sc.str());
    sc.clear();
    sc.str("");
    s_text.set_color(s.color());
    win.attach(s_text);

    Graph_lib::Arc s1(Point{250, 150}, 150,150,0,180);
    s1.set_color(Color::black);
    win.attach(s1);
    Text s_text1(Point{250, 150}, "Arc black 0-180");
    s_text1.set_color(s1.color());
    win.attach(s_text1);

    Graph_lib::Arc s2(Point{350,150}, 150, 150,0,90);
    s2.set_color(Color::yellow);
    s2.set_fill_color(Color::yellow);
    win.attach(s2);
    Text s_text2(Point{350+150/2, 150}, "Arc yellow 0-90");
    s_text2.set_color(s2.color());
    win.attach(s_text2);


    Graph_lib::Arc s3(Point{550,150}, 150,150,0,270);
    s3.set_color(Color::dark_cyan);
    win.attach(s3);
    Text s_text3(s3.point(0), "Arc dark_cyan 0-270");
    s_text3.set_color(s3.color());
    win.attach(s_text3);


    Text info1{Point{0,0}, "Arc draw ellipse, w!=h"};
    win.attach(info1);

    Graph_lib::Arc c(Point{50,350}, 45, 90, 0,360);
    info1.move( c.point(0).x-25, c.point(0).y-25);
    c.set_color(Color::dark_green);
    win.attach(c);
    sc << "Arc ellipse dark_green, rect:"
       << c.major() << 'x'<< c.minor()
       << ", angle:" << c.angle_beg() << '-' << c.angle_end();
    Text c_text(c.point(0), sc.str());
    sc.clear();
    sc.str("");
    c_text.set_color(c.color());
    win.attach(c_text);

    Graph_lib::Arc c1(Point{150,375}, 40,80, 60, 180);
    c1.set_color(Color::black);
    win.attach(c1);
    sc << "Arc ellipse black, rect:"
       << c1.major() << 'x'<< c1.minor()
       << ", angle:" << c1.angle_beg() << '-' << c1.angle_end();
    Text c1_text(c1.point(0), sc.str());
    sc.clear();
    sc.str("");
    c1_text.set_color(c1.color());
    win.attach(c1_text);

    Graph_lib::Arc ss2(Point{800,600},200,200,0,90);
    ss2.set_color(Color::black);
    ss2.set_fill_color(Color::yellow);
    win.attach(ss2);

    win.wait_for_button();
}
// use of class Arc
// Arc(Point p, int width, int hight, double start, double end);
// the bounding box of ellipse is rectangle with a Point and width x hight
// The Point is a top left corner.
// start and end are angles
// Angles are measured from 3 o'clock counter-clockwise

void draw_Boxes()  //ex2
// use of class Box
// Box(Point p, int width, int hight, int radius);
{

    using namespace Graph_lib;
    Point pWin{100,100};
    Simple_window win{pWin, width_window-100,height_window-100,"My window"};

    Box b(Point(100,100), 50, 50, 10);
    b.set_color(Color::black);
    b.set_fill_color(Color::yellow);
    win.attach(b);

    Box b2(Point(400,400), 100, 50, 24);
    b2.set_color(Color::black);
    b2.set_fill_color(Color::yellow);
    win.attach(b2);

    Box b3(Point(50,30), 100, 50, 5);
    b3.set_color(Color::blue);
    b3.set_fill_color(Color::yellow);
    win.attach(b3);

    Box b4(Point(50,600), 400, 300, 50);
    b4.set_color(Color::blue);
    b4.set_fill_color(Color::yellow);
    win.attach(b4);


    win.wait_for_button();
}


void draw_Arrows()
// use of class Arrow
//
{
   using namespace Graph_lib;

   Point pWin{100,100};
   Simple_window win{pWin, width_window-100,height_window-100,"My window"};

   Graph_lib::Arc cir_arrow(Point(300, 300), 200, 200, 0, 360);      // Circle
   win.attach(cir_arrow);
   Arrow ar(cir_arrow.center(), Point(cir_arrow.center().x+40,
                                       cir_arrow.center().y+40));
   win.attach(ar);
   Arrow ar1(Point(cir_arrow.center().x-cir_arrow.major()/2,
                   cir_arrow.center().y),
             Point(cir_arrow.center().x-cir_arrow.major()/2+50,
                   cir_arrow.center().y));
   win.attach(ar1);
   Arrow ar2(Point(cir_arrow.center().x+cir_arrow.major()/2,
                   cir_arrow.center().y),
             Point(cir_arrow.center().x+cir_arrow.major()/2+50,
                   cir_arrow.center().y));
   win.attach(ar2);
   Arrow ar3(Point(cir_arrow.center().x,
                   cir_arrow.center().y-cir_arrow.minor()/2),
             Point(cir_arrow.center().x,
                   cir_arrow.center().y-cir_arrow.minor()/2+50));
   win.attach(ar3);


   double alpha= PI/4; // 45 angle
   double vu, vy, vx;
    // sin alpha = vy/vu;
    // vy = sin alpha * vu;
    // cos alpha = vx / vu;
    // vx=cos alpha * vu;
   vu =  cir_arrow.major()/2;
   vx =  cos(alpha) * vu;
   vy =  sin(alpha) * vu;
   //std::cout  << vx << ',' << vy <<'\n'
   //           << cos(alpha) << ',' << sin(alpha) <<'\n'
   //           << sqrt(2)/2;
   Arrow ar4(Point(cir_arrow.center().x-vx,
                   cir_arrow.center().y-vy),
             Point(cir_arrow.point(0).x,
                   cir_arrow.point(0).y));
   win.attach(ar4);
   Arrow ar5(Point(200, 100), Point(100, 145));
   win.attach(ar5);
   Arrow ar6(Point(400, 100), Point(45, 55));
   win.attach(ar6);
   win.wait_for_button();
}

void use_rectangle_functions()
{
    using namespace Graph_lib;

   Point pWin{100,100};
   Simple_window win{pWin, width_window-100,height_window-100,"My window"};

    //rectangle show
   Graph_lib::Rectangle r(Point(600,600), 50, 50);
   win.attach(r);
   Arrow arr_rect(center(r), Point(center(r).x-60, center(r).y-20));
   win.attach(arr_rect);
   Arrow arr_rect1(n(r), Point(n(r).x-60, n(r).y-20));
   win.attach(arr_rect1);
   Arrow arr_rect2(s(r), Point(s(r).x-60, s(r).y-20));
   win.attach(arr_rect2);
   Arrow arr_rect3(e(r), Point(e(r).x-60, e(r).y-20));
   win.attach(arr_rect3);
   Arrow arr_rect4(w(r), Point(w(r).x-60, w(r).y-20));
   win.attach(arr_rect4);
   Arrow arr_rect5(ne(r), Point(ne(r).x-60, ne(r).y-20));
   win.attach(arr_rect5);
   Arrow arr_rect6(nw(r), Point(nw(r).x-60, nw(r).y-20));
   win.attach(arr_rect6);
   Arrow arr_rect7(se(r), Point(se(r).x-60, se(r).y-20));
   win.attach(arr_rect7);
   Arrow arr_rect8(sw(r), Point(sw(r).x-60, sw(r).y-20));
   win.attach(arr_rect8);
   win.wait_for_button();
}

 void use_ellipse_functions()
 // ex 5
 // n(), s(), e(), w(), center(), ne(), se(), sw(), and nw()
 {
    using namespace Graph_lib;

   Point pWin{100,100};
   Simple_window win{pWin, width_window-100,height_window-100,"My window"};

    // ellipse show
   Graph_lib::Ellipse e(Point(300,500), 100, 50);
   e.set_color(Color::black);
   e.set_fill_color(Color::dark_green);
   win.attach(e);
   Arrow arr_e(n(e), Point(n(e).x, n(e).y-40));
   win.attach(arr_e);
   Arrow arr_e1(s(e), Point(s(e).x, s(e).y+40));
   win.attach(arr_e1);
   Arrow arr_e2(Graph_lib::e(e), Point(Graph_lib::e(e).x+60, Graph_lib::e(e).y));
   win.attach(arr_e2);
   Arrow arr_e3(Graph_lib::w(e), Point(Graph_lib::w(e).x-60, Graph_lib::w(e).y));
   win.attach(arr_e3);
   Arrow arr_e4(ne(e), Point(center(e).x+e.major(), center(e).y-e.minor()));
   win.attach(arr_e4);
   Arrow arr_e5(se(e), Point(center(e).x+e.major(), center(e).y+e.minor()));
   win.attach(arr_e5);
   Arrow arr_e6(nw(e), Point(center(e).x-e.major(), center(e).y-e.minor()));
   win.attach(arr_e6);
   Arrow arr_e7(sw(e), Point(center(e).x-e.major(), center(e).y+e.minor()));
   win.attach(arr_e7);
   Graph_lib::Mark mk_e(center(e), 'x');
   win.attach(mk_e);

   Graph_lib::Circle c(Point(200, 200), 100);
   c.set_color(Color::dark_magenta);
   win.attach(c);
   Arrow arr_c(n(c), Point(n(c).x, n(c).y-40));
   win.attach(arr_c);
   Arrow arr_c1(s(c), Point(s(c).x, s(c).y+40));
   win.attach(arr_c1);
   Arrow arr_c2(Graph_lib::e(c), Point(Graph_lib::e(c).x+40, Graph_lib::e(c).y));
   win.attach(arr_c2);
   Arrow arr_c3(w(c), Point(w(c).x-40, w(c).y));
   win.attach(arr_c3);
   Graph_lib::Mark mk_c(center(c), 'x');
   win.attach(mk_c);
   Arrow arr_c4(ne(c), Point(ne(c).x+40, ne(c).y-40));
   win.attach(arr_c4);
   Arrow arr_c5(se(c), Point(se(c).x+40, se(c).y+40));
   win.attach(arr_c5);
   Arrow arr_c6(sw(c), Point(sw(c).x-40, sw(c).y+40));
   win.attach(arr_c6);
   Arrow arr_c7(nw(c), Point(nw(c).x-40, nw(c).y-40));
   win.attach(arr_c7);
   win.wait_for_button();
 }


 void use_Text_Box()
 // ex 6
 // a class diagram , creating a new Box class with text
 {
    using namespace Graph_lib;

   Point pWin{100,100};
   Simple_window win{pWin, width_window-100,height_window-100,"My window"};
   // One letter 8 pixels, + sides 10
   Text_Box tb(Point(300,50),118,26,5,"Shapes Diagram"); // 14*8+10
   tb.b.set_color(Color::dark_green);
   tb.b.set_fill_color(Color::cyan);
   tb.set_color(Color::black);
   win.attach(tb);

   Text_Box tb1(Point(200,100), 60, "Window"); // 8*6
   tb1.b.set_color(Color::dark_green);
   tb1.b.set_fill_color(Color::cyan);
   tb1.set_color(Color::black);
   win.attach(tb1);

   Text_Box tb2(Point(290,100), 80, "Line_style"); //
   tb2.b.set_color(Color::dark_green);
   tb2.b.set_fill_color(Color::cyan);
   tb2.set_color(Color::black);
   win.attach(tb2);

   Text_Box tb3(Point(400,100),55, "Color");
   tb3.b.set_color(Color::dark_green);
   tb3.b.set_fill_color(Color::cyan);
   tb3.set_color(Color::black);
   win.attach(tb3);

   Text_Box tb4(Point(tb1.point(0).x-30, tb1.point(0).y+60), 110, "Simple_window");
   tb4.b.set_color(Color::dark_green);
   tb4.b.set_fill_color(Color::cyan);
   tb4.set_color(Color::black);
   win.attach(tb4);

   Text_Box tb5(Point(tb4.b.point(0).x+150, tb4.b.point(0).y-15), 55, "Shape");
   tb5.b.set_color(Color::dark_green);
   tb5.b.set_fill_color(Color::cyan);
   tb5.set_color(Color::black);
   win.attach(tb5);

   Text_Box tb6(Point(tb4.b.point(0).x+245, tb4.b.point(0).y), 55, "Point");
   tb6.b.set_color(Color::dark_green);
   tb6.b.set_fill_color(Color::cyan);
   tb6.set_color(Color::black);
   win.attach(tb6);


   Text_Box tb7(Point(tb4.b.point(0).x-20, tb4.b.point(0).y+70), 38, "Line");
   tb7.b.set_color(Color::dark_green);
   tb7.b.set_fill_color(Color::cyan);
   tb7.set_color(Color::black);
   win.attach(tb7);
   Arrow arr_tb7(n(tb7.b), Point(s(tb5.b).x-22, s(tb5.b).y));
   arr_tb7.set_color(Color::black);
   win.attach(arr_tb7);

   Text_Box tb8(Point(tb7.b.point(0).x+38+6, tb7.b.point(0).y), 45, "Lines");
   tb8.b.set_color(Color::dark_green);
   tb8.b.set_fill_color(Color::cyan);
   tb8.set_color(Color::black);
   win.attach(tb8);
   Arrow arr_tb8(n(tb8.b), Point(s(tb5.b).x-10, s(tb5.b).y));
   arr_tb8.set_color(Color::black);
   win.attach(arr_tb8);

   Text_Box tb9(Point(tb8.b.point(0).x+45+6, tb7.b.point(0).y), 59, "Polygon");
   tb9.b.set_color(Color::dark_green);
   tb9.b.set_fill_color(Color::cyan);
   tb9.set_color(Color::black);
   win.attach(tb9);
   Arrow arr_tb9(n(tb9.b), s(tb5.b));
   arr_tb9.set_color(Color::black);
   win.attach(arr_tb9);

   Text_Box tb10(Point(tb9.b.point(0).x+59+6, tb9.b.point(0).y), 38, "Axis");
   tb10.b.set_color(Color::dark_green);
   tb10.b.set_fill_color(Color::cyan);
   tb10.set_color(Color::black);
   win.attach(tb10);
   Arrow arr_tb10(n(tb10.b), Point(s(tb5.b).x+6, s(tb5.b).y));
   arr_tb10.set_color(Color::black);
   win.attach(arr_tb10);

   Text_Box tb11(Point(tb10.b.point(0).x+38+6, tb10.b.point(0).y), 73, "Rectangle");
   tb11.b.set_color(Color::dark_green);
   tb11.b.set_fill_color(Color::cyan);
   tb11.set_color(Color::black);
   win.attach(tb11);
   Arrow arr_tb11(n(tb11.b), Point(s(tb5.b).x+8, s(tb5.b).y));
   arr_tb11.set_color(Color::black);
   win.attach(arr_tb11);

   Text_Box tb12(Point(tb11.b.point(0).x+73+6, tb11.b.point(0).y), 38, "Text");
   tb12.b.set_color(Color::dark_green);
   tb12.b.set_fill_color(Color::cyan);
   tb12.set_color(Color::black);
   win.attach(tb12);
   Arrow arr_tb12(n(tb12.b), Point(s(tb5.b).x+18, s(tb5.b).y));
   arr_tb12.set_color(Color::black);
   win.attach(arr_tb12);

   Text_Box tb13(Point(tb12.b.point(0).x+38+6, tb12.b.point(0).y), 48, "Image");
   tb13.b.set_color(Color::dark_green);
   tb13.b.set_fill_color(Color::cyan);
   tb13.set_color(Color::black);
   win.attach(tb13);
   Arrow arr_tb13(n(tb13.b), Point(s(tb5.b).x+28, s(tb5.b).y));
   arr_tb13.set_color(Color::black);
   win.attach(arr_tb13);

   win.wait_for_button();
 }


 void rgb_color_chart()
 // ex 7
 {
     using namespace Graph_lib;
     Simple_window win(Point(0,100), width_window-100, height_window-100, "RGB color chart");

     const int chart_size = 256;
     const int rows = 25;
     const int columns = 8;
     const int r_size = 15; // rectangle size
     const Point startpr(50,50); // start_point_rect(50,50);
     Graph_lib::Vector_ref<Graph_lib::Rectangle> vec_prects;

     unsigned char red=32;
     unsigned char green=32;
     unsigned char blue=32;

// 5x5x8 BRG color cube https://www.fltk.org/doc-1.3/drawing.html#drawing_colors
// red to go down a row, blue to go down one cube, green to go right

     for(unsigned char row=0; row<rows; row++)
        for(unsigned char column=0; column<columns; column++)
        {
            vec_prects.push_back( new Graph_lib::Rectangle
                                 (Point(startpr.x+r_size*column, startpr.y+r_size*row), r_size, r_size));
            vec_prects[vec_prects.size()-1].set_color(fl_rgb_color(red, green, blue));
            //vec_prects[vec_prects.size()-1].set_style(Line_style::solid);
            // for RGB use fl_rgb_color(red, green, blue)
            // for color cube from FLTK use  fl_color_cube(red, green, blue)
            vec_prects[vec_prects.size()-1].set_fill_color(fl_color_cube(row%5, column, row/5));

            win.attach(vec_prects[vec_prects.size()-1]);
        }
    win.wait_for_button();
 }


 void  regular_hexagons()
 // ex 8
 {
     using namespace Graph_lib;
     Point pWin{50,100};
     Simple_window win{pWin, width_window-100,height_window-100,"regular hexagons"};

     Regular_hexagon hexa(Point(300,300), 60, 30);
     hexa.set_color(Color::black);

     win.attach(hexa);
     Mark xhex(hexa.center(), 'x');
     win.attach(xhex);

     Regular_hexagon hexa1(Point(200,200), 30, 15);
     hexa1.set_color(Color::black);

     win.attach(hexa1);
     Mark xhex1(hexa1.center(), 'x');
     win.attach(xhex1);

     Regular_hexagon hexa2(Point(500,200), 30, 45);
     hexa2.set_color(Color::black);

     win.attach(hexa2);
     Mark xhex2(hexa2.center(), 'x');
     win.attach(xhex2);

     Regular_hexagon hexa3(Point(600,200), 30, 45);
     hexa3.set_color(Color::black);

     win.attach(hexa3);
     Mark xhex3(hexa3.center(), 'x');
     win.attach(xhex3);

     Regular_hexagon hexa4(Point(200,300), 30);
     hexa4.set_color(Color::black);

     win.attach(hexa4);
     Mark xhex4(hexa4.center(), 'x');
     win.attach(xhex4);

     win.wait_for_button();
 }


void tile_hexagons()
// ex 9
{

     using namespace Graph_lib;
     Point pWin{50,100};
     Simple_window win{pWin, width_window-100,height_window-100,"Tile of hexagons"};
     const int hex_r = 50;
     // cos 30 = hex_height/hex_r
     const double tri_height = hex_r*(sqrt(3)/2);
     const double hex_width = 2*tri_height;

     Point pstart(300,300);
     Regular_hexagon hexa(pstart, hex_r, 30);
     hexa.set_color(Color::black);
     hexa.set_fill_color(fl_color_cube(0,7,0));
     win.attach(hexa);

     Regular_hexagon hexa1(Point(pstart.x+hex_width, pstart.y), hex_r, 30);
     hexa1.set_color(Color::black);
     hexa1.set_fill_color(fl_color_cube(4,3,0));
     win.attach(hexa1);

     Regular_hexagon hexa2(Point(pstart.x+2*hex_width-0.5,pstart.y), hex_r, 30);
     hexa2.set_color(Color::black);
     hexa2.set_fill_color(fl_color_cube(4,7,4));
     win.attach(hexa2);

     Regular_hexagon hexa3(Point(pstart.x+tri_height, (pstart.y+hex_r+sin(30*PI/180)*hex_r+0.5)), hex_r, 30);
     hexa3.set_color(Color::black);
     hexa3.set_fill_color(fl_color_cube(4,0,0));
     win.attach(hexa3);


     Regular_hexagon hexa4(Point(pstart.x+hex_width+tri_height,pstart.y+hex_r+sin(30*PI/180)*hex_r+0.5), hex_r, 30);
     hexa4.set_color(Color::black);
     hexa4.set_fill_color(fl_color_cube(4,0,4));
     win.attach(hexa4);

     Regular_hexagon hexa5(Point(pstart.x+400,pstart.y), hex_r, 30);
     hexa5.set_color(Color::black);
     hexa5.set_fill_color(fl_color_cube(2,7,2));
     win.attach(hexa5);

     Regular_hexagon hexa6(Point(pstart.x+300,pstart.y), hex_r, 30);
     hexa6.set_color(Color::black);
     win.attach(hexa6);

     win.wait_for_button();
}

void regular_polygons()
// ex 10
{

     using namespace Graph_lib;
     Point pWin{50,100};
     Simple_window win{pWin, width_window-100,height_window-100,"Regular polygons"};
     const int hex_r = 50;
     // cos 30 = hex_height/hex_r
     const double tri_height = hex_r*(sqrt(3)/2);
     const double hex_width = 2*tri_height;

     Point pstart(300,300);
     Regular_polygon hexa(pstart, hex_r, 3);
     hexa.set_color(Color::black);
     hexa.set_fill_color(fl_color_cube(0,7,0));
     win.attach(hexa);

     Regular_polygon hexa1(Point(pstart.x+hex_width, pstart.y), hex_r, 4);
     hexa1.set_color(Color::black);
     hexa1.set_fill_color(fl_color_cube(4,3,0));
     win.attach(hexa1);

     Regular_polygon hexa2(Point(pstart.x+2*hex_width-0.5,pstart.y), hex_r, 4);
     hexa2.set_color(Color::black);
     hexa2.set_fill_color(fl_color_cube(4,7,4));
     win.attach(hexa2);

     Regular_polygon hexa3(Point(pstart.x+tri_height, (pstart.y+hex_r+sin(30*PI/180)*hex_r+0.5)), hex_r, 6);
     hexa3.set_color(Color::black);
     hexa3.set_fill_color(fl_color_cube(4,0,0));
     win.attach(hexa3);


     Regular_polygon hexa4(Point(pstart.x+hex_width+tri_height,pstart.y+hex_r+sin(30*PI/180)*hex_r+0.5), hex_r, 7);
     hexa4.set_color(Color::black);
     hexa4.set_fill_color(fl_color_cube(4,0,4));
     win.attach(hexa4);

     Regular_polygon hexa5(Point(pstart.x+400,pstart.y), hex_r, 8);
     hexa5.set_color(Color::black);
     hexa5.set_fill_color(fl_color_cube(2,7,2));
     win.attach(hexa5);

     Regular_polygon hexa6(Point(pstart.x+300,pstart.y), hex_r, 9);
     hexa6.set_color(Color::black);
     win.attach(hexa6);

     win.wait_for_button();
}


// ex 11
// Foci (focus points) of an ellipse
void foci_ellipse()
{
     using namespace Graph_lib;
     Point pWin{50,100};
     Simple_window win{pWin, width_window-100,height_window-100,"Foci of an ellipse"};
     int w_ellipse=300;
     int h_ellipse=200;

     Point pstart(400,400);
     Point pfoci1{pstart.x - (int) sqrt(pow(w_ellipse,2) -(int) pow(h_ellipse,2)),pstart.y};
     Point pfoci2{pstart.x+(int)sqrt(pow(w_ellipse,2)-(int)pow(h_ellipse,2)),pstart.y};
     Mark mfoci1(pfoci1, 'x');
     win.attach(mfoci1);
     Mark mfoci2(pfoci2, 'x');
     win.attach(mfoci2);
     Graph_lib::Ellipse el(pstart, w_ellipse, h_ellipse);
     el.set_color(fl_color_cube(3,3,0));
     win.attach(el);
    // Arrow yaxis(Point{400,500}, Point{400, 200 });
     //yaxis.set_color(fl_color_cube(3,0,4));
     //win.attach(yaxis);
     //Arrow xaxis(Point{300,400}, Point{700, 400 });
     //xaxis.set_color(fl_color_cube(3,0,4));
    // win.attach(xaxis);

     Graph_lib::Axis xax(Axis::x,pstart,400, 40,"x axis [10px]");
     xax.set_color(fl_color_cube(3,0,4));
     win.attach(xax);
     Graph_lib::Axis yax(Axis::y,pstart,300, 30,"y axis [10px]");
     yax.set_color(fl_color_cube(3,0,4));
     win.attach(yax);

     Point pEllipse = give_point(el, 30);
     Mark mPoint(pEllipse, 'x');
     win.attach(mPoint);
     Lines lines_foci{pEllipse, pfoci1, pEllipse, pfoci2 };
     lines_foci.set_color(fl_color_cube(4,0,0));
     win.attach(lines_foci);

     Graph_lib::Text foci_text1(Point(pfoci1.x, pfoci1.y+20), "F1");
     foci_text1.set_color(Color::black);
     win.attach(foci_text1);

     Graph_lib::Text foci_text2(Point(pfoci2.x, pfoci2.y+20), "F2");
     foci_text2.set_color(Color::black);
     win.attach(foci_text2);
     win.wait_for_button();
}

// ex 12
// Draw a circle. Move a mark around on the circle , after the "Next" button is pressed
void  move_mark_Circle()
{
     using namespace Graph_lib;
     Point pWin{50,100};
     Simple_window win{pWin, width_window-100,height_window-100,"The Mark around the Circle"};

     Point pstart(300, 300);
     int radius = 30;
     Circle cm(pstart, radius);
     cm.set_color(Color::black);
     win.attach(cm);
     /*  marks are growing on the Circle
     Vector_ref<Mark> m;
     for(double angle_rad = 0.0; angle_rad<=2*PI; angle_rad+=0.2)
     {
        m.push_back(new Mark(give_point(cm, angle_rad), 'x'));
        win.attach(m[m.size()-1]);
        win.wait_for_button();
     }*/
     int step=10;
     int angle=0;
     Mark m(give_point(cm, angle), 'x');
     win.attach(m);
     win.wait_for_button();
     Point pnew;
     for(angle = step; angle<=360; angle+=step)
     {
        pnew = give_point(cm, angle);
        int dx = pnew.x - m.point(0).x;
        int dy = pnew.y - m.point(0).y;
        m.move(dx,dy);
        win.wait_for_button();
     }

}


 void rgb_color_chart_Invisible()
 // ex 13
 // chart without a lines around each color;
 {
     using namespace Graph_lib;
     Simple_window win(Point(0,100), width_window-100, height_window-100,
                       "RGB color chart without lines around each color");

     const int chart_size = 256;
     const int rows = 25;
     const int columns = 8;
     const int r_size = 15; // rectangle size
     const Point startpr(50,50); // start_point_rect(50,50);
     Graph_lib::Vector_ref<Graph_lib::Rectangle> vec_prects;

     unsigned char red=32;
     unsigned char green=32;
     unsigned char blue=32;

// 5x5x8 BRG color cube https://www.fltk.org/doc-1.3/drawing.html#drawing_colors
// red to go down a row, blue to go down one cube, green to go right

     for(unsigned char row=0; row<rows; row++)
        for(unsigned char column=0; column<columns; column++)
        {
            vec_prects.push_back( new Graph_lib::Rectangle
                                 (Point(startpr.x+r_size*column, startpr.y+r_size*row), r_size, r_size));
            vec_prects[vec_prects.size()-1].set_color(Color::invisible);
            //vec_prects[vec_prects.size()-1].set_color(fl_rgb_color(red, green, blue));
            //vec_prects[vec_prects.size()-1].set_style(Line_style::solid);
            // for RGB use fl_rgb_color(red, green, blue)
            // for color cube from FLTK use  fl_color_cube(red, green, blue)
            vec_prects[vec_prects.size()-1].set_fill_color(fl_color_cube(row%5, column, row/5));

            win.attach(vec_prects[vec_prects.size()-1]);
        }

    win.wait_for_button();
 }

// ex 14
 // The right triangle class
 // Make an octagonal shape out of eight right triangles of different colors.
 void rigth_triangles()
 {

    using namespace Graph_lib;
    Simple_window win(Point(0,100), width_window-100, height_window-100,
                       "an octagonal shape out of eight right triangles of different colors");

    Point pstart{300,300};
    Point a{300,300};
    Point b{450,450};

    double cos30 = cos(30*PI/180);
    double sin30 =  sin(30*PI/180);
    // slope = rise/run
    double run = 50;
    double  slope = tan(60*PI/180);
    double rise = run*slope;

    int base=50;
    //std::cout << "slope: " << slope << '\n';
    std::cout << "2*base*cos30+base:" << 2*base*cos30+base << '\n';
    //Right_triangle rtriangle(pstart, Point(pstart.x+50, pstart.y), 60);
    //win.attach(rtriangle);

    Right_triangle rtriangle1(Point(pstart.x, pstart.y), Point(pstart.x+base, pstart.y), -60);
    //rtriangle1.set_color(fl_color_cube(1,1,1));
    rtriangle1.set_fill_color(fl_color_cube(1,1,1));
    win.attach(rtriangle1);



    Right_triangle rtriangle2(Point(pstart.x+2*base*cos30+base, pstart.y-2*base*cos30-base),
                              Point(pstart.x+2*base*cos30+base, pstart.y-2*base*cos30), 60);

    //rtriangle2.set_color(fl_color_cube(0,7,0));
    rtriangle2.set_fill_color(fl_color_cube(0,7,0));
    win.attach(rtriangle2);
    Right_triangle rtriangle3(Point(pstart.x+2*base*cos30+base, pstart.y-2*base*cos30-base),
                              Point(pstart.x+2*base*cos30+base, pstart.y-2*base*cos30), -60);
    //rtriangle3.set_color(fl_color_cube(4,7,0));
    rtriangle3.set_fill_color(fl_color_cube(4,7,0));
    win.attach(rtriangle3);

    Right_triangle rtriangle4(Point(pstart.x+2*2*base*cos30+2*base, pstart.y),
                              Point(pstart.x+2*2*base*cos30+2*base-base, pstart.y),  -60);
    //rtriangle4.set_color(fl_color_cube(1,4,1));
    rtriangle4.set_fill_color(fl_color_cube(1,4,1));
    win.attach(rtriangle4);


    Right_triangle rtriangle5(Point(pstart.x+2*2*base*cos30+2*base, pstart.y),
                              Point(pstart.x+2*2*base*cos30+2*base-base, pstart.y), 60);
    //rtriangle5.set_color(fl_color_cube(2,4,2));
    rtriangle5.set_fill_color(fl_color_cube(2,7,2));
    win.attach(rtriangle5);

    Right_triangle rtriangle6(Point(pstart.x+2*base*cos30+base, pstart.y+2*base*cos30+base),
                              Point(pstart.x+2*base*cos30+base, pstart.y+2*base*cos30), 60);
    //rtriangle6.set_color(fl_color_cube(4,0,2));
    rtriangle6.set_fill_color(fl_color_cube(4,0,2));
    win.attach(rtriangle6);
    Right_triangle rtriangle7(Point(pstart.x+2*base*cos30+base, pstart.y+2*base*cos30+base),
                              Point(pstart.x+2*base*cos30+base, pstart.y+2*base*cos30), -60);
    //rtriangle7.set_color(fl_color_cube(3,0,3));
    rtriangle7.set_fill_color(fl_color_cube(3,0,3));
    win.attach(rtriangle7);

    Right_triangle rtriangle8(Point(pstart.x, pstart.y),
                              Point(pstart.x+base, pstart.y), 60);
    //rtriangle8.set_color(fl_color_cube(4,5,4));
    rtriangle8.set_fill_color(fl_color_cube(4,5,4));
    win.attach(rtriangle8);



    Right_triangle rtriangle10(Point(pstart.x+300, pstart.y+200),
                              Point(pstart.x+300+base, pstart.y+200+base), 60);
    //rtriangle10.set_color(fl_color_cube(4,4,4));
    rtriangle10.set_fill_color(fl_color_cube(4,3,4));
    win.attach(rtriangle10);

    Right_triangle rtriangle11(Point(pstart.x+300, pstart.y+200),
                              Point(pstart.x+300+base, pstart.y+200+base), -60);
    //rtriangle11.set_color(fl_color_cube(4,4,4));
    rtriangle11.set_fill_color(fl_color_cube(4,4,4));
    win.attach(rtriangle11);

    Right_triangle rtriangle12(Point(pstart.x+400, pstart.y+200),
                               Point(pstart.x+500, pstart.y+100), -60);
    //rtriangle12.set_color(fl_color_cube(4,4,4));
    rtriangle12.set_fill_color(fl_color_cube(4,5,4));
    win.attach(rtriangle12);

    Right_triangle rtriangle13(Point(pstart.x+300, pstart.y+300),
                               Point(pstart.x+200, pstart.y+400), 60);
    //rtriangle13.set_color(fl_color_cube(4,4,4));
    rtriangle13.set_fill_color(fl_color_cube(4,5,4));
    win.attach(rtriangle13);


   /* Right_triangle rtriangle2(a,b, 30*PI/180);
    win.attach(rtriangle2);
    Right_triangle rtriangle3(a,b, 30*PI/180);
    win.attach(rtriangle3);
    Right_triangle rtriangle4(a,b, 30*PI/180);
    win.attach(rtriangle4);
    Right_triangle rtriangle5(a,b, 30*PI/180);
    win.attach(rtriangle5);
    Right_triangle rtriangle6(a,b, 30*PI/180);
    win.attach(rtriangle6);
    Right_triangle rtriangle7(a,b, 30*PI/180);
    win.attach(rtriangle7);

     */




     win.wait_for_button();
 }


void tile_right_triangles()
{

    using namespace Graph_lib;
    Simple_window win(Point(0,100), width_window-100, height_window-100,
                       "tile_right_triangles");

    Point pstart{300,300};
    Vector_ref<Right_triangle> s;

    int base=40;
    //int member=0;
    for(int member=0; member<402;) // only even numbers
    {
        pstart.x=300;
        for(int count =0; count <40; count++)
        {
            // tg 60 = vx/vy => vx=vy*tg60
            s.push_back(new Right_triangle(Point(pstart.x+base, pstart.y), Point(pstart.x, pstart.y), -60));
            s[member].set_fill_color(fl_color_cube(count%5,count%4+2,count%5));
            s[member].set_color(fl_color_cube(0,0,0));
            win.attach(s[member]);
            member++;
            s.push_back(new Right_triangle(Point(pstart.x, pstart.y-base*sqrt(3)), Point(pstart.x+base, pstart.y-base*sqrt(3)), 60));
            s[member].set_fill_color(fl_color_cube(member%3+2,member%2+5,member%5));
            s[member].set_color(fl_color_cube(0,0,0));
            win.attach(s[member]);
            member++;
            pstart.x+=base;
        }
        pstart.y+=base*sqrt(3);
    }


      //  int base=20;
    //s.push_back(new Right_triangle(Point(pstart.x+base, pstart.y), Point(pstart.x, pstart.y), -60));
    //s[0].add(Point(200,200));
    //win.attach(s[0]);
    win.wait_for_button();

}
