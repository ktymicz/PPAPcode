//Z:\Stroustrup Code\PPP2code\Simple_window.h

// ex00 // Draw a letter: K by polygon,
// ex01 Draw a rectangle using Rectangle and polygon
// ex02 Draw a 100-by-30 Rectangle and place the text “Howdy!” inside it
// ex03  Draw your initials 150 pixels high.
        // Use a thick line. Draw each initial in a different color.
// ex 4 Draw a 3-by-3 tic-tac-toe board of alternating white and red squares
// ex05 // Draw a red ¼-inch frame around a rectangle that is three-quarters the height of your screen and two-thirds the width
//
#include "..\FLTK_PPAP\Simple_window.h" // get access to our window library
#include "..\FLTK_PPAP\Graph.h" // get access to our graphics library facilities

#include <iostream>
#include <vector>
#include <math.h>


 

const int width_window = 1920;
 const int hight_window = 1080;
 const double PI = 3.14159265;
// drill
 void drill(Graph_lib::Simple_window& win);
// ex00 // Draw a letter: K by polygon,
 void DrawK(Graph_lib::Simple_window& win);
// ex01 Draw a rectangle using Rectangle and polygon
 void drawRect(Graph_lib::Simple_window& win, Graph_lib::Point srec, Graph_lib::Point srecP, int width, int hight);
// ex 02 Draw a 100-by-30 Rectangle and place the text “Howdy!” inside it
 void drawHowdy(Graph_lib::Simple_window& win);
// ex 03 Draw your initials 150 pixels high.
// Use a thick line. Draw each initial in a different color.
 void initials(Graph_lib::Simple_window& win);
// ex 04 Draw a 3-by-3 tic-tac-toe board of alternating white and red squares
 void drawTicTacToeBoard(Graph_lib::Simple_window& win, int side_size, Graph_lib::Point startP);
// ex 05
// 3/4 screen width = 1440 , 2/3 screen hight = 720
 // // Draw a red ¼-inch frame around a rectangle that is three-quarters
 // the height of your screen and two-thirds the width
 void drawRectScreen(Graph_lib::Simple_window& win);
// ex 06
 void tooBig();
// ex 7, House
namespace House
{
    using namespace Graph_lib;
    const Point startBase{300,300};
    const int width_base = 450;
    const int hight_base = 300;
    const Point topRoof{ startBase.x+(width_base/2), startBase.y-(hight_base/2) };
    const Point topWindow1{ startBase.x+width_base/6,startBase.y+hight_base/6 };
    const Point topWindow2{startBase.x+width_base-(width_base/6+width_base/4),
                            startBase.y+hight_base/6 };
    const int window_width = width_base/4;
    const int window_hight = hight_base/4;
    const int polygons_smoke=5;
    const Point startChimney{startBase.x+((width_base/2)/2),
                                startBase.y-((hight_base/2)/2)-hight_base/6 };
    const int chimney_width=width_base/10;
    const int chimney_hight=hight_base/6;
    //const Point smoke_chimney{};
}
void drawHouse(Graph_lib::Simple_window& win);
// draw the file diagram from �12.8
void ex10(Graph_lib::Simple_window& win);
// draw a series of regular polygons one inside the other
void ex11(Graph_lib::Simple_window& win);
// signum function
double sgn(double d);
void ex12(int a, int b, double m, double n, int N);
void draw_Superelipse(double a, double b, double m, double n, int N);




int chapter_12_drill_ex()
try
{

    using namespace Graph_lib;
//using namespace Graph_lib; // our graphics facilities are in Graph_lib


 Point pWin{100,100};
 // The win is working for one at a time
 Simple_window win{pWin ,width_window-100,hight_window-100,"My window"};


 drill(win);
 //drawRect(win, Graph_lib::Point{150,150}, Graph_lib::Point{300,300}, 40, 50);
 //DrawK(win); // ex1
 //drawHowdy(win); // ex 2
 // initials(win); // ex 3
  // ex04
   //drawTicTacToeBoard(Simple_window & win, int side_size, Point startP)
   //drawTicTacToeBoard(win, 45, Point{100,100});  // ex04
 //drawRectScreen(win); // ex5
 //tooBig();// ex 6

   // drawHouse(win);
     //draw_Superelipse( 5,8,2,2,40);
/*
    arrow(Point{100,100}, Point{200,200});
    arrow(Point{100,100}, Point{500,120});
    arrow(Point{200,200}, Point{120,120});
    arrow(Point{500,100}, Point{120,120});
    arrow(Point{120,120}, Point{200,100});
    arrow(Point{10,10}, Point{90,30});


     // ex10(win);
    //ex12(8,5,2,2,40);


    arrow2(Point{100,100}, Point{200,200});
    arrow2(Point{100,100}, Point{500,120});
    arrow2(Point{200,200}, Point{120,120});
    arrow2(Point{500,100}, Point{120,120});
    arrow2(Point{120,120}, Point{200,100});
     arrow2(Point{10,10}, Point{90,30});
     */


 
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


// drill
void drill(Graph_lib::Simple_window& win)
{
    using namespace Graph_lib;
    Graph_lib::Polygon poly; // make a shape (a polygon)
    poly.add(Graph_lib::Point{ 300,200 }); // add a point, {300,200}
    poly.add(Graph_lib::Point{ 100,100 }); // add another point, {350,100}
    poly.add(Graph_lib::Point{ 100,200 }); // add a third point, {400,200}
    poly.set_color(Graph_lib::Color::red); // adjust properties of poly
    win.attach(poly); // connect poly to the window

    Graph_lib::Axis xa{ Graph_lib::Axis::x, Graph_lib::Point{20,350}, 280, 10, "x axis" }; // make a axis
    // Axis :: x means horizontal
    // starting at (20, 300)
    // 280 pixels long
    // 10 "notches"
    // label the axis "a xis"
    xa.set_color(Color::dark_blue);
    win.attach(xa); // attach xa to the window, win
    win.set_label("Canvas #2"); // attach xa to the window, win


    Axis ya{ Axis::y, Point{20,350},280,10,"y axis" };
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);
    win.attach(ya);


    Function sine{ sin,0,100,Point{20,150},1000,50,50 };
    sine.set_color(Color::magenta);
    win.attach(sine);

    Graph_lib::Polygon poly5; // make a shape (a polygon)
    poly5.add(Graph_lib::Point{ 100,250 }); // add a point, {300,200}
    poly5.add(Graph_lib::Point{ 200,225 }); // add another point, {350,100}
    poly5.add(Graph_lib::Point{ 300,225 }); // add a third point, {400,200}
    poly5.add(Graph_lib::Point{ 300,300 });
    poly5.add(Graph_lib::Point{ 200,300 });
    poly5.set_color(Graph_lib::Color::yellow);
    win.attach(poly5);


    Graph_lib::Rectangle r{ Point{25,125}, 50, 25 };
    win.attach(r);

    r.set_fill_color(Color::yellow);
    poly.set_style(Line_style(Line_style::dash, 3));
    poly5.set_fill_color(Graph_lib::Color::blue);
    poly5.set_style(Line_style(Line_style::dash, 2));


    Text t{ Point{150,150}, "Hello, graphical world!" };
    win.attach(t);
    t.set_font(Font::times_bold);
    t.set_font_size(20);
    t.set_color(Color::white);

    Image ii{ Point{325, 200}, "image.jpg" };
    win.attach(ii);

    win.wait_for_button(); // give control to the display engine
}

// ex00 // Draw a letter: K by polygon,
void DrawK(Graph_lib::Simple_window& win)
{
    using namespace Graph_lib;
    Graph_lib::Polygon poly0;  // values in pixels
    poly0.add(Point{ 25,25 });   // p0
    poly0.add(Point{ 35,25 });   // p1 x+10, yprev
    poly0.add(Point{ 45,48 });   // p2 x+10 p2.x==p8.x, y==(hight of letter/2)-2
    poly0.add(Point{ 55,25 });   // p3 x+10 p3.x==p5.x==p9.x, yprev-=23
    poly0.add(Point{ 65,25 });   // p4 x+10 p4.x==p7.x, p4.y=yprev
    poly0.add(Point{ 55,50 });   // p5  x3.x, y+(hight of letter/2)
    poly0.add(Point{ 75,75 });   // p6 p6.x = p4.x+10, p6.y=hight of letter
    poly0.add(Point{ 65,75 });   // p7 p4.x, p7.y=yprev
    poly0.add(Point{ 45,52 });   // p8 p8
    poly0.add(Point{ 55,75 });   // p9
    poly0.add(Point{ 45,75 });   // p10
    poly0.set_color(Color::red);
    win.attach(poly0);
    win.wait_for_button();
}


// ex01 Draw a rectangle using Rectangle and polygon
void drawRect(Graph_lib::Simple_window& win, Graph_lib::Point srec, Graph_lib::Point srecP, int width, int hight)
{
    Graph_lib::Rectangle rec{ srec,width,hight };
    rec.set_color(Graph_lib::Color::blue);
    win.attach(rec);

    Graph_lib::Polygon rectP;
    rectP.add(Graph_lib::Point{ srecP.x, srecP.y });
    rectP.add(Graph_lib::Point{ srecP.x + width, srecP.y });
    rectP.add(Graph_lib::Point{ srecP.x + width, srecP.y + hight });
    rectP.add(Graph_lib::Point{ srecP.x, srecP.y + hight });
    rectP.set_color(Graph_lib::Color::red);
    win.attach(rectP);
    win.wait_for_button();
}


// ex 02 Draw a 100-by-30 Rectangle and place the text “Howdy!” inside it
void drawHowdy(Graph_lib::Simple_window& win)
{
    using namespace Graph_lib;
    Graph_lib::Rectangle rec{ Point{100,100} ,100,30 };
    rec.set_color(Graph_lib::Color::blue);
    win.attach(rec);

    Graph_lib::Text t(Point{ 110,120 }, "Howdy!");

    win.attach(t);
    t.set_font(Graph_lib::Font::helvetica_bold_italic);
    t.set_color(Graph_lib::Color::dark_magenta);
    t.set_font_size(20);
    win.wait_for_button();

}
// ex 03 Draw your initials 150 pixels high.
// Use a thick line. Draw each initial in a different color.

void initials(Graph_lib::Simple_window& win)
{
    using namespace Graph_lib;
    Graph_lib::Open_polyline polyLine; // K
    polyLine.add(Point{ 100,100 });
    polyLine.add(Point{ 100, 250 });
    polyLine.add(Point{ 100,185 });
    polyLine.add(Point{ 175,100 });
    polyLine.add(Point{ 100,185 });
    polyLine.add(Point{ 175,250 });
    polyLine.set_color(Color::blue);
    polyLine.set_style(Line_style(Line_style::solid, 4));


    Graph_lib::Open_polyline polyLine2; // T
    polyLine2.add(Point{ 200,100 });
    polyLine2.add(Point{ 350,100 });
    polyLine2.add(Point{ 275,100 });
    polyLine2.add(Point{ 275,100 });
    polyLine2.add(Point{ 275,250 });

    polyLine2.set_color(Color::green);
    polyLine2.set_style(Line_style(Line_style::solid, 4));


    win.attach(polyLine);
    win.attach(polyLine2);
    win.wait_for_button();


}
// ex 04 Draw a 3-by-3 tic-tac-toe board of alternating white and red squares
void drawTicTacToeBoard(Graph_lib::Simple_window& win, int side_size, Graph_lib::Point startP)
{
    using namespace Graph_lib;
    const int size = 9;
    Point pT[size];
    int width = side_size;
    int hight = side_size;
    for (int i = 0; i < size; i++)
    {
        if (i % 3)
            pT[i].x = pT[i - 1].x + width;
        else
        {
            pT[i].x = startP.x;
        }

        if (i % 3)
            pT[i].y = pT[i - 1].y;
        else
        {
            pT[i].y = startP.y;
            startP.y += hight;
        }
    }

    Graph_lib::Rectangle rect1(pT[0], side_size, side_size);
    rect1.set_color(Color::white);
    win.attach(rect1);

    Graph_lib::Rectangle rect2(pT[1], side_size, side_size);
    rect2.set_color(Color::black);
    win.attach(rect2);

    Graph_lib::Rectangle rect3(pT[2], side_size, side_size);
    rect3.set_color(Color::white);
    win.attach(rect3);

    Graph_lib::Rectangle rect4(pT[3], side_size, side_size);
    rect4.set_color(Color::black);
    win.attach(rect4);

    Graph_lib::Rectangle rect5(pT[4], side_size, side_size);
    rect5.set_color(Color::white);
    win.attach(rect5);

    Graph_lib::Rectangle rect6(pT[5], side_size, side_size);
    rect6.set_color(Color::black);
    win.attach(rect6);

    Graph_lib::Rectangle rect7(pT[6], side_size, side_size);
    rect7.set_color(Color::white);
    win.attach(rect7);

    Graph_lib::Rectangle rect8(pT[7], side_size, side_size);
    rect8.set_color(Color::black);
    win.attach(rect8);

    Graph_lib::Rectangle rect9(pT[8], side_size, side_size);
    rect9.set_color(Color::white);
    win.attach(rect9);

    win.wait_for_button();
}
// ex 05
// 3/4 screen width = 1440 , 2/3 screen hight = 720
 // // Draw a red ¼-inch frame around a rectangle that is three-quarters
 // the height of your screen and two-thirds the width
void drawRectScreen(Graph_lib::Simple_window& win)
{
    using namespace Graph_lib;
    Graph_lib::Rectangle rect(Point{ 100,100 }, int(width_window * 0.66)
        , int(hight_window * 0.75));
    rect.set_color(Color::dark_blue);
    rect.set_style(Line_style(Line_style::solid, 15));
    win.attach(rect);
    win.wait_for_button();

}
// ex 06
void tooBig()
{
    using namespace Graph_lib;
    Simple_window win(Graph_lib::Point{ 100,100 }, width_window, hight_window + 20, "Too Big");
    Graph_lib::Rectangle rect(Point{ 0,0 }, 1920, 1090);
    rect.set_color(Color::red);
    win.attach(rect);
    win.wait_for_button();
}

void drawHouse(Graph_lib::Simple_window& win)
{
    using namespace Graph_lib;
    using namespace House;



    // base
    Graph_lib::Rectangle base(startBase, width_base, hight_base);
    base.set_color(Color::blue);
    base.set_style(Line_style(Line_style::solid, 5));
    win.attach(base);
    // roof
    Graph_lib::Polygon roof;
    roof.add(startBase);
    roof.add(topRoof);
    roof.add(Point{ startBase.x + width_base, startBase.y });
    roof.set_color(Color::dark_green);
    win.attach(roof);
    // window 1
    Graph_lib::Rectangle window1(topWindow1, window_width, window_hight);
    window1.set_color(Color::yellow);
    win.attach(window1);
    // window 2
    Graph_lib::Rectangle window2(topWindow2, window_width, window_hight);
    window2.set_color(Color::yellow);
    win.attach(window2);
    // chimney
    Graph_lib::Rectangle chimney(startChimney,
        chimney_width, chimney_hight);
    chimney.set_color(Color::black);
    win.attach(chimney);

    std::cout << "start.x+((width_base/2)/2): " << startBase.x + ((width_base / 2) / 2) << '\n'
        << "start.y-((hight_base/2)/2)-hight_base/6: "
        << startBase.y - ((hight_base / 2) / 2) - hight_base / 6 << '\n'
        << "start.x+(width_base/2): " << startBase.x + (width_base / 2) << '\n'
        << "start.y-(hight_base/2)" << startBase.y - (hight_base / 2) << '\n';



    Graph_lib::Polygon smoke_chimney;
    Point startPointSmokeChimney{ startChimney.x + chimney_width / 4, startChimney.y - chimney_hight / 4 };
    smoke_chimney.add(startPointSmokeChimney);
    smoke_chimney.add(Point{ (startChimney.x + chimney_width / 2),
                       startChimney.y });
    smoke_chimney.add(Point{ startChimney.x + int(chimney_width * 0.75),
                      startChimney.y - chimney_hight / 4 });
    smoke_chimney.set_color(Color::cyan);
    win.attach(smoke_chimney);


    win.wait_for_button();


}



// draw the file diagram from �12.8
void ex10(Graph_lib::Simple_window& win)
{
    using namespace Graph_lib;
    Graph_lib::Rectangle fltk1(Point(400, 10), 120, 40);
    fltk1.set_fill_color(Color::yellow);
    win.attach(fltk1);
    Graph_lib::Rectangle fltk2(Point(406, 16), 120, 40);
    fltk2.set_fill_color(Color::yellow);
    win.attach(fltk2);
    Graph_lib::Rectangle fltk3(Point(412, 22), 120, 40);
    fltk3.set_fill_color(Color::yellow);
    win.attach(fltk3);
    Text fltk_txt(Point(418, 42), "FLTK headers");
    win.attach(fltk_txt);

    Graph_lib::Rectangle win_rect(Point(389, 130), 166, 80);
    win_rect.set_fill_color(Color::yellow);
    win.attach(win_rect);
    Text win_txt0(Point(389, 127), "Window.h:");
    win_txt0.set_font(Font::helvetica_bold);
    win.attach(win_txt0);
    Text win_txt1(Point(395, 150), "// window interface:");
    win.attach(win_txt1);
    Text win_txt2(Point(395, 170), "class Window {...};");
    win_txt2.set_font(Font::helvetica_bold);
    win.attach(win_txt2);
    Text win_txt3(Point(395, 190), "...");
    win.attach(win_txt3);

    Open_polyline win_fltk;
    win_fltk.add(Point(472, 130));
    win_fltk.add(Point(472, 62));
    win.attach(win_fltk);
    Graph_lib::Polygon win_fltk_arw;
    win_fltk_arw.add(Point(472, 62));
    win_fltk_arw.add(Point(474, 67));
    win_fltk_arw.add(Point(470, 67));
    win_fltk_arw.set_fill_color(Color::black);
    win.attach(win_fltk_arw);

    // add rest, would be much easier if not everything were passed by reference
    // and would thus stop existing when leaving a scope

    win.wait_for_button();
}
// draw a series of regular polygons one inside the other
void ex11(Graph_lib::Simple_window& win)
{
    using namespace Graph_lib;
    Graph_lib::Polygon tri;
    tri.add(Point(200, 20));
    tri.add(Point(300, 20));
    tri.add(Point(250, 106));
    win.attach(tri);

    Open_polyline square;
    square.add(Point(200, 20));
    square.add(Point(200, 120));
    square.add(Point(300, 120));
    square.add(Point(300, 20));
    win.attach(square);

    Open_polyline pentagon;
    pentagon.add(Point(200, 20));
    pentagon.add(Point(169, 115));
    pentagon.add(Point(250, 179));
    pentagon.add(Point(331, 115));
    pentagon.add(Point(300, 20));
    win.attach(pentagon);

    Open_polyline hexagon;
    hexagon.add(Point(200, 20));
    hexagon.add(Point(150, 107));
    hexagon.add(Point(200, 194));
    hexagon.add(Point(300, 194));
    hexagon.add(Point(350, 107));
    hexagon.add(Point(300, 20));
    win.attach(hexagon);

    win.wait_for_button();
}


// signum function
double sgn(double d)
{
    if (d > 0) return 1;
    else if (d < 0) return -1;
    else return 0;
}

void ex12(int a, int b, double m, double n, int N)
{
    using namespace Graph_lib;
    const double pi = 3.14159;
    a = 100 * a;    // a = 1 corresponds to -100px to +100px
    b = 100 * b;

    Point tl(300, 25);
    Simple_window win(tl, a * 2 + 20, b * 2 + 20, "Superellipse");

    // get N points on superellipse - shift them all by Point(a,b)
    // to have them centered in the window

    vector<Point> points;

    for (double theta = 0; theta < 2 * pi; theta += 2 * pi / N) {
        double x = pow(abs(cos(theta)), 2 / m) * a * sgn(cos(theta)) + a + 10;
        double y = pow(abs(sin(theta)), 2 / n) * b * sgn(sin(theta)) + b + 10;
        points.push_back(Point(x, y));
    }

    Open_polyline interior1;
    for (int i = 0; i < points.size() / 4; ++i) {
        //interior1.add(points[i]);
        for (int j = i; j < points.size(); ++j) {
            if (i != j) {
                interior1.add(points[i]);
                interior1.add(points[j]);
            }
        }
    }
    interior1.set_color(Color::red);
    win.attach(interior1);

    Open_polyline interior2;
    for (int i = points.size() / 4; i < points.size() / 2; ++i) {
        interior2.add(points[i]);
        for (int j = i; j < points.size(); ++j) {
            if (i != j) {
                interior2.add(points[j]);
                interior2.add(points[i]);
            }
        }
    }
    interior2.set_color(Color::green);
    win.attach(interior2);

    Open_polyline interior3;
    for (int i = points.size() / 2; i < 3 * points.size() / 4; ++i) {
        interior3.add(points[i]);
        for (int j = i; j < points.size(); ++j) {
            if (i != j) {
                interior3.add(points[j]);
                interior3.add(points[i]);
            }
        }
    }
    interior3.set_color(Color::blue);
    win.attach(interior3);

    Open_polyline interior4;
    for (int i = 3 * points.size() / 4; i < points.size(); ++i) {
        interior4.add(points[i]);
        for (int j = i; j < points.size(); ++j) {
            if (i != j) {
                interior4.add(points[j]);
                interior4.add(points[i]);
            }
        }
    }
    interior4.set_color(Color::yellow);
    win.attach(interior4);

    // draw polyline
    Closed_polyline superell;
    for (int i = 0; i < points.size(); ++i)
        superell.add(points[i]);
    superell.set_style(Line_style(Line_style::solid, 4));
    win.attach(superell);

    win.wait_for_button();
}
/*
double sgn(double d)
{
    if(d)
        return 1;
    else if(d<0)
        return -1;
    else return 0;
}
*/
void draw_Superelipse(double a, double b, double m, double n, int N)
{
    using namespace Graph_lib;


    a *= 100;// a px to 100a px
    b *= 100;
    const double pi = 3.14159;
    Simple_window win(Point{ 10,10 }, 2 * b + 40, 2 * a + 40, "superelipse");


    std::vector<Point> points;

    double x;
    double y;
    Closed_polyline Super_E;
    for (double angle = 0; angle <= 2 * pi; angle += 2 * pi / N)
    {
        y = pow(abs(sin(angle)), 2 / m) * a * sgn(sin(angle));
        x = pow(abs(cos(angle)), 2 / n) * b * sgn(cos(angle));
        points.push_back(Point(x + b + 20, y + a + 20));
        //Super_E.add(Point{x+225,y+225});
    }

    const int number_links = 4;
    Open_polyline links[number_links];

    for (int lin = 0; lin < number_links; ++lin) {
        for (int i = lin * (points.size() / 4); i<int(points.size() / (4.0 / (lin + 1))); i++) {
            for (int j = i + 1; j<int(points.size() / (4.0 / (lin + 1))); j++) {

                links[lin].add(points[i]);
                links[lin].add(points[j]);

            }
        }
    }
    links[0].set_color(Color::blue);
    links[1].set_color(Color::dark_yellow);
    links[2].set_color(Color::dark_magenta);
    links[3].set_color(Color::green);
    win.attach(links[0]);
    win.attach(links[1]);
    win.attach(links[2]);
    win.attach(links[3]);

    for (int i = 0; i < points.size(); ++i)
        Super_E.add(points[i]);
    Super_E.set_style(Line_style(Line_style::solid, 2));
    win.attach(Super_E);
    win.wait_for_button();

}


