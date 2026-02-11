#include <iostream>
#include <string.h>

class C
{
    private:
    int id;
    char *name;
    public:
    C()
    {
        name = new char[100];
    }
    void setName(char name[])
    {
        strcpy(this->name, name);
    }
    void setId(int id)
    {
        this->id = id;
    }
    void print()
    {
        std::cout << id << "\n";
        std::cout << name << "\n";
    }
    C (C& obj)
    {
        char *ch = new char[sizeof(obj.name) + 1];
        strcpy(ch, obj.name);
        this->name = ch;
        this->id = obj.id;
    }
};
int main()
{
    /*C c;
    c.setName("yash");
    c.setId(4);
    C d(c);
    //c.print();
    //d.print();
    c.setName("yashBoss");
    c.setId(5);
    c.print();
    d.print();//shallow copy */

    C a;
    a.setId(1);
    a.setName("boss");
    C b(a);
    a.print();
    b.print();

    a.setName("Toss");
    a.print();
    b.print();//deep copy
    return 0;
};