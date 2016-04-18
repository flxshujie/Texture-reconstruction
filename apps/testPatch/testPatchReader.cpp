#include<iostream>
#include<string>
#include "../../io/PatchBase.h"
using namespace std;
int main()
{
    string dir_name = "/home/vipl/Desktop/shujie/Texture/bin" ;
    PatchReader patchReader(dir_name);
    patchReader.parsePatch();
    return 0;

}
