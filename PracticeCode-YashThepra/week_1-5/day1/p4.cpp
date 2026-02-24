#include <iostream>

class animal
{
public:
    int wt;
    int ht;
    animal(int w, int h)
    {
        wt = w;
        ht = h;
    }
    void show()
    {
        std::cout << "weight of the animal: " << wt << " " << "height of the animal: " << ht << "\n";
    }
    int getwt()
    {
        return wt;
    }
    animal incWt()
    {
        wt++;
        return *this;
    }
};

class dog : public animal
{
public:
    int tail;
    dog(int tail, int wt, int ht) : animal(wt, ht)
    {
        this->tail = tail;
    }
};

class cat : public animal
{
public:
    int roundTail;
    cat(int tail, int wt, int ht) : animal(wt, ht)
    {
        roundTail = tail;
    }
};

/*void speak(const dog& obj)
{
    std::cout << "I am dog.\n";
}*/

/*void speak(const cat& obj)
{
    std::cout << "I am cat.\n";
}*/

void speak(const animal& obj)
{
    std::cout << "I am animal only.\n";
}
int main()
{
    cat c(10, 11, 12);
    dog d(13, 14, 15);
    speak(d);
    speak(c);
    animal *a = new cat(20, 22, 25);
    //a->getwt().getwt().getwt();
    speak(*a);

    //std::cout << a->incWt().incWt().incWt() << "\n";
    std::cout << a->incWt().incWt().incWt().getwt() << "\n";
    a->incWt().incWt().show();
}
