#include <iostream>
#include "bmplib.h"
#include <unistd.h>
using namespace std;
class photo_editor{
private:
    unsigned char imgGS[SIZE][SIZE];
public:
    void load_image(){
        string image_name,path = "\\imgs\\";
        cout << "Please enter the name of the image to process (NOTE: Must be in imgs folder):";
        cin >> image_name;
        path += image_name;
        path += ".bmp";
        char cwd[PATH_MAX];
        readGSBMP(strcat(getcwd(cwd,sizeof(cwd)),path.c_str()),imgGS);
    }
    void save_image () {
        char imageFileName[100];

        // Get gray scale result image target file name
        cout << "Enter the result image name:";
        cin >> imageFileName;
        // Add to it .bmp extension and load image
        strcat (imageFileName, ".bmp");
        writeGSBMP(imageFileName, imgGS);
    }
    bool is_digits(string& str)
    {
        for (char ch : str) {
            if (!(ch >= 48 && ch <= 57)) {
                return false;
            }
        }
        return true;
    }
    // filter 1 : black and white filter
    void Black_n_white_filter(){
        for(int i = 0 ; i < SIZE ; i++){
            for(int j = 0 ; j < SIZE ; j++){
                /*looping on each pixel and if the value is greater than 127
                 * we make that pixel white else we make it black */
                if(imgGS[i][j] > 127){
                    imgGS[i][j] = 255;
                }
                else{
                    imgGS[i][j] = 0;
                }
            }
        }
    }
    // filter 4 : flip image filter
    void flip(){
        // choosing the direction
        cout << "Enter 1 for vertical flip or 2 for horizontal flip:";
        int direction;cin>>direction;
        if(direction == 1){
            /* we iterate over the columns and rows of the photo,
            * focusing on the upper half of the image.
            * during this process, it swaps each row with its corresponding
            * row on the other side, creating a vertical mirror effect.
            */
            for(int i = 0 ; i < SIZE/2 ; i++){
                for (int j = 0; j <SIZE ; ++j) {
                    swap(imgGS[i][j] , imgGS[SIZE-i][j]);
                }
            }
        }
        else if(direction == 2){
            /* we iterate over the columns and rows of the photo,
            * focusing on the left half of the image.
            * during this process, it swaps each column with its corresponding
            * column on the other side, creating a horizontal mirror effect.
            */
            for(int i = 0 ; i < SIZE ; i++){
                for (int j = 0; j <SIZE/2 ; ++j) {
                    swap(imgGS[i][j] , imgGS[i][SIZE-j]);
                }
            }
        }
        else
        {
            cout << "wrong direction, please try again\n";
            flip();
        }
    }
    void menu(){
        cout << "1-  Black & White Filter\n"
                "2-  Invert Filter\n"
                "3-  Merge Filter \n"
                "4-  Flip Image\n"
                "5-  Darken and Lighten Image \n"
                "6-  Rotate Image\n"
                "7-  Detect Image Edges \n"
                "8-  Enlarge Image\n"
                "9-  Shrink Image\n"
                "10- Mirror 1/2 Image\n"
                "11- Shuffle Image\n"
                "12- Blur Image\n"
                "13- Crop Image\n"
                "14- Skew Image Right  \n"
                "15- Skew Image Up  \n"
                "16- Save the image to a file\n"
                "0-  Exit\n"
                "Please select a filter to apply or 0 to exit:";
        string choice_s;cin>>choice_s;
        int choice=0;
        if(is_digits(choice_s)){
            choice = stoi(choice_s);
        }
        else
        {
            cout << "Invalid filter, please try again\n";
            menu();
        }
        if(choice == 1){
            Black_n_white_filter();
        }
        else if (choice == 2){

        }
        else if(choice == 3){

        }
        else if(choice == 4){
            flip();
        }
        else if(choice == 5){

        }
        else if(choice == 6){

        }
        else if(choice == 7){

        }
        else if(choice == 8){

        }
        else if(choice == 9){

        }
        else if(choice == 10){

        }
        else if(choice == 11){

        }
        else if(choice == 12){

        }
        else if(choice == 13){

        }
        else if(choice == 14){

        }
        else if(choice == 15){

        }
        else if(choice == 16){
            save_image();
        }
        else if(choice == 0){
            return;
        }
        else {
            cout << "Invalid filter, please try again\n";
        }
        menu();
    }
};
int main() {
    photo_editor photo;
    photo.load_image();
    photo.menu();
}
