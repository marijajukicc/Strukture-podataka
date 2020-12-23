/*9. Napisati program koji omoguæava rad s binarnim stablom pretraživanja. Treba
omoguæiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Tree* Branch;
typedef struct Tree {
	int el;
	Branch left;
	Branch right;
}tree;

int print_inorder(Branch);
int print_postorder(Branch);
int print_preorder(Branch);
Branch delete_branch(int, Branch);
Branch insert_branch(int, Branch);
Branch search_tree(int, Branch);
Branch empty_tree(Branch);
Branch allocate_branch(int el);
Branch find_min(Branch min);

int main() {
	Branch root = (Branch)malloc(sizeof(tree));
	int find, delete;
	root = NULL;
	root = insert_branch(2, root);
	root = insert_branch(6, root);
	root = insert_branch(7, root);
	root = insert_branch(4, root);
	root = insert_branch(9, root);
	root = insert_branch(1, root);

	puts("In order:");
	print_inorder(root);
	puts("\nIn postorder:");
	print_postorder(root);
	puts("\nIn preorder:");
	print_preorder(root);

	printf("\nInput the element you are trying to delete: ");
	scanf("%d", &delete);
	Branch deleted = delete_branch(delete, root);
	puts("\nTree now looks:");
	print_inorder(root);
	printf("\nInput the element you are trying to find: ");
	scanf(" %d", &find);
	Branch found = search_tree(find, root);
	if (found != NULL) {
		printf("We found your tree %d", found->el);
	}
	else printf("We couldn't find the tree you are looking for\n");
	return 0;
}

Branch empty_tree(Branch new) {
	if (new != NULL) {
		empty_tree(new->left);
		empty_tree(new->right);
		free(new);
	}
	return NULL;
}

Branch search_tree(int el, Branch tree) {
	if (tree == NULL)
		return NULL;
	else if (el < tree->el) {
		return search_tree(el, tree->left);
	}
	else if (el > tree->el) {
		return search_tree(el, tree->right);
	}
	return tree;
}

Branch insert_branch(int el, Branch tree) {
	if (tree == NULL) {
		tree = allocate_branch(el);
	}
	else if (el < tree->el)
		tree->left = insert_branch(el, tree->left);
	else if (el > tree->el)
		tree->right = insert_branch(el, tree->right);
	return tree;
}

Branch allocate_branch(int el) {
	Branch a;
	a = (Branch)malloc(sizeof(tree));
	if (a == NULL) {
		puts("Allocation failed");
		return NULL;
	}
	a->el = el;
	a->left = NULL;
	a->right = NULL;
	return a;
}

int print_inorder(Branch b) {
	if (b != NULL) {
		print_inorder(b->left);
		printf("%d ", b->el);
		print_inorder(b->right);
	}
	return 0;
}
int print_postorder(Branch b) {
	if (b != NULL) {
		print_postorder(b->left);
		print_postorder(b->right);
		printf("%d ", b->el);
	}
	return 0;
}
int print_preorder(Branch b) {
	if (b != NULL) {
		printf("%d ", b->el);
		print_preorder(b->left);
		print_preorder(b->right);
	}
	return 0;
}

Branch delete_branch(int el, Branch b) {
	Branch temp;
	if (b == NULL) {
		puts("There is no branch to delete");
		return NULL;
	}
	else if (el < b->el)
		b->left = delete_branch(el, b->left);
	else if (el > b->el)
		b->right = delete_branch(el, b->right);
	else {
		if (b->left != NULL && b->right != NULL) {
			temp = find_min(b->right);
			printf("\nNajmanji je %d\n", temp->el);
			b->el = temp->el;
			b->right = delete_branch(b->el, b->right);
		}
		else {
			temp = b;
			if (b->left == NULL)
				b = b->right;
			else
				b = b->left;
			free(temp);
		}
	}
	return b;
}

Branch find_min(Branch min) {
	if (min != NULL) {
		while (min->left != NULL)
			min = min->left;
	}
	return min;
}