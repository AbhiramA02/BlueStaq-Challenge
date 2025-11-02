#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Elevator{
  private:
    int currFloor;
    std::queue<int> eRequests;

  public:
    Elevator(int startFloor = 1) : currFloor(startFloor) {
      std::cout << "\n[Start] Floor #" << currFloor << ".\n";
    }

    void addRequest(int floor){
      if(floor > 0 && floor < 11){
        eRequests.push(floor);
        std::cout << "[Request] Floor #" << floor << " added.\n";
      }else{
        std::cout << "[Invalid Request]\n";
      }
    }

    void step(){
      if(eRequests.empty()){
        std::cout << "[Idle] Waiting on Floor #" << currFloor << ".\n";
      }else{
        int targetFloor = eRequests.front();
        if(currFloor < targetFloor){
          currFloor++;
          std::cout << "[Moving Up] Now at Floor #" << currFloor << ".\n";
        }else if(currFloor > targetFloor){
          currFloor--;
          std::cout << "[Moving Down] Now at Floor #" << currFloor << ".\n";
        }else{
          std::cout << "[Arrived] Reached Floor #" << currFloor << ".\n";
          eRequests.pop();
        }
      }
    }
};

int main(){
  /* Assume 10 Floors + Start at Floor 1 + Runs for 30s*/
  int numRequests;
  std::cin >> numRequests;

  std::vector<std::vector<int>> allRequests(30);
  for(int i = 0; i < numRequests; i++){
    int time, floor;
    std::cin >> time >> floor;
    allRequests[time].push_back(floor);
  }

  Elevator elevatorAA;
  for(int t = 0; t <= 30; t++){
    std::cout << "\n[TICK " << t << "]\n";
    for(int indvRequest: allRequests[t]){
      elevatorAA.addRequest(indvRequest);
    }

    elevatorAA.step();
  }

  return 0;
}