import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main{
	public static void main(String[] args) {
		String regex = "^(?:(?:[^ac]{2})*(?:(?:ac|ca|aa|cc)(?:[^ac]{2})*)*)?$";
		String even_regex = "(.{2})*";
		Pattern pat = Pattern.compile(even_regex);
		String s = "abcdabcddcbadcba";
		Matcher mat = pat.matcher(s);
		Pattern pattern = Pattern.compile(regex);
		Matcher matcher = pattern.matcher(s);
		if (matcher.matches()) {
			System.out.println("The input matches the pattern.");
        } else {
			System.out.println("The input does not match the pattern.");
        }
	}
}