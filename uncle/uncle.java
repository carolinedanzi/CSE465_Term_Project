/**
* @author Caroline Danzi
* Dr. Zmuda
* CSE 465
* Great Uncle Problem
*/

import java.util.HashSet;

public class uncle {
	
	public static HashSet<Person> people = new HashSet<Person>();
	
	/**
	* Determines if the first person is the second person's great uncle or aunt
	* Help on iterators from http://www.tutorialspoint.com/java/util/hashset_iterator.htm
	*/
	public static boolean isGreatUncleAunt(String uncleName, String childName) {
		// Find the Person corresponding to the string uncle and child 
		Person uncle = findPerson(uncleName);
		Person child = findPerson(childName);
		
		// Get a set of the child's great grandparents
		HashSet<String> parents = child.getParents();
		HashSet<String> grandparents = new HashSet<String>();
		HashSet<String> greatgparents = new HashSet<String>();
		for(String name : parents) {
			Person p = findPerson(name);
			grandparents.addAll(p.getParents());
		}
		for(String name : grandparents) {
			Person p = findPerson(name);
			greatgparents.addAll(p.getParents());
		}
		
		// Get uncle's parents and spouse's parents (if they are married)
		HashSet<String> uncleParents = uncle.getParents();
		if(uncle.isMarried()) {
			Person spouse = findPerson(uncle.getSpouse());
			uncleParents.addAll(spouse.getParents());
		}
		
		// Check to see if the uncle & spouse's parents are in the list
		// of the child's great grandparents
		for(String uncleParent : uncleParents) {
			if(greatgparents.contains(uncleParent)) {
				return true;
			}
		}
		return false;
	}
	
	public static Person findPerson(String name) {
		Person ret = null;
		for(Person p : people) {
			if(p.getName().equals(name)) {
				ret = p;
			}
		}
		return ret;
	}
	
	public static void initializePeople() {
		people.add(new Person("male1", "female1"));
		people.add(new Person("female1", "male1"));
		people.add(new Person("male2", "male1", "female1", "female3"));
		people.add(new Person("female3", "male2"));
		people.add(new Person("male3", "male1", "female1", "female4"));
		people.add(new Person("female4", "male3"));
		people.add(new Person("female2", "male1", "female1", "male6"));
		people.add(new Person("male6", "female2"));
		people.add(new Person("male4", "male2", "female3", "female6"));
		people.add(new Person("female6", "male4"));
		people.add(new Person("male8", "male2", "female3", "female8"));
		people.add(new Person("female8",  "male8"));
		people.add(new Person("female5", "male3", "female4"));
		people.add(new Person("male5", "male3", "female4"));
		people.add(new Person("female7", "male4", "female6"));
		people.add(new Person("male7", "male4", "female6", "female10"));
		people.add(new Person("female10", "male7"));
		people.add(new Person("female9", "male8", "female8"));
	}
	
	public static void main(String[] args) {
		initializePeople();
		System.out.println("True : " + isGreatUncleAunt("male6", "female7"));
		System.out.println("False : " + isGreatUncleAunt("male6", "male8"));
		System.out.println("False : " + isGreatUncleAunt("female7", "male3"));
		System.out.println("True : " + isGreatUncleAunt("female4", "male7"));
		System.out.println("True : " + isGreatUncleAunt("male3", "male7"));
		
		System.out.println("True : " + isGreatUncleAunt("male6", "female7"));
		System.out.println("False : " + isGreatUncleAunt("female7", "male6"));
		System.out.println("False : " + isGreatUncleAunt("male5", "female8"));
		System.out.println("False : " + isGreatUncleAunt("male5", "male8"));
		System.out.println("False : " + isGreatUncleAunt("male8", "female8"));
	}
}