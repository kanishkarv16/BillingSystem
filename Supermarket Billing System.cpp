#include<iostream>                              // go to compiler options
#include<stdlib.h>								// go to settings	
#include<conio.h>								// go to code generation
#include<iomanip>
#include<ctime>
#include<string>								// language standard - ISO C++11
using namespace std;							// warning check iso c/c++ conformace - yes

//FUNCTIONS	
void display_home_page();
void display_login_panel();
void main_menu();
void create_bill();
void add_item();
int check_equality(string,string);
void modify_or_delete_item();
void show_cart_items();
void show_products();
void generate_final_bill();
void empty_cart();

bool products_present=false;

class products {
	private : // protected lets only its derived class access its data
		int id; bool set_id=false;
		int nos=0;
		double price,discount,value;
		string name,unit;
	public :
	// constructor to initialize the data members of products
	products(int id, string name, double price, double discount,string unit)
	{
		this->id=id; 
		this->price=price; 
		this->discount=discount; 
		this->name=name;
		this->unit=unit;	
	} 	
	
	void display()
	{
		cout << "\t     " << id << "\t\t" << name << "\t\t\t" << unit << "\t\t" << fixed <<
		setprecision(2) << price << "\t\t" << discount << "%" << endl;	
	}
		
	void display_cart_item()
	{
		if(set_id==true)
		{
			products_present=true;
			value=nos*price-(discount/100)*(nos*price);
			cout << "\t\t  " << id << "\t" << name << "\t\t" << unit << "\t" << price << "\t"
			<< discount << "\t\t" << nos << "\t\t" << value << endl;
		}
	}
	
	friend void add_item();
	friend void modify_or_delete_item();
	friend void empty_cart();
	friend void generate_final_bill();
};
//DATABASE
products p[10]={
		products(1,"RICE",30,5,"1KG"),
		products(2,"MILK",50,2,"500ML"),
		products(3,"COKE",20,4,"125ML"),
		products(4,"ORANGES",90,10,"1KG"),
		products(5,"SOAPS",40,20,"120G"),
		products(6,"EGGS",30,3,"6NO'S"),
		products(7,"BADAM",122,40,"1KG"),
		products(8,"KETCHUP",72,30,"950G"),
		products(9,"OIL",130,25,"1PACK"),
		products(10,"KURKURE",20,5,"52G")
	};


void display_home_page(){
	int choice;
	cout << "\n\n\n\n\n\n\n";
	restart :
	cout << "\t\t\t\t\t------------------------------\n";
	cout << "\t\t\t\t\t| Supermarket Billing System |\n";
	cout << "\t\t\t\t\t------------------------------\n\n";
	cout << "\t\t\t\t\t  Press 1 = login / 0 = quit\n\n";
	cout << "\t\t\t\t\t        Enter : "; 
	start:
		cin >> choice;
	if(choice == 1)
	{
		system("cls");
		display_login_panel();
		return ;
	} 
	else if(choice == 0)
		return; 
	else 
	{
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t\t      *** Please Enter a valid choice ***";
		cout << "\n\n\n\n\n";
		goto restart ;
	}
	return ;
}

void display_login_panel(){
	cout << "\n\n\n\n\n\n\n\n\n";
	restart:
	char ch;
	string username, password="",response;
	cout << "\t\t\t\t\t------------- LOGIN -------------\n\n" << endl;
	cout << "\t\t\t\t\tEnter Username(admin) : "; 
		cin >> username;
	cout << "\t\t\t\t\tEnter password(admin) : "; 
	while(1)
	{
		ch = getch();
		if( (int) ch == 13)
			break;
		else if((int)ch == 8)
		{
			password.pop_back();
			cout << "\b \b";		
		}
		else
		{
			password.push_back(ch);
			cout << "*";	
		}
	}
	if(username == "admin" and password == "admin")
	{
		system("cls");
		cout << "\n\n\t\t\t\t\t\tWelcome Admin \n\n\n" << endl;
		main_menu();
		return ;
	}
	else
	{
		system("cls");
		cout << "\n\n\t\t\t\t          *** Credentials Are Wrong ***" << endl;
		cout << "\n\t\t\t\t                    Try Again";
		cout << "\n\n\n\n\n";
		goto restart;
	}
}

void main_menu(){
	int choice;
	system("cls");
	cout << "\n\n\n\n\n";
	start:
	cout << "\t\t\t\t\t      ------------------\n";
	cout << "\t\t\t\t\t      |    MAIN MENU   |\n";
	cout << "\t\t\t\t\t      ------------------\n\n";
	cout << "\t\t\t\t\t      1.CREATE BILL" << endl;
	cout << "\t\t\t\t\t      2.SHOW PRODUCTS" << endl;
	cout << "\t\t\t\t\t      3.EXIT(LOGOUT)" << endl;
	cout << "\n\t\t\t\t\t      Enter : "; 
	cin >> choice;
	switch(choice)
	{
		case 1:
			create_bill();
			break;
		case 2:
			show_products();
			break;		
		case 3:
			cout << "\n\n\n\n\n\n\n\n\n";
			break;
			
		default:
			system("cls");
			cout << "\n\n\t\t\t\t\t  *** Enter a Valid Choice ***\n\n\n";
			goto start; 
	}
	return ;
}

void create_bill(){
	system("cls");
	cout << "\n\n\n\n\n";
	int choice,n;
	cout << "\t\t\t\t\t      --------------------\n";
	cout << "\t\t\t\t\t      |    CREATE BILL   |\n";
	cout << "\t\t\t\t\t      --------------------\n\n";
	cout << "\t\t\t\t\t      1.ADD ITEM INTO BILL" << endl;
	cout << "\t\t\t\t\t      2.MODIFY/DELETE AN ITEM IN BILL" << endl;
	cout << "\t\t\t\t\t      3.SHOW CART ITEMS" << endl;
	cout << "\t\t\t\t\t      4.SHOW ALL PRODUCTS" << endl;
	cout << "\t\t\t\t\t      5.EMPTY CART" << endl;
	cout << "\t\t\t\t\t      6.GENERATE FINAL BILL" << endl;
	cout << "\t\t\t\t\t      7.EXIT(GO BACK TO MAIN MENU)" << endl;
	cout << "\n\t\t\t\t\t      Enter : "; 
	cin >> choice;	
	switch(choice)
	{
		case 1:
			add_item();
			break;
		case 2:
			modify_or_delete_item();
			break;
		case 3:
			show_cart_items();
			if(products_present==false)
			{
				cout << "\n\t\t\t\t\t    Cart Is Empty. Please Add Items\n";	
				cout << "\n\t\t\t\t\t    Press Anything to Add Items...";
				getch();
				add_item();	
				return;	
			}
			cout << "\n\n\t\t\t\tPress any Key to redirect to CREATE BILL Menu...";
			getch();
			create_bill();
			break;
		case 4:
			show_products();
			break;
		case 5:
			empty_cart();
			break;
		case 6:
			generate_final_bill();
			break;
		case 7:
			main_menu();
			break;
		default:
			system("cls");
			cout << "\n\n\t\t\t\t\t  *** Enter a Valid Choice ***\n\n\n";
			create_bill();			
	}
	return ;
}

void add_item(){
	int	res_id;string res_name; int i,nos;
//	string res_name; Need To Be Updated
	int response;
	system("cls");
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t      -------------------\n";
	cout << "\t\t\t\t\t      |    ADD ITEMS    |\n";
	cout << "\t\t\t\t\t      -------------------\n\n";
	cout << "\t\t\t\t\t      1.ADD ITEM BY ITS NAME\n"; 
	cout << "\t\t\t\t\t      2.ADD ITEM BY ITS ID\n" ; 
	cout << "\t\t\t\t\t      3.EXIT TO CREATE BILL MENU\n";
	cout << "\n\t\t\t\t\t      Enter : "; 
		cin >> response;
	if(response == 1 or response == 2)
	{
		system("cls");
		cout << "\n\n\n\n\n";
			cout << "\t\t\t\t\t      -------------------\n";
			cout << "\t\t\t\t\t      |    ADD ITEMS    |\n";
			cout << "\t\t\t\t\t      -------------------\n\n";
		
		if(response == 1)
		{
			cout << "\t\t\t\t\t      ENTER ITEM NAME : ";
			cin >> res_name;
			for(i=0;i<10;++i)
			{
				if(check_equality(res_name,p[i].name))
				break;
			}
		}
		
		else
		{
			cout << "\t\t\t\t\t      ENTER ITEM ID : ";
			cin >> res_id;
			for(i=0;i<10;++i)
			{	
				if(res_id == p[i].id) // in case of successful search i gets stored
				break;
			}
		}
		
		if(i==10) // in case of unsuccessful search
		{
			cout << "\n\t\t\t\t\tProduct not found. Try Again\n\n";	
			cout << "\n\n\t\t\t\t\t Press Anything to Retry...";
			getch();
			add_item();
			return ;
		}
		else
		{
			cout << "\n";
			cout << "\t\t  --------------------------------------------------------------------------------------\n";
			cout << "\t\t     ID\t\tPRODUCT NAME\t\tUNIT\t\tPRICE\t\tDISCOUNT" << endl;
			cout << "\t\t  --------------------------------------------------------------------------------------\n";
			cout << "\t" ;
			p[i].display();
			
			if(p[i].set_id==false) 
			p[i].set_id=true;      
			cout << "\n\n\t\t\t\t\t      ENTER NUMBER OF UNITS : "; 
			cin >> nos;
			p[i].nos+=nos;
			cout << "\n\n";
			cout << "\t\t\t\t\t     Product added successfully\n\n";
			cout << "\n\t\t\t\t\tPress any key to Display Cart Item List "; 
			getch();		
			show_cart_items();	
			abc:
			cout << "\n\t\t\t\t\t\t1.ADD MORE ITEMS\n\t\t\t\t\t\t2.EXIT TO CREATE BILL MENU\n\n\t\t\t\t\t\tENTER : ";	
			cin >> response;
			if(response==1)
			add_item();
			else if(response==2)
			create_bill();
			else
			{
				system("cls");
				cout << "\n\n\n\t\t\t\t\t\t*** Enter a valid choice ***\n";
				goto abc;
			}
		}
	}	
	
	else if(response == 3)
	create_bill();
	
	else
	{
		cout << "\n\t\t\t\t\t Enter A Valid Response and Try Again\n\n";	
		cout << "\n\n\t\t\t\t\t Press Anything to Retry...";
		getch();
		add_item();
	}			
}

int check_equality(string a,string b)
{
	int i,j;
	for(i=0,j=0;a[i]!='\0' and b[j]!='\0';++i,++j)
	{
		if(toupper(a[i])==toupper(b[j]))
		continue;
		else
		break;
	}
	return a[i]=='\0' and b[j]=='\0' ? 1 : 0;
}

void modify_or_delete_item()
{
	int	res_id,i,new_q,o;
//	string res_name; Need To Be Updated
	int response;
	system("cls");
	end:
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t      ----------------------\n";
	cout << "\t\t\t\t\t      |    CHANGE ITEMS    |\n";
	cout << "\t\t\t\t\t      ----------------------\n\n";
	cout << "\t\t\t\t\t      1.MODIFY QUANTITY OF AN ITEM IN CART\n"; 
	cout << "\t\t\t\t\t      2.DELETE ITEM IN CART\n"; 
	cout << "\t\t\t\t\t      3.EXIT TO CREATE BILL MENU\n";
	cout << "\n\t\t\t\t\t      Enter : "; cin >> response;
	if(response==1)
	{
//		modify_item();
		if(products_present==false)
		{
			
			cout << "\n\n\n\t\t\t\t\t     Cart Is Empty. Please Add Items\n";	
			cout << "\n\t\t\t\t\t      Press Any KEY to Add Items...";
			getch();
			add_item();	
			return;	
		}
		start:
		show_cart_items();	
		cout << "\n\n\t\t\t\t\tENTER ITEM ID: ";
		cin >> res_id;
		for(i=0;i<10;++i)
		{	
			if(res_id == p[i].id and p[i].set_id==true) // in case of successful search i gets stored
			break;
		}
		if(i==10) // in case of unsuccessful search
		{
			cout << "\n\t\t\t\t\tProduct not found. Try Again\n\n";	
			cout << "\n\n\t\t\t\t\t Press Anything to Retry...";
			getch();
			modify_or_delete_item();
			return ;
		}
		else
		{
			cout << "\n\t\t\t\t\tENTER NEW QUANTITY: ";
			cin >> new_q;
			if(new_q<=0)
			{
				cout << "\n\t\t\t\t\tDO YOU WANT TO DELETE ITEM?" << endl;
				cout << "\n\t\t\t\t\t1.YES";
				cout << "\n\t\t\t\t\t2.NO" << endl;
				cout << "\n\t\t\t\t\tENTER: ";
				cin >> o;
				if(o==1)
				{
					goto start1;
				}
				else if(o==2)
				{
					system("cls");
					cout << "\n\t\t\t\t\tCHANGE ITEM QUANTITY TO NON-ZERO\n";
					show_cart_items();
					goto start;
				}
				else
				{
					system("cls");
					cout << "\n\t\t\t\t\tENTER A VALID NUMBER AND TRY AGAIN\n";
					goto start;
				}
			}
			p[i].nos=new_q;
			system("cls");
			cout << "\n\n\n\n\n";
			cout << "\t\t\t\t\tProduct Modified Successfully\n\n";
			cout << "\n\t\t\t\t\tPress any key to Display Cart Item List "; 
			getch();		
			cout << "\t\t\t******UPDATED CART******\n";
			show_cart_items();	
			abc:
			cout << "\n\n\t\t\t\t\t1.CHANGE MORE ITEMS\n\t\t\t\t\t2.EXIT TO CREATE BILL MENU\n\t\t\t\t\tENTER : ";	
			cin >> response;
			if(response==1)
			modify_or_delete_item();
			else if(response==2)
			create_bill();
			else
			{
				system("cls");
				goto abc;
			}
		}
	}
	else if(response==2)
	{
//		delete_item();
		if(products_present==false)
		{
			cout << "\n\n\n\t\t\t\t\t     Cart Is Empty. Please Add Items\n";	
			cout << "\n\t\t\t\t\t      Press Any KEY to Add Items...";
			getch();
			add_item();	
			return;	
		}
		show_cart_items();
		cout << "\n\n\t\t\t\t\tENTER ITEM ID: ";
		cin >> res_id;
		start1:
		for(i=0;i<10;++i)
		{	
			if(res_id == p[i].id and p[i].set_id==true) // in case of successful search i gets stored
			break;
		}
		if(i==10) // in case of unsuccessful search
		{
			cout << "\n\t\t\t\t\tProduct not found. Try Again\n\n";	
			cout << "\n\n\t\t\t\t\t Press Anything to Retry...";
			getch();
			modify_or_delete_item();
			return ;
		}
		else
		{
			p[i].set_id=false;
			p[i].nos=0;
			system("cls");
			cout << "\n\n\n\n\n";
			cout << "\t\t\t\t\tProduct Modified Successfully\n\n";
			cout << "\n\t\t\t\t\tPress any key to Display Cart Item List "; 
			getch();		
			cout << "\t\t\t******UPDATED CART******\n";
			show_cart_items();	
			abc1:
			cout << "\n\n\t\t\t\t\t1.CHANGE MORE ITEMS\n\t\t\t\t\t2.EXIT TO CREATE BILL MENU\n\t\t\t\t\tENTER : ";	
			cin >> response;
			if(response==1)
			modify_or_delete_item();
			else if(response==0)
			create_bill();
			else
			{
				system("cls");
				goto abc1;
			}
		}
		
	}
	else if(response==3)
	{
		create_bill();
	}
	else
	{
		system("cls");
		cout << "\n\t\t\t\t\tENTER A VALID NUMBER AND TRY AGAIN\n";
		cout << "\n\t\t\t\t PRESS ANYTHING TO RETRY...";
		goto end;
	}
}

void show_cart_items(){
	system("cls");
	cout << "\n\n";
	cout << "\t\t\t\t\t    -----------CART ITEMS-----------\n\n\n";	
	cout << "\t\t----------------------------------------------------------------------------------------\n";
	cout << "\t\t  ID\tPRODUCT NAME\tUNIT\tPRICE\tDISCOUNT\tQUANTITY\tVALUE" << endl;
	cout << "\t\t----------------------------------------------------------------------------------------\n";			
	for(int i=0;i<10;++i)
	{
		p[i].display_cart_item();
	}
	cout << "\n\n";
}

void empty_cart(){
	system("cls");
	if(products_present==false)
	{
		cout << "\n\n\t\t\t\t      Cart is already empty\n";
	}
	else
	{
		int i;
		for(i=0;i<10;++i)
		{
			p[i].set_id=false;
			p[i].nos=0;
			p[i].value=0;
		}
		cout << "\n\n\t\t\t\t      Cart Has Been Deleted\n";
	}
	cout << "\t\t\t\t      Press KEY To Go To Create Bill Menu....";
	getch();
	create_bill();
	return;
}

void show_products(){
	int i;
	char s;
	system("cls");
	cout << "\n\n";
	cout << "\t\t\t\t\t-----------PRODUCTS-----------\n\n\n";
	cout << "\t  --------------------------------------------------------------------------------------\n";
	cout << "\t     ID\t\tPRODUCT NAME\t\tUNIT\t\tPRICE\t\tDISCOUNT" << endl;
	cout << "\t  --------------------------------------------------------------------------------------\n";
	for(i=0;i<10;i++)
	{
		p[i].display();
	}
	cout << "\n\n\t\t\t\t   *** YOU WILL BE REDIRECTED TO CREATE BILL MENU ***" << endl;
	cout << "\n\n\t\t\t\t\t Press Anything to Continue...";
	getch();
	create_bill();
}

void generate_final_bill(){
	int response;
	string payment_method="";
	system("cls");
	if(products_present==false)
	{
		cout << "\n\n\n\n\n\t\t\t\tCart Is Empty. Please Add Items to proceed to payment\n";	
		cout << "\n\t\t\t\tPress Any KEY to Add Items...";
		getch();
		add_item();	
		return;	
	}
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t      -----------------------\n";
	cout << "\t\t\t\t\t      |    PAYMENT METHOD   |\n";
	cout << "\t\t\t\t\t      -----------------------\n\n";
	cout << "\t\t\t\t\t      1.CASH" << endl;
	cout << "\t\t\t\t\t      2.CARD" << endl;
	cout << "\t\t\t\t\t      3.MOBILE PAYMENTS" << endl;
	cout << "\t\t\t\t\t      4.CANCEL/ABORT" << endl << endl;
	cout << "\t\t\t\t\t      ENTER: ";
	cin >> response;
	if(response==1)
	payment_method="CASH";
	else if(response==2)
	payment_method="CARD";
	else if(response==3)
	payment_method="ONLINE";
	else
	empty_cart();
	if(products_present==false)
	{
		cout << "\n\t\t\t\tCart Is Empty. Please Add Items\n";	
		cout << "\n\t\t\t\t Press Anything to Add Items...";
		getch();
		add_item();	
		return;	
	}
	double total_value=0;
	int total_quantity=0,total_item=0;
	system("cls");
	cout << "\n\n";
	cout << "\t\t\t\t\t\t\t VNR MART" << endl;
	cout << "\t\t\t\t\t\t\tTAX INVOICE" << endl;
	cout << "\t\t------------------------------------------------------------------------------------------\n";
	time_t now = time(0);   
	char* date_time = ctime(&now);
	cout << "\t\tBill No:5001\t\t\t" << "\t\t\tBill Date:" << date_time << endl;
	cout << "\n\t\t------------------------------------------------------------------------------------------\n";
	cout << "\t\t   ID\tPRODUCT NAME\tUNIT\tPRICE\tDISCOUNT\tQUANTITY\tVALUE" << endl;
	cout << "\t\t------------------------------------------------------------------------------------------\n";			
	for(int i=0;i<10;++i)
	{
		if(p[i].set_id==true)
		total_item++;
		p[i].display_cart_item();
		total_value=total_value+p[i].value;
		total_quantity=total_quantity+p[i].nos;
	}
	cout << "\t\t------------------------------------------------------------------------------------------\n";			
	cout << "\t\t   Items: " << total_item << "\t\t\tQuantity: " << total_quantity << "\t\tTotal Payable Amount: " << total_value << endl;
	cout << "\t\t------------------------------------------------------------------------------------------\n";
	cout << "\t\t             <---------------Payment Received From Customer--------------->\n\n";			
	cout << "\t\t   Payment Method: " << payment_method;
}

int main(){
	display_home_page();
	cout << "\n\n\t\t\t\t\t\tTHANKS FOR USING\n\n\n"; 	
	return 0;
}
