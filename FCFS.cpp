#include<bits/stdc++.h>
using namespace std;

struct process_struct
{
	float pid;
	float  at;
	float bt;
	float ct, wt, tat, rt, start_time;
} ps[100];


bool compareAT(struct process_struct a, struct process_struct b)
{
	int x = a.at;
	int y = b.at;
	return x < y;
}

bool comparePID(struct process_struct a, struct process_struct b)
{
	int x = a.pid;
	int y = b.pid;

	return x < y;
}

int main()
{
	int n;
	cin >> n; // no of process

	float sum_tat = 0, sum_wt = 0, sum_rt = 0;

	float length_cycle, total_idle_time = 0;

	float cpu_utilization;

	cout << fixed << setprecision(2);

	for (int i = 0; i < n; i++)
	{
		cin >> ps[i].at; //arrival time
		ps[i].pid = i;
	}

	for (int i = 0; i < n; i++)
	{
		cin >> ps[i].bt;
	}

	sort(ps, ps + n, compareAT);

	for (int i = 0; i < n; i++)
	{
		ps[i].start_time = (i == 0) ? ps[i].at : max(ps[i].at, ps[i - 1].ct);

		ps[i].ct = ps[i].start_time + ps[i].bt;
		ps[i].tat = ps[i].ct - ps[i].at;
		ps[i].wt = ps[i].tat - ps[i].bt;
		ps[i].rt = ps[i].wt;

		sum_tat += ps[i].tat;
		sum_wt += ps[i].wt;
		sum_rt += ps[i].rt;

		total_idle_time += (i == 0) ? 0 : (ps[i].start_time - ps[i - 1].ct);
	}
	length_cycle = ps[n - 1].ct - ps[0].start_time;

	//sort(ps, ps + n, comparePID);

	for (int i = 0; i < n; i++)
	{
		cout << i << " " << ps[i].at << " " << ps[i].bt << " " << ps[i].ct << " " << ps[i].tat << " " << ps[i].wt << " " << ps[i].rt << endl;
	}

	cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

	cout << sum_tat / n << endl;
	cout << sum_wt / n << endl;
	cout << sum_rt / n << endl;

	cout << n / (float)length_cycle; //throughput;

	cout << cpu_utilization * 100;






}