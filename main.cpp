#include <iostream>
#include "bmplib.h"
#include <unistd.h>
#include <cmath>
using namespace std;
class photo_editor{
private:
    unsigned char imgGS[SIZE][SIZE];
    unsigned char imgGS2[SIZE][SIZE];
public:
    void load_image(){
        string image_name,path = "\\imgs\\";
        cout << "Please enter the name of the image to process (NOTE: Must be in imgs folder, without bmp):";
        cin >> image_name;
        path += image_name;
        path += ".bmp";
        char cwd[PATH_MAX];
        readGSBMP(strcat(getcwd(cwd,sizeof(cwd)),path.c_str()),imgGS);
    }
    void show_image(){
        showGSBMP(imgGS);
    }
    void save_image () {
        // the image will be saved at cmake files in tmp folder
        string imageFileName, path = "\\tmp\\";
        // Get gray scale result image target file name
        cout << "Enter the result image name(saved in tmp folder at cmake) : ";
        cin >> imageFileName;
        //adding the extension
        imageFileName += ".bmp";
        path += imageFileName;
        char cwd[PATH_MAX];
        writeGSBMP(strcat(getcwd(cwd,sizeof(cwd)),path.c_str()), imgGS);
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

    // filter 2 : invert filter
    void invert_filter()
    {
        for (int i = 0; i < SIZE; i++)
        {
            // Reflects pixels ( new pixel = 255 - old pixel)
            for (int j = 0; j < SIZE; j++)
                imgGS[i][j] = 255 - imgGS[i][j];
        }
    }

    // filter 3 : Merge Filter
    void Merge_Filter()
    {
        // uploading the second image
        string image_name,path = "\\imgs\\";
        cout << "Please enter the name of the second image to process (NOTE: Must be in imgs folder, without .bmp):";
        cin >> image_name;
        path += image_name;
        path += ".bmp";
        char cwd[PATH_MAX];
        readGSBMP(strcat(getcwd(cwd,sizeof(cwd)),path.c_str()),imgGS2);

        // Merging two photos requires
        // every pixel to be the average of
        // the 2 pixels from each photo

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                imgGS[i][j] = (imgGS[i][j] + imgGS2[i][j]) /2;
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


    // filter 5 : Darken and Lighten Image
    void Darken_and_Lighten_Image ()
    {
        // choose the filter wanted
        cout <<"select a number :\n(1) lighten\n(2) darken\n";
        int x;
        cin >> x;

        // this is the lightening filter
        if (x == 1)
        {
            // 1. subtract full light value (255) - the original light value
            // 2. add the result to the original light value
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    imgGS[i][j] = imgGS[i][j] + (255 - imgGS[i][j])/2;
                }

            }
        }
        else
        {
            // divide the original by two
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    imgGS[i][j] = imgGS[i][j]/2;
                }

            }
        }
    }

    // filter 6 : rotate image
    void Rotate_Image()
    {
        unsigned char imgGS1[SIZE][SIZE];
        cout << "choose angle :\n(.90\t.180\t.270)\n";
        int x;
        cin >> x;
        if (x == 90)
        {
            for (int i  = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                    imgGS1[j][255 - i] = imgGS[i][j];
            }
        }
        else if (x == 180)
        {
            for (int i  = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                    imgGS1[255 - i][255 - j] = imgGS[i][j];
            }
        }
        else
        {
            for (int i  = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                    imgGS1[255 - j][i] = imgGS[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                imgGS[i][j] = imgGS1[i][j];
    }

    // filter 7 : detect edges
    void detect_edges(){
        /*
         * i have followed in this filter a well known algorithm called
         * sobel edge detection algorithm
         * i have read about it in this article
         * https://homepages.inf.ed.ac.uk/rbf/HIPR2/sobel.htm
         */
        // this is called convolution kernel and we need 2
        // one for columns and the other for rows
        int column_mask[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
        int row_mask[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
        // this is called Pseudo-convolution kernels and it is used
        // to compute the gradient
        int ix[254][254]={0};
        int iy[254][254]={0};
        // first we here compute the horizontal gradient for the photo
        for (int i = 0; i <254 ; ++i) {
            for (int j = 0; j <254 ; ++j) {
                int pixel = 0;
                for (int k = 0; k <3 ; ++k) {
                    for (int l = 0; l <3 ; ++l) {
                        pixel += (imgGS[i+k][j+l] * row_mask[k][l]);
                    }
                }
                ix[i][j] = pixel;
            }
        }
        // second we here compute the vertical gradient for the photo
        for (int i = 0; i <254 ; ++i) {
            for (int j = 0; j <254 ; ++j) {
                int pixel = 0;
                for (int k = 0; k <3 ; ++k) {
                    for (int l = 0; l <3 ; ++l) {
                        pixel += (imgGS[i+k][j+l] * column_mask[k][l]);
                    }
                }
                iy[i][j] = pixel;
            }
        }
        int res[254][254]={0};
        int threshold = 0;
        // here we find the magnitude for every pixel
        // using the formula sqrt(ix^2 + iy^2)
        for (int i = 0; i <254 ; ++i) {
            for (int j = 0; j <254 ; ++j) {
                double temp = 0;
                temp = sqrt(double(ix[i][j]*ix[i][j]) + double(iy[i][j]*iy[i][j]));
                res[i][j] = round(temp);
                threshold += res[i][j];
            }
        }
        // here we get the threshold which is the value
        // we will use to find if the pixel is edge or no
        threshold = round(double(threshold)/double(64516));
        for (int i = 0; i <254 ; ++i) {
            for (int j = 0; j <254 ; ++j) {
                // if the value is less than the threshold
                // we make it white (not an edge);
                if(res[i][j] <= threshold){
                    res[i][j] = 255;
                }
                else{
                    // else we make it black
                    // And it's considered as an edge
                    res[i][j] = 0;
                }
            }
        }
        // getting back the values into our main array
        // to use the saveImage() function
        for (int i = 0; i < 254; ++i) {
            for (int j = 0; j < 254; ++j) {
                imgGS[i][j] = res[i][j];
            }
        }
    }

    //filter 8 : enlarge image
    void enlarge_image()

    {

        // first of all choose the quarter you want to enlarge
        cout << "Choose the number of the required quarter :\n1. quarter one\n2. quarter two\n3. quarter three\n4. quarter four\n";
        int quarter;
        cin >> quarter;
        char mod_imgGS[2 * SIZE][2 * SIZE];

        //enlarging image dimensions to double
        for (int i = 0; i < 2 * SIZE; i++)
        {
            for (int j = 0; j < 2 * SIZE; j++)
            {
                mod_imgGS[i][j] = imgGS[i / 2][j / 2];
            }
        }

        // detecting the quarter based on the input
        if (quarter == 1)
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    imgGS[i][j] = mod_imgGS[i][j];
                }
            }
        }
        else if (quarter == 2)
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    imgGS[i][j] = mod_imgGS[i][255 + j];
                }
            }
        }
        else if (quarter == 3)
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    imgGS[i][j] = mod_imgGS[255 + i][j];
                }
            }
        }
        else
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    imgGS[i][j] = mod_imgGS[255 + i][255 + j];
                }
            }
        }
    }

    // filter 9 : Shrink Image
    void shrink_image ()
    {
        // enter the size
        cout << "Shrink\n1) 1/2\n2) 1/3\n3) 1/4\n";
        int s;
        cin >> s;
        char mod_img[256][256] = {0};

        if (s == 1)
        {
            // Merging every 4 pixels in one pixel
            for (int i = 0; i < 128; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    mod_img[i][j] = (imgGS[2 * i][2 * j] + imgGS[2 * i + 1][2 * j + 1]
                                     +  imgGS[2 * i + 1][2 * j] + imgGS[2 * i][2 * j + 1]) / 4;
                }
            }

        }
        else if (s == 2)
        {
            // Merging every 9 pixels in 1 pixel
            for (int i = 0; i < 85; i++)
            {
                for (int j = 0; j < 85; j++)
                {
                    mod_img[i][j] = (imgGS[3 * i][3 * j] + imgGS[3 * i][3 * j + 1]
                                     +  imgGS[3 * i][3 * j + 2] + imgGS[3 * i + 1][3 * j]
                                     +  imgGS[3 * i + 1][3 * j + 1] + imgGS[3 * i + 1][3 * j + 2]
                                     +  imgGS[3 * i + 2][3 * j] + imgGS[3 * i + 2][3 * j + 1]
                                     +  imgGS[3 * i + 2][3 * j + 2]) / 9;
                }
            }
        }

        else
        {
            // Merging every 15 pixels in 1 pixel
            for (int i = 0; i < 64; i++)
            {
                for (int j = 0; j < 64; j++)
                {

                    mod_img[i][j] = (imgGS[4 * i][4 * j] + imgGS[4 * i][4 * j + 1]
                                     +  imgGS[4 * i][4 * j + 2] + imgGS[4 * i][4 * j + 3]
                                     +  imgGS[4 * i + 1][4 * j] + imgGS[4 * i + 3][4 * j + 1]
                                     +  imgGS[4 * i + 1][4 * j + 2] +  imgGS[4 * i + 1][4 * j + 3]
                                     +  imgGS[4 * i + 2][4 * j] +  imgGS[4 * i + 2][4 * j + 1]
                                     +  imgGS[4 * i + 2][4 * j + 2] +  imgGS[4 * i + 2][4 * j + 3]
                                     +  imgGS[4 * i + 3][4 * j] +  imgGS[4 * i + 3][4 * j + 1]
                                     +  imgGS[4 * i + 3][4 * j + 2] +  imgGS[4 * i + 3][4 * j + 3]) / 16;
                }
            }
        }
        for (int i = 0; i  < 256; i++)
        {
            for (int j = 0; j < 256; j++)
                imgGS[i][j] = mod_img[i][j];
        }

    }

    // filter a : mirror half
    void mirror_half(){
        cout << "1- upper half\n"
                "2- lower half\n"
                "3- right half\n"
                "4- left half\n"
                "Enter the half that you want to mirror:";
        int target_half;cin>>target_half;
        if(target_half == 1){
            // copying each pixel into the opposite pixel
            // in the lower half which makes the upper mirror effect
            for (int i = 0; i <SIZE/2; ++i) {
                for (int j = 0; j < SIZE ; ++j) {
                    imgGS[SIZE-i][j] = imgGS[i][j];
                }
            }
        }
        else if(target_half == 2){
            // copying each pixel into the opposite pixel
            // in the upper half which makes the lower mirror effect
            for (int i = 0; i <SIZE/2; ++i) {
                for (int j = 0; j < SIZE ; ++j) {
                    imgGS[i][j] = imgGS[SIZE-i][j];
                }
            }
        }
        else if(target_half == 3){
            // copying each pixel into the opposite pixel
            // in the left half which makes the right mirror effect
            for (int i = 0; i <SIZE; ++i) {
                for (int j = 0; j < SIZE/2 ; ++j) {
                    imgGS[i][j] = imgGS[i][SIZE-j];
                }
            }
        }
        else if(target_half == 4){
            // copying each pixel into the opposite pixel
            // in the right half which makes the left mirror effect
            for (int i = 0; i <SIZE; ++i) {
                for (int j = 0; j < SIZE/2 ; ++j) {
                    imgGS[i][SIZE-j] = imgGS[i][j];
                }
            }
        }
        else
        {
            cout << "Wrong choice, please try again";
            mirror_half();
        }
    }


    //filter b : shuffle image
    void shuffle_image()
    {

        // create four arrays
        char quarter1[128][128], quarter2[128][128], quarter3[128][128], quarter4[128][128];

        // save the quarters of the original photo in these four arrays
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
                quarter1[i][j] = imgGS[i][j];
        }
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
                quarter2[i][j] = imgGS[i][127 + j];
        }
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
                quarter3[i][j] = imgGS[127 + i][j];
        }for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
                quarter4[i][j] = imgGS[127 + i][127 + j];
        }

        // ask the user to enter the new order
        cout << "Enter the order of the quarters :\n";
        int a[4];
        for (int i = 0; i < 4; i++)
            cin >> a[i];

        // order the arrays in the original photo as the user wants :

        //quarter one in the original photo
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if (a[0] == 1)
                    imgGS[i][j] = quarter1[i][j];
                if (a[0] == 2)
                    imgGS[i][j] = quarter2[i][j];
                if (a[0] == 3)
                    imgGS[i][j] = quarter3[i][j];
                if (a[0] == 4)
                    imgGS[i][j] = quarter4[i][j];
            }
        }

        //quarter two in the original photo
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if (a[1] == 1)
                    imgGS[i][128 + j] = quarter1[i][j];
                else if (a[1] == 2)
                    imgGS[i][128 + j] = quarter2[i][j];
                else if (a[1] == 3)
                    imgGS[i][128 + j] = quarter3[i][j];
                else
                    imgGS[i][128 + j] = quarter4[i][j];
            }
        }

        //quarter three in the original photo
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if (a[2] == 1)
                    imgGS[128 + i][j] = quarter1[i][j];
                else if (a[2] == 2)
                    imgGS[128 + i][j] = quarter2[i][j];
                else if (a[2] == 3)
                    imgGS[128 + i][j] = quarter3[i][j];
                else
                    imgGS[128 + i][j] = quarter4[i][j];
            }
        }

        //quarter four in the original photo
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if (a[3] == 1)
                    imgGS[128 + i][128 + j] = quarter1[i][j];
                else if (a[3] == 2)
                    imgGS[128 + i][128 + j] = quarter2[i][j];
                else if (a[3] == 3)
                    imgGS[128 + i][128 + j] = quarter3[i][j];
                else
                    imgGS[128 + i][128 + j] = quarter4[i][j];
            }
        }

    }
    // filter c : blur image
    void blur_image ()
    {
        char mod_img[256][256] = {0};
        int s, cnt;

        //calculate the average of every 25 pixels with the currant pixel
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                s = cnt = 0;
                for (int x = i - 2; x <= i + 2; x++)
                {
                    for (int y = j - 2; y <= j + 2; y++)
                    {
                        s += imgGS[x][y];
                        if (imgGS[x][y] > 0)
                            cnt++;
                    }
                }
                mod_img[i][j] = s / cnt;
            }
        }

        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
                imgGS[i][j] = mod_img[i][j];
        }
    }

    // filter d : crop image
    void crop_image(){
        cout << "Please enter x and y seperated by space:";
        int x,y;cin>>x>>y;
        cout << "please enter l and w seperated by space:";
        int l,w;cin>>l>>w;
        // making the area between 0 and x white
        for (int i = 0; i <SIZE ; ++i) {
            for (int j = 0; j <x ; ++j) {
                imgGS[i][j] = 255;
            }
        }
        // making the area between x+width and the end of the image white
        for (int i = 0; i <SIZE ; ++i) {
            for (int j = x+w; j <SIZE ; ++j) {
                imgGS[i][j] = 255;
            }
        }
        // making the area between 0 and y white
        for (int i = 0; i <y ; ++i) {
            for (int j = 0; j <SIZE ; ++j) {
                imgGS[i][j] = 255;
            }
        }
        // making the area between y+length and the end of the image white
        for (int i = y+l; i <SIZE ; ++i) {
            for (int j = 0; j <SIZE ; ++j) {
                imgGS[i][j] = 255;
            }
        }
        // eventually its result the area we want to stay the same
        // while the rest of the image become white
    }

    //filter e : skew image right
    void skew_image_right ()
    {
        char mod_img[256][256] = {0};

        // shift variable is created to get the right indices
        int shift = 128;
        for (int i = 0; i < 256; i++)
        {
            //  shift variable is decremented every 2 rounds on the columns
            if (i % 2 != 0)
                shift--;


            // The index i, j + shift is meant to get the precise index of the skewed image
            // Each pixel is colored as the average of the 2 pixels compressed to half the size
            for (int j = 0; j < 128; j++)
                mod_img[i][j + shift] = (imgGS[i][j * 2] + imgGS[i][j * 2 + 1]) / 2;

        }
        for (int i = 0; i < 256; i++)
            for (int j = 0; j < 256; j++)
                imgGS[i][j] = mod_img[i][j];
    }

    //filter f : skew image up
    void skew_image_up ()
    {
        char mod_img[256][256] = {0};

        // shift variable is created to get the right indices
        int shift = 128;
        for (int j = 0; j < 256; j++)
        {
            //  shift variable is decremented every 2 rounds on the columns
            if (j % 2 != 0)
                shift--;

            // The index i + shift, j is meant to get the precise index of the skewed image
            // Each pixel is colored as the average of the 2 pixels compressed to half the size
            for (int i = 0; i < 128; i++)
                mod_img[i + shift][j] = (imgGS[i * 2][j] + imgGS[i * 2 + 1][j]) / 2;

        }
        for (int i = 0; i < 256; i++)
            for (int j = 0; j < 256; j++)
                imgGS[i][j] = mod_img[i][j];
    }
    void menu2() {
        cout << "Make your choice :\n"
                "0-  Exit\n"
                "1-  show image\n"
                "2-  save image\n"
                "3-  return to filter menu\n";
        string choice_s;
        cin >> choice_s;
        int choice = 0;
        if (is_digits(choice_s)) {
            choice = stoi(choice_s);
        } else {
            cout << "Invalid choice, please try again\n";
            menu2();
        }
        if(choice == 1) {
            show_image();
        }
        else if(choice == 2) {
            save_image();
        }
        else if(choice == 3) {
            menu();
        }
        else if (choice == 0) {
            return;
        }

        else {
            cout << "Invalid choice, please try again\n";

        }
        menu2();
    }

    void menu() {
        cout <<
             "Make your choice :\n"
             "0-  Exit\n"
             "1-  Black & White Filter\n"
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
             "15- Skew Image Up  \n";
        string choice_s;
        cin >> choice_s;
        int choice = 0;
        if (is_digits(choice_s)) {
            choice = stoi(choice_s);
        } else {
            cout << "Invalid filter, please try again\n";
            menu();
        }
        if (choice == 1) {
            Black_n_white_filter();
        } else if (choice == 2) {
            invert_filter();

        } else if (choice == 3) {
            Merge_Filter();
        } else if (choice == 4) {
            flip();
        } else if (choice == 5) {
            Darken_and_Lighten_Image();
        } else if (choice == 6) {
            Rotate_Image();
        } else if (choice == 7) {
            detect_edges();
        } else if (choice == 8) {
            enlarge_image();
        } else if (choice == 9) {
            shrink_image();
        } else if (choice == 10) {
            mirror_half();
        } else if (choice == 11) {
            shuffle_image();
        } else if (choice == 12) {
            blur_image ();
        } else if (choice == 13) {
            crop_image();
        } else if (choice == 14) {
            skew_image_right ();
        } else if (choice == 15) {
            skew_image_up ();
        } else if (choice == 0)
        {
            return;
        }
        else {
            cout << "Invalid filter, please try again\n";
            menu();
        }
        menu2();
    }

};
int main() {
    photo_editor photo;
    photo.load_image();
    photo.menu();
}
