
public class ProfList {

	String[] names = { "Emad Al-Gailani", "Jackie Wang", "First Last" };
	String[] departnemnt = { "EECS", "EECS", "Art" };
	String[] availible = {
			"Mon: Lassoande building room 2003 from 14:30 to 16:30\n  Tue: Lassoande building room 2003 from 12:30 to 13:30\n Friday: Lassoande building room 2004 from 14:30 to 16:30",
			"Mon: Stacie Library room 2003 from 14:30 to 16:30\n  Tue: Scott Library room 2003 from 12:30 to 13:30\n Friday: Lassoande building room 2004 from 14:30 to 16:30",
			"Sat: Student Center room 2003 from 14:30 to 16:30\n  Tue: Scott Library room 2003 from 12:30 to 13:30\n Friday: Lassoande building room 2004 from 14:30 to 16:30" };

	public int[] namesFoundIndexs(String name) {
		int[] index = new int[name.length()];
		int numOfIndex = 0;
		int[] returnIndex = new int[numOfIndex];

		for (int i = 0; i < name.length(); i++) {
			if (names[i].equals(name)) {
				index[numOfIndex] = i;
				numOfIndex++;
			}

		}

		if (numOfIndex == 0) {
			return null;
		} else {

			for (int i = 0; i < numOfIndex; i++) {
				returnIndex[i] = index[i];
			}
			return returnIndex;
		}
	}

	public void showNameandDepartment(int[] indexs) {
		for (int i = 0; i < indexs.length; i++) {
			System.out.println(names[i] + " " + departnemnt[i]);
		}
	}

	public void printAvailible(int index) {
		System.out.println(availible[index]);
	}

	public static void main(String[] args) {

	}

}
