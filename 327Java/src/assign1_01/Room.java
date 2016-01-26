package assign1_01;

public class Room{
	private int xCoord;
	private int yCoord;
	private int height;
	private int width;
	Tile[][] room;
	
	public Room(){
		height = 0;
		width = 0;
		xCoord = 0;
		yCoord = 0;
		room = new Tile[height][width];
	}
	public Room(int heightGiven, int widthGiven){
		height = heightGiven;
		width = widthGiven;
		room = new Tile[height][width];
		fillRoom();
	}
	public Room(int heightGiven, int widthGiven, int xCoordGiven, int yCoordGiven){
		height = heightGiven;
		width = widthGiven;
		xCoord = xCoordGiven;
		yCoord = yCoordGiven;
		room = new Tile[width][height];
		fillRoom();
	}
	public void fillRoom(){
		for(int i = 0; i < room.length;i++){
			for(int j = 0; j< room[0].length;j++){
				room[i][j] = new Floor();
			}
		}
	}
	public String toString(){
		String toReturn = "";
		for(int i = 0; i < room.length;i++){
			for(int j = 0; j< room[0].length;j++){
				toReturn += room[i][j].getSymbol();
			}
			toReturn += "\n";
		}
		return toReturn;
	}
	public int getHeight(){
		return height;
	}public int getWidth(){
		return width;
	}
	public int getXCoord(){
		return xCoord;
	}
	public int getYCoord(){
		return yCoord;
	}
	public void setXCoord(int xCoordGiven){
		xCoord = xCoordGiven;
	}
	public void setYCoord(int xCoordGiven){
		xCoord = xCoordGiven;
	}
	
}
