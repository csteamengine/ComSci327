public class RationalNumbers {
	public static void main(String[] args){
		hyperbinary(5);
	}
	public static int hyperbinary(int b){
		if(b == 0){
			return 1;
		}else if(b %2 !=0){
			return hyperbinary((b-1)/2);
		}else{
			int n = (b-2)/2;
			return hyperbinary(n) + hyperbinary(n+1);
		}
	}
	public static void hyperbinaryList(){
		int[] arr = new int[100000000];
		for(int i = 0;i < arr.length;i++){
			if(i == 0){
				arr[i] = 1;
			}else if(i%2 == 0){
				arr[i] = arr[(i/2)-1] + arr[i/2];
			}else{
				arr[i] = arr[(i-1)/2];
			}
		}
		
	}
	public static void rational(int b){
		System.out.println(hyperbinary(b) + " / " + hyperbinary(b+1));
	}
}
