#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double p_stdnorm(double z);

#define MU_A 170.8 
#define MU_B 169.7 
#define sigma_A 5.43 
#define sigma_B 5.5
int main(void)
{
    int i;
    double val,z1,z2,u1,b1,u2,b2,x1,x2,YUDO_A=1,YUDO_B=1;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;
    double L1=1,L2=1;

    u1=MU_A;
    b1=sigma_A;
    u2=MU_B;
    b2=sigma_B;
    

    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%lf",&val);
        
        z1=(val-u1)/b1;
        z2=(val-u2)/b2;
        x1=p_stdnorm(z1);
        x2=p_stdnorm(z2);
        YUDO_A=YUDO_A*x1;
        YUDO_B=YUDO_B*x2;
        



    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("L_A: %f\n",YUDO_A);
    printf("L_B: %f\n",YUDO_B);

    return 0;


}

double p_stdnorm(double z)
{
    return 1/sqrt(2*M_PI) * exp(-z*z/2);
}

