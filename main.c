#include<stdio.h>
#include<openacc.h>
float func(float x,float y);
int main()
{
    float sx,ex,yp,h,i,yp1,s,s1,s2,s3,s4;
    printf("Enter the value of Y(1) ::");
    scanf("%f",&yp);
    printf("Enter the value of Start x ::");
    scanf("%f",&sx);
    printf("Enter the value of End x ::");
    scanf("%f",&ex);
    printf("Enter the value of h ::");
    scanf("%f",&h);

#ifdef openacc
    #pragma openacc loop kernels reduce (:*)
#pragma openacc independent
#elif omp
    #pragma omp for parallel reduce (:*)
#pragma omp single
#endif
    for(i=sx;i<=ex+h;i=i+h)
    {
        s1 = i*yp;
        s2 = (i+(h/2))*(yp+((h/2)*s1));
        s3 = (i+(h/2))*(yp+((h/2)*s2));
        s4 = (i+h)*(yp+(h*s3));
        s = (s1+(2*s2)+(2*s3)+s4)/6;
        yp1 = yp + (h*s);
        if((int)(i*10)==(int)(ex*10))

#ifdef openacc
#pragma openacc wait
#elif omp
            #pragma omp barrier
#pragma omp master
#endif
        {
            printf("\nx=%.4f\ty=%.4f",i,yp);
            else
            printf("\nx=%.4f\ty=%.4f\ty1=%.4f\th=%.4f\ts=%.4f",i,yp,yp1,h,s);
        }
        yp = yp1;
    }
    return 0;
}
