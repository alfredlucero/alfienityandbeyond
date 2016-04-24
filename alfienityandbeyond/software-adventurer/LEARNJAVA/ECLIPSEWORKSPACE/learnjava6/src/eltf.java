import java.util.*;

class Runner extends Thread {

	public void run() {
		for(int i = 0; i < 10; i++) {
			System.out.println("Hello " + i);
			
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
}


class Athlete implements Runnable {

	public void run() {
		for (int i = 0; i < 5; i++) {
			System.out.println("Jump " + i);
		}
		
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}

public class eltf {
	/**
	 * Practice with exceptions, lists, threads, and files
	 * @param args
	 */
	public static void main(String[] args) {
		/*
		Scanner input = new Scanner(System.in);
		
		try {
			System.out.println("Enter first number code: ");
			int n1 = input.nextInt();
			System.out.println("Enter second number code: ");
			int n2 = input.nextInt();
			int quotient = n1/n2;
			System.out.println(quotient);
		} 
		catch(Exception e){
			System.out.println("You can't do that");
		}
		
		Runner runner1 = new Runner();
		runner1.start(); // use run method in separate thread
		
		Runner runner2 = new Runner();
		runner2.start(); // run two threads concurrently
	
		Thread t1 = new Thread(new Athlete());
		Thread t2 = new Thread(new Athlete());
		
		t1.start();
		t2.start();
		*/
		
		// ArrayList
		ArrayList<String> dict = new ArrayList<String>(2);
		dict.add("Alfred");
		dict.add("Justine");
		dict.add("Pikachu");
		System.out.println(dict);
		System.out.println();
		
		for (String s : dict) {
			int i = dict.indexOf(s);
			System.out.println(i + " = " + s);
		}
		
		System.out.println(dict.get(1));
		System.out.println();
		
		// LinkedList
		LinkedList<Integer> nums = new LinkedList<Integer>();
		nums.add(1);
		nums.add(17);
		nums.add(1995);
		nums.remove(0);
		System.out.println(nums);
		System.out.println();
		
		// Modern iteration, Java 5 and later
		for (Integer num: nums)
			System.out.println(num);
		System.out.println();
		
		// Older way
		Iterator<Integer> it = nums.iterator();		
		int count;
		while(it.hasNext()){
			count = it.next();
			System.out.println(count);
		}
		System.out.println();
			
		
		// HashMap
		HashMap<String, Integer> student = new HashMap<String, Integer>();
		student.put("Alfred Lucero", 604251044);
		int id = student.get("Alfred Lucero");
		System.out.println("Your id is " + id);
		System.out.println();
		
		// HashSet
		HashSet<String> set1 = new HashSet<String>();
		set1.add("dog");
		set1.add("cat");
		
	}
}