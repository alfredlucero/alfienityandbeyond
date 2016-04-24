package learnjava3;

public class arrays {
	/**
	 * Practice with arrays
	 * @param args
	 */
	public static void main(String[] args){
		int numbers[] = {0,1,2,3,4};
		int sum = 0;
		
		for (int i = 0; i < numbers.length; i++)
			sum += numbers[i];
			
		System.out.println("The average of the array of numbers is: " + sum/5);
	
		int total = 0;
		int randomNumbers[] = {10, 20, 30, 40};
		for (int x: randomNumbers)
			total += x;
		
		System.out.println("The total sum of the random numbers is " + total);
	
	}
}
