#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

extern void get_bound(int num_male, int num_whole, double* lower_bound, double* upper_bound);
extern int choose(int n, int r);

struct D{double ID; int gender; double height;}; 

int main(void)
{  
    int i,n;
    double val,id,ID;
    char fname[FILENAME_MAX];
    char fname2[FILENAME_MAX];
    char buf[256];
    char buf2[256];
    FILE* fp,*fp2;
    int num_male, num_female, num_unknown, num_whole;
    int gender;
    double lower_bound,upper_bound;
    struct D date[14];

    i=-1;
    n=0;
    
              

    
    printf("input the filename of sample height:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    printf("input the filename of sample ID:");
    fgets(fname2,sizeof(fname2),stdin);
    fname2[strlen(fname2)-1] = '\0';
    printf("the filename of sample: %s\n",fname2);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    fp2 = fopen(fname2,"r");
    if(fp2==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    num_male=num_female=num_unknown=0;
    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%d,%lf",&gender, &val);
        i++;
        date[i].gender=gender;
        date[i].height=val;
        
        if(gender==1){ num_male++;
        }else if(gender==2){ num_female++;
        }else{ num_unknown++;
        }
    }
    num_whole = num_male+num_female+num_unknown;

    i=0;
     printf("Which ID's data do you want? :");
    scanf("%lf",&id);
    printf("---\n");

    while(fgets(buf2,sizeof(buf2),fp2) != NULL){
        sscanf(buf2,"%lf",&ID);
        i++;
       date[i].ID=ID;
    
    }
      for(i=1;i<=num_whole;i++){
          if(date[i].ID==id){
              
            printf("ID:%.0lf\n",date[i].ID);
            printf("gender:");
            if(date[i].gender==1){printf("male\n");}
            else{ printf("female\n");}
            printf("height:%.1lf\n",date[i].height);   
             n=1;
             }
      }
      if(n==0){printf("No date\n");}
      printf("---\n");

    


    printf("================================\n");
    printf("Number of male sample : %d\n",num_male);
    printf("Number of female sample : %d\n",num_female);
    printf("Male Ratio : %lf\n",(double)num_male/num_whole);


    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    if(fclose(fp2) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    } 


    
    

    get_bound(num_male, num_whole, &lower_bound, &upper_bound);

    printf("Population Male Ratio (estimated) : %lf--%lf\n",lower_bound,upper_bound);
    printf("============================\n");

    return 0;

}

void get_bound(int num_male, int num_whole, double* lower_bound, double* upper_bound)
{
    double z;
    int n;
    
    z=0;
    n=0;
    while(z < 0.025){
        z += choose(num_whole,num_male) * pow((double)n/num_whole, num_male) * pow((double)(num_whole-n)/num_whole, num_whole-num_male); 
        printf("%lf\n",z);
        n ++; 
    }
    *lower_bound = (double)(n-1)/num_whole;

    z=0;
    n=num_whole;
    while(z< 0.025){
        z += choose(num_whole,num_male) * pow((double)n/num_whole, num_male) * pow((double)(num_whole-n)/num_whole, num_whole-num_male);
        printf("%lf\n",z);
        n --;
    }
    *upper_bound = (double)(n+1)/num_whole;
}

int choose(int n, int r)
{
    int i,bunbo,bunshi;

    bunbo=bunshi=1;
    for(i=n;i>r;i--) bunbo *= i;
    for(i=r;i>0;i--) bunshi *= i;
    return bunbo/bunshi;
}
