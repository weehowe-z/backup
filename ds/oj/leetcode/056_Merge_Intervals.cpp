#include <iostream>
#include <vector>

using namespace std;

struct Interval {
  int start;
  int end;
  Interval(): start(0),end(0){}
  Interval(int s, int e): start(s),end(e){}
};


class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
      std::vector<Interval>::iterator it = intervals.begin();

      while (it != intervals.end()){
        if (newInterval.end < it->start){
          intervals.insert(it, newInterval);
          return intervals;
        }else if (newInterval.start > it -> end){
          ++it;
          continue;
        }else{
          newInterval.start = min(newInterval.start, it->start);
          newInterval.end = max(newInterval.end, it->end);
          it = intervals.erase(it);
        }
      }
      intervals.insert(intervals.end(), newInterval);
      return intervals;
    }
};

int main(int argc, char const *argv[]) {
  /* code */


  return 0;
}
