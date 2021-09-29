#include<bits/stdc++.h>

using namespace std;

struct process_struct
{
	int pid;
	int at;
	int bt;
	int ct, wt, tat, rt, start_time;
	int bt_remaining;
} ps[100];


bool compareAT(struct process_struct a, struct process_struct b)
{
	float x = a.at;
	float y = b.at;

	return x < y;
}

bool comparePID(struct process_struct a, struct process_struct b)
{
	float x = a.pid;
	float y = b.pid;

	return x < y;
}


int main()
{
	int n;
	int index;
	cin >> n;

	queue<int>q;
	int cpu_utilization;

	bool visited[100] = {false}, is_first_process = true;
	int current_time = 0, max_completion_time;

	int completed = 0, tq, total_idle_time = 0, length_cycle = 0;
	float sum_tat = 0, sum_wt = 0, sum_rt = 0;

	cout << fixed << setprecision(2);

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
	cin >> tq;
	sort(ps, ps + n, compareAT);

	q.push(0);
	visited[0] = true;

	while (completed != n)
	{
		index = q.front();
		q.pop();


		if (ps[index].bt_remaining == ps[index].bt)
		{
			ps[index].start_time = max(current_time, ps[index].at);
			total_idle_time += (is_first_process == true) ? 0 : ps[index].start_time - current_time;
			current_time = ps[index].start_time;
			is_first_process = false;
		}

		if (ps[index].bt_remaining - tq > 0)
		{
			ps[index].bt_remaining -= tq;
			current_time += tq;
		}
		else
		{
			current_time += ps[index].bt_remaining;
			ps[index].bt_remaining = 0;
			completed++;

			ps[index].ct = current_time;
			ps[index].tat = ps[index].ct - ps[index].at;
			ps[index].wt = ps[index].tat - ps[index].bt;
			ps[index].rt = ps[index].start_time - ps[index].at;

			sum_tat += ps[index].tat;
			cout << ps[index].tat << endl;
			sum_wt += ps[index].wt;
			sum_rt += ps[index].rt;
		}

		//check which process needs to be put in ready queue

		for (int i = 1; i < n; i++)
		{
			if (ps[i].bt_remaining > 0 and ps[i].at <= current_time and visited[i] == false)
			{
				q.push(i);
				visited[i] = true;
			}
		}

		if (ps[index].bt_remaining > 0)
			q.push(index);

		if (q.empty())
		{
			for (int i = 1; i < n; i++)
			{
				if (ps[i].bt_remaining > 0)
				{
					q.push(i);
					visited[i] = true;
					break;
				}
			}
		}
	}

	max_completion_time = INT_MIN;
	for (int i = 0; i < n; i++)
		max_completion_time = max(max_completion_time, ps[i].ct);

	length_cycle = max_completion_time - ps[0].at;

	cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

	sort(ps, ps + n, comparePID);

	for (int i = 0; i < n; i++)
		cout << ps[i].ct << " ";

	cout << endl;

	cout << sum_tat / n << endl;
	cout << sum_wt / n << endl;
	cout << sum_rt / n << endl;

}