/*
 *
 *
 *
 *compile using : gcc inputfile.c -lX11 -lXtst -o opfile
 */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#define LeftClick 1
#define RightClick 3
#define False 0
#define True 1

Display *displayMain;

void start();
/*
 *should call before first mouse function call
 */
void end();
/*
 * should call before end of prg
 */
int mouseMove(int x, int y,int screen);
/*
 * Move Mouse 
 * @param screen should be 0 if not used
 */
int mousebutton(Window window,int x,int y, int button, int is_press);


int mouseup(int x,int y, int button); 


int mousedown(int x,int y, int button);

int mouseclick(int x,int y, int button);

int getMouseloc(int *x,int *y);



void start()
{
  displayMain= XOpenDisplay(NULL);
  if(displayMain == NULL)
	{
	  fprintf(stderr, "Can't Open Display !!!\n");
	  exit(EXIT_FAILURE);
	}
  
}
void end()
{
  if(displayMain != NULL)
    XCloseDisplay(displayMain);
}

int mouseMove(int x, int y,int screen)
{
  if(displayMain == NULL) start();
  int ret=0;
  Window screen_root = RootWindow(displayMain, screen);
  ret = XWarpPointer(displayMain, None, screen_root, 0, 0, 0, 0, x, y);
  XFlush(displayMain);
  return ret;
}

int mousebutton(Window window,int x,int y, int button, int is_press)
{
  if(displayMain == NULL) start();
  int ret = 0;
  ret = XTestFakeButtonEvent(displayMain, button, is_press, CurrentTime);
  XFlush(displayMain);
  return ret;
}

int mouseup(int x,int y, int button) 
{
  if(displayMain == NULL) start();
  Window screen_root = RootWindow(displayMain, 0);
  XWarpPointer(displayMain, None, screen_root, 0, 0, 0, 0, x, y);
  return mousebutton(None,x,y, button, False);
}

int mousedown(int x,int y, int button) 
{
  if(displayMain == NULL) start();
  Window screen_root = RootWindow(displayMain, 0);
  XWarpPointer(displayMain, None, screen_root, 0, 0, 0, 0, x, y);
  return mousebutton(None,x,y, button, True);
}

int mouseclick(int x,int y, int button)
{
  mousedown(x,y,button);
  mouseup(x,y,button);
}
int getMouseloc(int *x,int *y)
{
  int ret;
  Window window = 0;
  Window root = 0;
  int win_x_return,win_y_return;
  unsigned int mask_return;
  Screen *screen = ScreenOfDisplay(displayMain, 0);
  ret=XQueryPointer(displayMain,RootWindowOfScreen(screen) ,&root, &window,x,y, &win_x_return, &win_y_return,&mask_return);
  return ret;
}
