package assign1_01;



public class tester {
	public static void main(String[] args){
		Dungeon dung = new Dungeon();
		dung.fillDungeon();
		dung.addRoom();
		dung.cutCorridors();
		System.out.println(dung.toString());
//		int[][] test = new int[5][10];
//		System.out.println(test.length);
//		for(int i = 0;i< test.length;i++){
//			for(int j = 0; j<test[0].length;j++){
//				System.out.print(".");
//			}
//			System.out.println();
//		}
	}

}

