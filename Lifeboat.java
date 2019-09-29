class Solution {
    public int solution(int[] people, int limit) {
        int answer = 0;
        // 간사람은 0으로 바꿔서 해결하자. // 
        
        int totalWeight = 0;
        int idx = 0;
        for(int w : people) {
        	totalWeight += w;
        }
        while(totalWeight > 0) {
        	int rideOnBoatPeopleCount = 0;
        	int weight = 0;
        	for(int i = idx; i<people.length;i++) {
        		if(people[idx] == 0) {idx++; break;}
        		if(people[i]+ weight > limit) {}
        		else if( people[i]+ weight == limit) {
        			if(rideOnBoatPeopleCount > 0) {
        				int equalWeight = 0;
        				for(int j = idx;j<people.length;j++) {
        					if(people[j] == 0) continue;
        					if(equalWeight + people[j] == limit) {
        						equalWeight += people[j];
        						people[j] = 0;
        						break;
        					}else if(equalWeight + people[j] < limit) {
        						equalWeight += people[j];
        						people[j] = 0;
        					}
        				}
        			}
        			people[idx] = 0;
        			totalWeight -= limit;
        			answer++; idx++;
        			break;
        		}
        		else if( people[i]+ weight < limit) {
        			weight += people[i];
        			rideOnBoatPeopleCount++;
        		}
        		
        		if(i == people.length - 1) { // 맨끝이라면...
        			int equalWeight = 0;
        			if(rideOnBoatPeopleCount > 0) {
        				for(int j = idx;j<people.length;j++) {
        					if(people[j] == 0) continue;
        					if(equalWeight + people[j] == limit) {
        						equalWeight += people[j];
        						people[j] = 0;
        						break;
        					}else if(equalWeight + people[j] < limit) {
        						equalWeight += people[j];
        						people[j] = 0;
        					}
        				}
        			}
        			people[idx] = 0;
        			totalWeight -= equalWeight;
        			answer++; idx++;
        		}
        	}
        }
       
        return answer;
    }
}


public class Lifeboat {

	public static void main(String[] args) {
		int[] people= {70,50,80,50};
		System.out.println(new Solution().solution(people, 100));

	}

}
