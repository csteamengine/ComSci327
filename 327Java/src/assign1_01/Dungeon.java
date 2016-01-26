package assign1_01;

import java.util.Random;

public class Dungeon {
	public static int width = 80;
	public static int height = 21;
	public Tile[][] dungeon;
	public Room[] rooms;
	public int seed;
	Random rand;
	public Dungeon(){
		rand = new Random();
		int numRooms = rand.nextInt(3) + 5;
		rooms = new Room[numRooms];
		dungeon = new Tile[height][width];
		
	}
	public Dungeon(int seedGiven){
		seed = seedGiven;
		rand = new Random(seed);
		int numRooms = rand.nextInt(3) + 5;
		rooms = new Room[numRooms];
		dungeon = new Tile[height][width];
	}
	public void fillDungeon(){
		for(int i = 0;i < height;i++){
			for(int j = 0; j < width;j++){
				dungeon[i][j] = new Rock();
			}
		}
	}
	public String toString(){
		String toReturn = "";
		for(int i = 0;i < height;i++){
			for(int j = 0; j < width;j++){
				toReturn += dungeon[i][j].getSymbol();
			}
			toReturn += "\n";
		}
		toReturn += "Text Line: 1\nText Line: 2\nText Line: 3";
		return toReturn;
	}
	public void addRoom(){
		int xCoord;
		int yCoord;
		int rHeight;
		int rWidth;
		boolean[][] available = new boolean[21][80];
		for(int i = 0;i<available.length;i++){
			for(int j = 0; j<available[0].length;j++){
				available[i][j] = true;
			}
		}
		for(int j = 0;j<rooms.length;j++){
			if(j == 0){
				rHeight = rand.nextInt(7)+3;
				rWidth = rand.nextInt(7)+3;
				xCoord = rand.nextInt(69)+1;
				yCoord = rand.nextInt(10)+1;
				for(int i = xCoord -1; i<=xCoord + rWidth +1;i++){
					for(int k = yCoord -1;k<=yCoord + rHeight +1;k++){
						available[k][i] = false;
					}
				}
			}else{
				rHeight = rand.nextInt(7)+3;
				rWidth = rand.nextInt(7)+3;
				xCoord = rand.nextInt(69)+1;
				yCoord = rand.nextInt(10)+1;
				int counter = 0;
				boolean avail = false;
				while(!avail){
					counter++;
					for(int i = xCoord;i<=xCoord + rWidth;i++){
						for(int m = yCoord;m<=yCoord + rHeight;m++){
							if(available[m][i] == false){
								avail = false;
								xCoord = rand.nextInt(69)+1;
								yCoord = rand.nextInt(10)+1;
								break;
							}else{
								avail = true;
							}
						}
						if(!avail){
							break;
						}
					}
					if(counter > 1000){
						rHeight = rand.nextInt(7)+3;
						rWidth = rand.nextInt(7)+3;
					}
				}
				for(int i = xCoord-1; i<=xCoord + rWidth +1;i++){
					for(int k = yCoord-1;k<=yCoord + rHeight +1;k++){
						available[k][i] = false;
					}
				}
			}			
			rooms[j] = new Room(rHeight,rWidth,xCoord,yCoord);
		}
		insertRooms();
		
	}
	public void cutCorridors(){
		sort();
		int counter = 0;
		while(counter < rooms.length-1){
			int curX = rooms[counter].getXCoord() + (rooms[counter].getWidth())/2-1;
			int curY = rooms[counter].getYCoord() + (rooms[counter].getHeight())/2-1;
			int tarX = rooms[counter + 1].getXCoord() + (rooms[counter+ 1].getHeight())/2-1;
			int tarY = rooms[counter + 1].getYCoord() + (rooms[counter + 1].getHeight())/2-1;
			if(rooms[counter+1].getWidth() == 3){
				tarX = rooms[counter+1].getXCoord() +1;
			}
			if(rooms[counter+1].getHeight() == 3){
				tarY = rooms[counter+1].getYCoord() +1;
			}
			while(curX != tarX){
				
				if(curX <= tarX){
					curX++;
					if(!dungeon[curY][curX].getLock()){
						dungeon[curY][curX] = new Corridor();
					}
					
				}else if(curX >= tarX){
					curX--;
					if(!dungeon[curY][curX].getLock()){
						dungeon[curY][curX] = new Corridor();
					}
				}
			}
			while(curY != tarY){
				if(curY <= tarY){
					curY++;
					if(!dungeon[curY][curX].getLock()){
						dungeon[curY][curX] = new Corridor();
					}
				}else if(curY >= tarY){
					curY--;
					if(!dungeon[curY][curX].getLock()){
						dungeon[curY][curX] = new Corridor();
					}
				}
			}
			counter++;
		}
//		for(int i = 0;i<rooms.length-1;i++){
//			int num = rand.nextInt(rooms[i].getHeight() -2)+1;
//			int num1 = rand.nextInt(rooms[i+1].getWidth() -2)+1;
//			if(rooms[i].getYCoord() + num < rooms[i+1].getYCoord()){  //rooms[i].getYCoord() +num < rooms[i+1].getYCoord()
//				for(int j = rooms[i].getXCoord() + rooms[i].getWidth();j< rooms[i+1].getXCoord() + num1;j++){  //+ rand.nextInt(rooms[i+1].getWidth())
//					dungeon[rooms[i].getYCoord()+ num][j] = new Corridor();
//				}
//				int test = rooms[i+1].getYCoord();
//				for(int m = rooms[i].getYCoord() + num;m< test;m++ ){
//					dungeon[m][rooms[i+1].getXCoord() + num1]= new Corridor();
//				}
//			}else if(rooms[i].getYCoord() > rooms[i+1].getYCoord() + rooms[i+1].getHeight()){
//				for(int j = rooms[i].getXCoord() + rooms[i].getWidth();j< rooms[i+1].getXCoord() + num1;j++){  //+ rand.nextInt(rooms[i+1].getWidth())
//					dungeon[rooms[i].getYCoord()+ num][j] = new Corridor();
//				}
//				for(int k = rooms[i].getYCoord() + num;k<rooms[i+1].getYCoord() + rooms[i+1].getHeight();k++){
//					dungeon[k][rooms[i+1].getXCoord() + num1] = new Corridor();
//				}
//			}
//		}
	}
	public void sort(){
		for(int l = 0;l<rooms.length;l++){
			int low= l;
			for(int i = l+1;i<rooms.length;i++){
				if(rooms[i].getXCoord()<rooms[low].getXCoord()){
					low = i;
				}else if(rooms[i].getXCoord() == rooms[low].getXCoord()){
					if(rooms[i].getYCoord() < rooms[low].getYCoord()){
						low = i;
					}
				}
			}
			swap(low,l);
		}
	}
	public void swap(int low,int spot){
		Room temp = rooms[spot];
		rooms[spot] = rooms[low];
		rooms[low] = temp;
	}
	public void insertRooms(){
		for(int i = 0; i< rooms.length;i++){
			if(rooms[i] == null){
				break;
			}
			for(int k = rooms[i].getXCoord();k<rooms[i].getWidth() + rooms[i].getXCoord();k++){
				for(int j = rooms[i].getYCoord();j<rooms[i].getHeight() + rooms[i].getYCoord();j++){
					dungeon[j][k] = new Floor();
				}
			}
			
		}
	}
	
}
