public class RationalNumbers {
	public static void main(String[] args){
		for(int i = 0;i< 1024;i++){
			System.out.println(hyperbinary(i));
		}
		System.out.println(hyperbinary(1023));
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
	
}
