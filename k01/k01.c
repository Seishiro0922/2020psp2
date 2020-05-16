#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(int i,double val,double ave)
{ ave=1;
  ave=(i-1)*ave/i+val/i;
  return ave;     
}
extern double var_online(int i,double val, double ve,double save,double var)
{  save=1;
   ve=1;
   var=(((i-1)*save/i)+val*val/i)-pow((((i-1)*ve/i)+val/i),2);
   save=(i-1)*save/i+val*val/i;
   ve=(i-1)*ve/i+val/i;
    return var;
}


int main(void)
{   
    int i=0;
    double val,ave,save,var,A1,A2,u,x,ve;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;

    

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

        A1=ave_online(i,val,ave);
        A2=var_online(i,val,save,ve,var);

        
    }

     u=i*A2/(i-1);
     x=A1;
     
    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }
    printf("ave=%lf\n",A1);
    printf("var=%lf\n",A2);
    printf("u=%lf\n", u);
    printf("x=%lf\n", x);


    return 0;


}

