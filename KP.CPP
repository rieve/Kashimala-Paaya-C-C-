#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>

void startpage();
void instruction();

// for mouse instruction
union REGS in, o;
int x, y, i,m, n, cl;
int *a, *b, *c;

// for mouse coordinate to click
void click(int *, int *, int *)
{
 in.x.ax=3;
 int86(0x33, &in, &o);
 cl=o.x.bx;
 m=o.x.cx;
 n=o.x.dx;
}

static int csc=0;//static variable for counting consecutive 5 and 4

//class for storing coordinates of token where players will move
class Position
{
 private:
  int x,y;

 public:
  void setcoord(int x,int y)
  {
   this->x=x;
   this->y=y;
  }

  void display(int b){ //token display
   if(b==1)
   {
    setcolor(15);
    circle(x,y,7);
    setfillstyle(SOLID_FILL,RED); //red token
    floodfill(x,y,15);
   }
   if(b==2)
   {
    setcolor(15);
    circle(x,y,7);
    setfillstyle(SOLID_FILL,YELLOW); //yellow token
    floodfill(x,y,15);
   }
   if(b==3)
   {
    setcolor(0);
    circle(x,y,7);
    setfillstyle(SOLID_FILL,BLACK);
    floodfill(x,y,0);
   }
  }
};

//class for player with required properties
class Player{
private:
 Position pos;//player has attribute of type class Position

public:
 int posindex;
 int status;

Player(){
 status=0;
}

void setposition(int pindex,Position p){
 posindex=pindex;
 pos=p;
}

void display(int b){
 pos.display(b);
}
};

//create board interface before player gets displayed
void showboard()
{
 for(int count_2=0; count_2<2; count_2++);
  {
   setcolor(11);
   rectangle(0,20,639,450);
   rectangle(0,20,420,450);
   setcolor(12);
   rectangle((0+count_2),(20+count_2),(420-count_2),(450-count_2));
   setcolor(13);
   rectangle((2+count_2),(22+count_2),(418-count_2),(448-count_2));
   setcolor(9);
   rectangle((4+count_2),(24+count_2),(416-count_2),(446-count_2));
   setcolor(14);
   rectangle((6+count_2),(26+count_2),(414-count_2),(444-count_2));
  }

  setcolor(8);
  line(110,29,110,441);
  line(310,29,310,441);
  // board section-lines //
  int h=54;
  for(int i=0; i<16; i++)
  {
   line(9,h,411,h);
   h+=24;
  }
  // safe zone //
  setfillstyle(9,4);
  bar(111,29,309,54);
  bar(111,126,309,151);
  bar(111,222,309,247);
  bar(111,318,309,343);
  bar(111,415,309,439);
  // info //
  setcolor(4);
  outtextxy(345,10,"START");
  outtextxy(30,455,"START");
  outtextxy(20,10,"Player 1");
  outtextxy(340,455,"Player 2");
  setcolor(15);
  setfillstyle(1,4);
  bar(421,424,638,449);
  outtextxy(465,435,"Press ESC to EXIT");
  setcolor(11);
  outtextxy(430,30,"Press ENTER to SHUFFLE");
}

//save all the circle coordinates where player can move to an array of object of class Position
void initializecoords(Position p[])
{
 int x=0,y=465,d=7*31,h=0,i,j;
 j=0;
 for(i=0; i<=16; i++)  //1st loop //for red token
 {
  p[j++].setcoord(x+d-6,x+y-d/10-18-h);
  h+=24;
 }
 h=0;
 for(i=0; i<17; i++) //2nd loop //for red token
 {
  p[j++].setcoord(y-d/4-50,x+d/20+32+h);
  h+=24;
 }
 h=0;
 for(i=0; i<17; i++) //3rd loop //for yellow token
 {
  p[j++].setcoord(x+d-5,x+d/20+32+h);
  h+=24;
 }
 h=0;
 for(i=0; i<17; i++)  //4th loop  //for yellow token
 {
  p[j++].setcoord(x+d/4-2,x+y-d/10-18-h);
  h+=24;
 }
 h=0;
}

//save circle coordinates for initial position of player inside their base (i.e; before player is unlocked)
void initializecoords2(Position pi[]){
int x=0,y=465,d=7*31,i,j,z=18,l=19;

//token position coordinates
for(i=0; i<17; i++)
{
 pi[i].setcoord(x+d/4+2,x+y-d/10-z);  //red token
 pi[17+i].setcoord(y-d/4-55,x+y/20+l);//yellow token
 z=z+24;
 l=l+24;
}
}

//initialize players to initial positions defined by above function and set status to 1 for players depending upon value of n(no. of players choosen in game)
void initializeplayer(Player red[],Player yellow[],Position pi[]){
//red coins positions
 red[0].setposition(-1,pi[0]);
 red[1].setposition(-1,pi[1]);
 red[2].setposition(-1,pi[2]);
 red[3].setposition(-1,pi[3]);
 red[4].setposition(-1,pi[4]);
 red[5].setposition(-1,pi[5]);
 red[6].setposition(-1,pi[6]);
 red[7].setposition(-1,pi[7]);
 red[8].setposition(-1,pi[8]);
 red[9].setposition(-1,pi[9]);
 red[10].setposition(-1,pi[10]);
 red[11].setposition(-1,pi[11]);
 red[12].setposition(-1,pi[12]);
 red[13].setposition(-1,pi[13]);
 red[14].setposition(-1,pi[14]);
 red[15].setposition(-1,pi[15]);
 red[16].setposition(-1,pi[16]);

//yellow coins positions
 yellow[0].setposition(-1,pi[17]);
 yellow[1].setposition(-1,pi[18]);
 yellow[2].setposition(-1,pi[19]);
 yellow[3].setposition(-1,pi[20]);
 yellow[4].setposition(-1,pi[21]);
 yellow[5].setposition(-1,pi[22]);
 yellow[6].setposition(-1,pi[23]);
 yellow[7].setposition(-1,pi[24]);
 yellow[8].setposition(-1,pi[25]);
 yellow[9].setposition(-1,pi[26]);
 yellow[10].setposition(-1,pi[27]);
 yellow[11].setposition(-1,pi[28]);
 yellow[12].setposition(-1,pi[29]);
 yellow[13].setposition(-1,pi[30]);
 yellow[14].setposition(-1,pi[31]);
 yellow[15].setposition(-1,pi[32]);
 yellow[16].setposition(-1,pi[33]);

// token status
for(int i=0; i<=16; i++)
{
 red[i].status=1; //red token
 yellow[i].status=1; //yellow token
}
}

//display all the players which are active
void displayplayer(Player red[],Player yellow[]){
int i;
red[0].display(1);
yellow[0].display(2);
for(i=1; i<17; i++)
{
 red[i].display(1); //red token
 yellow[i].display(2); //yellow token
}
}

// bar shuffle display
void one() //bar display for 1
{
 setcolor(5);
 settextstyle(3,0,1);
 outtextxy(510,200,"kasi");
 setfillstyle(1,15);
 bar(455,260,605,285);
 setfillstyle(1,4);
 bar(455,295,605,320);
 bar(455,330,605,355);
 bar(455,365,605,390);
 settextstyle(0,0,0);
}
void two() //bar display for 2
{
 setcolor(5);
 settextstyle(3,0,1);
 outtextxy(510,200,"dwadi");
 setfillstyle(1,15);
 bar(455,260,605,285);
 bar(455,295,605,320);
 setfillstyle(1,4);
 bar(455,330,605,355);
 bar(455,365,605,390);
 settextstyle(0,0,0);
}
void three() //bar display for 3
{
 setcolor(5);
 settextstyle(3,0,1);
 outtextxy(510,200,"sudi");
 setfillstyle(1,15);
 bar(455,260,605,285);
 bar(455,295,605,320);
 bar(455,330,605,355);
 setfillstyle(1,4);
 bar(455,365,605,390);
 settextstyle(0,0,0);
}
void four()  //bar display for 4
{
 setcolor(5);
 settextstyle(3,0,1);
 outtextxy(510,200,"chya");
 setfillstyle(1,15);
 bar(455,260,605,285);
 bar(455,295,605,320);
 bar(455,330,605,355);
 bar(455,365,605,390);
 settextstyle(0,0,0);
}
void five()  //bar display for 5
{
 setcolor(5);
 setcolor(5);
 settextstyle(3,0,1);
 outtextxy(510,200,"ngha");
 setfillstyle(1,4);
 bar(455,260,605,285);
 bar(455,295,605,320);
 bar(455,330,605,355);
 bar(455,365,605,390);
 settextstyle(0,0,0);
}
//main logic of rolling a dice for each player turn
void rolldice(Player red[], Player yellow[], Position p[], Position pi[], int turn){
setcolor(8);
int x=0,y=465,i,j,k,s,q,r;
char *name;
csc=0;//consecutive six counter

if(turn==1){
name="Player 1";
}
if(turn==2){
name="Player 2";
}

repeat://label for repeating turn if player gets 5
setcolor(11);
//outtextxy(430,30,"Press ENTER to SHUFFLE");
outtextxy(y+10,x+60,"Turn: ");
outtextxy(y+60,x+60,name);
char ch;
while(1){
ch=getch();
if(ch==27 || ch==13)
break;
}
if(turn==1)
{
 if(ch==27)  // executes if player 1 presses esc
 {
  setcolor(15);
  setfillstyle(1,8);
  bar(60,150,360,300);
  settextstyle(1,0,2);
  outtextxy(110,170,"******* WINNER *******");
  settextstyle(0,0,3);
  outtextxy(120,230,"PLAYER 2");
  delay(1000);
  exit(0);
 }
}
if(turn==2)
{
 if(ch==27)   //execute if player 2 presses esc
 {
  setfillstyle(1,8);
  bar(60,150,360,300);
  settextstyle(1,0,2);
  outtextxy(100,170,"******* WINNER *******");
  settextstyle(0,0,3);
  outtextxy(120,230,"PLAYER 1");
  delay(1000);
  exit(0);
 }
}
if(ch==13){//execute if player presses Enter key
char roll[1];
time_t t;
srand((unsigned) time(&t));//for generating random number based on time
int n=rand()%5+1;
itoa(n,roll,10);

outtextxy(y+20,x+90,"You shuffled:");
settextstyle(0,0,5);
outtextxy(y+50,x+140,roll);
if(n==1)
{
 one();
 delay(500);
}
if(n==2)
{
 two();
 delay(500);
}
if(n==3)
{
 three();
 delay(500);
}
if(n==4)
{
 four();
 delay(500);
}
if(n==5)
{
 five();
 delay(500);
}
settextstyle(0,0,0);

if(n==5 && csc==2 && n==4 && csc==2){//reset player if it has encountered 2 fives and again has got 5 while rolling(random number generated)
if(turn==1)
red[0].setposition(-1,pi[0]);
if(turn==2)
yellow[0].setposition(-1,pi[17]);
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow);
}else{
if((turn==1 && red[0].posindex==-1)||(turn==2 && yellow[0].posindex==-1)/*||(turn==3 && green[0].posindex==-1)||(turn==4 && blue[0].posindex==-1)*/){//for initial 1 to unlock player
if(turn==1 && n==1){
red[0].posindex=0;
red[0].setposition(0,p[0]);
}
if(turn==2 && n==1){
yellow[0].posindex=34;
yellow[0].setposition(34,p[34]);
}
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow);
}
else{
if((turn==1&&red[0].posindex+n<=57)||(turn==2&&yellow[0].posindex+n<=63)){ //for movement
for(i=0; i<n; i++){
setcolor(11);
outtextxy(y+10,x+60,"Turn: ");
outtextxy(y+60,x+60,name);
outtextxy(y+20,x+90,"You shuffled:");
settextstyle(0,0,5);
outtextxy(y+50,x+140,roll);
settextstyle(0,0,0);
if(n==1)
{
 one();
}
if(n==2)
{
 two();
}
if(n==3)
{
 three();
}
if(n==4)
{
 four();
}
if(n==5)
{
 five();
}

if(turn==1){
int index=red[0].posindex;
red[0].setposition(index+1,p[index+1]);
if(index==33){
red[0].posindex=0;
red[0].setposition(0,p[0]);
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow);
}
}
if(turn==2){
int index=yellow[0].posindex;
yellow[0].setposition(index+1,p[index+1]);
if(index==67){
yellow[0].posindex=34;
yellow[0].setposition(34,p[34]);
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow);
}
}
delay(500);
cleardevice();
showboard();
displayplayer(red,yellow);
}
}
int ri=red[0].posindex,yi=yellow[0].posindex;//cut player if two player has same position
if(turn==1){
if(ri!=0 && ri!=4 && ri!=8 && ri!=12 && ri!=16 && yi!=34 && yi!=38 && yi!=42 && yi!=46 && yi!=50){
if(ri==ri && yi==(50-ri)){
yellow[0].posindex==17;
yellow[0].setposition(-1,p[17]);
yellow[0].display(3);
yellow[0].status==-1;
return;
}
delay(500);
}
}
if(turn==2){
if(ri!=0 && ri!=4 && ri!=8 && ri!=12 && ri!=16 && yi!=34 && yi!=38 && yi!=42 && yi!=46 && yi!=50){
if(ri==ri && yi==(50-ri)){
red[0].posindex==-1;
red[0].setposition(-1,p[-1]);
red[0].display(3);
red[0].status==-1;
return;
}
}
delay(500);
}
}

if(n==5 || n==4){
csc++;
goto repeat;
}
}
}
}

// starting page of the game
void startpage()
{
 int x=0,y=10;
 in.x.ax=1;
 int86(0x33, &in, &o);
 settextstyle(0,0,0);
 setcolor(3);
 // page border
 for(int i=0; i<=70; i++)
 {
  outtextxy(x,10,"*");
  outtextxy(x,450,"*");
  x=x+10;
  delay(10);
 }
 for(i=0; i<=43; i++)
 {
  outtextxy(0,y,"*");
  outtextxy(629,y,"*");
  y=y+10;
  delay(10);
 }
 setcolor(15);
 setfillstyle(9,4);
 bar(190,35,488,123);
 //frame border
 for(i=0; i<300; i+=10)
 {
  setcolor(i+1);
  outtextxy(190+i,35,"\b");
  outtextxy(190+i,115,"\b");
 }
 for(i=0; i<90; i+=10)
 {
  setcolor(i+1);
  outtextxy(190,35+i,"\b");
  outtextxy(480,35+i,"\b");
 }
 setcolor(15);
 outtextxy(305,55,"WELCOME");
 outtextxy(290,75,"*** TO ***");
 outtextxy(275,95,"KASIMALA PAAYA");
 setcolor(0);
 settextstyle(8,0,2);
 setfillstyle(1,3);
 bar(x/2-80,y/2-50,x/2+40, y/2-10);
 outtextxy(x/2-48,y/2-46,"PLAY");

 bar(x/2-110,y/2+5,x/2+70, y/2+45);
 outtextxy(x/2-90,y/2+8,"INSTRUCTION");

 bar(x/2-80,y/2+60,x/2+40, y/2+100);
 outtextxy(x/2-48,y/2+65,"EXIT");

 setcolor(12);
 settextstyle(0,0,0);
 outtextxy(20,430,"Developed By: NAYAM");

 while(!kbhit()) // for mouse click action coordinates
 {
  click(&m, &n, &cl);
  if(m>(x/2-80) && m<(x/2+40) && n>(y/2-50) && n<(y/2-10) && cl==1)
  {
   cleardevice();
   delay(100);
   showboard();
   Position p[200];
   Position pi[200];
   initializecoords(p);
   initializecoords2(pi);
   Player red[50];
   Player yellow[50];
   initializeplayer(red,yellow,pi);
   displayplayer(red,yellow);
  }
  else if(m>(x/2-110) && m<(x/2+70) && n>(y/2+5) && n<(y/2+45) && cl==1)
  {
   cleardevice();
   delay(100);
   instruction();
  }
  else if(m>(x/2-80) && m<(x/2+40) && n>(y/2+60) && n<(y/2+100) && cl==1)
  {
   cleardevice();
   exit(0);
  }
 }
}

// instructions page
void instruction()
{
 char sh;
 setcolor(3);
 outtextxy(0,435,"Press ESC to EXIT");
 settextstyle(8,0,2);
 outtextxy(30,10,"******************** INSTRUCTIONS ********************");
 printf("\n\n\n");
 printf("\n1.The court shall be selected through players choice.");
 printf("\n2.There are total 17 coulumns with total 5 safe zones at the interval of 3 boxes.");
 printf("\n3.The token moves from right to left of players side.");
 printf("\n4.The bars are to be dropped horizontally.\n If after dropping the bars,there comes:\n\ta.One white and 3 black: 1 or Kasi\n\t Only after getting this,a token is validated to move.\n\tb.Two white and two black: 2 or doka\n\tc.Three white and one black: 3 or sudi\n\td.All white: 4 or peee\n\te.All black:5 or ngi");
 printf("\nNote:When a player gets 4 or 5,they get a chance to drop the bars again.");
 printf("\n5.Once a player’s token is at safe zone,next player cant place the token there.");
 printf("\n6.Once the token reaches from A to A’,the token now moves towards B in clockwise direction.");
 printf("\n7.Once all tokens of a player is captured ,game is over.Also by quiting,the game also can be over.");
 while(1)
 {
  sh=getch();
  if(sh==27)
  {
   cleardevice();
   startpage();
  }
 }
}

//main function
void main(){
int gd=DETECT,gm,i,j,k,n;
initgraph(&gd,&gm,"..\\BGI");

cleardevice();
startpage();
Position p[200];
Position pi[200];
initializecoords(p);
initializecoords2(pi);

Player red[50];
Player yellow[50];
initializeplayer(red,yellow,pi);

i=1;
while(1){
if((i==1 && red[0].status==1)||(i==2 && yellow[0].status==1)){//execute rolldice for only active player
rolldice(red,yellow,p,pi,i);
}
i++;
if(i==5)
i=1;
}
closegraph();
}