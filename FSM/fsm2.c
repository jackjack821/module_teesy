/**                               											  
 ******************************************************************************
 *@copyright  https://www.jianshu.com/p/917c0fb8778b
 *@author  	  wuyijun                                                        
 *@version    2.使用switch case                                                
 *@date       19/9/2019                                                
 *@brief                                                           
 ******************************************************************************
 */													   						  

int main()
{
    int state = SPRING;
    while (1)
    {
        switch(state){
        case SPRING:
            spring_thing();
            state = SUMMER;
            break;
        case SUMMER:
            summer_thing();
            state = AUTUMN;
            break;
        case AUTUMN:
            autumn_thing();
            state = WINTER;
            break;
        case WINTER:
            winter_thing();
            state = SPRING;
            break;
        default:
            break;

        }
        sleep(1);
    }

    return 0;
}