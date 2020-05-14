/**************************************************************
 * Author ：尚林杰
 * Date ：2020.2.24
 * Description : 计算机系统#1
 * Question : 写入数据部分for为什么成功不了？
 * *************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENXD 16
#define LENBI 4

void printASCIIleft(char*, int);    //左侧输出ASCII
void printASCIIright(char*, int);   //右侧输出ASCII
void printASCIIbin(char*, int);
void printBin(char*, int);          //输出二进制
void printDec(char*, int, const char*);   //输出对应十进制数字，后续进行转换

char *asciiabl[]={ \
    "NUL","SOH","STX","ETX","EOT",
    "ENQ","ACK","BEL","BS","TAB",
    "LF", "VT", "FF", "CR", "SO",
    "SI","DLE","DC1","DC2","DC3",
    "DC4","NAK","SYN","ETB","CAN",
    "EM","SUB","ESC","FS","GS","RS",
    "US","SP","!"};
    
int main(int argc,char * argv[])
{
    //未输入-X指令
    if (argc < 3) {
        printf ("Please enter a command.\n");
        printf ("-x/X for hexadecimal.\n");
        printf ("-d/D for decimal.\n");
        printf ("-b/B for binary.\n");

        return -1;
    }

    else if (strcmp(argv[1], "-x") && strcmp(argv[1], "-X") &&
            strcmp(argv[1], "-d") && strcmp(argv[1], "-D") && 
            strcmp(argv[1], "-b") && strcmp(argv[1], "-B")) {
                printf ("Please enter a correct command.\n");
                printf ("-x/X for hexadecimal.\n");
                printf ("-d/D for decimal.\n");
                printf ("-b/B for binary.\n");

                return -1;
            }

    FILE *fp = NULL;
    fp = fopen(argv[2], "rb");

    //打开失败
    if (fp == NULL) {
        printf ("Opening file %s failed.", argv[2]);
        return -1;
    }

    char data;
    
    char lenXD[LENXD];
    char lenBI[LENBI];
    int loc = 0;

    while(!feof(fp)) {
        data = fgetc(fp);

        //输入为-x -X -d -D
        if (!strcmp(argv[1], "-x") || !strcmp(argv[1], "-X") || 
            !strcmp(argv[1], "-d") || !strcmp(argv[1], "-D")) {
             //在lenXD中填充字符                   
            if (loc < LENXD && (!feof(fp))) {
                lenXD[loc] = data;
                loc++;
            }
                
                /*for (int i = 0; i < LENXD, !feof(fp); i++) {
                    data = fgetc(fp);
                    lenXD[i] = data;
                }*/

            else {
                //输出
                if (!strcmp(argv[1], "-x")) {
                    printASCIIleft(lenXD, LENXD);
                    printDec(lenXD, LENXD, "%2.2x\t");
                    printf("\n");
                } 
                else if (!strcmp(argv[1], "-X")) {
                    printDec(lenXD, LENXD, "%2.2x\t");
                    printf("  ");
                    printASCIIright(lenXD, LENXD);
                } 
                else if (!strcmp(argv[1], "-d")) {
                    printASCIIleft(lenXD, LENXD);
                    printDec(lenXD, LENXD, "%03d\t");
                    printf("\n");
                } 
                else if (!strcmp(argv[1], "-D")) {
                    printDec(lenXD, LENXD, "%03d\t");
                    printf("  ");
                    printASCIIright(lenXD, LENXD);
                }

                loc = 0;
                lenXD[loc] = data;
                loc++;
            }

        }
    
        //输入为 -b -B
         else {
            //在lenBI中填充字符
            if (loc < LENBI && (!feof(fp))) {
                lenBI[loc] = data;
                loc++;
            }
            
            /*for (int i = 0; i < LENBI, !feof(fp); i++) {
                data = fgetc(fp);
                lenBI[i] = data;
            }*/

            else {
            if (!strcmp(argv[1], "-b")) {
                printASCIIbin(lenBI, LENBI);
                printBin(lenBI, LENBI);
                printf("\n");
                } 
            else if (!strcmp(argv[1], "-B")) {
                printBin(lenBI, LENBI);
                printf("  ");
                printASCIIright(lenBI, LENBI);
            }
            loc = 0;
            lenBI[loc] = data;
            loc++;

         }

        }   
    }   //end of while(!feof(fp))

    fclose(fp);
    return 0;
    
}   
//////////////////////////////////////////////////////end of main

//左侧输出ASCII表，小间距
void printASCIIleft(char *len, int LEN)
{
    char data;

    for (int i = 0; i < LEN; i++) {
        data = len[i];
        if (data < 0) {
            printf ("%c\t", '.');
        }
        else if (data <= 0x20) {
            printf ("%s\t", asciiabl[(unsigned char)data]);
        }
        else {
            printf ("%c\t", data);
        }    
    }
    
    printf ("\n");
}

//右侧输出ASCII，无间距
void printASCIIright(char *len, int LEN)
{
    char data;

    for (int i = 0; i < LEN; i++) {
        data = len[i];
        if (data < 0) {
            printf ("%c", '.');
        }
        else if (data <= 0x20) {
            printf ("%s", asciiabl[(unsigned char)data]);
        }
        else {
            printf ("%c", data);
        }    
    }
    
    printf ("\n");
}

//二进制左侧输出ASCII，大间距
void printASCIIbin(char *len, int LEN)
{
    char data;

    for (int i = 0; i < LEN; i++) {
        data = len[i];
        if (data < 0) {
            printf ("%c\t\t", '.');
        }
        else if (data <= 0x20) {
            printf ("%s\t\t", asciiabl[(unsigned char)data]);
        }
        else {
            printf ("%c\t\t", data);
        }    
    }
    
    printf ("\n");
}

//输出十进制，后续转换
void printDec(char *len, int LEN, const char *fmt)
{
    for (int i = 0; i < LEN; i++) {
        printf (fmt, (unsigned char)len[i]);
    }
}

//输出二进制
void printBin(char* len, int LEN)
{
   for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < 8; j++)
            printf("%c", (len[i] & (0x80 >> j)) != 0 ? '1' : '0'); // get binary method
        printf("\t"); 
   }
}

