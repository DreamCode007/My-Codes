//Rotating Pyramid in c
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
float x, y,z;
float xp, yp;
float A = 0, B = 0, C = 0;
int length = 28;
float ooz;
float xshift = 0,yshift = 10;
int dfc = 18;
int dfs = 40;
int idx;
const int width = 44 , height = 40;
float calcX(int i, int j, int k) 
{
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calcY(int i, int j, int k) 
{ 
    return j * cos (A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
}

float calcZ(int i, int j, int k) 
{ 
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

float zbuffer[width*height];
char buffer[width*height];

void calc(int i, int j, int k, char ch){
    x = calcX(i,j,k);
    y = calcY(i,j,k);
    z = calcZ(i,j,k)+dfs;
    ooz = 1/z;
    xp = (int)(width/2 - xshift+ x*dfc*ooz);
    yp = (int)(height/2 - yshift+ y*dfc*ooz);
    idx = xp + yp*width;
    if (idx >= 0 && idx < width*height)
    {
        if (ooz > zbuffer[idx])
        {
            zbuffer[idx] = ooz;
            buffer[idx] = ch;
        }    
    }
}    

int main()
{
    printf("\x1b[2J");
    while(1)
    {
        memset(buffer, ' ', width*height);
        memset(zbuffer, 0, width*height*4);
        
        for (float i = 0 ; i < length/2; i += 0.05)
        {        
            for(float k = -i; k < i; k += 0.05)
            {
                calc(i,2*i,k, '@');
                calc(-i,2*i,k, '~');
                
                
            }
                
        }
        for (float k = 0 ; k < length/2; k += 0.05)
        {        
            for(float i = -k; i < k; i += 0.05)
            {
                calc(i,2*k,k, '*');
                calc(i,2*k,-k, '$');
            }
        } 
        printf("\x1b[H");
        for (int k = 0; k < width * height; k++)
        {
            putchar((k % width) ? buffer[k] : '\n');
        }    
        //A += 0.03;
        B += 0.06; 
        //C += 0.04;
        usleep(8000*2);   
    }
    return 0;
}
