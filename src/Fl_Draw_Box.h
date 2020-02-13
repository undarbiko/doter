#ifndef Fl_Draw_Box_H
#define Fl_Draw_Box_H

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>

#define UPDATE_RATE 0.05
class Fl_Draw_Box: public Fl_Box {
    unsigned char* pixbuf; 
    void draw();
    ~Fl_Draw_Box();
public:
    Fl_Draw_Box(int x ,int y, int h, int w);
    // PLOT A PIXEL AS AN RGB COLOR INTO THE PIXEL BUFFER
    void PlotPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
    // MAKE A NEW PICTURE IN THE PIXEL BUFFER, SCHEDULE FLTK TO DRAW IT
    void RenderImage();
};

#endif //Fl_Draw_Box_H