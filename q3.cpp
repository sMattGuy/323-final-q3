#include <iostream>
#include <stdlib.h>
#include <fstream>

class Q3{
	public:
	int n;
	int** adjMatrix;
	int* valArray;
	
	Q3(int n){
		this->n = n;
		this->adjMatrix = new int*[n+1];
		for(int i=0;i<n+1;i++){
			this->adjMatrix[i] = new int[n+1];
		}
		for(int i=1;i<n+1;i++){
			for(int j=1;j<n+1;j++){
				if(i == j){
					this->adjMatrix[i][j] = 1;
				}
				else{
					this->adjMatrix[i][j] = 0;
				}
			}
		}
		this->valArray = new int[n+1];
		this->valArray[0] = 1;
		this->valArray[1] = 0;
		for(int i=2;i<n+1;i++){
			this->valArray[i] = 0;
		}
	}
	
	void loadMatrix(int node1, int node2){
		this->adjMatrix[node1][node2] = 1;
	}
	bool checkDone(){
		for(int i=1;i<this->n+1;i++){
			if(this->valArray[i] == 0){
				return false;
			}
		}
		return true;
	}
	bool validCheck(int nextNode, int newValue){
		for(int j=1;j<=this->n;j++){
			if(this->adjMatrix[nextNode][j] == 1 && this->valArray[j] == newValue){
				return false;
			}
		}
		return true;
	}
	void printArray(std::ofstream& output){
		output<<this->n<<std::endl;
		for(int i=1;i<this->n+1;i++){
			output<<i<<"\t"<<(char)this->valArray[i]<<std::endl;
		}
	}
};

int main(int argc, char* argv[]){
	if(argc != 4){
		std::cout<<"You must include 3 arguments (inFile, outFile1, outFile2)"<<std::endl;
		return -1;
	}
	std::ifstream inFile(argv[1]);
	if(!inFile.good()){
		std::cout<<"Invalid input file."<<std::endl;
		return -1;
	}
	std::ofstream out1;
	std::ofstream out2;
	out1.open(argv[2],std::ios::out);
	out2.open(argv[3],std::ios::out);
	
	int N = 0;
	inFile >> N;
	int newValue = 65;
	Q3* q = new Q3(N);
	
	int node1;
	while(inFile >> node1){
		int node2;
		inFile >> node2;
		q->loadMatrix(node1, node2);
	}
	for(int i=1;i<N+1;i++){
		for(int j=1;j<N+1;j++){
			out2<<q->adjMatrix[i][j]<<"\t";
		}
		out2<<std::endl;
	}
	while(!q->checkDone()){
		int nextNode = 1;
		while(nextNode <= N){
			if(q->valArray[nextNode] == 0){
				if(q->validCheck(nextNode, newValue)){
					out2<<"assigning "<<nextNode<<" the value "<<newValue<<std::endl;
					q->valArray[nextNode] = newValue;
				}
			}
			nextNode++;
		}
		q->printArray(out2);
		newValue++;
	}
	q->printArray(out1);
}