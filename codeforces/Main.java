
public class Main{
	static {
		System.out.println("Static block");
		new Main();
	}

	Main() {
		System.out.println("Constructor");
	}
	public static void main(String[] args) {
		System.out.println("Main method");
	}
}