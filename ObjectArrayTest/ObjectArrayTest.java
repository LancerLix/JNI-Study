import java.util.*;

class ObjectArrayTest{
	private static native int[][] initInt2DArray(int size);
	public static void main(String[] args){
		int [][] i2arr=initInt2DArray(255);
		for(int i=0;i<255;i++){
			for(int j=0;j<255;j++){
				System.out.print(""+i2arr[i][j]);
			}
		System.out.println();
		}
	}

	static{
		System.loadLibrary("ObjectArrayTest");
	}
}