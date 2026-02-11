#include <iostream>

class Batsman
{
    private:
    double strikeRate;
    public:
    void set(int sr)
    {
        if (sr >=0)
        {
            this->strikeRate = sr;
        }
        else 
        {
            this->strikeRate = 0;
        }
    }
    void print()
    {
        std::cout << strikeRate << "\n";
    }
};
int main()
{
    Batsman virat;
    virat.set(150);
    virat.print();
    Batsman babar;
    babar.set(-20000);
    babar.print();//controlled access through encapsulation thus protects invariants.
    return 0;
}