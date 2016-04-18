#include<iostream>
#include<string>
#include "../../io/BundlerBase.h"
using namespace std;
int main()
{
    string dir_name = "/home/vipl/Desktop/shujie/Texture/bin" ;
    Bundler bundler(dir_name);
    bundler.readData();

    return 0 ;
}
