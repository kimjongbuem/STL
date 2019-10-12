import java.util.*;

class Solution {
    public int solution(int[] scoville, int K) {
        int answer = 0;
//        List<Integer> list = new ArrayList<Integer>();
//        for(int e : scoville) {
//        	list.add(e);
//        }
//        while(!checkScoville(list, K)) {
//        	answer++;
//        	int mix = list.get(0) + list.get(1) * 2;
//        	list.remove(0); list.remove(0);
//        	list.add(mix);
//        	list.sort(null);
//        }
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
        for(int e : scoville) {
        	pq.add(e);
        }
        while(pq.peek() < K) {
        	if (pq.size() == 1) return answer = -1;
        	int mix = pq.poll() + pq.poll() * 2 ;
        	pq.add(mix);
        	answer++;
        }
        
        
        return answer;
    }
    private boolean checkScoville(List<Integer> list, int K) {
    	for(int v : list) {
    		if(K > v) return false;
    	}
    	return true;
    }
}



public class TheHotter {
	public static void main(String[] args) {
		int scoville[]= {1,2,3,9,10,12};
		System.out.println(new Solution().solution(scoville, 7));
	}

}
