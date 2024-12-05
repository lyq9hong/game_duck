#include<graphics.h>
#include<math.h>
#define Width 1200
#define Height 700
#define FPS 100
float randminmax(int min,int max);
int randfu();
//  玩家
struct player{
  float R=15,x,y,vx,vy,ax,ay,Vmax=3,F=0.06,f=0.03;
  //  画下来
  void draw(){
    setcolor(WHITE);
    setfillcolor(GREENYELLOW);
    fillcircle(x,y,R);
  }
  //  初始化
  void begin(){
    x=Width/2;
    y=Height/2;
    vx=0;
    vy=0;
  }
  //  变
  void deta(){
    //  遇墙停止
    if(x<R){
      vx=0;
      x=R;
    }
    else if(x>Width-R){
      vx=0;
      x=Width-R;
    }
    if(y<R){
      vy=0;
      y=R;
    }
    else if(y>Height-R){
      vy=0;
      y=Height-R;
    }
    //  按键控制加速度
    if((keystate(key_W)!=0&&keystate(key_S)!=0)||(keystate(key_W)==0&&keystate(key_S)==0)){
      if((vy+f)*(vy-f)<0){
        ay=-vy;
      }
      else if(vy>0&&vy-f>0){
        ay=-f;
      }
      else if(vy<0&&vy+f<0){
        ay=f;
      }
    }
    else if(keystate(key_W)){
      ay=-F;
    }
    else if(keystate(key_S)){
      ay=F;
    }
    if((keystate(key_A)!=0&&keystate(key_D)!=0)||(keystate(key_A)==0&&keystate(key_D)==0)){
      if((vx+f)*(vx-f)<0){
        ax=-vx;
      }
      else if(vx>0&&vx-f>0){
        ax=-f;
      }
      else if(vx<0&&vx+f<0){
        ax=f;
      }
    }
    else if(keystate(key_A)){
      ax=-F;
    }
    else if(keystate(key_D)){
      ax=F;
    }
    //  dx  dy
    x+=vx;
    y+=vy;
    //  dv
    vx+=ax;
    vy+=ay;
    //  控制最大速度
    if(vx>Vmax)
    vx=Vmax;
    if(vx<-Vmax)
    vx=-Vmax;
    if(vy>Vmax)
    vy=Vmax;
    if(vy<-Vmax)
    vy=-Vmax;
  }
};
player p1;
//  硫磺火
struct Sfire{
  float R=10,x,y,vx,vy,distance,Vmax=1.5;
  //  初始化
  void begin(){
    x=(-2)*R;
    y=(-2)*R;
    vx=0;
    vy=0;
  }
  //  发射
  void chu(){
    if(randminmax(0,Width+Height)<Width){
      x=randminmax(0,Width);
      y=Height/2+randfu()*(Height/2+R);
      vx=0;
      if(y>0){
        vy=-Vmax;
      }
      else{
        vy=Vmax;
      }
    }
    else{
      y=randminmax(0,Height);
      x=Width/2+randfu()*(Width/2+R);
      vy=0;
      if(x>0){
        vx=-Vmax;
      }
      else{
        vx=Vmax;
      }
    }
  }
  //  位移
  void deta(){
    x+=vx;
    y+=vy;
    distance=sqrt((x-p1.x)*(x-p1.x)+(y-p1.y)*(y-p1.y));
  }
  //  画下来
  void draw(){
    setcolor(PINK);
    setfillcolor(RED);
    fillcirclef(x,y,R);
  }
};
Sfire SulfurFire[64];
//  红月
struct Rmoon{
  float R=50,x,y,vx,vy,v=1.25,distance;
  //  初始化
  void begin(){
    if(randfu()==1){
      x=Width;
      if(randfu()==1){
        y=Height;
      }
      else{
        y=0;
      }
    }
    else{
      x=0;
      if(randfu()==1){
        y=Height;
      }
      else{
        y=0;
      }
    }
  }
  //  变
  void deta(){
    distance=sqrt((x-p1.x)*(x-p1.x)+(y-p1.y)*(y-p1.y));
    vx=(p1.x-x)*v/distance;
    vy=(p1.y-y)*v/distance;
    x+=vx;
    y+=vy;
  }
  //  画下来
  void draw(){
    setcolor(PINK);
    setfillcolor(RED);
    fillcircle(x,y,R);
  }
};
Rmoon Redmoon;
//  异端
struct Heterodox{
  float R=20,x,y,vx,vy,ax,ay,distance,F=0.06;
  //  初始化
  void begin(){
    if(randfu()==1){
      x=Width;
      if(randfu()==1){
        y=Height;
      }
      else{
        y=0;
      }
    }
    else{
      x=0;
      if(randfu()==1){
        y=Height;
      }
      else{
        y=0;
      }
    }
  }
  //  变
  void deta(){
    //  遇墙停止
    if(x<R){
      vx=0;
      x=R;
    }
    else if(x>Width-R){
      vx=0;
      x=Width-R;
    }
    if(y<R){
      vy=0;
      y=R;
    }
    else if(y>Height-R){
      vy=0;
      y=Height-R;
    }
    //  
    distance=sqrt((x-p1.x)*(x-p1.x)+(y-p1.y)*(y-p1.y));
    ax=(p1.x-x)*F/distance;
    ay=(p1.y-y)*F/distance;
    vx+=ax;
    vy+=ay;
    x+=vx;
    y+=vy;
  }
  //  画下来
  void draw(){
    setcolor(PINK);
    setfillcolor(RED);
    fillcircle(x,y,R);
    setfillcolor(BLACK);
    fillcircle(x,y,R/2);
  }
};
Heterodox Heathen;
//  < ! ! !  主函数  ! ! ! >
int main(){
  int time,i,live;
  char textbegin[]="按esc键退出，按其他键开始";
  close_console();
  setinitmode(0x1,0,0);
  initgraph(Width,Height);
  setcolor(WHITE);
  ege_xyprintf(100,100,"%s",textbegin);
  Sleep(100);
while(1){
  flushkey();
  getch();
  if(keystate(key_esc))
  break;
  time=0;
  p1.begin();
  Redmoon.begin();
  Heathen.begin();
  for(i=0;i<64;i++){
    SulfurFire[i].begin();
  }
  live=1;
  while(keystate(key_esc)==0){
    p1.deta();
    p1.draw();
    Redmoon.deta();
    Redmoon.draw();
    Heathen.deta();
    Heathen.draw();
    if(time%41==0)
    SulfurFire[time%64].chu();
    for(i=0;i<64;i++){
      SulfurFire[i].deta();
      SulfurFire[i].draw();
    }
    time++;
    delay_fps(FPS);
    cleardevice();
    if(Redmoon.distance<Redmoon.R+p1.R)
    break;
    if(Heathen.distance<Heathen.R+p1.R)
    break;
    for(i=0;i<64;i++){
      if(SulfurFire[i].distance<SulfurFire[i].R+p1.R){
        live=0;
        break;
      }
    }
    if(live==0)
    break;
  }
  setcolor(WHITE);
  ege_xyprintf(100,100,"%s",textbegin);
  ege_xyprintf(100,50,"存活时间 : 0%.2f s",((float)time)/100);
  Sleep(1000);
}
  closegraph();
  return 0;
}
//  随机值
float randminmax(int min,int max){
  return (rand()%(max-min+1))+min;
}
//  随机正负数
int randfu(){
  if(rand()%2){
    return 1;
  }
  else{
    return -1;
  }
}