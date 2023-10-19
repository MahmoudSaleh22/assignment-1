//ASSIGNMENT_1_NAMES_IDS_EMAILS_H

// Mohammed Ahmed Hemdan Mohammed            20220427           mohammedahmed98731@gmail.com


// Mahmoud Saleh Saad tookhey                20220431           mahmoud22saleh22@gmail.com


// Hosny Mohammed Hosny Metwally             20221048           hosnymohammed17@gmail.com

#include <iostream>
#include "bmplib.cpp"
#include "bmplib.h"
#include <unistd.h>
#include <cmath>
#include <cstring>
using namespace std;
class photo_editor{
private:
    unsigned char image[SIZE][SIZE][3];
    unsigned char image2[SIZE][SIZE][3];
public:
    void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
}
    void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, image);
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

   // filter 1 : black and white
   void black_n_white_RGB() {
   unsigned char image_gs[SIZE][SIZE];
   // first convert the RBG image to gray scale
   for (int i = 0; i < SIZE; i++){
      for (int j = 0; j < SIZE; j++){
         image_gs[i][j] = image[i][j][0]*0.299 + image[i][j][1]*0.587 + image[i][j][2]*0.114;
      }
   }
   for(int i = 0 ; i < SIZE ; i++){
      for(int j = 0 ; j < SIZE ; j++){
         /*looping on each pixel and if the value is greater than 127
         * we make that pixel white else we make it black */
         if(image_gs[i][j] > 127){
            image_gs[i][j] = 255;
         }
         else{
            image_gs[i][j] = 0;
         }
      }
   }
   // copying the values into our main array so we can use the saveImage function
   for(int i = 0 ; i < SIZE ; i++){
      for(int j = 0 ; j <SIZE ; j++){
         if(image_gs[i][j] == 0){
            for(int k = 0 ; k < 3 ; k++){
               image[i][j][k]=0;
            }
         }
         else{
            for(int k = 0 ; k < 3 ; k++){
               image[i][j][k]=255;
            }
         }
      }
   }
}
    // filter 2 : invert filter
    void invert_filter()
    {
        for (int i = 0; i < SIZE; i++)
        {
            // Reflect pixels ( new pixel = 255 - old pixel)
            for (int j = 0; j < SIZE; j++)
                image[i][j][0] = 255 - image[i][j][0];
        }

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
                image[i][j][1] = 255 - image[i][j][1];
        }

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
                image[i][j][2] = 255 - image[i][j][2];
        }
    }
    // filter 3 : Merge Filter
    void Merge_Filter()
    {
    }

    // filter 4 : flip image filter
    void flip_RGB(){
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
                  for(int k = 0 ; k<3 ; k++){
                     swap(image[i][j][k] , image[SIZE-i][j][k]);
                  }
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
                  for(int k = 0 ; k<3 ;k++){
                     swap(image[i][j][k] , image[i][SIZE-j][k]);
                  }
                }
            }
        }
        else
        {
            cout << "wrong direction, please try again\n";
            flip_RGB();
        }
    }
    // filter 5 : Darken and Lighten Image
    void Darken_and_Lighten_Image()
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
                    image[i][j][0] = image[i][j][0] + (255 - image[i][j][0])/2;
                }

            }
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][1] = image[i][j][1] + (255 - image[i][j][1])/2;
                }

            }
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][2] = image[i][j][2] + (255 - image[i][j][2])/2;
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
                    image[i][j][0] = image[i][j][0]/2;
                }

            }
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][1] = image[i][j][1]/2;
                }

            }
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][2] = image[i][j][2]/2;
                }

            }
        }
    }

    // filter 6 : rotate image
    void Rotate_Image()
    {
    }

    // filter 7 : detect edges
void detect_edges_RGB(){
    /*
         * i have followed in this filter a well known algorithm called
         * sobel edge detection algorithm
         * i have read about it in this article
         * https://homepages.inf.ed.ac.uk/rbf/HIPR2/sobel.htm
    */
   unsigned char image_gs[SIZE][SIZE];
   // first convert the RBG image to gray scale
   for (int i = 0; i < SIZE; i++){
      for (int j = 0; j < SIZE; j++){
         image_gs[i][j] = image[i][j][0]*0.299 + image[i][j][1]*0.587 + image[i][j][2]*0.114;
      }
   }
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
                  pixel += (image_gs[i+k][j+l] * row_mask[k][l]);
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
                  pixel += (image_gs[i+k][j+l] * column_mask[k][l]);
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
            // else we make it black
            // And it's considered as an edge
            else{
               res[i][j] = 0;
            }
      }
   }
   // returning to the main grayscale array
   for (int i = 0; i < 254; ++i) {
      for (int j = 0; j < 254; ++j) {
            image_gs[i][j] = res[i][j];
      }
   }
   // getting back the values into our main array
   // to use the saveImage() function
   for(int i = 0 ; i < SIZE ; i++){
      for(int j = 0 ; j < SIZE ; j++){
         if(image_gs[i][j] == 0){
            for(int k = 0 ; k < 3 ;k++){
               image[i][j][k]=0;
            }
         }
         else{
            for(int k = 0 ; k < 3 ;k++){
               image[i][j][k]=255;
            }
         }
      }
   }
}
    //filter 8 : enlarge image
    void Enlarge_image ()
    {
        // first of all choose the quarter you want to enlarge
        cout << "Choose the number of the required quarter :\n1. quarter one\n2. quarter two\n3. quarter three\n4. quarter four\n";
        int quarter;
        cin >> quarter;
        unsigned char mod_image[2 * SIZE][2 * SIZE][3];
        //enlarging image dimensions to double
        for (int i = 0; i < 2 * SIZE; i++)
        {
            for (int j = 0; j < 2 * SIZE; j++)
                mod_image[i][j][0] = image[i / 2][j / 2][0];
        }
        for (int i = 0; i < 2 * SIZE; i++)
        {
            for (int j = 0; j < 2 * SIZE; j++)
                mod_image[i][j][1] = image[i / 2][j / 2][1];

        }
        for (int i = 0; i < 2 * SIZE; i++)
        {
            for (int j = 0; j < 2 * SIZE; j++)
                mod_image[i][j][2] = image[i / 2][j / 2][2];
        }


        // detecting the quarter based on the input
        if (quarter == 1)
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][0] = mod_image[i][j][0];
                    image[i][j][1] = mod_image[i][j][1];
                    image[i][j][2] = mod_image[i][j][2];
                }
            }
        }
        else if (quarter == 2)
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][0] = mod_image[i][255 + j][0];
                    image[i][j][1] = mod_image[i][255 + j][1];
                    image[i][j][2] = mod_image[i][255 + j][2];
                }
            }
        }
        else if (quarter == 3)
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][0] = mod_image[255 + i][j][0];
                    image[i][j][1] = mod_image[255 + i][j][1];
                    image[i][j][2] = mod_image[255 + i][j][2];
                }
            }
        }
        else
        {
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][0] = mod_image[255 + i][255 + j][0];
                    image[i][j][1] = mod_image[255 + i][255 + j][1];
                    image[i][j][2] = mod_image[255 + i][255 + j][2];
                }
            }
        }

    }

    // filter 9 : Shrink Image
    void shrink_image ()
    {
    }

    // filter a : mirror half
    void mirror_half_RGB(){
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
                  for(int k = 0 ; k < 3 ; k++){
                     image[SIZE-i][j][k] = image[i][j][k];
                  }
                }
            }
        }
        else if(target_half == 2){
            // copying each pixel into the opposite pixel
            // in the upper half which makes the lower mirror effect
            for (int i = 0; i <SIZE/2; ++i) {
                for (int j = 0; j < SIZE ; ++j) {
                  for(int k = 0 ; k<3 ; k++){
                     image[i][j][k] = image[SIZE-i][j][k];
                  }
                }
            }
        }
        else if(target_half == 3){
            // copying each pixel into the opposite pixel
            // in the left half which makes the right mirror effect
            for (int i = 0; i <SIZE; ++i) {
                for (int j = 0; j < SIZE/2 ; ++j) {
                  for(int k = 0 ; k<3 ; k++){
                     image[i][j][k] = image[i][SIZE-j][k];
                  }
                }
            }
        }
        else if(target_half == 4){
            // copying each pixel into the opposite pixel
            // in the right half which makes the left mirror effect
            for (int i = 0; i <SIZE; ++i) {
                for (int j = 0; j < SIZE/2 ; ++j) {
                  for(int k = 0 ; k<3 ;k++){
                     image[i][SIZE-j][k] = image[i][j][k];
                  }
                }
            }
        }
        else
        {
            cout << "Wrong choice, please try again";
            mirror_half_RGB();
        }
    }


    //filter b : shuffle image
     void shuffle_image()
    {
        // create four arrays
        unsigned char quarter1[128][128][3], quarter2[128][128][3], quarter3[128][128][3], quarter4[128][128][3];

        // save the quarters of the original photo in these four arrays
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                quarter1[i][j][0] = image[i][j][0];
                quarter1[i][j][1] = image[i][j][1];
                quarter1[i][j][2] = image[i][j][2];
            }
        }
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                quarter2[i][j][0] = image[i][127 + j][0];
                quarter2[i][j][1] = image[i][127 + j][1];
                quarter2[i][j][2] = image[i][127 + j][2];
            }
        }
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                quarter3[i][j][0] = image[127 + i][j][0];
                quarter3[i][j][1] = image[127 + i][j][1];
                quarter3[i][j][2] = image[127 + i][j][2];
            }
        }
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                quarter4[i][j][0] = image[127 + i][127 + j][0];
                quarter4[i][j][1] = image[127 + i][127 + j][1];
                quarter4[i][j][2] = image[127 + i][127 + j][2];
            }
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
                {
                    image[i][j][0] = quarter1[i][j][0];
                    image[i][j][1] = quarter1[i][j][1];
                    image[i][j][2] = quarter1[i][j][2];
                }
                if (a[0] == 2)
                {
                    image[i][j][0] = quarter2[i][j][0];
                    image[i][j][1] = quarter2[i][j][1];
                    image[i][j][2] = quarter2[i][j][2];
                }
                if (a[0] == 3)
                {
                    image[i][j][0] = quarter3[i][j][0];
                    image[i][j][1] = quarter3[i][j][1];
                    image[i][j][2] = quarter3[i][j][2];
                }
                if (a[0] == 4)
                {
                    image[i][j][0] = quarter4[i][j][0];
                    image[i][j][1] = quarter4[i][j][1];
                    image[i][j][2] = quarter4[i][j][2];
                }
            }
        }

        //quarter two in the original photo
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if (a[1] == 1)
                {
                    image[i][128 + j][0] = quarter1[i][j][0];
                    image[i][128 + j][1] = quarter1[i][j][1];
                    image[i][128 + j][2] = quarter1[i][j][2];
                }
                else if (a[1] == 2)
                {
                    image[i][128 + j][0] = quarter2[i][j][0];
                    image[i][128 + j][1] = quarter2[i][j][1];
                    image[i][128 + j][2] = quarter2[i][j][2];
                }
                else if (a[1] == 3)
                {
                    image[i][128 + j][0] = quarter3[i][j][0];
                    image[i][128 + j][1] = quarter3[i][j][1];
                    image[i][128 + j][2] = quarter3[i][j][2];
                }
                else
                {
                    image[i][128 + j][0] = quarter4[i][j][0];
                    image[i][128 + j][1] = quarter4[i][j][1];
                    image[i][128 + j][2] = quarter4[i][j][2];
                }
            }
        }

        //quarter three in the original photo
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if (a[2] == 1)
                {
                    image[128 + i][j][0] = quarter1[i][j][0];
                    image[128 + i][j][1] = quarter1[i][j][1];
                    image[128 + i][j][2] = quarter1[i][j][2];
                }
                else if (a[2] == 2)
                {
                    image[128 + i][j][0] = quarter2[i][j][0];
                    image[128 + i][j][1] = quarter2[i][j][1];
                    image[128 + i][j][2] = quarter2[i][j][2];
                }
                else if (a[2] == 3)
                {
                    image[128 + i][j][0] = quarter3[i][j][0];
                    image[128 + i][j][1] = quarter3[i][j][1];
                    image[128 + i][j][2] = quarter3[i][j][2];
                }
                else
                {
                    image[128 + i][j][0] = quarter4[i][j][0];
                    image[128 + i][j][1] = quarter4[i][j][1];
                    image[128 + i][j][2] = quarter4[i][j][2];
                }
            }
        }

        //quarter four in the original photo
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                if (a[3] == 1)
                {
                    image[128 + i][128 + j][0] = quarter1[i][j][0];
                    image[128 + i][128 + j][1] = quarter1[i][j][1];
                    image[128 + i][128 + j][2] = quarter1[i][j][2];
                }
                else if (a[3] == 2)
                {
                    image[128 + i][128 + j][0] = quarter2[i][j][0];
                    image[128 + i][128 + j][1] = quarter2[i][j][1];
                    image[128 + i][128 + j][2] = quarter2[i][j][2];
                }
                else if (a[3] == 3)
                {
                    image[128 + i][128 + j][0] = quarter3[i][j][0];
                    image[128 + i][128 + j][1] = quarter3[i][j][1];
                    image[128 + i][128 + j][2] = quarter3[i][j][2];
                }
                else
                {
                    image[128 + i][128 + j][0] = quarter4[i][j][0];
                    image[128 + i][128 + j][1] = quarter4[i][j][1];
                    image[128 + i][128 + j][2] = quarter4[i][j][2];
                }
            }
        }

    }

    // filter c : blur image
    void blur_image ()
    {
    }

    // filter d : crop image
    void crop_image_RBG(){
        cout << "Please enter x and y seperated by space:";
        int x,y;cin>>x>>y;
        cout << "please enter l and w seperated by space:";
        int l,w;cin>>l>>w;
        // making the area between 0 and x to white
        for (int i = 0; i <SIZE ; ++i) {
            for (int j = 0; j <x ; ++j) {
                for(int k = 0 ; k <3 ; k++){
                  image[i][j][k] = 255;
               }
            }
        }
        // making the area between x+width and the end of the image to white
        for (int i = 0; i <SIZE ; ++i) {
            for (int j = x+w; j <SIZE ; ++j) {
                for(int k = 0 ; k <3 ; k++){
                  image[i][j][k] = 255;
               }
            }
        }
        // making the area between 0 and y to white
        for (int i = 0; i <y ; ++i) {
            for (int j = 0; j <SIZE ; ++j) {
                for(int k = 0 ; k <3 ; k++){
                  image[i][j][k] = 255;
               }
            }
        }
        // making the area between y+length and the end of the image to white
        for (int i = y+l; i <SIZE ; ++i) {
            for (int j = 0; j <SIZE ; ++j) {
               for(int k = 0 ; k <3 ; k++){
                  image[i][j][k] = 255;
               }
            }
        }
        // eventually its result that the area we want to stay it stays the same
        // while the rest of the image become white
    }

    //filter e : skew image right
    //filter e : skew image right
    void skew_image_right ()
    {
        unsigned char mod_img[256][256][3] = {0};

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
            {
                mod_img[i][j + shift][0] = (image[i][j * 2][0] + image[i][j * 2 + 1][0]) / 2;
                mod_img[i][j + shift][1] = (image[i][j * 2][1] + image[i][j * 2 + 1][1]) / 2;
                mod_img[i][j + shift][2] = (image[i][j * 2][2] + image[i][j * 2 + 1][2]) / 2;
            }

        }
        for (int i = 0; i < 256; i++)
            for (int j = 0; j < 256; j++)
            {
                image[i][j][0] = mod_img[i][j][0];
                image[i][j][1] = mod_img[i][j][1];
                image[i][j][2] = mod_img[i][j][2];
            }
    }

    //filter f : skew image up
    void skew_image_up ()
    {
    }
    void menu2() {
        cout << "Make your choice :\n"
                "0-  Exit\n"
                "1-  save image\n"
                "2-  return to filter menu\n";
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
            saveImage();
        }
        else if(choice == 2) {
            menu();
        }
        else if (choice == 0) {
          exit(0);
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
            black_n_white_RGB();
        } else if (choice == 2) {
            invert_filter();
        } else if (choice == 3) {
            Merge_Filter();
        } else if (choice == 4) {
            flip_RGB();
        } else if (choice == 5) {
            Darken_and_Lighten_Image();
        } else if (choice == 6) {
            Rotate_Image();
        } else if (choice == 7) {
            detect_edges_RGB();
        } else if (choice == 8) {
            Enlarge_image();
        } else if (choice == 9) {
            shrink_image();
        } else if (choice == 10) {
            mirror_half_RGB();
        } else if (choice == 11) {
            shuffle_image();
        } else if (choice == 12) {
            blur_image ();
        } else if (choice == 13) {
            crop_image_RBG();
        } else if (choice == 14) {
            skew_image_right ();
        } else if (choice == 15) {
            skew_image_up ();
        } else if (choice == 0)
        {
            exit(0);
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
    photo.loadImage();
    photo.menu();
}