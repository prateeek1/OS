#include<bits/stdc++.h>
using namespace std;

struct process_struct
{
	float pid;
	float at;
	float bt;
	float ct, wt, tat, rt, start_time;
	float bt_remaining;
} ps[100];

int findmax(int a, int b)
{
	return a > b ? a : b;
}

int findmin(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	int n;
	cin >> n;


	bool is_first_process = true;
	bool is_completed[100] = {false};

	int current_time = 0;
	int completed = 0;


	float sum_tat = 0, sum_wt = 0, sum_rt = 0;
	int total_idle_time = 0, prev = 0, length_cycle = 0;

	float cpu_utilization;
	int max_completion_time, min_arrival_time;
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

	while (completed != n)
	{
		int min_index = -1;
		int minimum = INT_MAX;
		for (int i = 0; i < n; i++)
		{
			if (ps[i].at <= current_time and is_completed[i] == false)
			{
				if (ps[i].bt_remaining < minimum)
				{
					minimum = ps[i].bt_remaining;
					min_index = i;
				}
				if (ps[i].bt_remaining == minimum)
				{
					if (ps[i].at < ps[min_index].at)
					{
						minimum = ps[i].bt_remaining;
						min_index = i;
					}
				}
			}
		}

		if (min_index == -1)
		{
			current_time++;
		}
		else
		{
			if (ps[min_index].bt_remaining == ps[min_index].bt)
			{
				ps[min_index].start_time = current_time;
				total_idle_time += (is_first_process == true) ? 0 : ps[min_index].start_time - prev;
				is_first_process = false;
			}
			ps[min_index].bt_remaining -= 1;
			current_time++;
			prev = current_time;


			if (ps[min_index].bt_remaining == 0)
			{

				ps[min_index].ct = current_time;
				ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
				ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
				ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;

				sum_tat += ps[min_index].tat;
				sum_wt += ps[min_index].wt;
				sum_rt += ps[min_index].rt;
				completed++;

				is_completed[min_index] = true;

			}

		}
	}


	max_completion_time = INT_MIN;
	min_arrival_time = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		max_completion_time = findmax(max_completion_time, ps[i].ct);
		min_arrival_time = findmin(min_arrival_time, ps[i].at);
	}
	length_cycle = max_completion_time - min_arrival_time;

	for (int i = 0; i < n; i++)
		cout << ps[i].ct << " ";

	cout << endl;

	cout << sum_tat / n << endl;
	cout << sum_wt / n << endl;
	cout << sum_rt / n << endl;
}
