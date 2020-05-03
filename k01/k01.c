#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(int i,double val[i],double ave,int n)
{ 
  ave=1;
     for(i=1;i<=n;i++){
         ave=((i-1)*ave)/i+val[i]/i;
     }
     return ave;
}
extern double var_online(int i,double val[i], double ave,double save,int n,double var)
{  
   ave=1;save=1;
    for(i=1;i<=n;i++){
       var=(((i-1)*save)/i+(val[i]*val[i])/i)-pow((((i-1)*ave)/i+(val[i]/i)),2);
        save=(((i-1)*save)/i+pow(val[i],2)/i);
        ave=((i-1)*ave)/i+val[i]/i;
    }
    return var;
}


int main(void)
{   
    int i,n;
    double val[i],ave,save,var;
    float A1,A2;
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
        sscanf(buf,"%lf",&val[i]);
        scanf("%d", &n);

        A1=ave_online(i,val,ave,n);
        A2=var_online(i,val,save,ave,n,var);
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }
    printf("ave=%lf\n",A1);
    printf("var=%lf\n",A2);


    return 0;


}

