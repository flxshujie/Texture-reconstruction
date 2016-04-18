#include<iostream>
#include<string>
#include "../../io/PlyBase.h"
using namespace std;
int main()
{
    string dir_name = "/home/vipl/Desktop/shujie/Texture/bin" ;
    PlyReader plyReader(dir_name);
    plyReader.parsePly();
    return 0;

}
