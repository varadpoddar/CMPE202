#ifndef DEMETERAUTO_H_
#define DEMETERAUTO_H_

class Sparkplug
{
public:
    void replace() { /* replace sparkplug */ }
};

class Engine
{
public:
    Sparkplug *get_sparkplug() const { return plug; }

    void replace_sparkplug()
    {
        plug->replace();
    }

private:
    Sparkplug *plug;
};

class DemeterAuto
{
public:
    void service_sparkplug(Sparkplug *plug)
    {
        plug->replace();
    }

    void maintain_auto()
    {
        engine.replace_sparkplug();

        Sparkplug *plug1 = engine.get_sparkplug();
        plug1->replace();

        Sparkplug *plug2 = new Sparkplug();
        plug2->replace();
    }

private:
    Engine engine;
};

#endif /* DEMETERAUTO_H_ */
