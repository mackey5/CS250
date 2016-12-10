#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct X{
  char a;
  int i;
  char b;
  int *p;
};

struct tree_node
{
    char *str;
    struct tree_node *left;
    struct tree_node *right;
};

void memdump(char * p , int len)
/***
 * memdump: dump memory in bytes and in ascii code.
 * Example of dump:
 * 0xbeab36e0: 41 76 00 40 09 00 00 00 30 00 00 00 e4 36 ab be Av.@....0....6.. 
 * 0xbeab36f0: 00 00 00 00 00 00 28 40 48 65 6c 6c 6f 20 77 6f ......(@Hello wo
 *
 * Argument:
 *  p: the pointer to the target memory
 *  len: the length of dump output
 *
 ***/
{
  //p = (unsigned long)p+8;
  int counter = 0;
  while ((unsigned long)p % 16 != 0) {
    //printf("%p: \n", (unsigned long) p);
    p = (unsigned long) p -1;			//alignes the address to 16
    counter++;
    //printf("%p: \n", (unsigned long) p);
  }
  printf("%p: ", (unsigned long) p);	//prints first address

  for (int i = 0; i <= len-1; i++) {
    int c = p[i]&0xFF;
    if (counter > i)			//PIAZZA stated we do NOT need to print ".." to align it
	printf(".. ");
   else {

    printf("%02hhx ", c);

    if (i== (len-1) && (i % 16 != 15)) {
      int k = i;
      for (k; k%16 != 15; k++) {
        printf("   ");			//prints spaces in between
      }
     printf(" ");
     for (int j = k-15; j<=i; j++) {
	int d = p[j]&0xFF;
	printf("%c", (32<=d && d<=127)?d:'.');	//prints the ascii value of the value
     }
    printf("\n");
   }
   if (i%16 == 15) {
    printf(" ");
    for (int j = i-15; j<= i; j++) {
	int d = p[j]&0xFF;
	printf("%c", (32<=d && d<=127)?d:'.');	//also prints the ascii value, just in a different case
    }
    printf("\n");		//newline to seperate each address

    if (i< (len-1))					//prints next address
	printf("0x%x: ", (unsigned long) (p+i+1));
   }
  }}
}

struct tree_node *create_tree_node(char *str, struct tree_node *left, struct tree_node *right)
/***
 * create_tree_node: wrapper function for creating tree_node
 * 
 * You don't need to modify this part
 *
 * Argument:
 *  root: pointer to struct tree_node
 *
 ***/
{
    struct tree_node *node = (struct tree_node *) malloc(sizeof(struct tree_node));
    node->str = str;
    node->left = left;
    node->right = right;

    return node;
}

void free_tree(struct tree_node *root)
/***
 * free_tree: free allocated tree_node recursively
 * 
 * You don't need to modify this part
 *
 * Argument:
 *  root: pointer to struct tree_node
 *
 ***/
{
    if(root == NULL)
    {
        return;
    }

    free(root->str);
    free_tree(root->left);
    free_tree(root->right);
    free(root);

    return;
}

main() {
    char str[20];
    int a;
    int b;
    double y;
    int int_array[4];
    struct X x;
    char *s;

    printf("str:       %p\n", str);
    printf("&a:        %p\n", &a);
    printf("&b:        %p\n", &b);
    printf("&y:        %p\n", &y);
    printf("&x:        %p\n", &x);
    printf("int_array: %p\n", int_array);
    printf("\n");  

    // memdump before variable assignment
    printf("\n               -----Part 3.1 before variable assignment-----\n\n");
    memdump((char *) &x.a, 96);

    strcpy(str, "Hello World\n");
    a = 5;
    b = -5;
    y = 12.625;
    int_array[0] = 0;
    int_array[1] = 10;
    int_array[2] = 20;
    int_array[3] = 30;
    x.a = 'A';
    x.i = 9;
    x.b = '0';
    x.p = &x.i;

    // memdump after variable assignment
    printf("\n               -----Part 3.1 after variable assignment-----\n\n");
    memdump((char *) &x.a, 96);

    // The following assignments may cause a compiler warning. 'Safely' ignore the warning.
    // However, using *(int_array + n) instead of int_array[n] does not cause a warning.
    int_array[4] = 1685024583;
    int_array[5] = 543521122;
    int_array[6] = 1819438935;
    int_array[7] = 100;
    
    // memdump after buffer overflow
    printf("\n               -----Part 3.1 after buffer overflow-----\n\n");
    memdump((char *) &x.a, 96);

    struct tree_node *root = create_tree_node(NULL, NULL, NULL);
    printf("\n               -----Part 3.2 tree_node before variable assignment-----\n\n");
    memdump((char *) root, 256);

    /* Create the binary tree */
    s = strdup("to");
    struct tree_node *left = create_tree_node(s, NULL, NULL);
    s = strdup("lab8");
    struct tree_node *right = create_tree_node(s, NULL, NULL);
    s = strdup("Welcome");
    root->str = s;
    root->left = left;
    root->right = right;

    printf("\n               -----Part 3.2 tree_node after variable assignment-----\n\n");
    memdump((char *)root, 256);

    free_tree(root);
}
