//
// Created by vantan on 2016/02/17.
//

#include "Random.h"

namespace rew
{
    namespace system
    {
        std::mt19937& Random::GetRandom()
        {
            static std::random_device seed;
            static std::mt19937 random(seed());
            return random;
        }

        int Random::RandomRange(int min, int max)
        {
            std::uniform_int_distribution<int>random(min, max);
            return random(GetRandom());
        }

        float Random::RandomRange(float min, float max)
        {
            std::uniform_real_distribution<float>random(min, max);
            return random(GetRandom());
        }
    }
}