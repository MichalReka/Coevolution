#include "Utilities.h"

float Utilities::GetRandomFloat()
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(0, 1);
    return dis(e);
}