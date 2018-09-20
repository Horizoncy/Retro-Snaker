
//有考虑过用GUI写这个但是.......还是算了吧....在这里写的关键在于每秒刷新界面.所以获取时间和方向键显得尤为重要. 
//mfc和qt???.............不存在的........... 
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<cstdio>
#include<windows.h> 
#include<fstream>
#include<string>
#include<cstring> 
using namespace std;
int main_menu(); 
class user
{
	public:
		virtual void registor();
		virtual bool login();
	protected:
	    string name,password;
};
class vip:public user 
{  
    public:
    	bool  login(); 
}; 
bool vip::login()
{ 
int flag=0;
	int n=0;
	char c;
	string temp; 
	string pass; 
	int main_menu();
	ifstream fin("vipuser.txt");
	if(!fin) 
	{
		cout<<"文件打开失败"<<endl; 
		system("pause");
		exit(0);
	}
	cout<<"请输入用户名 ";
	cin>>name;
	while (fin>>temp)
	{
		n=0;
		if (temp==name)
		{	
			fin>>temp;
			cout<<"请输入密码: ";//cin>>pass;
			while((c=getch())&&c!=13){pass.push_back(c);cout<<"*";}//密文密码 
			if (pass==temp) 
			{
				cout<<"登录成功"<<endl;
				return true; 
			}
			else cout<<"密码错误"<<endl;
		} 
		if(flag==1) break;
		else continue;
	}
	if(flag==0)
	{
	    cout<<"对不起找不到该用户"<<endl;
	    system("pause");
		return false;
	}
	else return true;
	
}  
void user:: registor()
{
	ofstream fout("user.txt",ios::app);
	if(!fout) {
		cout<<"无法打开文件"<<endl;
		system("pause");
		exit(0);
	}
	
	cout<<"请输入用户名: ";
	cin>>name;
	cout<<"请输入密码: ";
	cin>>password;
	cout<<"注册成功!"<<endl;
	fout<<name<<" "<<password<<endl;
	fout.close();
} 
bool user::login()
{
	int flag=0;
	int n=0;
	char c;
	string temp; 
	string pass; 
	ifstream fin("user.txt");
	if(!fin) 
	{
		cout<<"文件打开失败"<<endl; 
		system("pause");
		exit(0);
	}
	cout<<"请输入用户名 ";
	cin>>name;
	while (fin>>temp)
	{
		n=0;
		if (temp==name)
		{	
			fin>>temp;
			cout<<"请输入密码: ";//cin>>pass;
			while((c=getch())&&c!=13){pass.push_back(c);cout<<"*";}//密文密码 
			if (pass==temp) 
			{
				cout<<"登录成功"<<endl;
				return true; 
			}
			else cout<<"密码错误"<<endl;
		} 
		if(flag==1) break;
		else continue;
	}
	if(flag==0)
	{
	    cout<<"对不起找不到该用户"<<endl;
	    system("pause");
		return false;
	}
	else return true;
} 
int main_menu()
{
	system("cls");
	bool flag; 
    user op;
    vip op1; 
    cout<<"\t************************************************************"<<endl;
    cout<<"\t\t\t1.登录\n";
    cout<<"\t\t\t2.注册\n";
    cout<<"\t\t\t3.退出\n";
    cout<<"\t\t\t4.vip登录\n";
    cout<<"\t************************************************************"<<endl;
    cout<<"请输入序号进行操作：";
    int choice;
    cin>>choice;
    switch(choice)
    {
   	    case 1:flag=op.login();break;
        case 2:op.registor();break;
        case 3:exit(0);break;
        case 4:flag=op1.login();break; 
        default: cout<<"输入序号出错!";
    }
    if(flag==true) if(choice==1) return 1;else return 4; 
    else main_menu();
} 

char map[22][32];
typedef class 
{
	public: 
        int x,y; 
}Point;
Point  snake[600],food,Next;
class youxi
{	
	public:
		youxi(int grade,int length,int autotime,int head,int tail,char diraction);
		void gotoxy(int x,int y);
		void Update(char map[][32],int grade,int length,int autotime);
		void welcome();
		void creatfood();
		void youxijiemian();
		int rungame();
		void eatfood();
		void noteat();
	private:
		int head,tail,grade,length,autotime;
        char diraction;
}; 
youxi::youxi(int grade,int length,int autotime,int head,int tail,char diraction)
{
	this->grade=grade;
	this->length=length;
	this->autotime=autotime;
    this->head=head;
    this->tail=tail;
    this->diraction=diraction;
}
void youxi::gotoxy(int x,int y)//用光标解决画面闪烁的问题 
{
	HANDLE hConsoleOutput;
	COORD dwCursorPostion;
	dwCursorPostion.X=x;
	dwCursorPostion.Y=y;
	hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPostion); 
} 
inline void youxi::Update(char map[][32],int grade,int length,int autotime)//用内联函数降低内存的占用率 
{
	//system("cls");
	gotoxy(0,0);
	int c,y; 
	cout<<endl;
	for(c=0;c<22;c++)
	{
	    cout<<"   ";
	    for(y=0;y<32;y++) 
	    	cout<<map[c][y];
		if(c==0)  cout<<"	"<<"您现在的等级是:"<<grade;
		if(c==2)  cout<<"	"<<"蛇身长为:"<<length;
       	cout<<endl;   
	}
}                
inline void youxi::welcome()
{
    cout<<endl<<endl<<endl<<"			"<<"贪吃蛇游戏马上开始!";
	double start;
	int i;
	for(i=3;i>=0;i--)
	{
	    start=(double)clock()/CLOCKS_PER_SEC;//程序运行到现在的时间
		while((double)clock()/CLOCKS_PER_SEC-start<=1);
		if(i>0)
		{
			system("cls");
			cout<<endl<<endl<<endl<<"			"<<"进入倒计时"<<i<<endl;
		} 
		else  Update(map,grade,length,autotime);
	}
}  
inline void youxi::creatfood()
{
	srand(int(time (0)));
	do{
		food.x=rand()%30+1;
		food.y=rand()%20+1;
	}while(map[food.x][food.y]!=' ');
	map[food.x][food.y]='*';
} 
inline void youxi::youxijiemian()
{
	int c,y;
	for(c=1;c<=20;c++)
	for(y=1;y<=30;y++) 
		map[c][y]=' '; 
	for(c=0;c<=21;c++)
	{map[c][0]='*';map[c][31]='*';}
	for(c=0;c<=31;c++)
	{map[21][c]='*';map[0][c]='*';}
	map[1][1]=map[1][2]=' ';
	map[1][3]='*';
	head=2;tail=0;
	snake[head].x=1;snake[head].y=3;//蛇头下标;
	snake[tail].x=1;snake[tail].y=1;//蛇尾下标; 
	creatfood();
} 
inline  int youxi::rungame()
{
	bool over=true;
	double start=(double)clock()/CLOCKS_PER_SEC;//程序运行到现在所用时间;
	while((over=(double)clock()/CLOCKS_PER_SEC-start<=autotime/1000.0)&&!_kbhit());//不断循环直至超过自动更新时间或者有敲击键盘; 
	if(over==true)
	{
		getch(); 
		diraction=getch(); 
	} 
	switch(diraction)
	{
		case 72:Next.x=snake[head].x-1;Next.y=snake[head].y;break;//上 
		case 80:Next.x=snake[head].x+1;Next.y=snake[head].y;break;//下
		case 75:Next.x=snake[head].x;Next.y=snake[head].y-1;break;//左 
		case 77:Next.x=snake[head].x;Next.y=snake[head].y+1;break;//右
		default:cout<<"    错误按键,游戏结束!"<<endl;
		return 0; 
	} 
	if(Next.x==0||Next.x==21||Next.y==0||Next.y==31){ cout<<"    撞到边界,游戏结束!"<<endl;system("pause");return 0;}
	if(map[Next.x][Next.y]!=' '&&!(Next.x==food.x&&Next.y==food.y)) { cout<<"    吃到自己,游戏结束!"<<endl;system("pause");return 0;}
	if(length==600) { cout<<"    恭喜您!通关啦!"<<endl;system("pause");return 0;}
	return 1; 
} 
inline void youxi::eatfood()
{
	length++; 
	int egrade=length/10+1;
	if(egrade!=grade){grade=egrade;if(autotime>=100){autotime=550-grade;}} //每升一级减少自动时间,增加游戏难度;
	map[Next.x][Next.y]='*'; //蛇头位置变化
	head++;
	creatfood();
	snake[head].x=Next.x;snake[head].y=Next.y; 
	Update(map,grade,length,autotime); 
}
inline void youxi::noteat()
{
	map[snake[tail].x][snake[tail].y]=' ';
	tail=(tail+1)%600;
	map[Next.x][Next.y]='*'; 
	head=(head+1)%600;
	snake[head].x=Next.x;snake[head].y=Next.y; 
	Update(map,grade,length,autotime); 
} 
void playgame()
{
	int next;
	system("cls");
	youxi player1(1,3,500,2,0,77);
	player1.youxijiemian();
	player1.welcome();
	while(true)
	{
		if(player1.rungame())
		{
			if(Next.x==food.x&&Next.y==food.y) player1.eatfood();
			else player1.noteat();
	    }
	    else break;
	} 

} 
bool adminplaygame()
{
	int next;
	system("cls");
	youxi player1(1,3,500,2,0,77);
	player1.youxijiemian();
	player1.welcome();
	while(true)
	{
		if(player1.rungame())
		{
			if(Next.x==food.x&&Next.y==food.y) {player1.eatfood();} 
			else player1.noteat();
	    }
	    else break;
	} 
	system("cls");
	cout<<"\n\n\n				        1：重新开始游戏"<<endl;
	cout<<"\n\n\n				        2：下一个玩家"<<endl;
	cout<<"\n\n\n				        3：退出游戏"<<endl;
	cout<<"\n\n\n				        请选择你的意向：";
	fflush(stdin);
	cin>>next;
	if (next==1) adminplaygame();
	else if(next==2) return true;
	else return false; 
} 

int main()
{
	system("color 5e"); //背景颜色以及字体颜色
	switch(main_menu())
	{
		default:playgame();break;
		case 4:while(adminplaygame()){main_menu();};break;
	}
    return 0;
}
