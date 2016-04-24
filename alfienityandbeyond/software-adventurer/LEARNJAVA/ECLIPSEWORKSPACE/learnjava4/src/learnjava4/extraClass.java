package learnjava4;

public class extraClass {
	
	private int specialNumber;
	private String specialName;
	
	public extraClass(){}
	
	public extraClass(int number, String name) {
		specialNumber = number;
		specialName = name;
	}
	
	// Repeat the message as an echo
	public void echo(String message) {
		System.out.println(message + " " + message);
	}
	
	public String getSpecialName() {
		return specialName;
	}
	public int getSpecialNumber() {
		return specialNumber;
	}
	
	public void setSpecialName(String specialName) {
		this.specialName = specialName;
	}
	public void setSpecialNumber(int specialNumber) {
		this.specialNumber = specialNumber;
	}
	
}
