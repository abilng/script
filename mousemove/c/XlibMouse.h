/*
 *
 *
 *
 *compile using : gcc inputfile.c -lX11 -lXtst -o opfile
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

#define LeftClick 1
#define RightClick 3
#define False 0
#define True 1
#define DEFAULT_DELAY 12

Display *displayMain;

void XlibMouseStart();
/**
 *should call before first mouse function call
 */
void XlibMouseEnd();
/**
 * should call before end of prg
 */
int mouseMove(int x, int y,int screen);
/**
 * Move Mouse 
 * @param screen should be 0 (Default screen) if not used
 */
int mouseButton(Window window, int button, int is_press);
/**
 *for pressing or releasing button 
 * @param button (1,2,3,4,5) use LeftClick(1) or RightClick(3)
 * @param is_press True (press) or False (release)
 */

int mouseUp(int x,int y, int button); 
/**
 *for release mouse 
 *@param x,y -coordinate of point at which mouse is released
 *@param button type -LeftClick or RightClick
 */

int mouseDown(int x,int y, int button);
/**
 *for pressing mouse 
 *@param x,y -coordinate of point at which mouse is pressed
 *@param button type -LeftClick or RightClick
 */


int mouseClick(int x,int y, int button);
/**
 *for a single click 
 *@param x,y -coordinate of point
 *@param button type -LeftClick or RightClick
 */
int getMouseloc(int *x,int *y);
/**
 *return current position of mouse
 *@param x,y -return values
 */

void XlibMouseStart()
{
  displayMain= XOpenDisplay(NULL);
  if(displayMain == NULL)
	{
	  fprintf(stderr, "Can't Open Display !!!\n");
	  exit(EXIT_FAILURE);
	}
  
}
void XlibMouseEnd()
{
  if(displayMain != NULL)
    XCloseDisplay(displayMain);
}

int mouseMove(int x, int y,int screen)
{
  if(displayMain == NULL) XlibMouseStart();
  int ret=0;
  Window screen_root = RootWindow(displayMain, screen);
  ret = XWarpPointer(displayMain, None, screen_root, 0, 0, 0, 0, x, y);
  XFlush(displayMain);
  return ret;
}

int mouseButton(Window window, int button, int is_press)
{
  if(displayMain == NULL) XlibMouseStart();
  int ret = 0;
  ret = XTestFakeButtonEvent(displayMain, button, is_press, CurrentTime);
  XFlush(displayMain);
  return ret;
}

int mouseUp(int x,int y, int button) 
{
  if(displayMain == NULL) XlibMouseStart();
  Window screen_root = RootWindow(displayMain, 0);
  XWarpPointer(displayMain, None, screen_root, 0, 0, 0, 0, x, y);
  return mouseButton(None,button, False);
}

int mouseDown(int x,int y, int button) 
{
  if(displayMain == NULL) XlibMouseStart();
  Window screen_root = RootWindow(displayMain, 0);
  XWarpPointer(displayMain, None, screen_root, 0, 0, 0, 0, x, y);
  return mouseButton(None, button, True);
}

int mouseClick(int x,int y, int button)
{
  mouseDown(x,y,button);
  usleep(DEFAULT_DELAY);
  mouseUp(x,y,button);
}
int getMouseLoc(int *x,int *y)
{
  int ret;
  Window window = 0;
  Window root = 0;
  int win_x_return,win_y_return;
  unsigned int mask_return;
  Screen *screen = ScreenOfDisplay(displayMain, 0);
  ret=XQueryPointer(displayMain, RootWindowOfScreen(screen) ,&root, &window,x,y, &win_x_return, &win_y_return,&mask_return);
  return ret;
}
