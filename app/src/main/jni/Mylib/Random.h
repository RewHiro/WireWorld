//
// Created by vantan on 2016/02/17.
//

#ifndef PRIMITIVEMONSTER03_RANDOM_H
#define PRIMITIVEMONSTER03_RANDOM_H

#include <random>


namespace rew
{
    namespace system
    {
        class Random
        {
        public:

            static std::mt19937& GetRandom();

            static int RandomRange(int min, int max);
            static float RandomRange(float min, float max);
        };
    }
}



#endif //PRIMITIVEMONSTER03_RANDOM_H
