#include<bits/stdc++.h>
using namespace std;

struct process
{
	int pid;
	int at;
	int bt;
	int priority;
	int start_time;
	int ct;
	int tat;
	int wt;
	int rt;
	int bt_remaining;
} ps[100];


int main()
{
	int n;
	cin >> n;

	float sum_tat = 0, sum_wt = 0, sum_rt = 0;
	int is_completed[100] = {};
	int total_idle_time = 0;
	int cpu_utilization = 0;

	cout << setprecision(2) << fixed;

	for (int i = 0; i < n; i++)
	{
		cin >> ps[i].at;
		ps[i].pid = i;
	}

	for (int i = 0; i < n; i++)
	{
		cin >> ps[i].bt;
		ps[i].bt_remaining = ps[i].bt;
	}

	for (int i = 0; i < n; i++)
	{
		cin >> ps[i].priority;
	}

	int current_time = 0;
	int completed = 0;
	int prev = 0;

	while (completed != n)
	{
		int idx = -1;
		int mx = -1;

		for (int i = 0; i < n; i++)
		{
			if (ps[i].at <= current_time and is_completed[i] == 0)
			{
				if (ps[i].priority > mx)
				{
					mx = ps[i].priority;
					idx = i;
				}

				if (ps[i].priority == mx)
				{
					if (ps[i].at < ps[idx].at)
					{
						mx = ps[i].priority;
						idx = i;
					}
				}
			}
		}

		if (idx != -1)
		{
			cout << current_time << " " << idx << endl;
			if (ps[idx].bt_remaining == ps[idx].bt)
			{
				ps[idx].start_time = current_time;
				total_idle_time += ps[idx].start_time - prev;
			}

			ps[idx].bt_remaining -= 1;
			current_time++;
			prev = current_time;

			if (ps[idx].bt_remaining == 0)
			{
				ps[idx].ct = current_time;
				ps[idx].tat = ps[idx].ct - ps[idx].at;
				ps[idx].wt = ps[idx].tat - ps[idx].bt;
				ps[idx].rt = ps[idx].start_time - ps[idx].at;

				sum_tat += ps[idx].tat;
				sum_wt += ps[idx].wt;
				sum_rt += ps[idx].rt;

				is_completed[idx] = 1;
				completed++;

			}
		}
		else
			current_time++;

	}

	int min_arrival_time = INT_MAX;
	int max_completion_time = INT_MIN;

	for (int i = 0; i < n; i++)
	{
		min_arrival_time = min(min_arrival_time, ps[i].at);
		max_completion_time = max(max_completion_time, ps[i].ct);
	}


	for (int i = 0; i < n; i++)
		cout << ps[i].ct << " ";

	cout << endl;


	cout << sum_tat / n << endl;
	cout << sum_wt / n << endl;
	cout << sum_rt / n << endl;
	cpu_utilization = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
	int throughput = float(n) / (max_completion_time - min_arrival_time);


}