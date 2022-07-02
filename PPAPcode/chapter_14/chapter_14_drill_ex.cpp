#include <iostream>
#include <vector>
#include <math.h>
#include <memory>
#include <Simple_window.h> // get access to our window library
#include <Graph.h>

 const int width_window = 1920;
 const int height_window = 1080;

 void Smiley_Frowny();
 void immobile_Circle();
 void striped_rectangle();
 void striped_circle();
 void striped_closed_polyline();
 void octagon();
 
 void draw_Binary_tree();
 void printIterator();
 void group_shape();
 void change_color_squares(Fl_Color first, Fl_Color second, Graph_lib::Group& tiles);
 void shows_Tiles();
 void use_Controller();
 void use_S_Controller();
 void exception_hierarchy();


 class Iterators
 {
 public:
     Iterators(){}
     virtual double* next() = 0;
     
 };

 class Vector_iterator : public Iterators
 {
     long num{0};
 public:
     Vector_iterator(std::vector<double> vec) : v { vec } {  }
     virtual double* next() 
     {
         return  ((v.size()-num) > 0) ? &v[num++] : nullptr;
        
         // if (v.size() - num > 0) {
         //    return   &v[num++];
         //}
         //return nullptr;
     }
     std::vector<double> v;
     virtual ~Vector_iterator() {}
 };

 class List_iterator : public Iterators
 {
     long num{0};
     std::list<double>::iterator it;
 public:
     List_iterator(std::list<double> list) : l{ list } { 
         it =  l.begin() ;
     }
     virtual double* next() 
     {       
         if (l.size() - num > 0) {
             auto temp =  &*it;
             num++;
             it++;
             return  temp;
           }
         return nullptr;
         
     }  
     std::list<double> l;     
     virtual ~List_iterator() {}
 };

 void print(Iterators& it);


 class A
 {
 public:
     
     A() {}
     virtual double g() = 0;
 };

 class B:public A
 {
     double d;
 public:

     B(double dd) :d{ dd } {}
     virtual double g() { return d; }
 };

 class C :public A
 {
     double d;
 public:

     C(double dd) :d{ dd } {}
     virtual double g() { return d; }
 };

 


 int chapter_14_drill_ex()
try
{
    /*using namespace Graph_lib;
    Graph_lib::Simple_window win(Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Graph_lib::Immobile_Circle circle_immobile(Point{400, 300}, 40);
    // circle_immobile.move(20,20); // protected in this context :_)
    win.attach(circle_immobile);
    */



   // Smiley_Frowny();
    //immobile_Circle();
    //striped_rectangle();
    //striped_circle();
    striped_closed_polyline();
    //octagon();
    //group_shape();
    //shows_Tiles();
     //draw_Binary_tree();
    // printIterator();
     //use_S_Controller();
    // use_Controller();
     //exception_hierarchy();
    
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


void exception_hierarchy()
{
    using namespace Graph_lib;
    Graph_lib::Simple_window win(Graph_lib::Point(100, 100),
        width_window - 1000, height_window - 500, "My window");

    Point p{ 400,40 };
    int size = 100;
    Graph_lib::Text_Box root_exception(p, size, "exception");
    Graph_lib::Text_Box logic_er(Point(p.x-2*size, p.y+size), size, "logic_error");
    Graph_lib::Text_Box runtime_er(Point(p.x, p.y + size), size, "runtime_error");
    Graph_lib::Text_Box bad_type(Point(p.x+2*size, p.y + size), size, "bad_typeid");

    root_exception.set_color(fl_color_cube(3, 5, 2)); //..color_cube(3, 5, 2) - gold 
    root_exception.b.set_color(fl_color_cube(3, 5, 2));
    logic_er.set_color(fl_color_cube(3, 5, 2));
    logic_er.b.set_color(fl_color_cube(3, 5, 2));
    runtime_er.set_color(fl_color_cube(3, 5, 2));
    runtime_er.b.set_color(fl_color_cube(3, 5, 2));
    bad_type.set_color(fl_color_cube(3, 5, 2));
    bad_type.b.set_color(fl_color_cube(3, 5, 2));


    win.color(fl_color_cube(3, 3, 3));  //..color_cube(3, 3, 3) - pink
    win.attach(root_exception);
    win.attach(logic_er);
    win.attach(runtime_er);
    win.attach(bad_type);
    win.wait_for_button();
}


void use_Controller()
{
    using namespace Graph_lib;
    Graph_lib::Simple_window win(Graph_lib::Point(100, 100),
        width_window - 1000, height_window - 500, "My window");
    Point p(50, 50);
    
    Graph_lib::Binary_tree_triangle tree(3, 20, Point(50, 50));
   // tree.set_color(Color::black);

    for (int i = 0; i < tree.gtext.size(); i++)
    {
        Graph_lib::Text& txt_tmp=(Graph_lib::Text&) tree.gtext[i];
        
        std::ostringstream ost;
        ost <<  i ;
        std::cout << "adress" << &tree.gtext[0] << '\n'
            << "adress" << &txt_tmp << '\n';
        txt_tmp.set_label(ost.str());

        
    }
        
    tree.gtext.set_color(Color::dark_blue);
    Shape_Controller node_Control0(tree.c[0]);
    node_Control0.off();
    node_Control0.show();   

    Shape_Controller node_Control1(tree.c[1]);
    node_Control1.show();


    

    Graph_lib::Arc arcShape(p, 50, 50, 30, 240);
    arcShape.set_color(Color::blue);
    Shape_Controller shpCnt(arcShape);
    shpCnt.show();


    win.attach(tree);
    win.attach(arcShape);
    win.wait_for_button();

    node_Control0.on();
    node_Control0.show();

    node_Control1.set_level(149);
    node_Control1.set_fill_level(144);
    node_Control1.show();
    shpCnt.off();
    shpCnt.show();
    win.wait_for_button();
    
    
    shpCnt.on();
    shpCnt.set_level(125);
    shpCnt.set_fill_level(183);
    shpCnt.show();

    node_Control0.set_level(129);
    node_Control0.set_fill_level(134);
    node_Control0.show();
    node_Control1.show();
    win.wait_for_button();
}

void use_S_Controller()
{
    Graph_lib::S_Controller c(21, true);
    Graph_lib::Controller_Status cs(c);
    Graph_lib::test_Controller_Status tcs(c);
    c.show();
    cs.show();
    tcs.show();
    
    c.set_level(18);
    c.off();
    c.show();
    cs.show();
    tcs.show();
}

void print(Iterators& it)
{
    auto ptemp = it.next();
    do {
        if (ptemp == nullptr)
            std::cout << " next() returns address: nullptr" << '\n';
        else
            std::cout << " next() returns address: " << ptemp << '\n';
        ptemp = it.next();
    } while (ptemp != nullptr);

}

void printIterator()
{

    //std::vector<std::unique_ptr<A>> a;
    //for (int c = 0; c < 6;)
    //{
    //    a.push_back(std::make_unique<B>(2.5+c));
    //    c++;
    //    a.push_back(std::make_unique<C>(2.5 + c));
    //    c++;
    //
    //}
    //for(auto& v:a)
    //    std::cout << "ss" << (v->g()) << '\n';

    
    //std::unique_ptr<List_iterator> s = std::make_unique<List_iterator>(2.6);
    
    std::list<double>s2{ 3.5 };
    std::list<double>s3;
    std::vector<double>s4{3.5,4.5,5.5};
    
    std::vector<std::unique_ptr<Iterators>> s;
    s.push_back(std::make_unique<List_iterator>(s2));
    s.push_back(std::make_unique<List_iterator>(s3));
    s.push_back(std::make_unique<Vector_iterator>(s4));
    for (int c = 0; c < 6;)
    {
        s.push_back(std::make_unique<List_iterator>(std::list<double> {c+2.5, c+3.5, c+4.5}));
        
        c++;
        s.push_back(std::make_unique<Vector_iterator>(std::vector<double> { c + 2.6, c + 3.6, c + 4.6 }));
        c++;
        
    }
    //Using Abstract class pointer to derived class to call (v->next()) ;
    for (auto& v : s)
    {
        print(*v);
    }
        
}

void draw_Binary_tree() // 11,12,14
{
    using Graph_lib::Point;
    Graph_lib::Simple_window win(Graph_lib::Point(100, 100),
        width_window - 1000, height_window - 500, "My window");
    
    //Graph_lib::Binary_tree_triangle s(5, 20);
    //win.attach(s);
    Graph_lib::Binary_tree bt(6, 50, Point(200,50));
    for(int count=0; count<bt.c.size(); count++)
        bt.c[count].set_fill_color(fl_color_cube(4, 7, 1));
    
    win.attach(bt);
        //bt.move()

    win.wait_for_button();
}


void shows_Tiles()
// Tiles is a class with a grid (squares),
// default colors: blue and black for squares.
// Tilies(Point p1, Point p2, side length)
// p1 - start point, p2 - end point
// change_color_squares(Fl_Color first, Fl_Color second)
{
    Graph_lib::Simple_window win(Graph_lib::Point(100, 100),
        width_window - 1000, height_window - 500, "My window");
    Graph_lib::Tiles ts(Graph_lib::Point(80, 80), Graph_lib::Point(400, 400), 40);


    win.attach(ts);
    win.wait_for_button();
    ts.change_color_squares(fl_color_cube(4, 7, 1), fl_color_cube(2, 7, 3));
    ts.move(50, 50);
    win.wait_for_button();
}

void group_shape()
{
   // using namespace Graph_lib;
    Graph_lib::Simple_window win(Graph_lib::Point(100,100),
                    width_window-1000,height_window-500,"My window");
    Graph_lib::Group gr;
    //Graph_lib::Rectangle s(Graph_lib::Rectangle(Point(100,100),40,40));
    
    for (int dy = 0, oddy=0; dy < 200; dy += 40)
    {
        for (int dx = 0, oddx = oddy; dx < 200; dx += 40) {
            gr.add_Shape(new Graph_lib::Rectangle(Graph_lib::Point(100 + dx, 100 + dy), 40, 40));
            if (oddx % 2)
                gr[gr.size() - 1].set_fill_color(Graph_lib::Color::blue);
            else
                gr[gr.size() - 1].set_fill_color(Graph_lib::Color::black);
            ++oddx;
        }
        ++oddy;
    }        
    win.attach(gr);
    win.wait_for_button();
   
    change_color_squares(fl_color_cube(4, 7, 1), fl_color_cube(2, 7, 3), gr);
    gr.move(50, 50);
    win.wait_for_button();
    
}

void change_color_squares(Fl_Color firstc, Fl_Color secondc, Graph_lib::Group& tiles)
{
    
    for (int s=0, oddy = 0, oddx=0; s < tiles.size(); s++) {
        if (oddx % 2)
            tiles[s].set_fill_color(firstc);
        else
            tiles[s].set_fill_color(secondc);
        ++oddx;
        if (tiles.size()>s+1 && tiles[s + 1].point(0).y != tiles[s].point(0).y) {
            ++oddy;
            oddx = oddy;
        }
            
    }
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
    scp.add(Point{80,80});
    scp.add(Point{120, 120});
    scp.add(Point{200, 150});
    scp.add( Point{10,130});

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
    Smiley_hat sh(Point(300, 100), 50);
    win.attach(sh);
    //win.attach(m);
    //win.attach(fy);

    //Smiley_hat sh(Point(300,200), 50);
    //win.attach(sh);

    win.wait_for_button();
}
