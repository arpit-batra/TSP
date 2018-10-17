#include<bits/stdc++.h>
#include <chrono>
#include <iostream>

using namespace std;

struct timer
{
    typedef std::chrono::steady_clock clock ;
    typedef std::chrono::seconds seconds ;

    void reset() { start = clock::now() ; }

    unsigned long long seconds_elapsed() const
    { return std::chrono::duration_cast<seconds>( clock::now() - start ).count() ; }

    private: clock::time_point start = clock::now() ;
};


// eu
// 2
// 1.4 6.3
// 2.5 6.9
// 0 5.3
// 1.9 0



// int num_cities=0;

float temperature = 10e10;

int generate_random_number_range(int num_cities) {
	int min = 0;
	int max = num_cities-1;
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

	auto random_integer = uni(rng);

	return random_integer;
}

float cost_tour(vector<int> &tour, int num_cities, vector<vector<float>> &distance) {
	float cost = 0.0;
	for (int i = 0; i < num_cities-1; ++i)
	{
		cost += distance[tour[i]][tour[i+1]];	
	}
	cost += distance[tour[num_cities-1]][tour[0]];
	return cost;
}

vector<int> generate_next_tour(vector<int> cur, int num_cities) {
	int min = 0;
	int max = num_cities-1;
	int a=0,b=0;
	vector<int> next = cur;
	while(a==b){
		a = generate_random_number_range(num_cities);
		b = generate_random_number_range(num_cities);
	}
	// cout<<a<<" "<<b<<endl;

	// swap(next[a],next[b]);

	if(a>b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	reverse(next.begin()+a,next.begin()+b);
	// for (int i = 0; i < num_cities; ++i)
	// {
	// 	cout<<next[i]<<" ";
	// }
	// cout<<endl;

	return next;
}

bool cal_prob(float cur_cost, float next_cost, float temperature) {
	srand(time(NULL));
    if(cur_cost>next_cost){
        return true;
    }
    else
    {
	    double sigmoid_prob = 1/(1+exp(-1*(cur_cost - next_cost)/temperature));
	    double random_prob = (double)rand() / (double) RAND_MAX;
	    if(sigmoid_prob > random_prob)
	        return true;
	    else 
	        return false;
    }
}
// 50:30
// 51:30

vector<int> greedy_simulated_annealing(vector<int> cur_tour, int num_cities, vector<vector<float>> &distance) {
	float cur_cost = cost_tour(cur_tour,num_cities,distance);
	float min_cost = cur_cost;
	vector<int> min_tour = cur_tour;
	vector<int> next_tour;
	float next_cost;
	int flag=0;
	// double startTime = GetTickCount();
	// timer t ;
	// t.reset();
	const clock_t begin_time = clock();
	cout<<begin_time<<endl;
	// return cur_tour;
	while((float( clock () - begin_time ) /  CLOCKS_PER_SEC)<=300) {
		flag=0;
		int counter = 0;
		float time = (float( clock () - begin_time ) /  CLOCKS_PER_SEC);
		cout<<temperature<<" - "<<time<<endl;
		while((counter<1000 || flag==0) && (float( clock () - begin_time ) /  CLOCKS_PER_SEC)<=300) {
			next_tour = generate_next_tour(cur_tour,num_cities);
			next_cost = cost_tour(next_tour,num_cities,distance);
			bool move_ahead = cal_prob(cur_cost,next_cost,temperature);
			if(move_ahead==true) {
				cur_cost = next_cost;
				cur_tour = next_tour;
				flag=1;
			}
			if(min_cost>cur_cost) {
				min_cost = cur_cost;
				min_tour = cur_tour;
			}
			counter++;
		}
		temperature = temperature*0.99;
		if(temperature<1) {
			temperature = 1;
		}
	}
	cout<<"\n\ntime = "<<(float( clock () - begin_time ) /  CLOCKS_PER_SEC)<<" sec \n";
	cout<<"min cost = "<<min_cost<<endl;
	return min_tour;

}

int main() {
	string type_dist;
	cin>>type_dist;
	int num_cities;
	cin>>num_cities;
	pair<float, float> cities[num_cities];
	// cout<<cities.size()<<endl;
	for (int i = 0; i < num_cities; ++i)
	{
		cin>>cities[i].first;
		cin>>cities[i].second;
	}
	// for (int i = 0; i < num_cities; ++i)
	// {
	// 	cout<<cities[i].first<<" "<<cities[i].second<<" \n";
	// }
	// cout<<endl;

	vector<vector<float>> distance(num_cities, vector<float>(num_cities));

	for (int i = 0; i < num_cities; ++i)
	{
		// distance[i].resize(num_cities);
		for (int j = 0; j < num_cities; ++j) {
			cin>>distance[i][j];
		}
	}

	// for (int i = 0; i < num_cities; ++i)
	// {
	// 	for (int j = 0; j < num_cities; ++j) {
	// 		cout<<distance[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	vector<int> tour(num_cities);

	for (int i = 0; i < num_cities; ++i)
	{
		tour[i] = i;
	}
	cout<<type_dist<<" wit no. of cities = "<<num_cities<<endl;
	int n;
	cin>>n;
	vector<int> min_tour = greedy_simulated_annealing(tour,num_cities,distance);
	for (int i = 0; i < num_cities; ++i)
	{
		cout<<min_tour[i]<<" ";
	}
	cout<<endl;
	cout<<type_dist<<" wit no. of cities = "<<num_cities<<endl;
	
	for (int i = 0; i < num_cities; ++i)
	{
		cout<<cities[i].first<<" "<<cities[i].second<<" ";
	}
	cout<<endl;
}