#include <stdio.h>
#include "todo.h"

int main(void)
{
  init_task();
  char ch;
  printf("Commands: \n");
  printf("a: add task\n""r: remove task\n"
      "p: print all tasks\n""c: clear all tasks\n"
      "q: quit\n");
  do {
   printf("Enter command: ");
   scanf("%c",&ch);
    while ( getchar() != '\n');
   //fflush(stdin);
   switch(ch)
   {
     case 'a': 
       add_task();
       break;
     case 'p':
       print_task();
       break;
     case 'c':
       clear_tasks();
       break;
     case 'r':
       remove_task();
       break;
      case 'q':
       return 0;
   }
   //getchar();
  } while(1);
return 0;
}
