#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void add_student();
void search_student();
void student_record();
void remove_student();

struct student{
    char first_name[50];
    char last_name[50];
    int roll;
    char Class[10];
    char address[20];
    float per;
};

void main(){
    int choice = 0;
    while(choice!=5){
        printf("\t\t\t=========Student Management System=========\n\n\n");
        printf("\t\t\t\t  1.Add student Record\n");
        printf("\t\t\t\t  2.Search student\n");
        printf("\t\t\t\t  3.Student Record\n");
        printf("\t\t\t\t  4.Remove student\n");
        printf("\t\t\t\t  5.Exit\n");
        printf("\t\t\t-------------------------------------------\n");
        printf("\t\t\t\t  ");
        scanf("%d", &choice);

        switch(choice){
        case 1:
            system("cls");
            add_student();
            system("cls");
            break;

        case 2:
            system("cls");
            search_student();
            printf("\t\t\t\tPress any key to exit..\n");
            getch();
            system("cls");
            break;
        case 3:
            system("cls");
            student_record();
            printf("\t\t\t\tPress any key to exit..\n");
            getch();
            system("cls");
            break;
        case 4:
            system("cls");
            remove_student();
            printf("\t\t\t\tPress any key to exit..\n");
            getch();
            system("cls");
            break;
        default:
            system("cls");
            getch();
            printf("Enter any key to continue.....");
            getch();
            system("cls");
            break;

        }
    }
}

void add_student(){
    struct student info;
    FILE *fp;
    char another;

    do{
        system("cls");
        printf("\t\t\t\t=======Add Student Info=======\n");
        fp=fopen("student info","a");
        printf("\n\t\t\t\t Enter First Name :  ");
        scanf("%s",info.first_name);
        printf("\n\t\t\t\t Enter Last Name  :  ");
        scanf("%s",info.last_name);
        printf("\n\t\t\t\t Enter Roll no    :  ");
        scanf("%d",&info.roll);
        printf("\n\t\t\t\t Enter Class      :  ");
        scanf("%s",info.Class);
        printf("\n\t\t\t\t Enter Address    :  ");
        scanf("%s",info.address);
        printf("\n\t\t\t\t Enter Percentage :  ");
        scanf("%f",&info.per);
        printf("\n\t\t\t\t-----------------------------------\n");
        if(fp==NULL){
            printf("\t\tCan't Open File\n");
        }
        else{
            printf("\t\t\t\tRecorded Successfully\n");
        }
        fwrite(&info,sizeof(struct student),1,fp);
        fclose(fp);

        printf("\t\t\t\tDo you want to add another student?(y/n): ");
        scanf("%s",&another);

    }while(another=='y'||another=='Y');
}


void search_student(){
    FILE *fp;
    struct student info;
    int roll,found=0;
    fp=fopen("student info","r");

    printf("\t\t\t\t=======Search Student=======\n\n");
    printf("\t\t\t Enter Roll NO: ");
    scanf("%d",&roll);

    while(fread(&info,sizeof(struct student),1,fp)){
        if(info.roll==roll){
            found=1;
            printf("\n\t\t\t\tStudent Name  : %s %s",info.first_name,info.last_name);
            printf("\n\t\t\t\tRoll          : %d ",info.roll);
            printf("\n\t\t\t\tClass         : %s ",info.Class);
            printf("\n\t\t\t\tAddress       : %s ",info.address);
            printf("\n\t\t\t\tPercentage    : %f ",info.per);
            printf("\n\t\t\t--------------------------------------\n");
        }
    }
    if(!found){
        printf("\t\t\t\tRecord Not Found\n");
    }

    fclose(fp);
    getch();
}


void student_record(){
    FILE *fp;
    struct student info;
    fp=fopen("student info","r");
    printf("\t\t\t=======Student Records=======\n\n");


    if(fp==NULL){
        fprintf(stderr,"\t\t\tCan't Open File\n");
    }
    else{
        printf("\t\t\t\t Records \n");
        printf("\t\t\t--------------------------------------\n");
    }


    while(fread(&info,sizeof(struct student),1,fp)){
        printf("\n\t\t\t\tStudent Name  : %s %s",info.first_name,info.last_name);
        printf("\n\t\t\t\tRoll          : %d ",info.roll);
        printf("\n\t\t\t\tClass         : %s ",info.Class);
        printf("\n\t\t\t\tAddress       : %s ",info.address);
        printf("\n\t\t\t\tPercentage    : %f ",info.per);
        printf("\n\t\t\t--------------------------------------\n");
    }

    fclose(fp);
    getch();
}




void remove_student(){
    FILE *fp,*fp1;
    struct student info;
    int roll,found=0;

    printf("\t\t\t\t=======Delete Student Record=======\n\n");
    fp=fopen("student info","r");
    fp1=fopen("temp.txt","w");
    printf("\t\t\t Enter Roll NO: ");
    scanf("%d",&roll);

    if(fp==NULL){
        fprintf(stderr,"\t\t\tCan't Open File\n");
    }

    while(fread(&info,sizeof(struct student),1,fp)){
        if(info.roll==roll){
            found=1;
        } else {
            fwrite(&info,sizeof(struct student),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);

    if(found){
        remove("student info");
        rename("temp.txt","student info");
        printf("\n\t\t\t\t--------------------------------------\n");
        printf("\t\t\t\t Delete Record Successfully\n");
    }
    if(!found){
            printf("\n\t\t\t\t--------------------------------------\n");
            printf("\n\t\t\t Record Not Found\n");
    }
    getch();
}
