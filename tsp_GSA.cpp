// Implementation of TSP by Greedy Simulated Annealing
// by B16047, B16127
#include<bits/stdc++.h>
#include <chrono>
#include <iostream>

using namespace std;

float distance_of_cities[510][510]={};

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

float cost_tour(vector<int> &tour, int num_cities) {
	float cost = 0.0;

	for (int i = 0; i < num_cities-1; ++i)
	{
		cost += distance_of_cities[tour[i]][tour[i+1]];	
		// cout<<"cost = "<<distance_of_cities[tour[i]][tour[i+1]]<<endl;
	}
	cost += distance_of_cities[tour[num_cities-1]][tour[0]];
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
	
	if(a>b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	reverse(next.begin()+a,next.begin()+b);
	
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

void print_vec(vector<int> &vec){
    for(int i = 0;i < vec.size();++i)
        cout << vec[i] << " ";
    cout << endl;
}

vector<int> greedy_simulated_annealing(vector<int> cur_tour, int num_cities) {
	float cur_cost = cost_tour(cur_tour,num_cities);
	float min_cost = cur_cost;
	vector<int> min_tour = cur_tour;
	cout.flush();
    print_vec(min_tour);
	vector<int> next_tour;
	float next_cost;
	int flag=0;
	const clock_t begin_time = clock();
	
	while((float( clock () - begin_time ) /  CLOCKS_PER_SEC)<=295) {
		flag=0;
		int counter = 0;
		float time = (float( clock () - begin_time ) /  CLOCKS_PER_SEC);
		// cout<<temperature<<" - "<<time<<" - "<<min_cost<<endl;
		while((counter<1000 || flag==0) && (float( clock () - begin_time ) /  CLOCKS_PER_SEC)<=297) {
			next_tour = generate_next_tour(cur_tour,num_cities);
			next_cost = cost_tour(next_tour,num_cities);
			bool move_ahead = cal_prob(cur_cost,next_cost,temperature);
			if(move_ahead==true) {
				cur_cost = next_cost;
				cur_tour = next_tour;
				flag=1;
			}
			if(min_cost>cur_cost) {
				min_cost = cur_cost;
				min_tour = cur_tour;
				cout.flush();
    			print_vec(min_tour);
			}
			counter++;
		}
		temperature = temperature*0.99;
		
	}
	// cout<<"\n\ntime = "<<(float( clock () - begin_time ) /  CLOCKS_PER_SEC)<<" sec \n";
	// cout<<"min cost = "<<min_cost<<endl;
	return min_tour;

}




int main(int argc,char const *argv[]) {
	cout<<"hey"<<endl;;
	string type_dist;
	cin>>type_dist;
	int num_cities;
	cin>>num_cities;
	// cout<<num_cities<<endl;
	pair<float, float> cities[num_cities];
	for (int i = 0; i < num_cities; ++i)
	{
		cin>>cities[i].first;
		cin>>cities[i].second;
	}


	for (int i = 0; i < num_cities; ++i)
	{
		for (int j = 0; j < num_cities; ++j) {
			cin>>distance_of_cities[i][j];
		}
	}

	vector<int> tour(num_cities);

	for (int i = 0; i < num_cities; ++i)
	{
		tour[i] = i;
	}

	for (int i =0; i < num_cities; ++i) {
	   int j = generate_random_number_range(num_cities-i); // Pick random number from 0 <= r < n-i.  Pick favorite method
	   // j == 0 means don't swap, otherwise swap with the element j away
	   if (j != 0) { 
	      std::swap(tour[i], tour[i+j]);
	   }
	}


	vector<int> min_tour = greedy_simulated_annealing(tour,num_cities);
	for (int i = 0; i < num_cities; ++i)
	{
		cout<<min_tour[i]<<" ";		
	}
	cout<<endl;
	
}