//compile: gcc inputfile.c -lX11 -lXtst -o opfile
// gcc sample.c -lX11 -lXtst

#include"XlibMouse.h"

int main()
{
XlibMouseStart();
for(;;)
{
int x,y;
scanf("%d %d",&x,&y);
if(x==0&&y==0) break;
// mouseclick(x,y,LeftClick);
getMouseLoc(&x,&y);
printf("%d %d \n",x,y);
}
XlibMouseEnd();
}
