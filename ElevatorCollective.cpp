#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

enum Direction { DOWN = -1, IDLE = 0, UP = 1 };

class Elevator{
  private:
    int currFloor;
    Direction dir;
    std::set<int> upStops;                    
    std::set<int, std::greater<int>> downStops; 
    int minFloor, maxFloor;

    Direction chooseIdleDirection(){
      if (upStops.empty() && downStops.empty()) return IDLE;
      int distUp = upStops.empty()   ? INT_MAX : (*upStops.begin()) - currFloor;
      int distDn = downStops.empty() ? INT_MAX : currFloor - (*downStops.begin());
      if (distUp == INT_MAX && distDn == INT_MAX) return IDLE;
      if (distUp < distDn) return UP;
      if (distDn < distUp) return DOWN;
      return UP; // tie-break upward
    }

    bool shouldStopHere() {
      bool stop = false;
      if(dir == UP){
        auto it = upStops.find(currFloor);
        if(it != upStops.end()){ upStops.erase(it); stop = true; }
      }else if(dir == DOWN){
        auto it = downStops.find(currFloor);
        if(it != downStops.end()){ downStops.erase(it); stop = true; }
      }else{
        bool any = false;
        auto itU = upStops.find(currFloor);
        if(itU != upStops.end()){ upStops.erase(itU); any = true; }
        auto itD = downStops.find(currFloor);
        if(itD != downStops.end()){ downStops.erase(itD); any = true; }
        stop = any;
      }
      return stop;
    }

    void maybeReverse() {
      if (dir == UP && upStops.empty() && !downStops.empty()) dir = DOWN;
      else if (dir == DOWN && downStops.empty() && !upStops.empty()) dir = UP;
      else if (upStops.empty() && downStops.empty()) dir = IDLE;
    }

  public:
    Elevator(int startFloor = 1, int lo = 1, int hi = 10)
      : currFloor(startFloor), dir(IDLE), minFloor(lo), maxFloor(hi) {
      std::cout << "\n[Start] Floor #" << currFloor << ".\n";
    }

    void addRequest(int floor){
      if(floor < minFloor || floor > maxFloor){
        std::cout << "[Invalid Request]\n";
        return;
      }
      if(floor > currFloor){
        if(upStops.insert(floor).second)
          std::cout << "[Request] ↑ Floor #" << floor << " added.\n";
      }else if (floor < currFloor){
        if(downStops.insert(floor).second)
          std::cout << "[Request] ↓ Floor #" << floor << " added.\n";
      }else{
        upStops.insert(floor);
        downStops.insert(floor);
        std::cout << "[Request] ⦿ Current Floor #" << floor << " added.\n";
      }

      if (dir == IDLE) dir = chooseIdleDirection();
    }

    void step(){
      if(shouldStopHere()){
        std::cout << "[Arrived] Doors open at Floor #" << currFloor << ".\n";
        maybeReverse();
        return;
      }

      if (dir == IDLE) dir = chooseIdleDirection();

      if(dir == UP){
        if (currFloor < maxFloor) {
          currFloor++;
          std::cout << "[Moving Up] Now at Floor #" << currFloor << ".\n";
        } else {
          dir = DOWN;
        }
      }else if(dir == DOWN){
        if (currFloor > minFloor) {
          currFloor--;
          std::cout << "[Moving Down] Now at Floor #" << currFloor << ".\n";
        } else {
          dir = UP;
        }
      }else{
        std::cout << "[Idle] Waiting on Floor #" << currFloor << ".\n";
      }

      if(shouldStopHere()){
        std::cout << "[Arrived] Doors open at Floor #" << currFloor << ".\n";
        maybeReverse();
      } else {
        maybeReverse();
      }
    }
};

int main(){
  /* 10 Floors, start at 1, run for 30 ticks (0..30) */
  int numRequests;
  if(!(std::cin >> numRequests)) return 0;

  std::vector<std::vector<int>> allRequests(31);
  for(int i = 0; i < numRequests; i++){
    int time, floor;
    std::cin >> time >> floor;
    if(0 <= time && time <= 30){
      allRequests[time].push_back(floor);
    }
  }

  Elevator elevatorAA(1, 1, 10);
  for(int t = 0; t <= 30; t++){
    std::cout << "\n[TICK " << t << "]\n";
    for(int indvRequest: allRequests[t]){
      elevatorAA.addRequest(indvRequest);
    }
    elevatorAA.step();
  }
  return 0;
}