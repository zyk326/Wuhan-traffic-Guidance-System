#include<iostream>
#include<stdlib.h>
#include<limits.h>
#define MaxSize 30
#define LinessNum 13
using namespace std; 
//存放每个站信息 
struct aaa{
	int number;//站点编号 
	string name;//站点名称 
	int sidenum;//相邻站点数量 
	int side[MaxSize];//相邻站点编号 
	int belong[MaxSize];//属于哪些线路 
	int benum; //属于的线路数量 
}Station[32]={{1,"机场",1,{3},{},0},{2,"汉口站",1,{4},{},0},{3,"黄浦路",4,{1,4,5,11},{},0},{4,"航空路",3,{2,3,7},{},0},{5,"江汉路",3,{3,6,7},{},0},{6,"武汉港",1,{5},{},0},{7,"武胜路",3,{4,5,8},{},0},{8,"琴台",4,{9,10,17,7},{},0},{9,"动物园",1,{8},{},0},{10,"归元寺",1,{8},{},0},
			{11,"岳家咀",3,{3,12,15},{},0},{12,"东湖",3,{11,14,13},{},0},{13,"唐山",2,{12,23},{},0},{14,"武大",4,{12,15,20,21},{},0},{15,"洪山广场",4,{11,14,16,19},{},0},{16,"汉阳门",2,{15,18},{},0},{17,"黄鹤楼",2,{8,18},{},0},{18,"大东门",4,{16,17,19,25},{},0},{19,"中南路",3,{15,18,20},{},0},{20,"街道口",4,{14,19,21,26},{},0},
			{21,"卓刀泉",4,{14,20,22,27},{},0},{22,"体院",2,{21,23},{},0},{23,"鲁巷",3,{13,22,24},{},0},{24,"华中科大",2,{23,30},{},0},{25,"武昌站",3,{18,26,29},{},0},{26,"武汉理工大",4,{20,25,27,29},{},0},{27,"化四院",3,{21,26,28},{},0},{28,"武汉化院",2,{27,30},{},0},{29,"华中农大",2,{25,26},{},0},{30,"关山",2,{24,28}},{},0}; 
struct bbb{
	int which;//所属线路 
	int nunbers;//线路包含几个站 
	int Stas[MaxSize]; //包含的站点编号 
}Liness[MaxSize]={{1,7,{2,4,7,8,17,18,25}},{2,5,{2,4,7,5,6}},{3,13,{2,4,7,8,17,18,19,20,21,22,23,24,30}},{4,3,{1,3,4}},
				{5,9,{4,7,8,17,18,19,15,11,3}},{6,5,{9,8,7,5,3}},{7,8,{10,8,17,18,16,15,14,12}},{8,5,{4,3,11,12,13}},{9,5,{25,26,27,28,30}},{10,4,{29,26,20,14}},
				{11,5,{29,25,18,17,8}},{12,5,{30,24,23,13,12}},{13,11,{6,5,3,11,15,19,20,21,27,28,30}}};
				//连通信息
typedef struct{
	int n;
	int Sta[MaxSize][MaxSize];//各个站的连通情况 
}Route;
//创建站点的关联线路
void CreatRold(Route *&a){
	for(int i=1;i<=LinessNum;i++){
		for(int j=1;j<=Liness[i-1].nunbers;j++){
			int a=Liness[i-1].Stas[j-1];//第i条线路的第j个站点 
			int b=Liness[i-1].which;//这条线路的编号 
			Station[a-1].belong[Station[a-1].benum++]=b;//benum数字永远比所属线路数大一 
		}
	}
} 
//创建站点的关联数组
void CreatArray(Route *&a){
	int i,j,k=0,flag=0;
	for(i=0;i<a->n;i++){
		for(j=0;j<a->n;j++){
			if(i==j)
				a->Sta[i][j]=0;
			else
				a->Sta[i][j]=INT_MAX;
		}
	}
	for(i=0;i<a->n;i++){
		for(k=0;k<Station[i].sidenum;k++) {
			int buf=Station[i].side[k]-1;
			a->Sta[i][Station[i].side[k]-1]=1;
		}
	}
}
//打印
void show(Route *a){
	int i,j;
	cout<<"站点的矩阵表示"<<endl; 
	for(i=0;i<a->n;i++){
		for(j=0;j<a->n;j++){
			cout<<a->Sta[i][j]<<" ";
		}
		cout<<endl;
	}
	for(i=0;i<MaxSize;i++){
		cout<<"第"<<i+1<<"个站点的所属线路：";
		for(j=0;j<Station[i].benum;j++){
			cout<<Station[i].belong[j]<<" ";
		}
		cout<<"\t||"<<"第"<<i+1<<"个站点的所属线路个数：";
		cout<<Station[i].benum<<" ";
		cout<<endl;
	}
} 
//初始化数据 
void InitData(Route *&a,int v){
	a=(Route *)malloc(sizeof(Route));
	int i,j;
	a->n=v;
}
//创建初始路线数组
void InitArray(int RodeArray[],int now,int max,int witch,int endlist[][MaxSize],int indexnow){
	int i,j,k;
	cout<<"initarray 's now :::"<<now<<endl;
	int bufnow=now;
	if(now==0)
		bufnow+=1;
	int init=endlist[witch][bufnow];
	if(now>=1){
		int hind=endlist[witch][now-1];
		for(int m=0;m<Station[init].benum;m++){
			for(int n=0;n<Station[hind].benum;n++){
				int fromSta=Station[init].belong[m];
				int toSta=Station[hind].belong[n];
				if(fromSta==toSta){
					RodeArray[max++]=toSta;//max的数字与可换乘线路数相等 
				}
			}	
		}	
	//检测RodeArray数组
	/* */
	cout<<init+1<<"   ";
	if(now==indexnow)
		cout<<"可乘坐：";	
	else
		cout<<"可换乘：";	
	for(i=0;i<max;i++){
	cout<<RodeArray[i];
		if(i!=max-1)
			cout<<"、";
	} 
	cout<<"路公交||  "<<endl;
	cout<<hind+1<<"   "<<"可乘坐：";
		for(i=0;i<max;i++){
			cout<<RodeArray[i];
			if(i!=max-1)
				cout<<"、";
		} 
		cout<<"路公交||  "<<endl;

//	cout<<"max is  "<<max<<endl;

	}else{
		int hind=endlist[witch][bufnow-1];
		for(int m=0;m<Station[init].benum;m++){
			for(int n=0;n<Station[hind].benum;n++){
				int fromSta=Station[init].belong[m];
				int toSta=Station[hind].belong[n];
				if(fromSta==toSta){
					RodeArray[max++]=toSta;//max的数字与可换乘线路数相等 
				}
			}	
		}
		cout<<hind+1<<"   "<<"可换乘：";
		for(i=0;i<max;i++){
			cout<<RodeArray[i];
			if(i!=max-1)
				cout<<"、";
		}
		cout<<"路公交||  "<<endl; 
	}
} 
//更新RodeArray数组
void Reflash(int RodeArray[],int max,int buffRode[],int maxbuff,int now,int witch){
	max=maxbuff;int i; 
	for(i=0;i<=maxbuff;i++){
		RodeArray[i]=buffRode[i];
	}
	cout<<"Reflash 's now :::"<<now<<endl;
	cout<<witch+1<<"   "<<"可乘坐：";
		for(i=0;i<=max;i++){
			cout<<RodeArray[i];
			if(i!=max)
				cout<<"、";
		}
		cout<<"路公交||  "<<endl;
} 
//计算最短路径需要换乘的次数
void ChaTime(int endlist[][MaxSize],int ansnum,int now,int Times[]){
//	cout<<"test***||   ";cout<<ansnum<<"   "<<now<<" ||"<<endl;
	int i,j,m,n;
	for(i=0;i<=ansnum;i++){
		Times[i]=0;
	}//cout<<"testin***";
	for(i=0;i<=ansnum;i++){
		//cout<<"############################################################################";
		int max=0,RodeArray[MaxSize],buffRode[MaxSize],maxbuff=-1;
		InitArray(RodeArray,now,max,i,endlist,now);
		if(now>=2){
			for(j=now-2;j>=0;--j){
			//	cout<<"循环的   "<<Times[0]<<"    j is "<<j<<"    "; 
				int flag=0,init=endlist[i][j];
				for(int jj=0;jj<Station[init].benum;jj++){
					//cout<<endlist[0][jj]<<"  ";
				//	cout<<"|**"<<Station[init].belong[jj]<<"**|";
				}		
			//	cout<<"|now is :"<<now<<"  |init is :"<<init<<"|";
				//int hind=endlist[witch][now-1];
				for(int m=0;m<=max;m++){
					//cout<<"test in||";
					for(int n=0;n<Station[init].benum;n++){					
						int toSta=Station[init].belong[n];
					//	cout<<"("<<RodeArray[m]<<"|||"<<toSta<<")";

						//maxbuff=0;
					//int toSta=Station[hind].belong[n];
						if(RodeArray[m]==toSta){
							//cout<<"has been in"<<endl;
							flag=1;
							buffRode[++maxbuff]=RodeArray[m];				
						}
					}	
				}
				if(flag==0){
				//	cout<<"***flag=0  **"<<endl;
					Times[i]++;
					//if(j>0)					 
					InitArray(RodeArray,j,0,i,endlist,now);
					j--;
				}else if(flag==1){
				//	cout<<"***flag=1  **"<<endl;
					flag=0;
					//cout<<j<<"**";
					Reflash(RodeArray,max,buffRode,maxbuff,j,endlist[i][j]);
				}
			}
		}
	/*	for(j=now;j>=0;j--){	cout<<"testin"<<endl;
			int init=endlist[i][j];
			int hind=endlist[i][j-1];
			for(int m=0;m<Station[init].benum;m++){
				for(int n=0;n<Station[hind].benum;n++){
					if(Station[init].belong[m]==Station[hind].belong[n]){	
						flag=1;
						n=Station[hind].benum;
				    }
				}
					if(flag==1){
						m=Station[init].benum;
					}
				}
				if(flag==0){
					Times[i]++; 
				}else{
					flag=0;
				}
		}*/
	}
} 
//排序路径,从大到小 
void SortTimes(int Times[],int init,int ansnum,int Deal[]){
	if(ansnum<=init)
		return;
	int i=init,j=ansnum,base=Times[init],temp;
	while(i<j){
		while(Times[j]>=base&&i<j)
			j--;
		while(Times[i]<=base&&i<j)
			i++;
		if(i<j){
			temp=Times[i];
			Times[i]=Times[j];
			Times[j]=temp;
			temp=Deal[i];
			Deal[i]=Deal[j];
			Deal[j]=temp;
		}
	}
	Times[init]=Times[i];
	Times[i]=base;
	Deal[init]=Deal[i];
	Deal[i]=Deal[init];
	SortTimes(Times,init,i-1,Deal);
	SortTimes(Times,i+1,ansnum,Deal);
}
//打印路径
void Showrode(int ansnum,int endlist[][MaxSize],int now,int to){
	int i,j;
	//cout<<"test***||   ";cout<<ansnum<<"   "<<now<<" ||"<<endl;
	//endlist[ansnum][0]=to;
	for(j=0;j<=ansnum;j++){
		for(i=0;i<=now;i++){
			int buff=endlist[j][i]+1;
			cout<<buff<<" ";//从数组中拿到的是下标 
		}
		cout<<endl;
	}
/*	for(j=0;j<=ansnum;j++){
		for(i=0;i<now;i++){
			cout<<endlist[j][i]+1<<" ";//从数组中拿到的是下标 
		}
		cout<<endl;
	}*/
	int Times[MaxSize];//记录每一条线路换乘次数。
	int Deal[MaxSize]; //换乘次数排序 
	for(i=0;i<=ansnum;i++){
		Deal[i]=i;
	}
	for(i=0;i<=ansnum;i++){
		//cout<<"deal is"<<Deal[i]<<"|";		
	}
	ChaTime(endlist,ansnum,now,Times);//计算每条路径换乘次数。用Times一维数组存放 
	//cout<<"最终的  "<<Times[0]<<"  ";
	//int Max,first=Times[0]; 
	SortTimes(Times,0,ansnum,Deal);//从大到小，用Deal存放路径下标 
/*	for(i=0;i<=ansnum;i++){
			//cout<<endlist[i][Times[i]]<<" ";

		cout<<Times[i]<<"  "<<Deal[i]<<"||";
	}*/
	for(j=0;j<=ansnum;j++){ 
		for(i=now;i>=0;i--){
			int buff=endlist[Deal[j]][i]+1;
			cout<<buff<<" ";//从数组中拿到的是下标 
		}
		cout<<"换乘了："<<Times[j]<<"次"<<endl;
	}
}
//复制前面的数组元素
void CopyList(int endlist[][MaxSize],int ansnum,int now){
		for(int i=0;i<=now;i++){
			endlist[ansnum][i]=endlist[ansnum-1][i];
		}
} 
//获得路径数组                      0            end      v   0
void Getrode(int endlist[][MaxSize],int now,int from,int to,int ansnum,int path[][MaxSize],int s[],int anser[2],int init){
	int i;
	anser[0]=max(anser[0],ansnum);
	anser[1]=max(anser[1],now);
	cout<<"testone||   ";cout<<ansnum<<"   "<<now<<" ||"<<from<<"||"<<endl;
	/**/if(from!=0){
		endlist[ansnum][now]=from;
	}else{
		if(init==0)
			endlist[ansnum][now]=from;
		else
			anser[1]=now-1;
	}
	cout<<"testone||   ";cout<<ansnum<<"   "<<now<<" ||"<<from<<"||"<<endl;
	//endlist[ansnum][now]=from;
	for(i=0;i<s[from];i++){	
	/*if(from==0){
			//endlist[ansnum][now]=to;
		}else{
			int bufnow=now;
			if(i>=1){
				int bufans=ansnum+1;
				CopyList(endlist,bufans,now);
				ansnum++;
			}
			Getrode(endlist,++bufnow,path[from][i],to,ansnum,path,s,anser);
			//now=0; 
			//ansnum++;
		}*/
		if(from!=0){
			int bufnow=now;
			if(i>=1){
				int bufans=ansnum+1;
				CopyList(endlist,bufans,now);
				ansnum++;
			}
			if(from!=0)
			Getrode(endlist,++bufnow,path[from][i],to,ansnum,path,s,anser,init);
		}
	}
} 
//得到最短路径         路径          站点前缀数 站点数   起点  
Dispath(int dist[],int path[][MaxSize],int s[],int n,int v,int t){
	cout<<"起点：";
	cout<<v+1<<endl;
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<s[i];j++){
			cout<<path[i][j];
			if(j!=s[i]-1&&j>=0){
				cout<<"、";
			}	
		}
		cout<<"  |  ";
	}
	cout<<endl;
	int endlist[MaxSize][MaxSize],ansnum=0;
	cout<<"终点："<<t+1<<endl;
	i=0;
	int now=0;
	int anser[2]={0,0};//[0]代表ansnum，[1]代表 new
	Getrode(endlist,now,t,v,ansnum,path,s,anser,v);//获得多条路径 ，以二维数组存放 
	//cout<<anser[0]<<"   "<<anser[1]<<" ||"<<endl;	
	Showrode(anser[0],endlist,anser[1],t);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
	/**/
}
//Dijkstra算法
void Dijkstra(Route *g,int v,int t){
	int s[MaxSize],dist[MaxSize],path[MaxSize][MaxSize];
	int i,j,u,mindis,num[MaxSize];
	for(i=0;i<g->n;i++){
		dist[i]=g->Sta[v][i];
		num[i]=1;
		s[i]=0;
		if(g->Sta[v][i]<INT_MAX){
			path[i][0]=v;
		}else{
			path[i][0]=-1;
		}
	}
	s[v]=1;path[v][0]=0;
	for(i=0;i<g->n;i++){
		mindis=INT_MAX;
		for(j=0;j<g->n;j++){
			if(s[j]==0&&dist[j]<mindis){
				u=j;
				mindis=dist[j];	
			}
		}
		s[u]=1;
		for(j=0;j<g->n;j++){
			if(s[j]==0){
				if(g->Sta[u][j]<INT_MAX&&dist[u]+g->Sta[u][j]<dist[j]){
					dist[j]=dist[u]+g->Sta[u][j];
					num[j]=1;
					path[j][0]=u;	
				}
				else if(g->Sta[u][j]<INT_MAX&&dist[u]+g->Sta[u][j]==dist[j]){
					num[j]++;
					path[j][num[j]-1]=u;
				}
			}
		}
	}	
	//path[8][0]=path[9][0]=7;
	Dispath(dist,path,num,g->n,v,t);
} 
int main()
{
	int num=30;
	Route *a;
	InitData(a,num);
	CreatArray(a);//创建二维数组 
	CreatRold(a);//创建线路表 
	show(a);
	int from=0,to=29;//均以下标表示 
	Dijkstra(a,from,to); //获得并打印最短路径 	
	return 0;
}



