#include<iostream>
#include<fstream>
#include<time.h>
using std::ifstream;
using std::ofstream;
using namespace std;

class SparseMatrix{
	int row ,column;
	int **sparse;
	int term;
	public:
		SparseMatrix(int r,int c,int t);
		int **Transpose(int ** array,int term);
		int **FastTranspose(int ** array,int term);
};

SparseMatrix::SparseMatrix(int r, int c,int t) 
{
	row = r;
	column = c;
	term = t;
}


    int **SparseMatrix::Transpose(int ** array,int term)
{
    int current=0;
	int **transpose=new int*[term];
    for (int i = 0; i < term; ++i) {
    	transpose[i] = new int[3];
    }
	for(int j=0 ; j< column ; j++ ){
		for( int k=0 ; k < term ; k++ ){
			if (array[k][1]== j){
				transpose[current][0]=j;
                transpose[current][1]=array[k][0];
                transpose[current][2]=array[k][2];
                current++;
            }
		}		
	}
	return transpose;

}

    int** SparseMatrix::FastTranspose(int ** array,int term)
{
	int *rowsize=new int[column];
	int *rowstart=new int[column];
	for(int i=0;i<column;i++){
		rowsize[i]=0;
		rowstart[i]=0;
	}
	for(int i=0;i<term;i++){
		rowsize[array[i][1]]++;
	}
	for(int i=1;i<column;i++){
		rowstart[i]=rowstart[i-1]+rowsize[i-1];
	}
	
	int **fasttranspose=new int*[term];
    for (int i = 0; i < term; ++i) {
    	fasttranspose[i] = new int[3];
    }
	for(int i=0;i<term;i++){
		int j=rowstart[array[i][1]];
		fasttranspose[j][0]=array[i][1];
		fasttranspose[j][1]=array[i][0];
		fasttranspose[j][2]=array[i][2];
		rowstart[array[i][1]]++;
	}

	delete[] rowsize;
	delete[] rowstart;
	
	return fasttranspose;
	
}

	



int main(){
	ifstream inputfile;
	ofstream outputfile;
	int row,column;
	int term=0;
	
	inputfile.open("p2.in.txt");
	outputfile.open("p2.out.txt");
	inputfile >> row >> column;
	int** matrix= new int*[row]; // dynamic array (size 10) of pointers to int

    for (int i = 0; i < row; ++i) {
    	matrix[i] = new int[column];
    }
    
	for(int  i=0 ;i < row ; i++){
		for(int j=0 ; j < column ; j++ ){
			inputfile >> matrix[i][j];
		}
	}
	for(int  i=0 ;i < row ; i++){
		for(int j=0 ; j < column ; j++ ){
			if(matrix[i][j]!=0)
			    term++;
		}
	}
	int** a= new int*[term];

    for (int i = 0; i < term; ++i) {
    	a[i] = new int[3];
    }
    int** b= new int*[term];

    for (int i = 0; i < term; ++i) {
    	b[i] = new int[3];
    }
    int** sparse= new int*[term];

    for (int i = 0; i < term; ++i) {
    	sparse[i] = new int[3];
    }
	for(int k=0;k<term;k++){
	    for(int  i=0 ;i < row ; i++){
	    	for(int j=0 ; j < column ; j++ ){
	    		if(matrix[i][j]!=0){
	    			sparse[k][0]=i;
			        sparse[k][1]=j;
			        sparse[k][2]=matrix[i][j];
			        k++;
			    }
			}
	    }
	}
    
    
	SparseMatrix obj(row,column,term);
    double start=clock();
	outputfile << "-------Use the sparse matrix in the TextBook to import-------" << endl << endl;
	outputfile<<"Tranditional 2D Matrix Representation:"<< endl;
    for(int  i=0 ;i < row ; i++){
		for(int j=0 ; j < column ; j++ ){
			outputfile << matrix[i][j]<< "\t";
		}
		outputfile << endl;
    }
    double end=clock();
    outputfile << double(end-start)/CLOCKS_PER_SEC <<"second" << endl;
    
    
    long start1 = time(NULL);
	outputfile<<"Using Transpose Method:"<<endl;
	a=obj.Transpose(sparse,term);
    for(int i=0;i<term;i++)
		outputfile<<a[i][0]<<" "<<a[i][1]<<" "<< a[i][2]<<"\n";
	long end1 = time(NULL);
    outputfile << double(end1-start1)/1000<<"second" << endl;	
	
    long start2 = time(NULL);
	outputfile<<"Using FastTranspose Method:"<<endl;
	b=obj.FastTranspose(sparse,term);
	for(int i=0;i<term;i++)
		outputfile<<b[i][0]<<" "<<b[i][1]<<" "<< b[i][2]<<"\n";
	long end2 = time(NULL);
    outputfile << double(end2-start2)/1000<<"second" << endl;
	inputfile.close();
	outputfile.close();
	
	system("pause");
	return 0;
}

