//https://blog.csdn.net/l455702707/article/details/88142820


#include <stdio.h>
#define N 3
int st7511_send_cmd(int * g); 
int average2(int LCD_SWRESET[N]); 
int main()
{
	int LCD_SWRESET[3]={2, 0xAE, 0xA5};	
	int * a = LCD_SWRESET; //数组名类型是int *
	printf("我们需要的数据是：%d\n",st7511_send_cmd(LCD_SWRESET)); //数组名传递给指针
	printf("我们需要的数据是：%d\n",average2(LCD_SWRESET)); //数组名传递给数组名
	printf("我们需要的数据是：%d\n",average2(a));     //指针传递给数组名
	printf("我们需要的数据是：%d\n",st7511_send_cmd(a));     //指针传递给指针
}
int st7511_send_cmd(int * g) //定义int *型的指针参数
{
	int *a=g; 
	int ave,sum=0;  
	for(;g<a+N;g++) {
		sum+=*g;	}
	return ave=sum/N;		
}






int average2(int LCD_SWRESET[N])
{
	int ave,sum=0;  
	for(int i=0;i<N;i++){
		sum+=LCD_SWRESET[i];}	
	return ave=sum/N;		
}