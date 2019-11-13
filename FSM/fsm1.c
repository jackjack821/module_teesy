/**                               											  
 ******************************************************************************
 *@copyright  https://www.jianshu.com/p/917c0fb8778b
 *@author  	  wuyijun                                                        
 *@version    https://www.jianshu.com/p/917c0fb8778b                                                  
 *@date       19/9/2019                                                
 *@brief                                                           
 ******************************************************************************
 */													   						  
#include <stdio.h>
enum year_state
{
    SPRING,
    SUMMER,
    AUTUMN,
    WINTER
};

void spring_thing()
{
    printf("hello spring\n");
}
void summer_thing()
{
    printf("hello summer\n");
}
void autumn_thing()
{
    printf("hello autumn\n");
}
void winter_thing()
{
    printf("hello winter\n");
}

int main()
{
    int state = SPRING;
    while (1)
    {
        if (state == SPRING)
        {
            spring_thing();//相应的处理
            state = SUMMER;//状态改变
        }
        else if (state == SUMMER)
        {
            summer_thing();
            state = AUTUMN;
        }
        else if (state == AUTUMN)
        {
            autumn_thing();
            state = WINTER;
        }
        else if (state == WINTER)
        {
            winter_thing();
            state = SPRING;
        }
        sleep(1);
    }

    return 0;
}