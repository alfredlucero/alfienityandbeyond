
public class main {
	/**
	 * Practice with classes/inheritance/polymorphism
	 * @param args
	 */
	public static void main(String[] args) {
		
		car garage[] = new car[2];
		
		garage[0] = new audi();
		garage[1] = new porsche();
		
		for(int i = 0; i < garage.length; i++)
			useCar(garage[i]);
	}
	
	public static void useCar(car vehicle) {
		vehicle.drive();
	}
}
