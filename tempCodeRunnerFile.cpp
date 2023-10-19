void blur_image ()
    {
        char mod_image[256][256][3] = {0};
        int s1, s2, s3, cnt;
        //calculate the average of every 25 pixels with the currant pixel
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                s1 = s2 = s3 = cnt = 0;
                for (int x = i - 2; x <= i + 2; x++)
                {
                    for (int y = j - 2; y <= j + 2; y++)
                    {
                        
                        if (image[x][y][0] > 0)
                            cnt++;
                        s1 += image[x][y][0];
                        s2 += image[x][y][1];
                        s3 += image[x][y][2];
                        
                    }
                }
                mod_image[i][j][0] = s1 / cnt;
                mod_image[i][j][1] = s2 / cnt;
                mod_image[i][j][2] = s3 / cnt;
            }
        }
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                image[i][j][0] = mod_image[i][j][0];
                image[i][j][1] = mod_image[i][j][1];
                image[i][j][2] = mod_image[i][j][2];
            }
                
        }
    }