#include <stdio.h>

typedef struct example{
    //int x = 10; give error can't initialze because no object exists yet
    int x;
    /*void print(int num)
    {
        x = num;
        printf("%d\n", x);
    }*/
   //static int y;
}one;

typedef struct empty1{

}two;

int main()
{
    printf("%ld\n", sizeof(two));
    return 0;
}