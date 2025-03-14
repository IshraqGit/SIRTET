#include "colors.h"

using namespace std;

const Color darkGrey = {26  , 31 , 40 , 255};
const Color green = {47 , 230 , 23 , 255};
const Color red = {232 , 18 , 18 , 255};
const Color orange = {225 , 116 , 17 , 255};
const Color yellow = {242 , 234 , 4 , 255};
const Color purple = {166 , 0 , 247 , 255};
const Color cyan = {21 , 204 , 209 , 255};
const Color blue = {13 , 64 , 216 , 255};
const Color darkBlue = {103, 9, 9, 255};
const Color lightBlue = {223, 106, 106, 255}; 

vector<Color> getCellColors()
{
    return {darkGrey , green , red , orange , 
            yellow , purple , cyan , blue};
}