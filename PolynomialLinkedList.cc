//Student Name : Marc Klocke
//Student ID : 260399607

#include<stdio.h>
#include<math.h>
#include<iostream>

//Used typedef to make define the struct for the linked list
typedef struct TermElement
{
	int degree;
	double coefficient;
	struct TermElement* next;
};

//Evaluate method evaluats a single polynomial based on the x input
double evaluate(TermElement* input, double x)
{
	double result;
	double temp;
	
	//Used the power method from math.h
	temp = pow(x, input->degree);
	result = temp * input->coefficient;
	
	return result;
}

//Adds a node(new polynomial) to the list, if list is empty then first entry makes the list
TermElement* addTerm(TermElement* root, int degree, double coefficient)
{
	//Initialising variables needed for later methods
	TermElement* current = new TermElement;
	TermElement* toAdd = new TermElement;

	//Setting the new Node up with input variables
	toAdd->degree = degree;
	toAdd->coefficient = coefficient;
	
	//Checks to see if first entry
	if(root == NULL)
	{
		toAdd->next = NULL;
		return toAdd;
	}

	//Checks if the the new node belongs in front of the new node
	if(toAdd->degree > root->degree)
	{
		toAdd->next = root;
		return toAdd;
	}

	//Checks to see if the root node and the input node are of the same degree
	//If they are of same degree they merge
	//If resulting coefficient is zero then node is deleted
	if(toAdd->degree == root->degree)
	{
		root->coefficient = toAdd->coefficient + root->coefficient;
		if(root->coefficient == 0)
		{
			root = root->next;
			delete root;
		}
	}

	current = root;
	
	while(current->next != NULL)
	{
		TermElement* next = new TermElement;
		next = current->next;
		
		//Finds the proper place in the list and adds the node
		//Modifies the pointers for the list
		if(toAdd->degree < current->degree && toAdd->degree > next->degree)
		{
			current->next = toAdd;
			toAdd->next = next;
			return root;
		}

		//Already checked the root case earlier, so start from next node
		if(toAdd->degree == next->degree)
		{
			next->coefficient = (next->coefficient) + (toAdd->coefficient);
			if(current->coefficient == 0)
			{
				//Delete node from the linked list by pointing it to NULL
				current->next = next->next;
				next->next = NULL;
				delete next;
			}
			return root;
				
		}

		current = current->next;
	}
	return root;
}


double evaluatePolynomial(TermElement* root, double x)
{
	//Check to see if root is NULL
	if(root == NULL)
	{
		return 0;
	}
	double runningTotal = 0;
	
	TermElement* current = new TermElement;
	current = root;
	
	//Use evaluate on each node and add them all together
	while(current->next != NULL)
	{
		double temp = evaluate(current,x);
		runningTotal = runningTotal + temp;
		current = current->next;
	}
	
	return runningTotal;
}

//This method finds the derivative of each node and modifies said node accordingly
void derivative(TermElement* root)
{
	TermElement* current = new TermElement;
	current = root;

	//Just goes through entire list
	while(current->next != NULL)
	{
		current->coefficient = current->coefficient * current->degree;
		current->degree = current->degree - 1;
		current = current->next;
	}
}

//Deletes every node in the list, it was hard to test this so I put it in a infinite loop
//As Dan suggested, it seemed to work fine
void freeList(TermElement* root)
{
	TermElement* current = new TermElement;
	current = root;
	TermElement* next = new TermElement;

	while(current->next != NULL)
	{
		next = current->next;
		delete current;			
		current = next;
	}
}

//Print method for testing purposes
void printList(TermElement* root)
{
	TermElement* current = new TermElement;
	current = root;

	while(current != NULL)
	{
		printf("Degree: %d \n", current->degree);
		printf("Coefficient: %f \n", current->coefficient);
		printf("Done \n");
		printf("\n");
		current = current->next;
	}
}

//Main for testing purposes
int main()
{
	TermElement* root = addTerm(NULL, 1, 2);
	root = addTerm(root,7,8);
	root = addTerm(root,4,5);
	root = addTerm(root,3,1);
	root = addTerm(root,11,2);
	printf("Unmodified List: \n");
	printList(root);
	derivative(root);
	printf("After Derivation: \n");
	printList(root);
	
	double test = evaluatePolynomial(root, 2);
	printf("Total Evaluation: %f \n", test);

	return 0;
}
