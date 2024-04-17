#include <iostream>
#include <string>
using namespace std;

// размеры 
enum class Size { S = 20, M = 30, L = 40, XXL = 50 };

class Beverage abstract // базовый абстрактный напиток
{
protected:
    Size size;
    double price;
    string description;

public:
    Size getSize() const
    {
        return size;
    }

    double getPrice() const
    {
        return price;
    }

    string getDescription() const
    {
        return description;
    }

    void print() const
    {
        cout << description << " = " << price << " UAH\n";
    }
};

// shaverma classic - конкретный базовый food без добавок
class ShavermaClassic : public Beverage
{
public:
    ShavermaClassic(Size size)
    {
        this->size = size;
        description = "very delicious classic shaverma";

        if (size == Size::M) price = 150; // 330г
        else if (size == Size::L) price = 200; // 400г
        else throw "invalid shaverma size";
    }
};

// shaverma cheese - конкретный базовый food без добавок
class ShavermaCheese : public Beverage
{
public:
    ShavermaCheese()
    {
        // size = ...
        description = "very delicious cheese shaverma";
        price = 150;
    }
};

// hotdog - конкретный базовый food без добавок
class HotDog : public Beverage
{
public:
    HotDog()
    {
        // size = ...
        description = "delicious snack";
        price = 30;
    }
};

////////////////////////////////////////////////////////////////

// базовая абстрактная добавка (надо было назвать Additive?)
class Condiment abstract : public Beverage // добавка помечена как наследник food - это важно для реализации паттерна!
{
protected:
    Beverage* beverage; // указатель на оригинальный food
};

// sauce
class SauceCondiment : public Condiment
{
public:
    SauceCondiment(Beverage* beverage)
    {
        this->beverage = beverage; // добавка
        description = this->beverage->getDescription() + " + Sauce (5 UAH)";
        price = this->beverage->getPrice() + 5;
    }

    SauceCondiment() 
    {
        this->beverage = this; 
        description = "large pack of sauce to go";
        price = 10;
    }
};

class CheeseCondiment : public Condiment
{
public:
    CheeseCondiment(Beverage* beverage)
    {
        this->beverage = beverage;
        description = this->beverage->getDescription() + " + Cheese (15 UAH)";
        price = this->beverage->getPrice() + 15;
    }
};

class MeatCondiment : public Condiment
{
public:
    MeatCondiment(Beverage* beverage)
    {
        this->beverage = beverage;
        description = this->beverage->getDescription() + " + Meat (40 UAH)";
        price = this->beverage->getPrice() + 40;
    }
};

int main()
{
    Beverage* hotDog = new HotDog();
    Beverage* shavermaClassic = new ShavermaClassic(Size::L);
    Beverage* shavermaCheese = new ShavermaCheese();

    hotDog->print();
    shavermaClassic->print();
    shavermaCheese->print();

    cout << "================================================\n";

    Beverage* upgradedShavermaPlus = new MeatCondiment(new SauceCondiment(new HotDog()));
    upgradedShavermaPlus->print();

    Beverage* doubleCheeseShaverma = new CheeseCondiment(upgradedShavermaPlus);
    doubleCheeseShaverma->print();

    Beverage* extraMeatShaverma = new MeatCondiment(new MeatCondiment(new MeatCondiment(new ShavermaClassic(Size::L))));
    extraMeatShaverma->print();

    Beverage* sauceToGo = new SauceCondiment(new SauceCondiment(new SauceCondiment()));
    sauceToGo->print();
}