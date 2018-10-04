/*
Decription	:硬件不支持读寄存器
Author		:Alan Zhang
Date		:2018-08-18 22:36:50
Version		:1.0.0
*/
#include "ili9325.h"
#include "systick.h"

#define RED     0xF800
#define GREEN   0x03e0
#define BLUE    0x001f
#define WHITE   0xffff
#define BLACK   0x0000


#define ILI9325_WR_H()  GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define ILI9325_WR_L()  GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define ILI9325_RS_H()  GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define ILI9325_RS_L()  GPIO_ResetBits(GPIOA,GPIO_Pin_1)

void ili9325WriteIo(u16 data)
{
    GPIOB->ODR = (GPIOB->ODR & 0x00ff)|(data&0xff00);  
    ILI9325_WR_L();  
    ILI9325_WR_H();
    GPIOB->ODR = (GPIOB->ODR & 0x00ff)|((data<<8)&0xff00);
    ILI9325_WR_L();
    ILI9325_WR_H(); 
}

static void ili9325WriteReg(u16 regAddr,u16 data)
{
    ILI9325_RS_L();
    ili9325WriteIo(regAddr);
    ILI9325_RS_H();
    ili9325WriteIo(data);
}

void ili9325StartWriteDram(void)
{
    ILI9325_RS_L();
    ili9325WriteIo(0x0022);
    ILI9325_RS_H();
}

void ili9325SetCursor(u16 x,u16 y)
{ 
	ili9325WriteReg(0x0020,y);
	ili9325WriteReg(0x0021,x);
}

void ili9325SetWindows(u16 xStart,u16 xEnd,u16 yStart,u16 yEnd)
{
    ili9325WriteReg(0x0050, yStart);
    ili9325WriteReg(0x0051, yEnd);
    ili9325WriteReg(0x0052, xStart);
    ili9325WriteReg(0x0053, xEnd);
}

static void ili9325Clear(u16 color)
{
    u16 i , j ;
    ILI9325_CS_L();
    ili9325SetCursor(0,0);
    ili9325SetWindows(0,319,0,239);
    ili9325StartWriteDram();
    for(i=0;i<240;i++)
    {
        for(j=0;j<320;j++)
        {
            ili9325WriteIo(color);
        }
    }
    ILI9325_CS_H();
}

static u8 counter = 0 ;
static u16 colorList[5] = {RED,GREEN,BLUE,WHITE,BLACK};

void ili9325Test(void)
{
    if(++counter >= 5)
    {
        counter = 0 ;
    }
    ili9325Clear(colorList[counter]);  
}


static void ili9325RegInit(void)
{
    ILI9325_CS_L();

    ili9325WriteReg(0x00e7,0x0012);
    ili9325WriteReg(0x00e5,0x4000);
    systickDelay(100);
    //==============================
    ili9325WriteReg(0x0000,0x0000);
    ili9325WriteReg(0x0000,0x0000);
    ili9325WriteReg(0x0000,0x0000);
    ili9325WriteReg(0x0000,0x0001);
    ili9325WriteReg(0x00A4,0x0001);  //CALB=1
    systickDelay(10);
    ili9325WriteReg(0x0060,0x2700);  //NL
    ili9325WriteReg(0x0008,0x0808);  //FP & BP
    ili9325WriteReg(0x0030,0x0214);  //Gamma settings
    ili9325WriteReg(0x0031,0x3715);
    ili9325WriteReg(0x0032,0x0604);
    ili9325WriteReg(0x0033,0x0E16);
    ili9325WriteReg(0x0034,0x2211);
    ili9325WriteReg(0x0035,0x1500);
    ili9325WriteReg(0x0036,0x8507);
    ili9325WriteReg(0x0037,0x1407);
    ili9325WriteReg(0x0038,0x1403);
    ili9325WriteReg(0x0039,0x0020);
    ili9325WriteReg(0x0090,0x0015);  //DIVI & RTNI
    ili9325WriteReg(0x0010,0x0410);  //BT,AP
    ili9325WriteReg(0x0011,0x0237);  //VC,DC0,DC1
    ili9325WriteReg(0x0029,0x0046);  //VCM1
    ili9325WriteReg(0x002A,0x0046);  //VCMSEL,VCM2
    ili9325WriteReg(0x0007,0x0000);
    ili9325WriteReg(0x0012,0x0189);  //VRH,VCMR,PSON=0,PON=0
    ili9325WriteReg(0x0013,0x1100);  //VDV
    systickDelay(150);
    ili9325WriteReg(0x0012,0x01B9);  //PSON=1,PON=1
    ili9325WriteReg(0x0001,0x0000);  //Other mode settings
    ili9325WriteReg(0x0002,0x0200);  //BC0=1--Line inversion
    ili9325WriteReg(0x0003,0x1038);
    ili9325WriteReg(0x0009,0x0001);
    ili9325WriteReg(0x000A,0x0000);
    ili9325WriteReg(0x000D,0x0000);
    ili9325WriteReg(0x000E,0x0030);  //VCOM equalize
    ili9325WriteReg(0x0050,0x0000);  //Display window area setting
    ili9325WriteReg(0x0051,0x00EF);
    ili9325WriteReg(0x0052,0x0000);
    ili9325WriteReg(0x0053,0x013F);
    ili9325WriteReg(0x0061,0x0001);
    ili9325WriteReg(0x006A,0x0000);
    ili9325WriteReg(0x0080,0x0000);
    ili9325WriteReg(0x0081,0x0000);
    ili9325WriteReg(0x0082,0x005F);
    ili9325WriteReg(0x0092,0x0100);
    ili9325WriteReg(0x0093,0x0701);
    systickDelay(80);
    ili9325WriteReg(0x0007,0x0100);  //BASEE=1--Display On
    ili9325WriteReg(0x0020,0x0000);
    ili9325WriteReg(0x0021,0x0000);
    
    ILI9325_CS_H();
}

void ili9325Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct ;
    GPIO_InitStruct.GPIO_Pin = 0xff00 ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_Init(GPIOB,&GPIO_InitStruct);

    GPIO_SetBits(GPIOB, 0xff00);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4) ;
    
    ili9325RegInit();
    ili9325Clear(0x0000);
}

void drawLine(u16 xStart,u16 xEnd,u16 yStart,u16 yEnd,u16 color)
{
    double yStep ;
    u16 ySteps = 0 ;
    
    yStep = (double)(yEnd - yStart)/(double)(xEnd-xStart) ;

    while(xStart<xEnd)
    {
        drawDot(xStart, yStart+(u16)(yStep*ySteps), color);
        xStart++ ;
        ySteps++ ;
    } 
}

void drawDot(u16 x,u16 y,u16 color)
{
    ILI9325_CS_L();
    ili9325SetCursor(x, y);
    ili9325SetWindows(x, x+1, y, y+1);
    ili9325StartWriteDram();
    ili9325WriteIo(color);
    ILI9325_CS_H();    
}

void fillShape(u16 xStart,u16 yStart,u16 xSize,u16 ySize,u16* dataP)
{
    u16 i,j ;
    ILI9325_CS_L();
    ili9325SetCursor(xStart, yStart);
    ili9325SetWindows(xStart, xStart+xSize, yStart, yStart+ySize);
    ili9325StartWriteDram();

    for(i=0;i<xSize;i++)
    {
        for(j=0;j<ySize;j++)
        {
            ili9325WriteIo(*(dataP));
        }
    }
    ILI9325_CS_H(); 
}




