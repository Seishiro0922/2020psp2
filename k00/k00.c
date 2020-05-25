#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    double max_val=0,min_val=200;
    double val;
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
        if(val>max_val){
            max_val = val;
        }
        if(val<min_val){
            min_val = val;
        }
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("Highest: %f\n",max_val);
    printf("Lowest: %f\n",min_val);

    return 0;
}
