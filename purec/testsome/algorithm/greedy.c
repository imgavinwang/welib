/*活动安排问题
问题：设有N个活动时间集合，每个活动都要使用同一个会议室，而且同一时间内只能有一个活动使用。
要求是尽可能多的使参加的活动最大化。
求解：就是要在所给的活动集合中选出最大的相容活动子集合：
1)将活动按照结束时间进行从小到大排序。
2)然后用i代表第i个活动，s[i]代表第i个活动开始时间，e[i]代表第i个活动的结束时间。
3)按照从小到大排序，挑选出结束时间尽量早的活动，
并且满足后一个活动的起始时间晚于前一个活动的结束时间，
全部找出这些活动就是最大的相容活动子集合。
*/
#include <stdio.h>
const int N = 7;

void greedySelect(int n, int s[], int e[], int mark[])
{
	mark[0] = 1;
	int j = 0;

	//依次检查活动i是否与当前已选择的活动相容
	for(int i=1; i<n; i++) {
		if(s[i] >= e[j]) { 
			mark[i] = 1;
			j = i;
		}
	}
}

int main()
{
	//存储活动开始时间
	int s[N] = {1,6,4,7,11,11,14};
	//存储活动结束时间，活动按活动结束时间从小到大排序
	int e[N] = {3,7,8,9,13,15,16};
	int mark[N] = {0};

	printf("All activies(sTime, eTime):\n");
	for(int i=0; i<N; i++) printf("%d: (%d, %d)\n", i, s[i], e[i]);
	greedySelect(N, s, e, mark);
	printf("Max activies:\n");
	for(int i=0; i<N; i++) {
		if(mark[i] == 1) printf("%d: (%d, %d)\n", i, s[i], e[i]);
	}

	return 0;
}
