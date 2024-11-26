#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node* next;
};

void Push(struct node** headRef, int data) {
    struct node* newNode = new struct node;
    newNode->data = data;
    newNode->next = *headRef;
    *headRef = newNode;
}

void Print(struct node* head) { 
    struct node* current = head;

    while(current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int Length(struct node* head) {
    struct node* current = head;
    int counter = 0;
    while (current != NULL) {
        current = current->next;
        counter++;
    }
    return counter;
}

void AddToEnd(struct node** headRef, int data) {
    struct node* current = *headRef;
    struct node* newNode = new struct node;
    newNode->data = data;
    newNode->next = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to reverse a linked list
void reverse(struct node** head_ref) {
    struct node* prev = NULL;
    struct node* current = *head_ref;
    struct node* next;

    while (current != NULL) {
        next = current->next; 
        current->next = prev;
        prev = current;        
        current = next;
    }
    *head_ref = prev;
}

bool compareLists(struct node* head1, struct node* head2) {
    struct node* temp1 = head1;
    struct node* temp2 = head2;

    while (temp1 && temp2) {
        if (temp1->data == temp2->data) {
            temp1 = temp1->next;
            temp2 = temp2->next;
        } else {
            return false;
        }
    }

    // Both lists should reach the end at the same time
    return (temp1 == NULL && temp2 == NULL);
}

// Function to check if a linked list is a palindrome
bool isPalindrome(struct node* head) {
    if (head == NULL || head->next == NULL)
        return true;

    struct node* slow = head;
    struct node* fast = head;
    struct node* prev_slow = head;
    struct node* midnode = NULL;  // To handle odd size list
    struct node* second_half;
    bool result = true;

    // Get the middle of the list
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;

        // We need previous of the slow pointer for linked lists with odd elements
        prev_slow = slow;
        slow = slow->next;
    }

    // For odd sized lists, skip the middle element
    if (fast != NULL) {
        midnode = slow;
        slow = slow->next;
    }

    // Terminate first half and reverse second half
    second_half = slow;
    prev_slow->next = NULL;
    reverse(&second_half);

    // Compare the two halves
    result = compareLists(head, second_half);

    // Reconstruct the original list by reversing the second half again
    reverse(&second_half);

    if (midnode != NULL) {  // If there was a middle node
        prev_slow->next = midnode;
        midnode->next = second_half;
    } else {
        prev_slow->next = second_half;
    }

    return result;
}

// Function to merge two sorted linked lists
struct node* mergeLists(struct node* head1, struct node* head2) {
    struct node dummy;  // Dummy node to form the new list
    struct node* tail = &dummy;
    dummy.next = NULL;

    while (true) {
        if (head1 == NULL) {
            tail->next = head2;
            break;
        } else if (head2 == NULL) {
            tail->next = head1;
            break;
        }

        if (head1->data <= head2->data) {
            tail->next = head1;
            head1 = head1->next;
        } else {
            tail->next = head2;
            head2 = head2->next;
        }

        tail = tail->next;
    }

    return dummy.next;
}

// method to free the memory, avoiding leaks
void freeList(struct node* head) {
	struct node* current = head;
	struct node* nextNode;

	while (current != NULL) { 
		nextNode = current->next;
		delete current;
		current = nextNode;
	}

}

int main() {
    // Test isPalindrome function
    struct node* head = NULL;
    AddToEnd(&head, 2);
    AddToEnd(&head, 3);
    AddToEnd(&head, 4);
    AddToEnd(&head, 3);
    AddToEnd(&head, 2);
    cout << "List: ";
    Print(head);
    if (isPalindrome(head)) {
        cout << "Output: true" << endl;
    } else {
        cout << "Output: false" << endl;
    }

    // Second test case for isPalindrome
    struct node* head2 = NULL;
    AddToEnd(&head2, 2);
    AddToEnd(&head2, 1);
    AddToEnd(&head2, 4);
    AddToEnd(&head2, 3);
    AddToEnd(&head2, 2);
    cout << "List: ";
    Print(head2);
    if (isPalindrome(head2)) {
        cout << "Output: true" << endl;
    } else {
        cout << "Output: false" << endl;
    }

    // Test mergeLists function
    struct node* head1 = NULL;
    AddToEnd(&head1, 8);
    AddToEnd(&head1, 10);
    struct node* head3 = NULL;
    AddToEnd(&head3, 6);
    AddToEnd(&head3, 8);
    AddToEnd(&head3, 9);

    struct node* merged = mergeLists(head1, head3);
    cout << "Merged List: ";
    Print(merged);

    freeList(head);
    freeList(head2);
    freeList(merged); // as head 3 is part of the merged list now.

    return 0;
}

