#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(int i,double val,double ave)
{  
     ave=((i-1)/i*ave)+(val/i);    
  return ave;
}
extern double var_online(int i,double val, double ve,double save,double var)
{  
   var=(((i-1)*save/i)+val*val/i)-pow((((i-1)*ve/i)+val/i),2);
   save=(i-1)*save/i+val*val/i;
   ve=(i-1)*ve/i+val/i;
   return var;
}


int main(void)
{   
    int i=0;
    double val=1,ave=1,save,var,ve,pm,samplemean,samplevariance,populationmean,populationvariance;
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

        samplemean=ave_online(i,val,ave);
        
        samplevariance=var_online(i,val,save,ve,var);

        
    }

     populationvariance=i*samplevariance/(i-1);
     populationmean=samplemean;

     pm=pow(populationvariance/i,0.5);
     
    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }
    printf("sample mean=%lf\n",samplemean);
    printf("sample variance=%lf\n",samplevariance);
    printf("population mean=%lf\n", populationmean);
    printf("population variance=%lf\n", populationvariance);
    printf("pm=%lf\n",pm);


    return 0;


}

