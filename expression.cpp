#include<iostream.h>
#include<fstream>
#include<string.h>
#include<stack>
/*
Check expression and brackets valid or not
evaluate the expression which may contain the following characters:
 ? =, +, ?, *, / and the three types of brackets "(,)", "[,]", "{,}" where
+, -, *, / are operations
*/
using namespace std;
bool AddBrackets(stack <char>&,char);
bool Check(char,char);
bool Check(stack <float>);
void numberss(char ,stack<float>&,int &,int &,char);
main(){//start main
     	stack <char>Brackets;
      stack <float>numbers;
     string line;
     int x=2;
     int z=2;
	ifstream myfile("infile.txt");
	if(myfile.is_open())//reading from the file
	{
		while(!myfile.eof()){
			getline(myfile,line);
			if(line[0]!=NULL)
			cout<<"The expressions is : "<<line<<endl;
			for(int i=0;line[i]!=NULL;i++){
   	          switch(line[i]){
	   	       case '(' :case ')':case '[':case ']':case '{':case '}':{
	   	       	if(z!=false){
	       	   		if(AddBrackets(Brackets,line[i])==false)
	             	z=false;
	             	else
	             	z=true;
	       	   	}
	   	       	break;
	   	}
	   	case '+':case '-':case '*':case '/':case '?':case '=':{
	   		if(x!=false)
	   		numberss(line[i],numbers,x,i,line[i+1]);
	   	}
	   	
   	}
   }
   cout<<endl;
             if(!Brackets.empty())
             cout<<"Invalid Brackets.\n";
             else{
             	if(z==true)
                cout<<"Valid Brackets"<<endl;
                if(z==false)
                cout<<"Invalid Brackers"<<endl;
             }
             
   	
   		    if(x==true)
   			cout<<"Valid operation"<<endl;
   			if(x==false)
   			cout<<"Invalid operation"<<endl;
			x=2;
			z=2;
			cout<<endl<<endl;
			while(!numbers.empty())
			numbers.pop();
			while(!Brackets.empty())
			Brackets.pop();
			
		}
	}//end read file
   else
   cout<<"unable to open file"<<endl;
   myfile.close();  //close file 
   
   
   



}//end main
bool AddBrackets(stack <char>&Brackets,char c){//Function to add brackets
	if(c=='(' || c=='{' || c=='[')//if was open bracket
	Brackets.push(c);
	else{
		if(c==')' || c==']' || c=='}')//if was close bracket we need to check first if empty
			if(Brackets.empty()){
				cout<<c<<" Invalid parentherses.\n";
				return false;
			}
		else{//second we need to check if last bracket was added match this one
			if(Check(Brackets.top(),c)==false){
				cout<<Brackets.top()<<" "<<c<<"Invalid parentheses sinse they do not math to each other.\n";
				Brackets.pop();
				
				return false;
			}
			else{
				cout<<Brackets.top()<<" "<<c<<"Valid parentheses"<<endl;
				Brackets.pop();
			}
		}
		
	}
	return true;
}	//end AddBrackets
bool Check(char open,char close){//Check Last bracket if match the new one(open and close brackets)
	if(open =='(' && close == ')')
	return true;
	if(open == '[' && close ==']')
	return true;
	if(open =='{' && close == '}')
	return true;
	return false;
}//end Check
bool Check(stack <float>n){//Check the object have more or equal to 2 numbers for each operation
	int c=0;
	while(!n.empty()){
		n.pop();
		c++;
	}
	if(c>=2)
	return true;
	else
	return false;
}//end Check
void numberss(char x,stack<float>&numb,int &z,int &i,char f){// Function to managing the operations
	switch(x){//start switch
			case '?':{//start case ? which is for reading a number
	   		cout<<"Enter an number: ";
	   		float x;
	   		cin>>x;
	   		numb.push(x);
	   		z=true;
	   		break;
	   	}//end case ?
	   		case '+':{// start case +
	   		float x,m;
	   		if(f=='+'){//If there is two + behind each other,  I wil ladd 1 to the last top number in the stack
		   		if(numb.size()>=1){
		   			x=numb.top();
		   			cout<<x;
		   			numb.pop();
		   			x++;
		   			numb.push(x);
		   			z=true;
		   			i++;
		   			cout<<" ++ = "<<x<<" Valid operation\n";
		   		}
		   		else{
	   			cout<<"invalid since operation of ++ needs 1 operands to be performed\n";
	   			z=false;
	   		}
		   	}
		   	else{// If only one +
	   		if(Check(numb)==true){
		   		x=numb.top();
		   		numb.pop();
		   		m=numb.top();
		   		numb.pop();
		   		numb.push(m+x);
		   		cout<<m<<" + "<<x<<" = "<<m+x;
		   		cout<<" Valid operation\n";	
		   		z=true;
		   	}
		   	else{
	   			cout<<"invalid since any operation needs 2 operands to be performed\n";
	   			z=false;
	   		}
		   	}
	   		break;
	   	}//end case +
	   	case '*':{//start case *
	   		float x,m;
		   	if(Check(numb)==true){
		   		x=numb.top();
		   		numb.pop();
		   		m=numb.top();
		   		numb.pop();
		   		numb.push(m*x);
		   		cout<<m<<" * "<<x<<" = "<<m*x;
		   		cout<<" Valid operation\n";	
		   		z=true;
		   	}
		   	else{
	   			cout<<"invalid since any operation needs 2 operands to be performed\n";
	   			z=false;
	   		}
	   		
	   		break;
	   	}//end case *
	   	case '/':{//start case /
	   		float x,m;
	   		if(Check(numb)==true){
		   		x=numb.top();
		   		cout<<x;
		   		numb.pop();
		   		m=numb.top();
		   		numb.pop();
		   		numb.push(m/x);
		   		cout<<m<<" / "<<x<<" = "<<m/x;
		   		cout<<" Valid operation\n";	
		   		z=true;
		   	}
		   	else{
	   			cout<<"invalid since any operation needs 2 operands to be performed\n";
	   			z=false;
	   		}

	   		break;
	   	}//end case /
	   	case '-':{//start case -
	   		float x,m;
	   		if(Check(numb)==true){
		   		x=numb.top();
		   		numb.pop();
		   		m=numb.top();
		   		numb.pop();
		   		numb.push(m-x);
		   		cout<<m<<" - "<<x<<" = "<<m-x ;
		   		cout<<" Valid operation\n";	
		   		z=true;
		   	}
		   	else{
	   			cout<<"invalid since any operation needs 2 operands to be performed\n";
	   			z=false;
	   		}
	   		break;
	   	}//end csae -
	   	case '=':{// star tcsae = which is print the top number in the stack
	   		if(!numb.empty()){
		   		cout<<"The top of the stack is: ";
	   		cout<<numb.top()<<endl;
		   	}
		   	else
		   	cout<<"There is no numbers entered yet\n";
	   		break;
	   	}// end case =
		
	}//end switch
}//end numberss