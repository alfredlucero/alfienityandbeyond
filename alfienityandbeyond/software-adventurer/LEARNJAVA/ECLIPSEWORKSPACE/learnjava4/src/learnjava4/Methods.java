package learnjava4;

import java.util.Scanner;

public class Methods {
	/**
	 * Practice with methods, classes/objects
	 * @param args
	 */
	public static void main(String[] args) {
		sayHelloWorld();
		
		String name;
		System.out.println("To whom shall I say hello to?");
		Scanner nameInput = new Scanner(System.in);
		name = nameInput.nextLine();
		
		sayHelloTo(name);
		
		int number;
		System.out.println("Now give me a number to square!");
		Scanner numberInput = new Scanner(System.in);
		number = numberInput.nextInt();
		number = square(number);
		System.out.println("The number squared is " + number);
		
		extraClass extraClassObject = new extraClass();
		extraClassObject.echo("Echo");
		extraClassObject.setSpecialName("Alfred");
		extraClassObject.setSpecialNumber(17);
		System.out.println("Special name is " + extraClassObject.getSpecialName() + " and the special number is " + extraClassObject.getSpecialNumber());
		
		System.out.println("Now we're going to make an airplane");
		airplane boeing = new airplane();
		boeing.numPassengers = 200;
		boeing.cruiseSpeed = 500;
		boeing.fuelCapacity = 2000.50;
		boeing.fuelBurnRate = 400.25;
		
		System.out.println("The boeing aircraft can hold " + boeing.numPassengers + " passengers");
		
		
		
	}
	
	static int square(int x) {
		return x * x;
	}
	
	static void sayHelloTo(String name) {
		System.out.println("Hello " + name);
	}
	
	static void sayHelloWorld() {
		System.out.println("Hello World!");
	}
}

class airplane {
	int numPassengers;		// number of people
	int cruiseSpeed;		// miles per hour
	double fuelCapacity;	// gallons
	double fuelBurnRate;	// gallons per hour
}
