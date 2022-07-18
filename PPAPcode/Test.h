//#pragma once
//#include <FL/Fl_GIF_Image.H>
//#include <FL/Fl_JPEG_Image.H>

//#include <Graph.h>
//#include<map>
//#include <windows.h>
/*void add_lvl()
{
    int c_count_bottom_lvl = pow(2, bottom_lvl); // how many circles at the bottom lvl, // (2^n)/2
    pbottom_lvl.x = point(0).x + shape_size * (pow(2, lvls - 1 - bottom_lvl) - 1) + 0.5 * shape_size;
    int csize = c.size();
    int dxc = 0;
    // add circles
    for (int count = 0; count < c_count_bottom_lvl; count++) {
        c.add_Shape(new Graph_lib::Circle(Point(pbottom_lvl.x + dxc, pbottom_lvl.y), shape_size / 2));
        c.set_color(Graph_lib::Color::blue);
        dxc += shape_size * pow(2, lvls - bottom_lvl);
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
            gtext.add_Shape(new Graph_lib::Text(Point(((const Circle&)c[csize + count]).point(0).x + dxt, ((const Circle&)c[csize + count]).point(0).y + dyt), ((const Text&)gtext[csize - pnodes + node]).label() + ct));
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
    // update variables values
    bottom_lvl++;
    pbottom_lvl.y += 2 * shape_size;
}
*/