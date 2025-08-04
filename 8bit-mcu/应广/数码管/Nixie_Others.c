

if((data_hun==0 &&  data_ten!=0) || (data_hun==0 && data_ten==0 && data_bit!=0))//显示两位数时，百位不显示0
if(data_hun==0 && data_ten==0 && data_bit!=0)//显示一位数时，百十位不显示0


//Switch-case 段选
switch(Data_L) //低位
{		
	case 0 : LED1_Flag = 0b_0011_1111; break; // Display: 0	
	case 1 : LED1_Flag = 0b_0000_0110; break; // Display: 1
	case 2 : LED1_Flag = 0b_0101_1011; break; // Display: 2
	case 3 : LED1_Flag = 0b_0100_1111; break; // Display: 3
	case 4 : LED1_Flag = 0b_0110_0110; break; // Display: 4
	case 5 : LED1_Flag = 0b_0110_1101; break; // Display: 5
	case 6 : LED1_Flag = 0b_0111_1101; break; // Display: 6
	case 7 : LED1_Flag = 0b_0000_0111; break; // Display: 7
	case 8 : LED1_Flag = 0b_0111_1111; break; // Display: 8
	case 9 : LED1_Flag = 0b_0110_1111; break; // Display: 9

    default: LED1_Flag = 0b_0111_1111;	break;	
}




