#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Round_Button.H>
#include "Fl_Draw_Box.h"

int main(int argc, char **argv) {
  //Fl::visual(FL_RGB);
  Fl_Window *window = new Fl_Window(600,600);
  Fl_Draw_Box *box = new Fl_Draw_Box(20,20,500,500);
  box->box(FL_UP_BOX);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}