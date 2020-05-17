#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(int i,double val,double ave)
{  ave=1; 
   i++;
     ave=((i-1)*ave/i)+(val/i);    
  return ave;
}
extern double var_online(int n,double val, double ve,double save,double var)
{  save=1;
   ve=1;
   n++;
   var=(((n-1)*save/n)+val*val/n)-pow((((n-1)*ve/n)+val/n),2);
   save=(n-1)*save/n+val*val/n;
   ve=(n-1)*ve/n+val/n;
   return var;
}


int main(void)
{   
    int i=0,n=0;
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

        A1=ave_online(i,val,ave);
        A2=var_online(n,val,save,ve,var);

        
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

