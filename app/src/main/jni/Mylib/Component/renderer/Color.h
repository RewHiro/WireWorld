//
// Created by vantan on 2016/02/14.
//

#ifndef PRIMITIVEMONSTER03_COLOR_H
#define PRIMITIVEMONSTER03_COLOR_H

#include "../../Object.h"

namespace rew
{
    namespace system
    {
        namespace renderer
        {
            template<typename T>
            class Color : public Object
            {
            public:
                Color(T red, T green, T blue, T alpha):
                red_(red),
                green_(green),
                blue_(blue),
                alpha_(alpha)
                {

                }

                inline T GetRed()const{return red_;}
                inline T GetGreen()const{return green_;}
                inline T GetBlue()const{return blue_;}
                inline T GetAlpha()const{return alpha_;}

            private:
                T red_;
                T green_;
                T blue_;
                T alpha_;
            };
        }
    }
}



#endif //PRIMITIVEMONSTER03_COLOR_H
