#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<graphics.h>


char b[50][10];
int getout=0;
int f=0,r=0;

class attribute{
	float fval;int ftype;
	public:
	float retval(){
		return fval;
	}
	int rtype(){
		return ftype;
	}
	void put(float val,int type){
		fval=val;ftype=type;
	}
	void show(){
		cout<<endl<<fval<<' '<<ftype;
	}
}ele[100],ref[50];

void putnumber(int &itr,int loc,char eq[]){
	float ref=0;int stit=0;float tv=1;
	while((eq[itr]>='0'&& eq[itr]<='9') || eq[itr]=='.'){
		if(eq[itr]=='.')stit=1;
		else{
			if(stit==0){
				ref*=10;
				float pt=eq[itr]-48;
				ref+=pt;
			}
			else if(stit==1){
				tv/=10;
				float pt=eq[itr]-48;
				ref+=pt*tv;
			}
		}
		itr++;
	}
	ele[loc].put(ref,0);
	itr--;
}

void putidentity(int &itr,int loc,char eq[]){
	float ref;char identity[5];
	int i=0,j=itr;
	while(eq[j=itr]!='('){
		identity[i]=eq[j];
		i++;itr++;
	}identity[i]='\0';
	itr--;
	if(strcmpi(identity,"sin")==0)ele[loc].put(0,6);
	else if(strcmpi(identity,"cos")==0)ele[loc].put(1,6);
	else if(strcmpi(identity,"tan")==0)ele[loc].put(2,6);
	else if(strcmpi(identity,"asin")==0)ele[loc].put(3,6);
	else if(strcmpi(identity,"acos")==0)ele[loc].put(4,6);
	else if(strcmpi(identity,"atan")==0)ele[loc].put(5,6);
	else if(strcmpi(identity,"log")==0)ele[loc].put(6,6);
	else if(strcmpi(identity,"ln")==0)ele[loc].put(7,6);
	else if(strcmpi(identity,"abs")==0)ele[loc].put(8,6);
}

float x;
int plot=1;

void putfunc(char eq[]){
	int i=0,pos=0;
	while(eq[i]!='\0'){
		if(eq[i]=='*')ele[pos].put(3,1);
		else if(eq[i]=='/')ele[pos].put(4,1);
		else if(eq[i]=='-')ele[pos].put(2,1);
		else if(eq[i]=='+')ele[pos].put(1,1);
		else if(eq[i]=='^')ele[pos].put(5,1);
		else if(eq[i]=='x')ele[pos].put(x,2);
		else if(eq[i]=='(')ele[pos].put(pos,3);
		else if(eq[i]==')')ele[pos].put(pos,4);
		else if(eq[i]>='0' &&eq[i]<='9')putnumber(i,pos,eq);
		else putidentity(i,pos,eq);
		pos++;i++;
	}
	ele[pos].put(0,5);
}




int getlength(attribute ref1[]){
	int i=0;
	while(ref1[i].rtype()!=5){
		i++;
	}
	return i;
}

void shiftar(int it,attribute ref2[]){
	for(;it<=getlength(ref2)-2;it++)ref2[it].put(ref2[it+2].retval(),ref2[it+2].rtype());
}

int brexist(){
	for(int i=0;i<getlength(ele);i++){
		if(ele[i].rtype()==3)return 1;
	}
	return 0;
}

void calcpart(attribute sam[]);

void cpyatt(int start,int stop){
	for(int i=0;i+start+1<stop;i++)
		ref[i].put(ele[i+start+1].retval(),ele[i+start+1].rtype());
	ref[i].put(0,5);
}

void putatt(int start,int stop){
	ele[start].put(ref[0].retval(),ref[0].rtype());
	for(int i=start+1,j=stop+1;j<=getlength(ele);j++,i++){
		ele[i].put(ele[j].retval(),ele[j].rtype());
	}
}

void srchbrac(){
	int j=0,fbreak=0;
	for(int i=0;i<getlength(ele);i++){
		if(fbreak==0){
			if(ele[i].rtype()==4){
				for(j=i;j>=0;j--){
					if(ele[j].rtype()==3){
						cpyatt(j,i);
						calcpart(ref);
						putatt(j,i);
						fbreak=1;
						break;
					}
				}
			}
		}
		else break;
	}

}

void calcfun(){
	while(brexist()==1){
		srchbrac();
	}
	calcpart(ele);
	if(plot==0)ele[0].put(0,0);
}

int chkpow(attribute ref3[]){
	for(int i=0;i<getlength(ref3);i++){
		if(ref3[i].retval()==5 &&ref3[i].rtype()==1)return i;
	}
	return -1;
}

int chkprim(attribute ref3[]){
	for(int i=0;i<getlength(ref3);i++){
		if((ref3[i].retval()==3 || ref3[i].retval()==4) &&ref3[i].rtype()==1)return i;
	}
	return -1;
}

int checkidentity(attribute ref4[]){
	for(int i=0;i<getlength(ref4);i++){
		if(ref4[i].rtype()==6)return i;
	}
	return -1;
}

int chksec(attribute ref4[]){
	for(int i=0;i<getlength(ref4);i++){
		if((ref4[i].retval()==1 || ref4[i].retval()==2) &&ref4[i].rtype()==1)return i;
	}
	return -1;
}
float put;

int checkdomain(float type,float val){
	if(type==3||type==4){
		if(val>=-1&& val<=1)return 1;
		return 0;
	}
	else if(type==6||type==7){
		if(val>0)return 1;
		else return 0;
	}
	else return 1;
}

float validentity(float type,float val){
	if(checkdomain(type,val)==1){
		if(type==0)put=sin(val);
		else if(type==1)put=cos(val);
		else if(type==2)put=tan(val);
		else if(type==3)put=asin(val);
		else if(type==4)put=acos(val);
		else if(type==5)put=atan(val);
		else if(type==6)put=log10(val);
		else if(type==7)put=log(val);
		else if(type==8)put=fabs(val);
	}
	else {
		put=0;plot=0;
	}
	return put;
}

void calcpart(attribute sam[]){
	int i=0;
	if(sam[0].rtype()==1 &&sam[0].retval()==2){
		sam[1].put(-sam[1].retval(),0);
		for(int k=0;k<getlength(sam);k++){
			sam[k].put(sam[k+1].retval(),sam[k+1].rtype());
		}
	}
	while(getlength(sam)!=1){
		float ref=0;
		if(checkidentity(sam)!=-1){
			i=checkidentity(sam);
			ref=validentity(sam[i].retval(),sam[i+1].retval());
			sam[i].put(ref,0);
			for(int j=i+1;j<=getlength(sam);j++)sam[j].put(sam[j+1].retval(),sam[j+1].rtype());
		}
		else if(chkpow(sam)!=-1){
			i=chkpow(sam);
			double a=sam[i-1].retval();double b=sam[i+1].retval();
			if((a<0 && b==ceil(b))||a>0)ref=pow(a,b);
			else {ref=0;plot=0;}
			sam[i-1].put(ref,0);
			shiftar(i,sam);
		}
		else{
			i=chkprim(sam);
			if(i!=-1){
				if(sam[i].retval()==3){
					ref=sam[i-1].retval()*sam[i+1].retval();
					sam[i-1].put(ref,0);
				}
				else if(sam[i].retval()==4){
					ref=sam[i-1].retval()/sam[i+1].retval();
					sam[i-1].put(ref,0);
				}
				shiftar(i,sam);
			}
			else{
				i=chksec(sam);
				if(sam[i].retval()==1){
					ref=sam[i-1].retval()+sam[i+1].retval();
					sam[i-1].put(ref,0);
				}
				else if(sam[i].retval()==2){
					ref=sam[i-1].retval()-sam[i+1].retval();
					sam[i-1].put(ref,0);
				}
				shiftar(i,sam);
			}
		}
	}
}

char* inttochar(float x){
	char text[100];
	int i=0;
	long int y,f;float z=fabs(x);
	f=(z-floor(z))*1000;
	y=floor(z);
	text[i++]='.';
	while(y!=0){
		text[i]=y%10+48;
		y=y/10;
		i++;
	}
	if(x>0)text[i++]='+';
	else if(x<0)text[i++]='-';
	text[i]='\0';
	strrev(text);
	i=0;
	char text2[10];
	while(f!=0){
		text2[i]=f%10+48;
		f=f/10;
		i++;
	}
	text2[i]='\0';
	strrev(text2);
	strcat(text,text2);
	return text;
}

float map(float arg,float min_in,float max_in,float min_out,float max_out){
	if(arg<min_in)return min_out;
	else if(arg>max_in)return max_out;
	else if(arg>=min_in && arg<=max_in){
			float m=(max_out-min_out)/(max_in-min_in);
			float c=min_out-m*min_in;
			arg=m*arg+c;
	}
	return arg;
}

void background(float minx,float miny,float range,int drwx,int drwy,int drx){
	float zerx=map(0,minx,minx+range,drwx,drx);
	float zery=map(0,miny,miny+range,0,drwy);
	int j=-10,k=-10;
	setcolor(7);
	for(int i=-10;i<=10;i++){
		setcolor(LIGHTGRAY);
		float px=zerx+((drx-drwx)/20)*i;
		float py=zery+(drwy/20)*i;
		px=int(px);py=int(py);
		if(px>drx)j--;
		if(px<drwx)j++;
		if(py>drwy)k--;
		if(py<0)k++;
	}
	for(i=-10;i<=10;i++){
		setcolor(LIGHTGRAY);
		float px=zerx+((drx-drwx)/20)*j;
		float py=(zery+(drwy/20)*k);
		px=int(px);py=int(drwy-py);
		line(drwx,py,drx,py);
		line(px,0,px,drwy);
		setcolor(LIGHTBLUE);
		settextstyle(2,VERT_DIR,0.1);
		outtextxy(px-5,drwy-zery-5,inttochar(map(i,-10,10,minx,minx+range)));
		settextstyle(2,HORIZ_DIR,0);
		outtextxy(zerx+5,py-5,inttochar(map(i,-10,10,miny,miny+range)));
		j++;k++;
	}
	setcolor(8);
	line(drwx,drwy-zery,drx,drwy-zery);
	line(zerx,0,zerx,drwy);
}

void drawscreen(int select);

float zr=1;

void plotfunc(float minx,float miny,float range);

int plotloop=0;

void control(){
	char x;static float minx=-10,miny=-10,range=20;
	drawscreen(2);plotfunc(minx,miny,range);
	while(!kbhit());
	x = getch();
	if (x==27) plotloop=1;
	else if(x=='+'){range=range/2;minx=minx/2;miny/=2;zr/=2;}
	else if(x=='-'){range=range*2;minx=minx*2;miny*=2;zr*=2;}
	else if(x==0 || x==-32){
		x=getch();
		if(x==72)miny-=range/20;//down
		else if(x==80)miny+=range/20;//up
		else if(x==75)minx+=range/20;//right
		else if(x==77)minx-=range/20;//left
	}
	cleardevice();
}

void logo(int x,int y,int scale){
	int tr1[]={x,y,x-25*scale,y,x,y-25*scale,x,y};
	int tr2[]={x,y,x-25*scale,y,x,y+25*scale,x,y};
	int tr3[]={x,y,x+25*scale,y,x,y+25*scale,x,y};
	setfillstyle(SOLID_FILL,RED);
	fillpoly(4, tr1);
	setfillstyle(SOLID_FILL,LIGHTGREEN);
	fillpoly(4, tr2);
	setfillstyle(SOLID_FILL,GREEN);
	fillpoly(4, tr3);
	setcolor(LIGHTBLUE);
	settextstyle(3,HORIZ_DIR,2+scale);
	outtextxy(x+25*scale,y,"RAPHY");
}

void plotfunc(float minx,float miny,float range){
	background(minx,miny,range,270,getmaxy()-20,getmaxx()-20);
	for(int j=f;j<r;j++){
		for(float i=0;i<=range;i+=0.01*zr){
			putfunc(b[j]);
			x=map(i,0,range,minx,minx+range);
			calcfun();
			if(plot==1){
				float px=map(i,0,range,minx,minx+range);
				px=map(px,minx,minx+range,270,getmaxx()-20);
				float py=map(ele[0].retval(),miny,miny+range,getmaxy()-20,0);
				px=int(px);py=int(py);
				putpixel(px,py,j+3);
			}
		else plot=1;
		}
	}
}

void deletebutton(int x,int y){
	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL,WHITE);
	rectangle(x-5,y-5,x+13,y+12);
	floodfill(x+2,y+3,DARKGRAY);
	line(x,y,x,y+10);
	line(x,y+10,x+8,y+10);
	line(x+8,y+10,x+8,y);
	for(int i=0;i<3;i++)line(2+x+2*i,y,2+x+2*i,y+8);
	arc(x+4,y+13,60,120,15);
}

void drawfig(int x,int y,int color,char text[]){
	setfillstyle(SOLID_FILL, color);
	int points[]={x,y,x+250,y,x+250,y+20,x,y+20};
	setcolor(color);
	fillpoly(4, points);
	char a[5];
	settextstyle(8,HORIZ_DIR,1);
	a[0]=159;a[1]='(';a[2]='x';a[3]=')';a[4]='=';
	setcolor(DARKGRAY);outtextxy(x+5,y-6,a);
	settextstyle(2,HORIZ_DIR,5);
	setcolor(DARKGRAY);
	outtextxy(x+60,y+1,text);
	deletebutton(x+220,y+6);
}	

void plotbutton(int x,int y,int select){
	setcolor(LIGHTGRAY);
	if(select!=2)setfillstyle(SOLID_FILL, DARKGRAY);
	else setfillstyle(SOLID_FILL,GREEN);
	rectangle(x-40,y-30,x+40,y+30);
	floodfill(x,y,LIGHTGRAY);
	setcolor(LIGHTGREEN);
	settextstyle(8,HORIZ_DIR,2);
	outtextxy(x-20,y-10,"PLOT");
}

void enterbutton(int x,int y,int select){
	setcolor(LIGHTGRAY);
	if(select!=1)setfillstyle(SOLID_FILL, CYAN);
	else setfillstyle(SOLID_FILL, GREEN);
	rectangle(x-25,y-12,x+25,y+12);
	floodfill(x,y,LIGHTGRAY);
	setcolor(WHITE);
	settextstyle(2,HORIZ_DIR,6);
	outtextxy(x-25,y-5,"ENTER");
}

void exitbutton(int x,int y,int select){
	setcolor(LIGHTGRAY);
	if(select!=3)setfillstyle(SOLID_FILL, DARKGRAY);
	else setfillstyle(SOLID_FILL,GREEN);
	rectangle(x-40,y-30,x+40,y+30);
	floodfill(x,y,LIGHTGRAY);
	setcolor(LIGHTGREEN);
	settextstyle(8,HORIZ_DIR,2);
	outtextxy(x-20,y-10,"EXIT");
}

void drawscreen(int select){
	logo(100,30,1);
	settextstyle(8, HORIZ_DIR, 1);
	setcolor(DARKGRAY);
	outtextxy(10,50,"Enter function:");
	setcolor(LIGHTGRAY);
	rectangle(10,80,250,100);
	enterbutton(220,120,select);
	plotbutton(80,400,select);
	exitbutton(220,400,select);
	for(int i=f;i<r;i++)drawfig(10,(i+3)*40+20,i+3,b[i]);

}

void getdata(char data[],int c,int d,int mode){
	char a;
	cleardevice();
	setcolor(GREEN);
	settextstyle(2,HORIZ_DIR,6);
	int i=1;
	data[0]='\0';
	cleardevice();
	drawscreen(1);
	while(!kbhit());
	a=getch();
	if(a!=13){
		data[0]=a;
		setcolor(GREEN);
		settextstyle(2,HORIZ_DIR,6);
		outtextxy(c,d,data);
	}
	while(a!=13){
		drawscreen(1);
		while(!kbhit());
		cleardevice();
		a = getch();
		if(int(a)!=8&& a!=13&&a!=33){data[i]=a;i++;}
		else if(a==8 &&i>0)i--;
		data[i]='\0';
		setcolor(GREEN);
		settextstyle(2,HORIZ_DIR,6);
		outtextxy(c,d,data);
	}
	cleardevice();
	drawscreen(0);
}

void displaymode(int op){
	if(op==0){
		if(r<6){
			getdata(b[r],13,77,2);
			r++;
		}
	}
	else if(op==1){
		cleardevice();
		drawscreen(2);
		plotloop=0;
		while(plotloop==0)control();
	}
	else if(op==2){
		cleardevice();
		drawscreen(3);
		getout=1;
	}
	else{
		int del=op-3;
		for(int i=del;i<r-1;i++)strcpy(b[i],b[i+1]);
		r--;cleardevice();
		drawscreen(0);
	}
}

void drawrect(int op){
	cleardevice();
	drawscreen(0);
	setcolor(5);
	if(op==0)rectangle(194,107,246,133);
	else if(op==1)rectangle(40,370,120,430);
	else if(op==2)rectangle(180,370,260,430);
	else rectangle(224,(op)*40+20,244,(op)*40+39);
}

int op=0;

void navigate(){
	char x;int tot=r+3;
	drawscreen(0);
	drawrect(op);
	while(!kbhit());
	cleardevice();
	x = getch();
	if(x==13)displaymode(op);
	else if(x==0 || x==-32){
		x=getch();
		if(x==80){//down
			op++;op%=tot;
		}
		else if(x==72){//up
			if(op==0)op=tot-1;
			else op--;
		}
	}
}


void main(){
    int gdriver = DETECT, gmode;
    clrscr();
    initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
    setbkcolor(WHITE);
    logo(getmaxx()/2,getmaxy()/2,4);
    getch();
    while(getout!=1)navigate();
    closegraph();
}

