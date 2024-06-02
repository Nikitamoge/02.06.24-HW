#include <iostream>
#include <string>

using namespace std;

/*
Абстрактная фабрика - порождающий паттерн проектирования,
который предоставляет интерфейс для создания семейств взаимосвязанных или взаимозависимых объектов,
не специфицируя их конкретных классов.

Применимость
- система не должна зависеть от того, как создаются, компонуются и представляются входящие в нее объекты;
- входящие в семейство взаимосвязанные объекты должны использоваться вместе и необходимо обеспечить выполнение этого ограничения;
- система должна конфигурироваться одним из семейств составляющих ее объектов;

Паттерн абстрактная фабрика обладает следующими плюсами и минусами:
 * изолирует конкретные классы.
 * упрощает замену семейств продуктов.
 * гарантирует сочетаемость продуктов.
*/

class Herbivore {
public:
    virtual string Name() = 0;
    virtual int GetWeight() = 0;
    virtual void EatVegan() = 0;
    virtual bool IsAlive() = 0;
    virtual void Alive(bool alive) = 0;
    virtual ~Herbivore() {}
};

class Predator {
public:
    virtual string Name() = 0;
    virtual int Power() = 0;
    virtual void EatMeat(Herbivore* herbivore) = 0;
    virtual ~Predator() {}
};

class Wildebeest : public Herbivore {
private:
    int weight;
    bool alive;
public:
    Wildebeest() : weight(300), alive(true) {}

    string Name() override {
        return "Wildebeest";
    }
    int GetWeight() override {
        return weight;
    }
    void EatVegan() override {
        weight += 10;
    }
    bool IsAlive() override {
        return alive;
    }
    void Alive(bool Alive) override {
        alive = Alive;
    }
};

class Bison : public Herbivore {
private:
    int weight;
    bool alive;
public:
    Bison() : weight(500), alive(true) {}

    string Name() override {
        return "Bison";
    }
    int GetWeight() override {
        return weight;
    }
    void EatVegan() override {
        weight += 10;
    }
    bool IsAlive() override {
        return alive;
    }
    void Alive(bool Alive) override {
        alive = Alive;
    }
};

class Elk : public Herbivore {
private:
    int weight;
    bool alive;
public:
    Elk() : weight(400), alive(true) {}

    string Name() override {
        return "Elk";
    }
    int GetWeight() override {
        return weight;
    }
    void EatVegan() override {
        weight += 10;
    }
    bool IsAlive() override {
        return alive;
    }
    void Alive(bool Alive) override {
        alive = Alive;
    }
};

class Lion : public Predator {
private:
    int power;
public:
    Lion() : power(400) {}

    string Name() override {
        return "Lion";
    }
    int Power() override {
        return power;
    }
    void EatMeat(Herbivore* herbivore) override {
        if (power > herbivore->GetWeight()) {
            power += 10;
            herbivore->Alive(false);
            cout << "Lion eats " << herbivore->Name() << " and gains power\n";
        }
        else {
            power -= 10;
            cout << "Lion fails to eat " << herbivore->Name() << " and loses power\n";
        }
    }
};

class Wolf : public Predator {
private:
    int power;
public:
    Wolf() : power(400) {}

    string Name() override {
        return "Wolf";
    }
    int Power() override {
        return power;
    }
    void EatMeat(Herbivore* herbivore) override {
        if (power > herbivore->GetWeight()) {
            power += 10;
            herbivore->Alive(false);
            cout << "Wolf eats " << herbivore->Name() << " and gains power\n";
        }
        else {
            power -= 10;
            cout << "Wolf fails to eat " << herbivore->Name() << " and loses power\n";
        }
    }
};

class Tiger : public Predator {
private:
    int power;
public:
    Tiger() : power(450) {}

    string Name() override {
        return "Tiger";
    }
    int Power() override {
        return power;
    }
    void EatMeat(Herbivore* herbivore) override {
        if (power > herbivore->GetWeight()) {
            power += 10;
            herbivore->Alive(false);
            cout << "Tiger eats " << herbivore->Name() << " and gains power\n";
        }
        else {
            power -= 10;
            cout << "Tiger fails to eat " << herbivore->Name() << " and loses power\n";
        }
    }
};

class Continent {
public:
    virtual Herbivore* CreateHerbivore() = 0;
    virtual Predator* CreateCarnivore() = 0;
    virtual ~Continent() {}
};

class Africa : public Continent {
public:
    Herbivore* CreateHerbivore() override {
        return new Wildebeest();
    }
    Predator* CreateCarnivore() override {
        return new Lion();
    }
};

class NorthAmerica : public Continent {
public:
    Herbivore* CreateHerbivore() override {
        return new Bison();
    }
    Predator* CreateCarnivore() override {
        return new Wolf();
    }
};

class Eurasia : public Continent {
public:
    Herbivore* CreateHerbivore() override {
        return new Elk();
    }
    Predator* CreateCarnivore() override {
        return new Tiger();
    }
};

class AnimalWorld {
private:
    Herbivore* herbivore;
    Predator* predator;
public:
    AnimalWorld(Continent* factory) {
        herbivore = factory->CreateHerbivore();
        predator = factory->CreateCarnivore();
    }

    ~AnimalWorld() {
        delete herbivore;
        delete predator;
    }

    void MealsHerbivores() {
        if (herbivore->IsAlive()) {
            herbivore->EatVegan();
            cout << herbivore->Name() << " eats grass and now weighs " << herbivore->GetWeight() << " kg\n";
        }
    }

    void NutritionCarnivores() {
        if (herbivore->IsAlive()) {
            predator->EatMeat(herbivore);
        }
    }
};

void TypeAnimalWorld(Continent* continent, const string& continentName) {
    cout << continentName << endl;
    AnimalWorld world(continent);
    world.MealsHerbivores();
    world.NutritionCarnivores();
    cout << endl;
    delete continent;
}

int main() {
    TypeAnimalWorld(new Africa(), "Africa");
    TypeAnimalWorld(new NorthAmerica(), "North America");
    TypeAnimalWorld(new Eurasia(), "Eurasia");
}