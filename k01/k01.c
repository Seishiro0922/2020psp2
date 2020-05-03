#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(double val,double ave,int i)
{return ((i-1)*ave[i-1])/i + val[i]/i;}
extern double var_online(double val, double ave,double save,int i)
{return (((i-1)*save[i-1])/i+pow(val[i],2)/i)-pow((((i-1)*ave[i-1]/i)+(val[i]/i)),2);}

int main(void)
{
    double val[i],ave,var,save;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;
    int i;
    i=0;
    save=pow(ave_online,2);

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
        i++;
        ave=ave_online(val[i],ave,i);
        var=var_online(val[i],ave,save,i);


    save=var_online(save,pow(val,2),i);



    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }
    printf("ave=%lf\n",ave);
    printf("var=%lf\n",var);


    return 0;


}

