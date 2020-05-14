// Report
//1.little ending : 56789 = 0000ddd5 ; 输出为d5 > dd > 00 > 00
//2.1.常量移位——编译器——输入多少位就是多少位，超出补0/1
//2.2.变量移位——CPU——如果移位的位数 b 大于了该类型的大小 sz ，则先用b对sz取模，即 b = b % sz，然后再进行移位运算
//    int类型为4字节，因此就是4 * 8 = 32位：当<< 40时，应40 % 32 = 8，即8位，8 / 4 = 2，左移两字节，
//    也就是两个数字。
//3.编译器 ：gcc        操作系统 ：linux        版本 ：ubuntu 18.04
//
//Author ：             尚林杰
//Student Number :      3019244115
//Date :                2020/3/8
//Description :         计算机系统#2

#include <stdio.h>
//functions prototype declearation
void checkShift();
void inplaceReverseArray();
void reverse_array(int a[], size_t cnt);
int gVar;

int main()
{
        int x1=23,y1=0xAA;

        //pinter test
        int B=-12345;
        int *p;
        int i;
        p=&B; //B的存储地址给p
        *p= 56789;
        char *pc;
        pc =(char*)&B;

        //check pointer addressed value
        printf("%d = %8.8x\n",p[0],p[0]);
        printf("%d = %x\n",(char)pc[0],pc[0]&0xFF);
        
        //check local address & endian
        for(i=0;i<sizeof(B);i++)
        {
               printf("localVar @ %p:%2.2x\n",pc+i,(unsigned char)*(pc+i));
        }
	
        //check global address & endian
        pc=(char *)&gVar;
        gVar=0x12345678;
        for(i=0;i<sizeof(B);i++)
        {
               printf("gVar @ %p:%2.2x\n",pc+i,(unsigned char)*(pc+i));
        }
		
	//check code address
        printf("main @ %p\n",main);

	//check lib code address
        printf("printf @ %p\n",printf);
      	
      	
      	//check inplace swap
        x1=0x23;
        y1=0xAA;
        printf("before swap: %x,%x\n",x1,y1);
        inpswap(&x1,&y1);
        printf("after swap: %x,%x\n",x1,y1);
        printf("%d,%d\n",x1,y1);

        //check Logical/arithmetic shift
      	checkShift();

     	//use inplace swap reverse array element
     	inplaceReverseArray();

}


//check shfit bits>=variable size
//learn shift 
void checkShift()
{
	unsigned uBig=0x00123456;
	int varBig=(0x00123456 >>32);
	
	//signed shift constant  by compiler
	varBig=(0x87123456 >>32);
	//code4output varBig result
        printf ("0x87123456 >>32 varBig x : ");
        printf ("%x\t\t",varBig);
        printf ("0x87123456 >>32 varBig d : ");
        printf ("%d\n",varBig);
	
	
	varBig=(0x87123456 >>40);
	//code4output varBig result
        printf ("0x87123456 >>40 varBig x : ");
        printf ("%x\t\t",varBig);
        printf ("0x87123456 >>40 varBig d : ");
        printf ("%d\n",varBig);
	

	varBig=(0x87123456 <<32);
	//code4output varBig result
        printf ("0x87123456 <<32 varBig x : ");
        printf ("%x\t\t",varBig);
        printf ("0x87123456 <<32 varBig d : ");
        printf ("%d\n",varBig);

	varBig=(0x87123456 <<40);
	//cod4output varBig result
        printf ("0x87123456 <<40 varBig x : ");
        printf ("%x\t\t",varBig);
        printf ("0x87123456 <<40 varBig d : ");
        printf ("%d\n",varBig);
	
	varBig=(0x87123456);
	varBig <<=32;
	//code4output varBig result
        printf ("0x87123456 <<=32 varBig x : ");
        printf ("%x\t\t",varBig);
        printf ("0x87123456 <<=32 varBig d : ");
        printf ("%d\n",varBig);
	
        //varable shift by CPU
	varBig=(0x87123456);
	varBig <<=40;
	//code4output varBig result
        printf ("0x87123456 <<=40 varBig x : ");
        printf ("%x\t\t",varBig);
        printf ("0x87123456 <<=40 varBig d : ");
        printf ("%d\n",varBig);


	varBig=(0x87123456);
	varBig >>=32;
	//code4output varBig result
        printf ("0x87123456 >>=32 varBig x : ");
        printf ("%x\t\t",varBig);
        printf ("0x87123456 >>=32 varBig d : ");
        printf ("%d\n",varBig);
	

	varBig=(0x87123456);
	varBig >>=40;
	//code4output varBig result
        printf ("0x87123456 >>=40 varBig x : ");
        printf ("%x\t\t",varBig);
        printf ("0x87123456 >>=40 varBig d : ");
        printf ("%d\n",varBig);
	
	//unsigned shift by variable
        uBig=0x87654321;
	uBig <<=40;
	//code4output uBig result
        printf ("0x87654321 <<=40 uBig x : ");
        printf ("%x\t\t",uBig);
        printf ("0x87654321 <<=40 uBig d : ");
        printf ("%d\n",uBig);
	
        uBig=0x87654321;
	uBig <<=32;
	//code output uBig result
        printf ("0x87654321 <<=32 uBig x : ");
        printf ("%x\t\t",uBig);
        printf ("0x87654321 <<=32 uBig d : ");
        printf ("%d\n",uBig);

	//unsigned shift by variable
        uBig=0x87654321;
	uBig >>=40;
	//code4output uBig result
        printf ("0x87654321 >>=40 uBig x : ");
        printf ("%x\t\t",uBig);
        printf ("0x87654321 >>=40 uBig d : ");
        printf ("%d\n",uBig);
	
        uBig=0x87654321;
	uBig >>=32;
	//code output uBig result
        printf ("0x87654321 >>=32 uBig x : ");
        printf ("%x\t\t",uBig);
        printf ("0x87654321 >>=32 uBig d : ");
        printf ("%d\n",uBig);


	unsigned int varBig2=(0x123456 << 40);//compiler =>0
        printf ("0x123456 << 40 varBig2 x : ");
        printf ("%x\t\t",varBig2);
        printf ("0x123456 << 40 varBig2 d : ");
        printf ("%d\n",varBig2);

}

//you can not use other array as intermidiate buffer
//参考 中文ebook  p38练习题2.11，完善代码，找出BUG
//ref  Englisg Book p91 Practice Problem 2.11 complete the code & find bugs
void inplaceReverseArray()
{
        int table1[]={1,2,3,4,5};
        int table2[]={1,2,3,4};

        //output table1 contents

        reverse_array(table1,sizeof(table1)/sizeof(int));

        //output reversed table1 contents
        printf ("table1 after reverse : ");
        for (int i = 0; i < 5; i++) {
                printf ("%d", table1[i]);
        }
        printf ("\n");


        //output table2 contents

        reverse_array(table2,sizeof(table2)/sizeof(int));

        //output reversed table2 contents
        printf ("table2 after reverse : ");
        for (int i = 0; i < 4; i++) {
                printf ("%d", table2[i]);
        }
        printf ("\n");

}


//reverseArray without buffer
//
void reverse_array(int a[], size_t cnt)
{

        size_t first, last;
        for (first = 0, last = cnt-1; first < last; first++,last--)
        {
                inpswap(&a[first], &a[last]);
        }
}


//swap without buffer
void inpswap(int*x,int*y)
{
        *x=*x^*y;
        *y=*x^*y;
        *x=*x^*y;
}

