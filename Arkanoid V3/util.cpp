#include "util.h"

Util::Util()
{

}

bool Util::between(int x, int borne1, int borne2)
{
    return ((x <= borne1 && x >= borne2) || (x >= borne1 && x <= borne2));
}
