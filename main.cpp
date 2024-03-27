#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std ;

#define MAXENTRIES 60000

// To determine which quarter to be filled
static int quart ;

// To prevent storing repeated points
static int xprevious , yprevious;

// To add the menu of shapes and colours on the window
void AddMenus(HWND hwnd);


// To save the points to draw the shapes and its color
/** The shape of the vector : [P1.X , P1.Y , r_P1 , g_P1 , b_P1 , P2.x , ..... ] **/
vector<int> SavePoints ;




/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HMENU hMenu;
void AddMenus(HWND hwnd);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    /** d. Try to make combination between your console and window **/
    cout << "This is a program for drawing shapes as : line , circle , ellipse , curves , square , rectangle , cardinal splines." << endl;
    cout << "Also it can fill part or all of the shape with lines , curves , circles or even clip a shape inside a rectangle "<< endl;
    cout << "or square window." << endl ;
    cout << endl ;
    cout << "These are the names & IDs of team members : " << endl;
    cout << " Name :  Nagham Mohamed  ,   ID : 20208037 " << endl ;
    cout << " Name :  Shrouk Hani     ,   ID : 20208017 " << endl;
    cout << " Name :  Rawan Reda      ,   ID : 20208013 " << endl;
    cout << " Name :  Aya Saad        ,   ID : 20208008 " << endl;
    cout << " Name :  Ghada Mamdouh   ,   ID : 20198063 " << endl << endl;

    cout << " These are some instructions / clicks steps for using this program : " << endl << endl;
    cout << "- First you have to input the points ( clicks ) then choose the colour of drawing then choose what to be drawn from the menu."<<endl <<endl;

    cout << " - For line drawing / circle drawing / circle filling ( using any algorithm ) : " << endl;
    cout << "1. Then click single left click down. " << endl;
    cout << "2. Then drag and single click up ( leave the mouse )."<<endl << endl;

    cout << "- For filling square / rectangle using curves / drawing an ellipse / point clipping ( using any algorithm ) : " << endl;
    cout << "1. Click single left click down. " << endl;
    cout << "2. Then drag and single click up ( leave the mouse )."<<endl;
    cout << "3. Then click double right click."<<endl;
    cout << "4. Then click single right click down." << endl << endl;

    cout << "- For filling using flood fill ( using any algorithm ) : " << endl;
    cout << "1. Click single left click down. " << endl;
    cout << "2. Then drag and single click up ( leave the mouse )."<<endl;
    cout << "3. Then click double right click."<<endl;
    cout << "4. Then click single right click down. " << endl<< endl;

    cout << "- For convex polygon filling / drawing cardinal splines : " << endl;
    cout << "1. Click single left click down. " << endl;
    cout << "2. Then drag and single click up ( leave the mouse )."<<endl;
    cout << "3. Then click single right click down. " << endl;
    cout << "4. Then drag and single click up ( leave the mouse )."<<endl << endl;

    cout << "- For non-convex polygon filling : " << endl;
    cout << "1. Click single left click down. " << endl;
    cout << "2. Then drag and single click up ( leave the mouse )."<<endl;
    cout << "3. Then click double right click ."<<endl;
    cout << "4. Then click single right click down. " << endl;
    cout << "5. Then drag and single click up ( leave the mouse )."<<endl << endl;

    cout << "- For line clipping using ( any algorithm ): " << endl;
    cout << "1. Click single left click down. " << endl;
    cout << "2. Then drag and single click up ( leave the mouse )."<<endl;
    cout << "3. Then click double right click ."<<endl;
    cout << "4. Then click single right click down. " << endl;
    cout << "5. Then drag and single click up ( leave the mouse )."<<endl << endl;

    cout << "- For polygon clipping : " << endl;
    cout << "1. Click single left click down. " << endl;
    cout << "2. Then drag and single click up ( leave the mouse )."<<endl;
    cout << "3. Then Click double right click down. " << endl;
    cout << "4. Then click 4 single right clicks."<<endl;

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);

    /** b. Try to change the shape of your window mouse **/
    wincl.hCursor = LoadCursor (NULL, IDC_HAND );
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */

    /** a. Change the background of window to be white **/
    wincl.hbrBackground = (HBRUSH) WHITE_BRUSH;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Computer Graphics Project"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1200,                 /* The programs width */
           800,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    //HWND hwnd = CreateWindow(TEXT("MyClass"), TEXT(""), WS_OVERLAPPEDWINDOW, 60, 60, 1800, 900, nullptr, nullptr, h, nullptr);
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


////////////////////////////////////////////////////////////////

// Function to round a a number
int Round(double x)
{
    return (int)(x+0.5);
}




/** i. Implement line algorithms [DDA, Midpoint and parametric] **/
/// To draw line using DDA line algorithm
void SimpleDDA(HDC hdc,int xs,int ys,int xe,int ye, COLORREF color)
{
    int dx = xe-xs;
    int dy = ye-ys;

    SetPixel(hdc , xs,ys,color) ;
    SavePoints.push_back(xs) ;
    SavePoints.push_back(ys) ;
    SavePoints.push_back(GetRValue(color));  // To store the r value of the color
    SavePoints.push_back(GetGValue(color));  // To store the g value of the color
    SavePoints.push_back(GetBValue(color));  // To store the b value of the color
    xprevious = xs ;
    yprevious = ys ;
    if(abs(dx) >= abs(dy))
    {
        int x = xs , xinc = dx>0?1:-1;   // if ( dy > 0 ) xinc = 1 else xinc = -1
        double y = ys , yinc = (double)dy/dx*xinc;
        while( x != xe )
        {
            x += xinc;
            y += yinc;
            SetPixel(hdc,x,Round(y),color);
            if ( x != xprevious || Round(y) != yprevious )
            {
                SavePoints.push_back(x) ;
                SavePoints.push_back(Round(y)) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = x ;
                yprevious = Round(y) ;
            }
        }
    }
    else
    {
        int y = ys , yinc = dy>0?1:-1; // if ( dy > 0 ) yinc = 1 else yinc = -1
        double x = xs , xinc = (double)dx/dy*yinc;
        while( y != ye )
        {
            x += xinc;
            y += yinc;
            if ( Round(x) != xprevious || y != yprevious )
            {
                SavePoints.push_back(Round(x)) ;
                SavePoints.push_back(y) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = Round(x) ;
                yprevious = y ;
            }
        }
    }
}


//Two functions to help in drawing the midpoint( Bresenham ) line.
void LowLine(HDC hdc,int x0,int y0,int x1, int y1,COLORREF color)
{
    // To count the number of points
    //int counter = 0 ;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int  y = y0;

    for ( int x=x0; x<x1; x++)
    {
        SetPixel(hdc,x,y,color);
        if ( x != xprevious || y != yprevious )
        {
            SavePoints.push_back(x) ;
            SavePoints.push_back(y) ;
            SavePoints.push_back(GetRValue(color));  // To store the r value of the color
            SavePoints.push_back(GetGValue(color));  // To store the g value of the color
            SavePoints.push_back(GetBValue(color));  // To store the b value of the color
            xprevious = x ;
            yprevious = y ;
        }
        if (D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx)) ;
        }
        else
            D = D + 2*dy;
    }
}


void HighLine(HDC hdc,int x0, int y0,int x1, int y1,COLORREF color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x0;

    for (int y=y0; y<y1; y++)
    {
        SetPixel(hdc,x,y,color);
        if ( x != xprevious || y != yprevious)
        {
            SavePoints.push_back(x) ;
            SavePoints.push_back(y) ;
            SavePoints.push_back(GetRValue(color));  // To store the r value of the color
            SavePoints.push_back(GetGValue(color));  // To store the g value of the color
            SavePoints.push_back(GetBValue(color));  // To store the b value of the color
            xprevious = x ;
            yprevious = y ;
        }
        if(D > 0)
        {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else
            D = D + 2*dx;
    }
}

/// To draw line using midpoint algorithm ( Bresenham's line )
void DrawMidpointLine(HDC hdc,int xc,int yc,int x,int y,COLORREF c)
{
    if (abs(y - yc) < abs(x - xc))
    {
        if (xc > x)
            LowLine(hdc,x, y, xc, yc,c);
        else
            LowLine(hdc,xc, yc, x, y,c);
    }
    else
    {
        if (yc > y)
            HighLine(hdc,x, y, xc, yc,c);
        else
            HighLine(hdc,xc, yc, x, y,c);
    }
}


/// To draw line using Parametric Line algorithm
void DrawParametricLine(HDC hdc,int xs,int ys,int xe,int ye, COLORREF color)
{
    double dx = xe-xs;
    double dy = ye - ys;
    SetPixel(hdc,xs,ys,color);
    if ( xs != xprevious || ys != yprevious )
    {
        SavePoints.push_back(xs) ;
        SavePoints.push_back(ys) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xs ;
        yprevious = ys ;
    }
    for(double t = 0; t < 1; t+=0.0001)
    {
        int x = xs + (t * dx);
        int y = ys + (t * dy);
        SetPixel(hdc, x, y,color);
        if ( Round(x) != xprevious || y != yprevious )
        {
            SavePoints.push_back(Round(x) ) ;
            SavePoints.push_back(Round(y) ) ;
            SavePoints.push_back(GetRValue(color));  // To store the r value of the color
            SavePoints.push_back(GetGValue(color));  // To store the g value of the color
            SavePoints.push_back(GetBValue(color));  // To store the b value of the color
            xprevious = Round(x) ;
            yprevious = Round(y) ;
        }
    }
}

////////////////////////////////////////////////////////////////

/** j. Implement Circle algorithms (Direct, Polar, iterative Polar, midpoint and modified Midpoint) **/

void Draw8Points(HDC hdc,int xc,int yc, int a, int b, COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);
    if ( xc+a != xprevious || yc+b != yprevious )
    {
        SavePoints.push_back(xc+a) ;
        SavePoints.push_back(yc+b) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc+a ;
        yprevious = yc+b ;
    }

    SetPixel(hdc, xc-a, yc+b, color);
    if ( xc-a != xprevious ||  yc+b != yprevious)
    {
        SavePoints.push_back(xc-a) ;
        SavePoints.push_back(yc+b) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc-a ;
        yprevious = yc+b ;
    }


    SetPixel(hdc, xc-a, yc-b, color);
    if ( xc-a != xprevious || yc-b != yprevious)
    {
        SavePoints.push_back(xc-a) ;
        SavePoints.push_back(yc-b) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc-a ;
        yprevious = yc-b ;
    }

    SetPixel(hdc, xc+a, yc-b, color);
    if ( xc+a != xprevious || yc-b != yprevious )
    {
        SavePoints.push_back(xc+a) ;
        SavePoints.push_back(yc-b) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc+a ;
        yprevious = yc-b ;
    }

    SetPixel(hdc, xc+b, yc+a, color);
    if ( xc+b != xprevious || yc+a != yprevious )
    {
        SavePoints.push_back(xc+b) ;
        SavePoints.push_back(yc+a) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc+b ;
        yprevious = yc+a ;
    }

    SetPixel(hdc, xc-b, yc+a, color);
    if ( xc-b != xprevious || yc+a != yprevious )
    {
        SavePoints.push_back(xc-b) ;
        SavePoints.push_back(yc+a) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc-b ;
        yprevious = yc+a ;
    }


    SetPixel(hdc, xc-b, yc-a, color);
    if ( xc-b != xprevious || yc-a != yprevious )
    {
        SavePoints.push_back(xc-b) ;
        SavePoints.push_back(yc-a) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc-b ;
        yprevious = yc-a ;
    }


    SetPixel(hdc, xc+b, yc-a, color);
    if ( xc+b != xprevious || yc-a != yprevious )
    {
        SavePoints.push_back(xc+b) ;
        SavePoints.push_back(yc-a) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc+b ;
        yprevious = yc-a ;
    }
}


/// To draw circle using Direct ( Cartesian ) circle algorithm
void CircleDirect(HDC hdc,int xc,int yc, int R, COLORREF color)
{
    int x = 0,y = R;
    int R2 = R*R;
    while( x < y )
    {
        x++;
        y = Round(sqrt((double)(R2-x*x)));
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}

/// To draw circle using Polar circle algorithm
 void CirclePolar(HDC hdc,int xc,int yc, int R, COLORREF color)
{
    int x = R,y = 0;
    double theta = 0,dtheta = 1.0/R;
    while(x>y)
    {
        theta += dtheta;
        x = Round(R*cos(theta));
        y = Round(R*sin(theta));
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}

/// To draw circle using Iterative Polar circle algorithm
 void CircleIterativePolar(HDC hdc,int xc,int yc, int R, COLORREF color)
{
    double x = R,y = 0;
    double dtheta = 1.0/R;
    double cdtheta = cos(dtheta),sdtheta = sin(dtheta);
    Draw8Points(hdc,xc,yc,R,0,color);
    while( x > y )
    {
        double x1 = x*cdtheta-y*sdtheta;
        y = x*sdtheta+y*cdtheta;
        x = x1;
        Draw8Points(hdc,xc,yc,round(x),round(y),color);
    }
}


/// To draw circle using Midpoint circle algorithm ( Bresenham's circle algorithm )
void CircleMidpoint(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x = 0,y = R;
    int d = 1-R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while( x < y )
    {
        if( d < 0 )
        {
            d += 2*x+2;
        }
        else
        {
            d += 2*(x-y)+5;
            y--;
        }
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}

/// To draw circle using Modified Midpoint circle algorithm
void CircleModifiedMidpoint(HDC hdc,int xc,int yc, int R, COLORREF color)
{
    int x = 0,y = R;
    int d = 1-R;
    int c1 = 3, c2 = 5-2*R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while( x < y )
    {
        if( d < 0 )
        {
            d += c1;
            c2 += 2;
        }
        else
        {
            d += c2;
            c2 +=4;
            y--;
        }
        c1 += 2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}


////////////////////////////////////////////////////////////////

/** k. Filling Circle with lines after taking filling quarter from user **/

void drawlines (HDC hdc, int xc, int yc, int x, int y,int quart ,COLORREF c)
{
    switch(quart)
    {
        case 1 :
        {
            DrawMidpointLine(hdc,xc,yc,xc+x , yc-y,c) ;
            DrawMidpointLine(hdc,xc,yc,xc+y , yc-x,c);
            break;
        }
        case 2 :
        {
            DrawMidpointLine(hdc,xc,yc,xc-x , yc-y  ,c);
            DrawMidpointLine(hdc,xc,yc,xc-y , yc-x  ,c);
            break;
        }
        case 3 :
        {
            DrawMidpointLine(hdc,xc,yc,xc-x , yc+y,c);
            DrawMidpointLine(hdc,xc,yc,xc-y , yc+x,c);
            break;
        }
        case 4 :
        {
            DrawMidpointLine(hdc,xc,yc,xc+x , yc+y ,c);
            DrawMidpointLine(hdc,xc,yc,xc+y , yc+x ,c);
            break;
        }
    }
}


void Circle_filling ( HDC hdc , int xc , int yc , double R,int quart, COLORREF color)
{
    int x = 0 ;
    int y = R ;
    double d = 1-R ;
    drawlines(hdc,xc,yc , x , y ,quart,color) ;
    while( x < y )
    {
        if ( d < 0  )
        {
            d += 2*x+3;
        }
        else
        {
            d += 2 * ( x-y)+5 ;
            y-- ;
        }
        x++ ;
        drawlines(hdc,xc,yc , x , y ,quart,color) ;
    }
}


////////////////////////////////////////////////////////////////

/** l . Filling Circle with other circles after taking filling quarter from user **/


void drawcircles (HDC hdc, int xc , int yc , int x , int y , int quart , COLORREF color)
{
    switch(quart)
    {
        case 1 :
        {
            SetPixel(hdc,xc+x,yc-y,color);
            if ( xc+x != xprevious || yc-y != yprevious )
            {
                SavePoints.push_back(xc+x) ;
                SavePoints.push_back(yc-y) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = xc+x ;
                yprevious = yc-y ;
            }

            SetPixel(hdc,xc+y,yc-x,color);
            if ( xc+y != xprevious || yc-x != yprevious )
            {
                SavePoints.push_back(xc+y) ;
                SavePoints.push_back(yc-x) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = xc+y ;
                yprevious = yc-x ;
            }
            break;
        }
        case 2 :
        {
            SetPixel(hdc,xc-x,yc-y,color);
            if ( xc-x != xprevious || yc-y != yprevious )
            {
                SavePoints.push_back(xc-x) ;
                SavePoints.push_back(yc-y) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = xc-x ;
                yprevious = yc-y ;
            }

            SetPixel(hdc,xc-y,yc-x,color);
            if ( xc-y != xprevious || yc-x != yprevious )
            {
                SavePoints.push_back(xc-y) ;
                SavePoints.push_back(yc-x) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = xc-y ;
                yprevious = yc-x ;
            }
            break;
        }
        case 3 :
        {
            SetPixel(hdc,xc-x,yc+y,color);
            if ( xc-x != xprevious || yc+y != yprevious )
            {
                SavePoints.push_back(xc-x) ;
                SavePoints.push_back(yc+y) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = xc-x ;
                yprevious = yc+y ;
            }

            SetPixel(hdc,xc-y,yc+x,color);
            if ( xc-y != xprevious || yc+x != yprevious )
            {
                SavePoints.push_back(xc-y) ;
                SavePoints.push_back(yc+x) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = xc-y ;
                yprevious = yc+x ;
            }
            break;
        }
        case 4 :
        {
            SetPixel(hdc,xc+x,yc+y,color);
            if ( xc+x != xprevious || yc+y != yprevious )
            {
                SavePoints.push_back(xc+x) ;
                SavePoints.push_back(yc+y) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = xc+x ;
                yprevious = yc+y ;
            }

            SetPixel(hdc,xc+y,yc+x,color);
            if ( xc+y != xprevious || yc+x != yprevious )
            {
                SavePoints.push_back(xc+y) ;
                SavePoints.push_back(yc+x) ;
                SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                xprevious = xc+y ;
                yprevious = yc+x ;
            }
            break;
        }
    }
}


void filledcircle ( HDC hdc , int xc , int yc , int R,int quart , COLORREF color)
{
    for(int i=0; i< R; i++)
    {
        int x = 0;
        int y = i;
        SetPixel(hdc,R, 0, color);
        if ( R != xprevious || 0 != yprevious )
        {
            SavePoints.push_back(R) ;
            SavePoints.push_back(0) ;
            SavePoints.push_back(GetRValue(color));  // To store the r value of the color
            SavePoints.push_back(GetGValue(color));  // To store the g value of the color
            SavePoints.push_back(GetBValue(color));  // To store the b value of the color
            xprevious = R ;
            yprevious = 0 ;
        }
        int d = 1 - R;
        int d1 = 3;
        int d2 = 5 - 2 * R;
        while (x < y)
        {
            if (d < 0)
            {
                d += d1;
                d1 += 2;
                d2 += 2;
                x++;
            }
            else
            {
                d += d2;
                d1 += 2;
                d2 += 4;
                x++;
                y--;
            }
            drawcircles(hdc,xc,yc,x,y,quart,color) ;
        }
    }
}


////////////////////////////////////////////////////////////////

/** m. Filling square with hermit curve ( vertical ) **/

struct Point
{
    double x, y;
    Point( double a = 0.0 , double b = 0.0): x(a), y(b) {}
};

/// To draw hermit curve
void HermitCurve ( HDC hdc , Point &p1 , Point &s1 , Point &p2 , Point &s2 , COLORREF color)
{

    double alpha1 = 2*p1.x+1*s1.x-2*p2.x+s2.x;
    double beta1 = -3*p1.x-2*s1.x+3*p2.x-s2.x;
    double gamma1= s1.x;
    double sigma1= p1.x;

    double alpha2 = 2*p1.y+1*s1.y-2*p2.y+s2.y;
    double beta2 = -3*p1.y-2*s1.y+3*p2.y-s2.y;
    double gamma2 = s1.y;
    double sigma2 = p1.y;

    for (double t=0;t<=1;t+=0.001)
    {
        double xt =(t*t*t*alpha1)+(t*t*beta1)+(t*gamma1)+sigma1;
        double yt =(t*t*t*alpha2)+(t*t*beta2)+(t*gamma2)+sigma2;
        SetPixel(hdc,round(xt),round(yt),color);
        if ( round(xt) != xprevious || round(yt) != yprevious )
        {
            SavePoints.push_back(round(xt)) ;
            SavePoints.push_back(round(yt)) ;
            SavePoints.push_back(GetRValue(color));  // To store the r value of the color
            SavePoints.push_back(GetGValue(color));  // To store the g value of the color
            SavePoints.push_back(GetBValue(color));  // To store the b value of the color
            xprevious = round(xt) ;
            yprevious = round(yt) ;
        }
    }
}


/// Function to fill a square with hermit curves
void SquareFilling( HDC hdc , double left , double right , double top , double bottom  , COLORREF c)
{
    double side_length = right - left ;
    while( left < right )
    {
        double new_x = left - side_length/16;
        Point T1( (left - new_x),  (top - (top+side_length/16)));
        Point T2( (left - new_x), (bottom - (bottom/16)));
        Point p1 ( left , top ) ;
        Point p2 ( left , bottom ) ;
        HermitCurve(hdc, p1, T1, p2, T2 , c);
        left += side_length/140;
    }
}


////////////////////////////////////////////////////////////////

/** n. Filling rectangle with bezier curve ( horizontal ) **/


// To draw bezier curve
void BezierCurve(HDC hdc,Point& p1,Point& p2,Point& p3,Point& p4,COLORREF color)
{
    for (double t=0 ; t <= 1 ; t+=0.001)
    {
        double drawX = pow(1-t,3)*p1.x+3*t*pow(1-t,2)*p2.x+3*t*t*(1-t)*p3.x+t*t*t*p4.x;
        double drawY = pow(1-t,3)*p1.y+3*t*pow(1-t,2)*p2.y+3*t*t*(1-t)*p3.y+t*t*t*p4.y;
        SetPixel(hdc,drawX,drawY,color);
        if ( drawX != xprevious || drawY != yprevious )
        {
            SavePoints.push_back(drawX) ;
            SavePoints.push_back(drawY) ;
            SavePoints.push_back(GetRValue(color));  // To store the r value of the color
            SavePoints.push_back(GetGValue(color));  // To store the g value of the color
            SavePoints.push_back(GetBValue(color));  // To store the b value of the color
            xprevious = drawX ;
            yprevious = drawY ;
        }
    }
}

/// Function to fill a rectangle with bezier curves
void RectangleFilling (HDC hdc, double left , double right , double top , double bottom , COLORREF c)
{
    double width = right - left ;
    double height = top - bottom ;
    while( top < bottom )
    {
        Point T2( (left+width/32),  (top+height/32));
        Point T1( (right-width/32), (top+height/32));
        Point P1(left, top);
        Point P2(right, top);
        BezierCurve(hdc, P1, T1, T2, P2, c ) ;
        top += width/128;
    }
}


////////////////////////////////////////////////////////////////

/** O. Convex & Non-convex filling algorithms **/

typedef struct {int xleft, xright;} Table[1000];


void swap_(Point &p1, Point &p2)
{
    Point temp;
    temp.x=p1.x;
    temp.y=p1.y;
    p1.x=p2.x;
    p1.y=p2.y;
    p2.x=temp.x;
    p2.y=temp.y;
}

void Initialize_table(Table t)
{
    for(int i=0; i<1000; i++)
    {
        t[i].xleft=INT_MAX;
        t[i].xright=-INT_MAX;
    }
}

void EdgeToTable(Point p1, Point p2, Table t)
{
    if(p1.y == p2.y)
        return;
    if(p1.y > p2.y)
        swap_(p1,p2);
    int y=p1.y;
    double x=p1.x, inverse_slope=(double)(p2.x-p1.x)/(p2.y-p1.y);
    while (y<p2.y)
    {
        if(x < t[y].xleft) //check left -->
            t[y].xleft=(int)ceil(x);
        if(x > t[y].xright) //check right <--
            t[y].xright=(int)floor(x);
        y++;
        x+=inverse_slope;
    }
}

void PolygonToTable(Point p[], int n, Table t)
{
    Point v1=p[n-1];
    for(int i=0; i<n; i++)
    {
        Point v2=p[i];
        EdgeToTable(v1, v2, t);
        v1=v2;
    }
}

void TableToScreen(HDC hdc, Table t, COLORREF c)
{
    for(int i=0; i<1000; i++)
    {
        if(t[i].xleft < t[i].xright)
            DrawMidpointLine(hdc, t[i].xleft, i, t[i].xright, i, c);
    }
}

void ConvexFill(HDC hdc, Point p[], int n, COLORREF c)
{
    Table t;
    Initialize_table(t);
    PolygonToTable(p, n, t);
    TableToScreen(hdc, t, c);
}



/// Non-convex filling algorithm

struct Points
{
    int x , y ;
};


struct EdgeRec
{
    double x;
    double minv;
    int ymax;
    bool operator< ( EdgeRec r )
    {
        return x < r.x;
    }
};
typedef list<EdgeRec> EdgeList ;

// To construct an edge record for a given edge’s end points
EdgeRec InitEdgeRec( Points& v1,Points& v2)
{
    if( v1.y > v2.y )
        swap(v1,v2);
    EdgeRec rec;
    rec.x=v1.x;
    rec.ymax=v2.y;
    rec.minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
    return rec;
}

// To initialize the edge table (an array of edge lists) from the edges of the polygon by calling InitEdgeRec for each edge
void InitEdgeTable(Points *polygon,int n, EdgeList table[] )
{
    Points v1 = polygon[n-1];
    for(int i = 0 ; i < n ; i++)
    {
        Points v2 = polygon[i];
        if( v1.y == v2.y )
        {
            v1 = v2;
            continue;
        }
        EdgeRec rec = InitEdgeRec(v1, v2);
        table[v1.y].push_back(rec);
        v1=polygon[i];
     }
}

// To fill the non-convex polygon
void GeneralPolygonFill(HDC hdc,Points *polygon,int n,COLORREF color)
{
    EdgeList *table = new EdgeList [MAXENTRIES];
    InitEdgeTable(polygon,n,table);
    int y=0;
    while( y < MAXENTRIES && table[y].size()==0)
    {
        y++;
    }
    if( y== MAXENTRIES )
        return;
    EdgeList ActiveList = table[y];
    while ( ActiveList.size()>0 )
    {
        ActiveList.sort();
        for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
        {
            int x1=(int)ceil(it->x);
            it++;
            int x2=(int)floor(it->x);
            for( int x = x1 ;x <= x2 ;x++)
            {
                SetPixel(hdc,x,y,color);
                if ( x != xprevious || y != yprevious )
                {
                    SavePoints.push_back(x) ;
                    SavePoints.push_back(y) ;
                    SavePoints.push_back(GetRValue(color));  // To store the r value of the color
                    SavePoints.push_back(GetGValue(color));  // To store the g value of the color
                    SavePoints.push_back(GetBValue(color));  // To store the b value of the color
                    xprevious = x ;
                    yprevious = y ;
                }
            }
         }
         y++;
         EdgeList::iterator it=ActiveList.begin();
         while( it != ActiveList.end())
         if( y == it-> ymax)
            it=ActiveList.erase(it);
         else
            it++;
         for( EdgeList::iterator it=ActiveList.begin(); it!=ActiveList.end() ; it++)
         {
             it->x += it->minv;
         }
         ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
     }
     delete[] table;
}


////////////////////////////////////////////////////////////////


/** p. Recursive and Non-recursive Flood Fill **/

void RecursiveFloodFill(HDC hdc,int x,int y,COLORREF bc,COLORREF fc)
{
    COLORREF c = GetPixel(hdc,x,y);
    if( c == bc || c == fc )
        return;
    SetPixel(hdc,x,y,fc);
    if ( x != xprevious || y != yprevious )
    {
        SavePoints.push_back(x) ;
        SavePoints.push_back(y) ;
        SavePoints.push_back(GetRValue(fc));  // To store the r value of the color
        SavePoints.push_back(GetGValue(fc));  // To store the g value of the color
        SavePoints.push_back(GetBValue(fc));  // To store the b value of the color
        xprevious = x ;
        yprevious = y ;
    }

    RecursiveFloodFill(hdc,x+1,y,bc,fc);
    RecursiveFloodFill(hdc,x-1,y,bc,fc);
    RecursiveFloodFill(hdc,x,y-1,bc,fc);
    RecursiveFloodFill(hdc,x,y+1,bc,fc);
}


/// Non-recursive flood fill
struct Vertex
{
    int x,y;
    Vertex(int x,int y):x(x),y(y) { }
};


void NonRecursiveFloodFill(HDC hdc, int x,int y,COLORREF Cb,COLORREF Cf)
{
    stack<Vertex> S;
    S.push(Vertex(x,y));
    while(!S.empty())
    {
        Vertex v = S.top();
        S.pop();
        COLORREF c = GetPixel(hdc , v.x,v.y);
        if( c == Cb || c == Cf)
           continue;
        SetPixel(hdc,v.x,v.y,Cf);
        if ( v.x != xprevious || v.y != yprevious )
        {
            SavePoints.push_back(v.x) ;
            SavePoints.push_back(v.y) ;
            SavePoints.push_back(GetRValue(Cf));  // To store the r value of the color
            SavePoints.push_back(GetGValue(Cf));  // To store the g value of the color
            SavePoints.push_back(GetBValue(Cf));  // To store the b value of the color
            xprevious = v.x ;
            yprevious = v.y ;
        }
        S.push(Vertex(v.x+1,v.y));
        S.push(Vertex(v.x-1,v.y));
        S.push(Vertex(v.x,v.y+1));
        S.push(Vertex(v.x,v.y-1));
    }
}


////////////////////////////////////////////////////////////////


/** q. Cardinal Spline Curve **/

void CardinalSpline(HDC hdc, Point p1, Point p2, Point p3, Point p4,int c ,COLORREF color) // n-> no. of point , c -> constant tension factor
{
    Point p31 ;
    p31.x= p3.x-p1.x;
    p31.y= p3.y-p1.y;

    Point t2;
    t2.x=(1.0-c)*2.0*(p31.x);
    t2.y=(1.0-c)*2.0*(p31.y);

    Point p42 ;
    p42.x= p4.x-p2.x;
    p42.y= p4.y-p2.y;

    Point t3;
    t3.x=(1.0-c)*2.0*(p42.x);
    t3.y=(1.0-c)*2.0*(p42.y);

    HermitCurve(hdc,p1,t2,p4,t3,color);

}

////////////////////////////////////////////////////////////////


/** r. Ellipse Algorithms [Direct, polar and midpoint] **/
void Draw4Points(HDC hdc,int xc,int yc,int x,int y,COLORREF color )
{
    SetPixel(hdc,xc+x,yc+y,color);
    if ( xc+x != xprevious || yc+y != yprevious )
    {
        SavePoints.push_back(xc+x) ;
        SavePoints.push_back(yc+y) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc+x ;
        yprevious = yc+y ;
    }


    SetPixel(hdc,xc+x,yc-y,color);
    if ( xc+x != xprevious || yc-y != yprevious )
    {
        SavePoints.push_back(xc+x) ;
        SavePoints.push_back(yc-y) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc+x ;
        yprevious = yc-y ;
    }

    SetPixel(hdc,xc-x,yc+y,color);
    if ( xc-x != xprevious || yc+y != yprevious )
    {
        SavePoints.push_back(xc-x) ;
        SavePoints.push_back(yc+y) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc-x ;
        yprevious = yc+y ;
    }

    SetPixel(hdc,xc-x,yc-y,color);
    if ( xc-x != xprevious || yc-y != yprevious )
    {
        SavePoints.push_back(xc-x) ;
        SavePoints.push_back(yc-y) ;
        SavePoints.push_back(GetRValue(color));  // To store the r value of the color
        SavePoints.push_back(GetGValue(color));  // To store the g value of the color
        SavePoints.push_back(GetBValue(color));  // To store the b value of the color
        xprevious = xc-x ;
        yprevious = yc-y ;
    }
}



/// Ellipse Direct algorithm
void elipse_direct (HDC hdc,int xc,int yc,int a,int b,COLORREF color)
{
    double x,y;
    double move_=1;
    //((x - xc) / a)^2 + ((y - yc) / b)^2 = 1 -> code of Cartesian direct algo
    for (int i = -a; i <= a; i += move_)
    {
        x=i;
        y= y = b * sqrt(1 - (x * x) / (a * a));
        Draw4Points(hdc,xc,yc,round(x),round(y),color);
    }
     for (int i = -b; i <= b; i += move_)
    {
        y = i;
        x = a * sqrt(1 - (y * y) / (b * b));
        Draw4Points(hdc,xc,yc,round(x),round(y),color);
    }
}


/// Ellipse Polar algorithm
void elipse_polar (HDC hdc,int xc,int yc,int r1,int r2,COLORREF color)
{
    double dtheta=1.0/max(r1,r2);
    double x=r1;
    double y=0;
    double theta=0;
    Draw4Points(hdc,xc,yc,x,y,color);
    while (x>0)
    {
        theta+=dtheta;
        x=r1*cos(theta);
        y=r2*sin(theta);
        Draw4Points(hdc,xc,yc,round(x),round(y),color);
    }
}


/// Ellipse Midpoint algorithm
void elipse_midpoint(HDC hdc,double xc,double yc,double a,double b,COLORREF color)
{
    double x=0;
    double y=b;
    //d1 = b^2 + a^2/4 - a^2b.
    int d1 = b * b + a * a / 4 - a * a * b;
    Draw4Points(hdc,xc,yc,x,y,color);
    while (x<=a)
    {
        //double d=((pow(((x+1.0)-xc),2.0))/(r1*r1))+((pow(((y-0.5)-yc),2.0))/(r2*r2))-1.0;
        if(d1<0)
        {
            //d1 = d1 + 2b^2x + 3b^2
            d1 = d1 + 2 * b * b * x + 3 * b * b;
            x++;
        }
        else
       {
           //d1 = d1 + 2b^2x + 3b^2 - 4a^2y + 4a^2
            d1 = d1 + 2 * b * b * x - 4 * a * a * y + 2 * a * a + 3 * b * b;
           x++;
           y--;
       }
       Draw4Points(hdc,xc,yc,round(x),round(y),color);
    }
    while (y >= 0)
    {
        if (d1 > 0)
        {
            y--;
            d1 = d1 - 4 * a * a * y + 2 * a * a;
        } else
        {
            y--;
            x++;
            d1 = d1 + 2 * b * b * x - 4 * a * a * y + 2 * a * a + 3 * b * b;
        }
       Draw4Points(hdc,xc,yc,round(x),round(y),color);
    }
}



////////////////////////////////////////////////////////////////

/** s. Clipping algorithms using Rectangle as Clipping Window[Point ,Line, Polygon] **/

union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
     };
};

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)out.left=1;
    else if(x>xright)out.right=1;
    if(y<ytop)out.top=1;
    else if(y>ybottom)out.bottom=1;
    return out;
}


void VIntersect(double xstart,double ystart,double xend,double yend,int x,double *xi,double *yi)
{
    *xi=x;
    *yi=ystart+(x-xstart)*(yend-ystart)/(xend-xstart);
}


void HIntersect(double xstart,double ystart,double xend,double yend,int y,double *xi,double *yi)
{
    *yi=y;
    *xi=xstart+(y-ystart)*(xend-xstart)/(yend-ystart);
}

/// Point Clipping
void PointClipping(HDC hdc,int x,int y,int xleft,int ytop,int xright,int ybottom,COLORREF color)
{
    if(x>=xleft && x<= xright && y>=ytop && y<=ybottom)
    {
        SetPixel(hdc,x,y,color);
        if ( x != xprevious || y != yprevious )
        {
            SavePoints.push_back(x) ;
            SavePoints.push_back(y) ;
            SavePoints.push_back(GetRValue(color));  // To store the r value of the color
            SavePoints.push_back(GetGValue(color));  // To store the g value of the color
            SavePoints.push_back(GetBValue(color));  // To store the b value of the color
            xprevious = x ;
            yprevious = y ;
        }
    }
}


/// Line  Clipping
void LineClipping(HDC hdc,int xstart,int ystart,int xend,int yend,int xleft,int ytop,int xright,int ybottom,COLORREF c)
{
    double x1=xstart,y1=ystart,x2=xend,y2=yend;
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out1.right)
                VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else if(out1.top)
                HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else
                HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x1=xi;
            y1=yi;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out2.top)
                HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out2.right)
                VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x2=xi;
            y2=yi;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    //drawing the clipped line
    if(!out1.All && !out2.All)
    {
        DrawMidpointLine(hdc,round(x1),round(y1),round(x2),round(y2),c);
    }
}

/// Polygon Clipping

bool InLeft(Point& p,double xleft)
{
    return p.x>=xleft;
}
bool InRight(Point& p,double xright)
{
    return p.x<=xright;
}
bool InTop(Point& p,double ybottom)
{
    return p.y>=ybottom;
}
bool InBottom(Point& p,double ytop)
{
    return p.y<=ytop;
}

Point VIntersect(Point& v1,Point& v2,double xedge)
{
    Point r;
    r.x=xedge;
    r.y=v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
    return r;
}
Point HIntersect(Point& v1,Point& v2,double yedge)
{
    Point r;
    r.y=yedge;
    r.x=v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
    return r;
}

typedef vector <Point> pvector;

pvector ClipWithEdge(pvector p,double edge,bool (*in)(Point &,double),Point(*intersect)(Point &,Point&,double) )
{
    pvector OutList;
    int n=p.size();
    Point v1=p[n-1];
    bool in1=in(v1,edge);
    for(int i=0; i<n; i++)
    {
        Point v2=p[i];
        bool in2=in(v2,edge);
        if(!in1 && in2)
        {
            OutList.push_back(intersect(v1,v2,edge));
            OutList.push_back(v2);
        }
        else if(in1 && in2) OutList.push_back(v2);
        else if(in1) OutList.push_back(intersect(v1,v2,edge));
        v1=v2; // to take the next edge
        in1=in2;
    }
    return OutList;
}


void SuthHodge (HDC hdc,pvector p,int xleft,int ytop,int xright,int ybottom,COLORREF c)
{
    pvector r;
    r = ClipWithEdge(p,xleft,InLeft,VIntersect);
    r = ClipWithEdge(r,xright,InRight,VIntersect);
    r = ClipWithEdge(r,ybottom,InBottom,HIntersect);
    r = ClipWithEdge(r,ytop,InTop,HIntersect);

    int n=r.size();
    Point v1 =r[n-1];
    for(int i=0; i<n; i++) // to draw lines of the pylgon after clipping
    {
        Point v2=r[i];
        DrawMidpointLine(hdc,round(v1.x),round(v1.y),round(v2.x),round(v2.y),c);
        v1=v2;
    }

}



static double xs , ys , xe , ye , r = 255 , g = 0 , b = 0 , xe2 , ye2 , x , y , x2 , y2 , xleft , xright , ytop , ybottom ;


// For convex polygon points , cardinal splines
// Points struct is used upon x , y are double numbers
Point p[4];

//  points of polygon clipped which are stored in the vector
Point P1 , P2 , P3 , P4 ;

// For non-convex polygon points
// Points struct is used upon x , y are integers
Points *s = new Points[5];

// For polygon clipping to store all of the points in a vector
pvector v ;

// Upon taking the points from the clicks ( the polygon is drawn with 4 points )
bool polygon_clipping = false ;

// To count till 4 clicks ( number of polygon clipped points )
static int counter = 0 ;

// For saving the shapes in a file
bool SaveFlag = 0 ;
fstream outdata; // outdata is like cin





//  This function is called by the Windows function DispatchMessage()
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int xPar = LOWORD(lParam);
    int yPar = HIWORD(lParam);
    switch (message)                  // handle the messages
    {
        case WM_COMMAND:
        {
            switch(wParam)
            {
                /// g. Implement save function for all data in screen
                /// To save the screen data
                case 1:
                {
                    SaveFlag = 1 ;
                    outdata.open("Project.txt"); // opens the file
                    if( !outdata )   // file couldn't be opened
                    {
                        cout<< "Error: file could not be opened" << endl;
                        exit(1);
                    }
                    cout << endl;
                    for (int i = 0 ; i  < SavePoints.size() ; i += 5 )
                    {
                        outdata << SavePoints[i] << endl;
                        outdata << SavePoints[i+1] << endl;
                        outdata << SavePoints[i+2] <<endl ;
                        outdata << SavePoints[i+3] <<endl ;
                        outdata << SavePoints[i+4] <<endl;
                    }
                    outdata.close();
                    break;
                }
                /// h. Implement load function to load data from files
                /// To load the screen data
                case 2:
                {

                    outdata.open("Project.txt"); // opens the file
                    if( !outdata )   // file couldn't be opened
                    {
                        cout<< "Error: file could not be opened" << endl;
                        exit(1);
                    }
                    // To make sure that the file is saved to be able to be loaded
                    if(true)
                    {
                        HDC hdc = GetDC(hwnd);
                        int i = 0 ;
                        int r , g , b , x , y ;
                        COLORREF color ;
                        while (!outdata.eof())
                        {
                            outdata >> x ;
                            outdata >> y ;
                            outdata >> r ;
                            outdata >> g ;
                            outdata >> b ;
                            color = RGB(r , g , b) ;
                            SetPixel(hdc,x,y,color);
                        }
                        outdata.close();
                        ReleaseDC(hwnd,hdc);
                   }
                   break;
                }
                /// f. Implement item to clear screen from shapes
                /// To clear the screen contents
                case 3:
                {
                    RECT rc;
                    GetClientRect(hwnd, &rc);
                    InvalidateRect(hwnd, &rc, TRUE);
                    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); // white color
                    HDC hdc = GetDC(hwnd);
                    FillRect(hdc, &rc, hBrush);
                    DeleteObject(hBrush);
                    ReleaseDC(hwnd, hdc);
                    std::ofstream outdata("Project.txt", std::ios::trunc);
                    if (!outdata.is_open())
                    {
                        std::cerr << "Failed to open 'Project.txt' file " << std::endl;
                    }
                    else
                    {
                        outdata.close();
                        cout << "File 'Project.txt' is cleared." << endl;
                    }
                    break;
                }
                /// To draw a line using DDA algorithm
                case 4:
                {
                    HDC hdc=GetDC(hwnd);
                    SimpleDDA(hdc,xs,ys,xe,ye,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To draw a line using midpoint algorithm
                case 5:
                {
                    HDC hdc=GetDC(hwnd);
                    DrawMidpointLine(hdc,xs,ys,xe,ye,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To draw a line using parametric line algorithm
                case 6:
                {
                    HDC hdc=GetDC(hwnd);
                    DrawParametricLine(hdc,xs,ys,xe,ye,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To draw a circle using direct algorithm
                case 7:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleDirect(hdc,xs,ys,radius,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To draw a circle using polar algorithm
                case 8:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CirclePolar(hdc,xs,ys,radius,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To draw a circle using iterative polar algorithm
                case 9:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleIterativePolar(hdc,xs,ys,radius,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To draw a circle using midpoint algorithm
                case 10:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To draw a circle using modified midpoint algorithm
                case 11:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleModifiedMidpoint(hdc,xs,ys,radius,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill the 1st quarter of a circle with lines
                case 12:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b)) ;
                    Circle_filling(hdc,xs,ys,radius,1,(r,g,b)) ; // quart = 1
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill the 2nd quarter of a circle with lines
                case 13:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b)) ;
                    Circle_filling(hdc,xs,ys,radius,2,(r,g,b)) ; // quart = 2
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill the 3rd quarter of a circle with lines
                case 14:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b)) ;
                    Circle_filling(hdc,xs,ys,radius,3,(r,g,b)) ; // quart = 3
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill the 4th quarter of a circle with lines
                case 15:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b)) ;
                    Circle_filling(hdc,xs,ys,radius,4,(r,g,b)) ; // quart = 4
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill the 1st quarter of a circle with circles
                case 16:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b)) ;
                    filledcircle(hdc,xs,ys,radius,1,(r,g,b)) ; // quart = 1
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill the 2nd quarter of a circle with circles
                case 17:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b)) ;
                    filledcircle(hdc,xs,ys,radius,2,(r,g,b)) ; // quart = 2
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill the 3rd quarter of a circle with circles
                case 18:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b)) ;
                    filledcircle(hdc,xs,ys,radius,3,(r,g,b)) ; // quart = 3
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill the 4th quarter of a circle with circles
                case 19:
                {
                    HDC hdc=GetDC(hwnd);
                    double radius=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    CircleMidpoint(hdc,xs,ys,radius,RGB(r,g,b)) ;
                    filledcircle(hdc,xs,ys,radius,4,(r,g,b)) ; // quart = 4
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill a square with hermit curves
                case 20:
                {
                    HDC hdc=GetDC(hwnd);
                    int side_length = xright - xleft ;
                    ybottom = ytop + side_length ;
                    //Drawing the square to be filled with hermit curves
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));

                    SquareFilling( hdc , xleft , xright , ytop , ybottom , RGB(r,g,b)) ;
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill a rectangle with bezier curves
                case 21:
                {
                    HDC hdc=GetDC(hwnd);
                    // Drawing a rectangle to be filled with bezier curves
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));

                    RectangleFilling( hdc , xleft , xright , ytop , ybottom , RGB(r,g,b)) ;
                    ReleaseDC(hwnd,hdc);
                    break;
                }
                /// To fill a convex polygon
                case 22 :
                {
                    HDC hdc=GetDC(hwnd);
                    ConvexFill(hdc, p, 4, RGB(r,g,b)); // the number of points of polygon = 4 ( constant )
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To fill a non-convex polygon
                case 23 :
                {
                    HDC hdc=GetDC(hwnd);
                    GeneralPolygonFill(hdc,s,5,RGB(r,g,b)); // the number of points of polygon = 5 ( constant )
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To fill a square using recursive flood fill
                case 24 :
                {
                    HDC hdc=GetDC(hwnd);
                    int side_length = xright - xleft ;
                    ybottom = ytop + side_length ;

                    //Drawing a square to be filled
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));

                    RecursiveFloodFill(hdc,x,y,RGB(r,g,b),RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break ;

                }
                /// To fill a square using non-recursive flood fill
                case 25 :
                {
                    HDC hdc = GetDC(hwnd);
                    int side_length = xright - xleft ;
                    ybottom = ytop + side_length ;
                    //Drawing a square to be filled
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));

                    NonRecursiveFloodFill(hdc,x,y,RGB(r,g,b),RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To draw a cardinal spline
                case 26 :
                {
                    HDC hdc=GetDC(hwnd);
                    CardinalSpline(hdc ,p[0],p[1],p[2],p[3],0.5,RGB(r,g,b)) ; // The tension factor ( c ) = 0.5 ( constant )
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To draw an ellipse using direct algorithm
                case 27 :
                {
                    HDC hdc=GetDC(hwnd);
                    double radius1=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    double radius2=sqrt((xe2-xs)*(xe2-xs)+(ye2-ys)*(ye2-ys));
                    elipse_direct(hdc,xs,ys,radius1,radius2,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                 /// To draw an ellipse using polar algorithm
                case 28 :
                {
                    HDC hdc=GetDC(hwnd);
                    double radius1=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    double radius2=sqrt((xe2-xs)*(xe2-xs)+(ye2-ys)*(ye2-ys));
                    elipse_polar(hdc,xs,ys,radius1,radius2,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To draw an ellipse using midpoint algorithm
                case 29 :
                {
                    HDC hdc=GetDC(hwnd);
                    double radius1=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    double radius2=sqrt((xe2-xs)*(xe2-xs)+(ye2-ys)*(ye2-ys));
                    elipse_midpoint(hdc,xs,ys,radius1,radius2,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To clip a point using square as a clipping window
                case 30 :
                {
                    HDC hdc=GetDC(hwnd);
                    int side_length = xright - xleft ;
                    ybottom = ytop + side_length ;
                    //Drawing the square window
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));

                    PointClipping(hdc,x,y,xleft,ytop,xright,ybottom,RGB(r,g,b)) ;
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To clip a line using square as a clipping window
                case 31 :
                {
                    HDC hdc=GetDC(hwnd);
                    int side_length = xright - xleft ;
                    ybottom = ytop + side_length ;
                    //Drawing the square window
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));

                    LineClipping(hdc,x,y,x2,y2,xleft,ytop,xright,ybottom,RGB(r,g,b)) ;
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To clip a polygon using square as a clipping window
                case 32 :
                {
                    HDC hdc = GetDC(hwnd);
                    int side_length = xright - xleft ;
                    ybottom = ytop + side_length ;
                    //Drawing the square window
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));
                    polygon_clipping = true ;

                    SuthHodge(hdc,v,xleft,ytop,xright,ybottom,RGB(r,g,b));
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To clip a point using rectangle as a clipping window
                case 33 :
                {
                    HDC hdc=GetDC(hwnd);
                    // Drawing a rectangle window
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));

                    PointClipping(hdc,x,y,xleft,ytop,xright,ybottom,RGB(r,g,b)) ;
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /// To clip a line using rectangle as a clipping window
                case 34 :
                {
                    HDC hdc=GetDC(hwnd);
                    // Drawing a rectangle window
                    DrawMidpointLine(hdc,xleft,ytop,xright,ytop,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ytop,xleft,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xright,ytop,xright,ybottom,RGB(r,g,b));
                    DrawMidpointLine(hdc,xleft,ybottom,xright,ybottom,RGB(r,g,b));

                    LineClipping(hdc,x,y,x2,y2,xleft,ytop,xright,ybottom,RGB(r,g,b)) ;
                    ReleaseDC(hwnd,hdc);
                    break ;
                }
                /** Shape color **/

                /// To choose the Red colour
                case 35 :
                {
                    r = 200 ;
                    g = 0 ;
                    b = 0 ;
                    break ;
                }
                /// To choose the Green colour
                case 36 :
                {
                    r = 0 ;
                    g = 150 ;
                    b = 0 ;
                    break ;
                }
                /// To choose the Blue colour
                case 37 :
                {
                    r = 0 ;
                    g = 0 ;
                    b = 150 ;
                    break ;
                }
                /// To choose the White colour
                case 38 :
                {
                    r = 150 ;
                    g = 150 ;
                    b = 150 ;
                    break ;
                }
                /// To choose the Black colour
                case 39 :
                {
                    r = 0 ;
                    g = 0 ;
                    b = 0 ;
                    break ;
                }
                /// To choose the Grey colour
                case 40 :
                {
                    r = 160 ;
                    g = 160 ;
                    b = 160 ;
                    break ;
                }
                /// To choose the Light blue colour
                case 41 :
                {
                    r = 0 ;
                    g = 150 ;
                    b = 150 ;
                    break ;
                }
                /// To choose the Brown colour
                case 42 :
                {
                    r = 102 ;
                    g = 51 ;
                    b = 0 ;
                    break ;
                }
                /// To choose the Pink colour
                case 43 :
                {
                    r = 255 ;
                    g = 52 ;
                    b = 255 ;
                    break ;
                }
                /// To choose the Violet colour
                case 44 :
                {
                    r = 150 ;
                    g = 0 ;
                    b = 150 ;
                    break ;
                }
            }
            break;
        }
        // single click
        case WM_LBUTTONDOWN:
        {
            xleft = xs = p[0].x = s[0].x = LOWORD(lParam);
            ytop  = ys = p[0].y = s[0].y = HIWORD(lParam);
            break;
        }
        case WM_LBUTTONUP:
        {
            xright = xe = p[1].x = s[1].x = LOWORD(lParam);
            ye =  p[1].y = s[1].y = HIWORD(lParam);
            break;
        }
        // double click
        case WM_RBUTTONDBLCLK:
        {
            xe2 = s[2].x = LOWORD(lParam);
            ybottom = ye2 = s[2].y = HIWORD(lParam);
            break;
        }
        // Single click
        case WM_RBUTTONDOWN:
        {
            counter ++ ;
            if ( counter == 1 )
            {
                x = p[2].x = s[3].x = LOWORD(lParam);
                y = p[2].y = s[3].y = HIWORD(lParam);
            }
            if ( counter == 2 )
            {
                P1.x = LOWORD(lParam);
                P1.y = HIWORD(lParam);
                v.push_back(P1) ;
            }
            if ( counter == 3 )
            {
                P2.x = LOWORD(lParam);
                P2.y = HIWORD(lParam);
                v.push_back(P2) ;
            }
            if ( counter == 4 )
            {
                P3.x = LOWORD(lParam);
                P3.y = HIWORD(lParam);
                v.push_back(P3) ;
            }
            if ( counter == 5 )
            {
                P4.x = LOWORD(lParam);
                P4.y = HIWORD(lParam);
                v.push_back(P4) ;
                counter = 0 ;
            }
            break;
        }
        case WM_RBUTTONUP:
        {
            x2 =  p[3].x = s[4].x = LOWORD(lParam);
            y2 =  p[3].y = s[4].y = HIWORD(lParam);
            break;
        }
        case WM_CREATE:
        {
            AddMenus(hwnd);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage (0);       // send a WM_QUIT to the message queue
            break;
        }
        default:                      // for messages that we don't deal with
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

// To create a menu for the requirements so that the user can choose from itthe color of drawing/filling and which option to be executed
void AddMenus(HWND hwnd)
{
    hMenu = CreateMenu();

    HMENU hFileMenu = CreateMenu();
    AppendMenu(hFileMenu,MF_STRING,1,"Save");
    AppendMenu(hFileMenu,MF_STRING,2,"Load");
    AppendMenu(hFileMenu,MF_STRING,3,"Clear");
    AppendMenu(hFileMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenu,"Settings");

    HMENU LineMenu = CreateMenu();
    AppendMenu(LineMenu,MF_STRING,4,"DDA");
    AppendMenu(LineMenu,MF_STRING,5,"MidPoint");
    AppendMenu(LineMenu,MF_STRING,6,"Parametric");
    AppendMenu(LineMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)LineMenu,"Line");

    HMENU CircleMenu = CreateMenu();
    AppendMenu(CircleMenu,MF_STRING,7,"Direct");
    AppendMenu(CircleMenu,MF_STRING,8,"Polar");
    AppendMenu(CircleMenu,MF_STRING,9,"Iterative Polar");
    AppendMenu(CircleMenu,MF_STRING,10,"Midpoint");
    AppendMenu(CircleMenu,MF_STRING,11,"Modified Midpoint");
    AppendMenu(CircleMenu,MF_STRING,12,"Fill the 1st quarter using lines");
    AppendMenu(CircleMenu,MF_STRING,13,"Fill the 2nd quarter using lines");
    AppendMenu(CircleMenu,MF_STRING,14,"Fill the 3rd quarter using lines");
    AppendMenu(CircleMenu,MF_STRING,15,"Fill the 4th quarter using lines");
    AppendMenu(CircleMenu,MF_STRING,16,"Fill the 1st quarter using circles");
    AppendMenu(CircleMenu,MF_STRING,17,"Fill the 2nd quarter using circles");
    AppendMenu(CircleMenu,MF_STRING,18,"Fill the 3rd quarter using circles");
    AppendMenu(CircleMenu,MF_STRING,19,"Fill the 4th quarter using circles");
    AppendMenu(CircleMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)CircleMenu,"Circle");

    HMENU SquareMenu = CreateMenu();
    AppendMenu(SquareMenu,MF_STRING,20,"Hermit Curve ( vertical )");
    AppendMenu(SquareMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)SquareMenu,"Square Filling");

    HMENU RectangleMenu = CreateMenu();
    AppendMenu(RectangleMenu,MF_STRING,21,"Bezier Curve ( horizontal )");
    AppendMenu(RectangleMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)RectangleMenu,"Rectangle Filling");

    HMENU FillingMenu = CreateMenu();
    AppendMenu(FillingMenu,MF_STRING,22,"Convex polygon filling");
    AppendMenu(FillingMenu,MF_STRING,23,"Non-convex polygon filling");
    AppendMenu(FillingMenu,MF_STRING,24,"Recursive flood fill");
    AppendMenu(FillingMenu,MF_STRING,25,"Non-Recursive flood fill");
    AppendMenu(FillingMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)FillingMenu,"Filling");

    HMENU SplinesMenu = CreateMenu();
    AppendMenu(SplinesMenu,MF_STRING,26,"Cardinal Splines ");
    AppendMenu(SplinesMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)SplinesMenu,"Splines");

    HMENU EllipseMenu = CreateMenu();
    AppendMenu(EllipseMenu,MF_STRING,27,"Direct");
    AppendMenu(EllipseMenu,MF_STRING,28,"Polar");
    AppendMenu(EllipseMenu,MF_STRING,29,"Midpoint");
    AppendMenu(EllipseMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)EllipseMenu,"Ellipse");

    HMENU SFillingMenu=CreateMenu();
    AppendMenu(SFillingMenu,MF_STRING,30,"Point");
    AppendMenu(SFillingMenu,MF_STRING,31,"Line");
    AppendMenu(SFillingMenu,MF_STRING,32,"Polygon");
    AppendMenu(SFillingMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)SFillingMenu," Square Clipping");

    HMENU RFillingMenu = CreateMenu();
    AppendMenu(RFillingMenu,MF_STRING,33,"Point");
    AppendMenu(RFillingMenu,MF_STRING,34,"Line");
    AppendMenu(RFillingMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)RFillingMenu," Rectangle Clipping");

    HMENU shape_ColorMenu = CreateMenu();
    AppendMenu(shape_ColorMenu,MF_STRING,35,"Red");
    AppendMenu(shape_ColorMenu,MF_STRING,36,"Green");
    AppendMenu(shape_ColorMenu,MF_STRING,37,"Blue");
    AppendMenu(shape_ColorMenu,MF_STRING,38,"White");
    AppendMenu(shape_ColorMenu,MF_STRING,39,"Black");
    AppendMenu(shape_ColorMenu,MF_STRING,40,"Grey");
    AppendMenu(shape_ColorMenu,MF_STRING,41,"Light Blue");
    AppendMenu(shape_ColorMenu,MF_STRING,42,"Brown");
    AppendMenu(shape_ColorMenu,MF_STRING,43,"Pink");
    AppendMenu(shape_ColorMenu,MF_STRING,44,"Violet");
    AppendMenu(shape_ColorMenu,MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)shape_ColorMenu," Shape Color");

    SetMenu(hwnd,hMenu);
}
