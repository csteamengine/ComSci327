package assign1_01;

//Parent class of every character in the game. Such as person, rock, floor, monster, ring, weapon...
public class Tile {
	private char symbol;
	private int strength;
	private boolean locked;
	public Tile(){
		locked = false;
	}
	public Tile(char sym, int stren, boolean lock){
		symbol = sym;
		strength = stren;
		locked = lock;
	}
	public String getSymbol(){
		return symbol+"";
	}
	public int getStrength(){
		//TODO
		return 0;
	}
	public void setLock(boolean lock){
		locked = lock;
	}
	public boolean getLock(){
		return locked;
	}
}
