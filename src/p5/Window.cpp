// updated Mon Apr 15 17:16:51 PDT 2019

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory>
#include <cassert>
#include "Window.h"
#include "Symbol.h"
#ifdef P5
#include "Locator.h"
#endif
#include "Game_object.h"
#include "Scope_manager.h"
#include "Event_manager.h"

#include <GL/gl.h>
#include <GL/freeglut.h>

extern Window *window;

extern void user_quit_program();

int clock_tick;

void draw_all_game_objects()
{
  glClear(GL_COLOR_BUFFER_BIT);
  Game_object::draw_all_game_objects();
  glutSwapBuffers();
}

// if the window is resized, must redraw
void window_reshape_callback(int width, int height)
{
  #ifdef P5
    window->set_width(width);
    window->set_height(height);
    draw_all_game_objects();
  #endif
}

// called when windowing-system determines the graphics in the window
// may be out of date
void window_visibility_callback(int state)
{
  draw_all_game_objects();
}

void draw_callback()
{
  // only redraw the game objects if one of them has changed
  // Note: if any field of any game object has changed since the last
  // time the screen was drawn, graphics_out_of_date_with_last_rendering()
  // will return true
  if (Game_object::graphics_out_of_date_with_last_rendering())
  {
    draw_all_game_objects();
  }
}

void timer_callback(int value)
{
  // std::cout << "timer_callback()" << std::endl;

  Game_object::animate_all_game_objects();
  draw_callback();

  // glut timer functions must be re-registered each time
  glutTimerFunc(clock_tick, timer_callback, 0);
}

void keyboard_callback(unsigned char key, int x, int y)
{
  Event_manager& event_manager = Event_manager::instance();
  switch (key)
  {
    case ' ' : event_manager.execute_handlers(Window::SPACE);
         break;
    case 'A' :
    case 'a' : event_manager.execute_handlers(Window::AKEY);
         break;
    case 'S' :
    case 's' : event_manager.execute_handlers(Window::SKEY);
         break;
    case 'D' :
    case 'd' : event_manager.execute_handlers(Window::DKEY);
         break;
    case 'F' :
    case 'f' : event_manager.execute_handlers(Window::FKEY);
         break;
    case 'H' :
    case 'h' : event_manager.execute_handlers(Window::HKEY);
         break;
    case 'J' :
    case 'j' : event_manager.execute_handlers(Window::JKEY);
         break;
    case 'K' :
    case 'k' : event_manager.execute_handlers(Window::KKEY);
         break;
    case 'L' :
    case 'l' : event_manager.execute_handlers(Window::LKEY);
         break;
    case 'W' :
    case 'w' : event_manager.execute_handlers(Window::WKEY);
         break;
    case 'Z' :
    case 'z' : event_manager.execute_handlers(Window::ZKEY);
         break;
    case 'Q' :
    case 'q' :
         user_quit_program();
        glutLeaveMainLoop();
  }
}

void special_callback(int key, int x, int y)
{
  Event_manager& event_manager = Event_manager::instance();
  switch (key)
  {
    case GLUT_KEY_F1:
      event_manager.execute_handlers(Window::F1);
      break;
    case GLUT_KEY_UP:
      event_manager.execute_handlers(Window::UPARROW);
      break;
    case GLUT_KEY_DOWN:
      event_manager.execute_handlers(Window::DOWNARROW);
      break;
    case GLUT_KEY_LEFT:
      event_manager.execute_handlers(Window::LEFTARROW);
      break;
    case GLUT_KEY_RIGHT:
      event_manager.execute_handlers(Window::RIGHTARROW);
      break;
  }
}

// update mouse_x and/or mouse_y if they exist in symbol_table
void update_mouse_x_y_in_symbol_table(int x, int y)
{
  #ifdef P5
    Scope_manager& scope_manager = Scope_manager::instance();
    std::shared_ptr<Symbol> symbol = scope_manager.lookup("mouse_x");
    if (symbol != nullptr && symbol->get_type() == GPL::INT)
      symbol->as_lvalue()->mutate(x);
  
    symbol = scope_manager.lookup("mouse_y");
    if (symbol != nullptr && symbol->get_type() == GPL::INT)
      // GLUT origin is top left, gpl origin is bottom left
      symbol->as_lvalue()->mutate(window->height() - y);
  #endif
}

void mouse_callback(int button, int state, int x, int y)
{
  Event_manager& event_manager = Event_manager::instance();
  assert(window != NULL);
  update_mouse_x_y_in_symbol_table(x,y);
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    event_manager.execute_handlers(Window::LEFTMOUSE_UP);
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    event_manager.execute_handlers(Window::LEFTMOUSE_DOWN);
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
    event_manager.execute_handlers(Window::MIDDLEMOUSE_UP);
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    event_manager.execute_handlers(Window::MIDDLEMOUSE_DOWN);
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    event_manager.execute_handlers(Window::RIGHTMOUSE_UP);
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    event_manager.execute_handlers(Window::RIGHTMOUSE_DOWN);

  // else ignore this event

}

void motion_callback(int x, int y)
{
  Event_manager& event_manager = Event_manager::instance();
  assert(window != NULL);
  update_mouse_x_y_in_symbol_table(x,y);
  event_manager.execute_handlers(Window::MOUSE_DRAG);
}

void passive_motion_callback(int x, int y)
{
  Event_manager& event_manager = Event_manager::instance();
  assert(window != NULL);
  update_mouse_x_y_in_symbol_table(x,y);
  event_manager.execute_handlers(Window::MOUSE_MOVE);
}

void read_keypresses_from_standard_input_callback()
{
  while (true)
  {
    // skip whitespace (except actual spaces, they are legal input)
    while (isspace(std::cin.peek()) && std::cin.peek() != ' ')
      std::cin.ignore();

    char keypress;
    std::cin.get(keypress);

    // if there was a problem (such as reaching EOF) stop
    if (!std::cin.good())
      break;

    Event_manager& event_manager = Event_manager::instance();
    switch(keypress)
    {
      case 6:  // ^F
        event_manager.execute_handlers(Window::F1);
        break;
      case 1:  // ^A
        event_manager.execute_handlers(Window::UPARROW);
        break;
      case 2: // ^B
        event_manager.execute_handlers(Window::DOWNARROW);
        break;
      case 4: // ^D
        event_manager.execute_handlers(Window::LEFTARROW);
        break;
      case 3: // ^C
        event_manager.execute_handlers(Window::RIGHTARROW);
        break;
      default:
        keyboard_callback(keypress, 0, 0);
    }
    draw_callback();
  }

  // only call this function the first time we are idle
  // it is assumed that all the commands will have been read by now
  glutIdleFunc(0);
}

Window::Window(int x, int y, int w, int h, std::string title, int speed,
               double red, double green, double blue,
               bool read_keypresses_from_standard_input /* = false */
              )
{
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_title = title;
  m_read_keypresses_from_standard_input = read_keypresses_from_standard_input;

  if (speed > 100)
    speed = 100;
  if (speed < 1)
    speed = 1;

  // This formula sets up the meaning of the speed
  // Speed is very machine dependent, this may have to be changed
  // for very fast or very slow machine

  // special case, low speeds are really slow for debugging
  if (speed <= 10)
    clock_tick = (11 - speed) * 1000;
  else clock_tick = ((103 - speed) * (103 - speed))/10;

  // glut can be controlled by command line arguments pass to glutInit().
  // In order to simplify argument parsing in gpl.cpp, command line
  // arguments are not passed to glutInit()
  int phony_argc = 1;
  char* phony_argv[2];
  char bobby[4]{"gpl"};
  phony_argv[0] = bobby;
  phony_argv[1] = 0;

  glutInit(&phony_argc,phony_argv);
  //free(phony_argv[0]);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(m_w,m_h);
  glutInitWindowPosition(m_x,m_y);

  glutCreateWindow(m_title.c_str());

  // if we are suppose to read characters from the command line
  // (this is a testing/debugging tool)
  if (m_read_keypresses_from_standard_input)
    // use an idle function to read the commands
    glutIdleFunc(read_keypresses_from_standard_input_callback);

  // redraws all objects if window is changed by windowing system
  glutReshapeFunc(window_reshape_callback);
  glutVisibilityFunc(window_visibility_callback);

  glutDisplayFunc(draw_callback);
  glutTimerFunc(clock_tick, timer_callback, 0);
  glutKeyboardFunc(keyboard_callback);
  glutSpecialFunc(special_callback);

  glutMouseFunc(mouse_callback);
  glutMotionFunc(motion_callback);
  glutPassiveMotionFunc(passive_motion_callback);

  glViewport(0, 0, m_w, m_h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, m_w, 0, m_h);
  glClearColor (red, green, blue, 0.0);
}

void Window::set_width(int width)
{
  #ifdef P5
    Scope_manager& scope_manager = Scope_manager::instance();
    m_w = width;
  
    // if there is an INT symbol window_width, update it
    std::shared_ptr<Symbol> symbol = scope_manager.lookup("window_width");
    if (symbol != nullptr && symbol->get_type() == GPL::INT)
      symbol->as_lvalue()->mutate(width);
  #endif
}

void Window::set_height(int height)
{
  #ifdef P5
    Scope_manager& scope_manager = Scope_manager::instance();
    m_h = height;

    // if there is an INT symbol window_height, update it
    std::shared_ptr<Symbol> symbol = scope_manager.lookup("window_height");
    if (symbol != nullptr && symbol->get_type() == GPL::INT)
      symbol->as_lvalue()->mutate(height);
  #endif
}

// dump the current front openGL color buffer to 
// the given file (Written by Johnathan Smith)
void Window::dump_pixels(const char *dumpwindow_filename)
{
  assert(dumpwindow_filename);

  // Allocate new byte array, bail if that doesn't happen
  std::shared_ptr<char> pixels(new char[m_w * m_h * 3]);

  // Set front buffer to be read and read buffer into pixels
  glReadBuffer(GL_FRONT);
  //glReadPixels(0, 0, m_w, m_h, GL_RGB, GL_UNSIGNED_BYTE, pixels.get());
  glReadPixels(0, 0, m_w, m_h, GL_RGB, GL_BYTE, pixels.get());

  // Open output file for text writing, bail if that doesn't happen
  FILE* outputFile = fopen(dumpwindow_filename, "w");
  assert(outputFile);

  // Start at top left of frame buffer (for the hell of it) and spit out
  // each byte in the array as a char.
  for (int i = m_h-1; i >= 0; i--)
    for (int j = 0 ; j < m_w; j++)
      for(int k = 0; k < 3; k++)
        fprintf(outputFile, "%c", pixels.get()[i*m_w+j+k]);
  fclose(outputFile);

}

void Window::initialize()
{
  Event_manager& event_manager = Event_manager::instance();
  event_manager.execute_handlers(Window::INITIALIZE);
}

void Window::main_loop()
{
  glutMainLoop();
//tagger  glutLeaveMainLoop(); INVESTIGATE THIS
}
