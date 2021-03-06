#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

float f1(float x);
float f2(float x);
float f3(float x);
float f4(float x);
float f5(float x);

float root(float(*f)(float), float(*g)(float), float a, float b, float eps1);
float integral(float(*f)(float), float a, float b, float eps2);

int main(int argc, char ** argv){
	float x1 = root(f3, f2, 5, 7, 0.0001);
    float x2 = root(f3, f1, 2.1, 3, 0.0001);
    float x3 = root(f2, f1, 5, 8, 0.0001);
    float s1 = integral(f1, x2, x3, 0.0001);
    float s2 = integral(f2, x1, x3, 0.0001);
    float s3 = integral(f3, x2, x1, 0.0001);
    float area = s2 + s3 - s1;
    int key1 = strcmp(argv[1],"-root");
    int key2 = strcmp(argv[1],"-area");
    int key3 = strcmp(argv[1],"-help");
	int key4 = strcmp(argv[1],"-test");
	if (!key1)
      printf("Intersection points: %1.3lf %1.3lf %1.3lf\n", x1, x2, x3);
	if (!key2)
      printf("Area: %1.3lf\n", area);
	if (!key4){
		float x4 = root(f4, f5, 0.5, 1.02, 0.0001);
	    float x5 = root(f4, f5, 2.5, 3.5, 0.0001);
		float s4 = integral(f4, x4, x5, 0.0001);
		float s5 = integral(f5, x4, x5, 0.0001);
		float inter = s4 - s5;
		printf(" funktion1: 3/(x - 4) + 4\n funktion2: 3/x\n Area1: %1.3f\n Area2: %1.3f\n Intersection points %1.3f, %1.3f\n Intersection area: %1.3f", s4, s5, x4, x5, inter);
	}
    if (!key3){
     printf(" -area \n");
     printf(" -help \n");
	 printf(" -root \n");
	 printf(" -test \n");	
    }
    return 0;
    }

float root(float(*f)(float), float(*g)(float), float a, float b, float eps1){
    float fa = f(a) - g(a);
    float fb = f(b) - g(b);
    float mid = (a + b) / 2.0;
    int first = 1;
    float fmid = f(mid) - g(mid);
    if(fa >= fb)
        first = -1;
    if(fmid > (fa + fb) / 2.0)
        first = -1;

    float c;
    float fc;
    float fc_eps;
    if(first == 1){
        c = a;
    }
    else{
        c = b;
        eps1 = -eps1;
    }
    while(1){
        if(first == 1){
            a = c;
            fa = f(a) - g(a);
        }
        else{
            b = c;
            fb = f(b) - g(b);
        }
        c = (a * fb - b * fa) / (fb - fa);
        fc = f(c) - g(c);
        fc_eps = f(c + eps1) - g(c + eps1);


    if(!(fc * fc_eps > 0))
        break;
    }
    return c;
}
float integral(float (*f)(float), float a, float b, float eps2)
{
    float h = (b - a);
    float I1 = h * (f(a) / 2.0 + f(b) / 2.0), I2;
    while (1)
    {
        I2 = I1 / h;
        float q = a + h / 2.0;
        while (q < b)
        {
            I2 += f(q);
            q += h;
        }
        h /= 2.0;
        I2 *= h;
        if (fabs(I2 - I1) < eps2)
            break;
        I1 = I2;
    }
    return I2;
}

//float f1(float x){
//    return log(x);
//}
//float f2(float x){
//    return  x*(-2) + 14;
//}
//float f3(float x){
//    return 1/((-x)+2) + 6;
//}
