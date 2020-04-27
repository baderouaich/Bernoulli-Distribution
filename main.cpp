#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <random>
#include <cmath>

class BernoulliDistribution
{
public:
    bool operator()()
    {
        //clamp chance
        chance = std::clamp<double>(chance, 0.00, 1.00);

        //fifty fifty chance
        std::bernoulli_distribution dist(chance);
        auto &mt = GetEngine();
        return dist(mt);
    }

    /*0.50 = 50% black 50% white*/
    double chance = 0.50;

private:
    static std::mt19937& GetEngine()
    {
        static std::random_device seed_gen;
        static std::mt19937 engine(seed_gen());
        return engine;
    }
};


class DemoGraphic : public olc::PixelGameEngine
{

public:

    DemoGraphic()
    {
        sAppName = "Bernoulli Distribution Graphic Test";
    }

protected:
    BernoulliDistribution dist;


    bool OnUserCreate() override
    {

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {

        if(GetMouse(0).bPressed)
        {
            std::cout << "Chance: " << dist.chance << std::endl;
            Clear(olc::BLACK);
            for(unsigned int x = 0; x < ScreenWidth(); x++)
                for(unsigned int y = 0; y < ScreenHeight(); y++)
                    Draw(x, y, dist() ? olc::WHITE : olc::BLACK);
        }


        if(GetMouseWheel() > 0)
        {
           // up
           dist.chance += fElapsedTime * 2.0;
        }
        else if(GetMouseWheel() < 0)
        {
            // down
            dist.chance -= fElapsedTime * 2.0;
        }


        return true;
    }

    bool OnUserDestroy() override
    {
        return true;
    }

};



int main()
{
    DemoGraphic demo;
    if(demo.Construct(640, 480, 2, 2))
        demo.Start();
    return 0;
}
