#include <iostream>
#include "bmplib.h"
#include <unistd.h>
using namespace std;
unsigned char imgGS[SIZE][SIZE];
int main() {
    string image_name,path = "\\imgs\\";
    cout << "Enter Image name (NOTE: Must be in imgs folder): ";
    cin >> image_name;
    path += image_name;
    path += ".bmp";
    char cwd[PATH_MAX];
    readGSBMP(strcat(getcwd(cwd,sizeof(cwd)),path.c_str()),imgGS);
    showGSBMP(imgGS);
}
