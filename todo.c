#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "todo.h"

#define MAX_LENGTH 150
#define ID_LENGTH 3

struct task {
  char title[MAX_LENGTH-50];
  char body[MAX_LENGTH];
  char id[ID_LENGTH];
  struct task *next;
};

struct task *head=NULL;
int count =0;


static string random_id(void)
{
  srand( time(NULL));
  char lower_alpha[27];
  char upper_alpha[27];
  for(int i=0; i < 26; ++i)
    lower_alpha[i]=i+97, upper_alpha[i]=i+65;
  lower_alpha[26] =  upper_alpha[26] = '\0';
  int m = rand()%26;
  int n = rand()%26;

  char s[ID_LENGTH]={upper_alpha[m],lower_alpha[n],'\0'};
  string p = s;
  return p;
}
void init_task(void)
{
  FILE *fp;

  fp = fopen("db.bin","rb");
  if (fp == NULL){
    fprintf(stderr,"ERROR: Can't open file\n");
    return;
  }
  rewind(fp);
  //Retrieve tasks from database
  do {
    struct task *temp = malloc(sizeof(struct task));
   if (fread(temp,sizeof(struct task),1,fp)==1){
    temp->next = head;
    head = temp;
    ++count;
   }
  }while(!feof(fp) && !ferror(fp));

  fclose(fp);
}

bool is_full(void)
{
  return count == N;
}

bool is_empty(void)
{
  return count == 0;
}

void add_task(void)
{
  int i,n;
  struct task *temp = malloc(sizeof(struct task));
  printf("Enter title: ");
  fgets(temp->title,sizeof(temp->title),stdin);
  for(int i =0; i < sizeof(temp->title); ++i){
    if(temp->title[i] == '\n'){
      temp->title[i] = '\0';
      break;
    }
  }
  printf("Enter body: ");
  fgets(temp->body,sizeof(temp->body),stdin);
  for(int i =0; i < sizeof(temp->body); ++i){
    if(temp->body[i] == '\n'){
      temp->body[i] = '\0';
      break;
    }
  }
  strcpy(temp->id,random_id());
  temp->next = head;
  head=temp;
  ++count;

  FILE *fp;

  fp = fopen("db.bin","ab");
  if (fp == NULL){
    fprintf(stderr,"Can't save todos\n");
    return;
  }
  fwrite(temp,sizeof(struct task),1,fp);


  fclose(fp);
  printf("HURRAY! TASK CREATION SUCCESSFUL\n");
}
 
void print_task(void)
{
  if (head == NULL){
    fprintf(stderr,"ERROR: No task available!\n");
    return;
  }
  struct task *p;
  //printf("%s %15s  %15s\n","ID","TITLE","BODY");
  for(p=head; p != NULL; p=p->next){
    printf(">>>>>>>>>>>\t>>>>>>>>>>>>>\t>>>>>>>>>>\n");
    printf("ID: %s\nTITLE: %s\nBODY: %s\n\n",p->id,p->title,p->body);
  }

}

void clear_tasks(void)
{
  FILE *fp;
  fp = fopen("db.bin","wb");
  if(fp == NULL){
    fprintf(stderr,"Unable to clear tasks\n");
  }
  struct task  *prev=malloc(sizeof(struct task));
  for(;head!=NULL;prev=head,head=head->next){
    free(prev);
  }
  fclose(fp);
}

void remove_task(void)
{
  char id[3];
  printf("Enter task id: ");
  scanf("%s%*[^\n]",id);
  getchar();
  id[ID_LENGTH-1] = '\0';
  FILE *fp;
  fp = fopen("db.bin","rb");
  if(fp == NULL){
    fprintf(stderr,"ERROR: Unable to remove tasks\n");
    return;
  }
  struct task  *prev=malloc(sizeof(struct task));
  for(;head != NULL; prev = head,head = head->next){
    free(prev);
  }
  count =0;
  do {
    struct task *temp = malloc(sizeof(struct task));
   if (fread(temp,sizeof(struct task),1,fp)==1){
     ++count;	
     if(!strcmp(temp->id,id)){
       free(temp);
       --count;
       continue;
     }
     temp->next = head;
     head = temp;
   }
  }while(!feof(fp) && !ferror(fp));
  fclose(fp);
  fp = fopen("db.bin","wb");
  if (fp == NULL){
    fprintf(stderr,"ERROR:Program crashed\n");
    return;
  }
  struct task *p = malloc(sizeof(struct task));
  for(p=head;p!=NULL;p=p->next)
    fwrite(p,sizeof(struct task),1,fp);
  fclose(fp);
  printf("TASK WITH ID %s DELETED SUCCESSFULLY\n",id);

}


