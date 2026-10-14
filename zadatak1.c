#include<stdio.h>
#include<stdlib.h>

typedef struct student{
char name[10];
char lastName[10];
int bodovi;
}stud;

int main(){
    int i=0;
    int brojač=0;
    stud* student=NULL;
    char buffer[50]={0};
    FILE* fp= fopen("studenti.txt", "r");

    if (fp==NULL){
        printf("Datoteka se nije mogla otvoriti");
        return -1;
    }

    while(!feof(fp))
    {
     fgets(buffer,50,fp);
        brojač++;
    }
  printf("%d\n", brojač);

  fclose(fp);
    student=(stud*)malloc(brojač*sizeof(stud));

    if(!student){
    printf("greška");
return -2;}

fp=fopen("studenti.txt","r");
while(!feof(fp)){
    fscanf(fp, "%s %s %d", student[i].name, student[i].lastName, &student[i].bodovi);
    i++;
}
for(i=0;i<brojač;i++)
printf("%s %s %d \n", student[i].name, student[i].lastName, student[i].bodovi);

fclose(fp);
  free(student);

}