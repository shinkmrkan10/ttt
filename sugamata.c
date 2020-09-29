#include<stdio.h>

void display(char data[3][3]);
void init_board(char data[3][3]);
int turn_p(void);
int board_check(int num,char data);
void turn_e(char data[3][3]);
int win_check(char data[3][3]);
int main(void){
int i,j,tmp,win=0;
char data[3][3];
char *winner[2]={"Player","Computer"};
init_board(data);

printf("三目並べ\n");
printf("石を置く場所は1~9の数字で入力してください。\n");

for(i=0;i<9;i++){
display(data);
if(i%2==0){//i<9){
do{
tmp=turn_p();
}while(board_check(tmp,data[tmp/3][tmp%3])==1);
data[tmp/3][tmp%3]='X';

//turn_e(data);	//test
}else{
turn_e(data);
}
win=win_check(data);
if(win!=0){
break;
}
}

//win=1;	//test
if(win!=0){
printf("\n%s is winner!\n",winner[win-1]);
}else{
printf("\nDraw game.\n");
}
display(data);

return 0;
}

void display(char data[3][3]){ 
int i,j;
printf("+---+---+---+\n");
for(i=0;i<3;i++){
for(j=0;j<3;j++){
printf("| %c ",data[i][j]);
}
printf("|\n+---+---+---+\n");
}
printf("\n");
}

void init_board(char data[3][3]){
int i,j;
for(i=0;i<3;i++){
for(j=0;j<3;j++){
data[i][j]='0'+i*3+j+1;
}
}
}

int turn_p(void){
int in_num;
int flag=0;
do{
do{
printf("PLAYER please input board num:");
scanf("%d",&in_num);
}while(in_num<1 || 9<in_num);
printf("%dで良いですか? YES:1 NO:0\n");
do{
scanf("%d",&flag);
}while(flag<0 || 1<flag);
}while(flag==0);
return in_num-1;
}

int board_check(int num,char data){
if(data=='X' || data=='O'){
return 1;
}
return 0;
}

void turn_e(char data[3][3]){
int i,j,tmp=0,flag;
int point[8]={0},p_set[8]={1,2,3,4,5,6,7,8};
int p_num[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
for(i=0;i<3;i++){
for(j=0;j<3;j++){
if(data[i][j]=='X'){
point[i]+=1;
point[3+j]+=1;
if(i==j) point[6]+=1;
if(2-i==j) point[7]+=1;
}
if(data[i][j]=='O'){
point[i]-=2;
point[3+j]-=2;
if(i==j) point[6]-=2;
if(2-i==j) point[7]-=2;
}

}
}
for(i=0;i<8;i++){
if(point[i]==-3){
point[i]=0;
}
}
for(i=1;i<8;i++){
for(j=i;j>0;j--){
if(point[j-1]>point[j]){
tmp=point[j];
point[j]=point[j-1];
point[j-1]=tmp;
tmp=p_set[j];
p_set[j]=p_set[j-1];
p_set[j-1]=tmp;
}
}
}

if(point[0]==-4){
flag=p_set[0];
}else if(point[7]==2){
flag=p_set[7];
}else{
if(p_set[0]<p_set[7]){
flag=p_set[0]*10 + p_set[7];
}else{
flag=p_set[7]*10 + p_set[0];
}
}



for(i=0;i<8;i++){
printf("P[%d]:%d...",p_set[i],point[i]);
}
printf("\n");

/*
if(point[0]==-4){
flag=p_set[0];
}else if(point[7]==2){
flag=p_set[7];
}else if(point[0]==-2 && point[7]==1){
if(p_set[0]>p_set[7]){
flag=p_set[0]+p_set[7]*10;
}else{
flag=p_set[7]+p_set[0]*10;
}

}else if(point[7]==1){
flag=p_set[7];
}else if(point[0]==-2){
flag=point[0];
}else {
flag=p_set[7];
}
*/
printf("%d",flag);

if(flag<=3){
for(i=0;i<3;i++){
if('0'<=data[flag-1][i] && data[flag-1][i]<='9'){
data[flag-1][i]='O';
tmp=(flag-1)*3+i;
break;
}
}
}else if(flag <=6){
for(i=0;i<3;i++){
if('0'<=data[i][flag-4] && data[i][flag-4]<='9'){
data[i][flag-4]='O';
tmp=i*3+flag-4;
break;

}
}
}else if(flag ==7){
for(i=0;i<3;i++){
if('0'<=data[i][i] && data[i][i]<='9'){
data[i][i]='O';
tmp=i*3+i;
break;
}
}
}else if(flag ==8){
for(i=0;i<3;i++){
if('0'<=data[i][2-i] && data[i][2-i]<='9'){
data[i][2-i]='O';
tmp=i*3+2-i;
break;
}
}
}else if(flag>10){
for(i=0;i<3;i++){
for(j=0;j<3;j++){
if(p_num[(flag%10)-1][i]==p_num[(flag/10)-1][j]){
tmp=p_num[(flag/10)-1][j];
data[tmp/3][tmp%3]='O';
break;
}
}
}
}


/*
if(flag%10<7){
data[flag/10-1][(flag%10-1)%3]='O';
tmp=((flag/10)-1)*3+(flag%10-1)%3;
}else if(flag%10==7){
data[(flag/10-1)%3][(flag/10-1)%3]='O';
tmp=((flag/10-1)%3)*3+(flag/10-1)%3;
}else{
data[(flag/10)%3-1][2-((flag/10)%3-1)]='O';
tmp=((flag/10)%3)*3+(2-((flag/10)%3));
}
}
*/
printf("COMPUTER set on board %d\n",tmp+1);
}

int win_check(char data[3][3]){
int i,j,tmp;
int point[8]={0};
for(i=0;i<3;i++){
for(j=0;j<3;j++){
if(data[i][j]=='X'){
point[i]+=1;
point[3+j]+=1;
if(i==j) point[6]+=1;
if(2-i==j) point[7]+=1;
}
if(data[i][j]=='O'){
point[i]-=2;
point[3+j]-=2;
if(i==j) point[6]-=2;
if(2-i==j) point[7]-=2;
}

}
}

for(i=1;i<8;i++){
for(j=i;j>0;j--){
if(point[j-1]>point[j]){
tmp=point[j];
point[j]=point[j-1];
point[j-1]=tmp;
}
}
}
/*
for(i=0;i<8;i++){
printf("%d...",point[i]);
}
*/
if(point[7]==3){
return 1;
}else if(point[0]==-6){
return 2;
}
return 0;
}