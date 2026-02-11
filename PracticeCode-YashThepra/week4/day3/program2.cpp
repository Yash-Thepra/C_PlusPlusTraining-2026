#include <iostream>

//static int check;
class yash
{
    public:
    static int boss;
    void print()
    {
        std::cout << boss << "\n";
    }
};

class boss
{
    public:
    inline static int y = 10;//this is allowed
    boss()
    {
        y++;
    }
    void print()
    {
        std::cout << this->y << "\n";
    }
};

int yash::boss = 10;
 
int main()
{
    //check = 10;
    //std::cout << ++check << "\n";
    //non consst static requires definition outside class to access it.
    //int yash::boss = 10; qualified definition not allowed inside main or any function
    yash a;
    a.boss++;
    yash b;
    b.boss++;
    yash universal;
    universal.boss++;
    std::cout << yash::boss << "\n";

    boss m;
    boss n;
    boss o;
    std::cout << boss::y << "\n";
    return 0;
}