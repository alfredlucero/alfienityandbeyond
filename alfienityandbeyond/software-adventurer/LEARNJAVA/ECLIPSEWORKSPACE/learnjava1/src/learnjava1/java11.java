package learnjava1;

import java.util.Scanner;

public class java11 {
	
	/**
	 * Prints out "Hello World" to the console
	 * Get user input by using Scanner
	 * @param args
	 */
	public static void main(String args[]){
		System.out.println("Hello world");
		
		Scanner userInput = new Scanner(System.in);
		System.out.println(userInput.nextLine());
	}
}
