#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Solution{
    public:
        vector<int> sort(vector<int> vec){
            for(int i = 1;i<vec.size();i++){
                int index = i;
                while ((vec[index] < vec[index - 1]) && (index != 0))
                {
                    int temp = vec[index - 1];
                    vec[index - 1] = vec[index];
                    vec[index] = temp;
                    index--;
                }
                
            }
            return vec;
        }

        vector<int> randomVec(int num){
            vector<int> vec;
            srand((int)time(0));
            for(int i = 0;i<num;i++){
                vec.push_back(rand()%num);
            }
            return vec;
        }

        void printVec(vector<int> vec){
            for(int i;i<vec.size();i++){
                cout<<vec[i]<<",";
                }
        }
};

clock_t start,endtime;

int main(){
    Solution sol;

    //vector<int> input = {3,2,4,1,7,8,12,89,20,12,30,50,147,2};
    vector<int> input = sol.randomVec(100);

    start = clock();
    vector<int> output = sol.sort(input);
    endtime = clock();
    double totaltime = (double)(endtime - start)/CLOCKS_PER_SEC;
    sol.printVec(output);
    cout<<"Total Time: "<<totaltime*1000<<"ms"<<endl;
}