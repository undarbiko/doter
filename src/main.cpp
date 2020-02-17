#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Round_Button.H>
#include "Fl_Draw_Box.h"
#include <iostream>

int main(int argc, char **argv) {
  //Fl::visual(FL_RGB);
  Fl_Window *window = new Fl_Window(800,600);
  Fl_Draw_Box *box = new Fl_Draw_Box(20,20,500,500);
  Fl_Button *button = new Fl_Button(550, 20, 50, 30, "label");
  box->box(FL_UP_BOX);
  button->type(FL_NORMAL_BUTTON);
  window->end();
  window->show(argc, argv);
  int result = Fl::run();
  std::cout << "End " << result;
  return result;
}