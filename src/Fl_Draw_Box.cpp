#include "Fl_Draw_Box.h"
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>

// TIMER CALLBACK: CALLED TO UPDATE THE DRAWING
static void RenderImage_CB(void *userdata) {
    Fl_Draw_Box *box = (Fl_Draw_Box*)userdata;
    box->RenderImage();
    Fl::repeat_timeout(UPDATE_RATE, RenderImage_CB, userdata);
}


Fl_Draw_Box::Fl_Draw_Box(int x, int y, int w, int h):
        Fl_Box(x,y,w,h,"1234567"){
            const int ysize = this->h();
            const int xsize = this->w();
            Fl_Draw_Box::pixbuf = new unsigned char[ysize * xsize * 3];
            Fl_Draw_Box::RenderImage();
            Fl::add_timeout(UPDATE_RATE, RenderImage_CB, (void*)this);
}

Fl_Draw_Box::~Fl_Draw_Box(){
    delete[] Fl_Draw_Box::pixbuf;
}

void Fl_Draw_Box::draw(){
    const int x = this->x();//x position of top left point (from left to right)
    const int y = this->y();//y position of top left point (from top to bottom)
    const int ysize = this->h();
    const int xsize = this->w();
    fl_draw_image(Fl_Draw_Box::pixbuf, x, y, xsize, ysize, 3, xsize*3);
    std::string s = std::to_string((1.0 / Fl_Draw_Box::fps) * 1000000);
    this->copy_label(s.c_str());
    this->draw_label();
        //Fl_Box::draw();
        // int x = this->x();//x position of top left point (from left to right)
        // int y = this->y();//y position of top left point (from top to bottom)
        // int w = this->w();//weidth = xtr (top right) - xtp (top left) + 1, cant be 0, can be negative
        // int h = this->h();//height = ybl (bottom left) - ytl (top left) + 1, cant be 0, can be negative
        // fl_begin_points();
        // fl_color(255, 255, 255);
        // for (int i=y; i<y+h; i++){
        //     for (int j=x; j<x+w; j++){
        //         fl_point(j, i);
        //     }
        // }
        // fl_color(0, 0, 255);
        // fl_point(x, y);
        // fl_point(x+w-1, y+h-1);
        // for (int i=y; i<y+h; i++){
        //     fl_point(x, i);
        //     fl_point(x+w, i);
        // }
        // for (int j=x; j<x+w; j++){
        //     fl_point(j, y);
        //     fl_point(j, y+h);
        // }
        // fl_end_points();
}

// PLOT A PIXEL AS AN RGB COLOR INTO THE PIXEL BUFFER
void Fl_Draw_Box::PlotPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    const int ysize = this->h();
    const int xsize = this->w();
    *(Fl_Draw_Box::pixbuf + y*xsize*3 + x*3 + 0) = r;
    *(Fl_Draw_Box::pixbuf + y*xsize*3 + x*3 + 1) = g;
    *(Fl_Draw_Box::pixbuf + y*xsize*3 + x*3 + 2) = b;
}

// MAKE A NEW PICTURE IN THE PIXEL BUFFER
void Fl_Draw_Box::RenderImage() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    static unsigned char drawcount = 0;
    const int ysize = this->h();
    const int xsize = this->w();
    for ( int x=0; x<xsize; x++ )
        for ( int y=0; y<ysize; y++ )
            Fl_Draw_Box::PlotPixel(x, y, x+drawcount, y+drawcount, x+y+drawcount);
            //Fl_Draw_Box::PlotPixel(x, y, 255, 0, 0);
    ++drawcount;
    Fl_Draw_Box::redraw();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    Fl_Draw_Box::fps = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    //std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}