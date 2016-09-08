#include <cs50.h>
#include <stdio.h>

int main(void){

  const int BottlesPerMin = 12;
  int minutes=0;
   
  printf("minutes:");
  minutes = GetInt();
  printf("bottles: %d\n", BottlesPerMin*minutes);
  
  return 0;
}
