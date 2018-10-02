#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct document {
  void *state;
  void (*printItem)	   (struct document*, int);
  void (*startEnumeration) (struct document*);
  void (*stopEnumeration)  (struct document*);
} document_t;

typedef struct tree {
  int		value;
  int		nb_children;
  struct tree** child;
} tree_t;

int value_of  (tree_t* t) {
  return (t->value);
}

int is_leaf (tree_t* t) {
  return (t->nb_children == 0);
}

tree_t* leaf (int x) {
  tree_t* t = (tree_t*) malloc (sizeof (tree_t));
  t->value = x;
  t->nb_children = 0;
  t->child = NULL;
  return (t);
}

tree_t* node (int x, int size, ...) {
  va_list arguments;
  tree_t* t = (tree_t*) malloc (sizeof (tree_t));

  t->value = x;
  t->nb_children = size;
  t->child = (tree_t**) malloc (sizeof (tree_t*) * size);
  va_start (arguments, size);
  for (unsigned int i = 0; i < size; i++) {
    t->child[i] = va_arg (arguments, tree_t*);
  }
  va_end (arguments);
  return (t);
}

void printTree (tree_t* tree, document_t* doc) {
  if (is_leaf (tree)) {
    doc->printItem (doc, value_of (tree));
  } else {
    doc->printItem (doc, value_of (tree));
    doc->startEnumeration (doc);
    for (unsigned int i = 0; i < tree->nb_children; i++) {
      printTree (tree->child[i], doc);
    }
    doc->stopEnumeration (doc);
  }
}

void HTMLPrintItem (document_t* this, int x) {
  printf ("<li>%d</li>\n", x);
}

void HTMLStartEnumeration (document_t* this) {
  printf ("<ul>\n");
}

void HTMLStopEnumeration (document_t* this) {
  printf ("</ul>\n");
}

static document_t HTMLdoc = {
  NULL,
  HTMLPrintItem,
  HTMLStartEnumeration,
  HTMLStopEnumeration
};

void ConsolePrintItem (document_t* this, int x) {
  unsigned int offset = *((unsigned int*)this->state);
  char* indent = (char*) malloc (offset + 1);
  memset ((void*)indent, ' ', offset);
  indent[offset] = '\0';
  printf ("%s%d\n", indent, x);
}

void ConsoleStartEnumeration (document_t* this) {
  unsigned int* offset = (unsigned int*)this->state;
  (*offset) += 2;
}

void ConsoleStopEnumeration (document_t* this) {
  unsigned int* offset = (unsigned int*)this->state;
  (*offset) -= 2;
}

static unsigned int offset = 0;

static document_t Consoledoc = {
  &offset,
  ConsolePrintItem,
  ConsoleStartEnumeration,
  ConsoleStopEnumeration
};

int main (int argc, char** argv) {
  printTree (node (1, 2,
		   leaf (2),
		   node (3, 2,
			 leaf (4),
			 node (5, 2,
			       leaf (6),
			       leaf (7)))),
	     &Consoledoc);
}
