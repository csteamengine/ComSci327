package assign1_01;

public class DungeonGenerator {
	public static void main(String[] args){
		Dungeon dung = new Dungeon();
		dung.fillDungeon();
		dung.addRoom();
		dung.cutCorridors();
		System.out.println(dung.toString());
	}
}
