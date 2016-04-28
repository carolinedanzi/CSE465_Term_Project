import java.util.HashSet;

public class Person {
	private String name;
	private HashSet<String> parents;
	private String spouse;
	
	public Person(String name, String father, String mother, String spouse) {
		this.name = name;
		parents = new HashSet<String>();
		parents.add(mother);
		parents.add(father);
		this.spouse = spouse;
	}
	
	public Person(String name, String father, String mother) {
		this.name = name;
		parents = new HashSet<String>();
		parents.add(mother);
		parents.add(father);
		this.spouse = null;
	}
	
	public Person(String name, String spouse) {
		this.name = name;
		parents = new HashSet<String>();
		this.spouse = spouse;
	}
	
	public boolean isMarried() {
		return spouse != null;
	}
	
	public String getName() {
		return name;
	}
	
	// Use a HashSet
	public HashSet<String> getParents() {
		return parents;
	}
	
	public String getSpouse() {
		return spouse;
	}
}