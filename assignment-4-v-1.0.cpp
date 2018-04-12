#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
unsigned char cinputimage[SIZE][SIZE][RGB];  //color image
unsigned char binputimage[SIZE][SIZE];       //black image

void enlarge (unsigned char binputimage[SIZE][SIZE],int quarter1,int quarter2);
void enlargecol (unsigned char cinputimage[SIZE][SIZE][RGB],int quarter1,int quarter2);

void loadfile(int &bc){   //load file
    char imagename[100];
    bc=0;
    cout<<"**************************"<<endl;
    cout<<"ahlan ya user ya habibi"<<endl;
    cout<<"1-Black \n2-Coloured Image"<<endl;
    cout<<"your choice:";
    cin>>bc;
    cout<<"Enter the name of the image you want to process:";
    cin>>imagename;
    strcat(imagename,".bmp");
    if(bc==1){
        readGSBMP(imagename,binputimage);
    }
    else if(bc==2){
        readRGBBMP(imagename,cinputimage);
    }
    cout<<"***************************************\n";
}

void menu(int &filter){   //filter menu
    filter=0;
    cout<<"Please select a filter to apply or 0 to exit:"<<endl;
    cout<<"1- Black & White Filter\n2- Invert Filter\n3- Merge Filter\n4- Flip Image\n5- Darken and Lighten Image\n";
    cout<<"6- Rotate Image\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink Image\n10-Glass image\n";
    cout<<"11-Blur Image\n12-Save the image to a file\n13-Load another image\n0- Exit";
    cout<<"\nchoice:";
    cin>>filter;
}

void savebimage (unsigned char binputimage[SIZE][SIZE]){       //save black image
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, binputimage);
}

void savecimage (unsigned char cinputimage[SIZE][SIZE][RGB]){       //save color image
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, cinputimage);
}

void editbimage(unsigned char binputimage[SIZE][SIZE],int filter){
    if (filter==1){   //black and white filter
        int counter=0,avg=0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                   avg+=binputimage[i][j];
                   counter+=1;
            }
        }
        avg=avg/counter;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                if(binputimage[i][j]>avg){
                    binputimage[i][j]=255;
                }
                else if(binputimage[i][j]<avg){
                    binputimage[i][j]=0;
                }
            }
        }
    }

    else if (filter==2){   //invert filter
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                   if(binputimage[i][j]==255){
                        binputimage[i][j]=0;
                   }
                   else if(binputimage[i][j]==0){
                        binputimage[i][j]=255;
                   }
                   else {
                        binputimage[i][j]=255-binputimage[i][j];
                   }
            }
        }
    }
    else if (filter==3){   //merge
        char srr[100],out[100];
        cout<<"enter the image you want to merge with : " ;
        cin>>srr;
        cout<<"enter the name you want to save this image with : ";
        cin>>out;
        strcat(srr,".bmp");
        strcat(out,".bmp");

        unsigned char anotherIMG[SIZE][SIZE];
        readGSBMP(srr,anotherIMG);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                int avg = (anotherIMG[i][j] +binputimage[i][j])/2;
                anotherIMG[i][j] =avg;
                // binputimage[i][j] =avg;
            }

        }
        writeGSBMP(out, anotherIMG);
    }
    else if (filter==4){   //Flip
        char f;
        cout<<"Flip (h)orizontally or (v)ertically ?";
        cin>>f;
        unsigned char teminputimage[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                teminputimage[i][j]=binputimage[i][j];
            }
        }
        if (f=='h'||f=='H'){
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                   binputimage[i][j]=teminputimage[i][SIZE-j];
                }
            }
        }
        else if (f=='v'||f=='V'){
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                   binputimage[i][j]=teminputimage[255-i][j];
                }
            }
        }
    }

    else if (filter==5){   //Darken-lighten
        char opt;
        do{
            cout<<"what do you want darken or lighten the image"<<endl;
            cin>>opt;
        } while(!(opt =='l'|| opt =='L'||opt=='d' || opt =='D'));

        if(opt =='l'|| opt =='L'){
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                    if(binputimage[i][j] <= 170){
                        binputimage[i][j] += char((((50.0 / 100))*binputimage[i][j]));
                    }
                    else
                        binputimage[i][j] =255;
                }
            }

        }
        else{
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) 
                        binputimage[i][j] -=char((((50.0 / 100))*binputimage[i][j]));

            }
        }
        savebimage(binputimage);
    }


    else if(filter==6){   //rotate image
        string cho;
        cout<<"Rotate (90), (180) or (270) degrees?";
        cin>>cho;
        unsigned char teminputimage[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                    teminputimage[i][j]=binputimage[i][j];
            }
        }
        if(cho=="270"){
            for (int i=0; i<SIZE; i++) {
                for (int j=0; j<SIZE; j++) {
                            binputimage[i][j]=teminputimage[j][255-i];
                }
            }
        }
        else if(cho=="90"){
            for (int i=0; i<SIZE; i++) {
                for (int j=0; j<SIZE; j++) {
                            binputimage[i][j]=teminputimage[255-j][i];
                }
            }
        }
        else if(cho=="180"){
            for (int i=0; i<SIZE; i++) {
                for (int j=0; j<SIZE; j++) {
                            binputimage[i][j]=teminputimage[255-i][255-j];
                }
            }
        }
        }

    else if (filter==7){   //detect edges filter

        editbimage(binputimage,1);
        int h=1;
        bool  teminputimage[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                teminputimage[i][j]=false;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                if (binputimage[i][j]==0){
                while(h<5){
                    if ((binputimage[i][j+h]==0||binputimage[i][j-h]==0)&&(binputimage[i+h][j]==0&&binputimage[i-h][j]==0)){
                            ++h;
                    }
                    else{
                        break;
                    }
                }
                if(h==5){
                    teminputimage[i][j]=true;
                    h=1;
                }
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                if(teminputimage[i][j]==true){
                    binputimage[i][j]=255;
                }
            }
        }

    }

    else if( filter == 8){  //enlarge filter
        bool rightinput;
        do{
            rightinput = false;
            cout<<"which quarter you want to enlarge 1, 2,3 or 4? "<<endl;
            int choice;
            cin>>choice;
            switch(choice){
            case 1:
                enlarge(binputimage,0,0);
                break;
            case 2:
                enlarge(binputimage,0,SIZE/2);
                break;
            case 3:
                enlarge(binputimage,SIZE/2,0);
            case 4:
                enlarge(binputimage,SIZE/2,SIZE/2);
                break;
            default:
                cout<<"WRONG INPUT "<<endl;
                rightinput = true;
                cin.clear();
                cin.ignore(256, '\n');
            }
            }while(rightinput);
    }
     else if (filter==9){
         cout<<"what do you want to do with the image \n";
         cout<<"shrink by 1. 1/2 \n2. 1/4  \n3. 1/3  \n option : ";
         int  opt;
         cin >>opt;
         if(opt ==1){
            int x=0 ,y=0;
            unsigned char out[SIZE][SIZE];
            for (int i = 0; i < SIZE-1; i+=2) {
                int y=0;
                
                for (int j = 0; j< SIZE; j+=2) {
                    int avg =binputimage[i][j+1]+binputimage[i+1][j]+binputimage[i][j]+binputimage[i+1][j+1];
                    avg /=4;
                    out[x][y] =avg;
                    y++;
                    if(y==SIZE/2){
                        for(int k=y ; k<SIZE;++k)
                            out[x][k]=255;   
                    }
                }
                x++;
                if(x>=SIZE/2){
                    for(int k=x ; k<SIZE;++k){
                        for(int w=0 ; w<SIZE;++w){  out[k][w]=255;}
                    }
                        
                }
            }
            savebimage(out);
            }
        else if(opt==2){
            int x=0 ,y=0;
            unsigned char out[SIZE][SIZE];
            for (int i = 0; i < SIZE-1; i+=4) {
                int y=0;
                // start from 0 to 1/4 width of img
                for (int j = 0; j< SIZE; j+=4) {
                    // get avg for the 16 pixels
                    int avg =+binputimage[i+2][j]+binputimage[i+2][j+1]+
                    binputimage[i+2][j+2]+binputimage[i][j+2]+binputimage[i+1][j+2]+binputimage[i][j+1]+
                    binputimage[i+1][j]+binputimage[i][j]+binputimage[i+1][j+1]
                    +binputimage[i][j+3]+binputimage[i+1][j+3] +binputimage[i+2][j+3]+
                    binputimage[i+3][j]+binputimage[i+3][j+1]+binputimage[i+3][j+2]+binputimage[i+3][j+3];

                    avg /=16;
                    out[x][y] =avg;
                    y++;

                    if(y==SIZE/4){ // if y==size/4 make all the next pixels in white
                        for(int k=y ; k<SIZE;++k)
                            out[x][k]=255;   
                    }
                }
                x++;
                if(x>=SIZE/4){//if x==size/4 make all the next rows in white
                    for(int k=x ; k<SIZE;++k){//to iterate over the rows pixels
                        for(int w=0 ; w<SIZE;++w){  out[k][w]=255;}
                    }
                        
                }
            }
            savebimage(out);
        }
        else if(opt ==3){
            int x=0 ,y=0;
            unsigned char out[SIZE][SIZE];
            for (int i = 0; i < SIZE-1; i+=3) {
                int y=0;
                
                for (int j = 0; j< SIZE; j+=3) {
                    int avg =+binputimage[i+2][j]+binputimage[i+2][j+1]+
                    binputimage[i+2][j+2]+binputimage[i][j+2]+binputimage[i+1][j+2]+binputimage[i][j+1]+
                    binputimage[i+1][j]+binputimage[i][j]+binputimage[i+1][j+1];
                    avg /=9;
                    out[x][y] =avg;
                    y++;

                    if(y==SIZE/3){
                        for(int k=y ; k<SIZE;++k)
                            out[x][k]=255;   
                    }
                }
                x++;
                if(x>=SIZE/3){
                    for(int k=x ; k<SIZE;++k){
                        for(int w=0 ; w<SIZE;++w){  out[k][w]=255;}
                    }
                        
                }
            }
            savebimage(out);

        }
     }

    else if (filter==10){  //glass filter
                unsigned char teminputimage[SIZE][SIZE];
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j< SIZE; j++) {
                        teminputimage[i][j]=binputimage[i][j];
                    }
                }


           for (int i=0; i<SIZE; i++)
              for (int j=0; j<SIZE; j++) {
                 int srci, srcj;
                 do {
                    srci = i + rand()%5-2;
                    srcj = j + rand()%5-2;
                 }
                 while (srci < 0 || srcj < 0 || srci >= SIZE || srcj >= SIZE);
                    binputimage[i][j] = teminputimage[srci][srcj];
              }
                }

    else if(filter==11){   //blur filter
        unsigned char teminputimage[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                    teminputimage[i][j]=binputimage[i][j];
                }
            }
        for (int i=1; i<SIZE-1; i++) {
            for (int j=1; j<SIZE-1; j++) {
                    int avg = 0;
                    avg += teminputimage[i-1][j];    // N
                    avg += teminputimage[i-1][j-1];  // NW
                    avg += teminputimage[i][j-1];    // W
                    avg += teminputimage[i+1][j-1];  // SW
                    avg += teminputimage[i+1][j];    // S
                    avg += teminputimage[i+1][j+1];  // SE
                    avg += teminputimage[i][j+1];    // E
                    avg += teminputimage[i-1][j+1];  // NE
                    binputimage[i][j] = avg / 8;
                }
            }
        }

    else if (filter==12){  //Save image
        savebimage(binputimage);
    }


}


void editcimage(unsigned char cinputimage[SIZE][SIZE][RGB],int filter){
    if(filter==1){   //black&white color image
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                unsigned char r = cinputimage[i][j][0];
                unsigned char g = cinputimage[i][j][1];
                unsigned char b = cinputimage[i][j][2];
                binputimage[i][j] = (unsigned char)(.299*r + .587*g + .114*b);
            }
        }
        editbimage(binputimage,1);
        savebimage(binputimage);
    }

    else if(filter==2){   //invert color image
       for (int i=0; i<SIZE; i++) {
          for (int j=0; j<SIZE; j++) {
             for (int c=0; c<3; c++) {
                cinputimage[i][j][c] = 255-cinputimage[i][j][c];
             }
          }
       }
    }

    else if(filter==4){  //flip color image
        char f;
        cout<<"Flip (h)orizontally or (v)ertically ?";
        cin>>f;
        unsigned char teminputimage[SIZE][SIZE][RGB];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0;k<3;k++){
                    teminputimage[i][j][k]=cinputimage[i][j][k];
                }
            }
        }
        if (f=='h'||f=='H'){
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                    for (int k=0; k<3;k++){
                        cinputimage[i][j][k]=teminputimage[i][SIZE-j][k];
                    }
                }
            }
        }
        else if (f=='v'||f=='V'){
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                    for (int k=0; k<3;k++){
                        cinputimage[i][j][k]=teminputimage[255-i][j][k];
                    }
                }
            }
        }
    }

    else if(filter==6){   //rotate image
        string cho;
        cout<<"Rotate (90), (180) or (270) degrees?";
        cin>>cho;
        unsigned char teminputimage[SIZE][SIZE][RGB];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0;k<3;k++){
                    teminputimage[i][j][k]=cinputimage[i][j][k];
                }
            }
        }
        if(cho=="270"){
            for (int i=0; i<SIZE; i++) {
                for (int j=0; j<SIZE; j++) {
                    for (int k=0;k<RGB;k++){
                            cinputimage[i][j][k]=teminputimage[j][255-i][k];
                    }
                }
            }
        }
        else if(cho=="90"){
            for (int i=0; i<SIZE; i++) {
                for (int j=0; j<SIZE; j++) {
                    for (int k=0;k<RGB;k++){
                            cinputimage[i][j][k]=teminputimage[255-j][i][k];
                    }
                }
            }
        }
        else if(cho=="180"){
            for (int i=0; i<SIZE; i++) {
                for (int j=0; j<SIZE; j++) {
                    for (int k=0;k<RGB;k++){
                            cinputimage[i][j][k]=teminputimage[255-i][255-j][k];
                    }
                }
            }
        }
        }

    else if(filter==7){   //detect image edges     needs another look
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                unsigned char r = cinputimage[i][j][0];
                unsigned char g = cinputimage[i][j][1];
                unsigned char b = cinputimage[i][j][2];
                binputimage[i][j] = (unsigned char)(.299*r + .587*g + .114*b);
            }
        }
        editbimage(binputimage,7);
        savebimage(binputimage);
    }

    else if( filter == 8){  //enlarge filter
        bool rightinput;
        do{
            rightinput = false;
            cout<<"which quarter you want to enlarge 1, 2,3 or 4? "<<endl;
            int choice;
            cin>>choice;
            switch(choice){
            case 1:
                enlargecol(cinputimage,0,0);
                break;
            case 2:
                enlargecol(cinputimage,0,SIZE/2);
                break;
            case 3:
                enlargecol(cinputimage,SIZE/2,0);
            case 4:
                enlargecol(cinputimage,SIZE/2,SIZE/2);
                break;
            default:
                cout<<"WRONG INPUT "<<endl;
                rightinput = true;
                cin.clear();
                cin.ignore(256, '\n');
            }
            }while(rightinput);
    }

    else if(filter==9){   //shrink
        string cho;
        cout<<"Shrink to (1/2), (1/3) or (1/4)?";
        cin>>cho;
        if (cho=="1/2"){
        unsigned char r[SIZE][SIZE][RGB];
        for (int i=0; i<SIZE; i+=2) {
            for (int j=0; j<SIZE; j+=2) {
                    r[i][j][0] = (cinputimage[i][j][0]+cinputimage[i][j+1][0]+cinputimage[i+1][j][0]+cinputimage[i+1][j+1][0])/4;
                    r[i][j][1] = (cinputimage[i][j][1]+cinputimage[i][j+1][1]+cinputimage[i+1][j][1]+cinputimage[i+1][j+1][1])/4;
                    r[i][j][2] = (cinputimage[i][j][2]+cinputimage[i][j+1][2]+cinputimage[i+1][j][2]+cinputimage[i+1][j+1][2])/4;
            }
        }
        int x=0;
        int y=0;
        unsigned char outputimage[SIZE][SIZE][RGB];
        for(int i=0;i<SIZE/2;i++){
            for(int j=0;j<SIZE/2;j++){
                if(x>255){
                    x=0;
                    y=y+2;
                }
                outputimage[i][j][0]=r[y][x][0];
                outputimage[i][j][1]=r[y][x][1];
                outputimage[i][j][2]=r[y][x][2];
                x=x+2;
            }
        }
        savecimage(outputimage);
        }
        else if (cho=="1/3"){
        unsigned char r[SIZE][SIZE][RGB];
        for (int i=0; i<SIZE; i+=3) {
            for (int j=0; j<SIZE; j+=3) {
                    r[i][j][0] = (cinputimage[i][j][0]+cinputimage[i][j+1][0]+cinputimage[i][j+2][0]+cinputimage[i+1][j][0]+cinputimage[i+1][j+1][0]+cinputimage[i+1][j+2][0]+cinputimage[i+2][j][0]+cinputimage[i+2][j+1][0]+cinputimage[i+2][j+2][0])/9;
                    r[i][j][1] = (cinputimage[i][j][1]+cinputimage[i][j+1][1]+cinputimage[i][j+2][1]+cinputimage[i+1][j][1]+cinputimage[i+1][j+1][1]+cinputimage[i+1][j+2][1]+cinputimage[i+2][j][1]+cinputimage[i+2][j+1][1]+cinputimage[i+2][j+2][1])/9;
                    r[i][j][2] = (cinputimage[i][j][2]+cinputimage[i][j+1][2]+cinputimage[i][j+2][2]+cinputimage[i+1][j][2]+cinputimage[i+1][j+1][2]+cinputimage[i+1][j+2][2]+cinputimage[i+2][j][2]+cinputimage[i+2][j+1][2]+cinputimage[i+2][j+2][2])/9;
            }
        }
        int x=0;
        int y=0;
        unsigned char outputimage[SIZE][SIZE][RGB];
        for (int i=0;i<SIZE;i+=3){
            for (int j=0;j<SIZE;j+=3){
                if (x>SIZE/3){
                    x=0;
                    y=y+1;
                }
                if(y>SIZE/3){
                    goto label2;
                }
                outputimage[y][x][0]=r[i][j][0];
                outputimage[y][x][1]=r[i][j][1];
                outputimage[y][x][2]=r[i][j][2];
                x=x+1;
            }
        }
label2:
        savecimage(outputimage);
        }
        else if (cho=="1/4"){
        unsigned char r[SIZE][SIZE][RGB];
        for (int i=0; i<SIZE; i+=4) {
            for (int j=0; j<SIZE; j+=4) {
                    r[i][j][0] = (cinputimage[i][j][0]+cinputimage[i][j+1][0]+cinputimage[i][j+2][0]+cinputimage[i][j+3][0]+cinputimage[i+1][j][0]+cinputimage[i+1][j+1][0]+cinputimage[i+1][j+2][0]+cinputimage[i+1][j+3][0]+cinputimage[i+2][j][0]+cinputimage[i+2][j+1][0]+cinputimage[i+2][j+2][0]+cinputimage[i+2][j+3][0]+cinputimage[i+3][j][0]+cinputimage[i+3][j+1][0]+cinputimage[i+3][j+2][0]+cinputimage[i+3][j+3][0])/16;
                    r[i][j][1] = (cinputimage[i][j][1]+cinputimage[i][j+1][1]+cinputimage[i][j+2][1]+cinputimage[i][j+3][1]+cinputimage[i+1][j][1]+cinputimage[i+1][j+1][1]+cinputimage[i+1][j+2][1]+cinputimage[i+1][j+3][1]+cinputimage[i+2][j][1]+cinputimage[i+2][j+1][1]+cinputimage[i+2][j+2][1]+cinputimage[i+2][j+3][1]+cinputimage[i+3][j][1]+cinputimage[i+3][j+1][1]+cinputimage[i+3][j+2][1]+cinputimage[i+3][j+3][1])/16;
                    r[i][j][2] = (cinputimage[i][j][2]+cinputimage[i][j+1][2]+cinputimage[i][j+2][2]+cinputimage[i][j+3][2]+cinputimage[i+1][j][2]+cinputimage[i+1][j+1][2]+cinputimage[i+1][j+2][2]+cinputimage[i+1][j+3][2]+cinputimage[i+2][j][2]+cinputimage[i+2][j+1][2]+cinputimage[i+2][j+2][2]+cinputimage[i+2][j+3][2]+cinputimage[i+3][j][2]+cinputimage[i+3][j+1][2]+cinputimage[i+3][j+2][2]+cinputimage[i+3][j+3][2])/16;
            }
        }
        int x=0;
        int y=0;
        unsigned char outputimage[SIZE][SIZE][RGB];
        for(int i=0;i<SIZE/4;i++){
            for(int j=0;j<SIZE/4;j++){
                if(x>255){
                    x=0;
                    y=y+4;
                }
                outputimage[i][j][0]=r[y][x][0];
                outputimage[i][j][1]=r[y][x][1];
                outputimage[i][j][2]=r[y][x][2];
                x=x+4;
            }

        }
        savecimage(outputimage);
        }
    }

    else if(filter==10){  //glass filter
            unsigned char teminputimage[SIZE][SIZE][RGB];
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j< SIZE; j++) {
                    for(int k=0;k<3;k++){
                        teminputimage[i][j][k]=cinputimage[i][j][k];
                    }
                }
            }

            for (int i=0; i<SIZE; i++)
                for (int j=0; j<SIZE; j++) {
                    int srci, srcj;
                    do {
                        srci = i + rand()%5-2;
                        srcj = j + rand()%5-2;
                    }
                    while (srci < 0 || srcj < 0 || srci >= SIZE || srcj >= SIZE);
                    for (int c=0; c<RGB; c++)
                        cinputimage[i][j][c] = teminputimage[srci][srcj][c];
                }
    }

    else if(filter==11){  //blur filter
        unsigned char teminputimage[SIZE][SIZE][RGB];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0;k<3;k++){
                    teminputimage[i][j][k]=cinputimage[i][j][k];
                }
            }
        }
        for (int i=1; i<SIZE-1; i++) {
            for (int j=1; j<SIZE-1; j++) {
                for (int c=0; c<RGB; c++) {
                    int avg = 0;
                    avg += teminputimage[i-1][j][c];    // N
                    avg += teminputimage[i-1][j-1][c];  // NW
                    avg += teminputimage[i][j-1][c];    // W
                    avg += teminputimage[i+1][j-1][c];  // SW
                    avg += teminputimage[i+1][j][c];    // S
                    avg += teminputimage[i+1][j+1][c];  // SE
                    avg += teminputimage[i][j+1][c];    // E
                    avg += teminputimage[i-1][j+1][c];  // NE
                    cinputimage[i][j][c] = avg / 8;
                }
            }
        }
    }

    else if(filter==12){
        savecimage(cinputimage);
    }
}


int main()
{
    label:
    int bc=0,filter=0;
    loadfile(bc);   //load black or colored image
        while(true){
        menu(filter);  //load filter
        if(filter==0){
            break;
        }
        if (filter==13){
            goto label;
        }
        if (bc==1){     //black image
            editbimage(binputimage,filter);
        }
        else if (bc==2){   // colored image
            editcimage(cinputimage,filter);
        }

    }

    return 0;
}

void enlargecol (unsigned char cinputimage[SIZE][SIZE][RGB],int quarter1,int quarter2){  //enlarge color
    int x=0 , y;
    unsigned char teminputimage[SIZE][SIZE][RGB];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0;k<3;k++){
                    teminputimage[i][j][k]=cinputimage[i][j][k];
                }
            }
        }
    for(int i = quarter1; i < (quarter1 + (SIZE/2)); ++i){
        y = 0;
        for (int j = quarter2; j < (quarter2 + (SIZE/2)); ++j) {
                for (int k=0;k<3;k++){
                    cinputimage[x][y][k] = teminputimage[i][j][k];
                    cinputimage[x][y+1][k] = teminputimage[i][j][k];
                    cinputimage[x+1][y][k] = teminputimage[i][j][k];
                    cinputimage[x+1][y+1][k] = teminputimage[i][j][k];
                }

            y+=2;
        }
        x+=2;
}
}

void enlarge (unsigned char binputimage[SIZE][SIZE],int quarter1,int quarter2){     //enlarge black
    int x=0 , y;
    unsigned char tmp[SIZE][SIZE];
        for(int i=0;i<SIZE;++i){
            for(int j=0;j<SIZE;++j){
                tmp[i][j] = binputimage[i][j];
            }
        }
        for(int i = quarter1; i < (quarter1 + (SIZE/2)); ++i){
        y = 0;
        for (int j = quarter2; j < (quarter2 + (SIZE/2)); ++j) {
            binputimage[x][y] = tmp[i][j];
            binputimage[x][y+1] = tmp[i][j];
            binputimage[x+1][y] = tmp[i][j];
            binputimage[x+1][y+1] = tmp[i][j];
            y+=2;
        }
        x+=2;
}
}
