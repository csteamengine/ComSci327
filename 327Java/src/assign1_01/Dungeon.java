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
		for(int j = 0;j<rooms.length;j++){
			if(j == 0){
				rHeight = rand.nextInt(7)+3;
				rWidth = rand.nextInt(7)+3;
				xCoord = rand.nextInt(69)+1;
				yCoord = rand.nextInt(10)+1;
				for(int i = xCoord -1;i<xCoord + rWidth +1;i++){
					for(int k = yCoord -1; k<yCoord + rHeight + 1;k++){
						dungeon[k][i] = new Floor();
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
					for(int i = xCoord-1;i<=rWidth + xCoord +1;i++){
						for(int k = yCoord-1;k<=rHeight + yCoord + 1;k++){
							if(dungeon[k][i].getLock()){
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
				for(int i = xCoord;i<=xCoord + rWidth;i++){
					for(int k = yCoord; k<=yCoord + rHeight;k++){
						dungeon[k][i] = new Floor();
					}
				}
			}
			rooms[j] = new Room(rHeight,rWidth,xCoord,yCoord);
		}
		
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
}
