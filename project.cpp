#include<iostream>
#include<conio.h>
#include<fstream>
#include<windows.h>
using namespace std;

//Class
class product
{
	int pno;
	string name;
	float price,qty,tax,dis;
public:
	product()
	{
		pno=000;
		name="...";
		price=000;
		qty=000;
		tax=000;
		dis=000;
	}
	void create_product()
	{
		cout<<"Please Enter The Product No. of The Product: ";
		cin>>pno;
		cout<<"\n\nPlease Enter The Name of The Product: ";
		cin>>name;
		cout<<"\nPlease Enter The Price of The Product: ";
		cin>>price;
		cout<<"\nPlease Enter The Discount (%): ";
		cin>>dis;
	}
	void show_product()
	{
		cout<<"\nThe Product No. of The Product: "<<pno;
		cout<<"\nThe Name of The Product: "<<name;
		cout<<"\nThe Price of The Product: "<<price;
		cout<<"\nDiscount: "<<dis;
	}
	int getpno()
	{
		return pno;
	}
	float getprice()
	{
		return price;
	}
	string getname()
	{
		return name;
	}
	int getdis()
	{
		return dis;
	}
};
//class ends here

//Function for goto
BOOL gotoxy(const WORD x, const WORD y) {
    COORD xy;
    xy.X = x;
    xy.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
//Global declaration for stream object, object
fstream fp;
product pr;

//Function to write in file

void write_product()
{	fp.open("Shop.dat",ios::out|ios::app);
	pr.create_product();
	fp.write((char*)&pr,sizeof(product));
	fp.close();
	cout<<"\n\nThe Product Has Been Created ";
	getch();
}
//Function to read all records from file

void display_all()
{	system("cls");
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	fp.open("Shop.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		pr.show_product();
		cout<<"\n\n=============================\n";
		getch();
	}
	fp.close();
	getch();
}
//Function to read specific record from file

void display_sp(int n)
{
	int flag=0;
	fp.open("Shop.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.getpno()==n)
		{
			system("cls");
			pr.show_product();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	cout<<"\n\nrecord not exist";
	getch();
}

//Function to modify record of file

void modify_product()
{
	int no,found=0;
	system("cls");
	cout<<"\n\n\tTo Modify ";
	cout<<"\n\n\tPlease Enter The Product No. of The Product: ";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::out);
	while(fp.read((char*)&pr,sizeof(product)) && found==0)
	{
		if(pr.getpno()==no)
		{
			pr.show_product();
			cout<<"\nPlease Enter The New Details of Product:\n";
			pr.create_product();
			int pos=-1*(sizeof(product));
			fp.seekp(pos,ios::cur);
			fp.write((char*)&pr,sizeof(product));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	fp.close();
	if(found==0)
	cout<<"\n\n Record Not Found ";
	getch();
}
//Function to delete record of file

void delete_product()
{
	int no;
	system("cls");
	cout<<"\n\n\n\tDelete Record";
	cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete: ";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.getpno()!=no)
		{
			fp2.write((char*)&pr,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("Shop.dat");
	rename("Temp.dat","Shop.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}
//Function to display all products price list
void menu()
{
	system("cls");
	fp.open("Shop.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN";
		cout<<"\n Go To Admin Menu to create File";
		cout<<"\n\n Program is closing ....";
		getch();
		exit(0);
	}
	cout<<"\n\n\t\tProduct MENU\n\n";
	cout<<"====================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	cout<<"====================================================\n";
	while(fp.read((char*)&pr,sizeof(product)))
	{
		cout<<pr.getpno()<<"\t"<<pr.getname()<<"\t\t"<<pr.getprice()<<endl;
	}
	fp.close();
}
//Function to place order and generating bill for Products
void place_order()
{
	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	menu();
	cout<<"\n============================";
	cout<<"\n PLACE YOUR ORDER";
	cout<<"\n============================\n";
	do
	{
		cout<<"\n\nEnter The Product No. Of The Product : ";
		cin>>order_arr[c];
		cout<<"\nQuantity in number : ";
		cin>>quan[c];
		c++;
		cout<<"\nDo You Want To Order Another Product ? (y/n)";
		cin>>ch;
	}
	while(ch=='y' ||ch=='Y');
	cout<<"\n\nThank You For Placing The Order";
	getch();
	system("cls");
	gotoxy(36,2);
	cout<<"-INVOICE-\n";
	cout<<"\nPr No.\tPr Name \tQuantity \tPrice\t \tAmt \t\tNew Amt \n";
	for(int x=0;x<=c;x++)
	{
		fp.open("Shop.dat",ios::in);
		fp.read((char*)&pr,sizeof(product));
		while(!fp.eof())
		{
			if(pr.getpno()==order_arr[x])
			{
				amt=pr.getprice()*quan[x];
				damt=amt-(amt*pr.getdis()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<pr.getname()<<"\t"<<quan[x]<<"\t\t"<<pr.getprice()<<"\t\t"<<amt<<"\t\t"<<damt;
				total+=damt;
			}
			fp.read((char*)&pr,sizeof(product));
		}
		fp.close();
	}
	gotoxy(36,15);
	cout<<"TOTAL = "<<total;
	getch();
}
//Box
void box(void)
{
	int i;
	for(i=18;i<60;i++)
	{
		gotoxy(i,1);
		cout<<"*";
	}
	for(i=18;i<60;i++)
	{
		gotoxy(i,3);
		cout<<"*";
	}
	for(i=1;i<22;i++)
	{
		gotoxy(16,i);
		cout<<"*";
	}
	for(i=18;i<60;i++)
	{
		gotoxy(i,21);
		cout<<"*";
	}
	for(i=1;i<22;i++)
	{
		gotoxy(61,i);
		cout<<"*";
	}
}
//INTRODUCTION FUNCTION
void intro()
{
	system("cls");
	box();
	gotoxy(25,2);
	cout<<"|----------WELCOME----------|";
	gotoxy(32,5);
	cout<<"|SUPER MARKET|";
	gotoxy(34,6);
	cout<<"|BILLING|";
	gotoxy(33,10);
	cout<<"---PROJECT---";
	gotoxy(20,13);
	cout<<"MADE BY : VARNIKA KASHYAP";
	gotoxy(20,15);
	cout<<"UNIVERSITY ROLL NO.: 2014483 ";
	gotoxy(20,17);
	cout<<"SECTION: D";
	gotoxy(20,19);
	cout<<"CLASS ROLL NO.: 54 ";
	getch();
}
//ADMINISTRATOR MENU FUNCTION
void admin_menu()
{
	system("cls");
	box();
	char ch2;
	gotoxy(35,2);
	cout<<"ADMINISTRATOR MENU";
	gotoxy(32,4);
	cout<<"1.CREATE PRODUCT";
	gotoxy(28,6);
	cout<<"2.DISPLAY ALL PRODUCTS";
	gotoxy(36,8);
	cout<<"3.QUERY ";
	gotoxy(32,10);
	cout<<"4.MODIFY PRODUCT";
	gotoxy(32,12);
	cout<<"5.DELETE PRODUCT";
	gotoxy(30,14);
	cout<<"6.VIEW PRODUCT MENU";
	gotoxy(30,16);
	cout<<"7.BACK TO MAIN MENU";
	gotoxy(36,18);
	cout<<"8.EXIT";
	gotoxy(25,20);
	cout<<"Please Enter Your Choice (1-7) ";
	ch2=getche();
	switch(ch2)
	{
		case '1':
			system("cls");
			write_product();
			break;
		case '2':
			display_all();
			break;
		case '3':
			int num;
			system("cls");
			cout<<"\n\n\tPlease Enter The Product No. ";
			cin>>num;
			display_sp(num);
			break;
		case '4':
			modify_product();
			break;
		case '5':
			delete_product();
			break;
		case '6':
			menu();
			getch();
		case '7':
			break;

		case '8':
			exit(0);
			break;
		default:
			cout<<"\a";
			admin_menu();
			}


}
//THE MAIN FUNCTION OF PROGRAM
int main()
{
	char ch;
	intro();
	do
	{
		system("cls");
		box();
		gotoxy(34,2);
		cout<<"MAIN MENU";
		gotoxy(30,4);
		cout<<"01. ADMINISTRATOR";
		gotoxy(32,6);
		cout<<"02. CUSTOMER";
		gotoxy(34,8);
		cout<<"03. EXIT";
		gotoxy(25,10);
		cout<<"Please Select Your Option (1-3) ";
		ch=getche();
		switch(ch)
		{
			case '2':
				system("cls");
				place_order();
				getch();
				break;
			case '1':
				admin_menu();
				break;
			case '3':
				exit(1);
				break;
				default :
				cout<<"alert:wrong choice";
				break;
		}
	}
	while(ch!='3');
    return 0;
}

 
